#include <Wire.h>

int pm2 = 1, pm10 = 1;
unsigned long previous_loop, previous_10, previous_25, prev_time;

byte command_frame[5] = {0x81, 0x11, 0x6E, 0x01, 0x00};
byte received_data[16];
int sum = 0, rem = 0;

void send_command(byte command1, byte command2)
{
	command_frame[1] = command1;
	command_frame[2] = command2;
	sum = command_frame[0] + command_frame[1] + command_frame[2];
	rem = sum % 256;
	command_frame[3] = (sum - rem) / 256;
	command_frame[4] = rem;
	delay(3000);
	Serial.write(command_frame, 5);
}

bool checksum()
{
	sum = 0;
	for (int i = 0; i < 16; i++)
		sum += int(received_data[i]);

	rem = sum % ((int(command_frame[3]) * 256) + int(command_frame[4]));

	if (rem == 0)
		return true;
	else
		return false;
}

bool checkState()
{
	send_command(0x16, 0x69);

	if (Serial.available())
	{
		Serial.readBytes(received_data, 16);

		if (checksum())
		{
			if (received_data[2] & 1)
				return false;
			else
				return true;
		}
	}

	return false;
}

void calculate_pm()
{
	float pm2 = float(received_data[11]) * 256 + int(received_data[12]) / 10;
	float pm10 = float(received_data[13]) * 256 + int(received_data[14]) / 10;
	delay(3000);
}

void PM_setup()
{
	bool flag = checkState();
	if (!flag)
		send_command(0x15, 0x6A);
}

void PM_Reading()
{
	delay(3000);
	if (millis() - prev_time > 3000)
	{
		send_command(0x11, 0x6E);
		prev_time = millis();
	}

	if (Serial.available())
	{
		Serial.readBytes(received_data, 16);

		if (checksum())
			calculate_pm();
	}
}

void setup()
{
	Serial.begin(115200);
	PM_setup();
}

void loop()
{
	PM_Reading();
}