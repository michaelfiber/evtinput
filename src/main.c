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

int main(void)
{
	EvtInitDevices();
	while (1)
	{
		EvtPollDevices();
	}
	EvtCloseDevices();
	return 0;
}