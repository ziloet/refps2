#define EE_CORE_PROCESSOR_ID 0x2e42

enum r5900_exception
{
  CPU_INT_OVERFLOW,
  CPU_COPROCESSOR_UNUSABLE,
  CPU_TLB_REFILL,
  CPU_TLB_INVALD,
  CPU_TLB_MODIFIED,
};

enum cpu_privilages
{
  CPU_PRIVILAGES_KERNEL     = 0x0,
  CPU_PRIVILAGES_SUPERVISOR = 0x1,
  CPU_PRIVILAGES_USER       = 0x2,
  CPU_PRIVILAGES_RESERVED   = 0x3,
};

typedef struct
{
  uint32_t Index;
  uint32_t Random;
  uint32_t EntryLo0;
  uint32_t EntryLo1;
  uint32_t Context;
  uint32_t PageMask;
  uint32_t Wired;
  uint32_t Reserved;
  uint32_t BadVirtualAddress;
  uint32_t TimerCompare;
  uint32_t EntryHi;
  uint32_t TimerReferenceValue;
  uint32_t Status;
  uint32_t Cause;
  uint32_t ExceptionProgramCounter;
  uint32_t ProcessorID;
  uint32_t Config;
  uint32_t Reserved2[6];
  uint32_t BadPhysicalAddress;
  uint32_t Dummy;
  uint32_t PerformanceCounterAndControl[3];
  uint32_t Reserved3[2];
  uint32_t CacheTagLo;
  uint32_t CacheTagHi;
  uint32_t ErrorProgramCounter;
  uint32_t Reserved4;
  uint32_t Debug[8];
} cop0_registers;


typedef union
{
  cop0_registers Registers;
  uint32_t RegisterIndex[sizeof(cop0_registers) / sizeof(uint32_t)];
} cpu_cop0;

STATIC_ASSERT(sizeof(((cpu_cop0){0}).Registers) == sizeof(cop0_registers));