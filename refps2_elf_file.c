static elf_file
ElfFile_Create(FILE* File)
{
  elf_file Result = {0};
  elf_header ElfHeader = {0};
  fread(&ElfHeader, sizeof(ElfHeader), 1, File);

  ASSERT(ElfHeader.MagicID == ELF_MAGIC_ID);
  ASSERT(ElfHeader.Format == ELF_FORMAT_32);
  ASSERT(ElfHeader.Endianness == ELF_ENDIANNESS_LITTLE);
  ASSERT(ElfHeader.CurrentVersion == 1);
  ASSERT(ElfHeader.TargetISA == ELF_TARGET_ISA_MIPS);
  //ASSERT(ElfHeader.TargetABI == ?);
  ASSERT(ElfHeader.OriginalVersion == 1);
  Result.Header = ElfHeader;
  Result.Source = File;
  fseek(Result.Source, Result.Header.EntryPoint, SEEK_SET);
  


  return Result;
}

