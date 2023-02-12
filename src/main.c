#include "raylib.h"
#include "evtinput.h"

int main(void) 
{
	InitWindow(800, 480, "Test Input");

	SetTargetFPS(60);

	InitEvtDevices();

	while (!WindowShouldClose())
	{
		PollEvtDevices();
		BeginDrawing();
		ClearBackground(BLACK);
		DrawText("Test Input", 10, 10, GetFontDefault().baseSize * 5, WHITE);
		DrawFPS(10, 100);
		EndDrawing();
	}

	CloseEvtDevices();

	CloseWindow();
	
	return 0;
}