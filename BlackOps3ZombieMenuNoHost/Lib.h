#define TOC (0xDF1E60)//1.06
struct opd_s
{
	int sub;
	int toc;
};
enum Addr
{
	//G_Client = 0x18C42E8
 CG_BoldGameMessage_ = 0x011484, //1.05
 cBuf_Addtext_ = 0x5A657C,//1.07
 R_RegisterFont_ = 0x40073C,//1.07
 Material_RegisterHandle_ = 0x0409704,//1.07
 R_AddCmdDrawTextInternal_ = 0x04112B8,//1.07
 R_AddCmdDrawStretchPicInternal_ = 0x0410E68,//1.07
 cgarray = 0xF36274,//1.05 Il na pas bouger 
 Health = 0x360,
 Key_IsDown = 0x11CCA0C + 0x0F,//1.06
 R_SetFrameFog = 0x3D00E8,//1.07 
};
opd_s CG_BoldGameMessage_s = { CG_BoldGameMessage_,TOC};
void (*CG_BoldGameMessage)(int localclient,const char* msg) = (void(*)(int,const char*))&CG_BoldGameMessage_s;
opd_s cBuf_Addtext_s = {cBuf_Addtext_,TOC};
void (*cBuf_AddText)(int localclient,const char* dvar) = (void(*)(int,const char*))&cBuf_Addtext_s;
opd_s R_RegisterFont_s = { R_RegisterFont_, TOC };
void*(*R_RegisterFont)(const char * font, int imageTrac) = (void*(*)(const char *, int))&R_RegisterFont_s;
opd_s Material_RegisterHandle_s = { Material_RegisterHandle_, TOC };
void*(*Material_RegisterHandle)(const char *name, int imageTrack, bool errorIfMissing, int waitTime) = (void*(*)(const char*, int, bool, int))&Material_RegisterHandle_s;
opd_s R_AddCmdDrawTextInternal_s = { R_AddCmdDrawTextInternal_, TOC };
void(*R_AddCmdDrawTextInternal)(const char* text, int maxChars, void* font, float x, float y, float yScale, float xScale, float rotation, float* colors, int Style) = (void(*)(const char*, int, void*, float, float, float, float, float, float*, int))&R_AddCmdDrawTextInternal_s;
opd_s R_AddCmdDrawStretchPicInternal_s = { R_AddCmdDrawStretchPicInternal_, TOC };
void(*R_AddCmdDrawStretchPicInternal)(float x, float y, float w, float h, float s0, float t0, float s1, float t1, float* color, void *material) = (void(*)(float, float, float, float, float, float, float, float, float*, void*))&R_AddCmdDrawStretchPicInternal_s;
//Hud Menu Colors
float White[4] = { 1.0f, 1.0f, 1.0f, 0 };
float White2[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
float Black[4] = { 0, 0, 0, 0 };
float Purple[4] = { 0.4, 0, 0.4, 0 };
//Funcutions
void DrawShader(float x, float y, float width, float height, float * color, const char * material)
{
	R_AddCmdDrawStretchPicInternal(x, y, width, height, 1, 1, 1, 1, color, Material_RegisterHandle(material, 0, false, 0));
}
void DrawText(const char *xtext, float x, float y, const char *xfont, float xfontSize, float* color)
{
	R_AddCmdDrawTextInternal(xtext, 0x7FFFFFFF, R_RegisterFont(xfont, 0), x, y, xfontSize, xfontSize, 0, color, 0);
}
const char* Text2 = "";
bool Printer = false;
void Print(const char * text)
{
	Text2 = text;
	Printer = true;
}
bool InGame()
{
	if(*(int*)(0x373FE060) != 0x00)
		return true;
	else
		return false;
}







void DisableCheatProtection()
{
	*(int*)0x617D9C = 0x60000000;
	*(int*)0x617DB4  = 0x60000000;
	*(int*)0x617DCC = 0x38600000;//Thanks Milky For PPC 
}
void GodMode222()
{
	*(int*)0x18C4418 = 0x01010101;
}
void AmmoUn()
{
	*(int*)0x18C4862 = 0x7fffffff;
	*(int*)0x18C4826 = 0x7fffffff;
	*(int*)0x18BC8C2 = 0x7fffffff;
	*(int*)0x18C486A = 0x7fffffff;
	*(int*)0x18C4864 = 0x7fffffff;
}
void maxPoints()
{
	*(int*)0x18CA19D = 0xffffffff;
}
void GivePerks()
{
	*(int*)0x18f005c = 0x2a802e718;
	*(int*)0x18f0060 = 0x433ff815;
}
//Buttons
namespace ButtonMonitor
{
	enum Buttons
	{
		Up = 5460, //
		Down = 5476,
		R3 = 5384,
		Square = 5160,
	};
	bool Pressed(int Button)
	{
		if (*(char*)(Key_IsDown + Button))
			return true;
		else 
			return false;
	}
}

