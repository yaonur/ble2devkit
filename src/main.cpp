#include <MIDI.h>
#include <MIDIUSB.h>
#define DEBUG 0

#if DEBUG == 1
#define debug(x) Serial.print(x)
#define debugln(x) Serial.println(x)
#else
#define debug(x)
#define debugln(x)
#endif
int r1 = 2;
int r2 = 3;
int c1 = 6;
int c2 = 5;
int c3 = 4;
int is_pushed = false;
int pushed_button = 0;
bool mode_alt = true;
byte midi_channel = 1; // Change this if Plethora X3 uses different channel (1-16)

MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);
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
    return 94;
  }
  else if (message == 4)
  {
    return 95;
  }
  else if (message == 5)
  {
    return 92;
  }
  else
  {
    return 92;
  }
}

void setup()
{
  Serial.begin(9600);
  delay(1000); // Wait for serial to initialize
  debugln("Starting MIDI setup...");
  
  Serial1.begin(31250); // Standard MIDI baud rate
  MIDI.begin(MIDI_CHANNEL_OFF); // Initialize MIDI, but don't listen to any channel
  
  debugln("Serial1 initialized at 31250 baud");
  debug("Using MIDI channel: ");
  debugln(midi_channel);
  
  pinMode(c1, INPUT_PULLUP);
  pinMode(c2, INPUT_PULLUP);
  pinMode(c3, INPUT_PULLUP);

  pinMode(r1, OUTPUT);
  pinMode(r2, OUTPUT);
  digitalWrite(r1, HIGH);
  digitalWrite(r2, HIGH);

  pinMode(13, OUTPUT);
  
  debugln("Setup complete!");
}

void controlChange(byte control, byte value)
{
  debug("Sending CC: ");
  debug(control);
  debug(" Value: ");
  debug(value);
  debug(" Channel: ");
  debugln(midi_channel);
  
  // Send via USB MIDI
  midiEventPacket_t event = {0x0B, 0xB0 | (midi_channel - 1), control, value};
  MidiUSB.sendMIDI(event);
  MidiUSB.flush();
  
  // Send via hardware serial MIDI
  MIDI.sendControlChange(control, value, midi_channel);
  debugln("CC sent via Serial1");
}
void programChange(byte pc, byte channel = midi_channel)
{
  debug("Sending PC: ");
  debug(pc);
  debug(" Channel: ");
  debugln(channel);
  
  // Send via USB MIDI
  midiEventPacket_t event = {0x0C, 0xC0 | (channel - 1), pc, 0x00};
  MidiUSB.sendMIDI(event);
  MidiUSB.flush();
  
  // Send via hardware serial MIDI
  MIDI.sendProgramChange(pc, channel);
  debugln("PC sent via Serial1");
}
void process_button(int button, int message, int mode, byte channel = midi_channel)
{
  if (pushed_button !=button+message && read_button(button))
  {
    is_pushed = true;
    debugln("Button Pressed");
    debugln(button);
    debugln(message);
    pushed_button = button+message;
    if (mode == 0)
    {
      debugln("sending program change");
      debugln(message - 1);
      programChange(message - 1, channel);
    }
    else
    {
      debugln("sending control change");
      debugln(convertMessage(message));
      controlChange(convertMessage(message), 127);
    }
  } else if (pushed_button == button+message && read_button(button)==false){
    pushed_button = 0;
  }
}
void loop()
{
  
    delay(80);
    digitalWrite(r1,LOW);
    process_button(c1, 2, 0);
    process_button(c2, 3, 0);
    process_button(c3, 7, 1);
    delay(3);
    digitalWrite(r1,HIGH);
  
    digitalWrite(r2,LOW);
    process_button(c1, 4, 0, 2);
    process_button(c2, 5, 0, 2);
    process_button(c3, 6, 0, 2);
    delay(3);
    digitalWrite(r2,HIGH);

  // Test MIDI messages
  // debugln("=== Test Loop ===");
  
  // Test Program Change
  // debugln("Testing Program Change 0...");
  // programChange(0);
  // delay(800);
  
  // Test Control Change (CC 94 is mentioned for Plethora X3)
  // debugln("Testing Control Change 94...");
  // controlChange(94, 127);
  // delay(1000);


  
  // Test another Program Change
  // debugln("Testing Program Change 1...");
  // programChange(1);
  // delay(800);
  
  // debugln("--- End Test Loop ---");
  // delay(2000);
}