#pragma once

enum SubMenus { 
//this is where you would add all the submenus you like, although we can make a seperate file if that pleases you
	NOMENU,
	mainmenu,
	self,
};

 struct VECTOR2 {
	float x, y;
};
struct VECTOR2_2 {
	float w, h;
};
struct RGBAF {
	int r, g, b, a, f;
};
struct RGBA {
	int r, g, b, a;
};
struct RGB {
	int r, g, b;
};
extern float fx;
extern float fxx;
extern float fxxx;
extern float fxxxx;
namespace Menu {
//not used in example
	void DRAW_TEXTURE(std::string Streamedtexture, std::string textureName, float x, float y, float width, float height, float rotation, int r, int g, int b, int a);
	namespace Drawing {
		void Text(const char* text, RGBAF rgbaf, VECTOR2 position, VECTOR2_2 size, bool center, bool rightAlign = false, bool outline = true);
		void Title(const char* text, RGBAF rgbaf, VECTOR2 position, VECTOR2_2 size, bool center);
		void Rect(RGBA rgba, VECTOR2 position, VECTOR2_2 size);
		void Spriter(std::string Streamedtexture, std::string textureName, float x, float y, float width, float height, float rotation, int r, int g, int b, int a);
		void wTitle(const char* text, RGBAF rgbaf, VECTOR2 position, VECTOR2_2 size, bool center);
	}
	namespace Settings {
		extern bool selectPressed;
		extern bool leftPressed;
		extern bool rightPressed;
		extern bool center;
		extern bool DrawTextOutline;
		extern bool controllerinput;
		extern int titleRectTexture;

		extern int maxVisOptions;
		extern int currentOption;
		extern int optionCount;

		extern SubMenus currentMenu;
		extern int menuLevel;
		extern int optionsArray[1000];
		extern SubMenus menusArray[1000];

		extern float menuX;
		extern RGBAF count;
		extern RGBAF titleText;
		extern RGBA titleRect;
		extern RGBAF breakText;
		extern RGBAF optionText;
		extern RGBA selectedText;
		extern RGBAF arrow;
		extern RGBAF integre;
		extern RGBA optionRect;
		extern RGBA optionRect2;
		extern RGBA scroller;
		extern RGBA line;
		extern RGBA primary;
		extern RGBA secondary;

		extern int keyPressDelay;
		extern int keyPressPreviousTick;
		extern int keyPressDelay2;
		extern int keyPressPreviousTick2;
		extern int keyPressDelay3;
		extern int keyPressPreviousTick3;
		extern int openKey;
		extern int backKey;
		extern int upKey;
		extern int downKey;
		extern int leftKey;
		extern int rightKey;
		extern int selectKey;
		extern int arrowupKey;
		extern int arrowdownKey;
		extern int arrowleftKey;
		extern int arrowrightKey;
		extern int enterKey;
		extern int deleteKey;
		extern int openpress;
		extern int downpress;
		extern int uppress;
		extern int backpress;
		extern int click;
		extern int leftpress;
		extern int rightpress;

		extern int cursorMenuX;

		extern float scrollBarPos;
		extern float menuY;
		extern float menuWidth;
		extern float headerHeight;
		extern float scrollbarWidthIndex;
		extern float textSize;

    //teehee
		extern bool enable_scrollbar;
		extern float ScrollerSpeed;
    //Just more animation wise visually pleasing, if you want
		extern bool enable_smooth;

	}
	namespace MenuLevelHandler {
		void MoveMenu(SubMenus menu);
		void BackMenu();
	}
	namespace Checks {
		void Controlls();
	}
	namespace Tools {
		char* StringToChar(std::string string);
	}
	namespace Files {
		void WriteStringToIni(std::string string, std::string file, std::string app, std::string key);
		std::string ReadStringFromIni(std::string file, std::string app, std::string key);
		void WriteIntToIni(int intValue, std::string file, std::string app, std::string key);
		int ReadIntFromIni(std::string file, std::string app, std::string key);
		void WriteFloatToIni(float floatValue, std::string file, std::string app, std::string key);
		float ReadFloatFromIni(std::string file, std::string app, std::string key);
		void WriteBoolToIni(bool b00l, std::string file, std::string app, std::string key);
		bool ReadBoolFromIni(std::string file, std::string app, std::string key);
	}
	/*const std::string GetModulePath(HMODULE module);
	bool FileExists(const std::string& fileName);
	int RegisterFile(const std::string& fullPath, const std::string& fileName);*/
	void DrawGlare(float pX, float pY, float scaleX, float scaleY, int red, int green, int blue, int alpha);
	void render_globe(const float x, const float y, const float sx, const float sy, const int r, const int g, const int b);
	void Title(const char* title);
	void Beg();
	void Beg(const char * option);
	void info(const char * title);
	void Vehicle(std::string texture1, std::string texture2);
	void Speedometer(char* text);
	void fps(char* text);
	void AddSmallTitle(char* text);
	void AddSmallInfo(char* text, short line, char* option, char* option2);
	void AddSmallTitle2(char* text);
	void AddSmallInfo2(char* text, short line);
	void AddSmallTitle3(char* text);
	void SpeedText(char* text);
	bool MenuOptions2(const char * option, SubMenus newSub, int pid);
	void AddSmallInfo3(char* text, short line);
	bool Break(const char* option);
	bool Option(const char * option);
	bool Option(const char* option, std::function<void()> function);
	bool MenuOption(const char* option, SubMenus newSub);
	bool MenuOption(const char* option, SubMenus newSub, std::function<void()> function);
	bool Toggle(const char* option, bool& b00l);
	bool Toggle(const char* option, bool& b00l, std::function<void()> function);
	bool Int(const char* option, int& _int, int min, int max);
	bool Int(const char* option, int& _int, int min, int max, int step);
	bool Int(const char* option, int& _int, int min, int max, std::function<void()> function);
	bool Int(const char* option, int& _int, int min, int max, int step, std::function<void()> function);
	bool Float(const char* option, float& _float, int min, int max);
	bool Float(const char* option, float& _float, int min, int max, int step);
	bool Float(const char* option, float& _float, int min, int max, std::function<void()> function);
	bool Float(const char* option, float& _float, int min, int max, int step, std::function<void()> function);
	bool IntVector(const char* option, std::vector<int> Vector, int& position);
	bool IntVector(const char* option, std::vector<int> Vector, int& position, std::function<void()> function);
	bool FloatVector(const char* option, std::vector<float> Vector, int& position);
	bool FloatVector(const char* option, std::vector<float> Vector, int& position, std::function<void()> function);
	bool StringVector(const char* option, std::vector<std::string> Vector, int& position);
	bool StringVector(const char* option, std::vector<std::string> Vector, int& position, std::function<void()> function);
	bool StringVector(const char* option, std::vector<char*> Vector, int& position);
	bool StringVector(const char* option, std::vector<char*> Vector, int& position, std::function<void()> function);
//removed these 2
	bool Teleport(const char* option, Vector3 coords);
	void PlayerInfoIcon(std::string streamedtextureid, std::string textureid, short line_);
	void PlayerOption(int i);
	void Vehicle(std::string texture1, std::string texture2);
	void scroll(int* prev, const int cur);
	bool Teleport(const char* option, Vector3 coords, std::function<void()> function);
	void Log(char* msg);
	void logMessage(char* msg);
	void SimpleSmoothScrolling();
	void addText(std::string txt, bool withN);
	void statsinfo(); //this is for the 0w0s, no in example
	void drawScrollbar(int max_options, int option_count); //I mean. really...ig
	bool ListVector(const char * option, std::vector<char*> Vector, int & position);
	int pressedKey();
	//hotkeys, not used in example dw
	void addHotkey(std::string name);
	void removeHotkey(std::string name);
	void checkHotkey(std::string name, bool& b00l);
	void checkHotkey(std::string name, bool& b00l, std::function<void()> func);
	void checkHotkey(std::string name, std::function<void()> func);
	bool checkHotkey(std::string name);

	void customNotification(char* text);
	typedef struct
	{
		std::string dict;
		std::string texture;
	} sprite_info;

	void End();
	void End(const char * option);
}
