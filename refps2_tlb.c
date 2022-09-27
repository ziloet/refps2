#define RAM_SIZE (32 << 20)
#define BOOTROM_SIZE (4 << 20)
#define DVD_PLAYER_ROM_SIZE (4 << 20)

namespace Ps2MemSize
{
  static const uint MainRam = _32mb;      // 32 MB main memory!
  static const uint Rom   = _1mb * 4;     // 4 MB main rom
  static const uint Rom1    = 0x00040000;   // DVD player
  static const uint Rom2    = 0x00080000;   // Chinese rom extension (?)
  static const uint ERom    = 0x001C0000;   // DVD player extensions (?)
  static const uint Hardware  = _64kb;
  static const uint Scratch = _16kb;

  static const uint IopRam  = _1mb * 2;     // 2MB main ram on the IOP.
  static const uint IopHardware = _64kb;

  static const uint GSregs = 0x00002000;      // 8k for the GS registers and stuff.
}

typedef u8 mem8_t;
typedef u16 mem16_t;
typedef u32 mem32_t;
typedef u64 mem64_t;
typedef u128 mem128_t;


#define VTLB_UsePageFaulting 0

#if VTLB_UsePageFaulting

// The order of the components in this struct *matter* -- it has been laid out so that the
// full breadth of PS2 RAM and ROM mappings are directly supported.
struct EEVM_MemoryAllocMess
{
  uint8_t RAM[RAM_SIZE];
  uint8_t Padding1[0x1e000000 - RAM_SIZE];
  uint8_t DVDPlayerROM[DVD_PLAYER_ROM_SIZE];
  uint8_t Padding2[];

  uint8_t ROM[ROM_SIZE];
  u8 (&Main)[Ps2MemSize::MainRam];        // Main memory (hard-wired to 32MB)

  u8 _padding1[0x1e000000-Ps2MemSize::MainRam]
  u8 (&ROM1)[Ps2MemSize::Rom1];       // DVD player

  u8 _padding2[0x1e040000-(0x1e000000+Ps2MemSize::Rom1)]
  u8 (&EROM)[Ps2MemSize::ERom];       // DVD player extensions

  u8 _padding3[0x1e400000-(0x1e040000+Ps2MemSize::EROM)]
  u8 (&ROM2)[Ps2MemSize::Rom2];       // Chinese extensions

  u8 _padding4[0x1fc00000-(0x1e040000+Ps2MemSize::Rom2)];
  u8 (&ROM)[Ps2MemSize::Rom];       // Boot rom (4MB)
};

#else

struct EEVM_MemoryAllocMess
{
  u8 Main[Ps2MemSize::MainRam];     // Main memory (hard-wired to 32MB)
  u8 Scratch[Ps2MemSize::Scratch];    // Scratchpad!
  u8 ROM[Ps2MemSize::Rom];        // Boot rom (4MB)
  u8 ROM1[Ps2MemSize::Rom1];        // DVD player
  u8 ROM2[Ps2MemSize::Rom2];        // Chinese extensions
  u8 EROM[Ps2MemSize::ERom];        // DVD player extensions

  // Two 1 megabyte (max DMA) buffers for reading and writing to high memory (>32MB).
  // Such accesses are not documented as causing bus errors but as the memory does
  // not exist, reads should continue to return 0 and writes should be discarded.
  // Probably.

  u8 ZeroRead[_1mb];
  u8 ZeroWrite[_1mb];
};

#endif

struct IopVM_MemoryAllocMess
{
  u8 Main[Ps2MemSize::IopRam];      // Main memory (hard-wired to 2MB)
  u8 P[_64kb];              // I really have no idea what this is... --air
  u8 Sif[0x100];              // a few special SIF/SBUS registers (likely not needed)
};








#include "EventSource.h"
#include <atomic>

typedef struct
{
  uptr addr;
} page_fault_info;


void PageFaultInfo_Init(uptr address)
{
  addr = address;
}
















/*
  EE physical map :
  [0000 0000,1000 0000) -> Ram (mirrored ?)
  [1000 0000,1400 0000) -> Registers
  [1400 0000,1fc0 0000) -> Reserved (ingored writes, 'random' reads)
  [1fc0 0000,2000 0000) -> Boot ROM

  [2000 0000,4000 0000) -> Unmapped (BUS ERROR)
  [4000 0000,8000 0000) -> "Extended memory", probably unmapped (BUS ERROR) on retail ps2's :)
  [8000 0000,FFFF FFFF] -> Unmapped (BUS ERROR)

  vtlb/phy only supports the [0000 0000,2000 0000) region, with 4k pages.
  vtlb/vmap supports mapping to either of these locations, or some other (externaly) specified address.
*/



static void GoemonTlbMissDebug()
{
  // 0x3d5580 is the address of the TLB cache
  GoemonTlb* tlb = (GoemonTlb*)&eeMem->Main[0x3d5580];

  for (u32 i = 0; i < 150; i++) {
    if (tlb[i].valid == 0x1 && tlb[i].low_add != tlb[i].high_add)
      DevCon.WriteLn("GoemonTlbMissDebug: Entry %d is valid. Key %x. From V:0x%8.8x to V:0x%8.8x (P:0x%8.8x)", i, tlb[i].key, tlb[i].low_add, tlb[i].high_add, tlb[i].physical_add);
    else if (tlb[i].low_add != tlb[i].high_add)
      DevCon.WriteLn("GoemonTlbMissDebug: Entry %d is invalid. Key %x. From V:0x%8.8x to V:0x%8.8x (P:0x%8.8x)", i, tlb[i].key, tlb[i].low_add, tlb[i].high_add, tlb[i].physical_add);
  }
}

void __fastcall GoemonPreloadTlb()
{
  // 0x3d5580 is the address of the TLB cache table
  GoemonTlb* tlb = (GoemonTlb*)&eeMem->Main[0x3d5580];

  for (u32 i = 0; i < 150; i++) {
    if (tlb[i].valid == 0x1 && tlb[i].low_add != tlb[i].high_add) {

      u32 size  = tlb[i].high_add - tlb[i].low_add;
      u32 vaddr = tlb[i].low_add;
      u32 paddr = tlb[i].physical_add;

      // TODO: The old code (commented below) seems to check specifically for handler 0.  Is this really correct?
      //if ((uptr)vtlbdata.vmap[vaddr>>VTLB_PAGE_BITS] == POINTER_SIGN_BIT) {
      auto vmv = vtlbdata.vmap[vaddr>>VTLB_PAGE_BITS];
      if (vmv.isHandler(vaddr) && vmv.assumeHandlerGetID() == 0) {
        DevCon.WriteLn("GoemonPreloadTlb: Entry %d. Key %x. From V:0x%8.8x to P:0x%8.8x (%d pages)", i, tlb[i].key, vaddr, paddr, size >> VTLB_PAGE_BITS);
        vtlb_VMap(           vaddr , paddr, size);
        vtlb_VMap(0x20000000|vaddr , paddr, size);
      }
    }
  }
}

void __fastcall GoemonUnloadTlb(u32 key)
{
  // 0x3d5580 is the address of the TLB cache table
  GoemonTlb* tlb = (GoemonTlb*)&eeMem->Main[0x3d5580];
  for (u32 i = 0; i < 150; i++) {
    if (tlb[i].key == key) {
      if (tlb[i].valid == 0x1) {
        u32 size  = tlb[i].high_add - tlb[i].low_add;
        u32 vaddr = tlb[i].low_add;
        DevCon.WriteLn("GoemonUnloadTlb: Entry %d. Key %x. From V:0x%8.8x to V:0x%8.8x (%d pages)", i, tlb[i].key, vaddr, vaddr+size, size >> VTLB_PAGE_BITS);

        vtlb_VMapUnmap(           vaddr , size);
        vtlb_VMapUnmap(0x20000000|vaddr , size);

        // Unmap the tlb in game cache table
        // Note: Game copy FEFEFEFE for others data
        tlb[i].valid    = 0;
        tlb[i].key      = 0xFEFEFEFE;
        tlb[i].low_add  = 0xFEFEFEFE;
        tlb[i].high_add = 0xFEFEFEFE;
      } else {
        DevCon.Error("GoemonUnloadTlb: Entry %d is not valid. Key %x", i, tlb[i].key);
      }
    }
  }
}

// Generates a tlbMiss Exception
static __ri void vtlb_Miss(u32 addr,u32 mode)
{
  if (EmuConfig.Gamefixes.GoemonTlbHack)
    GoemonTlbMissDebug();

  // Hack to handle expected tlb miss by some games.
  if (Cpu == &intCpu) {
    if (mode)
      cpuTlbMissW(addr, cpuRegs.branch);
    else
      cpuTlbMissR(addr, cpuRegs.branch);

    // Exception handled. Current instruction need to be stopped
    throw Exception::CancelInstruction();
  }

  if( IsDevBuild )
    Cpu->ThrowCpuException( R5900Exception::TLBMiss( addr, !!mode ) );
  else
  {
    static int spamStop = 0;
    if ( spamStop++ < 50 )
      Console.Error( R5900Exception::TLBMiss( addr, !!mode ).FormatMessage() );
  }
}

// BusError exception: more serious than a TLB miss.  If properly emulated the PS2 kernel
// itself would invoke a diagnostic/assertion screen that displays the cpu state at the
// time of the exception.
static __ri void vtlb_BusError(u32 addr,u32 mode)
{
  // The exception terminate the program on linux which is very annoying
  // Just disable it for the moment
#ifdef __linux__
  if (0)
#else
  if( IsDevBuild )
#endif
    Cpu->ThrowCpuException( R5900Exception::BusError( addr, !!mode ) );
  else
    Console.Error( R5900Exception::TLBMiss( addr, !!mode ).FormatMessage() );
}


// ===========================================================================================
//  VTLB Public API -- Init/Term/RegisterHandler stuff 
// ===========================================================================================
//

// Assigns or re-assigns the callbacks for a VTLB memory handler.  The handler defines specific behavior
// for how memory pages bound to the handler are read from / written to.  If any of the handler pointers
// are NULL, the memory operations will be mapped to the BusError handler (thus generating BusError
// exceptions if the emulated app attempts to access them).
//
// Note: All handlers persist across calls to vtlb_Reset(), but are wiped/invalidated by calls to vtlb_Init()
//
__ri void vtlb_ReassignHandler( vtlbHandler rv,
                 vtlbMemR8FP* r8,vtlbMemR16FP* r16,vtlbMemR32FP* r32,vtlbMemR64FP* r64,vtlbMemR128FP* r128,
                 vtlbMemW8FP* w8,vtlbMemW16FP* w16,vtlbMemW32FP* w32,vtlbMemW64FP* w64,vtlbMemW128FP* w128 )
{
  pxAssume(rv < VTLB_HANDLER_ITEMS);

  vtlbdata.RWFT[0][0][rv] = (void*)((r8!=0)   ? r8  : vtlbDefaultPhyRead8);
  vtlbdata.RWFT[1][0][rv] = (void*)((r16!=0)  ? r16 : vtlbDefaultPhyRead16);
  vtlbdata.RWFT[2][0][rv] = (void*)((r32!=0)  ? r32 : vtlbDefaultPhyRead32);
  vtlbdata.RWFT[3][0][rv] = (void*)((r64!=0)  ? r64 : vtlbDefaultPhyRead64);
  vtlbdata.RWFT[4][0][rv] = (void*)((r128!=0) ? r128  : vtlbDefaultPhyRead128);

  vtlbdata.RWFT[0][1][rv] = (void*)((w8!=0)   ? w8  : vtlbDefaultPhyWrite8);
  vtlbdata.RWFT[1][1][rv] = (void*)((w16!=0)  ? w16 : vtlbDefaultPhyWrite16);
  vtlbdata.RWFT[2][1][rv] = (void*)((w32!=0)  ? w32 : vtlbDefaultPhyWrite32);
  vtlbdata.RWFT[3][1][rv] = (void*)((w64!=0)  ? w64 : vtlbDefaultPhyWrite64);
  vtlbdata.RWFT[4][1][rv] = (void*)((w128!=0) ? w128  : vtlbDefaultPhyWrite128);
}

vtlbHandler vtlb_NewHandler()
{
  pxAssertDev( vtlbHandlerCount < VTLB_HANDLER_ITEMS, "VTLB handler count overflow!" );
  return vtlbHandlerCount++;
}

// Registers a handler into the VTLB's internal handler array.  The handler defines specific behavior
// for how memory pages bound to the handler are read from / written to.  If any of the handler pointers
// are NULL, the memory operations will be mapped to the BusError handler (thus generating BusError
// exceptions if the emulated app attempts to access them).
//
// Note: All handlers persist across calls to vtlb_Reset(), but are wiped/invalidated by calls to vtlb_Init()
//
// Returns a handle for the newly created handler  See vtlb_MapHandler for use of the return value.
//
__ri vtlbHandler vtlb_RegisterHandler(  vtlbMemR8FP* r8,vtlbMemR16FP* r16,vtlbMemR32FP* r32,vtlbMemR64FP* r64,vtlbMemR128FP* r128,
                    vtlbMemW8FP* w8,vtlbMemW16FP* w16,vtlbMemW32FP* w32,vtlbMemW64FP* w64,vtlbMemW128FP* w128)
{
  vtlbHandler rv = vtlb_NewHandler();
  vtlb_ReassignHandler( rv, r8, r16, r32, r64, r128, w8, w16, w32, w64, w128 );
  return rv;
}


// Maps the given hander (created with vtlb_RegisterHandler) to the specified memory region.
// New mappings always assume priority over previous mappings, so place "generic" mappings for
// large areas of memory first, and then specialize specific small regions of memory afterward.
// A single handler can be mapped to many different regions by using multiple calls to this
// function.
//
// The memory region start and size parameters must be pagesize aligned.
void vtlb_MapHandler(vtlbHandler handler, u32 start, u32 size)
{
  verify(0==(start&VTLB_PAGE_MASK));
  verify(0==(size&VTLB_PAGE_MASK) && size>0);

  u32 end = start + (size - VTLB_PAGE_SIZE);
  pxAssume( (end>>VTLB_PAGE_BITS) < ArraySize(vtlbdata.pmap) );

  while (start <= end)
  {
    vtlbdata.pmap[start>>VTLB_PAGE_BITS] = VTLBPhysical::fromHandler(handler);
    start += VTLB_PAGE_SIZE;
  }
}

void vtlb_MapBlock(void* base, u32 start, u32 size, u32 blocksize)
{
  verify(0==(start&VTLB_PAGE_MASK));
  verify(0==(size&VTLB_PAGE_MASK) && size>0);
  if(!blocksize)
    blocksize = size;
  verify(0==(blocksize&VTLB_PAGE_MASK) && blocksize>0);
  verify(0==(size%blocksize));

  sptr baseint = (sptr)base;
  u32 end = start + (size - VTLB_PAGE_SIZE);
  verify((end>>VTLB_PAGE_BITS) < ArraySize(vtlbdata.pmap));

  while (start <= end)
  {
    u32 loopsz = blocksize;
    sptr ptr = baseint;

    while (loopsz > 0)
    {
      vtlbdata.pmap[start>>VTLB_PAGE_BITS] = VTLBPhysical::fromPointer(ptr);

      start += VTLB_PAGE_SIZE;
      ptr   += VTLB_PAGE_SIZE;
      loopsz  -= VTLB_PAGE_SIZE;
    }
  }
}

void vtlb_Mirror(u32 new_region,u32 start,u32 size)
{
  verify(0==(new_region&VTLB_PAGE_MASK));
  verify(0==(start&VTLB_PAGE_MASK));
  verify(0==(size&VTLB_PAGE_MASK) && size>0);

  u32 end = start + (size-VTLB_PAGE_SIZE);
  verify((end>>VTLB_PAGE_BITS) < ArraySize(vtlbdata.pmap));

  while(start <= end)
  {
    vtlbdata.pmap[start>>VTLB_PAGE_BITS] = vtlbdata.pmap[new_region>>VTLB_PAGE_BITS];

    start   += VTLB_PAGE_SIZE;
    new_region  += VTLB_PAGE_SIZE;
  }
}

__fi void* vtlb_GetPhyPtr(u32 paddr)
{
  if (paddr>=VTLB_PMAP_SZ || vtlbdata.pmap[paddr>>VTLB_PAGE_BITS].isHandler())
    return NULL;
  else
    return reinterpret_cast<void*>(vtlbdata.pmap[paddr>>VTLB_PAGE_BITS].assumePtr()+(paddr&VTLB_PAGE_MASK));
}

__fi u32 vtlb_V2P(u32 vaddr)
{
  u32 paddr = vtlbdata.ppmap[vaddr>>VTLB_PAGE_BITS];
  paddr    |= vaddr & VTLB_PAGE_MASK;
  return paddr;
}

//virtual mappings
//TODO: Add invalid paddr checks
void vtlb_VMap(u32 vaddr,u32 paddr,u32 size)
{
  verify(0==(vaddr&VTLB_PAGE_MASK));
  verify(0==(paddr&VTLB_PAGE_MASK));
  verify(0==(size&VTLB_PAGE_MASK) && size>0);

  while (size > 0)
  {
    VTLBVirtual vmv;
    if (paddr >= VTLB_PMAP_SZ) {
      if ((s32)paddr >= 0) {
        vmv = VTLBVirtual(VTLBPhysical::fromHandler(UnmappedPhyHandler0), paddr, vaddr);
      } else {
        vmv = VTLBVirtual(VTLBPhysical::fromHandler(UnmappedPhyHandler1), paddr & ~(1<<31), vaddr);
      }
    } else {
      vmv = VTLBVirtual(vtlbdata.pmap[paddr>>VTLB_PAGE_BITS], paddr, vaddr);
    }

    vtlbdata.vmap[vaddr>>VTLB_PAGE_BITS] = vmv;
    if (vtlbdata.ppmap)
      if (!(vaddr & 0x80000000)) // those address are already physical don't change them
        vtlbdata.ppmap[vaddr>>VTLB_PAGE_BITS] = paddr & ~VTLB_PAGE_MASK;

    vaddr += VTLB_PAGE_SIZE;
    paddr += VTLB_PAGE_SIZE;
    size -= VTLB_PAGE_SIZE;
  }
}

void vtlb_VMapBuffer(u32 vaddr,void* buffer,u32 size)
{
  verify(0==(vaddr&VTLB_PAGE_MASK));
  verify(0==(size&VTLB_PAGE_MASK) && size>0);

  uptr bu8 = (uptr)buffer;
  while (size > 0)
  {
    vtlbdata.vmap[vaddr>>VTLB_PAGE_BITS] = VTLBVirtual::fromPointer(bu8, vaddr);
    vaddr += VTLB_PAGE_SIZE;
    bu8 += VTLB_PAGE_SIZE;
    size -= VTLB_PAGE_SIZE;
  }
}

void vtlb_VMapUnmap(u32 vaddr,u32 size)
{
  verify(0==(vaddr&VTLB_PAGE_MASK));
  verify(0==(size&VTLB_PAGE_MASK) && size>0);

  while (size > 0)
  {

    VTLBVirtual handl;
    if ((s32)vaddr >= 0) {
      handl = VTLBVirtual(VTLBPhysical::fromHandler(UnmappedVirtHandler0), vaddr, vaddr);
    } else {
      handl = VTLBVirtual(VTLBPhysical::fromHandler(UnmappedVirtHandler1), vaddr & ~(1<<31), vaddr);
    }

    vtlbdata.vmap[vaddr>>VTLB_PAGE_BITS] = handl;
    vaddr += VTLB_PAGE_SIZE;
    size -= VTLB_PAGE_SIZE;
  }
}

// vtlb_Init -- Clears vtlb handlers and memory mappings.
void vtlb_Init()
{
  vtlbHandlerCount=0;
  memzero(vtlbdata.RWFT);

#define VTLB_BuildUnmappedHandler(baseName, highBit) \
  baseName##ReadSm<mem8_t,0>,   baseName##ReadSm<mem16_t,0>,  baseName##ReadSm<mem32_t,0>, \
  baseName##ReadLg<mem64_t,0>,  baseName##ReadLg<mem128_t,0>, \
  baseName##WriteSm<mem8_t,0>,  baseName##WriteSm<mem16_t,0>, baseName##WriteSm<mem32_t,0>, \
  baseName##WriteLg<mem64_t,0>, baseName##WriteLg<mem128_t,0>

  //Register default handlers
  //Unmapped Virt handlers _MUST_ be registered first.
  //On address translation the top bit cannot be preserved.This is not normaly a problem since
  //the physical address space can be 'compressed' to just 29 bits.However, to properly handle exceptions
  //there must be a way to get the full address back.Thats why i use these 2 functions and encode the hi bit directly into em :)

  UnmappedVirtHandler0 = vtlb_RegisterHandler( VTLB_BuildUnmappedHandler(vtlbUnmappedV, 0) );
  UnmappedVirtHandler1 = vtlb_RegisterHandler( VTLB_BuildUnmappedHandler(vtlbUnmappedV, 0x80000000) );

  UnmappedPhyHandler0 = vtlb_RegisterHandler( VTLB_BuildUnmappedHandler(vtlbUnmappedP, 0) );
  UnmappedPhyHandler1 = vtlb_RegisterHandler( VTLB_BuildUnmappedHandler(vtlbUnmappedP, 0x80000000) );

  DefaultPhyHandler = vtlb_RegisterHandler(0,0,0,0,0,0,0,0,0,0);

  //done !

  //Setup the initial mappings
  vtlb_MapHandler(DefaultPhyHandler,0,VTLB_PMAP_SZ);

  //Set the V space as unmapped
  vtlb_VMapUnmap(0,(VTLB_VMAP_ITEMS-1)*VTLB_PAGE_SIZE);
  //yeah i know, its stupid .. but this code has to be here for now ;p
  vtlb_VMapUnmap((VTLB_VMAP_ITEMS-1)*VTLB_PAGE_SIZE,VTLB_PAGE_SIZE);

  // The LUT is only used for 1 game so we allocate it only when the gamefix is enabled (save 4MB)
  if (EmuConfig.Gamefixes.GoemonTlbHack)
    vtlb_Alloc_Ppmap();

  extern void vtlb_dynarec_init();
  vtlb_dynarec_init();
}

// vtlb_Reset -- Performs a COP0-level reset of the PS2's TLB.
// This function should probably be part of the COP0 rather than here in VTLB.
void vtlb_Reset()
{
  for(int i=0; i<48; i++) UnmapTLB(i);
}

void vtlb_Term()
{
  //nothing to do for now
}

constexpr size_t VMAP_SIZE = sizeof(VTLBVirtual) * VTLB_VMAP_ITEMS;

// Reserves the vtlb core allocation used by various emulation components!
// [TODO] basemem - request allocating memory at the specified virtual location, which can allow
//    for easier debugging and/or 3rd party cheat programs.  If 0, the operating system
//    default is used.
void vtlb_Core_Alloc()
{
  // Can't return regions to the bump allocator
  static VTLBVirtual* vmap = nullptr;
  if (!vmap)
    vmap = (VTLBVirtual*)GetVmMemory().BumpAllocator().Alloc(VMAP_SIZE);
  if (!vtlbdata.vmap)
  {
    bool okay = HostSys::MmapCommitPtr(vmap, VMAP_SIZE, PageProtectionMode().Read().Write());
    if (okay) {
      vtlbdata.vmap = vmap;
    } else {
      throw Exception::OutOfMemory( L"VTLB Virtual Address Translation LUT" )
        .SetDiagMsg(pxsFmt("(%u megs)", VTLB_VMAP_ITEMS * sizeof(*vtlbdata.vmap) / _1mb)
      );
    }
  }
}

// The LUT is only used for 1 game so we allocate it only when the gamefix is enabled (save 4MB)
// However automatic gamefix is done after the standard init so a new init function was done.
void vtlb_Alloc_Ppmap()
{
  if (vtlbdata.ppmap) return;

  vtlbdata.ppmap = (u32*)_aligned_malloc( VTLB_VMAP_ITEMS * sizeof(*vtlbdata.ppmap), 16 );
  if (!vtlbdata.ppmap)
    throw Exception::OutOfMemory( L"VTLB PS2 Virtual Address Translation LUT" )
      .SetDiagMsg(pxsFmt("(%u megs)", VTLB_VMAP_ITEMS * sizeof(*vtlbdata.ppmap) / _1mb));

  // By default a 1:1 virtual to physical mapping
  for (u32 i = 0; i < VTLB_VMAP_ITEMS; i++)
    vtlbdata.ppmap[i] = i<<VTLB_PAGE_BITS;
}

void vtlb_Core_Free()
{
  if (vtlbdata.vmap) {
    HostSys::MmapResetPtr(vtlbdata.vmap, VMAP_SIZE);
    vtlbdata.vmap = nullptr;
  }
  safe_aligned_free( vtlbdata.ppmap );
}











static bool
DataCacheIsEnabled(ee_cpu* CPU)
{
  uint32_t Config = CPU->COP0.Registers.Config;
  bool Result = (Config >> 16) & 0x1;
  return Result;
}




static bool
CheckCache(uint32_t addr)
{
  bool Result = false;
  if(IsDataCacheEnabled(CPU))
  {
    for(int EntryIndex = 1; EntryIndex < TLB_ENTRIES_COUNT; EntryIndex += 1)
    {
      uint32_t Mask = CPU->TLB[EntryIndex].PageMask;
      Result  = (((tlb[EntryIndex].EntryLo1 & 0x38) >> 3) == 0x3) && ((addr >= tlb[EntryIndex].PFN1) && (addr <= tlb[EntryIndex].PFN1 + mask));
      Result |= (((tlb[EntryIndex].EntryLo0 & 0x38) >> 3) == 0x3) && ((addr >= tlb[EntryIndex].PFN0) && (addr <= tlb[EntryIndex].PFN0 + mask));
      if(Result) 
      { 
        break;
      }
    }
  }
  return Result;
}


template< typename DataType >
static DataType vtlb_memRead(u32 addr)
{
  static const uint DataSize = sizeof(DataType) * 8;
  auto vmv = vtlbdata.vmap[addr>>VTLB_PAGE_BITS];

  if (!vmv.isHandler(addr))
  {
    if (!CHECK_EEREC) 
    {
      if(CHECK_CACHE && CheckCache(addr)) 
      {
        switch( DataSize )
        {
          case 8: 
            return readCache8(addr);
            break;
          case 16: 
            return readCache16(addr);
            break;
          case 32: 
            return readCache32(addr);
            break;

          jNO_DEFAULT;
        }
      }
    }
    return *reinterpret_cast<DataType*>(vmv.assumePtr(addr));
  }

  //has to: translate, find function, call function
  u32 paddr=vmv.assumeHandlerGetPAddr(addr);
  //Console.WriteLn("Translated 0x%08X to 0x%08X", addr,paddr);
  //return reinterpret_cast<TemplateHelper<DataSize,false>::HandlerType*>(vtlbdata.RWFT[TemplateHelper<DataSize,false>::sidx][0][hand])(paddr,data);

  switch( DataSize )
  {
    case 8:
      return vmv.assumeHandler< 8, false>()(paddr);
    case 16:
      return vmv.assumeHandler<16, false>()(paddr);
    case 32:
      return vmv.assumeHandler<32, false>()(paddr);

    jNO_DEFAULT;
  }

  return 0;   // technically unreachable, but suppresses warnings.
}

static void
TLB_MemoryRead64(u32 mem, mem64_t *out)
{
  auto vmv = vtlbdata.vmap[mem>>VTLB_PAGE_BITS];

  if (!vmv.isHandler(mem))
  {
    if (!CHECK_EEREC) {
      if(CHECK_CACHE && CheckCache(mem)) 
      {
        *out = readCache64(mem);
        return;
      }
    }

    *out = *(mem64_t*)vmv.assumePtr(mem);
  }
  else
  {
    //has to: translate, find function, call function
    u32 paddr = vmv.assumeHandlerGetPAddr(mem);
    //Console.WriteLn("Translated 0x%08X to 0x%08X", addr,paddr);
    vmv.assumeHandler<64, false>()(paddr, out);
  }
}


static mem128_t
TLB_MemoryRead128(u32 mem)
{
  auto vmv = vtlbdata.vmap[mem>>VTLB_PAGE_BITS];

  if (!vmv.isHandler(mem))
  {
    if (!CHECK_EEREC) 
    {
      if(CHECK_CACHE && CheckCache(mem)) 
      {
        out->lo = readCache64(mem);
        out->hi = readCache64(mem+8);
        return;
      }
    }

    CopyQWC(out,(void*)vmv.assumePtr(mem));
  }
  else
  {
    //has to: translate, find function, call function
    u32 paddr = vmv.assumeHandlerGetPAddr(mem);
    //Console.WriteLn("Translated 0x%08X to 0x%08X", addr,paddr);
    vmv.assumeHandler<128, false>()(paddr, out);
  }
}


template< typename DataType >
void __fastcall vtlb_memWrite(u32 addr, DataType data)
{
  static const uint DataSize = sizeof(DataType) * 8;

  auto vmv = vtlbdata.vmap[addr>>VTLB_PAGE_BITS];

  if (!vmv.isHandler(addr))
  {   
    if (!CHECK_EEREC) 
    {
      if(CHECK_CACHE && CheckCache(addr)) 
      {
        switch( DataSize )
        {
        case 8: 
          writeCache8(addr, data);
          return;
        case 16:
          writeCache16(addr, data);
          return;
        case 32:
          writeCache32(addr, data);
          return;
        }
      }
    }

    *reinterpret_cast<DataType*>(vmv.assumePtr(addr))=data;
  }
  else
  {
    //has to: translate, find function, call function
    u32 paddr = vmv.assumeHandlerGetPAddr(addr);
    //Console.WriteLn("Translated 0x%08X to 0x%08X", addr,paddr);
    return vmv.assumeHandler<sizeof(DataType)*8, true>()(paddr, data);
  }
}

void __fastcall vtlb_memWrite64(u32 mem, const mem64_t* value)
{
  auto vmv = vtlbdata.vmap[mem>>VTLB_PAGE_BITS];

  if (!vmv.isHandler(mem))
  {   
    if (!CHECK_EEREC) 
    {
      if(CHECK_CACHE && CheckCache(mem)) 
      {
        writeCache64(mem, *value);
        return;
      }
    }

    *(mem64_t*)vmv.assumePtr(mem) = *value;
  }
  else
  {
    //has to: translate, find function, call function
    u32 paddr = vmv.assumeHandlerGetPAddr(mem);
    //Console.WriteLn("Translated 0x%08X to 0x%08X", addr,paddr);

    vmv.assumeHandler<64, true>()(paddr, value);
  }
}

void __fastcall vtlb_memWrite128(u32 mem, const mem128_t *value)
{
  auto vmv = vtlbdata.vmap[mem>>VTLB_PAGE_BITS];

  if (!vmv.isHandler(mem))
  {
    if (!CHECK_EEREC) 
    {
      if(CHECK_CACHE && CheckCache(mem)) 
      {
        writeCache128(mem, value);
        return;
      }
    }

    CopyQWC((void*)vmv.assumePtr(mem), value);
  }
  else
  {
    //has to: translate, find function, call function
    u32 paddr = vmv.assumeHandlerGetPAddr(mem);
    //Console.WriteLn("Translated 0x%08X to 0x%08X", addr,paddr);

    vmv.assumeHandler<128, true>()(paddr, value);
  }
}






#if 0

static bool
TLB_EvenPageMappingIsValid(tlb_entry)
{
  bool Result = Entry[0] & 
}

static bool
TLB_IsDirty(tlb_entry Entry)
{
  bool Result = Entry[1] & (1 << 2);
  return Result;
}

static uint32_t
TLB_CacheMode(tlb_entry Entry)
{
  uint32_t Result = Entry[1] & (0x7 << 3);
  return Result;
}

static uint32_t
TLB_PFN(tlb_entry Entry)
{

}

static uint32_t
TLB_ScratchPad(tlb_entry Entry)
{
  uint32_t Result = Entry[1] & (1 << 31);
  return Result;
}

static uint32_t
TLB_AddressSpaceID(tlb_entry Entry)
{
  uint32_t Result = Entry[2] & 0xff;
  return Result;
}

static uint32_t
TLB_Global(tlb_entry Entry)
{
  uint32_t Result = Entry[2] & << (1 << 12);
  return Result;
}

static uint32_t
TLB_VPN2(tlb_entry Entry)
{
  uint32_t Result = Entry[2] & (0x7ffff << 13);
  return Result;
}

static uint32_t
TLB_Mask(tlb_entry Entry)
{
  uint32_t Result = Entry[3] & (0xfff << 13);
  return Result;
}

static uint32_t
TranslateAddress(uint32_t VirtualAddress)
{

}

#endif