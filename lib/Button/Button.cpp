#include "Button.h"
#include <MIDI.h>
int p_state = 14;
int c_state = 14;
int is_pushed = 0;


bool read_button(int button)
{
	if (digitalRead(button) == LOW)
		return true;
	else
		return false;
}
void process_button(int button, int message, int button_type, int mode, int secondary)
{
	if (is_pushed == 0 && read_button(button))
	{
		Serial.print("button down:");
		debugln(button);
		if (mode == 0)
		{
			pc_button(button, message, secondary);
			is_pushed = button;
			if (button_type == 0)
			{
				p_state = button;
			}
			MIDI.sendProgramChange(message-1, 1);
		}
		else
		{
			cc_button(button, message, secondary);
			is_pushed = button;
			if (button_type == 1)
			{
				c_state = button;
			}
			MIDI.sendControlChange(convertMessage(message), 127, 1);
		}
	}
}

void pc_button(int button, int message, int secondary)
{
	if (p_state == button)
	{
		send_bl_midi(secondary, 1);
	}
	else
	{
		send_bl_midi(message, 0);
		c_state = 14;
	}
}

void cc_button(int button, int message, int secondary)
{
	if (c_state == button)
	{
		send_bl_midi(secondary, 1);
	}
	else
	{
		send_bl_midi(message, 1);
	}
}
void send_bl_midi(int message, int message_type)
{
	// if (BLEMidiServer.isConnected() == 0)
	// {
	// 	debugln("Not connected");
	// 	debug("message was :");
	// 	debug(message);
	// 	if (message_type == 0)
	// 	{
	// 		debugln(" program change");
	// 	}
	// 	else
	// 	{
	// 		debugln(" control change");
	// 	}
	// }
	// else
	// {

		if (message_type == 0)
		{
			debugln("sending pc");
			debug(message);
			BLEMidiServer.programChange(1, message);
		}
		else
		{
			debugln("sendingcc");
			debug(message);
			BLEMidiServer.controlChange(1, message, 127);

		}
	// }
}
int convertMessage(int message)  {
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
		return 85;
	}
	else
	{
		return 64;
	}
}

void reset_button(int r1, int r2)
{
	if (is_pushed == 0)
	{
		return;
	}
	delay(330);
	if (digitalRead(r1) == HIGH && digitalRead(r2) == HIGH)
	{
		is_pushed = 0;
	}
}