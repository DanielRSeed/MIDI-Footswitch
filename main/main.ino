enum EnumSwitchMode
{
  Momentary,
  Latching
};

class SwitchProcessor
{
private:
  EnumSwitchMode _switchMode;
  int _iLastButtonState = HIGH;
  unsigned long _lLastDebounceTime = 0;
  unsigned long _lDebounceDelay = 50;
  int _iButtonState;
  bool _bLEDState = false;

public:
  SwitchProcessor();
  SwitchProcessor(EnumSwitchMode switchMode);

  void ChangeMode(EnumSwitchMode switchMode);

  bool GetState(int iPin);
};

SwitchProcessor::SwitchProcessor()
{
  _switchMode = EnumSwitchMode::Momentary;
}

SwitchProcessor::SwitchProcessor(EnumSwitchMode switchMode)
{
  _switchMode = switchMode;
}

void SwitchProcessor::ChangeMode(EnumSwitchMode switchMode)
{
  _switchMode = switchMode;
}

bool SwitchProcessor::GetState(int iPin)
{
  // read the state for the pin
  int iReadState = digitalRead(iPin);

  // if the state changed since the last read
  if (iReadState != _iLastButtonState)
  {
    // set the current milliseconds
    _lLastDebounceTime = millis();
  }

  // if we have elapsed our wait time
  if ((millis() - _lLastDebounceTime) > _lDebounceDelay)
  {
    // if the state did change
    if (iReadState != _iButtonState)
    {
      // update the state
      _iButtonState = iReadState;

      // if the state is high, we need to switch the light on
      if (_iButtonState == HIGH)
      {
        _bLEDState = !_bLEDState;
      }
    }
  }

  // set this last read
  _iLastButtonState = iReadState;

  // if we're in momentary mode, just spit the read state out
  if (_switchMode == EnumSwitchMode::Momentary)
  {
    if (iReadState == HIGH)
      return true;

    return false;
  }

  return _bLEDState;
}

class Switch
{
private:
  int _iPinId;
  int _PIN_MODE;
  EnumSwitchMode _switchMode;
  SwitchProcessor *_switchProcessor;

public:
  Switch(int iPinId);
  Switch(int iPinId, int iPinMode);
  Switch(int iPinId, int iPinMode, EnumSwitchMode switchMode);
  Switch(int iPinId, EnumSwitchMode switchMode);

  void SetSwitchMode(EnumSwitchMode switchMode);
  bool GetState();
};

Switch::Switch(int iPinId)
    : Switch(iPinId, INPUT_PULLUP, EnumSwitchMode::Momentary){};

Switch::Switch(int iPinId, int iPinMode)
    : Switch(iPinId, iPinMode, EnumSwitchMode::Momentary){};

Switch::Switch(int iPinId, EnumSwitchMode switchMode)
    : Switch(iPinId, INPUT_PULLUP, switchMode){};

Switch::Switch(int iPinId, int iPinMode, EnumSwitchMode switchMode)
{
  _iPinId = iPinId;
  _PIN_MODE = iPinMode;
  _switchMode = switchMode;

  _switchProcessor = new SwitchProcessor(_switchMode);

  pinMode(_iPinId, iPinMode);
};

bool Switch::GetState()
{
  return _switchProcessor->GetState(_iPinId);
}

void Switch::SetSwitchMode(EnumSwitchMode switchMode)
{
  _switchProcessor->ChangeMode(switchMode);
}

Switch *_switch;
Switch *_switchModeSelect;

void setup()
{
  // set the built in LED pin to output
  pinMode(LED_BUILTIN, OUTPUT);

  _switch = new Switch(2, INPUT_PULLUP, EnumSwitchMode::Momentary);
  _switchModeSelect = new Switch(7, INPUT_PULLUP, EnumSwitchMode::Latching);
}

void loop()
{
  bool bSwitchState = _switchModeSelect->GetState();

  if(bSwitchState == true)
    _switch->SetSwitchMode(EnumSwitchMode::Latching);
  else
    _switch->SetSwitchMode(EnumSwitchMode::Momentary);

  bool bState = _switch->GetState();

  if (!bState)
    digitalWrite(LED_BUILTIN, HIGH);
  else
    digitalWrite(LED_BUILTIN, LOW);
}
