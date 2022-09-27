static uint8_t
MemoryRead8(uint32_t VirtualAddress)
{
  uint8_t Result = 0;
  if(VirtualAddress >= VIRTUAL_ADDRESS_RAM && VirtualAddress <= VIRTUAL_ADDRESS_RAM + RAM_SIZE)
  {
    uint32_t Address = VirtualAddress - VIRTUAL_ADDRESS_RAM;
    Result = ((uint8_t*)Console->RAM)[Address >> 2];
  }
  else if(VirtualAddress >= VIRTUAL_ADDRESS_ROM && VirtualAddress <= VIRTUAL_ADDRESS_ROM + ROM_SIZE)
  {
    uint32_t Address = VirtualAddress - VIRTUAL_ADDRESS_ROM;
    Result = ((uint8_t*)Console->ROM)[Address >> 2];
  }
  else
  {
    ASSERT(0);
  }
  return Result;
}

static uint16_t
MemoryRead16(uint32_t VirtualAddress)
{
  uint16_t Result = 0;
  if(VirtualAddress >= VIRTUAL_ADDRESS_RAM && VirtualAddress <= VIRTUAL_ADDRESS_RAM + RAM_SIZE)
  {
    uint32_t Address = VirtualAddress - VIRTUAL_ADDRESS_RAM;
    Result = ((uint16_t*)Console->RAM)[Address >> 2];
  }
  else if(VirtualAddress >= VIRTUAL_ADDRESS_ROM && VirtualAddress <= VIRTUAL_ADDRESS_ROM + ROM_SIZE)
  {
    uint32_t Address = VirtualAddress - VIRTUAL_ADDRESS_ROM;
    Result = ((uint16_t*)Console->ROM)[Address >> 2];
  }
  else
  {
    ASSERT(0);
  }
  return Result;
}

static uint32_t
MemoryRead32(uint32_t VirtualAddress)
{
  uint32_t Result = 0;
  if(VirtualAddress >= VIRTUAL_ADDRESS_RAM && VirtualAddress <= VIRTUAL_ADDRESS_RAM + RAM_SIZE)
  {
    uint32_t Address = VirtualAddress - VIRTUAL_ADDRESS_RAM;
    Result = ((uint32_t*)Console->RAM)[Address >> 2];
  }
  else if(VirtualAddress >= VIRTUAL_ADDRESS_ROM && VirtualAddress <= VIRTUAL_ADDRESS_ROM + ROM_SIZE)
  {
    uint32_t Address = VirtualAddress - VIRTUAL_ADDRESS_ROM;
    Result = ((uint32_t*)Console->ROM)[Address >> 2];
  }
  else
  {
    ASSERT(0);
  }
  return Result;
}


static void
MemoryWrite8(uint32_t VirtualAddress, uint8_t Value)
{
  if(VirtualAddress >= VIRTUAL_ADDRESS_RAM && VirtualAddress <= VIRTUAL_ADDRESS_RAM + RAM_SIZE)
  {
    uint32_t Address = VirtualAddress - VIRTUAL_ADDRESS_RAM;
    ((uint8_t*)Console->RAM)[Address >> 2] = Value;
  }
  else if(VirtualAddress >= VIRTUAL_ADDRESS_ROM && VirtualAddress <= VIRTUAL_ADDRESS_ROM + ROM_SIZE)
  {
    uint32_t Address = VirtualAddress - VIRTUAL_ADDRESS_ROM;
    ((uint8_t*)Console->ROM)[Address >> 2] = Value;
  }
  else
  {
    ASSERT(0);
  }
}


static void
MemoryWrite16(uint32_t VirtualAddress, uint16_t Value)
{
  if(VirtualAddress >= VIRTUAL_ADDRESS_RAM && VirtualAddress <= VIRTUAL_ADDRESS_RAM + RAM_SIZE)
  {
    uint32_t Address = VirtualAddress - VIRTUAL_ADDRESS_RAM;
    ((uint16_t*)Console->RAM)[Address >> 2] = Value;
  }
  else if(VirtualAddress >= VIRTUAL_ADDRESS_ROM && VirtualAddress <= VIRTUAL_ADDRESS_ROM + ROM_SIZE)
  {
    uint32_t Address = VirtualAddress - VIRTUAL_ADDRESS_ROM;
    ((uint16_t*)Console->ROM)[Address >> 2] = Value;
  }
  else
  {
    ASSERT(0);
  }
}

static void
MemoryWrite32(uint32_t VirtualAddress, uint32_t Value)
{
  if(VirtualAddress >= VIRTUAL_ADDRESS_RAM && VirtualAddress <= VIRTUAL_ADDRESS_RAM + RAM_SIZE)
  {
    uint32_t Address = VirtualAddress - VIRTUAL_ADDRESS_RAM;
    ((uint32_t*)Console->RAM)[Address >> 2] = Value;
  }
  else if(VirtualAddress >= VIRTUAL_ADDRESS_ROM && VirtualAddress <= VIRTUAL_ADDRESS_ROM + ROM_SIZE)
  {
    uint32_t Address = VirtualAddress - VIRTUAL_ADDRESS_ROM;
    ((uint32_t*)Console->ROM)[Address >> 2] = Value;
  }
  else
  {
    ASSERT(0);
  }
}
