#include "Button.h"
int r1 = 5;
int r2 = 4;
int c1 = 14;
int c2 = 27;
int c3 = 26;
int c4 = 25;
int c5 = 33;
bool button_up_state = false;

MIDI_CREATE_DEFAULT_INSTANCE();
void setup()
{
  // put your setup code here, to run once:
  // Serial.begin(31250);
  // Serial.begin(115200);
  BLEMidiServer.begin("espmcuMidi");
  MIDI.begin(MIDI_CHANNEL_OFF);
  pinMode(c1, INPUT_PULLUP);
  pinMode(c2, INPUT_PULLUP);
  pinMode(c3, INPUT_PULLUP);
  pinMode(c4, INPUT_PULLUP);
  pinMode(c5, INPUT_PULLUP);
  pinMode(r1, INPUT_PULLUP);
  pinMode(r2, INPUT_PULLUP);
  pinMode(22, OUTPUT);
  debugln("setup complete");
}

void loop()
{
  if (BLEMidiServer.isConnected())
  {

    digitalWrite(22, HIGH);
  }
  else
  {
    digitalWrite(22, LOW);
  }

  if (digitalRead(r1) == LOW)
  {
    process_button(c1, 1);
    process_button(c2, 2);
    process_button(c3, 3);
    process_button(c4, 4);
    process_button(c5, 5);
    delay(3);
  }
  else if (digitalRead(r2) == LOW)
  {
    process_button(c1, 1, 1, 1, 64);
    process_button(c2, 2, 1, 1, 64);
    process_button(c3, 3, 1, 1, 64);
    process_button(c4, 4, 1, 1, 64);
    process_button(c5, 5, 3, 1, 5);
    delay(3);
  }
  else if (digitalRead(r1) == HIGH && digitalRead(r2) == HIGH)
  {
    reset_button(r1,r2);
  }
  // MIDI.sendProgramChange(0, 1); // Send program change 0 on channel 1
  // delay(1500); // Wait for 1 second
  // MIDI.sendProgramChange(1, 1); // Send program change 1 on channel 1
  // delay(1500);
}