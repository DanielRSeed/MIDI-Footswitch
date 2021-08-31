#ifndef SWITCHPROCESSOR_CLASS
#define SWITCHPROCESSOR_CLASS

#include "SwitchProcessor.h"

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

#endif