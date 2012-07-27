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
struct KinematicState
{
	float X;
	float Y;
	float Z;
	float Roll;
	float Pitch;
	float Yaw;
	float Xdot;
	float Ydot;
	float Zdot;
	float Rolldot;
	float Pitchdot;
	float Yawdot;
};
void Initialise(){}
void ProcessEvents(){}
void ActOnState(){}
void ParseIMUData(KinematicState &state, char* imuData, int length)
{

}
int main() {
	cout << "Starting up the guidance :3" << endl;
	Initialise();
	KinematicState state;
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
			ParseIMUData(state, imuData, length);
		}

		ProcessEvents();

		ActOnState();
	}

}
