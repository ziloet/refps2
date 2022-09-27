DEFINE_MIPS_INSTRUCTION(BC0F)
{
  NOT_IMMPLEMENTED_YET();
  #if 0
  bool Value = CPU->COP0.ConditionFlag;
  bool Condition = (Value == false);
  bool IsLikely = false;
  ConditionalBranch(CPU, Condition, IsLikely);
  #endif
}

DEFINE_MIPS_INSTRUCTION(BC0FL)
{
  NOT_IMMPLEMENTED_YET();
  #if 0
  bool Value = CPU->COP0.ConditionFlag;
  bool Condition = (Value == false);
  bool IsLikely = true;
  ConditionalBranch(CPU, Condition, IsLikely);
  #endif
}

DEFINE_MIPS_INSTRUCTION(BC0T)
{
  NOT_IMMPLEMENTED_YET();
  #if 0
  bool Value = CPU->COP0.ConditionFlag;
  bool Condition = (Value == true);
  bool IsLikely = false;
  ConditionalBranch(CPU, Condition, IsLikely);
  #endif
}

DEFINE_MIPS_INSTRUCTION(BC0TL)
{
  NOT_IMMPLEMENTED_YET();
  #if 0
  bool Value = CPU->COP0.ConditionFlag;
  bool Condition = (Value == true);
  bool IsLikely = true;
  ConditionalBranch(CPU, Condition, IsLikely);
  #endif
}

DEFINE_MIPS_INSTRUCTION(DI)
{
  NOT_IMMPLEMENTED_YET();

}

DEFINE_MIPS_INSTRUCTION(EI)
{
  NOT_IMMPLEMENTED_YET();
}

DEFINE_MIPS_INSTRUCTION(ERET)
{
  NOT_IMMPLEMENTED_YET();
}


#if 0
DEFINE_MIPS_INSTRUCTION(MFC0)
{
  ASSERT(_FUNCTION_ == 0);  // otherwise instruction illegal
  int32_t Result = CPU->COP0.Registers[_RD_];
  CPU->Registers[_RT_].S64[0] = Result;
}

DEFINE_MIPS_INSTRUCTION(MFBPC)
{
  int32_t Result = CPU->COP0.DebugRegisters.BreakpointControl;
  CPU->Registers[_RT_].S64[0] = Result;
}

DEFINE_MIPS_INSTRUCTION(MFDAB)
{
  int32_t Result = CPU->COP0.DebugRegisters.DataAddress;
  CPU->Registers[_RT_].S64[0] = Result;
}

DEFINE_MIPS_INSTRUCTION(MFDABM)
{
  int32_t Result = CPU->COP0.DebugRegisters.DataAddressMasked;
  CPU->Registers[_RT_].S64[0] = Result;
}

DEFINE_MIPS_INSTRUCTION(MFDVB)
{
  int32_t Result = CPU->COP0.DebugRegisters.DataValue;
  CPU->Registers[_RT_].S64[0] = Result;
}

DEFINE_MIPS_INSTRUCTION(MFDVBM)
{
  int32_t Result = CPU->COP0.DebugRegisters.DataValueMasked;
  CPU->Registers[_RT_].S64[0] = Result;
}

DEFINE_MIPS_INSTRUCTION(MFIAB)
{
  int32_t Result = CPU->COP0.DebugRegisters.InstructionAddress;
  CPU->Registers[_RT_].S64[0] = Result;
}

DEFINE_MIPS_INSTRUCTION(MFIABM)
{
  int32_t Result = CPU->COP0.DebugRegisters.InstructionAddressMasked;
  CPU->Registers[_RT_].S64[0] = Result;
}

DEFINE_MIPS_INSTRUCTION(MFPC)
{
  int32_t Result = CPU->COP0.PerformanceCounterControl;
  CPU->Registers[_RT_].S64[0] = Result;
}

DEFINE_MIPS_INSTRUCTION(MFPS)
{
  int32_t Result = CPU->COP0.PerformanceEventSpecifier;
  CPU->Registers[_RT_].S64[0] = Result;
}

DEFINE_MIPS_INSTRUCTION(MTBPC)
{
  int32_t Result = CPU->Registers[_RT_].S32[0];
  CPU->COP0.DebugRegisters.BreakpointControl = Result;
}

DEFINE_MIPS_INSTRUCTION(MTC0)
{
  ASSERT(_FUNCTION_ == 0);  // otherwise instruction illegal
  int32_t Result = CPU->Registers[_RT_].S32[0];
  CPU->COP0.Registers[_RD_] = Result;
}

DEFINE_MIPS_INSTRUCTION(MTDAB)
{
  int32_t Result = CPU->Registers[_RT_].S32[0];
  CPU->COP0.DebugRegisters.DataAddress = Result;
}

DEFINE_MIPS_INSTRUCTION(MTDABM)
{
  int32_t Result = CPU->Registers[_RT_].S32[0];
  CPU->COP0.DebugRegisters.DataAddressMasked = Result;
}

DEFINE_MIPS_INSTRUCTION(MTDVB)
{
  int32_t Result = CPU->Registers[_RT_].S32[0];
  CPU->COP0.DebugRegisters.DataValue = Result;
}

DEFINE_MIPS_INSTRUCTION(MTDVBM)
{
  int32_t Result = CPU->Registers[_RT_].S32[0];
  CPU->COP0.DebugRegisters.DataValueMasked = Result;
}

DEFINE_MIPS_INSTRUCTION(MTIAB)
{
  int32_t Result = CPU->Registers[_RT_].S32[0];
  CPU->COP0.DebugRegisters.InstructionAddress = Result;
}

DEFINE_MIPS_INSTRUCTION(MTIABM)
{
  int32_t Result = CPU->Registers[_RT_].S32[0];
  CPU->COP0.DebugRegisters.InstructionAddressMasked = Result;
}

DEFINE_MIPS_INSTRUCTION(MTPC)
{
  int32_t Result = CPU->Registers[_RT_].S32[0];
  CPU->COP0.PerformanceCounterControl = Result;
}

DEFINE_MIPS_INSTRUCTION(MTPS)
{
  int32_t Result = CPU->Registers[_RT_].S32[0];
  CPU->COP0.PerformanceEventSpecifier = Result;
}
#endif


//static opcode_table


DEFINE_MIPS_INSTRUCTION(MF0)
{
  ASSERT(_SA_ == 0); // otherwise illegal instruction
  int32_t Result = 0;
  uint32_t RegisterIndex = _RD_;
  switch(RegisterIndex)
  {
    case 7:
    case 17:
    case 18:
    case 19:
    case 20:
    case 21:
    case 22:
    case 26:
    case 27:
    {
      // reserved registers, exception?
    } break;
    case 24:
    {
      NOT_IMMPLEMENTED_YET();
      uint32_t DebugRegisterIndex = _FUNCTION_;
      if(DebugRegisterIndex != 1)
      {
        Result = CPU->COP0.Registers.Debug[DebugRegisterIndex];
      }
    } break;
    case 25:
    {
      NOT_IMMPLEMENTED_YET();
      uint32_t PerfCounterIndex = _FUNCTION_;
      ASSERT((PerfCounterIndex & ~3) == 0); // wtf?
      Result = CPU->COP0.Registers.PerformanceCounterAndControl[PerfCounterIndex];
    } break;
    default:
    {
      Result = CPU->COP0.RegisterIndex[RegisterIndex];
    } break;
  }
  CPU->Registers[_RT_].S64[0] = Result;
}

DEFINE_MIPS_INSTRUCTION(MT0)
{
  int32_t Result = CPU->Registers[_RT_].S32[0];
  int32_t RegisterIndex = _RD_;
  switch(RegisterIndex)
  {
    case 7:
    case 17:
    case 18:
    case 19:
    case 20:
    case 21:
    case 22:
    case 26:
    case 27:
    {
      // reserved registers, exception?
      ASSERT(0);
    } break;
    case 24:
    {
      NOT_IMMPLEMENTED_YET();
      uint32_t DebugRegisterIndex = _FUNCTION_;
      if(DebugRegisterIndex != 1)
      {
        CPU->COP0.Registers.Debug[DebugRegisterIndex] = Result;
      }
    } break;
    case 25:
    {
      NOT_IMMPLEMENTED_YET();
      uint32_t PerfCounterIndex = _FUNCTION_;
      ASSERT((PerfCounterIndex & ~3) == 0);
      CPU->COP0.Registers.PerformanceCounterAndControl[PerfCounterIndex] = Result;
    } break;
    default:
    {
      CPU->COP0.RegisterIndex[RegisterIndex] = Result;
    } break;
  }
}

DEFINE_MIPS_INSTRUCTION(TLBR)
{
  NOT_IMMPLEMENTED_YET();
  //uint32_t Index = CPU->COP0.Registers.Index;
  //tlb_entry Entry = CPU.TLB[Index];
  //uint32_t GlobalBit = TLBGlobal(Entry);
  //uint32_t ASID = TLB_ASID(Entry);
  //uint32_t VPN  = TLB_VPN2(Entry);
  //uint32_t Concat = (VPN << 5) | ASID;
  //CPU->COP0.Registers.EntryLo1 = Entry[0] | GlobalBit;
  //CPU->COP0.Registers.EntryLo0 = Entry[1] | GlobalBit;
  //CPU->COP0.Registers.EntryHi  = (Concat) & ~(Entry[3]);
  //CPU->COP0.Registers.PageMask = Entry[3];
}

DEFINE_MIPS_INSTRUCTION(TLBWI)
{
  NOT_IMMPLEMENTED_YET();
  //uint32_t Index = CPU->COP0.Registers.Index;
  //CPU->TLB[Index][0] = (CPU->COP0.Registers.EntryLo1 & ~1) | 0;
  //CPU->TLB[Index][1] = (CPU->COP0.Registers.EntryLo0 & ~1) | 0;
  //CPU->TLB[Index][2] = ((CPU->COP0.Registers.EntryHi & ~0x7ff) | ((CPU->COP0.Registers.EntryLo0 & 1) & (CPU->COP0.Registers.EntryLo1 & 1)) | (CPU->COP0.Registers.EntryHi & 0x7ff)) & ~(CPU->COP0.Registers.PageMask);
  //CPU->TLB[Index][3] = CPU->COP0.Registers.PageMask;
}

DEFINE_MIPS_INSTRUCTION(TLBWR)
{
  NOT_IMMPLEMENTED_YET();
}

DEFINE_MIPS_INSTRUCTION(TLBP)
{
  NOT_IMMPLEMENTED_YET();
}