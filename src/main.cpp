#include <MIDI.h>
// #include <midi_Defs.h>
// #include <TimerOne.h>
int r1 = 5;
int r2 = 4;
int c1 = 14;
int c2 = 27;
int c3 = 26;
int c4 = 25;
int c5 = 33;
int is_pushed = 0;
bool mode_alt = true;
using namespace midi;
// MidiType type = Clock;

MIDI_CREATE_DEFAULT_INSTANCE();
// const unsigned long interval = 30000; // 500,000 microseconds = 500 milliseconds
// volatile bool sendClock = false;

// void sendMidiClock()
// {
//   if (sendClock)
//   {
//     MIDI.sendClock();
//     // Serial.print("clock");
//   }
// }
// bool ledState = false;
// void toggleLED()
// {
//   ledState = !ledState;
//   digitalWrite(22, ledState);
//   // MIDI.sendClock();
//    if (sendClock)
//   {
//     MIDI.sendClock();
//     // Serial.print("clock");
//   }
// }
// void sendBPM(int bpm)
// {
//   byte sysexMessage[] = {
//     0xF0,       // Start of SysEx
//     0x7F,       // Real-Time Universal SysEx ID
//     0x7F,       // Device ID (7F = all devices)
//     0x03,       // Sub-ID #1 (MIDI Time Code)
//     0x01,       // Sub-ID #2 (Full Message)
//     (byte)bpm,  // BPM value
//     0xF7        // End of SysEx
//   };
//   MIDI.sendSysEx(sizeof(sysexMessage), sysexMessage, true);
// }
void setup()
{
  MIDI.begin(MIDI_CHANNEL_OFF);
  pinMode(c1, INPUT_PULLUP);
  pinMode(c2, INPUT_PULLUP);
  pinMode(c3, INPUT_PULLUP);
  pinMode(c4, INPUT_PULLUP);
  pinMode(c5, INPUT_PULLUP);
  pinMode(r1, INPUT_PULLUP);
  pinMode(r2, INPUT_PULLUP);
  pinMode(22, OUTPUT);
  // Timer1.initialize(interval);
  // Timer1.attachInterrupt(toggleLED);
  // Timer1.attachInterrupt(sendMidiClock);
  // sendClock = true;
  // sendBPM(120);
}
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


void process_button(int button, int message, int mode)
{
  if (is_pushed == 0 && read_button(button))
  {
    is_pushed = button;
    if (mode == 0)
    {
      if (message == 5)
      {
        mode_alt = !mode_alt;
        return;
      }
      if (mode_alt)
      {

        MIDI.sendProgramChange(message - 1, 1);
      }
      else
      {
        MIDI.sendProgramChange(message + 3, 1);
      }
    }
    else
    {
      if (message == 5)
      {
          MIDI.sendControlChange(64, 127, 1);
          delay(30);
          MIDI.sendControlChange(64, 0, 1);
      }
      else
      {
          MIDI.sendControlChange(convertMessage(message), 127, 1);
      }
        }
  }
}
void reset_button(int r1, int r2)
{
  if (is_pushed == 0)
  {
    return;
  }
  delay(100);
  if (digitalRead(r1) == HIGH && digitalRead(r2) == HIGH)
  {
    is_pushed = 0;
  }
}

// long bpm = 120.0;
// long tempo = 1000.0 / (bpm / 60.0);

// float prevmillis = 0;
// float interval = tempo / 24.0;
// bool ledState = false;
void loop()
{
  // unsigned long currentMillis = millis();
  // if (currentMillis - prevmillis >= interval) {
  //   //save the last time.
  //   prevmillis = currentMillis;
  //   MIDI.sendClock();
  //   digitalWrite(22, ledState);
  //   ledState = !ledState;
  // }
  if (mode_alt)
  {

    digitalWrite(22, HIGH);
  }
  else
  {
    digitalWrite(22, LOW);
  }

  if (digitalRead(r1) == LOW)
  {
    process_button(c1, 1, 0);
    process_button(c2, 2, 0);
    process_button(c3, 3, 0);
    process_button(c4, 4, 0);
    process_button(c5, 5, 0);
    delay(3);
  }
  else if (digitalRead(r2) == LOW)
  {
    process_button(c1, 1, 1);
    process_button(c2, 2, 1);
    process_button(c3, 3, 1);
    process_button(c4, 4, 1);
    process_button(c5, 5, 1);
    delay(3);
  }
  else if (digitalRead(r1) == HIGH && digitalRead(r2) == HIGH)
  {
    reset_button(r1, r2);
  }
}
