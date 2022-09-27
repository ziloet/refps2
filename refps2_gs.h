enum gs_primitives
{
  GS_PRIMITIVE_POINT,
  GS_PRIMITIVE_LINE,
  GS_PRIMITIVE_LINE_STRIP,
  GS_PRIMITIVE_TRIANGLE,
  GS_PRIMITIVE_TRIANGLE_STRIP,
  GS_PRIMITIVE_TRIANGLE_FAN,
  GS_PRIMITIVE_SPRITE,
};


enum gs_color_data_formats
{
  COLOR_FORMAT_RGBA32,
  COLOR_FORMAT_RGB24,
  COLOR_FORMAT_RGBA16,

  // can only be used in texture buffer
  COLOR_FORMAT_IDTEX8,
  COLOR_FORMAT_IDTEX4,
};

typedef struct
{
  uint8_t FrameBuffer;
  uint8_t ZBuffer;
  uint8_t TextureBuffer;
  uint8_t ColorLookupTable;
  uint8_t Memory[MEBI_BYTE(4)];
} ps2_graphics_synthesizer;