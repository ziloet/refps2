typedef struct
{
  bool Key[256];
  bool CapsLock;
  bool NumLock;
} keyboard_state;

typedef struct
{
  bool ButtonX;
  bool ButtonTriangle;
  bool ButtonSquare;
  bool ButtonCircle;
  bool ButtonStart;
  bool ButtonSelect;
  bool ArrowRight;
  bool ArrowLeft;
  bool ArrowDown;
  bool ArrowUp;
  bool ButtonR1;
  bool ButtonL1;
  bool ButtonR2;
  bool ButtonR2;
  uint8_t StickLeft;
  uint8_t StickRight;
} gamepad_state;

typedef union
{
  keyboard_state Keyboard;
  gamepad_state  Gamepad;
} input_state;