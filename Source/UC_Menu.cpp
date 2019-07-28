#pragma once
//cause we nano bois
#include "stdafx.h"
#include "DContent.h"
#include "shellapi.h"
#include <iostream>
#include "Lists.h"
#include "structs.h"
#include "GUI.h"

//this may make your life a little eaier if you choose to use
void TeleportToClient(int Client)
{
	Vector3 Coords = ENTITY::GET_ENTITY_COORDS(Client, 1);
	if (PED::IS_PED_SITTING_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID()))
		ENTITY::SET_ENTITY_COORDS(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), Coords.x, Coords.y, Coords.z, 1, 0, 0, 1);
	else
		ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), Coords.x, Coords.y, Coords.z, 1, 0, 0, 1);
}
void main() {

//this is only if you want the little notification on the side when it loads
	UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
	UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME("Unknowncheats.me");
  //first 2 lets define the image we call, then a bool on whether we flash or not when it loads, after that is the Icon type
  //Then who is the sender, this case UC, and the subject well it's going to send unknowncheats.me, then a float for the standard duration.
	UI::_SET_NOTIFICATION_MESSAGE_CLAN_TAG_2("CHAR_MP_FM_CONTACT", "CHAR_MP_FM_CONTACT", 1, 8, "~r~UC", "~r~Unknowncheats.me", 1, "Game Hack Forum", 9, 0);
	UI::_DRAW_NOTIFICATION(FALSE, FALSE);
  while(true) {
    Menu::Checks::Controlls();
    //going to make sure to loop any bools that are in the update loop when true
		Features::UpdateLoop();
    static float step = 0.001f;
		switch (Menu::Settings::currentMenu) {
     //first case is going to be our home, our main menu
     case mainmenu:
		{
        Menu::Title("Unknown Cheats"); //your p2c name would typically go here :)
        Menu::Beg("Unknown Cheats Internal"); //The header bar under the header, I use custom headers so this is needed for me, and so users know where they are
        Menu::MenuOption("~b~Self Options", self); //self options in blue, the second arguement is the case we go to when it is clicked, you can find them all in gui.h
        Menu::End("~b~Unknowncheats.me"); //our footer
    }
    break;
    case self:
    {
        Menu::Title("Unknown Cheats"); 
        Menu::Beg("Self Options");
        if (Menu::Option("Commit Suicide")) { Memory::set_value<float>({ OFFSET_PLAYER , OFFSET_ENTITY_HEALTH }, 0); } //structs.h, set the players health to none
        Menu::Toggle("6 Wanted Stars", Features::sixstars_bool, [] { Features::sixstars(Features::sixstars_bool); });
        Menu::Option("Clean Ped", [] { int Ped = PLAYER::PLAYER_PED_ID(); PED::CLEAR_PED_BLOOD_DAMAGE(Ped); PED::RESET_PED_VISIBLE_DAMAGE(Ped); });
        if (Menu::Option("Random Outfit")) { PED::SET_PED_RANDOM_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), true); }
        Menu::End("Control Yourself!"); //our footer
    }
    break;
    }
    Menu::Beg();
		Menu::End();
		WAIT(0);
  }
}
void ScriptMain() {
	srand(GetTickCount());
	main();
}
