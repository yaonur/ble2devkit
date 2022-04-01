#include <midi_Defs.h>
#include <midi_Settings.h>
#include <MIDI.h>
#include <midi_Namespace.h>
#include <midi_Message.h>
#include <BLEMidi.h>
#include <Arduino.h>

int p1 = 33;
int p2 = 25;
int p3 = 26;
int p4 = 27;
int p5 = 14;
int c1 = 5;
int c2 = 18;
int c3 = 19;
int c4 = 35;
int c5 = 32;

bool read_button(int button);

void process_button(int button, int cc = 0, int pc = 0, int mode = 0, int seconday = 85);
void pc_button(int button, int pc, int seconday);
void send_bl_midi(int pc, int message_type = 0);