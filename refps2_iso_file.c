#define ISO_FILE_SYSTEM_AREA_OFFSET (1 << 15)

#if 0
static uint32_t
GetISONumSectors(FILE* File)
{
  uint32_t Result = 0;
  fseek(File, ISO_FILE_SYSTEM_AREA_OFFSET, SEEK_SET);
  iso_volume_descriptor IVD = {0};
  for (;;)
  {
    fread(&IVD, sizeof(IVD), 1, File);
    if (!ISOFile_IsValidVolumeDescriptor(&IVD))
    {
      break;
    }
    Result += 1;
  }
  return Result;
}

#endif

static bool
IsISOFormat(FILE* File, uint32_t BlockSize, int32_t BlockOffset)
{
  fseek(File, 16 * BlockSize + BlockOffset, SEEK_SET);
  uint64_t Id = 0;
  fread(&Id, sizeof(Id), 1, File);
  Id <<= 8;
  Id >>= 8;
  bool Result = (Id == 0x0001313030444301);
  return Result;
}

static void
IsoFile_Validate(iso_file* IsoFile)
{
  if (IsISOFormat(IsoFile->Source, 2048, 0))
  {
    IsoFile->BlockSize = 2048;
    IsoFile->BlockOffset = 24;
  }
}

static void
IsoFile_Delete(iso_file* IsoFile)
{
  fclose(IsoFile->Source);
  memset(IsoFile, 0, sizeof(*IsoFile));
}


static iso_file
IsoFile_Create(FILE* File)
{
  iso_file Result = {0};
  Result.Source = File;
  IsoFile_Validate(&Result);

  if(Result.BlockSize == 0)
  {
    IsoFile_Delete(&Result);
    return Result;
  }
  return Result;
}


