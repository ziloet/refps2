#define MAX_LINE_LENGTH 64
#define MIPS_INSTRUCTION_NOP 0
#define MIPS_FUNCTION(Instruction)        ((Instruction)  & 0x3f)
#define MIPS_SHIFT(Instruction)           (((Instruction) & (0x1f << 6))  >> 6)
#define MIPS_DEST_REGISTER(Instruction)   (((Instruction) & (0x1f << 11)) >> 11)
#define MIPS_TARGET_REGISTER(Instruction) (((Instruction) & (0x1f << 16)) >> 16)
#define MIPS_SOURCE_REGISTER(Instruction) (((Instruction) & (0x1f << 21)) >> 21)
#define MIPS_OPCODE(Instruction)          (((Instruction) & (0x3f << 26)) >> 26)
#define MIPS_IMMEDIATE(Instruction)       ((Instruction)  & 0x0000FFFF)

#define OPCODE_RESERVED    "<Reserved>"
#define OPCODE_UNDEFINED   "<Undefined>"
#define OPCODE_UNSUPPORTED "<Unsupported>"

typedef void disassemble_function(instruction_str*, uint32_t);
typedef void (*instruction_j)(uint32_t);
typedef void (*instruction_i)(uint8_t, uint8_t, uint16_t);
typedef void (*instruction_r)(uint8_t, uint8_t, uint8_t, uint8_t);




typedef struct
{
  uint32_t Offset;
  char[64] Output;
} instruction_str;


static void
StringAppend(char* Dest, char* Src, int DestSize)




enum instruction_format
{
  INSTRUCTION_FORMAT_I,
  INSTRUCTION_FORMAT_J,
  INSTRUCTION_FORMAT_R,
};

typedef struct
{
  instruction_format Format;
  char* Mnemonic;

  uint32_t Arg;
} instruction;




static const char* OpcodesNormal[64] =
{
  NULL,   // Special
  NULL,   // RegImm
  "J",
  "JAL",
  "BEQ",
  "BNE",
  "BLEZ",
  "BGTZ",
  "ADDI",
  "ADDIU",
  "SLTI",
  "SLTIU",
  "ANDI",
  "ORI",
  "XORI",
  "LUI",
  NULL,   // COP0
  NULL,   // COP1
  NULL,   // COP2
  OPCODE_RESERVED,
  "BEQL",
  "BNEL",
  "BLEZL",
  "BGTZL",
  "DADDI",
  "DADDIU",
  "LDL",
  "LDR",
  NULL,   // * MMI
  OPCODE_RESERVED,
  "LQ",   // *
  "SQ",   // *
  "LB",
  "LH",
  "LWL",
  "LW",
  "LBU",
  "LHU",
  "LWR",
  "LWU",
  "SB",
  "SH",
  "SWL",
  "SW",
  "SDL",
  "SDR",
  "SWR",
  "CACHE",
  OPCODE_UNSUPPORTED,
  "LWC1",
  OPCODE_UNSUPPORTED,
  "PREF",
  OPCODE_UNSUPPORTED,
  OPCODE_UNSUPPORTED,
  "LQC2", // **
  "LD",
  OPCODE_UNSUPPORTED,
  "SWC1",
  OPCODE_UNSUPPORTED,
  OPCODE_RESERVED,
  OPCODE_UNSUPPORTED,
  OPCODE_UNSUPPORTED,
  "SQC2", // **
  "SD",
};

static const char* OpcodesSpecial[64] =
{
  "SLL",
  OPCODE_RESERVED,
  "SRL",
  "SRA",
  "SLLV",
  OPCODE_RESERVED,
  "SRLV",
  "SRAV",
  "JR",
  "JALR",
  "MOVZ",
  "MOVN",
  "SYSCALL",
  "BREAK",
  OPCODE_RESERVED,
  "SYNC",
  "MFHI",
  "MTHI",
  "MFLO",
  "MTLO",
  "DSLLV",
  OPCODE_RESERVED,
  "DSRLV",
  "DSRAV",
  "MULT",
  "MULTU",
  "DIV",
  "DIVU",
  OPCODE_UNSUPPORTED,
  OPCODE_UNSUPPORTED,
  OPCODE_UNSUPPORTED,
  OPCODE_UNSUPPORTED,
  "ADD",
  "ADDU",
  "SUB",
  "SUBU",
  "AND",
  "OR",
  "XOR",
  "NOR",
  "MFSA", // *
  "MTSA", // *
  "SLT",
  "SLTU",
  "DADD",
  "DADDU",
  "DSUB",
  "DSUBU",
  "TGE",
  "TGEU",
  "TLT",
  "TLTU",
  "TEQ",
  OPCODE_RESERVED,
  "TNE",
  OPCODE_RESERVED,
  "DSLL",
  OPCODE_RESERVED,
  "DSRL",
  "DSRA",
  "DSLL32",
  OPCODE_RESERVED,
  "DSRL32",
  "DSRA32",
};

static const char* OpcodesRegImm[32] =
{
  "BLTZ",
  "BGEZ",
  "BLTZL",
  "BGEZL",
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  "TGEI",
  "TGEIU",
  "TLTI",
  "TLTIU",
  "TEQI",
  OPCODE_RESERVED,
  "TNEI",
  OPCODE_RESERVED,
  "BLTZAL",
  "BGEZAL",
  "BLTZALL",
  "BGEZALL",
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  "MTSAB", // *
  "MTSAH", // *
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
};

static const char* OpcodesCOP0[32] =
{
  "MF0",
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  "MT0",
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  NULL, // BC0
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  NULL, // C0
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
};  

static const char* OpcodesBC0[32] =
{
  "BC0F",
  "BC0T",
  "BC0FL",
  "BC0TL",
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
};

static const char* OpcodesC0[64] =
{
  OPCODE_UNDEFINED,
  "TLBR",
  "TLBWI",
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  "TLBWR",
  OPCODE_UNDEFINED,
  "TLBP",
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  "ERET",
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  "EI",
  "DI",
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
};

static const char* OpcodesCOP1[32] =
{
  "MFC1",
  OPCODE_RESERVED,
  "CFC1",
  OPCODE_RESERVED,
  "MTC1",
  OPCODE_RESERVED,
  "CTC1",
  OPCODE_RESERVED,
  NULL, // BC1-class
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  NULL, // S-class
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  NULL, // W-class
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
};

static const char* OpcodesBC1[32] =
{
  "BC1F",
  "BC1T",
  "BC1FL",
  "BC1TL",
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
};

static const char* OpcodesS[64] =
{
  "ADD",
  "SUB",
  "MUL",
  "DIV",
  "SQRT",
  "ABS",
  "MOV",
  "NEG",
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  "RSQRT",
  OPCODE_UNDEFINED,
  "ADDA",
  "SUBA",
  "MULA",
  OPCODE_UNDEFINED,
  "MADD",
  "MSUB",
  "MADDA",
  "MSUBA",
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  "CVTW",
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  "MAX",
  "MIN",
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  "C.F",
  OPCODE_UNDEFINED,
  "C.EQ",
  OPCODE_UNDEFINED,
  "C.LT",
  OPCODE_UNDEFINED,
  "C.LE",
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
};

static const char* OpcodesW[64] =
{
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  "CVTS",
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
  OPCODE_UNDEFINED,
};



static const char* OpcodesMMI[64] =
{
  "MADD",
  "MADDU",
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  "PLZCW",
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  NULL, // MMI0
  NULL, // MMI2
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  "MFHI1",
  "MTHI1",
  "MFLO1",
  "MTLO1",
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  "MULT1",
  "MULTU1",
  "DIV1",
  "DIVU1",
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  "MADD1",
  "MADDU1",
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  NULL, // MMI1
  NULL, // MMI3
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  "PMFHL",
  "PMTHL",
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  "PSLLH",
  OPCODE_RESERVED,
  "PSRLH",
  "PSRAH",
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  "PSLLW",
  OPCODE_RESERVED,
  "PSRLW",
  "PSRAW",
};

static const char* OpcodesMMI0[32] =
{
  "PADDW",
  "PSUBW",
  "PCGTW",
  "PMAXW",
  "PADDH",
  "PSUBH",
  "PCGTH",
  "PMAXH",
  "PADDB",
  "PSUBB",
  "PCGTB",
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  "PADDSW",
  "PSUBSW",
  "PEXTLW",
  "PPACW",
  "PADDSH",
  "PSUBSH",
  "PEXTLH",
  "PPACH",
  "PADDSB",
  "PSUBSB",
  "PEXTLB",
  "PPACB",
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  "PEXT5",
  "PPAC5",
};

static const char* OpcodesMMI1[32] =
{
  OPCODE_RESERVED,
  "PABSW",
  "PCEQW",
  "PMINW",
  "PADSBH",
  "PABSH",
  "PCEQH",
  "PMINH",
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  "PCEQB",
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  "PADDUW",
  "PSUBUW",
  "PEXTUW",
  OPCODE_RESERVED,
  "PADDUH",
  "PSUBUH",
  "PEXTUH",
  OPCODE_RESERVED,
  "PADDUB",
  "PSUBUB",
  "PEXTUB",
  "QFSRV",
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
};


static const char* OpcodesMMI2[32] =
{
  "PMADDW",
  OPCODE_RESERVED,
  "PSLLVW",
  "PSRLVW",
  "PMSUBW",
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  "PMFHI",
  "PMFLO",
  "PINTH",
  OPCODE_RESERVED,
  "PMULTW",
  "PDIVW",
  "PCPYLD",
  OPCODE_RESERVED,
  "PMADDH",
  "PHMADH",
  "PAND",
  "PXOR",
  "PMSUBH",
  "PHMSBH",
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  "PEXEH",
  "PREVH",
  "PMULTH",
  "PDIVBW",
  "PEXEW",
  "PROT3W",
};

static const char* OpcodesMMI3[32] =
{
  "PMADDUW",
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  "PSRAVW",
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  "PMTHI",
  "PMTLO",
  "PINTEH",
  OPCODE_RESERVED,
  "PMULTUW",
  "PDIVUW",
  "PCPYUD",
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  "POR",
  "PNOR",
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  "PEXCH",
  "PCPYH",
  OPCODE_RESERVED,
  OPCODE_RESERVED,
  "PEXCW",
  OPCODE_RESERVED,
};


static instruction_j TypeJ[2] =
{
  Decode_J,
  Decode_JAL,
};

static instruction_r TypeR[] =
{
  Decode_ADD,
  Decode_ADDU,
  Decode_AND,
  Decode_DADD,
  Decode_DADDU,
  Decode_DIV,
  Decode_DIVU,
  Decode_DSLL,
  Decode_DSLL32,
  Decode_DSLLV,
  Decode_DSRA,
  Decode_DSRA32,
  Decode_DSRAV,
  Decode_DSRL32,
  Decode_DSRLV,
  Decode_DSUB,
  Decode_DSUBU,
  Decode_JALR,
  Decode_JR,
  Decode_MFHI,
  Decode_MFLO,
  Decode_MOVN,
  Decode_MOVZ,
  Decode_MTHI,
  Decode_MTLO,
  Decode_MULT,
  Decode_MULTU,
  Decode_NOR,
  Decode_OR,
  Decode_SLL,
  Decode_SLLV,
  Decode_SLT,
  Decode_SLTU,
  Decode_SRA,
  Decode_SRAV,
  Decode_SRL,
  Decode_SRLV,
  Decode_SUB,
  Decode_SUBU,
  Decode_SYNC,
  Decode_TEQ,
  Decode_TGE,
  Decode_TGEU,
  Decode_TLT,
  Decode_TLTU,
  Decode_TNE,
  Decode_XOR,
  Decode_XORI,
};


static instruction_i TypeI[] =
{
  Decode_ADDI,
  Decode_ADDIU,
  Decode_ANDI,
  Decode_BEQ,
  Decode_BEQL,
  Decode_BGEZ,
  Decode_BGEZAL,
  Decode_BGEZALL,
  Decode_BGEZL,
  Decode_BGTZ,
  Decode_BGTZL,
  Decode_BLEZ,
  Decode_BLEZL,
  Decode_BLTZ,
  Decode_BLTZAL,
  Decode_BLTZALL,
  Decode_BLTZL,
  Decode_BNE,
  Decode_BNEL,
  Decode_DADDI,
  Decode_DADDIU,
  Decode_LB,
  Decode_LBU,
  Decode_LD,
  Decode_LDL,
  Decode_LDR,
  Decode_LH,
  Decode_LHU,
  Decode_LUI,
  Decode_LW,
  Decode_LWL,
  Decode_LWR,
  Decode_LWU,
  Decode_ORI,
  Decode_PREF,
  Decode_SB,
  Decode_SDL,
  Decode_SDR,
  
  
  Decode_SLTI,
  Decode_SLTIU,
  
  
  Decode_SW,
  Decode_SWL,
  Decode_SWR,
  Decode_TEQI,
  Decode_TGEI,
  Decode_TGEIU,
  Decode_TLTI,
  Decode_TLTIU,
  Decode_TNEI,
  
  

};

static void
DecodeInstruction(uint32_t Instruction, char* Buffer, uint32_t BufferSize)
{
  uint32_t Opcode = Instruction >> 26;
  switch(Opcode)
  {
    case 0x0:
    {
      uint32_t Function = Instruction & 0x3f;
      switch(Function)
      {
        case 0xc:
        {
          "SYSCALL";
        } break;
        case 0xd:
        {
          "BREAK";
        } break;
        case 0x34:
        {
          "BREAK";
        } break;
      }
    } break;
    case 0x1:
    {

    } break;
    case 0x2:
    case 0x3:
    {
      uint32_t Offset = Instruction & (0x3f << 26);

    } break;


    default:
    {
      
    } break;



  }
  //OpcodesNormal[_OPCODE_];
}

static void
AppendInstructionName(char* Buffer, uint32_t Instruction)
{
  uint32_t Opcode = Instruction >> 26;
  switch(Opcode)
  {
    case 0:
    {
      uint32_t Function = Instruction & 0x7f;
      switch(Function)
      {

      }
    } break;
    case 1:
    {

    } break;


    case 19:
    case 29:
    {
    } break;

    default:
    {
      StringAppend(Buffer, "<illegal>");
    } break;
  }
}


static void
DisassembleInstruction(uint32_t* Start, uint32_t MaxRead)
{
  for(uint32_t Index = 0; Index < MaxRead; Index += 1)
  {
    char StringBuffer[64] = {0};
    uint32_t Instruction = Start[Index];
    AppendInstructionName(StringBuffer, Instruction);
    AppendInstructionArguments(StringBuffer);
  }
}


#if 0

static void decode_j(char *outbuf, size_t n, uint32_t pc, uint32_t op)
{
    snprintf(outbuf,n,"j 0x%x",gettarget(pc,op));
}

static void decode_jal(char *outbuf, size_t n, uint32_t pc, uint32_t op)
{
    snprintf(outbuf,n,"jal 0x%x",gettarget(pc,op));
}

static void decode_beq(char *outbuf, size_t n, uint32_t pc, uint32_t op)
{
    snprintf(outbuf,n,"beq $%d,$%d,0x%x",getrs(op),getrt(op),getbroff(pc,op));
}

static void decode_bne(char *outbuf, size_t n, uint32_t pc, uint32_t op)
{
    snprintf(outbuf,n,"bne $%d,$%d,0x%x",getrs(op),getrt(op),getbroff(pc,op));
}

static void decode_blez(char *outbuf, size_t n, uint32_t pc, uint32_t op)
{
    if (!(check_opcode(op, 0xfc1f0000, 0x18000000)))
    {
        decode_illegal(outbuf, n, pc, op);
        return;
    }

    snprintf(outbuf,n,"blez $%d,0x%x",getrs(op),getbroff(pc,op));
}

static void decode_bgtz(char *outbuf, size_t n, uint32_t pc, uint32_t op)
{
    if (!(check_opcode(op, 0xfc1f0000, 0x1c000000)))
    {
        decode_illegal(outbuf, n, pc, op);
        return;
    }

    snprintf(outbuf,n,"bgtz $%d,0x%x",getrs(op),getbroff(pc,op));
}

static void decode_addi(char *outbuf, size_t n, uint32_t pc, uint32_t op)
{
    snprintf(outbuf,n,"addi $%d,$%d,%d",getrt(op),getrs(op),getsimm(op));
}

static void decode_addiu(char *outbuf, size_t n, uint32_t pc, uint32_t op)
{
    snprintf(outbuf,n,"addiu $%d,$%d,%d",getrt(op),getrs(op),getsimm(op));
}

static void decode_slti(char *outbuf, size_t n, uint32_t pc, uint32_t op)
{
    snprintf(outbuf,n,"slti $%d,$%d,%d",getrt(op),getrs(op),getsimm(op));
}

static void decode_sltiu(char *outbuf, size_t n, uint32_t pc, uint32_t op)
{
    snprintf(outbuf,n,"sltiu $%d,$%d,%d",getrt(op),getrs(op),getsimm(op));
}

static void decode_andi(char *outbuf, size_t n, uint32_t pc, uint32_t op)
{
    snprintf(outbuf,n,"andi $%d,$%d,0x%x",getrt(op),getrs(op),getimm(op));
}

static void decode_ori(char *outbuf, size_t n, uint32_t pc, uint32_t op)
{
    snprintf(outbuf,n,"ori $%d,$%d,0x%x",getrt(op),getrs(op),getimm(op));
}

static void decode_xori(char *outbuf, size_t n, uint32_t pc, uint32_t op)
{
    snprintf(outbuf,n,"xori $%d,$%d,0x%x",getrt(op),getrs(op),getimm(op));
}

static void decode_lui(char *outbuf, size_t n, uint32_t pc, uint32_t op)
{
    if (!(check_opcode(op, 0xffe00000, 0x3c000000)))
    {
        decode_illegal(outbuf, n, pc, op);
        return;
    }

    snprintf(outbuf,n,"lui $%d,0x%x",getrt(op),getimm(op));
}

static void decode_beql(char *outbuf, size_t n, uint32_t pc, uint32_t op)
{
    snprintf(outbuf,n,"beql $%d,$%d,0x%x",getrs(op),getrt(op),getbroff(pc,op));
}

static void decode_bnel(char *outbuf, size_t n, uint32_t pc, uint32_t op)
{
    snprintf(outbuf,n,"bnel $%d,$%d,0x%x",getrs(op),getrt(op),getbroff(pc,op));
}

static void decode_blezl(char *outbuf, size_t n, uint32_t pc, uint32_t op)
{
    if (!(check_opcode(op, 0xfc1f0000, 0x58000000)))
    {
        decode_illegal(outbuf, n, pc, op);
        return;
    }

    snprintf(outbuf,n,"blezl $%d,0x%x",getrs(op),getbroff(pc,op));
}

static void decode_bgtzl(char *outbuf, size_t n, uint32_t pc, uint32_t op)
{
    if (!(check_opcode(op, 0xfc1f0000, 0x5c000000)))
    {
        decode_illegal(outbuf, n, pc, op);
        return;
    }

    snprintf(outbuf,n,"bgtzl $%d,0x%x",getrs(op),getbroff(pc,op));
}

static void decode_lb(char *outbuf, size_t n, uint32_t pc, uint32_t op)
{
    snprintf(outbuf,n,"lb $%d,%d($%d)",getrt(op),getoffset(op),getbase(op));
}

static void decode_lh(char *outbuf, size_t n, uint32_t pc, uint32_t op)
{
    snprintf(outbuf,n,"lh $%d,%d($%d)",getrt(op),getoffset(op),getbase(op));
}

static void decode_lwl(char *outbuf, size_t n, uint32_t pc, uint32_t op)
{
    snprintf(outbuf,n,"lwl $%d,%d($%d)",getrt(op),getoffset(op),getbase(op));
}

static void decode_lw(char *outbuf, size_t n, uint32_t pc, uint32_t op)
{
    snprintf(outbuf,n,"lw $%d,%d($%d)",getrt(op),getoffset(op),getbase(op));
}

static void decode_lbu(char *outbuf, size_t n, uint32_t pc, uint32_t op)
{
    snprintf(outbuf,n,"lbu $%d,%d($%d)",getrt(op),getoffset(op),getbase(op));
}

static void decode_lhu(char *outbuf, size_t n, uint32_t pc, uint32_t op)
{
    snprintf(outbuf,n,"lhu $%d,%d($%d)",getrt(op),getoffset(op),getbase(op));
}

static void decode_lwr(char *outbuf, size_t n, uint32_t pc, uint32_t op)
{
    snprintf(outbuf,n,"lwr $%d,%d($%d)",getrt(op),getoffset(op),getbase(op));
}

static void decode_sb(char *outbuf, size_t n, uint32_t pc, uint32_t op)
{
    snprintf(outbuf,n,"sb $%d,%d($%d)",getrt(op),getoffset(op),getbase(op));
}

static void decode_sh(char *outbuf, size_t n, uint32_t pc, uint32_t op)
{
    snprintf(outbuf,n,"sh $%d,%d($%d)",getrt(op),getoffset(op),getbase(op));
}

static void decode_swl(char *outbuf, size_t n, uint32_t pc, uint32_t op)
{
    snprintf(outbuf,n,"swl $%d,%d($%d)",getrt(op),getoffset(op),getbase(op));
}

static void decode_sw(char *outbuf, size_t n, uint32_t pc, uint32_t op)
{
    snprintf(outbuf,n,"sw $%d,%d($%d)",getrt(op),getoffset(op),getbase(op));
}

static void decode_swr(char *outbuf, size_t n, uint32_t pc, uint32_t op)
{
    snprintf(outbuf,n,"swr $%d,%d($%d)",getrt(op),getoffset(op),getbase(op));
}

static void decode_cache(char *outbuf, size_t n, uint32_t pc, uint32_t op)
{
    snprintf(outbuf,n,"cache 0x%x,%d($%d)",getcacheop(op),getoffset(op),getbase(op));
}

static void decode_ll(char *outbuf, size_t n, uint32_t pc, uint32_t op)
{
    snprintf(outbuf,n,"ll $%d,%d($%d)",getrt(op),getoffset(op),getbase(op));
}

static void decode_pref(char *outbuf, size_t n, uint32_t pc, uint32_t op)
{
    snprintf(outbuf,n,"pref 0x%x,%d($%d)",getprefhint(op),getoffset(op),getbase(op));
}

static void decode_sc(char *outbuf, size_t n, uint32_t pc, uint32_t op)
{
    snprintf(outbuf,n,"sc $%d,%d($%d)",getrt(op),getoffset(op),getbase(op));
}

static void decode_sll(char *outbuf, size_t n, uint32_t pc, uint32_t op)
{
    if (!(check_opcode(op, 0xffe0003f, 0x00000000)))
    {
        decode_illegal(outbuf, n, pc, op);
        return;
    }

    snprintf(outbuf,n,"sll $%d,$%d,0x%x",getrd(op),getrt(op),getsa(op));
}

static void decode_srl(char *outbuf, size_t n, uint32_t pc, uint32_t op)
{
    if (!(check_opcode(op, 0xffe0003f, 0x00000002)))
    {
        decode_illegal(outbuf, n, pc, op);
        return;
    }

    snprintf(outbuf,n,"srl $%d,$%d,0x%x",getrd(op),getrt(op),getsa(op));
}

static void decode_sra(char *outbuf, size_t n, uint32_t pc, uint32_t op)
{
    if (!(check_opcode(op, 0xffe0003f, 0x00000003)))
    {
        decode_illegal(outbuf, n, pc, op);
        return;
    }

    snprintf(outbuf,n,"sra $%d,$%d,0x%x",getrd(op),getrt(op),getsa(op));
}

static void decode_sllv(char *outbuf, size_t n, uint32_t pc, uint32_t op)
{
    if (!(check_opcode(op, 0xfc0007ff, 0x00000004)))
    {
        decode_illegal(outbuf, n, pc, op);
        return;
    }

    snprintf(outbuf,n,"sllv $%d,$%d,$%d",getrd(op),getrt(op),getrs(op));
}

static void decode_srlv(char *outbuf, size_t n, uint32_t pc, uint32_t op)
{
    if (!(check_opcode(op, 0xfc0007ff, 0x00000006)))
    {
        decode_illegal(outbuf, n, pc, op);
        return;
    }

    snprintf(outbuf,n,"srlv $%d,$%d,$%d",getrd(op),getrt(op),getrs(op));
}

static void decode_srav(char *outbuf, size_t n, uint32_t pc, uint32_t op)
{
    if (!(check_opcode(op, 0xfc0007ff, 0x00000007)))
    {
        decode_illegal(outbuf, n, pc, op);
        return;
    }

    snprintf(outbuf,n,"srav $%d,$%d,$%d",getrd(op),getrt(op),getrs(op));
}

static void decode_jr(char *outbuf, size_t n, uint32_t pc, uint32_t op)
{
    if (!(check_opcode(op, 0xfc1fffff, 0x00000008)))
    {
        decode_illegal(outbuf, n, pc, op);
        return;
    }

    snprintf(outbuf,n,"jr $%d",getrs(op));
}

static void decode_jalr(char *outbuf, size_t n, uint32_t pc, uint32_t op)
{
    if (!(check_opcode(op, 0xfc1f07ff, 0x00000009)&&check_jalr(getrs(op), getrd(op))))
    {
        decode_illegal(outbuf, n, pc, op);
        return;
    }

    snprintf(outbuf,n,"jalr $%d,$%d",getrd(op),getrs(op));
}

static void decode_movz(char *outbuf, size_t n, uint32_t pc, uint32_t op)
{
    if (!(check_opcode(op, 0xfc0007ff, 0x0000000a)))
    {
        decode_illegal(outbuf, n, pc, op);
        return;
    }

    snprintf(outbuf,n,"movz $%d,$%d,$%d",getrd(op),getrs(op),getrt(op));
}

static void decode_movn(char *outbuf, size_t n, uint32_t pc, uint32_t op)
{
    if (!(check_opcode(op, 0xfc0007ff, 0x0000000b)))
    {
        decode_illegal(outbuf, n, pc, op);
        return;
    }

    snprintf(outbuf,n,"movn $%d,$%d,$%d",getrd(op),getrs(op),getrt(op));
}

static void decode_syscall(char *outbuf, size_t n, uint32_t pc, uint32_t op)
{
    snprintf(outbuf,n,"syscall 0x%x",getsyscode(op));
}

static void decode_break(char *outbuf, size_t n, uint32_t pc, uint32_t op)
{
    snprintf(outbuf,n,"break 0x%x,0x%x",getbc1(op),getbc2(op));
}

static void decode_sync(char *outbuf, size_t n, uint32_t pc, uint32_t op)
{
    if (!(check_opcode(op, 0xfffff83f, 0x0000000f)))
    {
        decode_illegal(outbuf, n, pc, op);
        return;
    }

    snprintf(outbuf,n,"sync 0x%x",getstype(op));
}

static void decode_mfhi(char *outbuf, size_t n, uint32_t pc, uint32_t op)
{
    if (!(check_opcode(op, 0xffff07ff, 0x00000010)))
    {
        decode_illegal(outbuf, n, pc, op);
        return;
    }

    snprintf(outbuf,n,"mfhi $%d",getrd(op));
}

static void decode_mthi(char *outbuf, size_t n, uint32_t pc, uint32_t op)
{
    if (!(check_opcode(op, 0xfc1fffff, 0x00000011)))
    {
        decode_illegal(outbuf, n, pc, op);
        return;
    }

    snprintf(outbuf,n,"mthi $%d",getrs(op));
}

static void decode_mflo(char *outbuf, size_t n, uint32_t pc, uint32_t op)
{
    if (!(check_opcode(op, 0xffff07ff, 0x00000012)))
    {
        decode_illegal(outbuf, n, pc, op);
        return;
    }

    snprintf(outbuf,n,"mflo $%d",getrd(op));
}

static void decode_mtlo(char *outbuf, size_t n, uint32_t pc, uint32_t op)
{
    if (!(check_opcode(op, 0xfc1fffff, 0x00000013)))
    {
        decode_illegal(outbuf, n, pc, op);
        return;
    }

    snprintf(outbuf,n,"mtlo $%d",getrs(op));
}

static void decode_mult(char *outbuf, size_t n, uint32_t pc, uint32_t op)
{
    if (!(check_opcode(op, 0xfc00ffff, 0x00000018)))
    {
        decode_illegal(outbuf, n, pc, op);
        return;
    }

    snprintf(outbuf,n,"mult $%d,$%d",getrs(op),getrt(op));
}

static void decode_multu(char *outbuf, size_t n, uint32_t pc, uint32_t op)
{
    if (!(check_opcode(op, 0xfc00ffff, 0x00000019)))
    {
        decode_illegal(outbuf, n, pc, op);
        return;
    }

    snprintf(outbuf,n,"multu $%d,$%d",getrs(op),getrt(op));
}

static void decode_div(char *outbuf, size_t n, uint32_t pc, uint32_t op)
{
    if (!(check_opcode(op, 0xfc00ffff, 0x0000001a)))
    {
        decode_illegal(outbuf, n, pc, op);
        return;
    }

    snprintf(outbuf,n,"div $%d,$%d",getrs(op),getrt(op));
}

static void decode_divu(char *outbuf, size_t n, uint32_t pc, uint32_t op)
{
    if (!(check_opcode(op, 0xfc00ffff, 0x0000001b)))
    {
        decode_illegal(outbuf, n, pc, op);
        return;
    }

    snprintf(outbuf,n,"divu $%d,$%d",getrs(op),getrt(op));
}

static void decode_add(char *outbuf, size_t n, uint32_t pc, uint32_t op)
{
    if (!(check_opcode(op, 0xfc0007ff, 0x00000020)))
    {
        decode_illegal(outbuf, n, pc, op);
        return;
    }

    snprintf(outbuf,n,"add $%d,$%d,$%d",getrd(op),getrs(op),getrt(op));
}

static void decode_addu(char *outbuf, size_t n, uint32_t pc, uint32_t op)
{
    if (!(check_opcode(op, 0xfc0007ff, 0x00000021)))
    {
        decode_illegal(outbuf, n, pc, op);
        return;
    }

    snprintf(outbuf,n,"addu $%d,$%d,$%d",getrd(op),getrs(op),getrt(op));
}

static void decode_sub(char *outbuf, size_t n, uint32_t pc, uint32_t op)
{
    if (!(check_opcode(op, 0xfc0007ff, 0x00000022)))
    {
        decode_illegal(outbuf, n, pc, op);
        return;
    }

    snprintf(outbuf,n,"sub $%d,$%d,$%d",getrd(op),getrs(op),getrt(op));
}

static void decode_subu(char *outbuf, size_t n, uint32_t pc, uint32_t op)
{
    if (!(check_opcode(op, 0xfc0007ff, 0x00000023)))
    {
        decode_illegal(outbuf, n, pc, op);
        return;
    }

    snprintf(outbuf,n,"subu $%d,$%d,$%d",getrd(op),getrs(op),getrt(op));
}

static void decode_and(char *outbuf, size_t n, uint32_t pc, uint32_t op)
{
    if (!(check_opcode(op, 0xfc0007ff, 0x00000024)))
    {
        decode_illegal(outbuf, n, pc, op);
        return;
    }

    snprintf(outbuf,n,"and $%d,$%d,$%d",getrd(op),getrs(op),getrt(op));
}

static void decode_or(char *outbuf, size_t n, uint32_t pc, uint32_t op)
{
    if (!(check_opcode(op, 0xfc0007ff, 0x00000025)))
    {
        decode_illegal(outbuf, n, pc, op);
        return;
    }

    snprintf(outbuf,n,"or $%d,$%d,$%d",getrd(op),getrs(op),getrt(op));
}

static void decode_xor(char *outbuf, size_t n, uint32_t pc, uint32_t op)
{
    if (!(check_opcode(op, 0xfc0007ff, 0x00000026)))
    {
        decode_illegal(outbuf, n, pc, op);
        return;
    }

    snprintf(outbuf,n,"xor $%d,$%d,$%d",getrd(op),getrs(op),getrt(op));
}

static void decode_nor(char *outbuf, size_t n, uint32_t pc, uint32_t op)
{
    if (!(check_opcode(op, 0xfc0007ff, 0x00000027)))
    {
        decode_illegal(outbuf, n, pc, op);
        return;
    }

    snprintf(outbuf,n,"nor $%d,$%d,$%d",getrd(op),getrs(op),getrt(op));
}

static void decode_slt(char *outbuf, size_t n, uint32_t pc, uint32_t op)
{
    if (!(check_opcode(op, 0xfc0007ff, 0x0000002a)))
    {
        decode_illegal(outbuf, n, pc, op);
        return;
    }

    snprintf(outbuf,n,"slt $%d,$%d,$%d",getrd(op),getrs(op),getrt(op));
}

static void decode_sltu(char *outbuf, size_t n, uint32_t pc, uint32_t op)
{
    if (!(check_opcode(op, 0xfc0007ff, 0x0000002b)))
    {
        decode_illegal(outbuf, n, pc, op);
        return;
    }

    snprintf(outbuf,n,"sltu $%d,$%d,$%d",getrd(op),getrs(op),getrt(op));
}

static void decode_tge(char *outbuf, size_t n, uint32_t pc, uint32_t op)
{
    snprintf(outbuf,n,"tge $%d,$%d,0x%x",getrs(op),getrt(op),gettrapcode(op));
}

static void decode_tgeu(char *outbuf, size_t n, uint32_t pc, uint32_t op)
{
    snprintf(outbuf,n,"tgeu $%d,$%d,0x%x",getrs(op),getrt(op),gettrapcode(op));
}

static void decode_tlt(char *outbuf, size_t n, uint32_t pc, uint32_t op)
{
    snprintf(outbuf,n,"tlt $%d,$%d,0x%x",getrs(op),getrt(op),gettrapcode(op));
}

static void decode_tltu(char *outbuf, size_t n, uint32_t pc, uint32_t op)
{
    snprintf(outbuf,n,"tltu $%d,$%d,0x%x",getrs(op),getrt(op),gettrapcode(op));
}

static void decode_teq(char *outbuf, size_t n, uint32_t pc, uint32_t op)
{
    snprintf(outbuf,n,"teq $%d,$%d,0x%x",getrs(op),getrt(op),gettrapcode(op));
}

static void decode_tne(char *outbuf, size_t n, uint32_t pc, uint32_t op)
{
    snprintf(outbuf,n,"tne $%d,$%d,0x%x",getrs(op),getrt(op),gettrapcode(op));
}

static void decode_madd(char *outbuf, size_t n, uint32_t pc, uint32_t op)
{
    if (!(check_opcode(op, 0xfc00ffff, 0x70000000)))
    {
        decode_illegal(outbuf, n, pc, op);
        return;
    }

    snprintf(outbuf,n,"madd $%d,$%d",getrs(op),getrt(op));
}

static void decode_maddu(char *outbuf, size_t n, uint32_t pc, uint32_t op)
{
    if (!(check_opcode(op, 0xfc00ffff, 0x70000001)))
    {
        decode_illegal(outbuf, n, pc, op);
        return;
    }

    snprintf(outbuf,n,"maddu $%d,$%d",getrs(op),getrt(op));
}

static void decode_mul(char *outbuf, size_t n, uint32_t pc, uint32_t op)
{
    if (!(check_opcode(op, 0xfc0007ff, 0x70000002)))
    {
        decode_illegal(outbuf, n, pc, op);
        return;
    }

    snprintf(outbuf,n,"mul $%d,$%d,$%d",getrd(op),getrs(op),getrt(op));
}

static void decode_msub(char *outbuf, size_t n, uint32_t pc, uint32_t op)
{
    if (!(check_opcode(op, 0xfc00ffff, 0x70000004)))
    {
        decode_illegal(outbuf, n, pc, op);
        return;
    }

    snprintf(outbuf,n,"msub $%d,$%d",getrs(op),getrt(op));
}

static void decode_msubu(char *outbuf, size_t n, uint32_t pc, uint32_t op)
{
    if (!(check_opcode(op, 0xfc00ffff, 0x70000005)))
    {
        decode_illegal(outbuf, n, pc, op);
        return;
    }

    snprintf(outbuf,n,"msubu $%d,$%d",getrs(op),getrt(op));
}

static void decode_clz(char *outbuf, size_t n, uint32_t pc, uint32_t op)
{
    if (!(check_opcode(op, 0xfc0007ff, 0x70000020)&&check_cl(getrt(op), getrd(op))))
    {
        decode_illegal(outbuf, n, pc, op);
        return;
    }

    snprintf(outbuf,n,"clz $%d,$%d",getrd(op),getrs(op));
}

static void decode_clo(char *outbuf, size_t n, uint32_t pc, uint32_t op)
{
    if (!(check_opcode(op, 0xfc0007ff, 0x70000021)&&check_cl(getrt(op), getrd(op))))
    {
        decode_illegal(outbuf, n, pc, op);
        return;
    }

    snprintf(outbuf,n,"clo $%d,$%d",getrd(op),getrs(op));
}

static void decode_sdbbp(char *outbuf, size_t n, uint32_t pc, uint32_t op)
{
    snprintf(outbuf,n,"sdbbp 0x%x",getsyscode(op));
}

static void decode_bltz(char *outbuf, size_t n, uint32_t pc, uint32_t op)
{
    snprintf(outbuf,n,"bltz $%d,0x%x",getrs(op),getbroff(pc,op));
}

static void decode_bgez(char *outbuf, size_t n, uint32_t pc, uint32_t op)
{
    snprintf(outbuf,n,"bgez $%d,0x%x",getrs(op),getbroff(pc,op));
}

static void decode_bltzl(char *outbuf, size_t n, uint32_t pc, uint32_t op)
{
    snprintf(outbuf,n,"bltzl $%d,0x%x",getrs(op),getbroff(pc,op));
}

static void decode_bgezl(char *outbuf, size_t n, uint32_t pc, uint32_t op)
{
    snprintf(outbuf,n,"bgezl $%d,0x%x",getrs(op),getbroff(pc,op));
}

static void decode_tgei(char *outbuf, size_t n, uint32_t pc, uint32_t op)
{
    snprintf(outbuf,n,"tgei $%d,%d",getrs(op),getsimm(op));
}

static void decode_tgeiu(char *outbuf, size_t n, uint32_t pc, uint32_t op)
{
    snprintf(outbuf,n,"tgeiu $%d,%d",getrs(op),getsimm(op));
}

static void decode_tlti(char *outbuf, size_t n, uint32_t pc, uint32_t op)
{
    snprintf(outbuf,n,"tlti $%d,%d",getrs(op),getsimm(op));
}

static void decode_tltiu(char *outbuf, size_t n, uint32_t pc, uint32_t op)
{
    snprintf(outbuf,n,"tltiu $%d,%d",getrs(op),getsimm(op));
}

static void decode_teqi(char *outbuf, size_t n, uint32_t pc, uint32_t op)
{
    snprintf(outbuf,n,"teqi $%d,%d",getrs(op),getsimm(op));
}

static void decode_tnei(char *outbuf, size_t n, uint32_t pc, uint32_t op)
{
    snprintf(outbuf,n,"tnei $%d,%d",getrs(op),getsimm(op));
}

static void decode_bltzal(char *outbuf, size_t n, uint32_t pc, uint32_t op)
{
    snprintf(outbuf,n,"bltzal $%d,0x%x",getrs(op),getbroff(pc,op));
}

static void decode_bgezal(char *outbuf, size_t n, uint32_t pc, uint32_t op)
{
    snprintf(outbuf,n,"bgezal $%d,0x%x",getrs(op),getbroff(pc,op));
}

static void decode_bltzall(char *outbuf, size_t n, uint32_t pc, uint32_t op)
{
    snprintf(outbuf,n,"bltzall $%d,0x%x",getrs(op),getbroff(pc,op));
}

static void decode_bgezall(char *outbuf, size_t n, uint32_t pc, uint32_t op)
{
    snprintf(outbuf,n,"bgezall $%d,0x%x",getrs(op),getbroff(pc,op));
}

static void decode_mfc0(char *outbuf, size_t n, uint32_t pc, uint32_t op)
{
    if (!(check_opcode(op, 0xffe007f8, 0x40000000)))
    {
        decode_illegal(outbuf, n, pc, op);
        return;
    }

    snprintf(outbuf,n,"mfc0 $%d,$%d,%d",getrt(op),getrd(op),getsel(op));
}

static void decode_mtc0(char *outbuf, size_t n, uint32_t pc, uint32_t op)
{
    if (!(check_opcode(op, 0xffe007f8, 0x40800000)))
    {
        decode_illegal(outbuf, n, pc, op);
        return;
    }

    snprintf(outbuf,n,"mtc0 $%d,$%d,%d",getrt(op),getrd(op),getsel(op));
}

static void decode_tlbr(char *outbuf, size_t n, uint32_t pc, uint32_t op)
{
    if (!(check_opcode(op, 0xffffffff, 0x42000001)))
    {
        decode_illegal(outbuf, n, pc, op);
        return;
    }

    snprintf(outbuf,n,"tlbr");
}

static void decode_tlbwi(char *outbuf, size_t n, uint32_t pc, uint32_t op)
{
    if (!(check_opcode(op, 0xffffffff, 0x42000002)))
    {
        decode_illegal(outbuf, n, pc, op);
        return;
    }

    snprintf(outbuf,n,"tlbwi");
}

static void decode_tlbwr(char *outbuf, size_t n, uint32_t pc, uint32_t op)
{
    if (!(check_opcode(op, 0xffffffff, 0x42000006)))
    {
        decode_illegal(outbuf, n, pc, op);
        return;
    }

    snprintf(outbuf,n,"tlbwr");
}

static void decode_tlbp(char *outbuf, size_t n, uint32_t pc, uint32_t op)
{
    if (!(check_opcode(op, 0xffffffff, 0x42000008)))
    {
        decode_illegal(outbuf, n, pc, op);
        return;
    }

    snprintf(outbuf,n,"tlbp");
}

static void decode_eret(char *outbuf, size_t n, uint32_t pc, uint32_t op)
{
    if (!(check_opcode(op, 0xffffffff, 0x42000018)))
    {
        decode_illegal(outbuf, n, pc, op);
        return;
    }

    snprintf(outbuf,n,"eret");
}

static void decode_deret(char *outbuf, size_t n, uint32_t pc, uint32_t op)
{
    if (!(check_opcode(op, 0xffffffff, 0x4200001f)))
    {
        decode_illegal(outbuf, n, pc, op);
        return;
    }

    snprintf(outbuf,n,"deret");
}

static void decode_wait(char *outbuf, size_t n, uint32_t pc, uint32_t op)
{
    snprintf(outbuf,n,"wait 0x%x",getwaitcode(op));
}

static void decode_OPCODE(char *outbuf, size_t n, uint32_t pc, uint32_t op);
static void decode_SPC1(char *outbuf, size_t n, uint32_t pc, uint32_t op);
static void decode_SPC2(char *outbuf, size_t n, uint32_t pc, uint32_t op);
static void decode_R(char *outbuf, size_t n, uint32_t pc, uint32_t op);
static void decode_COP0(char *outbuf, size_t n, uint32_t pc, uint32_t op);
static void decode_CO(char *outbuf, size_t n, uint32_t pc, uint32_t op);
static void decode_OPCODE(char *outbuf, size_t n, uint32_t pc, uint32_t op)
{
    switch (getopcode(op))
    {
        case 0:
            decode_SPC1(outbuf, n, pc, op);
            break;
        case 1:
            decode_R(outbuf, n, pc, op);
            break;
        case 2:
            decode_j(outbuf, n, pc, op);
            break;
        case 3:
            decode_jal(outbuf, n, pc, op);
            break;
        case 4:
            decode_beq(outbuf, n, pc, op);
            break;
        case 5:
            decode_bne(outbuf, n, pc, op);
            break;
        case 6:
            decode_blez(outbuf, n, pc, op);
            break;
        case 7:
            decode_bgtz(outbuf, n, pc, op);
            break;
        case 8:
            decode_addi(outbuf, n, pc, op);
            break;
        case 9:
            decode_addiu(outbuf, n, pc, op);
            break;
        case 10:
            decode_slti(outbuf, n, pc, op);
            break;
        case 11:
            decode_sltiu(outbuf, n, pc, op);
            break;
        case 12:
            decode_andi(outbuf, n, pc, op);
            break;
        case 13:
            decode_ori(outbuf, n, pc, op);
            break;
        case 14:
            decode_xori(outbuf, n, pc, op);
            break;
        case 15:
            decode_lui(outbuf, n, pc, op);
            break;
        case 16:
            decode_COP0(outbuf, n, pc, op);
            break;
        case 17:
        case 18:
        case 19:
        case 49:
        case 50:
        case 53:
        case 54:
        case 57:
        case 58:
        case 61:
        case 62:
            decode_unusable(outbuf, n, pc, op);
            break;
        case 20:
            decode_beql(outbuf, n, pc, op);
            break;
        case 21:
            decode_bnel(outbuf, n, pc, op);
            break;
        case 22:
            decode_blezl(outbuf, n, pc, op);
            break;
        case 23:
            decode_bgtzl(outbuf, n, pc, op);
            break;
        case 24:
        case 25:
        case 26:
        case 27:
        case 29:
        case 30:
        case 31:
        case 39:
        case 44:
        case 45:
        case 52:
        case 55:
        case 59:
        case 60:
        case 63:
            decode_reserved(outbuf, n, pc, op);
            break;
        case 28:
            decode_SPC2(outbuf, n, pc, op);
            break;
        case 32:
            decode_lb(outbuf, n, pc, op);
            break;
        case 33:
            decode_lh(outbuf, n, pc, op);
            break;
        case 34:
            decode_lwl(outbuf, n, pc, op);
            break;
        case 35:
            decode_lw(outbuf, n, pc, op);
            break;
        case 36:
            decode_lbu(outbuf, n, pc, op);
            break;
        case 37:
            decode_lhu(outbuf, n, pc, op);
            break;
        case 38:
            decode_lwr(outbuf, n, pc, op);
            break;
        case 40:
            decode_sb(outbuf, n, pc, op);
            break;
        case 41:
            decode_sh(outbuf, n, pc, op);
            break;
        case 42:
            decode_swl(outbuf, n, pc, op);
            break;
        case 43:
            decode_sw(outbuf, n, pc, op);
            break;
        case 46:
            decode_swr(outbuf, n, pc, op);
            break;
        case 47:
            decode_cache(outbuf, n, pc, op);
            break;
        case 48:
            decode_ll(outbuf, n, pc, op);
            break;
        case 51:
            decode_pref(outbuf, n, pc, op);
            break;
        case 56:
            decode_sc(outbuf, n, pc, op);
            break;
        default:
            /* unreachable */
            abort();
    }
}

static void decode_SPC1(char *outbuf, size_t n, uint32_t pc, uint32_t op)
{
    switch (getfunction(op))
    {
        case 0:
            decode_sll(outbuf, n, pc, op);
            break;
        case 1:
            decode_unusable(outbuf, n, pc, op);
            break;
        case 2:
            decode_srl(outbuf, n, pc, op);
            break;
        case 3:
            decode_sra(outbuf, n, pc, op);
            break;
        case 4:
            decode_sllv(outbuf, n, pc, op);
            break;
        case 5:
        case 14:
        case 20:
        case 21:
        case 22:
        case 23:
        case 28:
        case 29:
        case 30:
        case 31:
        case 40:
        case 41:
        case 44:
        case 45:
        case 46:
        case 47:
        case 53:
        case 55:
        case 56:
        case 57:
        case 58:
        case 59:
        case 60:
        case 61:
        case 62:
        case 63:
            decode_reserved(outbuf, n, pc, op);
            break;
        case 6:
            decode_srlv(outbuf, n, pc, op);
            break;
        case 7:
            decode_srav(outbuf, n, pc, op);
            break;
        case 8:
            decode_jr(outbuf, n, pc, op);
            break;
        case 9:
            decode_jalr(outbuf, n, pc, op);
            break;
        case 10:
            decode_movz(outbuf, n, pc, op);
            break;
        case 11:
            decode_movn(outbuf, n, pc, op);
            break;
        case 12:
            decode_syscall(outbuf, n, pc, op);
            break;
        case 13:
            decode_break(outbuf, n, pc, op);
            break;
        case 15:
            decode_sync(outbuf, n, pc, op);
            break;
        case 16:
            decode_mfhi(outbuf, n, pc, op);
            break;
        case 17:
            decode_mthi(outbuf, n, pc, op);
            break;
        case 18:
            decode_mflo(outbuf, n, pc, op);
            break;
        case 19:
            decode_mtlo(outbuf, n, pc, op);
            break;
        case 24:
            decode_mult(outbuf, n, pc, op);
            break;
        case 25:
            decode_multu(outbuf, n, pc, op);
            break;
        case 26:
            decode_div(outbuf, n, pc, op);
            break;
        case 27:
            decode_divu(outbuf, n, pc, op);
            break;
        case 32:
            decode_add(outbuf, n, pc, op);
            break;
        case 33:
            decode_addu(outbuf, n, pc, op);
            break;
        case 34:
            decode_sub(outbuf, n, pc, op);
            break;
        case 35:
            decode_subu(outbuf, n, pc, op);
            break;
        case 36:
            decode_and(outbuf, n, pc, op);
            break;
        case 37:
            decode_or(outbuf, n, pc, op);
            break;
        case 38:
            decode_xor(outbuf, n, pc, op);
            break;
        case 39:
            decode_nor(outbuf, n, pc, op);
            break;
        case 42:
            decode_slt(outbuf, n, pc, op);
            break;
        case 43:
            decode_sltu(outbuf, n, pc, op);
            break;
        case 48:
            decode_tge(outbuf, n, pc, op);
            break;
        case 49:
            decode_tgeu(outbuf, n, pc, op);
            break;
        case 50:
            decode_tlt(outbuf, n, pc, op);
            break;
        case 51:
            decode_tltu(outbuf, n, pc, op);
            break;
        case 52:
            decode_teq(outbuf, n, pc, op);
            break;
        case 54:
            decode_tne(outbuf, n, pc, op);
            break;
        default:
            /* unreachable */
            abort();
    }
}

static void decode_SPC2(char *outbuf, size_t n, uint32_t pc, uint32_t op)
{
    switch (getfunction(op))
    {
        case 0:
            decode_madd(outbuf, n, pc, op);
            break;
        case 1:
            decode_maddu(outbuf, n, pc, op);
            break;
        case 2:
            decode_mul(outbuf, n, pc, op);
            break;
        case 3:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
        case 16:
        case 17:
        case 18:
        case 19:
        case 20:
        case 21:
        case 22:
        case 23:
        case 24:
        case 25:
        case 26:
        case 27:
        case 28:
        case 29:
        case 30:
        case 31:
        case 34:
        case 35:
        case 36:
        case 37:
        case 38:
        case 39:
        case 40:
        case 41:
        case 42:
        case 43:
        case 44:
        case 45:
        case 46:
        case 47:
        case 48:
        case 49:
        case 50:
        case 51:
        case 52:
        case 53:
        case 54:
        case 55:
        case 56:
        case 57:
        case 58:
        case 59:
        case 60:
        case 61:
        case 62:
            decode_reserved(outbuf, n, pc, op);
            break;
        case 4:
            decode_msub(outbuf, n, pc, op);
            break;
        case 5:
            decode_msubu(outbuf, n, pc, op);
            break;
        case 32:
            decode_clz(outbuf, n, pc, op);
            break;
        case 33:
            decode_clo(outbuf, n, pc, op);
            break;
        case 63:
            decode_sdbbp(outbuf, n, pc, op);
            break;
        default:
            /* unreachable */
            abort();
    }
}

static void decode_R(char *outbuf, size_t n, uint32_t pc, uint32_t op)
{
    switch (getrt(op))
    {
        case 0:
            decode_bltz(outbuf, n, pc, op);
            break;
        case 1:
            decode_bgez(outbuf, n, pc, op);
            break;
        case 2:
            decode_bltzl(outbuf, n, pc, op);
            break;
        case 3:
            decode_bgezl(outbuf, n, pc, op);
            break;
        case 4:
        case 5:
        case 6:
        case 7:
        case 13:
        case 15:
        case 20:
        case 21:
        case 22:
        case 23:
        case 24:
        case 25:
        case 26:
        case 27:
        case 28:
        case 29:
        case 30:
        case 31:
            decode_reserved(outbuf, n, pc, op);
            break;
        case 8:
            decode_tgei(outbuf, n, pc, op);
            break;
        case 9:
            decode_tgeiu(outbuf, n, pc, op);
            break;
        case 10:
            decode_tlti(outbuf, n, pc, op);
            break;
        case 11:
            decode_tltiu(outbuf, n, pc, op);
            break;
        case 12:
            decode_teqi(outbuf, n, pc, op);
            break;
        case 14:
            decode_tnei(outbuf, n, pc, op);
            break;
        case 16:
            decode_bltzal(outbuf, n, pc, op);
            break;
        case 17:
            decode_bgezal(outbuf, n, pc, op);
            break;
        case 18:
            decode_bltzall(outbuf, n, pc, op);
            break;
        case 19:
            decode_bgezall(outbuf, n, pc, op);
            break;
        default:
            /* unreachable */
            abort();
    }
}

static void decode_COP0(char *outbuf, size_t n, uint32_t pc, uint32_t op)
{
    switch (getrs(op))
    {
        case 0:
            decode_mfc0(outbuf, n, pc, op);
            break;
        case 1:
        case 2:
        case 3:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
            decode_reserved(outbuf, n, pc, op);
            break;
        case 4:
            decode_mtc0(outbuf, n, pc, op);
            break;
        case 16:
        case 17:
        case 18:
        case 19:
        case 20:
        case 21:
        case 22:
        case 23:
        case 24:
        case 25:
        case 26:
        case 27:
        case 28:
        case 29:
        case 30:
        case 31:
            decode_CO(outbuf, n, pc, op);
            break;
        default:
            /* unreachable */
            abort();
    }
}

static void decode_CO(char *outbuf, size_t n, uint32_t pc, uint32_t op)
{
    switch (getfunction(op))
    {
        case 0:
        case 3:
        case 4:
        case 5:
        case 7:
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
        case 16:
        case 17:
        case 18:
        case 19:
        case 20:
        case 21:
        case 22:
        case 23:
        case 25:
        case 26:
        case 27:
        case 28:
        case 29:
        case 30:
        case 33:
        case 34:
        case 35:
        case 36:
        case 37:
        case 38:
        case 39:
        case 40:
        case 41:
        case 42:
        case 43:
        case 44:
        case 45:
        case 46:
        case 47:
        case 48:
        case 49:
        case 50:
        case 51:
        case 52:
        case 53:
        case 54:
        case 55:
        case 56:
        case 57:
        case 58:
        case 59:
        case 60:
        case 61:
        case 62:
        case 63:
            decode_reserved(outbuf, n, pc, op);
            break;
        case 1:
            decode_tlbr(outbuf, n, pc, op);
            break;
        case 2:
            decode_tlbwi(outbuf, n, pc, op);
            break;
        case 6:
            decode_tlbwr(outbuf, n, pc, op);
            break;
        case 8:
            decode_tlbp(outbuf, n, pc, op);
            break;
        case 24:
            decode_eret(outbuf, n, pc, op);
            break;
        case 31:
            decode_deret(outbuf, n, pc, op);
            break;
        case 32:
            decode_wait(outbuf, n, pc, op);
            break;
        default:
            /* unreachable */
            abort();
    }
}

#endif
