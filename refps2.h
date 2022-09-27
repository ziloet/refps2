#ifdef __clang__
#define function_ssse3 static __attribute__ ((__target__("ssse3")))
#else
#define function_ssse3 static
#endif

#define ASSERT(Expr) if(Expr); else DEBUG_BREAK()
#define ARRAY_LENGTH(Array) (sizeof(Array) / sizeof(Array[0]))
#define STATIC_ASSERT(Expr) typedef int static_assert_typedef[(Expr) ? 1 : -1]
#define KIBI_BYTE(Value) (Value * 1024)
#define MEBI_BYTE(Value) ((Value * 1024) * 1024)
#define ABS(Value) ((Value) < 0) ? -(Value) : Value
#define MIN(A, B) (((A) < (B)) ? (A) : (B))
#define MAX(A, B) (((A) > (B)) ? (A) : (B))
#define CLAMP(Min, Value, Max) (((Value) > (Max)) ? (Max) : ((Value) < (Min)) ? (Min) : (Value))

typedef float float32_t;

typedef union
{
  float32_t F32;
  uint32_t  U32;
  int32_t   S32;
} register32_t;

typedef union
{
  __m128    _128;
  __m128i   _128i;
  __m64     _64[2];
  uint64_t  U64[2];
  int64_t   S64[2];
  float32_t F32[4];
  uint32_t  U32[4];
  int32_t   S32[4];
} register128_t;

//int _fltused = 1;

#pragma function(memset)
static void*
memset(void* DestPtr, int Value, size_t NumBytes)
{
  unsigned char* Dest = (unsigned char*)DestPtr;
  unsigned char ByteValue = (unsigned char)Value;
  while(NumBytes)
  {
    *Dest = ByteValue;
    Dest += 1;
    NumBytes -= 1;
  }
  return Dest;
}