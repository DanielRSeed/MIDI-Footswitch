byte bButtonPin = 4;

enum EnumSwitchMode
{
  Momentary,
  Latching
};

class Switch
{
private:
  int _iPin;
  int _iLastButtonState = HIGH;
  int _iButtonState;
  unsigned long _lLastDebounceTime = 0;
  unsigned long _lDebounceDelay = 50;
  bool _bLEDState = false;
  EnumSwitchMode _switchMode = Momentary;
  void (*_delegateSwitchHandler)(bool);

public:
  
  Switch(int, int, void (*func)(bool));
  Switch(int, int, void (*func)(bool), EnumSwitchMode switchMode);

  // returns the toggle state of the switch
  bool GetSwitchToggleState(void)
  {
    // read the state for the pin
    int iReadState = digitalRead(_iPin);

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

    if(_bLEDState)
      _delegateSwitchHandler(true);

    // return the state
    return _bLEDState;
  }
};

Switch::Switch(int iPin, int iInputMode, void (*func)(bool))
{
  _iPin = iPin;

  // set the pin mode for the input
  pinMode(_iPin, iInputMode);

  _delegateSwitchHandler = func;
};

Switch::Switch(int iPin, int iInputMode, void (*func)(bool), EnumSwitchMode switchMode) 
  : Switch(iPin, iInputMode, func)
{
  // set the switch mode
  _switchMode = switchMode;
  _delegateSwitchHandler = func;
}

Switch *switch1;

void setup()
{
  // set the built in LED pin to output
  pinMode(LED_BUILTIN, OUTPUT);

  // declare our switch
  Switch _switch(4, INPUT_PULLUP, nullptr);

  switch1 = &_switch;
}

void loop()
{

  bool bState = switch1->GetSwitchToggleState();

}

void WriteState(bool bState){
  digitalWrite(LED_BUILTIN, bState);
}