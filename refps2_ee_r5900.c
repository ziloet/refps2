#if 0
static ps2_console*
GetConsolePointer(ee_cpu* CPU)
{
  uintptr_t ByteAddress = (uintptr_t)CPU;
  uintptr_t Offset = 
  ps2_console* Result = ByteAddress - Offset

}
#endif

static void
R5900_Reset(ee_cpu* CPU)
{
  memset(&CPU->COP0, 0, sizeof(CPU->COP0));
  CPU->ProgramCounter = EXCEPTION_VECTOR_RESET_NMI;
  CPU->COP0.Registers.ProcessorID = EE_CORE_PROCESSOR_ID;
  //CPU->COP0.Registers.Status.ERL = 1;
  //CPU->COP0.Registers.Status.BEV = 1;
  CPU->COP0.Registers.Status = 0x400004;
  //CPU->COP0.Random.UppderBound = 1;
}


#if 0
static void
R5900_Exception(ee_cpu* CPU, uint32_t ExceptionCode)
{
  CPU->COP0.Status.ExceptionLevel = 1;
  uint32_t ExceptionVectorAddress = 0;
  CPU->COP0.EPC = (CPU.ProgramCounter - 4);
  switch(ExceptionCode)
  {
    case EXCEPTION_RESET:
    case EXCEPTION_NMI:
    {
      ExceptionVectorAddress = EXCEPTION_VECTOR_RESET_NMI;
    } break;
    case EXCEPTION_TLB_REFILL:
    {
      ExceptionVectorAddress = EXCEPTION_VECTOR_TLB_REFILL;
    } break;
    case EXCEPTION_PERFORMANCE_COUNTER:
    {
      ExceptionVectorAddress = EXCEPTION_VECTOR_COUNTER;
    } break;
    case EXCEPTION_DEBUG:
    {
      ExceptionVectorAddress = EXCEPTION_VECTOR_DEBUG;
    } break;
    case EXCEPTION_INTERRUPT:
    {
      ExceptionVectorAddress = EXCEPTION_VECTOR_INTERRUPT;
    } break;
    default:
    {
      ExceptionVectorAddress = EXCEPTION_VECTOR_COMMON;
    } break;
  }
  CPU->ProgramCounter = ExceptionVectorAddress;
}

#endif

static void
FlushPipeline(ee_cpu* CPU)
{

}

static void
ClearInstructionCache(ee_cpu* CPU)
{

}

static void
FetchInstructions(ee_cpu* CPU)
{

}


#if 0
static void
ExecuteInstruction(ee_cpu* CPU, uint32_t Instruction)
{
  uint32_t Opcode = Instruction >> 26;
  switch(Opcode)
  {
    case 0:
    {
      uint32_t Function = Instruction  & 0x3f;
      uint8_t RS = (Instruction >> 21) & 0x1f;
      uint8_t RT = (Instruction >> 16) & 0x1f;
      uint8_t RD = (Instruction >> 11) & 0x1f;
      uint8_t SA = (Instruction >> 6)  & 0x1f;
      Opcode_Special[Function](RS, RT, RD, SA);
    } break;
    case 1:
    {
      uint8_t RS = (Instruction >> 21) & 0x1f;
      uint8_t RT = (Instruction >> 16) & 0x1f;
      uint16_t Offset = Instruction & 0xffff;
      Opcode_RegImm[RT](RS, Offset);
    } break;
  }
}
#endif

static uint32_t
ITLB_Read32(uint32_t VirtualAddress)
{
  uint32_t Result = 0;
  return Result;
//  auto vmv = vtlbdata.vmap[mem>>VTLB_PAGE_BITS];

//  if (!vmv.isHandler(mem))
//  {
//    if (!CHECK_EEREC) {
//      if(CHECK_CACHE && CheckCache(mem)) 
//      {
//        *out = readCache64(mem);
//        return;
//      }
//    }
//
//    *out = *(mem64_t*)vmv.assumePtr(mem);
//  }
//  else
//  {
//    //has to: translate, find function, call function
//    u32 paddr = vmv.assumeHandlerGetPAddr(mem);
//    //Console.WriteLn("Translated 0x%08X to 0x%08X", addr,paddr);
//    vmv.assumeHandler<64, false>()(paddr, out);
//  }
}

static void
R5900_Run(ee_cpu* CPU)
{
  for(;;)
  {
    //FetchInstructions(CPU);
    CPU->CurrentInstruction = MemoryRead32(CPU->ProgramCounter);
    CPU->CurrentInstruction = ITLB_Read32(CPU->ProgramCounter);
    uint32_t Opcode = (CPU->CurrentInstruction >> 26);
    Opcodes_R5900[Opcode](CPU);
    CPU->ProgramCounter += SIZEOF_INSTRUCTION;
  }
}





#if 0
R5900_ExceptionLv1(ee_cpu* CPU, int cause, int in_branch_delay)
{
  CPU->Cause ^= cause; // set Level 1 exception cause

  // if already in exception handler (i.e. EXL==1),
  // do not update EPC and Cause.BD.
  // Furthermore, use general vector in this case.
  if(Status.EXL)
  {
    vector = V_COMMON; // use general vector
  }
  else
  {
    // normal Level 1 exception processing
    if(in_branch_delay)
    {
      // Check for branch delay slot
      EPC = PC - 4;
      Cause.BD = 1;
    }
    else
    {
      EPC = PC;
      Cause.BD = 0;
    }
    // Set to kernel mode, and disable interrupts
    Status.EXL = 1;
    // Select vector
    if(cause == TLB_REFILL)
    {
      vector = V_TLB_REFILL;
    }
    else if(cause == INTERRUPT)
    {
      vector = V_INTERRUPT;
    }
    else
    {
      vector = V_COMMON;
    }
  }

  // Select vector base according to Status.BEV bit.
  if(Status.BEV)
  {
    PC = 0xBFC00200 + vector;
  }
  else
  {
    PC = 0x80000000 + vector;
  }
}

#endif