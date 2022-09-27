#define DEFINE_INSTRUCTION_MMI(Name) function_ssse3 void Name(ee_cpu* CPU)

static int32_t
AddSaturateS32(int32_t Value1, int32_t Value2)
{
  int64_t Sum = Value1 + Value2;
  int32_t Result = (int32_t)CLAMP(INT32_MIN, Sum, INT32_MAX);
  return Result;
}

static int32_t
SubSaturateS32(int32_t Value1, int32_t Value2)
{
  int64_t Sum = Value1 - Value2;
  int32_t Result = (int32_t)CLAMP(INT32_MIN, Sum, INT32_MAX);
  return Result;
}

static uint32_t
AddSaturateU32(uint32_t Value1, uint32_t Value2)
{
  uint64_t Sum = Value1 + Value2;
  uint32_t Result = (uint32_t)CLAMP(INT32_MIN, Sum, INT32_MAX);
  return Result;
}

static uint32_t
SubSaturateU32(uint32_t Value1, uint32_t Value2)
{
  int64_t Sum = Value1 - Value2;
  int32_t Result = (int32_t)CLAMP(INT32_MIN, Sum, INT32_MAX);
  return Result;
}

DEFINE_INSTRUCTION_MMI(DIV1)
{
  NOT_IMMPLEMENTED_YET();
}

DEFINE_INSTRUCTION_MMI(DIVU1)
{
  NOT_IMMPLEMENTED_YET();
}



DEFINE_INSTRUCTION_MMI(MADD)
{
  NOT_IMMPLEMENTED_YET();
  int32_t Value1 = (int32_t)CPU->Registers[_RS_].S64[0];
  int32_t Value2 = (int32_t)CPU->Registers[_RT_].S64[0];
  int64_t Product = (int64_t)Value1 * Value2;
  int64_t Result = (int32_t)Product;
  CPU->LO.S64[0] = Result;
  CPU->HI.S64[0] = (int32_t)(Product >> 32);
  CPU->Registers[_RD_].S64[0] = Result;
}

DEFINE_INSTRUCTION_MMI(MADD1)
{
  NOT_IMMPLEMENTED_YET();
}

DEFINE_INSTRUCTION_MMI(MADDU)
{
  NOT_IMMPLEMENTED_YET();
  uint32_t Value1 = (uint32_t)CPU->Registers[_RS_].U64[0];
  uint32_t Value2 = (uint32_t)CPU->Registers[_RT_].U64[0];
  uint64_t Product = (uint64_t)Value1 * Value2;
  int64_t Result = (int32_t)Product;
  CPU->LO.S64[0] = Result;
  CPU->HI.S64[0] = (int32_t)(Product >> 32);
  CPU->Registers[_RD_].S64[0] = Result;
}

DEFINE_INSTRUCTION_MMI(MADDU1)
{
  NOT_IMMPLEMENTED_YET();
}

DEFINE_INSTRUCTION_MMI(MFHI1)
{
  NOT_IMMPLEMENTED_YET();
  uint64_t Result = CPU->HI.U64[1];
  CPU->Registers[_RD_].U64[0] = Result;
}

DEFINE_INSTRUCTION_MMI(MFLO1)
{
  NOT_IMMPLEMENTED_YET();
  uint64_t Result = CPU->LO.U64[1];
  CPU->Registers[_RD_].U64[0] = Result;
}

DEFINE_INSTRUCTION_MMI(MTHI1)
{
  NOT_IMMPLEMENTED_YET();
  uint64_t Result = CPU->Registers[_RS_].U64[0];
  CPU->HI.U64[1] = Result;
}

DEFINE_INSTRUCTION_MMI(MTLO1)
{
  NOT_IMMPLEMENTED_YET();
  uint64_t Result = CPU->Registers[_RS_].U64[0];
  CPU->LO.U64[1] = Result;
}

DEFINE_INSTRUCTION_MMI(MULT1)
{
  NOT_IMMPLEMENTED_YET();
}

DEFINE_INSTRUCTION_MMI(MULTU1)
{
  NOT_IMMPLEMENTED_YET();
}

DEFINE_INSTRUCTION_MMI(PABSH)
{
  NOT_IMMPLEMENTED_YET();
  __m128i Value = CPU->Registers[_RT_]._128i;
  __m128i Result = _mm_abs_epi16(Value);
  CPU->Registers[_RD_]._128i = Result;
}

DEFINE_INSTRUCTION_MMI(PABSW)
{
  NOT_IMMPLEMENTED_YET();
  __m128i Value = CPU->Registers[_RT_]._128i;
  __m128i Result = _mm_abs_epi32(Value);
  CPU->Registers[_RD_]._128i = Result;
}

DEFINE_INSTRUCTION_MMI(PADDB)
{
  NOT_IMMPLEMENTED_YET();
  __m128i Value1 = CPU->Registers[_RS_]._128i;
  __m128i Value2 = CPU->Registers[_RT_]._128i;
  __m128i Result = _mm_add_epi8(Value1, Value2);
  CPU->Registers[_RD_]._128i = Result;
}

DEFINE_INSTRUCTION_MMI(PADDH)
{
  NOT_IMMPLEMENTED_YET();
  __m128i Value1 = CPU->Registers[_RS_]._128i;
  __m128i Value2 = CPU->Registers[_RT_]._128i;
  __m128i Result = _mm_add_epi16(Value1, Value2);
  CPU->Registers[_RD_]._128i = Result;
}

DEFINE_INSTRUCTION_MMI(PADDSB)
{
  NOT_IMMPLEMENTED_YET();
  __m128i Value1 = CPU->Registers[_RS_]._128i;
  __m128i Value2 = CPU->Registers[_RT_]._128i;
  __m128i Result = _mm_adds_epi8(Value1, Value2);
  CPU->Registers[_RD_]._128i = Result;
}

DEFINE_INSTRUCTION_MMI(PADDSH)
{
  NOT_IMMPLEMENTED_YET();
  __m128i Value1 = CPU->Registers[_RS_]._128i;
  __m128i Value2 = CPU->Registers[_RT_]._128i;
  __m128i Result = _mm_adds_epi16(Value1, Value2);
  CPU->Registers[_RD_]._128i = Result;
}

DEFINE_INSTRUCTION_MMI(PADDSW)
{
  NOT_IMMPLEMENTED_YET();
  #if 0
  // no intrinsic equivalent?
  __m128i Value1 = CPU->Registers[_RS_]._128i;
  __m128i Value2 = CPU->Registers[_RT_]._128i;
  __m128i Result = _mm_adds_epi32(Value1, Value2);
  CPU->Registers[_RD_].S32[Index] = Result;
  #endif
  for(int Index = 0; Index < 4; Index += 1)
  {
    int32_t Value1 = CPU->Registers[_RS_].S32[Index];
    int32_t Value2 = CPU->Registers[_RT_].S32[Index];
    int32_t Result = AddSaturateS32(Value1, Value2);
    CPU->Registers[_RD_].S32[Index] = Result;
  }
}

DEFINE_INSTRUCTION_MMI(PADDUB)
{
  NOT_IMMPLEMENTED_YET();
  __m128i Value1 = CPU->Registers[_RS_]._128i;
  __m128i Value2 = CPU->Registers[_RT_]._128i;
  __m128i Result = _mm_adds_epu8(Value1, Value2);
  CPU->Registers[_RD_]._128i = Result;
}

DEFINE_INSTRUCTION_MMI(PADDUH)
{
  NOT_IMMPLEMENTED_YET();
  __m128i Value1 = CPU->Registers[_RS_]._128i;
  __m128i Value2 = CPU->Registers[_RT_]._128i;
  __m128i Result = _mm_adds_epu16(Value1, Value2);
  CPU->Registers[_RD_]._128i = Result;
}

DEFINE_INSTRUCTION_MMI(PADDUW)
{
  NOT_IMMPLEMENTED_YET();
  #if 0
  // no intrinsic equivalent?
  __m128i Value1 = CPU->Registers[_RS_]._128i;
  __m128i Value2 = CPU->Registers[_RT_]._128i;
  __m128i Result = _mm_adds_epu32(Value1, Value2);
  CPU->Registers[_RD_]._128i = Result;
  #endif
  for(int Index = 0; Index < 4; Index += 1)
  {
    int32_t Value1 = CPU->Registers[_RS_].S32[Index];
    int32_t Value2 = CPU->Registers[_RT_].S32[Index];
    int32_t Result = AddSaturateU32(Value1, Value2);
    CPU->Registers[_RD_].S32[Index] = Result;
  }
}

DEFINE_INSTRUCTION_MMI(PADDW)
{
  NOT_IMMPLEMENTED_YET();
  __m128i Value1 = CPU->Registers[_RS_]._128i;
  __m128i Value2 = CPU->Registers[_RT_]._128i;
  __m128i Result = _mm_add_epi32(Value1, Value2);
  CPU->Registers[_RD_]._128i = Result;
}

DEFINE_INSTRUCTION_MMI(PADSBH)
{
  NOT_IMMPLEMENTED_YET();
  #if 0
  __m64 Value1 = CPU->Registers[_RS_]._64[0];
  __m64 Value2 = CPU->Registers[_RT_]._64[0];
  __m64 Result1 = _mm_sub_si16(Value1, Value2);
  __m64 Value3 = CPU->Registers[_RS_]._64[1];
  __m64 Value4 = CPU->Registers[_RT_]._64[1];
  __m64 Result2 = _mm_add_si16(Value3, Value4);
  __m128i Result = _mm_casti128_si64(Result1);
  Result = _mm_insert
  CPU->Registers[_RD_]._128i = Result;
  #endif
}

DEFINE_INSTRUCTION_MMI(PAND)
{
  NOT_IMMPLEMENTED_YET();
  __m128i Value1 = CPU->Registers[_RS_]._128i;
  __m128i Value2 = CPU->Registers[_RT_]._128i;
  __m128i Result = _mm_and_si128(Value1, Value2);
  CPU->Registers[_RD_]._128i = Result;
}

DEFINE_INSTRUCTION_MMI(PCEQB)
{
  NOT_IMMPLEMENTED_YET();
  __m128i Value1 = CPU->Registers[_RS_]._128i;
  __m128i Value2 = CPU->Registers[_RT_]._128i;
  __m128i Result = _mm_cmpeq_epi8(Value1, Value2);
  CPU->Registers[_RD_]._128i = Result;
}

DEFINE_INSTRUCTION_MMI(PCEQH)
{
  NOT_IMMPLEMENTED_YET();
  __m128i Value1 = CPU->Registers[_RS_]._128i;
  __m128i Value2 = CPU->Registers[_RT_]._128i;
  __m128i Result = _mm_cmpeq_epi16(Value1, Value2);
  CPU->Registers[_RD_]._128i = Result;
}

DEFINE_INSTRUCTION_MMI(PCEQW)
{
  NOT_IMMPLEMENTED_YET();
  __m128i Value1 = CPU->Registers[_RS_]._128i;
  __m128i Value2 = CPU->Registers[_RT_]._128i;
  __m128i Result = _mm_cmpeq_epi32(Value1, Value2);
  CPU->Registers[_RD_]._128i = Result;
}

DEFINE_INSTRUCTION_MMI(PCGTB)
{
  NOT_IMMPLEMENTED_YET();
  __m128i Value1 = CPU->Registers[_RS_]._128i;
  __m128i Value2 = CPU->Registers[_RT_]._128i;
  __m128i Result = _mm_cmpgt_epi8(Value1, Value2);
  CPU->Registers[_RD_]._128i = Result;
}

DEFINE_INSTRUCTION_MMI(PCGTH)
{
  NOT_IMMPLEMENTED_YET();
  __m128i Value1 = CPU->Registers[_RS_]._128i;
  __m128i Value2 = CPU->Registers[_RT_]._128i;
  __m128i Result = _mm_cmpgt_epi16(Value1, Value2);
  CPU->Registers[_RD_]._128i = Result;
}

DEFINE_INSTRUCTION_MMI(PCGTW)
{
  NOT_IMMPLEMENTED_YET();
  __m128i Value1 = CPU->Registers[_RS_]._128i;
  __m128i Value2 = CPU->Registers[_RT_]._128i;
  __m128i Result = _mm_cmpgt_epi32(Value1, Value2);
  CPU->Registers[_RD_]._128i = Result;
}

DEFINE_INSTRUCTION_MMI(PCPYH)
{
  NOT_IMMPLEMENTED_YET();
}

DEFINE_INSTRUCTION_MMI(PCPYLD)
{
  NOT_IMMPLEMENTED_YET();
}

DEFINE_INSTRUCTION_MMI(PCPYUD)
{
  NOT_IMMPLEMENTED_YET();
}

DEFINE_INSTRUCTION_MMI(PDIVBW)
{
  NOT_IMMPLEMENTED_YET();
}

DEFINE_INSTRUCTION_MMI(PDIVUW)
{
  NOT_IMMPLEMENTED_YET();
}

DEFINE_INSTRUCTION_MMI(PDIVW)
{
  NOT_IMMPLEMENTED_YET();
}

DEFINE_INSTRUCTION_MMI(PEXCH)
{
  NOT_IMMPLEMENTED_YET();
}

DEFINE_INSTRUCTION_MMI(PEXCW)
{
  NOT_IMMPLEMENTED_YET();
}

DEFINE_INSTRUCTION_MMI(PEXEH)
{
  NOT_IMMPLEMENTED_YET();
}

DEFINE_INSTRUCTION_MMI(PEXEW)
{
  NOT_IMMPLEMENTED_YET();
}

DEFINE_INSTRUCTION_MMI(PEXT5)
{
  NOT_IMMPLEMENTED_YET();
}

DEFINE_INSTRUCTION_MMI(PEXTLB)
{
  NOT_IMMPLEMENTED_YET();
}

DEFINE_INSTRUCTION_MMI(PEXTLH)
{
  NOT_IMMPLEMENTED_YET();
}

DEFINE_INSTRUCTION_MMI(PEXTLW)
{
  NOT_IMMPLEMENTED_YET();
}

DEFINE_INSTRUCTION_MMI(PEXTUB)
{
  NOT_IMMPLEMENTED_YET();
}

DEFINE_INSTRUCTION_MMI(PEXTUH)
{
  NOT_IMMPLEMENTED_YET();
}

DEFINE_INSTRUCTION_MMI(PEXTUW)
{
  NOT_IMMPLEMENTED_YET();
}

DEFINE_INSTRUCTION_MMI(PHMADH)
{
  NOT_IMMPLEMENTED_YET();
}

DEFINE_INSTRUCTION_MMI(PHMSBH)
{
  NOT_IMMPLEMENTED_YET();
}

DEFINE_INSTRUCTION_MMI(PINTEH)
{
  NOT_IMMPLEMENTED_YET();
}

DEFINE_INSTRUCTION_MMI(PINTH)
{
  NOT_IMMPLEMENTED_YET();
}

DEFINE_INSTRUCTION_MMI(PLZCW)
{
  NOT_IMMPLEMENTED_YET();
}

DEFINE_INSTRUCTION_MMI(PMADDH)
{
  NOT_IMMPLEMENTED_YET();
}

DEFINE_INSTRUCTION_MMI(PMADDUW)
{
  NOT_IMMPLEMENTED_YET();
}

DEFINE_INSTRUCTION_MMI(PMADDW)
{
  NOT_IMMPLEMENTED_YET();
}

DEFINE_INSTRUCTION_MMI(PMAXH)
{
  NOT_IMMPLEMENTED_YET();
}

DEFINE_INSTRUCTION_MMI(PMAXW)
{
  NOT_IMMPLEMENTED_YET();
}

DEFINE_INSTRUCTION_MMI(PMFHI)
{
  NOT_IMMPLEMENTED_YET();
}

DEFINE_INSTRUCTION_MMI(PMFHL)
{
  NOT_IMMPLEMENTED_YET();
}

DEFINE_INSTRUCTION_MMI(PMFLO)
{
  NOT_IMMPLEMENTED_YET();
}

DEFINE_INSTRUCTION_MMI(PMINH)
{
  NOT_IMMPLEMENTED_YET();
}

DEFINE_INSTRUCTION_MMI(PMINW)
{
  NOT_IMMPLEMENTED_YET();
}

DEFINE_INSTRUCTION_MMI(PMSUBH)
{
  NOT_IMMPLEMENTED_YET();
}

DEFINE_INSTRUCTION_MMI(PMSUBW)
{
  NOT_IMMPLEMENTED_YET();
}

DEFINE_INSTRUCTION_MMI(PMTHI)
{
  NOT_IMMPLEMENTED_YET();
}

DEFINE_INSTRUCTION_MMI(PMTHL)
{
  NOT_IMMPLEMENTED_YET();
}

DEFINE_INSTRUCTION_MMI(PMTLO)
{
  NOT_IMMPLEMENTED_YET();
}

DEFINE_INSTRUCTION_MMI(PMULTH)
{
  NOT_IMMPLEMENTED_YET();
}

DEFINE_INSTRUCTION_MMI(PMULTUW)
{
  NOT_IMMPLEMENTED_YET();
}

DEFINE_INSTRUCTION_MMI(PMULTW)
{
  NOT_IMMPLEMENTED_YET();
}

DEFINE_INSTRUCTION_MMI(PNOR)
{
  NOT_IMMPLEMENTED_YET();
}

DEFINE_INSTRUCTION_MMI(POR)
{
  NOT_IMMPLEMENTED_YET();
}

DEFINE_INSTRUCTION_MMI(PPAC5)
{
  NOT_IMMPLEMENTED_YET();
}

DEFINE_INSTRUCTION_MMI(PPACB)
{
  NOT_IMMPLEMENTED_YET();
}

DEFINE_INSTRUCTION_MMI(PPACH)
{
  NOT_IMMPLEMENTED_YET();
}

DEFINE_INSTRUCTION_MMI(PPACW)
{
  NOT_IMMPLEMENTED_YET();
}

DEFINE_INSTRUCTION_MMI(PREVH)
{
  NOT_IMMPLEMENTED_YET();
}

DEFINE_INSTRUCTION_MMI(PROT3W)
{
  NOT_IMMPLEMENTED_YET();
}

DEFINE_INSTRUCTION_MMI(PSLLH)
{
  NOT_IMMPLEMENTED_YET();
}

DEFINE_INSTRUCTION_MMI(PSLLVW)
{
  NOT_IMMPLEMENTED_YET();
}

DEFINE_INSTRUCTION_MMI(PSLLW)
{
  NOT_IMMPLEMENTED_YET();
}

DEFINE_INSTRUCTION_MMI(PSRAH)
{
  NOT_IMMPLEMENTED_YET();
}

DEFINE_INSTRUCTION_MMI(PSRAVW)
{
  NOT_IMMPLEMENTED_YET();
}

DEFINE_INSTRUCTION_MMI(PSRAW)
{
  NOT_IMMPLEMENTED_YET();
}

DEFINE_INSTRUCTION_MMI(PSRLH)
{
  NOT_IMMPLEMENTED_YET();
}

DEFINE_INSTRUCTION_MMI(PSRLVW)
{
  NOT_IMMPLEMENTED_YET();
}

DEFINE_INSTRUCTION_MMI(PSRLW)
{
  NOT_IMMPLEMENTED_YET();
}

DEFINE_INSTRUCTION_MMI(PSUBB)
{
  NOT_IMMPLEMENTED_YET();
  __m128i Value1 = CPU->Registers[_RS_]._128i;
  __m128i Value2 = CPU->Registers[_RT_]._128i;
  __m128i Result = _mm_sub_epi8(Value1, Value2);
  CPU->Registers[_RD_]._128i = Result;
}

DEFINE_INSTRUCTION_MMI(PSUBH)
{
  NOT_IMMPLEMENTED_YET();
  __m128i Value1 = CPU->Registers[_RS_]._128i;
  __m128i Value2 = CPU->Registers[_RT_]._128i;
  __m128i Result = _mm_sub_epi16(Value1, Value2);
  CPU->Registers[_RD_]._128i = Result;
}

DEFINE_INSTRUCTION_MMI(PSUBSB)
{
  NOT_IMMPLEMENTED_YET();
  __m128i Value1 = CPU->Registers[_RS_]._128i;
  __m128i Value2 = CPU->Registers[_RT_]._128i;
  __m128i Result = _mm_subs_epi8(Value1, Value2);
  CPU->Registers[_RD_]._128i = Result;
}

DEFINE_INSTRUCTION_MMI(PSUBSH)
{
  NOT_IMMPLEMENTED_YET();
  __m128i Value1 = CPU->Registers[_RS_]._128i;
  __m128i Value2 = CPU->Registers[_RT_]._128i;
  __m128i Result = _mm_subs_epi16(Value1, Value2);
  CPU->Registers[_RD_]._128i = Result;
}

DEFINE_INSTRUCTION_MMI(PSUBSW)
{
  NOT_IMMPLEMENTED_YET();
  #if 0
  // no intrinsic equivalent?
  __m128i Value1 = CPU->Registers[_RS_]._128i;
  __m128i Value2 = CPU->Registers[_RT_]._128i;
  __m128i Result = _mm_subs_epi32(Value1, Value2);
  CPU->Registers[_RD_]._128i = Result;
  #endif
  for(int Index = 0; Index < 4; Index += 1)
  {
    int32_t Value1 = CPU->Registers[_RS_].S32[Index];
    int32_t Value2 = CPU->Registers[_RT_].S32[Index];
    int32_t Result = SubSaturateS32(Value1, Value2);
    CPU->Registers[_RD_].S32[Index] = Result;
  }
}

DEFINE_INSTRUCTION_MMI(PSUBUB)
{
  NOT_IMMPLEMENTED_YET();
  __m128i Value1 = CPU->Registers[_RS_]._128i;
  __m128i Value2 = CPU->Registers[_RT_]._128i;
  __m128i Result = _mm_subs_epu8(Value1, Value2);
  CPU->Registers[_RD_]._128i = Result;
}

DEFINE_INSTRUCTION_MMI(PSUBUH)
{
  NOT_IMMPLEMENTED_YET();
  __m128i Value1 = CPU->Registers[_RS_]._128i;
  __m128i Value2 = CPU->Registers[_RT_]._128i;
  __m128i Result = _mm_subs_epu16(Value1, Value2);
  CPU->Registers[_RD_]._128i = Result;
}

DEFINE_INSTRUCTION_MMI(PSUBUW)
{
  NOT_IMMPLEMENTED_YET();
  #if 0
  // no intrinsic equivalent?
  __m128i Value1 = CPU->Registers[_RS_]._128i;
  __m128i Value2 = CPU->Registers[_RT_]._128i;
  __m128i Result = _mm_subs_epu32(Value1, Value2);
  CPU->Registers[_RD_]._128i = Result;
  #endif
  for(int Index = 0; Index < 4; Index += 1)
  {
    int32_t Value1 = CPU->Registers[_RS_].S32[Index];
    int32_t Value2 = CPU->Registers[_RT_].S32[Index];
    int32_t Result = SubSaturateU32(Value1, Value2);
    CPU->Registers[_RD_].S32[Index] = Result;
  }
}

DEFINE_INSTRUCTION_MMI(PSUBW)
{
  NOT_IMMPLEMENTED_YET();
  __m128i Value1 = CPU->Registers[_RS_]._128i;
  __m128i Value2 = CPU->Registers[_RT_]._128i;
  __m128i Result = _mm_sub_epi32(Value1, Value2);
  CPU->Registers[_RD_]._128i = Result;
}

DEFINE_INSTRUCTION_MMI(PXOR)
{
  NOT_IMMPLEMENTED_YET();
  __m128i Value1 = CPU->Registers[_RS_]._128i;
  __m128i Value2 = CPU->Registers[_RT_]._128i;
  __m128i Result = _mm_xor_si128(Value1, Value2);
  CPU->Registers[_RD_]._128i = Result;
}

DEFINE_INSTRUCTION_MMI(QFSRV)
{
  NOT_IMMPLEMENTED_YET();
}