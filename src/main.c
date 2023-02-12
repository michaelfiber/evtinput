/**
 * @file main.c
 * @author michaelfiber (michael@cubeofb.org)
 * @brief A test program for the evtinput library I am working on.
 * @version 0.1
 * @date 2023-02-12
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "evtinput.h"
#include "unistd.h"

int main(void)
{
<<<<<<< HEAD
	EvtInitDevices();
	while (1)
	{
		EvtPollDevices();
	}
	EvtCloseDevices();
=======
	InitEvtDevices();

	while (true)
	{
		PollEvtDevices();
	}

	CloseEvtDevices();
>>>>>>> 62f8fd026c5210c68ef59b2a919bd149d5399251
	return 0;
}