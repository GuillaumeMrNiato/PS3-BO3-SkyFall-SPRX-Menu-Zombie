#include "stdafx.h"
#include "PS3.h"
#include "Lib.h"
#include "Var.h"
#include "Auth.h"
#include <cellstatus.h>
#include <sysutil\sysutil_msgdialog.h>
#include <sysutil\sysutil_oskdialog.h>
#include <sysutil\sysutil_oskdialog_ext.h>
#include "Huds.h"


typedef long long __int64;
float BlueLight[4] = { 0.024, 0.251, 0.745, 1 };
float BlackLowAlpha[4] = { 0, 0, 0, 0.6};
float BlackMedAlpha[4] = { 0, 0, 0, 0.7 };
float je_sais_pas[4] = { 15, 214, 0, 0.6 };
float lol[3] = { 0, 250, 154 };
int maxOptions = 40;
bool OpenOption = false;
int submenuLevel;
int lastSubmenu[20];
int lastOption[20];
bool isOpen, isLoaded, print, storeText, isInGame;
int optionCount;
int submenu = 0;
enum Submenus
{
	Closed,
	Main_Menu,
	PlayerOptions,
	OnlinePlayers,
	AllPlayers,
	Player_Options,
	MoreOptionsOnline,
	Weapons1,
	Weapons2,
	CamoSub,
	Teleports_Evac,
	TeleportsAquarium,
	TeleportsExodus,
	TeleportsHunted,
	TeleportsHavoc,
	TeleportsMetro,
	TeleportsRedwood,
	TeleportsCombine,
	TeleportsBreach,
	Round,
	NoHost,
	Stats,
	Settings,
	Color_Title,
	AllClients,
	Shadow,
	Der,
	Shadow2,
	Der2,
	Shadowclients,
	Der2clients,
	Clients,
	weapons2clients,
	Shadow2clients,
	Der2weapons,
	weaponsac,
	shadowsac,
	derac,
	Giant,
	giantac,
	Giant2,
	Giant2weapons,
};
bool squarePress = false;
bool fastLeftPress = false;
bool leftPress = false;
bool fastRightPress = false;
bool rightPress = false;
int currentOption;
void OpenMenu()
{
	//Show Huds
	Purple[3] = 1;
	White[3] = 1;
	Black[3] = .7;
	//Slide Animation
	for(float i = -200; i <= 1 ;i+= 5)
    {
		Defx = i;
		sleep(5);
	}
	//Open Print
	Print("^6Menu ^2Opened");
	//Enables Menu Controls
	Open = true;
	sleep(50);
}
void CloseMenu()
{
	//Slide Animation
	for(float i = 1; i >= -200;i-= 5)
    {
		Defx = i;
		sleep(5);
	}
	//Hide Huds
	Purple[3] = 0;
	White[3] = 0;
	Black[3] = 0;
	//Close Print
	Print("^5Menu ^1Closed");
	//Disable & Reset Menu Controls
	Open = false;
	ScrollIndex = 0;
	ScrollPos = 160;
	sleep(50);
}
void ScrollDown()
{
	if (ScrollIndex == 19)//5 = max
	{
	   ScrollIndex = 0;
	}
	else
	{
		ScrollIndex = ScrollIndex + 1;  
	}
	ScrollPos = (ScrollIndex * 30) + ScrollDefault;
	sleep(50);
}
void ScrollUp()
{
	if (ScrollIndex == 0)
	{
		ScrollIndex = 13;//5 = max
	}
	else
	{
		ScrollIndex = ScrollIndex - 1;  
	}
	ScrollPos = (ScrollIndex * 30) + ScrollDefault;
	sleep(50);
}
void SelectOption()
{
	
}

void my_dialog2(int button, void *userdata)
{
      switch(button)
      {
       case CELL_MSGDIALOG_BUTTON_OK:
       case CELL_MSGDIALOG_BUTTON_NONE:
       case CELL_MSGDIALOG_BUTTON_ESCAPE:
       break;
       default:
	   break;
	  }
}

void Menu(uint64_t)
{
	sleep(20000);
	for (;;)
	{
		sleep(60);
		if (isInGame)
			{
				if (submenu == Closed)
				{
					if (ButtonMonitor::Pressed(ButtonMonitor::R3))
					{
						submenu = Main_Menu;
						submenuLevel = 0;
						currentOption = 1;
						Open = true;
						OpenMenu();
						sleep(100);
					}
				}
				else {
					if (ButtonMonitor::Pressed(ButtonMonitor::R3))
					{
						if (submenu == Main_Menu)
						{
							submenu = Closed;
							Open = false;
							CloseMenu();
						}
						else {
							submenu = lastSubmenu[submenuLevel - 1];
							currentOption = lastOption[submenuLevel - 1];
							submenuLevel--;

						}
						sleep(100);
					}
					else if (ButtonMonitor::Pressed(ButtonMonitor::Square))
					{
						OpenOption = true;
						sleep(100);
					}
					else if (ButtonMonitor::Pressed(ButtonMonitor::Up))
					{
						currentOption--;
						if (currentOption < 1)
						{
							currentOption = optionCount;
						}
						sleep(100);
					}
					else if (ButtonMonitor::Pressed(ButtonMonitor::Down))
					{
						currentOption++;
						if (currentOption > optionCount)
						{
							currentOption = 1;
						}
						ScrollDown();
						sleep(100);

					}
					
					sleep(30);
				}
			}
		//}
		else submenu = Closed;
	}
}


__int64 hookStub(int timeID){
	__asm("li %r3, 0x3");
}
float scroller[4] = { 1, 1, 0, 0.8 };
float* mInfoBarText = scroller;
void addTitle(char *title)
{
	//drawText("^0You Are Host", 1050, 50, "fonts/smallFont", 1.10, BlueLight);//if Host
	DrawText("^5SkyFall Menu ^6By ^1MrNiato\n^2Version : 1.08\n\n", 388, 100, "fonts/boldfont", 1.14, Purple);//Title Menu
	DrawShader(360, 0, 570, 1200, Black,"white");//Background
	DrawShader(360, 0, 570, 200, lol, "white");//Title Shader
	///
	DrawShader(360, 0, 570, 40, je_sais_pas,"white");//High
	DrawShader(360, 150, 570, 15, je_sais_pas,"white");//High
	DrawShader(360, 870, 570, 40, je_sais_pas,"white");//Down_Haut
	DrawShader(360, 1035, 570, 40, je_sais_pas,"white");//Down
	DrawShader(360, 40, 10, 995, je_sais_pas,"white");//Coter Gauche
	DrawShader(930, 0, 10, 1075, je_sais_pas,"white");//Coter Droit
	DrawText("^5SkyFall Menu By ^1MrNiato\n^7www.^5allcodrecovery^7.com\nThanks to : ^3Indie Developer", 415, 960, "fonts/smalldevfont", 1.6, mInfoBarText);//Credits Menu
}
char *infoText;
void AddOption(char *option, char *info)
{
	optionCount++;
	if (currentOption == optionCount)
		infoText = info;
	if (currentOption <= maxOptions && optionCount <= maxOptions)
		DrawText(option, 390, 210 + (optionCount * 35), "fonts/normalfond", 1.10, je_sais_pas);
	else if ((optionCount > (currentOption - maxOptions)) && optionCount <= currentOption)
		DrawText(option, 390, (((currentOption - maxOptions)), 210 + (optionCount * 35)), "fonts/normalfond", 1.10, White);
}
void addOption(char * Option, char* null)
{

	AddOption(Option, null);
	if (optionCount == currentOption)
	{

	}
	else DrawText(Option, 390, 210 + (optionCount * 35), "fonts/normalfond", 1.10, White);


}
int changeSubmenu(int newSubmenu)
{
	lastSubmenu[submenuLevel] = submenu;
	lastOption[submenuLevel] = currentOption;
	currentOption = 1;
	submenu = newSubmenu;
	submenuLevel++;
}
void addSubmenuOption(char *option, int newSubmenu, char *info)
{
		addOption(option, info);
		if (currentOption == optionCount && OpenOption)
			changeSubmenu(newSubmenu);
}
void Toggle(char* Stat)
{

	if (currentOption <= maxOptions && optionCount <= maxOptions)
		DrawText(Stat, 810, 250 + (optionCount * 35), "fonts/normalfond", 1.10, White);
	else if ((optionCount > (currentOption - maxOptions)) && optionCount <= currentOption)
		DrawText(Stat, 810, (((currentOption - maxOptions)), 250 + (optionCount * 35)), "fonts/normalfond", 1.10, White);
}
int getOption()
{
	if (OpenOption)
	{
		return currentOption;
	}
	else return 0;
}
void addBoolOption(char *option, bool b00l, char *info)
{
	char buf[50];
	if (b00l)
	{
		Toggle("^5Enabled");
		addOption(option, info);
	}
	else
	{
		Toggle("^1Disabled");
		addOption(option, info);
	}
}
bool GodMode;
bool Speedx2;
bool FakeLag;
bool Freeze;
bool hud;
bool spectator;
bool Third;
bool forcehost;
bool GodModeAC;
bool Speedx2AC;
bool FakeLagAC;
bool FreezeAC;
bool hudAC;
bool ThirdAC;
bool AmmoAC;
bool perks;
bool perksac;
bool specac;
bool notargetAC;
char* GetName(int ClientNum)
	 {
	  char* Name = ReadString(static_cast<unsigned int>(0x18CA098 + (0x61E0 * ClientNum)));
	  char* Name2 = ReadString(static_cast<unsigned int>(0x18CA098 + (0x61E0 * ClientNum)));
	  if (!strcmp(Name, "") && !strcmp(Name2, ""))
	  {
		  return "Not Connected";
	  }
	  else
	  {
		  return Name;
	  }
		 return;

	 }
  char* GetClientName(int Client)
  {
	  char* Names[4];
	  Names[Client] = ReadString((0x18CA098 + (0x61E0 * Client)));
	  if (Names[Client] == "")
	  {
		  Names[Client] = "Not Connected";
	  }
	  return Names[Client];
  }
int G_Client(int client)
{
	return 0x18C42E8 + (client * 0x61E0);
}
/*
Prestige : 0x37DDE5D8
Level : 0x37DDE57A
*/
  int selectedPlayer;
  __int64 ForceHost(int TimeId)
{
   cBuf_AddText(0, "partyMigrate_disabled 1");
   cBuf_AddText(0, "party_minplayers 1");	
   cBuf_AddText(0, "allowAllNAT 1");	
   cBuf_AddText(0, "party_connectToOthers 0");	
   cBuf_AddText(0, "party_maxplayers 4");	
}
  void WriteBytes(int address, char* input, int length)
	{
		for (int i = 0; i < length; i++)
		{
			*(char*)(address + (i)) = input[i];
		}
	}
__int64 Hook(int TimeId)
{
		*(int*)0x61A154 = 0x60000000;
	    *(int*)0x622DA4 = 0x60000000;
	    *(int*)0x622DCC = 0x38600000;
		*(int*)0x622D8C = 0x60000000;
	    *(int*)0x622DA4 = 0x60000000;
	    *(int*)0x622DBC = 0x38600000;
		*(int*)0x7B68E4 = 0x60000000;
	    *(int*)0x7B68EC = 0x60000000;
		*(int*)0x7B6910 = 0x60000000;
	    *(int*)0x7B6918 = 0x60000000;
		*(int*)0x7B692C = 0x60000000;
		*(int*)0x7B61A4 = 0x60000000;
		*(int*)0x7B61B4 = 0x60000000;
		*(int*)0x7B61CC = 0x60000000;
		// DrawText("^5SkyFall Menu Made By ^1MrNiato\n^7www.^5allcodrecovery^7.com\nThanks to : ^3Indie Developer", 900, 980, "fonts/smallFont", 1.14, BlueLight);//Credits Menu
	if (InGame() == true)
	{
			isInGame = true;
			optionCount = 0;
			switch (submenu)
			{
#pragma region Main Menu
			case Main_Menu:
				addTitle("^2By MrNiato");
				addSubmenuOption("Self Menu", PlayerOptions, NULL);
				addSubmenuOption("Primary Weapons Menu", Weapons1, NULL);
				addSubmenuOption("Secondary Weapons Menu", Weapons2, NULL);
				addSubmenuOption("Camos Menu", CamoSub, NULL);
				addSubmenuOption("Round Menu", Round, NULL);
				addSubmenuOption("Stats Menu", Stats, NULL);
				addSubmenuOption("Clients Menu", Clients, NULL);
				addSubmenuOption("All Clients Menu", AllClients, NULL);
				break;
#pragma endregion
				//All Perks : 018C4954
#pragma region Player Options
			case PlayerOptions:
				addTitle("^2Self Menu");
				addBoolOption("God Mode", GodMode, NULL);
				addBoolOption("Unlimited Ammo", Ammo, NULL);
				addOption("Max Points",  NULL);
				addBoolOption("Speed x2", Speedx2, NULL);
				addBoolOption("Fake Lag", FakeLag, NULL);
				addBoolOption("Freeze", Freeze, NULL);
				addBoolOption("Third Person", Third, NULL);
				addBoolOption("No Target", notarget, NULL);
				addBoolOption("Remove HUD", hud, NULL);
				addBoolOption("All Perks", perks, NULL);
				addBoolOption("Become Spectator", spectator, NULL);
				switch (getOption())
				{
				case 1:
					GodMode = !GodMode;
					if (GodMode == true)
					{
						*(int*)(G_Client(0) + 0x23) = 0x05000000;	
					}
					else if (GodMode == false)
					{
						*(int*)(G_Client(0) + 0x23) = 0x04000000;
					}
					break;
				case 2:
					Ammo = !Ammo;
					if (Ammo == true)
					{
						*(int*)(G_Client(0) + 0x57A) = 0x7fffffff;
						*(int*)(G_Client(0) + 0x53E) = 0x7fffffff;
						*(int*)(G_Client(0) + 0x582) = 0x7fffffff;
						*(int*)(G_Client(0) + 0x546) = 0x7fffffff;
						*(int*)(G_Client(0) + 0x57C) = 0x7fffffff;				
					}
					else if (Ammo == false)
					{
						*(int*)(G_Client(0) + 0x57A) = 0x00000000;
						*(int*)(G_Client(0) + 0x53E) = 0x00000000;
						*(int*)(G_Client(0) + 0x582) = 0x00000000;
						*(int*)(G_Client(0) + 0x546) = 0x00000000;
						*(int*)(G_Client(0) + 0x57C) = 0x00000000;	
					}
					break;
					case 3:
				        *(int*)(G_Client(0) + 0x5EB5) = 0x7fffffff;
					break;
					case 4:
				    Speedx2 = !Speedx2;
					if (Speedx2 == true)
					{
						*(int*)(0x18CA0E0) = 0x3fff0000;				
					}
					else if (Speedx2 == false)
					{
						*(int*)(0x18CA0E0) = 0x3f800000;
					}
					break;
					case 5:
					FakeLag = !FakeLag;
					if (FakeLag == true)
					{
						*(int*)(G_Client(0) + 0x5D27) = 0x01000000;				
					}
					else if (FakeLag == false)
					{
						*(int*)(G_Client(0) + 0x5D27) = 0x02000000;
					}
					break;
					case 6:
					Freeze = !Freeze;
					if (Freeze == true)
					{
						*(int*)(G_Client(0) + 0x130) = 0x10010101;				
					}
					else if (Freeze == false)
					{
						*(int*)(G_Client(0) + 0x130) = 0x01010101;
					}
					break;
					case 7:
					Third = !Third;
					if (Third == true)
					{
						*(int*)(G_Client(0) + 0x12C) = 0x00010000;				
					}
					else if (Third == false)
					{
						*(int*)(G_Client(0) + 0x12C) = 0x00000000;		
					}
					break;
					case 8:
					notarget = !notarget;
					if (notarget == true)
					{
						*(int*)(G_Client(0) + 0x5DE5) = 0xff006400;				
					}
					else if (notarget == false)
					{
						*(int*)(G_Client(0) + 0x5DE5) = 0x00006400;
					}
					break;
					case 9:
					hud = !hud;
					if (hud == true)
					{
						*(int*)(G_Client(0) + 0x5EFF) = 0x00000000;				
					}
					else if (hud == false)
					{
						*(int*)(G_Client(0) + 0x5EFF) = 0x03000000;
					}
					break;
					case 10:
					perks = !perks;
					if (perks == true)
					{
						*(int*)(G_Client(0) + 0x66C) = 0x2A802718;
						*(int*)(G_Client(0) + 0x670) = 0x04C00155;				
					}
					else if (perks == false)
					{
						*(int*)(G_Client(0) + 0x66C) = 0x00000000;
						*(int*)(G_Client(0) + 0x670) = 0x00000000;		
					}
					break;
					case 11:
					spectator = !spectator;
					if (spectator == true)
					{
						*(int*)(G_Client(0) + 0x23) = 0x07000000;
					}
					else if (spectator == false)
					{
					if (GodMode == true)
					{
						*(int*)(G_Client(0) + 0x23) = 0x05000000;				
					}
					else if (GodMode == false)
					{
						*(int*)(G_Client(0) + 0x23) = 0x04000000;
					}
					}
					break;
					case 12:
					forcehost = !forcehost;
					if (forcehost == true)
					{
						ForceHost(500);
					}
					else if (forcehost == false)
					{
						ForceHost(500000);
						cBuf_AddText(0, "party_minplayers 1");	
						cBuf_AddText(0, "allowAllNAT 1");	
						cBuf_AddText(0, "party_connectToOthers 0");	
						cBuf_AddText(0, "party_maxplayers 10");	
					}
					break;
				}

				break;
#pragma endregion
#pragma region LOL
              case Weapons1:
				addTitle("Primary Weapons Menu");
				addOption("Default Weapons", NULL);
				addOption("Vesper", NULL);
				addOption("VMP", NULL);
				addOption("Kuda", NULL);
				addOption("Infernus", NULL);
				addOption("The Impaler", NULL);
				addOption("Shadow Of Evils Weapons", NULL);
				addOption("Der Eisendrache Weapons", NULL);
				addOption("The Giant Weapons", NULL);
				switch (getOption())
				{
				case 1:
					*(int*)(G_Client(0) + 0x30B) = 0x01000000;
					break;
				case 2:
					*(int*)(G_Client(0) + 0x30B) = 0x02000000;
					break;
				case 3:
					*(int*)(G_Client(0) + 0x30B) = 0x04000000;
					break;
				case 4:
					*(int*)(G_Client(0) + 0x30B) = 0x06000000;
					break;
			    case 5:
					*(int*)(G_Client(0) + 0x30B) = 0x12000000;
					break;
                case 6:
					*(int*)(G_Client(0) + 0x30B) = 0x15000000;
					break;
				case 7:
					changeSubmenu(Shadow);
					break;
				case 8:
					changeSubmenu(Der);
					break;
				case 9:
					changeSubmenu(Giant);
					break;
				}
				break;
				case Shadow:
				addTitle("Shadows Weapons Menu");
				addOption("Mar-Astagua-Arbgwaoth", NULL);
				addOption("Nar-Ullaqua-Arbgwaoth", NULL);
				addOption("Lor-Zarozzor-Arbgwaoth", NULL);
				addOption("Weapon_Interdimensional_Gun", NULL);
				switch (getOption())
				{
				case 1:
					*(int*)(G_Client(0) + 0x30B) = 0x80000000;
					break;
				case 2:
					*(int*)(G_Client(0) + 0x30B) = 0x81000000;
					break;
				case 3:
					*(int*)(G_Client(0) + 0x30B) = 0x82000000;
					break;
				case 4:
					*(int*)(G_Client(0) + 0x30B) = 0x83000000;
					break;
				}
				break;
				case Der:
				addTitle("Einsendrache Weapons Menu");
				addOption("Wrath of the Ancients", NULL);
				addOption("Kreegakaleet lu Gosata'ahm", NULL);
				addOption("Kreeaho'ahm nal Ahmhogaroc", NULL);
				addOption("Kreeaho'ahm nal Ahmahm", NULL);
				addOption("Kreeaholo lu Kreemasaleet", NULL);
				addOption("Death Machine", NULL);
				switch (getOption())
				{
				case 1:
					*(int*)(G_Client(0) + 0x30B) = 0x76000000;
					break;
				case 2:
					*(int*)(G_Client(0) + 0x30B) = 0x79000000;
					break;
				case 3:
					*(int*)(G_Client(0) + 0x30B) = 0x7D000000;
					break;
				case 4:
					*(int*)(G_Client(0) + 0x30B) = 0x83000000;
					break;
				case 5:
					*(int*)(G_Client(0) + 0x30B) = 0x89000000;
					break;
                case 6:
					*(int*)(G_Client(0) + 0x30B) = 0x95000000;
					break;
				}
				break;
				case Giant:
				addTitle("The Giant Weapons Menu");
				addOption("RayGun", NULL);
				addOption("Wunderwaffe DG-2", NULL);
				addOption("Wunderwaffe DG-3 JZ", NULL);
				switch (getOption())
				{
				case 1:
					*(int*)(G_Client(0) + 0x30B) = 0x75000000;
					break;
				case 2:
					*(int*)(G_Client(0) + 0x30B) = 0x78000000;
					break;
				case 3:
					*(int*)(G_Client(0) + 0x30B) = 0x77000000;
					break;
				}
				break;
#pragma endregion
#pragma region Map Changer
			case Weapons2:
				//0x18C4643
				addTitle("Primary Weapons Menu");
				addOption("Default Weapons", NULL);
				addOption("Vesper", NULL);
				addOption("VMP", NULL);
				addOption("Kuda", NULL);
				addOption("Infernus", NULL);
				addOption("The Impaler", NULL);
				addOption("Shadow Of Evils Weapons", NULL);
				addOption("Der Eisendrache Weapons", NULL);
				addOption("The Giant Weapons", NULL);
				switch (getOption())
				{
				case 1:
					*(int*)(G_Client(0) + 0x35B) = 0x01000000;
					break;
				case 2:
					*(int*)(G_Client(0) + 0x35B) = 0x02000000;
					break;
				case 3:
					*(int*)(G_Client(0) + 0x35B) = 0x04000000;
					break;
				case 4:
					*(int*)(G_Client(0) + 0x35B) = 0x06000000;
					break;
			    case 5:
					*(int*)(G_Client(0) + 0x35B) = 0x12000000;
					break;
                case 6:
					*(int*)(G_Client(0) + 0x35B) = 0x15000000;
					break;
				case 7:
					changeSubmenu(Shadow2);
					break;
				case 8:
					changeSubmenu(Der2);
					break;     
				case 9:
					changeSubmenu(Giant2);
					break;     
				}
				break;
				case Shadow2:
				addTitle("Shadows Weapons Menu");
				addOption("Mar-Astagua-Arbgwaoth", NULL);
				addOption("Nar-Ullaqua-Arbgwaoth", NULL);
				addOption("Lor-Zarozzor-Arbgwaoth", NULL);
				addOption("Weapon_Interdimensional_Gun", NULL);
				switch (getOption())
				{
				case 1:
					*(int*)(G_Client(0) + 0x35B) = 0x80000000;
					break;
				case 2:
					*(int*)(G_Client(0) + 0x35B) = 0x81000000;
					break;
				case 3:
					*(int*)(G_Client(0) + 0x35B) = 0x82000000;
					break;
				case 4:
					*(int*)(G_Client(0) + 0x35B) = 0x83000000;
					break;
				}
				break;
				case Der2:
				addTitle("Einsendrache Weapons Menu");
				addOption("Wrath of the Ancients", NULL);
				addOption("Kreegakaleet lu Gosata'ahm", NULL);
				addOption("Kreeaho'ahm nal Ahmhogaroc", NULL);
				addOption("Kreeaho'ahm nal Ahmahm", NULL);
				addOption("Kreeaholo lu Kreemasaleet", NULL);
				addOption("Death Machine", NULL);
				switch (getOption())
				{
				case 1:
					*(int*)(G_Client(0) + 0x35B) = 0x76000000;
					break;
				case 2:
					*(int*)(G_Client(0) + 0x35B) = 0x79000000;
					break;
				case 3:
					*(int*)(G_Client(0) + 0x35B) = 0x7D000000;
					break;
				case 4:
					*(int*)(G_Client(0) + 0x35B) = 0x83000000;
					break;
				case 5:
					*(int*)(G_Client(0) + 0x35B) = 0x89000000;
					break;
				case 6:
					*(int*)(G_Client(0) + 0x35B) = 0x95000000;
					break;

				}
				break;
				case Giant2:
				addTitle("The Giant Weapons Menu");
				addOption("RayGun", NULL);
				addOption("Wunderwaffe DG-2", NULL);
				addOption("Wunderwaffe DG-3 JZ", NULL);
				switch (getOption())
				{
				case 1:
					*(int*)(G_Client(0) + 0x35B) = 0x75000000;
					break;
				case 2:
					*(int*)(G_Client(0) + 0x35B) = 0x78000000;
					break;
				case 3:
					*(int*)(G_Client(0) + 0x35B) = 0x77000000;
					break;
				}
				break;
#pragma endregion
#pragma region Round
			case CamoSub:
				addTitle("Camo Menu");
				addOption("First", NULL);
				addOption("Seconds", NULL);
				addOption("Third", NULL);
				addOption("Four", NULL);
				addOption("Five", NULL);
				addOption("Six", NULL);
				addOption("Seven", NULL);
				addOption("Eight", NULL);
				addOption("Nine", NULL);
				addOption("Ten", NULL);
				addOption("Dark Metter", NULL);
				addOption("Girl", NULL);
				switch (getOption())
				{
				case 1:
					*(int*)(G_Client(0) + 0x311) = 0x01000000;
					break;
				case 2:
					*(int*)(G_Client(0) + 0x311) = 0x02000000;
					break;
				case 3:
					*(int*)(G_Client(0) + 0x311) = 0x03000000;
					break;
				case 4:
					*(int*)(G_Client(0) + 0x311) = 0x04000000;
					break;
				case 5:
					*(int*)(G_Client(0) + 0x311) = 0x05000000;
					break;
				case 6:
					*(int*)(G_Client(0) + 0x311) = 0x06000000;
					break;
				case 7:
					*(int*)(G_Client(0) + 0x311) = 0x07000000;
					break;
				case 8:
					*(int*)(G_Client(0) + 0x311) = 0x08000000;
					break;
				case 9:
					*(int*)(G_Client(0) + 0x311) = 0x09000000;
					break;
				case 10:
					*(int*)(G_Client(0) + 0x311) = 0x0A000000;
					break;
				case 11:
					*(int*)(G_Client(0) + 0x311) = 0x11000000;
					break;
				case 12:
					*(int*)(G_Client(0) + 0x311) = 0x0C000000;
					break;
				}

				break;
				case Round:
				addTitle("Round Menu");
				addOption("Change Round to 9", NULL);
				addOption("Change Round to 16", NULL);
				addOption("Change Round to 25", NULL);
				addOption("Change Round to 41", NULL);
				addOption("Change Round to 57", NULL);
				addOption("Change Round to 89", NULL);
				switch (getOption())
				{
				case 1:
					*(int*)0x174A2AF = 0x09000000;
					break;
				case 2:
					*(int*)0x174A2AF = 0x10000000;
					break;
				case 3:
					*(int*)0x174A2AF = 0x19000000;
					break;
				case 4:
					*(int*)0x174A2AF = 0x29000000;
					break;
				case 5:
					*(int*)0x174A2AF = 0x39000000;
					break;
			   case 6:
					*(int*)0x174A2AF = 0x59000000;
					break;
				}

				break;
#pragma endregion
#pragma region Settings
			case Stats:
				addTitle("Stats Menu");
				addOption("Prestige 1", NULL);
				addOption("Prestige 2", NULL);
				addOption("Prestige 3", NULL);
				addOption("Prestige 4", NULL);
				addOption("Prestige 5", NULL);
				addOption("Prestige 6", NULL);
				addOption("Prestige 7", NULL);
				addOption("Prestige 8", NULL);
				addOption("Prestige 9", NULL);
				addOption("Prestige 10", NULL);
				addOption("Prestige 11", NULL);
				addOption("Level 35", NULL);
				switch (getOption())
				{
				case 1:
					char Prestige1[] = { 0x01 };
					WriteBytes(0x37DDE5D8, Prestige1, sizeof(Prestige1));
					break;
				case 2:
					char Prestige2[] = { 0x02 };
					WriteBytes(0x37DDE5D8, Prestige2, sizeof(Prestige2));
					break;
				case 3:
					char Prestige3[] = { 0x03 };
					WriteBytes(0x37DDE5D8, Prestige3, sizeof(Prestige3));
					break;
				case 4:
					char Prestige4[] = { 0x04 };
					WriteBytes(0x37DDE5D8, Prestige4, sizeof(Prestige4));
					break;
				case 5:
					char Prestige5[] = { 0x05 };
					WriteBytes(0x37DDE5D8, Prestige5, sizeof(Prestige5));
					break;
				case 6:
					char Prestige6[] = { 0x06 };
					WriteBytes(0x37DDE5D8, Prestige6, sizeof(Prestige6));
					break;
				case 7:
					char Prestige7[] = { 0x07 };
					WriteBytes(0x37DDE5D8, Prestige7, sizeof(Prestige7));
					break;
				case 8:
					char Prestige8[] = { 0x08 };
					WriteBytes(0x37DDE5D8, Prestige8, sizeof(Prestige8));
					break;
				case 9:
					char Prestige9[] = { 0x09 };
					WriteBytes(0x37DDE5D8, Prestige9, sizeof(Prestige9));
					break;
				case 10:
					char Prestige10[] = { 0x0A };
					WriteBytes(0x37DDE5D8, Prestige10, sizeof(Prestige10));
					break;
				case 11:
				   char Prestige11[] = { 0x0B };
					WriteBytes(0x37DDE5D8, Prestige11, sizeof(Prestige11));
					break;
				case 12:
					char Level[] = { 0x21 };
					WriteBytes(0x37DDE57A, Level, sizeof(Level));
					break;
				}
				break;
			case Clients:
				addTitle("Clients Menu");
				addOption(GetName(0), NULL);
				addOption(GetName(1), NULL);
				addOption(GetName(2), NULL);
				addOption(GetName(3), NULL);
				if (OpenOption)
				{
					selectedPlayer = currentOption - 1;
					changeSubmenu(Player_Options);
				}
				break;
				#pragma region Player Options
			case Player_Options:
				addTitle("Clients Menu");
				addOption("God Mode", NULL);
				addOption("Unlimited Ammo", NULL);
				addOption("Max Money", NULL);
				addOption("All Perks", NULL);
				addOption("Give Weapons", NULL);
				switch (getOption())
				{
				case 1:
					*(char*)(G_Client(selectedPlayer) + 0x23 + (selectedPlayer * 0x61E0)) = 0x05000000;
					break;
				case 2:
					*(char*)(G_Client(selectedPlayer) + 0x57A + (selectedPlayer * 0x61E0)) = 0x7fffffff;
					*(char*)(G_Client(selectedPlayer) + 0x53E + (selectedPlayer * 0x61E0)) = 0x7fffffff;
					*(char*)(G_Client(selectedPlayer) + 0x582 + (selectedPlayer * 0x61E0)) = 0x7fffffff;
					*(char*)(G_Client(selectedPlayer) + 0x546 + (selectedPlayer * 0x61E0)) = 0x7fffffff;
					break;
				case 3:
					*(char*)(G_Client(selectedPlayer) + 0x5EB5 + (selectedPlayer * 0x61E0)) = 0x7fffffff;
					break;
				case 4:
					*(char*)(G_Client(selectedPlayer) + 0x66C + (selectedPlayer * 0x61E0)) = 0x2A, 0x80, 0x27, 0x18, 0x04, 0xC0, 0x01, 0x55;
					break;
				case 5:
					changeSubmenu(weapons2clients);
					break;
				}
				break;
				case weapons2clients:
				//0x18C4643
				addTitle("Primary Weapons Menu");
				addOption("Default Weapons", NULL);
				addOption("Vesper", NULL);
				addOption("VMP", NULL);
				addOption("Kuda", NULL);
				addOption("Infernus", NULL);
				addOption("The Impaler", NULL);
				addOption("Shadow Of Evils Weapons", NULL);
				addOption("Der Eisendrache Weapons", NULL);
				addOption("The Giant Weapons", NULL);
				switch (getOption())
				{
				case 1:
					*(int*)(G_Client(selectedPlayer) + 0x30B) = 0x01000000;
					break;
				case 2:
					*(int*)(G_Client(selectedPlayer)+ 0x30B) = 0x02000000;
					break;
				case 3:
					*(int*)(G_Client(selectedPlayer) + 0x30B) = 0x04000000;
					break;
				case 4:
					*(int*)(G_Client(selectedPlayer) + 0x30B) = 0x06000000;
					break;
			    case 5:
					*(int*)(G_Client(selectedPlayer) + 0x30B) = 0x12000000;
					break;
                case 6:
					*(int*)(G_Client(selectedPlayer) + 0x30B) = 0x15000000;
					break;
				case 7:
					changeSubmenu(Shadow2clients);
					break;
				case 8:
					changeSubmenu(Der2weapons);
					break;
				case 9:
					changeSubmenu(Giant2weapons);
					break;
				}
				break;
				case Shadow2clients:
				addTitle("Shadows Weapons Menu");
				addOption("Mar-Astagua-Arbgwaoth", NULL);
				addOption("Nar-Ullaqua-Arbgwaoth", NULL);
				addOption("Lor-Zarozzor-Arbgwaoth", NULL);
				addOption("Weapon_Interdimensional_Gun", NULL);
				switch (getOption())
				{
				case 1:
					*(int*)(G_Client(selectedPlayer) + 0x30B) = 0x80000000;
					break;
				case 2:
					*(int*)(G_Client(selectedPlayer) + 0x30B) = 0x81000000;
					break;
				case 3:
					*(int*)(G_Client(selectedPlayer) + 0x30B) = 0x82000000;
					break;
				case 4:
					*(int*)(G_Client(selectedPlayer) + 0x30B) = 0x83000000;
					break;
				}
				break;
				case Der2weapons:
				addTitle("Einsendrache Weapons Menu");
				addOption("Wrath of the Ancients", NULL);
				addOption("Kreegakaleet lu Gosata'ahm", NULL);
				addOption("Kreeaho'ahm nal Ahmhogaroc", NULL);
				addOption("Kreeaho'ahm nal Ahmahm", NULL);
				addOption("Kreeaholo lu Kreemasaleet", NULL);
				addOption("Death Machine", NULL);
				switch (getOption())
				{
				case 1:
					*(int*)(G_Client(selectedPlayer) + 0x30B) = 0x76000000;
					break;
				case 2:
					*(int*)(G_Client(selectedPlayer) + 0x30B) = 0x79000000;
					break;
				case 3:
					*(int*)(G_Client(selectedPlayer) + 0x30B) = 0x7D000000;
					break;
				case 4:
					*(int*)(G_Client(selectedPlayer) + 0x30B) = 0x83000000;
					break;
				case 5:
					*(int*)(G_Client(selectedPlayer) + 0x30B) = 0x89000000;
					break;
                case 6:
					*(int*)(G_Client(selectedPlayer) + 0x30B) = 0x95000000;
					break;
				}
				break;
				case Giant2weapons:
				addTitle("The Giant Weapons Menu");
				addOption("RayGun", NULL);
				addOption("Wunderwaffe DG-2", NULL);
				addOption("Wunderwaffe DG-3 JZ", NULL);
				switch (getOption())
				{
				case 1:
					*(int*)(G_Client(selectedPlayer) + 0x30B) = 0x75000000;
					break;
				case 2:
					*(int*)(G_Client(selectedPlayer) + 0x30B) = 0x78000000;
					break;
				case 3:
					*(int*)(G_Client(selectedPlayer) + 0x30B) = 0x77000000;
					break;
				}
				break;
#pragma endregion
				case AllClients:
				addTitle("All Clients Menu");
				addBoolOption("God Mode", GodModeAC, NULL);
				addBoolOption("Unlimited Ammo", AmmoAC, NULL);
				addOption("Max Points",  NULL);
				addBoolOption("Speed x2", Speedx2AC, NULL);
				addBoolOption("Fake Lag", FakeLagAC, NULL);
				addBoolOption("Freeze", FreezeAC, NULL);
				addBoolOption("Third Person", ThirdAC, NULL);
				addBoolOption("No Target", notargetAC, NULL);
				addBoolOption("Remove HUD", hudAC, NULL);
				addBoolOption("All Perks", perksac, NULL);
				addBoolOption("Become Spectator", specac, NULL);
				addOption("Give Weapons", NULL);
				switch (getOption())
				{
				case 1:
					GodModeAC = !GodModeAC;
					if (GodModeAC == true)
					{
						*(int*)(0x18C430b) = 0x05000000;
						*(int*)(0x18C430b + 0x61E0) = 0x05000000;
						*(int*)(0x18C430b + 0x61E0 + 0x61E0) = 0x05000000;
						*(int*)(0x18C430b + 0x61E0 + 0x61E0 + 0x61E0) = 0x05000000;
					}
					else if (GodModeAC == false)
					{
						*(int*)(0x18C430b) = 0x04000000;
						*(int*)(0x18C430b + 0x61E0) = 0x04000000;
						*(int*)(0x18C430b + 0x61E0 + 0x61E0) = 0x04000000;
						*(int*)(0x18C430b + 0x61E0 + 0x61E0 + 0x61E0) = 0x04000000;
					}
					break;
				case 2:
					AmmoAC = !AmmoAC;
					if (AmmoAC == true)
					{
						*(int*)(0x18C4862) = 0x7fffffff;
						*(int*)(0x18C4826) = 0x7fffffff;
						*(int*)(0x18BC8C2) = 0x7fffffff;
						*(int*)(0x18C486A) = 0x7fffffff;
						*(int*)(0x18C4864) = 0x7fffffff;	

						*(int*)(0x18C4862 + 0x61E0) = 0x7fffffff;
						*(int*)(0x18C4826 + 0x61E0) = 0x7fffffff;
						*(int*)(0x18BC8C2 + 0x61E0) = 0x7fffffff;
						*(int*)(0x18C486A + 0x61E0) = 0x7fffffff;
						*(int*)(0x18C4864 + 0x61E0) = 0x7fffffff;	

						*(int*)(0x18C4862 + 0x61E0 + 0x61E0) = 0x7fffffff;
						*(int*)(0x18C4826 + 0x61E0 + 0x61E0) = 0x7fffffff;
						*(int*)(0x18BC8C2 + 0x61E0 + 0x61E0) = 0x7fffffff;
						*(int*)(0x18C486A + 0x61E0 + 0x61E0) = 0x7fffffff;
						*(int*)(0x18C4864 + 0x61E0 + 0x61E0) = 0x7fffffff;	

						*(int*)(0x18C4862 + 0x61E0 + 0x61E0 + 0x61E0) = 0x7fffffff;
						*(int*)(0x18C4826 + 0x61E0 + 0x61E0 + 0x61E0) = 0x7fffffff;
						*(int*)(0x18BC8C2 + 0x61E0 + 0x61E0 + 0x61E0) = 0x7fffffff;
						*(int*)(0x18C486A + 0x61E0 + 0x61E0 + 0x61E0) = 0x7fffffff;
						*(int*)(0x18C4864 + 0x61E0 + 0x61E0 + 0x61E0) = 0x7fffffff;	
					}
					else if (AmmoAC == false)
					{
						*(int*)(0x18C4862) = 0x00000000;
						*(int*)(0x18C4826) = 0x00000000;
						*(int*)(0x18BC8C2) = 0x00000000;
						*(int*)(0x18C486A) = 0x00000000;
						*(int*)(0x18C4864) = 0x00000000;	

						*(int*)(0x18C4862 + 0x61E0) = 0x00000000;
						*(int*)(0x18C4826 + 0x61E0) = 0x00000000;
						*(int*)(0x18BC8C2 + 0x61E0) = 0x00000000;
						*(int*)(0x18C486A + 0x61E0) = 0x00000000;
						*(int*)(0x18C4864 + 0x61E0) = 0x00000000;	

						*(int*)(0x18C4862 + 0x61E0 + 0x61E0) = 0x00000000;
						*(int*)(0x18C4826 + 0x61E0 + 0x61E0) = 0x00000000;
						*(int*)(0x18BC8C2 + 0x61E0 + 0x61E0) = 0x00000000;
						*(int*)(0x18C486A + 0x61E0 + 0x61E0) = 0x00000000;
						*(int*)(0x18C4864 + 0x61E0 + 0x61E0) = 0x00000000;	

						*(int*)(0x18C4862 + 0x61E0 + 0x61E0 + 0x61E0) = 0x00000000;
						*(int*)(0x18C4826 + 0x61E0 + 0x61E0 + 0x61E0) = 0x00000000;
						*(int*)(0x18BC8C2 + 0x61E0 + 0x61E0 + 0x61E0) = 0x00000000;
						*(int*)(0x18C486A + 0x61E0 + 0x61E0 + 0x61E0) = 0x00000000;
						*(int*)(0x18C4864 + 0x61E0 + 0x61E0 + 0x61E0) = 0x00000000;		
					}
					break;
				case 3:
					 *(int*)(0x18CA19D) = 0x7fffffff;
					 *(int*)(0x18CA19D + 0x61E0) = 0x7fffffff;
					 *(int*)(0x18CA19D + 0x61E0 + 0x61E0) = 0x7fffffff;
					 *(int*)(0x18CA19D + 0x61E0 + 0x61E0 + 0x61E0) = 0x7fffffff;
					break;
				case 4:
					Speedx2AC = !Speedx2AC;
					if (Speedx2AC == true)
					{
						*(int*)(0x18CA0E0) = 0x3fff0000;
						*(int*)(0x18CA0E0 + 0x61E0) = 0x3fff0000;		
						*(int*)(0x18CA0E0 + 0x61E0 + 0x61E0) = 0x3fff0000;		
						*(int*)(0x18CA0E0 + 0x61E0 + 0x61E0 + 0x61E0) = 0x3fff0000;		
					}
					else if (Speedx2AC == false)
					{
						*(int*)(0x18CA0E0) = 0x3f800000;
						*(int*)(0x18CA0E0+ 0x61E0) = 0x3f800000;
						*(int*)(0x18CA0E0 + 0x61E0 + 0x61E0) = 0x3f800000;
						*(int*)(0x18CA0E0 + 0x61E0 + 0x61E0 + 0x61E0) = 0x3f800000;
					}
					break;
				case 5:
					FakeLagAC = !FakeLagAC;
					if (FakeLagAC == true)
					{
						*(int*)(0x18CA00F) = 0x01000000;		
						*(int*)(0x18CA00F + 0x61E0) = 0x01000000;		
						*(int*)(0x18CA00F + 0x61E0 + 0x61E0) = 0x01000000;		
						*(int*)(0x18CA00F + 0x61E0 + 0x61E0 + 0x61E0) = 0x01000000;		
					}
					else if (FakeLagAC == false)
					{
						*(int*)(0x18CA00F) = 0x02000000;
						*(int*)(0x18CA00F + 0x61E0) = 0x02000000;
						*(int*)(0x18CA00F + 0x61E0 + 0x61E0) = 0x02000000;
						*(int*)(0x18CA00F + 0x61E0 + 0x61E0 + 0x61E0) = 0x02000000;
					}
					break;
				case 6:
					FreezeAC = !FreezeAC;
					if (FreezeAC == true)
					{
						*(int*)(0x18C4418) = 0x10010101;	
						*(int*)(0x18C4418 + 0x61E0) = 0x10010101;	
						*(int*)(0x18C4418 + 0x61E0 + 0x61E0) = 0x10010101;	
						*(int*)(0x18C4418 + 0x61E0 + 0x61E0 + 0x61E0) = 0x10010101;	
					}
					else if (FreezeAC == false)
					{
						*(int*)(0x18C4418) = 0x01010101;
						*(int*)(0x18C4418 + 0x61E0) = 0x01010101;
						*(int*)(0x18C4418 + 0x61E0 + 0x61E0) = 0x01010101;
						*(int*)(0x18C4418 + 0x61E0 + 0x61E0 + 0x61E0) = 0x01010101;
					}
					break;
				case 7:
					ThirdAC = !ThirdAC;
					if (ThirdAC == true)
					{
						*(int*)(0x18C4414) = 0x00010000;		
						*(int*)(0x18C4414 + 0x61E0) = 0x00010000;		
						*(int*)(0x18C4414 + 0x61E0 + 0x61E0) = 0x00010000;		
						*(int*)(0x18C4414 + 0x61E0 + 0x61E0 + 0x61E0) = 0x00010000;		
					}
					else if (ThirdAC == false)
					{
						*(int*)(0x18C4414) = 0x00000000;
						*(int*)(0x18C4414 + 0x61E0) = 0x00000000;
						*(int*)(0x18C4414 + 0x61E0 + 0x61E0) = 0x00000000;
						*(int*)(0x18C4414 + 0x61E0 + 0x61E0 + 0x61E0) = 0x00000000;
					}
					break;
				case 8:
					notargetAC = !notargetAC;
					if (notargetAC == true)
					{
						*(int*)(0x18CA0CD) = 0xff006400;		
						*(int*)(0x18CA0CD + 0x61E0) = 0xff006400;		
						*(int*)(0x18CA0CD + 0x61E0 + 0x61E0) = 0xff006400;		
						*(int*)(0x18CA0CD + 0x61E0 + 0x61E0 + 0x61E0) = 0xff006400;		
					}
					else if (notargetAC == false)
					{
						*(int*)(0x18CA0CD) = 0x00006400;
						*(int*)(0x18CA0CD + 0x61E0) = 0x00006400;
						*(int*)(0x18CA0CD + 0x61E0 + 0x61E0) = 0x00006400;
						*(int*)(0x18CA0CD + 0x61E0 + 0x61E0 + 0x61E0) = 0x00006400;
					}
					break;
				case 9:
					hudAC = !hudAC;
					if (hudAC == true)
					{
						*(int*)(0x18CA1E7) = 0x00000000;	
						*(int*)(0x18CA1E7 + 0x61E0) = 0x00000000;	
						*(int*)(0x18CA1E7 + 0x61E0 + 0x61E0) = 0x00000000;	
						*(int*)(0x18CA1E7 + 0x61E0 + 0x61E0 + 0x61E0) = 0x00000000;	
					}
					else if (hudAC == false)
					{
						*(int*)(0x18CA1E7) = 0x03000000;
						*(int*)(0x18CA1E7 + 0x61E0) = 0x03000000;
						*(int*)(0x18CA1E7 + 0x61E0 + 0x61E0) = 0x03000000;
						*(int*)(0x18CA1E7 + 0x61E0 + 0x61E0 + 0x61E0) = 0x03000000;
					}
					break;
				case 10:
					perksac = !perksac;
					if (perksac == true)
					{
						*(int*)(G_Client(0) + 0x66C) = 0x2A802718;
						*(int*)(G_Client(0) + 0x670) = 0x04C00155;
						*(int*)(G_Client(0) + 0x66C + 0x61E0) = 0x2A802718;
						*(int*)(G_Client(0) + 0x670 + 0x61E0) = 0x04C00155;
						*(int*)(G_Client(0) + 0x66C + 0x61E0 + 0x61E0) = 0x2A802718;
						*(int*)(G_Client(0) + 0x670 + 0x61E0 + 0x61E0) = 0x04C00155;
						*(int*)(G_Client(0) + 0x66C + 0x61E0 + 0x61E0 + 0x61E0) = 0x2A802718;
						*(int*)(G_Client(0) + 0x670 + 0x61E0 + 0x61E0 + 0x61E0) = 0x04C00155;
						*(int*)(G_Client(0) + 0x66C + 0x61E0 + 0x61E0 + 0x61E0 + 0x61E0) = 0x2A802718;
						*(int*)(G_Client(0) + 0x670 + 0x61E0 + 0x61E0 + 0x61E0 + 0x61E0) = 0x04C00155;
					}
					else if (perksac == false)
					{
                        *(int*)(G_Client(0) + 0x66C) = 0x00000000;
						*(int*)(G_Client(0) + 0x670) = 0x00000000;
						*(int*)(G_Client(0) + 0x66C + 0x61E0) = 0x00000000;
						*(int*)(G_Client(0) + 0x670 + 0x61E0) = 0x00000000;
						*(int*)(G_Client(0) + 0x66C + 0x61E0 + 0x61E0) = 0x00000000;
						*(int*)(G_Client(0) + 0x670 + 0x61E0 + 0x61E0) = 0x00000000;
						*(int*)(G_Client(0) + 0x66C + 0x61E0 + 0x61E0 + 0x61E0) = 0x00000000;
						*(int*)(G_Client(0) + 0x670 + 0x61E0 + 0x61E0 + 0x61E0) = 0x00000000;
						*(int*)(G_Client(0) + 0x66C + 0x61E0 + 0x61E0 + 0x61E0 + 0x61E0) = 0x00000000;
						*(int*)(G_Client(0) + 0x670 + 0x61E0 + 0x61E0 + 0x61E0 + 0x61E0) = 0x00000000;
					}
					break;
				case 11:
					specac = !specac;
					if (specac == true)
					{
						*(int*)(0x18C430B) = 0x07000000;
						*(int*)(0x18C430B + 0x61E0) = 0x07000000;	
						*(int*)(0x18C430B + 0x61E0 + 0x61E0) = 0x07000000;	
						*(int*)(0x18C430B + 0x61E0 + 0x61E0 + 0x61E0) = 0x07000000;	
					}
					else if (specac == false)
					{
						*(int*)(0x18C430B) = 0x04000000;
						*(int*)(0x18C430B + 0x61E0) = 0x04000000;
						*(int*)(0x18C430B + 0x61E0 + 0x61E0) = 0x04000000;
						*(int*)(0x18C430B + 0x61E0 + 0x61E0 + 0x61E0) = 0x04000000;
					}
					break;
				case 12:
					changeSubmenu(weaponsac);
					break;
				
				}
				break;
				case weaponsac:
				//0x18C4643
				addTitle("Primary Weapons Menu");
				addOption("Default Weapons", NULL);
				addOption("Vesper", NULL);
				addOption("VMP", NULL);
				addOption("Kuda", NULL);
				addOption("Infernus", NULL);
				addOption("The Impaler", NULL);
				addOption("Shadow Of Evils Weapons", NULL);
				addOption("Der Eisendrache Weapons", NULL);
				addOption("The Giant Weapons", NULL);
				switch (getOption())
				{
				case 1:
					*(int*)(G_Client(0) + 0x35B) = 0x01000000;
					*(int*)(G_Client(1) + 0x35B) = 0x01000000;
					*(int*)(G_Client(2) + 0x35B) = 0x01000000;
					*(int*)(G_Client(3) + 0x35B) = 0x01000000;
					break;
				case 2:
					*(int*)(G_Client(0) + 0x35B) = 0x02000000;
					*(int*)(G_Client(1) + 0x35B) = 0x02000000;
					*(int*)(G_Client(2) + 0x35B) = 0x02000000;
					*(int*)(G_Client(3) + 0x35B) = 0x02000000;
					break;
				case 3:
					*(int*)(G_Client(0) + 0x35B) = 0x04000000;
					*(int*)(G_Client(1) + 0x35B) = 0x04000000;
					*(int*)(G_Client(2) + 0x35B) = 0x04000000;
					*(int*)(G_Client(3) + 0x35B) = 0x04000000;
					break;
				case 4:
					*(int*)(G_Client(0) + 0x35B) = 0x06000000;
					*(int*)(G_Client(1) + 0x35B) = 0x06000000;
					*(int*)(G_Client(2) + 0x35B) = 0x06000000;
					*(int*)(G_Client(3) + 0x35B) = 0x06000000;
					break;
			    case 5:
					*(int*)(G_Client(0) + 0x35B) = 0x12000000;
					*(int*)(G_Client(1) + 0x35B) = 0x12000000;
					*(int*)(G_Client(2) + 0x35B) = 0x12000000;
					*(int*)(G_Client(3) + 0x35B) = 0x12000000;
					break;
                case 6:
					*(int*)(G_Client(0) + 0x35B) = 0x15000000;
					*(int*)(G_Client(1) + 0x35B) = 0x15000000;
					*(int*)(G_Client(2) + 0x35B) = 0x15000000;
					*(int*)(G_Client(3) + 0x35B) = 0x15000000;
					break;
				case 7:
					changeSubmenu(Shadow);
					break;
				case 8:
					changeSubmenu(Der);
					break;
				case 9:
					changeSubmenu(giantac);
					break;
				}
				break;
				case shadowsac:
				addTitle("Shadows Weapons Menu");
				addOption("Mar-Astagua-Arbgwaoth", NULL);
				addOption("Nar-Ullaqua-Arbgwaoth", NULL);
				addOption("Lor-Zarozzor-Arbgwaoth", NULL);
				addOption("Weapon_Interdimensional_Gun", NULL);
				switch (getOption())
				{
				case 1:
					*(int*)(G_Client(0) + 0x35B) = 0x80000000;
					*(int*)(G_Client(1) + 0x35B) = 0x80000000;
					*(int*)(G_Client(2) + 0x35B) = 0x80000000;
					*(int*)(G_Client(3) + 0x35B) = 0x80000000;
					break;
				case 2:
					*(int*)(G_Client(0) + 0x35B) = 0x81000000;
					*(int*)(G_Client(1) + 0x35B) = 0x81000000;
					*(int*)(G_Client(2) + 0x35B) = 0x81000000;
					*(int*)(G_Client(3) + 0x35B) = 0x81000000;
					break;
				case 3:
					*(int*)(G_Client(0) + 0x35B) = 0x82000000;
					*(int*)(G_Client(1) + 0x35B) = 0x82000000;
					*(int*)(G_Client(2) + 0x35B) = 0x82000000;
					*(int*)(G_Client(3) + 0x35B) = 0x82000000;
					break;
				case 4:
					*(int*)(G_Client(0) + 0x35B) = 0x83000000;
					*(int*)(G_Client(1) + 0x35B) = 0x83000000;
					*(int*)(G_Client(2) + 0x35B) = 0x83000000;
					*(int*)(G_Client(3) + 0x35B) = 0x83000000;
					break;
				}
				break;
				case derac:
				addTitle("Einsendrache Weapons Menu");
				addOption("Wrath of the Ancients", NULL);
				addOption("Kreegakaleet lu Gosata'ahm", NULL);
				addOption("Kreeaho'ahm nal Ahmhogaroc", NULL);
				addOption("Kreeaho'ahm nal Ahmahm", NULL);
				addOption("Kreeaholo lu Kreemasaleet", NULL);
				addOption("Death Machine", NULL);
				switch (getOption())
				{
				case 1:
					*(int*)(G_Client(0) + 0x35B) = 0x76000000;
					*(int*)(G_Client(1) + 0x35B) = 0x76000000;
					*(int*)(G_Client(2) + 0x35B) = 0x76000000;
					*(int*)(G_Client(3) + 0x35B) = 0x76000000;
					break;
				case 2:
					*(int*)(G_Client(0) + 0x35B) = 0x79000000;
					*(int*)(G_Client(1) + 0x35B) = 0x79000000;
					*(int*)(G_Client(2) + 0x35B) = 0x79000000;
					*(int*)(G_Client(3) + 0x35B) = 0x79000000;
					break;
				case 3:
					*(int*)(G_Client(0) + 0x35B) = 0x7D000000;
					*(int*)(G_Client(1) + 0x35B) = 0x7D000000;
					*(int*)(G_Client(2) + 0x35B) = 0x7D000000;
					*(int*)(G_Client(3) + 0x35B) = 0x7D000000;
					break;
				case 4:
					*(int*)(G_Client(0) + 0x35B) = 0x83000000;
					*(int*)(G_Client(1) + 0x35B) = 0x83000000;
					*(int*)(G_Client(2) + 0x35B) = 0x83000000;
					*(int*)(G_Client(3) + 0x35B) = 0x83000000;
					break;
				case 5:
					*(int*)(G_Client(0) + 0x35B) = 0x89000000;
					*(int*)(G_Client(1) + 0x35B) = 0x89000000;
					*(int*)(G_Client(2) + 0x35B) = 0x89000000;
					*(int*)(G_Client(3) + 0x35B) = 0x89000000;
					break;
				case 6:
					*(int*)(G_Client(0) + 0x35B) = 0x95000000;
					*(int*)(G_Client(1) + 0x35B) = 0x95000000;
					*(int*)(G_Client(2) + 0x35B) = 0x95000000;
					*(int*)(G_Client(3) + 0x35B) = 0x95000000;
					break;
				}
				break;
				case giantac:
				addTitle("The Giant Weapons Menu");
				addOption("RayGun", NULL);
				addOption("Wunderwaffe DG-2", NULL);
				addOption("Wunderwaffe DG-3 JZ", NULL);
				switch (getOption())
				{
				case 1:
					*(int*)(G_Client(0) + 0x30B) = 0x75000000;
					*(int*)(G_Client(1) + 0x30B) = 0x75000000;
					*(int*)(G_Client(2) + 0x30B) = 0x75000000;
					*(int*)(G_Client(3) + 0x30B) = 0x75000000;
					break;
				case 2:
					*(int*)(G_Client(0) + 0x30B) = 0x78000000;
					*(int*)(G_Client(1) + 0x30B) = 0x78000000;
					*(int*)(G_Client(2) + 0x30B) = 0x78000000;
					*(int*)(G_Client(3) + 0x30B) = 0x78000000;
					break;
				case 3:
					*(int*)(G_Client(0) + 0x30B) = 0x77000000;
					*(int*)(G_Client(1) + 0x30B) = 0x77000000;
					*(int*)(G_Client(2) + 0x30B) = 0x77000000;
					*(int*)(G_Client(3) + 0x30B) = 0x77000000;
					break;
				}
				break;
#pragma endregion
			}
			OpenOption = false;
			rightPress = false;
			leftPress = false;
			fastRightPress = false;
			fastLeftPress = false;
			squarePress = false;
		}
		else isInGame = false;
		return hookStub(TimeId);
}

extern "C" int _BlackOps3ZombieMenuNoHost_prx_entry(void)
{
	PatchInJump(R_SetFrameFog, (int)Hook, false);
	sys_ppu_thread_t id;
	sys_ppu_thread_create(&id,Menu,0,0x4AA,0x1000,0,"Menu");
	cellMsgDialogOpen(1,"SkyFall Mod Menu By MrNiato\nVersion : 1.08\nBlack ops 3 Version : 1.07\n\nChange Log : \nFix Stats Menu\nForce Host Removed",my_dialog2,(void*) 0x0000aaab, NULL);
    return SYS_PRX_RESIDENT;
}
SYS_MODULE_INFO( BlackOps3ZombieMrNiatoSPRX, 0, 1, 1);
SYS_MODULE_START( _BlackOps3ZombieMenuNoHost_prx_entry );

SYS_LIB_DECLARE_WITH_STUB( LIBNAME, SYS_LIB_AUTO_EXPORT, STUBNAME );
SYS_LIB_EXPORT( _BlackOps3ZombieMenuNoHost_export_function, LIBNAME );
sys_ppu_thread_t create_thread(void (*entry)(uint64_t), int priority, size_t stacksize, const char* threadname,sys_ppu_thread_t id)
{      
        if(sys_ppu_thread_create(&id, entry, 0, priority , stacksize, 0, threadname) == CELL_OK)
		{
			
        }      
    return id;
}

// An exported function is needed to generate the project's PRX stub export library
extern "C" int _BlackOps3ZombieMenuNoHost_export_function(void)
{
	console_write("\n\nINJECTED !\n\n");
    return CELL_OK;
}
