#ifndef SWITCHPROCESSOR_CLASS
#define SWITCHPROCESSOR_CLASS

#include "SwitchProcessor.h"

#pragma region Constructors

SwitchProcessor::SwitchProcessor() : SwitchProcessor::SwitchProcessor(EnumSwitchMode::Latching, HIGH) {}
SwitchProcessor::SwitchProcessor(EnumSwitchMode switchMode) : SwitchProcessor::SwitchProcessor(switchMode, HIGH) {}
SwitchProcessor::SwitchProcessor(int iOnState) : SwitchProcessor::SwitchProcessor(EnumSwitchMode::Latching, iOnState){}

SwitchProcessor::SwitchProcessor(EnumSwitchMode switchMode, int iOnState)
{
  _switchMode = switchMode;
  _iOnState = iOnState;
}
#pragma endregion

// Changes the mode of the processor, to handle latching or momentary switching
void SwitchProcessor::ChangeMode(EnumSwitchMode switchMode)
{
  _switchMode = switchMode;
}

// Returns the state of the switch, based on the switch mode
EnumSwitchMode SwitchProcessor::GetState(int iPin)
{
  // read the initial state of the pin
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

      // if the state is low, we need to switch the light on
      if (_iButtonState == LOW)
      {
        // flip our state
        _bSwitchState = !_bSwitchState;
      }
    }
  }

  // set this last read
  _iLastButtonState = iReadState;

  // if we're in momentary mode, just spit the read state out
  if (_switchMode == EnumSwitchMode::Momentary)
  {
    if (iReadState == HIGH)
    {
      return EnumSwitchMode::Momentary;
    }
    
    return EnumSwitchMode::Latching;
  }

  if (_bSwitchState)
    return EnumSwitchMode::Momentary;
  else
    return EnumSwitchMode::Latching;
}

#endif