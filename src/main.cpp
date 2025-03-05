#include "Button.h"

int c1 = 13;

bool button_up_state = false;

MIDI_CREATE_DEFAULT_INSTANCE();
void setup()
{
  // put your setup code here, to run once:
  // Serial.begin(31250);
  // Serial.begin(115200);
  BLEMidiServer.begin("espmcuMidi");
  // MIDI.begin(MIDI_CHANNEL_OFF);
  pinMode(c1, INPUT_PULLUP);
  pinMode(22, OUTPUT);
  debugln("setup complete");
}

void loop()
{
  if (BLEMidiServer.isConnected())
  {
    if (analogRead(c1) < 100)
    {
      if (button_up_state == false)
      {
        debugln("button pressed");
        // MIDI.sendNoteOn(36, 127, 1);
        // BLEMidiServer.controlChange(1, 36, 127);
        BLEMidiServer.noteOn(1, 36, 127);
      }
      button_up_state = true;
    } 
    else
    {
      if (button_up_state == true){
        debugln("button not pressed");
        // MIDI.sendNoteOff(36, 0, 1);
        // BLEMidiServer.controlChange(1, 36, 0);
        BLEMidiServer.noteOff(1, 36, 0);
      }
      button_up_state = false;
    }

    digitalWrite(22, HIGH);
  }
  else
  {
    digitalWrite(22, LOW);
  }
  // debugln(BLEMidiServer.isConnected());
  delay(50);

  
  // MIDI.sendProgramChange(0, 1); // Send program change 0 on channel 1
  // delay(1500); // Wait for 1 second
  // MIDI.sendProgramChange(1, 1); // Send program change 1 on channel 1
  // delay(1500);
}