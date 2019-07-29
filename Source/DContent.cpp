#include "stdafx.h"
#include "DContent.h"
#include "natives.h"
#include "structs.h"
#include <cmath>
#include <iostream>
#include <cstdio>
//you know those props that drop when you give money, applause here
#define PROP_MONEY_BAG_01 0x113FD533
#define PICKUP_MONEY_CASE 0xCE6FDD6B
#define PROP_POLY_BAG_01 0x9CA6F755

//leave these the b1g alone k thanks
Vector3 addVector(Vector3 vector, Vector3 vector2) {
	vector.x += vector2.x;
	vector.y += vector2.y;
	vector.z += vector2.z;
	vector._paddingx += vector2._paddingx;
	vector._paddingy += vector2._paddingy;
	vector._paddingz += vector2._paddingz;
	return vector;
}
double DegreeToRadian(double n) {
	return n * 0.017453292519943295;
}
Vector3 RotationToDirection(Vector3 rot) {
	double num = DegreeToRadian(rot.z);
	double num2 = DegreeToRadian(rot.x);
	double val = cos(num2);
	double num3 = abs(val);
	rot.x = (float)(-(float)sin(num) * num3);
	rot.y = (float)(cos(num) * num3);
	rot.z = (float)sin(num2);
	return rot;

}
Vector3 multiplyVector(Vector3 vector, float inc) {
	vector.x *= inc;
	vector.y *= inc;
	vector.z *= inc;
	vector._paddingx *= inc;
	vector._paddingy *= inc;
	vector._paddingz *= inc;
	return vector;
}
//Everything in here will be contiuously looped, when it is true here is an example
//You want to do the bool by the void, easy enough right: test_bool ? test(true) : NULL;
//If this is true we continuously loop the void, if its false then just do nothing
void Features::UpdateLoop()
{
   //self options
  	sixstars_bool ?sixstars(true) : NULL; // give player "6 stars"
	Neverwanted ? neverwanted(true) : NULL; //never wanted, using memory
	
}

//our first example
//define both in DContent.h, the bool as extern bool sixstar_bool, the void as void sixstar(bool toggle)
//make sure to put the proper parameters maybe you aren't using bool toggle or you renamed it
bool Features::sixstars_bool = false;
void Features::sixstars(bool toggle)
{
//if this is true we want to make good use of set fake wanted level
	if (toggle == true)
	{
		GAMEPLAY::SET_FAKE_WANTED_LEVEL(6);
	}
//if its not then why bother
	else
	{
		GAMEPLAY::SET_FAKE_WANTED_LEVEL(0);
	}
}
//in this example lets edit memory to make never wanted, lets do so like this:
bool Features::Neverwanted = false; //lets have the bool set to false first
void Features::neverwanted(bool toggle)
{	//while this is toggles we are going to be taking the local player, getting info and in this case the wanted level, and lets set it 
	//to 0, and loop so that you are not wanted, the offsets are updated so this will work
	Memory::set_value<int>({ OFFSET_PLAYER, OFFSET_PLAYER_INFO, OFFSET_PLAYER_INFO_WANTED }, 0);
}
bool Features::userHotkey = false;
