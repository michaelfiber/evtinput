#ifndef _EVTINPUT_H
#define _EVTINPUT_H 1

#include "stdbool.h"
#include "linux/input.h"

#ifndef MAX_EVT_DEVICES
#define MAX_EVT_DEVICES 10
#endif

#ifndef DEFAULT_EVDEV_PATH
#define DEFAULT_EVDEV_PATH "/dev/input/by-path"
#endif

#define MAX_DEVICE_NAME 256

#ifndef MAX_FILEPATH_LENGTH
// Maximum length for filepaths (Linux PATH_MAX default value)
#define MAX_FILEPATH_LENGTH 4096
#endif

#define EVT_TYPE_MOUSE 0
#define EVT_TYPE_KEYBOARD 1
#define EVT_TYPE_JOYSTICK 2
#define EVT_TYPE_TOUCHSCREEN 3
#define EVT_TYPE_COUNT 4

//"Value", "Min  ", "Max  ", "Fuzz ", "Flat ", "Resolution "

#define EVT_AXIS_VALUE 0
#define EVT_AXIS_MIN 1
#define EVT_AXIS_MAX 2
#define EVT_AXIS_FUZZ 3
#define EVT_AXIS_FLAT 4
#define EVT_AXIS_RES 5
#define EVT_AXIS_PROP_COUNT 6

typedef struct EvtAxis
{
	int props[EVT_AXIS_PROP_COUNT];
} EvtAxis;

typedef struct EvtDevice
{
	bool is_enabled;
	int evt_type;
	int fd;
	bool is_abs;
	EvtAxis *abs_axis[ABS_MISC + 1]
} EvtDevice;

void EvtInitDevices(void);
void EvtPollDevices(void);
void EvtCloseDevices(void);

#endif // _EVTINPUT_H