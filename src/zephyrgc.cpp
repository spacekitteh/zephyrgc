//============================================================================
// Name        : zephyrgc.cpp
// Author      : Sophie Taylor
// Version     : wat
// Copyright   : sup
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

void ReadIMU(char* out,int &length)
{
	//Read serial from here
	return;
}

void Initialise(){}
void ProcessEvents(){}
void ActOnState(){}
int main() {
	cout << "Starting up the guidance :3" << endl;
	Initialise();
	while(true)
	{
		char* imuData = NULL;
		int length = -1;
		ReadIMU(imuData, length);
		if (length == 0)
		{
			cout << "IMU hasn't sent another packet yet, yo" << endl;
		}
		else if (length <= -1)
		{
			cerr << "Something dun gone goofed reading from the IMU!" << endl;
		}
		else
		{
			//Grab kinematic state from IMU here
		}

		ProcessEvents();

		ActOnState();
	}

}
