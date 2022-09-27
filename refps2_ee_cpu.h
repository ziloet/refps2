#define SIZEOF_INSTRUCTION 4

enum virtual_addresses
{
  VIRTUAL_ADDRESS_RAM = 0x80000000,
  VIRTUAL_ADDRESS_ROM = 0xbfc00000,
};

enum exceptions_level2
{
  EXCEPTION_RESET        = 0,
  EXCEPTION_NMI          = 1,
  EXCEPTION_PERF_COUNTER = 2,
  EXCEPTION_DEBUG        = 3,
};

enum exceptions_level1
{
  EXCEPTION_INTERRUPT        = 0,
  EXCEPTION_TLB_MODIFIED     = 1,
  EXCEPTION_TLB_REFILL_LOAD  = 2,
  EXCEPTION_TLB_REFILL_STORE = 3,

  EXCEPTION_TLB_INVALID_FETCH_LOAD = 2,
  EXCEPTION_TLB_INVALID_STORE      = 3,

  EXCEPTION_ADDRESS_ERROR_FETCH_LOAD = 4,
  EXCEPTION_ADDRESS_ERROR_STORE      = 5,

  EXCEPTION_BUS_ERROR_FETCH          = 6,
  EXCEPTION_BUS_ERROR_STORE          = 7,
  EXCEPTION_SYSCALL                  = 8,
  EXCEPTION_BREAK                    = 9,
  EXCEPTION_RESERVED_INSTRUCTION     = 10,
  EXCEPTION_COPROCESSOR_USUABLE      = 11,
  EXCEPTION_OVERFLOW                 = 12,
  EXCEPTION_TRAP                     = 13,
};

enum exception_vectors
{
  EXCEPTION_VECTOR_RESET_NMI     = VIRTUAL_ADDRESS_ROM,
  EXCEPTION_VECTOR_DEBUG0        = 0xbfc00100,
  EXCEPTION_VECTOR_COMMON0       = 0xbfc00180,
  EXCEPTION_VECTOR_TLB_REFILL1   = 0xbfc00200,
  EXCEPTION_VECTOR_PERF_COUNTER1 = 0xbfc00280,
  EXCEPTION_VECTOR_DEBUG1        = 0xbfc00300,
  EXCEPTION_VECTOR_COMMON1       = 0xbfc00380,
  EXCEPTION_VECTOR_INTERRUPT1    = 0xbfc00400,
  EXCEPTION_VECTOR_TLB_REFILL0   = VIRTUAL_ADDRESS_RAM,
  EXCEPTION_VECTOR_PERF_COUNTER0 = 0x80000080,
  EXCEPTION_VECTOR_INTERRUPT0    = 0x80000200,
};

typedef struct
{
  register32_t Accumulator;
  register32_t Registers[32];
  register32_t ControlRegisters[2];
  bool EqualFlag;
  bool Overflow;
} cpu_cop1;

typedef struct
{
  uint32_t ProgramCounter;
  uint32_t CurrentInstruction;
  uint32_t NextInstruction;
  //cpu_tlb  TLB;
  //cpu_itlb ITLB;
  cpu_cop0 COP0;
  cpu_cop1 COP1;
  register128_t Registers[32];
  register128_t HI;
  register128_t LO;
  register32_t SA;
} ee_cpu;