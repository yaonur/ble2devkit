#include "Button.h"

int p_state = 0;
int c_state = 0;
int is_pushed = 0;

bool read_button(int button)
{
	if (digitalRead(button) == LOW)
		return true;
	else
		return false;
}

void process_button(int button, int cc = 0, int pc = 0, int mode = 0, int secondary = 85)
{
	if (is_pushed == 0 && read_button(button))
	{
		Serial.print("button pushed:");
		Serial.println(button);
		if (mode == 0)
		{
			pc_button(button, pc, secondary);
			is_pushed == 1;
			p_state = button;
		}
	}
}

void pc_button(int button, int pc, int secondary)
{
	if (p_state = button)
	{
		send_bl_midi(secondary, 1);
	}
	else
	{
		send_bl_midi(pc, 0);
	}
}

void send_bl_midi(int message, int message_type = 0)
{
	if (!BLEMidiServer.isConnected())
	{
		Serial.println("Not connected");
		return;
	}
	if (message_type == 0)
	{
		BLEMidiServer.programChange(1, message);
	}
	else
	{
		BLEMidiServer.controlChange(1, message, 127);
	}
}