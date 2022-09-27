#define DEFINE_MIPS_INSTRUCTION(Name) static void Name(ee_cpu* CPU)
#if 1
#define NOT_IMMPLEMENTED_YET(...) ASSERT(0)
#else
#define NOT_IMMPLEMENTED_YET(...)
#endif
//#define OFFSETOF(Struct, Member)    ((uintptr_t)&(((Struct*)0)->Member))
//#define GET_CONSOLE_PTR(Member, MemberPtr)  ((uintptr_t)(MemberPtr) - OFFSETOF(ps2_console, Member))

#define INSTRUCTION_NOP 0
#define _INSTRUCTION_ (CPU->CurrentInstruction)
//#define _OPCODE_      ((_INSTRUCTION_ & (0x3f << 26)) >> 26)
#define _OPCODE_      (_INSTRUCTION_ >> 26)
#define _RS_          ((_INSTRUCTION_ & (0x1f << 21)) >> 21)
#define _RT_          ((_INSTRUCTION_ & (0x1f << 16)) >> 16)
#define _RD_          ((_INSTRUCTION_ & (0x1f << 11)) >> 11)
#define _SA_          ((_INSTRUCTION_ & (0x1f << 6))  >> 6)
#define _FUNCTION_    (_INSTRUCTION_  & 0x3f)
#define _IMMEDIATE_   ((int16_t)(_INSTRUCTION_  & 0xffff))

#define _FS_ _RD_
#define _FD_ _SA_
#define _FT_ _RT_