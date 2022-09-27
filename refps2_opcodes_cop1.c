DEFINE_MIPS_INSTRUCTION(ABS_S)
{
  NOT_IMMPLEMENTED_YET();
  float32_t Value = CPU->COP1.Registers[_FS_].F32;
  float32_t Result = ABS(Value);
  CPU->COP1.Registers[_FD_].F32 = Result;
}

DEFINE_MIPS_INSTRUCTION(ADD_S)
{
  NOT_IMMPLEMENTED_YET();
  float32_t Value1 = CPU->COP1.Registers[_FS_].F32;
  float32_t Value2 = CPU->COP1.Registers[_FT_].F32;
  float32_t Result = Value1 + Value2;
  CPU->COP1.Registers[_FD_].F32 = Result;
}

DEFINE_MIPS_INSTRUCTION(ADDA_S)
{
  NOT_IMMPLEMENTED_YET();
  float32_t Value1 = CPU->COP1.Registers[_FS_].F32;
  float32_t Value2 = CPU->COP1.Registers[_FT_].F32;
  float32_t Result = Value1 + Value2;
  CPU->COP1.Accumulator.F32 = Result;
}

DEFINE_MIPS_INSTRUCTION(BC1F)
{
  NOT_IMMPLEMENTED_YET();
  bool Condition = (CPU->COP1.EqualFlag == 0);
  bool IsLikely = false;
  ConditionalBranch(CPU, Condition, IsLikely);
}

DEFINE_MIPS_INSTRUCTION(BC1FL)
{
  NOT_IMMPLEMENTED_YET();
  bool Condition = (CPU->COP1.EqualFlag == 0);
  bool IsLikely = true;
  ConditionalBranch(CPU, Condition, IsLikely);
}

DEFINE_MIPS_INSTRUCTION(BC1T)
{
  NOT_IMMPLEMENTED_YET();
  bool Condition = (CPU->COP1.EqualFlag == 1);
  bool IsLikely = false;
  ConditionalBranch(CPU, Condition, IsLikely);
}

DEFINE_MIPS_INSTRUCTION(BC1TL)
{
  NOT_IMMPLEMENTED_YET();
  bool Condition = (CPU->COP1.EqualFlag == 1);
  bool IsLikely = true;
  ConditionalBranch(CPU, Condition, IsLikely);
}

DEFINE_MIPS_INSTRUCTION(C_EQ_S)
{
  NOT_IMMPLEMENTED_YET();
  float32_t Value1 = CPU->COP1.Registers[_FS_].F32;
  float32_t Value2 = CPU->COP1.Registers[_FT_].F32;
  bool Result = (Value1 == Value2);
  CPU->COP1.EqualFlag = Result;
}

DEFINE_MIPS_INSTRUCTION(C_F_S)
{
  NOT_IMMPLEMENTED_YET();
  float32_t Value1 = CPU->COP1.Registers[_FS_].F32;
  float32_t Value2 = CPU->COP1.Registers[_FT_].F32;
  bool Result = (Value1 == Value2);
  CPU->COP1.EqualFlag = 0; // WTF?
}

DEFINE_MIPS_INSTRUCTION(C_LE_S)
{
  NOT_IMMPLEMENTED_YET();
  float32_t Value1 = CPU->COP1.Registers[_FS_].F32;
  float32_t Value2 = CPU->COP1.Registers[_FT_].F32;
  bool Result = (Value1 <= Value2);
  CPU->COP1.EqualFlag = Result;
}

DEFINE_MIPS_INSTRUCTION(C_LT_S)
{
  NOT_IMMPLEMENTED_YET();
  float32_t Value1 = CPU->COP1.Registers[_FS_].F32;
  float32_t Value2 = CPU->COP1.Registers[_FT_].F32;
  bool Result = (Value1 < Value2);
  CPU->COP1.EqualFlag = Result;
}

DEFINE_MIPS_INSTRUCTION(CFC1)
{
  NOT_IMMPLEMENTED_YET();
  //ASSERT(_FS_ == 0 || _FS_ == 31);
  float32_t Result = CPU->COP1.Registers[_FS_].F32;
  CPU->Registers[_RT_].F32[0] = Result;  // sign extend
}

DEFINE_MIPS_INSTRUCTION(CTC1)
{
  NOT_IMMPLEMENTED_YET();
  float32_t Result = CPU->Registers[_RT_].F32[0];
  CPU->COP1.Registers[_FS_].F32 = Result;
}

DEFINE_MIPS_INSTRUCTION(CVTS)
{
  NOT_IMMPLEMENTED_YET();
  int32_t Value = CPU->COP1.Registers[_FS_].S32;
  float32_t Result = (float32_t)Value;
  CPU->COP1.Registers[_FD_].F32 = Result;
}

DEFINE_MIPS_INSTRUCTION(CVTW)
{
  NOT_IMMPLEMENTED_YET();
  float32_t Value = CPU->COP1.Registers[_FS_].F32;
  int32_t Result = (int32_t)Value;
  CPU->COP1.Registers[_FD_].S32 = Result;  // convert and round
}

DEFINE_MIPS_INSTRUCTION(DIV_S)
{
  NOT_IMMPLEMENTED_YET();
  float32_t Value1 = CPU->COP1.Registers[_FS_].F32;
  float32_t Value2 = CPU->COP1.Registers[_FT_].F32;
  float32_t Result = Value1 / Value2;
  CPU->COP1.Registers[_FD_].F32 = Result;
}

DEFINE_MIPS_INSTRUCTION(MADD_S)
{
  NOT_IMMPLEMENTED_YET();
  float32_t Value1 = CPU->COP1.Registers[_FS_].F32;
  float32_t Value2 = CPU->COP1.Registers[_FT_].F32;
  float32_t Product = Value1 * Value2;
  float32_t Result = CPU->COP1.Accumulator.F32 + Product;
  CPU->COP1.Registers[_FD_].F32 = Result;
}

DEFINE_MIPS_INSTRUCTION(MADDA_S)
{
  NOT_IMMPLEMENTED_YET();
  float32_t Value1 = CPU->COP1.Registers[_FS_].F32;
  float32_t Value2 = CPU->COP1.Registers[_FT_].F32;
  float32_t Product = Value1 * Value2;
  float32_t Result = CPU->COP1.Accumulator.F32 + Product;
  CPU->COP1.Accumulator.F32 = Result;
}

DEFINE_MIPS_INSTRUCTION(MAX_S)
{
  NOT_IMMPLEMENTED_YET();
  float32_t Value1 = CPU->COP1.Registers[_FS_].F32;
  float32_t Value2 = CPU->COP1.Registers[_FT_].F32;
  float32_t Result = MAX(Value1, Value2);
  CPU->COP1.Registers[_FD_].F32 = Result;
}

DEFINE_MIPS_INSTRUCTION(MFC1)
{
  NOT_IMMPLEMENTED_YET();
  float32_t Result = CPU->COP1.Registers[_FS_].F32;
  CPU->Registers[_RT_].F32[0] = Result;  // sign extend
}

DEFINE_MIPS_INSTRUCTION(MIN_S)
{
  NOT_IMMPLEMENTED_YET();
  float32_t Value1 = CPU->COP1.Registers[_FS_].F32;
  float32_t Value2 = CPU->COP1.Registers[_FT_].F32;
  float32_t Result = MIN(Value1, Value2);
  CPU->COP1.Registers[_FD_].F32 = Result;
}

DEFINE_MIPS_INSTRUCTION(MOV_S)
{
  NOT_IMMPLEMENTED_YET();
  float32_t Result = CPU->COP1.Registers[_FS_].F32;
  CPU->COP1.Registers[_FD_].F32 = Result;
}

DEFINE_MIPS_INSTRUCTION(MSUB_S)
{
  NOT_IMMPLEMENTED_YET();
  float32_t Value1 = CPU->COP1.Registers[_FS_].F32;
  float32_t Value2 = CPU->COP1.Registers[_FT_].F32;
  float32_t Product = Value1 * Value2;
  float32_t Result = CPU->COP1.Accumulator.F32 - Product;
  CPU->COP1.Registers[_FD_].F32 = Result;
}

DEFINE_MIPS_INSTRUCTION(MSUBA_S)
{
  NOT_IMMPLEMENTED_YET();
  float32_t Value1 = CPU->COP1.Registers[_FS_].F32;
  float32_t Value2 = CPU->COP1.Registers[_FT_].F32;
  float32_t Product = Value1 * Value2;
  float32_t Result = CPU->COP1.Accumulator.F32 - Product;
  CPU->COP1.Accumulator.F32 = Result;
}

DEFINE_MIPS_INSTRUCTION(MTC1)
{
  NOT_IMMPLEMENTED_YET();
  float32_t Result = CPU->Registers[_RT_].F32[0];
  CPU->COP1.Registers[_FS_].F32 = Result;
}

DEFINE_MIPS_INSTRUCTION(MUL_S)
{
  NOT_IMMPLEMENTED_YET();
  float32_t Value1 = CPU->COP1.Registers[_FS_].F32;
  float32_t Value2 = CPU->COP1.Registers[_FT_].F32;
  float32_t Result = Value1 * Value2;
  CPU->COP1.Registers[_FD_].F32 = Result;
}

DEFINE_MIPS_INSTRUCTION(MULA_S)
{
  NOT_IMMPLEMENTED_YET();
  float32_t Value1 = CPU->COP1.Registers[_FS_].F32;
  float32_t Value2 = CPU->COP1.Registers[_FT_].F32;
  float32_t Result = Value1 * Value2;
  CPU->COP1.Accumulator.F32 = Result;
}

DEFINE_MIPS_INSTRUCTION(NEG_S)
{
  NOT_IMMPLEMENTED_YET();
  float32_t Value = CPU->COP1.Registers[_FS_].F32;
  float32_t Result = -Value;
  CPU->COP1.Registers[_FD_].F32 = Result;
}

DEFINE_MIPS_INSTRUCTION(RSQRT_S)
{
  NOT_IMMPLEMENTED_YET();
  float32_t Value1 = CPU->COP1.Registers[_FS_].F32;
  float32_t Value2 = CPU->COP1.Registers[_FT_].F32;
  float32_t Result = Value1 / sqrtf(Value2);
  CPU->COP1.Registers[_FD_].F32 = Result;
}

DEFINE_MIPS_INSTRUCTION(SQRT_S)
{
  NOT_IMMPLEMENTED_YET();
  float32_t Value = CPU->COP1.Registers[_FT_].F32;
  float32_t Result = sqrtf(Value);
  CPU->COP1.Registers[_FD_].F32 = Result;
}

DEFINE_MIPS_INSTRUCTION(SUB_S)
{
  NOT_IMMPLEMENTED_YET();
  float32_t Value1 = CPU->COP1.Registers[_FS_].F32;
  float32_t Value2 = CPU->COP1.Registers[_FT_].F32;
  float32_t Result = Value1 - Value2;
  CPU->COP1.Registers[_FD_].F32 = Result;
}

DEFINE_MIPS_INSTRUCTION(SUBA_S)
{
  NOT_IMMPLEMENTED_YET();
  float32_t Value1 = CPU->COP1.Registers[_FS_].F32;
  float32_t Value2 = CPU->COP1.Registers[_FT_].F32;
  float32_t Result = Value1 - Value2;
  CPU->COP1.Accumulator.F32 = Result;
}