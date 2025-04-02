#include "../../stdafx.h"
#include "CommandLightOn.h"
using namespace std;

int main() {
	print_file_line();

	Light livingRoomLight;
	LightOnCommand livingRoomLightOn(livingRoomLight);
	livingRoomLightOn.execute();

	return 0;
}