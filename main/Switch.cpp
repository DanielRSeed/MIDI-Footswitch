#ifndef SWITCH_CLASS
#define SWITCH_CLASS

#include "Switch.h"

Switch::Switch()
    : Switch(2, INPUT_PULLUP, EnumSwitchMode::Latching) {};

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

#endif