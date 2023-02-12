#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "dirent.h"
#include "linux/input.h"
#include "fcntl.h"
#include "unistd.h"
#include "evtinput.h"
#include "stdbool.h"

char supported_types[EVT_TYPE_COUNT][64] = {
	"event-mouse",
	"event-kbd",
	"event-joystick",
	"touchscreen-event"};

EvtDevice evt_devices[MAX_EVT_DEVICES] = {0};

int next_id()
{
	for (int i = 0; i < MAX_EVT_DEVICES; i++)
	{
		if (!evt_devices[i].is_enabled)
			return i;
	}

	return -1;
}

bool ends_with(char *haystack, char *needle)
{
	return strncmp(needle, haystack + strlen(haystack) - strlen(needle), strlen(needle)) == 0;
}

void config_evt_device(char *path, int evt_type)
{
	printf("Config %s\n", supported_types[evt_type]);
	
	int fd = open(path, O_RDONLY | O_NONBLOCK);
	if (fd < 0)
	{
		printf("Failed to open input device %s\n", path);
		return;
	}

	int id = next_id();
	if (id >= MAX_EVT_DEVICES)
	{
		printf("Reached max event devices, skipping %s\n", path);
		close(fd);
		return;
	}

	if (id < 0)
	{
		printf("There was an error finding the next available ID in evt_devices\n");
		close(fd);
		return;
	}

	unsigned char evtype_b[EV_MAX / 8 + 1];
	memset(evtype_b, 0, sizeof(evtype_b));

	if (ioctl(fd, EVIOCGBIT(0, EV_MAX), evtype_b) < 0)
	{
		printf("error calling EVIOCGBIT on %s\n", path);
		close(fd);
		return;
	}

	

	printf("  attrs:\n");

	// test all the bits in evtype_b
	for (int yalv = 0; yalv < EV_MAX; yalv++)
	{
		if (evt_test_bit(yalv, evtype_b))
		{
			printf("    ");
			switch (yalv)
			{
			case EV_SYN:
				printf("Sync ");
				break;
			case EV_KEY:
				printf("Key ");
				break;
			case EV_REL:
				printf("Relative ");
				break;
			case EV_ABS:
				printf("Absolute ");
				break;
			case EV_MSC:
				printf("Misc ");
				break;
			case EV_SND:
				printf("Sound ");
				break;
			case EV_REP:
				printf("Repeat ");
				break;
			case EV_FF:
			case EV_FF_STATUS:
				printf("Force feedback ");
				break;
			case EV_PWR:
				printf("Power Management ");
				break;
				;
			default:
				printf("Unknown(0x%04hx) ", yalv);
				break;
			}

			printf("\n");
		}
	}

	unsigned char key_bits[KEY_MAX / 8 + 1];
	ioctl(fd, EVIOCGBIT(EV_KEY, sizeof(key_bits)), &key_bits);

	if (evt_key_check(key_bits, BTN_LEFT))
	{
		printf("Has left button\n");
	}

	if (evt_key_check(key_bits, BTN_TOUCH))
	{
		printf("Has touch\n");
	}

	evt_devices[id].evt_type = evt_type;
	evt_devices[id].fd = fd;
	evt_devices[id].is_enabled = true;
}

void InitEvtDevices()
{
	char path[MAX_FILEPATH_LENGTH] = {0};
	printf("InitEvtDevices\n");
	DIR *d;
	struct dirent *ent;
	d = opendir(DEFAULT_EVDEV_PATH);
	if (d)
	{
		while ((ent = readdir(d)) != NULL)
		{
			int type = -1;
			for (int i = 0; i < EVT_TYPE_COUNT; i++)
			{
				if (ends_with(ent->d_name, supported_types[i]))
				{
					type = i;
				}
			}

			if (type > -1)
			{
				sprintf(path, "%s/%s", DEFAULT_EVDEV_PATH, ent->d_name);
				config_evt_device(path, type);
			}
		}
		closedir(d);
	}
}

void PollEvtDevices(void)
{
	struct input_event event = {0};

	for (int d = 0; d < MAX_EVT_DEVICES; d++)
	{
		if (!evt_devices[d].is_enabled)
		{
			continue;
		}

		while (read(evt_devices[d].fd, &event, sizeof(event)) == sizeof(event))
		{
			switch(event.type)
			{
				case EV_REL:
					//printf("Relative movement\n");
					break;
				case EV_ABS:
					//printf("Absolute movement\n");
					break;
			}
		}
	}
}

void CloseEvtDevices(void)
{
	for (int i = 0; i < MAX_EVT_DEVICES; i++)
	{
		if (evt_devices[i].is_enabled)
		{
			close(evt_devices[i].fd);
			evt_devices[i].evt_type = -1;
			evt_devices[i].is_enabled = false;
		}
	}
}