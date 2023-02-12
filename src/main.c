#include "evtinput.h"
#include "unistd.h"

int main(void)
{
	InitEvtDevices();

	while (true)
	{
		PollEvtDevices();
	}

	CloseEvtDevices();
	return 0;
}