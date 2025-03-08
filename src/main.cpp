// #include <MIDI.h>
#include <MIDIUSB.h>
#define DEBUG 0

#if DEBUG == 1
#define debug(x) Serial.print(x)
#define debugln(x) Serial.println(x)
#else
#define debug(x)
#define debugln(x)
#endif
int r1 = 21;

int is_pushed = false;


void setup()
{
  // Serial1.begin(31250);
  // Serial.begin(9600);

  pinMode(r1, INPUT);

}

void controlChange(byte control, byte value)
{
  midiEventPacket_t event = {0x0B, 0xB0, control, value};
  MidiUSB.sendMIDI(event);
  MidiUSB.flush();
}
void programChange(byte pc)
{
  midiEventPacket_t event = {0x0C, 0xC0, pc, 0x00};
  MidiUSB.sendMIDI(event);
  MidiUSB.flush();
}
void sendNoteOn(byte note, byte velocity)
{
  midiEventPacket_t event = {0x09, 0x90, note, velocity};
  MidiUSB.sendMIDI(event);
  MidiUSB.flush();
}

int distance = 0;
void loop()
{
  distance = analogRead(r1);
  if (distance < 28)
  {
    if (is_pushed == false)
    {
      sendNoteOn(36, 127);
      is_pushed = true;
    }
  }
  else if (distance > 31)
  {
    is_pushed = false;
  }
  delay(10);
  // debugln(distance);
  // sendNoteOn(36, 127);
  // delay(1000);
  // sendNoteOn(36, 0);
  // delay(1000);
}