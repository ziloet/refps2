static void
CheckControllers(void)
{
  for (DWORD ControllerIndex = 0; ControllerIndex < XUSER_MAX_COUNT; ControllerIndex++)
  {
    XINPUT_STATE ControllerState = {0};
    DWORD Result = XInputGetState(ControllerIndex, &ControllerState);
    if(Result == ERROR_SUCCESS)
    {
      // Controller is connected
    }
    else
    {
      // Controller is not connected
    }
  }
}

static void
CheckDeadzone(void)
{
  //int MAX = 0x7fff;
  XINPUT_STATE State = Controllers[Index].state;

  float LeftThumbX = State.Gamepad.sThumbLX;
  float LeftThumbY = State.Gamepad.sThumbLY;

  //determine how far the controller is pushed
  float Magnitude = sqrt(LX*LX + LY*LY);

  //determine the direction the controller is pushed
  float normalizedLX = LX / Magnitude;
  float normalizedLY = LY / Magnitude;
  float NormalizedMagnitude = 0;

  if (Magnitude > INPUT_DEADZONE)
  {
    if (Magnitude > 0x7fff)
    {
      Magnitude = 0x7fff;
    }

    //adjust magnitude relative to the end of the dead zone
    Magnitude -= INPUT_DEADZONE;

    //optionally normalize the magnitude with respect to its expected range
    //giving a magnitude value of 0.0 to 1.0
    NormalizedMagnitude = Magnitude / (32767 - INPUT_DEADZONE);
  }
  else //if the controller is in the deadzone zero out the magnitude
  {
    Magnitude = 0.0;
    NormalizedMagnitude = 0.0;
  }

  //repeat for right thumb stick
}


static void
DoViberation(void)
{
  XINPUT_VIBRATION Vibration = {0};
  Vibration.wLeftMotorSpeed = 32000; // use any value between 0-65535 here
  Vibration.wRightMotorSpeed = 16000; // use any value between 0-65535 here
  XInputSetState(ControllerIndex, &Vibration);
}

static void
GetAudioDeviceIDs(void)
{
  WCHAR SpeakerID[256] = {0};
  WCHAR MicrophoneID[256] = {0};
  XInputGetAudioDeviceIds(ControllerIndex, SpeakerID, ARRAY_LENGTH(SpeakerID), MicrophoneID, ARRAY_LENGTH(MicrophoneID));
}

static void
CreateMasteringVoice(void)
{
  IXAudio2* pXAudio2 = NULL;
  HRESULT hr = XAudio2Create(&pXAudio2, 0, XAUDIO2_DEFAULT_PROCESSOR);
  if (FAILED(hr))
  {
    return hr;
  }
  IXAudio2MasteringVoice* pMasterVoice = NULL;
  hr = pXAudio2->CreateMasteringVoice( &pMasterVoice, XAUDIO2_DEFAULT_CHANNELS, XAUDIO2_DEFAULT_SAMPLERATE, 0, renderId, NULL, AudioCategory_Communications);
  if (FAILED(hr))
  {
    return hr;
  }
}