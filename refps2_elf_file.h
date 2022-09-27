enum
{
  ELF_MAGIC_ID = 0x464c457f
};

enum elf_format
{
  ELF_FORMAT_32 = 1,
  ELF_FORMAT_64 = 2,
}; 

enum elf_endianness
{
  ELF_ENDIANNESS_LITTLE = 1,
  ELF_ENDIANNESS_BIG    = 2,
};

enum elf_target_instruction_set
{
  ELF_TARGET_ISA_MIPS = 0x8,
};


typedef struct
{
  uint32_t MagicID;
  uint8_t  Format;
  uint8_t  Endianness;
  uint8_t  CurrentVersion;
  uint8_t  TargetABI;
  uint8_t  ABIVersion;
  uint8_t  ReservedPaddingBytes[7];
  uint16_t ObjectFileType;
  uint16_t TargetISA;
  uint32_t OriginalVersion;
  uint32_t EntryPoint;
  uint32_t ProgramHeaderTableAddress;
  uint32_t SectionHeaderTableAddress;
  uint32_t ArchitectureSpecificFlags;
  uint16_t StructSize;
  uint16_t ProgramHeaderEntrySize;
  uint16_t ProgramHeaderEntriesCount;
  uint16_t SectionHeaderEntrySize;
  uint16_t SectionHeaderEntriesCount;
  uint16_t SectionHeaderNamesEntryIndex;
} elf_header;

STATIC_ASSERT(sizeof(elf_header) == 0x34);

typedef struct
{
  uint32_t SegmentType;
  uint32_t SegmentOffset;
  uint32_t SegmentVirtualAddress;
  uint32_t SegmentPhysicalAddress;
  uint32_t SegmentSizeInImage;
  uint32_t SegmentSizeInMemory;
  uint32_t SegmentDependentFlags;
  uint32_t Alignment;
} elf_program_header;

STATIC_ASSERT(sizeof(elf_program_header) == 0x20);

typedef struct
{
  uint32_t NameStringOffset;
  uint32_t Type;
  uint32_t Attributes;
  uint32_t SectionVirtualAddressInMemory;
  uint32_t SectionOffsetInImage;
  uint32_t SectionSizeInImage;
  uint32_t LinkedSectionIndex;
  uint32_t ExtraInfo;
  uint32_t RequiredAlignment;
  uint32_t EntrySize;
} elf_section_header;

STATIC_ASSERT(sizeof(elf_section_header) == 0x28);


typedef struct
{
  elf_header Header;
  elf_program_header* ProgramHeaderTable;
  elf_section_header* SectionHeaderTable;
  HANDLE Source;
} elf_file;
