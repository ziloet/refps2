#if 0

static ps2_console*
GetConsolePointer(ee_cpu* CPU)
{
  uintptr_t ByteAddress = (uintptr_t)CPU;
  uintptr_t Offset = 3463;
  ps2_console* Result = ByteAddress - Offset;
  return Result;
}
#endif

static void
SignalException(ee_cpu* CPU, uint32_t ExceptionCode)
{
  ASSERT(0);
}

static void
TrapOnOverflow32(ee_cpu* CPU, int32_t Value1, int32_t Value2)
{
  bool Overflow  = AddOverflow32(Value1, Value2);
  bool Underflow = AddUnderflow32(Value1, Value2);
  if(Overflow || Underflow)
  {
    SignalException(CPU, CPU_INT_OVERFLOW);
  }
}

static void
TrapOnOverflow64(ee_cpu* CPU, int64_t Value1, int64_t Value2)
{
  bool Overflow = AddOverflow64(Value1, Value2);
  bool Underflow = AddUnderflow64(Value1, Value2);
  if(Overflow || Underflow)
  {
    SignalException(CPU, CPU_INT_OVERFLOW);
  }
}

static void
NullifyCurrentInstruction(ee_cpu* CPU)
{
  ASSERT(0);
}

static void
ConditionalBranch(ee_cpu* CPU, bool Condition, bool IsLikely)
{
  if(Condition)
  {
    uint32_t Offset = (_IMMEDIATE_ << 2);
    CPU->ProgramCounter += Offset;
  }
  else if(IsLikely)
  {
    NullifyCurrentInstruction(CPU);
  }
}

static void
ConditionalTrap(ee_cpu* CPU, bool Condition)
{
  if(Condition)
  {
    //uint32_t TrapCode = (_INSTRUCTION_ & 0x3ff) >> 6; // used for software parameters
    SignalException(CPU, EXCEPTION_TRAP);
  }
}