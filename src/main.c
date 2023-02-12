#include "evtinput.h"

int main(void) 
{
	InitEvtDevices();
	PollEvtDevices();
	CloseEvtDevices();
	return 0;
}