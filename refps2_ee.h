#define PS2_EE_CPU_SPEED 294.912
//#define PS2_EE_CPU_SPEED 299    // on newer versions

#define INSTRUCTION_SIZE 4

enum entry_points
{
  ENTRY_POINT_BOOT   = 0xbfc00280,
  ENTRY_POINT_NORMAL = 0x80000080,
};

typedef struct
{
  int X;
} vpu1_graphics_interface;

typedef struct
{
  int X;
} ps2_image_processor;

typedef struct
{
  uint8_t Instructions[KIBI_BYTE(4)];
  uint8_t Data[KIBI_BYTE(4)];
} ee_cop2;

typedef struct
{
  uint8_t Instructions[KIBI_BYTE(16)];
  uint8_t Data[KIBI_BYTE(16)];
  register128_t Registers[32];
  vpu1_graphics_interface GIF;
} ee_vpu1;

typedef struct
{
  ee_cpu  CPU;
  ee_cop2 VPU0;
  ee_vpu1 VPU1;
} ps2_emotion_engine;