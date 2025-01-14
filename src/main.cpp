#include <MIDI.h>
#include <MIDIUSB.h>
#define DEBUG 1

#if DEBUG == 1
#define debug(x) Serial.print(x)
#define debugln(x) Serial.println(x)
#else
#define debug(x)
#define debugln(x)
#endif
int r1 = 25;
int r2 = 27;
int c1 = 36;
int c2 = 37;
int c3 = 38;
int is_pushed = 0;
bool mode_alt = true;

// MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);
MIDI_CREATE_DEFAULT_INSTANCE();
bool read_button(int button)
{
  if (digitalRead(button) == LOW)
    return true;
  else
    return false;
}
int convertMessage(int message)
{
  if (message == 1)
  {
    return 75;
  }
  else if (message == 2)
  {
    return 76;
  }
  else if (message == 3)
  {
    return 77;
  }
  else if (message == 4)
  {
    return 84;
  }
  else if (message == 5)
  {
    return 64;
  }
  else
  {
    return 64;
  }
}

void setup()
{
  MIDI.begin(MIDI_CHANNEL_OFF); // Initialize MIDI, but don't listen to any channel
  Serial1.begin(31250);
  Serial.begin(9600);
  pinMode(c1, INPUT_PULLUP);
  pinMode(c2, INPUT_PULLUP);
  pinMode(c3, INPUT_PULLUP);

  pinMode(r1, INPUT_PULLUP);
  pinMode(r2, INPUT_PULLUP);

  pinMode(13, OUTPUT);
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
void process_button(int button, int message, int mode)
{
  if (is_pushed == 0 && read_button(button))
  {
    is_pushed = button;
    if (mode == 0)
    {
      programChange(message - 1);
    }
    else
    {
      controlChange(convertMessage(message), 127);
    }
  }
}
void loop()
{
  if (digitalRead(r1) == LOW)
  {
    process_button(c1, 1, 0);
    process_button(c2, 2, 0);
    process_button(c3, 3, 0);
    delay(3);
  }
  else if (digitalRead(r2) == LOW)
  {
    process_button(c1, 4, 0);
    process_button(c2, 5, 0);
    process_button(c3, 6, 0);
    delay(3);
  }
  // Send MIDI over Serial
  // debugln("loop");
  // // MIDI.sendProgramChange(0, 1);
  // controlChange(75,127);
  // programChange(0);
  // MidiUSB.flush();
  // delay(1500);
  // // MIDI.sendProgramChange(1, 1);
  // // controlChange(76,127);
  // programChange(1);
  // MidiUSB.flush();
  // delay(1500);
  // // controlChange(77,127);
  // programChange(2);
  // MidiUSB.flush();
  // delay(1500);
}