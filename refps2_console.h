#define ROM_SIZE (4  << 20)
#define RAM_SIZE (32 << 20)

typedef struct
{
  ee_core_r3000 Processor;
  uint8_t RAM[MEBI_BYTE(2)];
} ps2_io_unit;

typedef struct
{
  ps2_emotion_engine EE;
  ps2_graphics_synthesizer GS;
  uint8_t ROM[ROM_SIZE];
  uint8_t RAM[RAM_SIZE];
  ps2_io_unit IPU;
} ps2_console;

static ps2_console* Console;  // this should be local scope