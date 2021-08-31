#ifndef SWITCHPROCESSOR_H
#define SWITCHPROCESSOR_H

#include "Arduino.h"
#include "./libraries/enums/EnumSwitchMode.h"

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

#endif
