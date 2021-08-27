byte bButtonPin = 2;

class Switch {
  private:
    int _iPin;
    int _iLastButtonState = HIGH;
    int _iButtonState;
    unsigned long _lLastDebounceTime = 0;
    unsigned long _lDebounceDelay = 50;
    bool _bLEDState = false;
    
  public:
    // constructor
    Switch(int, int);

    // returns the toggle state of the switch
    bool GetSwitchToggleState(void) {
      
      // read the state for the switch
      int iReadState = digitalRead(_iPin);
      
      // if the state changed since the last read
      if(iReadState != _iLastButtonState) {
        // set the current milliseconds
        _lLastDebounceTime = millis();
      }

      // if we have elapsed our wait time
      if((millis() - _lLastDebounceTime) > _lDebounceDelay) {

        // if the state did change
        if(iReadState != _iButtonState) {

          // update the state
          _iButtonState = iReadState;

          // if the state is high, we need to switch the light on
          if(_iButtonState == HIGH) {
            _bLEDState = !_bLEDState;
          }
        }
      }

      // set this last read
      _iLastButtonState = iReadState;

      // return the state
      return _bLEDState;
    }
};

Switch::Switch(int iPin, int iInputMode) {
  _iPin = iPin;

    // set the pin mode for the input
    pinMode(_iPin, iInputMode);

};

Switch *switch1;

void setup() {

  // enable for logging to serial com port
  //Serial.begin(9600);

  // set the built in LED pin to output
  pinMode(LED_BUILTIN, OUTPUT);

  // declare our switch
  Switch _switch1 (2, INPUT_PULLUP);

  switch1 = &_switch1;
}

void loop() {

    bool bState = switch1->GetSwitchToggleState();
    
    digitalWrite(LED_BUILTIN, bState);
    
}
