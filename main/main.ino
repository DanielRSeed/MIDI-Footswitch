#include <MIDI.h>

MIDI_CREATE_DEFAULT_INSTANCE();

#include "libraries/enums/EnumSwitchMode.h"
#include "libraries/SwitchProcessor/SwitchProcessor.h"
#include "libraries/Switch/Switch.h"

Switch *_switch;
Switch *_switchModeSelect;

void setup()
{
  // set the built in LED pin to output
  pinMode(LED_BUILTIN, OUTPUT);

  _switch = new Switch(2, INPUT_PULLUP, EnumSwitchMode::Momentary);
  _switchModeSelect = new Switch(3, INPUT_PULLUP, EnumSwitchMode::Latching);

  Serial.begin(9600);
  MIDI.begin(MIDI_CHANNEL_OFF);
}

bool _bLastState = true;
void loop()
{
  bool bSwitchState = _switchModeSelect->GetState();

  if(bSwitchState == true)
    _switch->SetSwitchMode(EnumSwitchMode::Latching);
  else
    _switch->SetSwitchMode(EnumSwitchMode::Momentary);

  bool bState = _switch->GetState();

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
