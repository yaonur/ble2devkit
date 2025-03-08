// #include <MIDI.h>
#include <MIDIUSB.h>
#define DEBUG 1

#if DEBUG == 0
#define debug(x) Serial.print(x)
#define debugln(x) Serial.println(x)
#else
#define debug(x)
#define debugln(x)
#endif
int r1 = 21;

int is_pushed = false;

// MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);
// MIDI_CREATE_DEFAULT_INSTANCE();

void setup()
{
  // MIDI.begin(MIDI_CHANNEL_OFF); // Initialize MIDI, but don't listen to any channel
  // Serial1.begin(31250);
  // Serial.begin(9600);

  pinMode(r1, INPUT);

}

void controlChange(byte control, byte value)
{
  midiEventPacket_t event = {0x0B, 0xB0, control, value};
  MidiUSB.sendMIDI(event);
}
void programChange(byte pc)
{
  midiEventPacket_t event = {0x0C, 0xC0, pc, 0x00};
  MidiUSB.sendMIDI(event);
}
int distance = 0;
void loop()
{
  // distance = analogRead(r1);
  // if (distance < 100)
  // {
  //   if (is_pushed == false)
  //   {
  //     controlChange(75, 127);
  //     is_pushed = true;
  //   }
  // }
  // else if (distance > 700)
  // {
  //   is_pushed = false;
  // }
  controlChange(37, 127);
  delay(1000);
  controlChange(38, 127);
  delay(1000);
}