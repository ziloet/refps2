DEFINE_MIPS_INSTRUCTION(INSTRUCTION_ILLEGAL)
{
  ASSERT(0);
}

static void
SanityCheck(ee_cpu* CPU, bool Condition)
{
  if(!Condition)
  {
    INSTRUCTION_ILLEGAL(CPU);
  }
}

static void
StoreProgramCounter(ee_cpu* CPU)
{
  CPU->Registers[31].U64[0] = CPU->ProgramCounter;
}

DEFINE_MIPS_INSTRUCTION(ADD)
{
  ASSERT(_SA_ == 0);
  int32_t Value1 = (int32_t)CPU->Registers[_RS_].S64[0];
  int32_t Value2 = (int32_t)CPU->Registers[_RT_].S64[0];
  TrapOnOverflow32(CPU, Value1, Value2);
  int32_t Result = Value1 + Value2;
  CPU->Registers[_RD_].S64[0] = Result;
}

DEFINE_MIPS_INSTRUCTION(ADDI)
{
  int32_t Value1 = (int32_t)CPU->Registers[_RS_].S64[0];
  int32_t Value2 = (int32_t)_IMMEDIATE_;
  TrapOnOverflow32(CPU, Value1, Value2);
  int32_t Result = Value1 + Value2;
  CPU->Registers[_RT_].S64[0] = Result;
}

DEFINE_MIPS_INSTRUCTION(ADDIU)
{
  uint32_t Value1 = (uint32_t)CPU->Registers[_RS_].U64[0];
  uint32_t Value2 = (uint32_t)_IMMEDIATE_;
  uint32_t Result = Value1 + Value2;
  CPU->Registers[_RT_].S64[0] = Result;
}

DEFINE_MIPS_INSTRUCTION(ADDU)
{
  ASSERT(_SA_ == 0);
  uint32_t Value1 = (uint32_t)CPU->Registers[_RS_].U64[0];
  uint32_t Value2 = (uint32_t)CPU->Registers[_RT_].U64[0];
  uint32_t Result = Value1 + Value2;
  CPU->Registers[_RD_].S64[0] = Result;
}

DEFINE_MIPS_INSTRUCTION(AND)
{
  ASSERT(_SA_ == 0);
  uint64_t Value1 = CPU->Registers[_RS_].U64[0];
  uint64_t Value2 = CPU->Registers[_RT_].U64[0];
  uint64_t Result = Value1 & Value2;
  CPU->Registers[_RD_].U64[0] = Result;
}

DEFINE_MIPS_INSTRUCTION(ANDI)
{
  uint64_t Value1 = CPU->Registers[_RS_].U64[0];
  uint64_t Value2 = (uint64_t)_IMMEDIATE_;
  uint64_t Result = Value1 & Value2;
  CPU->Registers[_RT_].U64[0] = Result;
}

DEFINE_MIPS_INSTRUCTION(BEQ)
{
  uint64_t Value1 = CPU->Registers[_RS_].U64[0];
  uint64_t Value2 = CPU->Registers[_RT_].U64[0];
  bool Condition = (Value1 == Value2);
  bool IsLikely = false;
  ConditionalBranch(CPU, Condition, IsLikely);
}

DEFINE_MIPS_INSTRUCTION(BEQL)
{
  uint64_t Value1 = CPU->Registers[_RS_].U64[0];
  uint64_t Value2 = CPU->Registers[_RT_].U64[0];
  bool Condition = (Value1 == Value2);
  bool IsLikely = true;
  ConditionalBranch(CPU, Condition, IsLikely);
}

DEFINE_MIPS_INSTRUCTION(BGEZ)
{
  uint64_t Value = CPU->Registers[_RS_].U64[0];
  bool Condition = (Value >= 0);
  bool IsLikely = false;
  ConditionalBranch(CPU, Condition, IsLikely);
}

DEFINE_MIPS_INSTRUCTION(BGEZAL)
{
  StoreProgramCounter(CPU);
  BGEZ(CPU);
}

DEFINE_MIPS_INSTRUCTION(BGEZL)
{
  uint64_t Value = CPU->Registers[_RS_].U64[0];
  bool Condition = (Value >= 0);
  bool IsLikely = true;
  ConditionalBranch(CPU, Condition, IsLikely);
}

DEFINE_MIPS_INSTRUCTION(BGEZALL)
{
  StoreProgramCounter(CPU);
  BGEZL(CPU);
}

DEFINE_MIPS_INSTRUCTION(BGTZ)
{
  uint64_t Value = CPU->Registers[_RS_].U64[0];
  bool Condition = (Value > 0);
  bool IsLikely = false;
  ConditionalBranch(CPU, Condition, IsLikely);
}

DEFINE_MIPS_INSTRUCTION(BGTZL)
{
  uint64_t Value = CPU->Registers[_RS_].U64[0];
  bool Condition = (Value > 0);
  bool IsLikely = true;
  ConditionalBranch(CPU, Condition, IsLikely);
}

DEFINE_MIPS_INSTRUCTION(BLEZ)
{
  uint64_t Value = CPU->Registers[_RS_].U64[0];
  bool Condition = (Value <= 0);
  bool IsLikely = false;
  ConditionalBranch(CPU, Condition, IsLikely);
}

DEFINE_MIPS_INSTRUCTION(BLEZL)
{
  uint64_t Value = CPU->Registers[_RS_].U64[0];
  bool Condition = (Value <= 0);
  bool IsLikely = true;
  ConditionalBranch(CPU, Condition, IsLikely);
}

DEFINE_MIPS_INSTRUCTION(BLTZ)
{
  uint64_t Value = CPU->Registers[_RS_].U64[0];
  bool Condition = (Value < 0);
  bool IsLikely = false;
  ConditionalBranch(CPU, Condition, IsLikely);
}

DEFINE_MIPS_INSTRUCTION(BLTZAL)
{
  StoreProgramCounter(CPU);
  BLTZ(CPU);
}

DEFINE_MIPS_INSTRUCTION(BLTZL)
{
  uint64_t Value = CPU->Registers[_RS_].U64[0];
  bool Condition = (Value < 0);
  bool IsLikely = true;
  ConditionalBranch(CPU, Condition, IsLikely);
}

DEFINE_MIPS_INSTRUCTION(BLTZALL)
{
  StoreProgramCounter(CPU);
  BLTZL(CPU);
}

DEFINE_MIPS_INSTRUCTION(BNE)
{
  uint64_t Value1 = CPU->Registers[_RS_].U64[0];
  uint64_t Value2 = CPU->Registers[_RT_].U64[0];
  bool Condition = (Value1 != Value2);
  bool IsLikely = false;
  ConditionalBranch(CPU, Condition, IsLikely);
}

DEFINE_MIPS_INSTRUCTION(BNEL)
{
  uint64_t Value1 = CPU->Registers[_RS_].U64[0];
  uint64_t Value2 = CPU->Registers[_RT_].U64[0];
  bool Condition = (Value1 != Value2);
  bool IsLikely = true;
  ConditionalBranch(CPU, Condition, IsLikely);
}

DEFINE_MIPS_INSTRUCTION(BREAK)
{
  uint32_t ExceptionCode = (_INSTRUCTION_ >> 6);
  SignalException(CPU, ExceptionCode);
}

DEFINE_MIPS_INSTRUCTION(DADD)
{
  int64_t Value1 = CPU->Registers[_RS_].S64[0];
  int64_t Value2 = CPU->Registers[_RT_].S64[0];
  TrapOnOverflow64(CPU, Value1, Value2);
  int64_t Result = Value1 + Value2;
  CPU->Registers[_RD_].S64[0] = Result;
}

DEFINE_MIPS_INSTRUCTION(DADDI)
{
  int64_t Value1 = CPU->Registers[_RS_].S64[0];
  int64_t Value2 = (int64_t)_IMMEDIATE_;
  TrapOnOverflow64(CPU, Value1, Value2);
  int64_t Result = Value1 + Value2;
  CPU->Registers[_RT_].S64[0] = Result;
}

DEFINE_MIPS_INSTRUCTION(DADDIU)
{
  uint64_t Value1 = CPU->Registers[_RS_].U64[0];
  uint64_t Value2 = (uint64_t)_IMMEDIATE_;
  uint64_t Result = Value1 + Value2;
  CPU->Registers[_RT_].U64[0] = Result;
}

DEFINE_MIPS_INSTRUCTION(DADDU)
{
  uint64_t Value1 = CPU->Registers[_RS_].U64[0];
  uint64_t Value2 = CPU->Registers[_RT_].U64[0];
  uint64_t Result = Value1 + Value2;
  CPU->Registers[_RD_].U64[0] = Result;
}

DEFINE_MIPS_INSTRUCTION(DIV)
{
  int32_t Value1 = (int32_t)CPU->Registers[_RS_].S64[0];
  int32_t Value2 = (int32_t)CPU->Registers[_RT_].S64[0];
  CPU->LO.S64[0] = Value1 / Value2;
  CPU->HI.S64[0] = Value1 % Value2;
}

DEFINE_MIPS_INSTRUCTION(DIVU)
{
  uint32_t Value1 = (uint32_t)CPU->Registers[_RS_].U64[0];
  uint32_t Value2 = (uint32_t)CPU->Registers[_RT_].U64[0];
  CPU->LO.U64[0] = Value1 / Value2;
  CPU->HI.U64[0] = Value1 % Value2;
}

DEFINE_MIPS_INSTRUCTION(DSLL)
{
  uint64_t Value = CPU->Registers[_RT_].U64[0];
  uint64_t Result = Value << _SA_;
  CPU->Registers[_RD_].U64[0] = Result;
}

DEFINE_MIPS_INSTRUCTION(DSLL32)
{
  uint64_t Value = CPU->Registers[_RT_].U64[0];
  uint64_t Result = Value << (_SA_ + 32);
  CPU->Registers[_RD_].U64[0] = Result;
}

DEFINE_MIPS_INSTRUCTION(DSLLV)
{
  uint64_t Value = CPU->Registers[_RT_].U64[0];
  uint32_t ShiftAmount = CPU->Registers[_RS_].U64[0] & 0x3f;
  uint64_t Result = Value << ShiftAmount;
  CPU->Registers[_RD_].U64[0] = Result;
}

DEFINE_MIPS_INSTRUCTION(DSRA)
{
  int64_t Value = CPU->Registers[_RT_].S64[0];
  int64_t Result = Value >> _SA_;
  CPU->Registers[_RD_].S64[0] = Result;
}

DEFINE_MIPS_INSTRUCTION(DSRA32)
{
  int64_t Value = CPU->Registers[_RT_].S64[0];
  int64_t Result = Value >> (_SA_ + 32);
  CPU->Registers[_RD_].S64[0] = Result;
}

DEFINE_MIPS_INSTRUCTION(DSRAV)
{
  int64_t  Value = CPU->Registers[_RT_].S64[0];
  uint32_t ShiftAmount = CPU->Registers[_RS_].U64[0] & 0x3f;
  int64_t Result = Value >> ShiftAmount;
  CPU->Registers[_RD_].S64[0] = Result;
}

DEFINE_MIPS_INSTRUCTION(DSRL)
{
  uint64_t Value = CPU->Registers[_RT_].U64[0];
  uint64_t Result = Value >> _SA_;
  CPU->Registers[_RD_].U64[0] = Result;
}

DEFINE_MIPS_INSTRUCTION(DSRL32)
{
  uint64_t Value = CPU->Registers[_RT_].U64[0];
  uint64_t Result = Value >> (_SA_ + 32);
  CPU->Registers[_RD_].U64[0] = Result;
}

DEFINE_MIPS_INSTRUCTION(DSRLV)
{
  uint64_t Value = CPU->Registers[_RT_].U64[0];
  uint32_t ShiftAmount = CPU->Registers[_RS_].U64[0] & 0x3f;
  uint64_t Result = Value >> ShiftAmount;
  CPU->Registers[_RD_].U64[0] = Result;
}

DEFINE_MIPS_INSTRUCTION(DSUB)
{
  int64_t Value1 = CPU->Registers[_RS_].U64[0];
  int64_t Value2 = CPU->Registers[_RT_].U64[0];
  TrapOnOverflow64(CPU, Value1, -Value2);
  int64_t Result = Value1 - Value2;
  CPU->Registers[_RD_].S64[0] = Result;
}

DEFINE_MIPS_INSTRUCTION(DSUBU)
{
  uint64_t Value1 = CPU->Registers[_RS_].U64[0];
  uint64_t Value2 = CPU->Registers[_RT_].U64[0];
  int64_t  Result = Value1 - Value2;
  CPU->Registers[_RD_].S64[0] = Result;
}

DEFINE_MIPS_INSTRUCTION(J)
{
  uint32_t Offset = ((uint32_t)_INSTRUCTION_ << 6) >> 4;
  uint32_t TargetAddress = CPU->ProgramCounter & (0xf << 28) | Offset;
  CPU->ProgramCounter = TargetAddress - SIZEOF_INSTRUCTION;
}

DEFINE_MIPS_INSTRUCTION(JAL)
{
  StoreProgramCounter(CPU);
  J(CPU);
}

DEFINE_MIPS_INSTRUCTION(JR)
{
  uint32_t TargetAddress = CPU->Registers[_RS_].U32[0];
  CPU->ProgramCounter = TargetAddress - SIZEOF_INSTRUCTION;
}

DEFINE_MIPS_INSTRUCTION(JALR)
{
  CPU->Registers[_RD_].U64[0] = CPU->ProgramCounter;
  JR(CPU);
}

DEFINE_MIPS_INSTRUCTION(LB)
{
  NOT_IMMPLEMENTED_YET();
  int32_t Base = CPU->Registers[_RS_].S32[0];
  int32_t Offset = (int32_t)_IMMEDIATE_;
  int32_t EffectiveAddress = Base + Offset;
  int8_t Result = MemoryRead8(EffectiveAddress);
  CPU->Registers[_RT_].S64[0] = Result;
}

DEFINE_MIPS_INSTRUCTION(LBU)
{
  NOT_IMMPLEMENTED_YET();
  int32_t Base = CPU->Registers[_RS_].S32[0];
  int32_t Offset = (int32_t)_IMMEDIATE_;
  int32_t EffectiveAddress = Base + Offset;
  uint8_t Result = MemoryRead8(EffectiveAddress);
  CPU->Registers[_RT_].S64[0] = Result;
}

DEFINE_MIPS_INSTRUCTION(LD)
{
  NOT_IMMPLEMENTED_YET();
  #if 0
  int32_t Base = CPU->Registers[_RS_].S32[0];
  int32_t Offset = (int32_t)_IMMEDIATE_;
  int32_t EffectiveAddress = Base + Offset;
  int64_t Result = MemoryRead64(EffectiveAddress);
  CPU->Registers[_RT_].S64[0] = Result;
  #endif
}

DEFINE_MIPS_INSTRUCTION(LDL)
{
  NOT_IMMPLEMENTED_YET();
}

DEFINE_MIPS_INSTRUCTION(LDR)
{
  NOT_IMMPLEMENTED_YET();
}

DEFINE_MIPS_INSTRUCTION(LH)
{
  NOT_IMMPLEMENTED_YET();
  int32_t Base = CPU->Registers[_RS_].S32[0];
  int32_t Offset = (int32_t)_IMMEDIATE_;
  int32_t EffectiveAddress = Base + Offset;
  int16_t Result = MemoryRead16(EffectiveAddress);
  CPU->Registers[_RT_].S64[0] = Result;
}

DEFINE_MIPS_INSTRUCTION(LHU)
{
  NOT_IMMPLEMENTED_YET();
  NOT_IMMPLEMENTED_YET();
  int32_t Base = CPU->Registers[_RS_].S32[0];
  int32_t Offset = (int32_t)_IMMEDIATE_;
  int32_t EffectiveAddress = Base + Offset;
  uint16_t Result = MemoryRead16(EffectiveAddress);
  CPU->Registers[_RT_].S64[0] = Result;
}

DEFINE_MIPS_INSTRUCTION(LUI)
{
  int32_t Value = (int32_t)_IMMEDIATE_ << 16;
  int64_t Result = (int64_t)Value;
  CPU->Registers[_RT_].S64[0] = Result;
}

DEFINE_MIPS_INSTRUCTION(LW)
{
  NOT_IMMPLEMENTED_YET();
  int32_t Base = CPU->Registers[_RS_].S32[0];
  int32_t Offset = (int32_t)_IMMEDIATE_;
  int32_t EffectiveAddress = Base + Offset;
  int16_t Result = MemoryRead16(EffectiveAddress);
  CPU->Registers[_RT_].S64[0] = Result;
}

DEFINE_MIPS_INSTRUCTION(LWL)
{
  NOT_IMMPLEMENTED_YET();
}

DEFINE_MIPS_INSTRUCTION(LWR)
{
  NOT_IMMPLEMENTED_YET();
}

DEFINE_MIPS_INSTRUCTION(LWU)
{
  NOT_IMMPLEMENTED_YET();
}

DEFINE_MIPS_INSTRUCTION(MFHI)
{
  uint64_t Result = CPU->HI.U64[0];
  CPU->Registers[_RD_].U64[0] = Result;
}

DEFINE_MIPS_INSTRUCTION(MFLO)
{
  uint64_t Result = CPU->LO.U64[0];
  CPU->Registers[_RD_].U64[0] = Result;
}

DEFINE_MIPS_INSTRUCTION(MOVN)
{
  uint64_t Value = CPU->Registers[_RT_].U64[0];
  if(Value != 0)
  {
    uint64_t Result = CPU->Registers[_RS_].U64[0];
    CPU->Registers[_RD_].U64[0] = Result;
  }
}

DEFINE_MIPS_INSTRUCTION(MOVZ)
{
  uint64_t Value = CPU->Registers[_RT_].U64[0];
  if(Value == 0)
  {
    uint64_t Result = CPU->Registers[_RS_].U64[0];
    CPU->Registers[_RD_].U64[0] = Result;
  }
}

DEFINE_MIPS_INSTRUCTION(MTHI)
{
  uint64_t Result = CPU->Registers[_RS_].U64[0];
  CPU->HI.U64[0] = Result;
}

DEFINE_MIPS_INSTRUCTION(MTLO)
{
  uint64_t Result = CPU->Registers[_RS_].U64[0];
  CPU->LO.U64[0] = Result;
}

DEFINE_MIPS_INSTRUCTION(MULT)
{
  int32_t Value1 = (int32_t)CPU->Registers[_RS_].S64[0];
  int32_t Value2 = (int32_t)CPU->Registers[_RT_].S64[0];
  int64_t Result = (int64_t)Value1 * Value2;
  CPU->LO.S64[0] = Result & 0xffffffff;
  CPU->HI.S64[0] = Result >> 32;
  if(_RD_ != 0)
  {
    CPU->Registers[_RD_].S64[0] = CPU->HI.S64[0] | CPU->LO.S64[0];
  }
}

DEFINE_MIPS_INSTRUCTION(MULTU)
{
  uint32_t Value1 = (uint32_t)CPU->Registers[_RS_].U64[0];
  uint32_t Value2 = (uint32_t)CPU->Registers[_RT_].U64[0];
  uint64_t Result = (uint64_t)Value1 * Value2;
  CPU->LO.S64[0] = Result & 0xffffffff;
  CPU->HI.S64[0] = Result >> 32;
  if(_RD_ != 0)
  {
    CPU->Registers[_RD_].S64[0] = CPU->HI.S64[0] | CPU->LO.S64[0];
  }
}

DEFINE_MIPS_INSTRUCTION(NOR)
{
  uint64_t Value1 = CPU->Registers[_RS_].U64[0];
  uint64_t Value2 = CPU->Registers[_RT_].U64[0];
  uint64_t Result = ~(Value1 | Value2);
  CPU->Registers[_RD_].U64[0] = Result;
}

DEFINE_MIPS_INSTRUCTION(OR)
{
  uint64_t Value1 = CPU->Registers[_RS_].U64[0];
  uint64_t Value2 = CPU->Registers[_RT_].U64[0];
  uint64_t Result = Value1 | Value2;
  CPU->Registers[_RD_].U64[0] = Result;
}

DEFINE_MIPS_INSTRUCTION(ORI)
{
  uint64_t Value1 = CPU->Registers[_RS_].U64[0];
  uint64_t Value2 = (uint64_t)_IMMEDIATE_;
  uint64_t Result = Value1 | Value2;
  CPU->Registers[_RT_].U64[0] = Result;
}

DEFINE_MIPS_INSTRUCTION(PREF)
{
  NOT_IMMPLEMENTED_YET();
}

DEFINE_MIPS_INSTRUCTION(SB)
{
  NOT_IMMPLEMENTED_YET();
}

DEFINE_MIPS_INSTRUCTION(SD)
{
  NOT_IMMPLEMENTED_YET();
}

DEFINE_MIPS_INSTRUCTION(SDL)
{
  NOT_IMMPLEMENTED_YET();
}

DEFINE_MIPS_INSTRUCTION(SDR)
{
  NOT_IMMPLEMENTED_YET();
}

DEFINE_MIPS_INSTRUCTION(SH)
{
  NOT_IMMPLEMENTED_YET();
}

DEFINE_MIPS_INSTRUCTION(SLL)
{
  int32_t Value = CPU->Registers[_RT_].S32[0];
  int64_t Result = Value << _SA_;
  CPU->Registers[_RD_].S64[0] = Result;
}

DEFINE_MIPS_INSTRUCTION(SLLV)
{
  int32_t Value = CPU->Registers[_RS_].S32[0];
  uint32_t ShiftAmount = CPU->Registers[_RT_].S32[0] & 0x1f;
  int64_t Result = Value << ShiftAmount;
  CPU->Registers[_RD_].S64[0] = Result;
}

DEFINE_MIPS_INSTRUCTION(SLT)
{
  int64_t Value1 = CPU->Registers[_RS_].S64[0];
  int64_t Value2 = CPU->Registers[_RT_].S64[0];
  bool Result = (Value1 < Value2);
  CPU->Registers[_RD_].U64[0] = Result;
}

DEFINE_MIPS_INSTRUCTION(SLTI)
{
  int64_t Value1 = CPU->Registers[_RS_].S64[0];
  int64_t Value2 = (int64_t)_IMMEDIATE_;
  bool Result = (Value1 < Value2);
  CPU->Registers[_RT_].U64[0] = Result;
}

DEFINE_MIPS_INSTRUCTION(SLTIU)
{
  uint64_t Value1 = CPU->Registers[_RS_].U64[0];
  uint64_t Value2 = (uint64_t)_IMMEDIATE_;
  bool Result = (Value1 < Value2);
  CPU->Registers[_RT_].U64[0] = Result;
}

DEFINE_MIPS_INSTRUCTION(SLTU)
{
  NOT_IMMPLEMENTED_YET();
  uint64_t Value1 = CPU->Registers[_RS_].U64[0];
  uint64_t Value2 = CPU->Registers[_RT_].U64[0];
  bool Result = (Value1 < Value2);
  CPU->Registers[_RD_].U64[0] = Result;
}

DEFINE_MIPS_INSTRUCTION(SRA)
{
  NOT_IMMPLEMENTED_YET();
}

DEFINE_MIPS_INSTRUCTION(SRAV)
{
  NOT_IMMPLEMENTED_YET();
}

DEFINE_MIPS_INSTRUCTION(SRL)
{
  NOT_IMMPLEMENTED_YET();
}

DEFINE_MIPS_INSTRUCTION(SRLV)
{
  NOT_IMMPLEMENTED_YET();
}

DEFINE_MIPS_INSTRUCTION(SUB)
{
  int32_t Value1 = (int32_t)CPU->Registers[_RS_].S64[0];
  int32_t Value2 = (int32_t)CPU->Registers[_RT_].S64[0];
  TrapOnOverflow32(CPU, Value1, -Value2);
  int32_t Result = Value1 - Value2;
  CPU->Registers[_RD_].S64[0] = Result;
}

DEFINE_MIPS_INSTRUCTION(SUBU)
{
  uint32_t Value1 = (uint32_t)CPU->Registers[_RS_].U64[0];
  uint32_t Value2 = (uint32_t)CPU->Registers[_RT_].U64[0];
  uint32_t Result = Value1 - Value2;
  CPU->Registers[_RD_].U64[0] = Result;
}

DEFINE_MIPS_INSTRUCTION(SW)
{
  uint32_t Base = CPU->Registers[_RD_].S32[0];
  int32_t Offset = (int32_t)_IMMEDIATE_;
  int32_t VirtualAddress = Base + Offset;
  uint32_t Value = CPU->Registers[_RT_].S32[0];
  MemoryWrite32(VirtualAddress, Value);
}

DEFINE_MIPS_INSTRUCTION(SWL)
{
  NOT_IMMPLEMENTED_YET();
}

DEFINE_MIPS_INSTRUCTION(SWR)
{
  NOT_IMMPLEMENTED_YET();
}

DEFINE_MIPS_INSTRUCTION(SYNC)
{
  //NOT_IMMPLEMENTED_YET();
}

DEFINE_MIPS_INSTRUCTION(SYSCALL)
{
  NOT_IMMPLEMENTED_YET();
  uint32_t SyscallCode = _INSTRUCTION_ >> 6;
  SignalException(CPU, SyscallCode);
}

DEFINE_MIPS_INSTRUCTION(TEQ)
{
  uint64_t Value1 = CPU->Registers[_RS_].U64[0];
  uint64_t Value2 = CPU->Registers[_RT_].U64[0];
  bool TrapCondition = (Value1 == Value2);
  ConditionalTrap(CPU, TrapCondition);
}

DEFINE_MIPS_INSTRUCTION(TEQI)
{
  int64_t Value1 = CPU->Registers[_RS_].S64[0];
  int64_t Value2 = (int64_t)_IMMEDIATE_;
  bool TrapCondition = (Value1 == Value2);
  ConditionalTrap(CPU, TrapCondition);
}

DEFINE_MIPS_INSTRUCTION(TGE)
{
  int64_t Value1 = CPU->Registers[_RS_].S64[0];
  int64_t Value2 = CPU->Registers[_RT_].S64[0];
  bool TrapCondition = (Value1 >= Value2);
  ConditionalTrap(CPU, TrapCondition);
}

DEFINE_MIPS_INSTRUCTION(TGEI)
{
  int64_t Value1 = CPU->Registers[_RS_].S64[0];
  int64_t Value2 = (int64_t)_IMMEDIATE_;
  bool TrapCondition = (Value1 >= Value2);
  ConditionalTrap(CPU, TrapCondition);
}

DEFINE_MIPS_INSTRUCTION(TGEIU)
{
  uint64_t Value1 = CPU->Registers[_RS_].U64[0];
  uint64_t Value2 = (uint64_t)_IMMEDIATE_;
  bool TrapCondition = (Value1 >= Value2);
  ConditionalTrap(CPU, TrapCondition);
}

DEFINE_MIPS_INSTRUCTION(TGEU)
{
  uint64_t Value1 = CPU->Registers[_RS_].U64[0];
  uint64_t Value2 = CPU->Registers[_RT_].U64[0];
  bool TrapCondition = (Value1 >= Value2);
  ConditionalTrap(CPU, TrapCondition);
}

DEFINE_MIPS_INSTRUCTION(TLT)
{
  int64_t Value1 = CPU->Registers[_RS_].S64[0];
  int64_t Value2 = CPU->Registers[_RT_].S64[0];
  bool TrapCondition = (Value1 < Value2);
  ConditionalTrap(CPU, TrapCondition);
}

DEFINE_MIPS_INSTRUCTION(TLTI)
{
  int64_t Value1 = CPU->Registers[_RS_].S64[0];
  int64_t Value2 = (int64_t)_IMMEDIATE_;
  bool TrapCondition = (Value1 < Value2);
  ConditionalTrap(CPU, TrapCondition);
}

DEFINE_MIPS_INSTRUCTION(TLTIU)
{
  uint64_t Value1 = CPU->Registers[_RS_].U64[0];
  uint64_t Value2 = (uint64_t)_IMMEDIATE_;
  bool TrapCondition = (Value1 < Value2);
  ConditionalTrap(CPU, TrapCondition);
}

DEFINE_MIPS_INSTRUCTION(TLTU)
{
  uint64_t Value1 = CPU->Registers[_RS_].U64[0];
  uint64_t Value2 = CPU->Registers[_RT_].U64[0];
  bool TrapCondition = (Value1 < Value2);
  ConditionalTrap(CPU, TrapCondition);
}

DEFINE_MIPS_INSTRUCTION(TNE)
{
  uint64_t Value1 = CPU->Registers[_RS_].U64[0];
  uint64_t Value2 = CPU->Registers[_RT_].U64[0];
  bool TrapCondition = (Value1 != Value2);
  ConditionalTrap(CPU, TrapCondition);
}

DEFINE_MIPS_INSTRUCTION(TNEI)
{
  int64_t Value1 = CPU->Registers[_RS_].S64[0];
  int64_t Value2 = (int64_t)_IMMEDIATE_;
  bool TrapCondition = (Value1 != Value2);
  ConditionalTrap(CPU, TrapCondition);
}

DEFINE_MIPS_INSTRUCTION(XOR)
{
  uint64_t Value1 = CPU->Registers[_RS_].U64[0];
  uint64_t Value2 = CPU->Registers[_RT_].U64[0];
  uint64_t Result = Value1 ^ Value2;
  CPU->Registers[_RD_].U64[0] = Result;
}

DEFINE_MIPS_INSTRUCTION(XORI)
{
  uint64_t Value1 = CPU->Registers[_RS_].U64[0];
  uint64_t Value2 = (uint64_t)_IMMEDIATE_;
  uint64_t Result = Value1 ^ Value2;
  CPU->Registers[_RT_].U64[0] = Result;
}