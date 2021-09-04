#include <MIDI.h>

MIDI_CREATE_DEFAULT_INSTANCE();

#include "EnumSwitchMode.h"
#include "SwitchProcessor.h"
#include "Switch.h"

// our mode select switch. This determines whether we're in latching or momentary mode
Switch *_switchModeSelect = NULL;

// our control switch. This is a switch that we'll use to output MIDI signals with
Switch *_switchControlSwitch = NULL;

void setup()
{
  // set the built in LED pin to output
  pinMode(LED_BUILTIN, OUTPUT);

  _switchControlSwitch = new Switch(2, INPUT_PULLUP, EnumSwitchMode::Momentary);
  _switchModeSelect = new Switch(3, INPUT_PULLUP, EnumSwitchMode::Latching);

  Serial.begin(9600);
  MIDI.begin(MIDI_CHANNEL_OFF);
}

bool _bLastState = true;
void loop()
{
  // find out what switch mode we're in
  EnumSwitchMode enumSwitchMode = _switchModeSelect->GetState();
   
   // set the switch mode for the control switch
  if(enumSwitchMode == EnumSwitchMode::Latching)
  {
    _switchControlSwitch->SetSwitchMode(EnumSwitchMode::Latching);
  }
  else
  {
    _switchControlSwitch->SetSwitchMode(EnumSwitchMode::Momentary);
  }

  // get the switch state now we know what type of switch we're dealing with
  bool bState = _switchControlSwitch->GetState();

  if (bState == _bLastState)
    return;

  if (bState)
  {
    digitalWrite(LED_BUILTIN, HIGH);
    //MIDI.sendProgramChange(30, 1);

    //Serial.print("hit");
    MIDI.sendControlChange(49, 127, 1);

    // if(!bSwitchState)
    MIDI.sendControlChange(49, 0, 1);
  }
  else
  {
    digitalWrite(LED_BUILTIN, LOW);
    //MIDI.sendControlChange(68, 0, 4);
       // MIDI.sendProgramChange(100, 1);
    //MIDI.sendControlChange(49, 0, 1);
  }

  _bLastState = bState;
}
