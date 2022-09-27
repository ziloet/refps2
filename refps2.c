static float
sqrtf(float Value)
{
  float Result = Value;
  // ...
  return Result;
}

static bool
StringsEqual(char* Str1, char* Str2)
{
  for(;;)
  {
    if(!Str1 || !Str2)
    {
      return Str1 == Str2;
    }
    if(*Str1 != *Str2)
    {
      return false;
    }
    if(*Str1 == '\0')
    {
      return true;
    }
    Str1 += 1;
    Str2 += 1;
  }
}

static bool
AddOverflow32(int32_t Value1, int32_t Value2)
{
  bool Result = (Value1 >= 0) && ((INT32_MAX - Value1) < Value2);
  return Result;
}

static bool
AddUnderflow32(int32_t Value1, int32_t Value2)
{
  bool Result = (Value1 < 0) && ((INT32_MIN - Value1) > Value2);
  return Result;
}

static bool
AddOverflow64(int64_t Value1, int64_t Value2)
{
  bool Result = (Value1 >= 0) && ((INT64_MAX - Value1) < Value2);
  return Result;
}

static bool
AddUnderflow64(int64_t Value1, int64_t Value2)
{
  bool Result = (Value1 < 0) && ((INT64_MIN - Value1) > Value2);
  return Result;
}