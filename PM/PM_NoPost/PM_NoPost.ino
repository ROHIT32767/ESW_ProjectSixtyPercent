#include <Wire.h>

int pm2 = 1, pm10 = 1;
unsigned long previous_loop, previous_10, previous_25, prev_time;

byte command_frame[9] = {0xAA, 0x02, 0x00, 0x00, 0x00, 0x00, 0x01, 0x67, 0xBB};
byte received_data[9];
int sum = 0;

void send_command(byte command)
{
	command_frame[1] = command;
	int sum = command_frame[0] + command_frame[1] + command_frame[2] + command_frame[3] + command_frame[4] + command_frame[5] + command_frame[8];
	int rem = sum % 256;
	command_frame[6] = (sum - rem) / 256;
	command_frame[7] = rem;
	delay(3000);
	Serial.write(command_frame, 9);
}

bool checksum()
{
	sum = int(received_data[0]) + int(received_data[1]) + int(received_data[2]) + int(received_data[3]) + int(received_data[4]) + int(received_data[5]) + int(received_data[8]);
	if (sum == ((int(received_data[6]) * 256) + int(received_data[7])))
	{
		return true;
	}
	else
		return false;
}
void calculate_pm()
{
	int pm2 = int(received_data[4]) * 256 + int(received_data[5]);
	int pm10 = int(received_data[2]) * 256 + int(received_data[3]);
	Serial.println(pm2);
	Serial.println(pm10);
	delay(3000);
}

void PM_setup()
{
	send_command(0x01);
}

void PM_Reading()
{
	delay(5000);
	if (millis() - prev_time > 5000)
	{
		send_command(0x02);
		prev_time = millis();
	}
	if (Serial.available())
	{
		Serial.readBytes(received_data, 9);
		if (checksum())
		{
			calculate_pm();
		}
	}
}

void setup()
{
	Serial.begin(9600);
	PM_setup();
}

void loop()
{
	PM_Reading();
	delay(2000);
}