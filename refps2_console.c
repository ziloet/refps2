static void
PS2Console_CopyBiosToMemory(ps2_console* Console, const WCHAR* BiosFileName)
{
  HANDLE BiosFile = CreateFileW(BiosFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
  ASSERT(BiosFile != INVALID_HANDLE_VALUE);
  LARGE_INTEGER FileSizeHolder = {0};
  GetFileSizeEx(BiosFile, &FileSizeHolder);
  DWORD FileSize = (DWORD)FileSizeHolder.QuadPart;
  ASSERT(FileSize <= sizeof(Console->ROM));
  DWORD BytesRead = 0;
  ReadFile(BiosFile, Console->ROM, FileSize, &BytesRead, NULL);
  ASSERT(BytesRead == FileSize);
  CloseHandle(BiosFile);
}

static void
PS2Console_Execute(ps2_console* Console)
{
  R5900_Reset(&Console->EE.CPU);
  R5900_Run(&Console->EE.CPU);
}

#if 0
static void
PS2Console_CopyProgramToMemory(ps2_console* Console, elf_file ElfFile)
{
  for(uint64_t Index = 0; Index < ElfFile.Header.ProgramHeaderEntriesCount; Index += 1)
  {
    LARGE_INTEGER ProgramHeaderEntry = { ElfFile.Header.ProgramHeaderTableAddress + (Index * ElfFile.Header.ProgramHeaderEntrySize) + 12 };
    SetFilePointerEx(ElfFile.Source, ProgramHeaderEntry, NULL, FILE_BEGIN);
    uint32_t SegmentPhysicalAddress = 0;
    ReadFile(ElfFile.Source, &SegmentPhysicalAddress, sizeof(SegmentPhysicalAddress), NULL, NULL);
    uint64_t Address = ElfFile.ProgramHeaderEntry[Index].SegmentPhysicalAddress;
    int BytesRead = fread(Console.RAM[Address], ElfFile.ProgramHeaderEntry[Index].SegmentSizeInImage, 1, ElfFile.Source);
    ASSERT(BytesRead == ElfFile.ProgramHeaderIndex[Index].SegmentSizeInImage);
  }
}

static void
PS2Console_CopySectionToMemory(ps2_console* Console, elf_file ElfFile)
{
  for(uint8_t Index = 0; Index < ElfFile.Header.SectionHeaderEntriesCount; Index += 1)
  {
    uint64_t Address = ElfFile.SectionHeaderEntry[Index].SectionVirtualAddressInMemory;
    fseek(ElfFile, ElfFile.SectionHeaderEntry[Index].SectionOffsetInImage, SEEK_SET);
    int BytesRead = fread(Console.RAM[Address], ElfFile.SectionHeaderEntry[Index].SectionSizeInImage, 1, ElfFile.Source);
    ASSERT(BytesRead == ElfFile.SectionHeaderEntry[Index].SectionSizeInImage);
  }
}

static void
PS2Console_InitElfFile(ps2_console* Console, const WCHAR* ElfFileName)
{
  elf_file ElfFile = {0};
  ElfFile.Source = CreateFileW(BiosFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
  ASSERT(ElfFile.Source != NULL);
  LARGE_INTEGER FileSizeHolder = {0};
  GetFileSizeEx(ElfFile.Source, &FileSizeHolder);
  DWORD FileSize = (DWORD)FileSizeHolder.QuadPart;
  ASSERT(FileSize <= sizeof(Console->RAM));
  DWORD BytesRead = 0;
  ReadFile(ElfFile, &ElfFile.Header, sizeof(ElfFile.Header), &BytesRead, NULL);
  ASSERT(BytesRead == sizeof(ElfFile.Header));
  PS2Console_CopyProgramToMemory(Console, ElfFile);
  PS2Console_CopySectionToMemory(Console, ElfFile);
  CloseHandle(ElfFile.Source);
}
#endif