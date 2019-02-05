#define TOC (0xDF1E60)//1.06

struct color_t {
	char r;
	char g;
	char b;
	char a;
};

union hudelem_color_t {
	color_t color;
	int rgba;
};

struct hudelem_s {
	float x;//0x00
	float y;//0x04
	float z;//0x08;
	float fontScale;//0xC
	float fromFontScale;//0x10
	int fontScaleStartTime;//0x14
	hudelem_color_t color;//0x18
	hudelem_color_t fromColor;//0x1C
	int fadeStartTime;//0x20
	int scaleStartTime;//0x24
	float fromX;//0x28
	float fromY;//0x2C
	int moveStartTime;//0x30
	int time;//0x34
	int duration;//0x38
	float value;//0x3C
	float sort;//0x40
	hudelem_color_t glowColor;//0x44
	int fxBirthTime;//0x48
	int flags;//0x4C
	short targetEntNum;//0x50
	short fontScaleTime;//0x52
	short fadeTime;//0x54
	short label;//0x56
	short width;//0x58
	short height; //0x5A
	short fromWidth;//0x5C
	short fromHeight;//0x5E
	short scaleTime;//0x60
	short moveTime;//0x62
	short text;//0x64
	short fxLetterTime;//0x66
	short fxDecayStartTime;//0x68
	short fxDecayDuration;//0x6A
	short fxRedactDecayStartTime;//0x6C
	short fxRedactDecayDuration;//0x6E
	unsigned char type;//0x70
	unsigned char font;//0x71
	unsigned char alignOrg;//0x72
	unsigned char alignScreen;//0x73
	short materialIndex;//0x74
	short offscreenMaterialIndex;//0x76
	unsigned char fromAlignOrg;//0x78
	unsigned char fromAlignScreen;//0x79
	unsigned char soundID;//0x7A
	unsigned char ui3dWindow;
};

typedef struct game_hudelem_s {
	hudelem_s elem;//0x00 - 0x7B
	int clientNum;//0x7C
	int team;//0x80
	int abilityFlag;//0x84
};


game_hudelem_s* HudElem_Alloc() {
	for (int i = 20; i < 1024; i++) {
			game_hudelem_s* elem = (game_hudelem_s*) (0x0173B658 + (i * 0x88)); // Struct size is constant through ZM and MP
			if (elem->elem.type == 0) {
				return elem;
			}
		}
	return (game_hudelem_s*)0;
}
opd_s G_MaterialIndex_t = { 0x389590, TOC };
opd_s G_LocalizedString_t = { 0x3894AC, TOC };
short(*G_MaterialIndex)(char*) = (short(*)(char*))&G_MaterialIndex_t;
short(*G_LocalizedString)(char*) = (short(*)(char*))&G_LocalizedString_t;
game_hudelem_s* setShader(int client, char* shader, float x, float y, short width, short height, unsigned char R, unsigned char G, unsigned char B, unsigned char A) {

	//printf("[*] Setting hud shader for client [%i]\n", client);

	game_hudelem_s* elem = HudElem_Alloc();
	elem->clientNum = client;
	elem->elem.type = 8;
	elem->elem.materialIndex = G_MaterialIndex(shader);
	elem->elem.width = width;
	elem->elem.height = height;
	elem->elem.x = x;
	elem->elem.y = y;
	elem->elem.alignOrg = 0x00;
	elem->elem.color.color.r = R;
	elem->elem.color.color.g = G;
	elem->elem.color.color.b = B;
	elem->elem.color.color.a = A;
	elem->elem.ui3dWindow = 0xFF;
	return elem;
}
game_hudelem_s* setText(int client, char* Text, int font, float fontSize, float x, float y,
	unsigned char R, unsigned char G, unsigned char B, unsigned char A,
	unsigned char gR, unsigned char gG, unsigned char gB, unsigned char gA) {

	//printf("[*] Setting hud text for client [%i]\n", client);

	game_hudelem_s* elem = HudElem_Alloc();
	elem->clientNum = client;
	elem->elem.type = 1;
	elem->elem.fontScale = fontSize;
	elem->elem.font = font;
	elem->elem.x = x;
	elem->elem.y = y;
	elem->elem.alignOrg = 0x00;
	elem->elem.text = G_LocalizedString(Text);
	elem->elem.color.color.r = R;
	elem->elem.color.color.g = G;
	elem->elem.color.color.b = B;
	elem->elem.color.color.a = A;
	elem->elem.glowColor.color.r = gR;
	elem->elem.glowColor.color.g = gG;
	elem->elem.glowColor.color.b = gB;
	elem->elem.glowColor.color.a = gA;
	elem->elem.ui3dWindow = 0xFF;
	return elem;
}
int GetLevelTime(){
	return *(int*) (0x01744A00 + 0x96C); // 0x1781F00 old address
}

void fadeOverTime(game_hudelem_s * elem, int Time,
	unsigned char R, unsigned char G, unsigned char B, unsigned char A) {

	elem->elem.fromColor = elem->elem.color;
	elem->elem.color.color.r = R;
	elem->elem.color.color.g = G;
	elem->elem.color.color.b = B;
	elem->elem.color.color.a = A;
	elem->elem.fadeTime = Time;
	elem->elem.fadeStartTime = GetLevelTime();
}


void fontScaleOverTime(game_hudelem_s * elem, int Time, float FontSize) {

	elem->elem.fromFontScale = elem->elem.fontScale;
	elem->elem.fontScale = FontSize;
	elem->elem.fontScaleTime = Time;
	elem->elem.fontScaleStartTime = GetLevelTime();
}

	game_hudelem_s* SetTypewriter(int clientIndex, char* Text, int Font, float FontSize, float X, float Y, char align, int WriteType = 0x800, short Lettertime = 200, short fxDecayStartTime = 7000, short fxDecayDuration = 1000, char R = 255, char G = 255, char B = 255, char A = 255, char GlowR = 255, char GlowG = 255, char GlowB = 255, char GlowA = 0)
	{
		game_hudelem_s* elemIndex = setText(clientIndex, Text, Font, FontSize, X, Y, R, G, B, A, GlowR, GlowG, GlowB, GlowA);
		elemIndex->elem.flags = WriteType;
		elemIndex->elem.fxBirthTime = GetLevelTime();
		elemIndex->elem.fxLetterTime = Lettertime;
		elemIndex->elem.fxDecayStartTime = fxDecayStartTime;
		elemIndex->elem.fxDecayDuration = fxDecayDuration;
		return elemIndex;
	}
	
	void moveOverTime(game_hudelem_s * elem, int time, float X, float Y) {
	elem->elem.fromX = elem->elem.x;
	elem->elem.fromY = elem->elem.y;
	elem->elem.moveStartTime = GetLevelTime();
	elem->elem.moveTime = time;
	elem->elem.x = X;
	elem->elem.y = Y;
}
	void changeText(game_hudelem_s* elem, char* text)
	{
		elem->elem.text = G_LocalizedString(text);
	}
