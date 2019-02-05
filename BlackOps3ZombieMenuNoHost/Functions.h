#include "Huds.h"


opd_s SV_GameSendServerCommand_t = { 0x5EC544, TOC };
void(*SV_GameSendServerCommand)(int client, int type, const char* cmd) = (void(*)(int, int, const char*))&SV_GameSendServerCommand_t;

        void iPrintln(int client, const char* text)
        {
			char buf[0x100];
			sprintf(buf, "; \"%s\"", text);
            SV_GameSendServerCommand(client, 1, buf);
        }



struct _base
{
	bool Drawn;
	bool Opened;
	game_hudelem_s* Shader;
	game_hudelem_s* Scroller;
	game_hudelem_s* Sidebar;
	game_hudelem_s* Sidebar2;
	game_hudelem_s* Text[15];
	game_hudelem_s* Title;
	int curSub;
	int scroll;
	int Ver;
};_base base[12];

struct _menu
{
	
	int index;
	int Submenu;
	int ParentID;
	int subID;
	void(*option)(int, int);
	int Param;
	int Param2;
	char* optionName;
	int optionAccessLevel;

};_menu menu[10][15];

void add_menu(int sub, int parentID)
{
	menu[sub][0].ParentID = parentID;
}
void add_option(char* funcName, int submenu, int index, int requiredAccess, void(*Option)(int, int),  int param = 0, int param2 = 0)
{
	menu[submenu][index].optionName = funcName;
	menu[submenu][index].optionAccessLevel = requiredAccess;
	menu[submenu][0].index = index;
	menu[submenu][index].option = Option;
	menu[submenu][index].Param = param;
	menu[submenu][index].Param2 = param2;
}
void moveScroller(int client, int scroll)
{
	moveOverTime(base[client].Scroller, 100, 200, 115 + (scroll * 15));
}
void switchSub(int client, int sub)
{
	for(int i = 0; i < 12; i ++)
	{
		fadeOverTime(base[client].Text[i], 100, 255, 255, 255, 0);
		changeText(base[client].Text[i], menu[sub][i].optionName);
		fadeOverTime(base[client].Text[i], 550, 255, 255, 255, 255);
	}
	base[client].curSub = sub;
	base[client].scroll = 0;
	moveScroller(client, base[client].scroll);
}
typedef struct cg_s//
{
	char _0x0000[132];
	int Ping; //0x0084 
	char _0x0088[8];
	int ClientNumber; //0x0090 
	char _0x0094[44];
	Vector3 Origin; //0x00C0 
	char _0x00CC[660];
	int Health; //0x0360 
	char _0x0364[4];
	int MaxHealth; //0x0368 
	char _0x036C[1324];
} cg_s, *pcg_s;//Size=0x01D4
cg_s* cg;

