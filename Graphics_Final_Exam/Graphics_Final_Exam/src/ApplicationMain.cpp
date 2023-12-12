#include "GraphicsApplication.h"

int main(int argc, char* argv[])
{
	Debugger::print = true;

	GraphicsApplication application;

	application.InitializeWindow(1366, 728);

	application.Render();

	return -1;
}