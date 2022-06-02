// #include <midi_Defs.h>
// #include <midi_Settings.h>
// #include <MIDI.h>
// #include <midi_Namespace.h>
// #include <midi_Message.h>
#include <BLEMidi.h>
// #include <Arduino.h>

#define DEBUG 0

#if DEBUG == 1
#define debug(x) Serial.print(x)
#define debugln(x) Serial.println(x)
#else
#define debug(x)
#define debugln(x)
#endif

bool read_button(int button);

void process_button(int button, int message, int button_type = 0, int mode = 0, int secondary = 85);
void pc_button(int button, int pc, int seconday);
void cc_button(int button, int message, int secondary);
void send_bl_midi(int pc, int message_type = 0);
void reset_button(int r1, int r2);