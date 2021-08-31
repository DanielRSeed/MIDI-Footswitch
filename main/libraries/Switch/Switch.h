#ifndef SWITCH_H
#define SWITCH_H

#include "Arduino.h"
#include "../SwitchProcessor/SwitchProcessor.h"

class Switch
{
private:
  int _iPinId;
  int _PIN_MODE;
  EnumSwitchMode _switchMode;
  SwitchProcessor *_switchProcessor;

public:
  Switch();
  Switch(int iPinId);
  Switch(int iPinId, int iPinMode);
  Switch(int iPinId, int iPinMode, EnumSwitchMode switchMode);
  Switch(int iPinId, EnumSwitchMode switchMode);

  bool GetState();
  void SetSwitchMode(EnumSwitchMode switchMode);
};
#endif