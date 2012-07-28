//============================================================================
// Name        : zephyrgc.cpp
// Author      : Sophie Taylor
// Version     : wat
// Copyright   : sup
// Description : Main program for autopilot
//============================================================================

#include <iostream>
#include <exception>
#include <stdexcept>
#include <cassert>
#include <memory>
#include <system_error>
#include <cstring>

#include "zephyrgc.h"

using namespace std;

void ReadIMU(char* out,int &length)
{
	//Read serial from here
	return;
}

void Initialise(){}
void ProcessEvents(){}
void ActOnState(){}
void ParseIMUData(shared_ptr<KinematicState> state, char* imuData, int length)
{
  assert(sizeof(KinematicState) == length);
  //THIS IS A SUPER FUCKING BAD IDEA
  memcpy(state.get(), (void*)imuData, length);
}
int main() {
	cout << "Starting up the guidance :3" << endl;
	Initialise();
	shared_ptr<KinematicState> state (new KinematicState());
	while(true)
	{
		char* imuData = NULL;
		int length = -1;
		ReadIMU(imuData, length);
		assert(length >= 1);
		if (length == 0)
		{
			cout << "IMU hasn't sent another packet yet, yo" << endl;
		}
		else if (length <= -1)
		{
			cerr << "Something dun gone goofed reading from the IMU!" << endl;
			throw runtime_error("Communication lost with IMU; check cable");
		}
		else
		{
			//Grab kinematic state from IMU here
			ParseIMUData(state, imuData, length);
		}

		if(state->Z <= 0)
		{
			cerr << "Um, height less than zero?";
			throw runtime_error("Height less than zero");
		}

		ProcessEvents();

		ActOnState();
	}

}
