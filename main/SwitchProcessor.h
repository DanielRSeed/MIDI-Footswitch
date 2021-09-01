#ifndef SWITCHPROCESSOR_H
#define SWITCHPROCESSOR_H

#include "Arduino.h"
#include "./EnumSwitchMode.h"

class SwitchProcessor
{
private:
  EnumSwitchMode _switchMode;
  int _iLastButtonState = HIGH;
  unsigned long _lLastDebounceTime = 0;
  unsigned long _lDebounceDelay = 50;
  int _iButtonState;
  bool _bSwitchState = false;
  int _iOnState;

public:
  SwitchProcessor();
  SwitchProcessor(int iOnState);
  SwitchProcessor(EnumSwitchMode switchMode);
  SwitchProcessor(EnumSwitchMode switchMode, int iOnState);

  void ChangeMode(EnumSwitchMode switchMode);

  EnumSwitchMode GetState(int iPin);
};

#endif
