//enum iso_type
//{
//	ISO_TYPE_ILLEGAL = 0,
//	ISO_TYPE_CD,
//	ISO_TYPE_DVD,
//	ISO_TYPE_AUDIO,
//	ISO_TYPE_DVDDL
//};

typedef enum
{
  ISO_VOL_DESC_TYPE_BOOT_RECORD   = 0,
  ISO_VOL_DESC_TYPE_PRIMARY       = 1,
  ISO_VOL_DESC_TYPE_SUPPLEMENTARY = 2,
  ISO_VOL_DESC_TYPE_PARTITION     = 3,
  ISO_VOL_DESC_TYPE_TERMINATOR    = 255,
} iso_volume_descriptor_type;

typedef struct
{
  uint8_t Type;
  char		ID[5];
  uint8_t Version;
  uint8_t Data[2041];
} iso_volume_descriptor;

enum iso_type
{
	ISO_TYPE_INVALID = 0,
	ISO_TYPE_2048,
	ISO_TYPE_RAW_2336,
	ISO_TYPE_RAW_2352,
	ISO_TYPE_RAWQ_2448,
	ISO_TYPE_NERO_ISO_2048,
	ISO_TYPE_NERO_RAW_2352,
	ISO_TYPE_NERO_RAWQ_2448,
};


typedef struct
{
	FILE* Source;
	enum iso_type Type;
	uint32_t NumSectors;
	uint32_t BlockSize;
	uint32_t BlockOffset;
} iso_file;
