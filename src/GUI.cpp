#include "stdafx.h"
//fonts have some fun, all shitty, should have used imgui ;)
enum Font
{
	ChaletLondon = 0,
	HouseScript = 1,
	Monospace = 2,
	Wingdings = 3,
	ChaletComprimeCologne = 4,
	Pricedown = 7
};
//Please get this shit of here, lol hehe
void str(const std::string& str, const int font, const float x, const float y, const float sx, const float sy,
	const int r, const int g, const int b, const int a, const bool outline, const bool shadow,
	const bool center)
{
	UI::SET_TEXT_FONT(font);
	UI::SET_TEXT_SCALE(sx, sy);
	UI::SET_TEXT_COLOUR(r, g, b, a);
	if (outline)
		UI::SET_TEXT_OUTLINE();
	if (shadow)
		UI::SET_TEXT_DROP_SHADOW();
	if (center)
		UI::SET_TEXT_CENTRE(1);
	UI::BEGIN_TEXT_COMMAND_DISPLAY_TEXT(static_cast<char*>("STRING"));
	const auto drawing_text = str.c_str();
	UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(const_cast<char*>(drawing_text));
	UI::END_TEXT_COMMAND_DISPLAY_TEXT(x, y);
}
//is this trash code over with yet, it's hurting me
void Menu::Drawing::Text(const char* text, RGBAF rgbaf, VECTOR2 position, VECTOR2_2 size, bool center, bool rightAlign, bool outline)
{
	UI::SET_TEXT_CENTRE(center);
	UI::SET_TEXT_COLOUR(rgbaf.r, rgbaf.g, rgbaf.b, rgbaf.a);
	UI::SET_TEXT_FONT(rgbaf.f);
	UI::SET_TEXT_SCALE(size.w, size.h);
	if (outline && Menu::Settings::DrawTextOutline) {
		UI::SET_TEXT_DROPSHADOW(1, 0, 0, 0, 0);
		UI::SET_TEXT_EDGE(1, 0, 0, 0, 0);
		UI::SET_TEXT_OUTLINE();
	}
	if (rightAlign) {
		UI::SET_TEXT_RIGHT_JUSTIFY(TRUE);
		UI::SET_TEXT_WRAP(Menu::Settings::menuX, Menu::Settings::menuX + 0.085f);
	}
	UI::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
	UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME((char*)text);
	UI::END_TEXT_COMMAND_DISPLAY_TEXT(position.x, position.y);
}

void Menu::Drawing::Spriter(std::string Streamedtexture, std::string textureName, float x, float y, float width, float height, float rotation, int r, int g, int b, int a)
{
	if (!GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED((char*)Streamedtexture.c_str()))
	{
		GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT((char*)Streamedtexture.c_str(), false);
	}
	else
	{
		GRAPHICS::DRAW_SPRITE((char*)Streamedtexture.c_str(), (char*)textureName.c_str(), x, y, width, height, rotation, r, g, b, a);
	}
}

//ye this pattern works, don't blame the pattern, used for those sweet ytds ur gonna use in your paid cheat
static fpFileRegister file_register = (fpFileRegister)(Memory::pattern("48 89 5C 24 ? 48 89 6C 24 ? 48 89 7C 24 ? 41 54 41 56 41 57 48 83 EC 50 48 8B EA 4C 8B FA 48 8B D9 4D 85 C9").count(1).get(0).get<decltype(file_register)>());
bool FileExists(const std::string& fileName)
{
	struct stat buffer;
	return (stat(fileName.c_str(), &buffer) == 0);
}
void YTD()
{
	std::string path = "Your Paid Cheat folder/";
	std::string name = "GenericP2Cname.ytd";
	const std::string fullPath = path + name;

	int textureID;
	if (FileExists(fullPath))
		file_register(&textureID, fullPath.c_str(), true, name.c_str(), false);
}
void Menu::Drawing::Rect(RGBA rgba, VECTOR2 position, VECTOR2_2 size)
{
	GRAPHICS::DRAW_RECT(position.x, position.y, size.w, size.h, rgba.r, rgba.g, rgba.b, rgba.a);
}

float gGlareDir;
float conv360(float base, float min, float max)
{
	float fVar0;
	if (min == max) return min;
	fVar0 = max - min;
	base -= SYSTEM::ROUND(base - min / fVar0) * fVar0;
	if (base < min) base += fVar0;
	return base;
}

float DrawGlareX = 1.120f;
float DrawGlareY = 0.507f;
float DrawGlareScaleX = 0.949f;
float DrawGlareScaleY = 0.958f;

void Menu::DrawGlare(float pX, float pY, float scaleX, float scaleY, int red, int green, int blue, int alpha)
{
	int gGlareHandle = GRAPHICS::REQUEST_SCALEFORM_MOVIE("MP_MENU_GLARE");
	Vector3 rot = CAM::GET_GAMEPLAY_CAM_ROT(2);
	float dir = conv360(rot.z, 0, 360);
	if ((gGlareDir == 0 || gGlareDir - dir > 0.5) || gGlareDir - dir < -0.5)
	{
		gGlareDir = dir;
		GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(gGlareHandle, "SET_DATA_SLOT");
		GRAPHICS::_ADD_SCALEFORM_MOVIE_METHOD_PARAMETER_FLOAT(gGlareDir);
		GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
	}
	GRAPHICS::DRAW_SCALEFORM_MOVIE(gGlareHandle, pX, pY, scaleX, scaleY, red, green, blue, alpha, 0);
}
bool Menu::Settings::enable_scrollbar = false;
bool Menu::Settings::DrawTextOutline = false;
int Menu::Settings::titleRectTexture = 0;
float Menu::Settings::menuX = 0.85f;
float Menu::Settings::menuY = 0.0f;
bool Menu::Settings::selectPressed = false;
bool Menu::Settings::leftPressed = false;
bool Menu::Settings::rightPressed = false;
bool firstopen = true;
int Menu::Settings::maxVisOptions = 16;
int Menu::Settings::currentOption = 0;
int Menu::Settings::optionCount = 0;
SubMenus Menu::Settings::currentMenu;
int Menu::Settings::menuLevel = 0;
int Menu::Settings::optionsArray[1000];
SubMenus Menu::Settings::menusArray[1000];

RGBAF Menu::Settings::count{ 255, 255, 255, 255, 6 };
RGBAF Menu::Settings::titleText{ 255, 255, 255, 255, 1 };
RGBA Menu::Settings::titleRect{ 100, 0, 0, 255 };
RGBAF Menu::Settings::optionText{ 255, 255, 255, 255, 4 };
RGBAF Menu::Settings::breakText{ 255, 255, 255, 255, 4 };
RGBAF Menu::Settings::arrow{ 255, 255, 255, 255, 3 };                          // Mod Menu Colors 
RGBA Menu::Settings::optionRect{ 0, 0, 0, 210 };
RGBA Menu::Settings::optionRect2{ 0, 0, 0, 255 };
RGBA Menu::Settings::scroller{ 1, 55, 191, 255 };
RGBAF Menu::Settings::integre{ 255, 255, 255, 255, 2 };
RGBA Menu::Settings::line{ 255, 255, 255, 255 };
RGBA Menu::Settings::primary{ 255, 0, 0 };
RGBA Menu::Settings::secondary{ 0, 255, 0 };

//You call this a globe, stfu faggot...ok
void Menu::render_globe(const float x, const float y, const float sx, const float sy, const int r, const int g,
	const int b)

{
	float g_glare_dir = 0;
	auto g_glare_handle = GRAPHICS::REQUEST_SCALEFORM_MOVIE(static_cast<char*>("MP_MENU_GLARE"));
	const auto rot = CAM::_GET_GAMEPLAY_CAM_ROT(2);
	const auto dir = conv360(rot.z, 0, 360);
	if ((g_glare_dir == 0 || g_glare_dir - dir > 0.5) || g_glare_dir - dir < -0.5)
	{
		g_glare_dir = dir;
		GRAPHICS::CALL_SCALEFORM_MOVIE_METHOD(g_glare_handle, static_cast<char*>("SET_DATA_SLOT"));
		GRAPHICS::_ADD_SCALEFORM_MOVIE_METHOD_PARAMETER_FLOAT(g_glare_dir);
		GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
	}
	GRAPHICS::DRAW_SCALEFORM_MOVIE(g_glare_handle, x, y, sx, sy, r, g, b, 20, 0);
	GRAPHICS::_SCREEN_DRAW_POSITION_END();
	//GRAPHICS::SET_SCALEFORM_MOVIE_AS_NO_LONGER_NEEDED(&g_glare_handle);

}
float fx = 0.516999f;
float fxx = 0.481000f;
float fxxx = 1.088999f;
float fxxxx = 0.902000f;



void Menu::Title(const char * title)
{
	if (Menu::Settings::titleRectTexture == 0) {
		Drawing::Spriter("YTD name", "P2C Banner here", Settings::menuX, 0.1175f, 0.21f, 0.085f, 0, 255, 255, 255, 255);
	}
	else if (Menu::Settings::titleRectTexture == 1) {
  //example thanks astrolux
		Drawing::Spriter("UCHeader", "astrolux", Settings::menuX, 0.1175f, 0.21f, 0.085f, 0, 255, 255, 255, 255);
	}
	else if (Menu::Settings::titleRectTexture == 2) {
  //Or draw one of the in game headers, OpenIV is your friend
		Drawing::Spriter("search boi", "google", Settings::menuX, 0.1175f, 0.21f, 0.085f, 0, 255, 255, 255, 255);
	}
	if (Settings::enable_scrollbar) {
		Drawing::Rect(Settings::secondary, { Settings::menuX - Settings::scrollbarWidthIndex, Settings::menuY + 0.1500f }, { 0.01f, 0.019f });
		Drawing::Text("3", Settings::arrow, { Settings::menuX - Settings::scrollbarWidthIndex - 0.005f, Settings::menuY + 0.137f }, { 0.30f, 0.30f }, false);
	}
	YTD();
	// Disable Controls
	UI::HIDE_HELP_TEXT_THIS_FRAME();
	CAM::SET_CINEMATIC_BUTTON_ACTIVE(0);
	UI::HIDE_HUD_COMPONENT_THIS_FRAME(10);
	UI::HIDE_HUD_COMPONENT_THIS_FRAME(6);
	UI::HIDE_HUD_COMPONENT_THIS_FRAME(7);
	UI::HIDE_HUD_COMPONENT_THIS_FRAME(9);
	UI::HIDE_HUD_COMPONENT_THIS_FRAME(8);
	CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_NEXT_CAMERA, true);
	CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_CHARACTER_WHEEL, true);
	CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_MELEE_ATTACK_LIGHT, true);
	CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_MELEE_ATTACK_HEAVY, true);
	CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_MULTIPLAYER_INFO, true);
	CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_PHONE, true);
	CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_MELEE_ATTACK_ALTERNATE, true);
	CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_VEH_CIN_CAM, true);
	CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_MAP_POI, true);
	CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_PHONE, true);
	CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_VEH_RADIO_WHEEL, true);
	CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_VEH_HEADLIGHT, true);

}

void DrawLeftText(const char* text, float x, float y, float size, int font, RGBA color, bool outline, bool shadow)
{
	UI::SET_TEXT_SCALE(size, size);
	UI::SET_TEXT_FONT(static_cast<int>(font));
	UI::SET_TEXT_COLOUR(color.r, color.g, color.b, color.a);
	if (outline)
		UI::SET_TEXT_OUTLINE();
	if (shadow)
		UI::SET_TEXT_DROP_SHADOW();

	UI::BEGIN_TEXT_COMMAND_DISPLAY_TEXT((char*)"STRING");
	UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME((char*)text);
	UI::END_TEXT_COMMAND_DISPLAY_TEXT(x, y);
}

void DrawCenteredText(const char* text, float x, float y, float size, int font, RGBA color, bool outline, bool shadow)
{
	UI::SET_TEXT_CENTRE(true);
	DrawLeftText(text, x, y, size, font, color, outline, shadow);
}

void DrawRightText(const char* text, float x, float y, float size, int font, RGBA color, bool outline, bool shadow)
{
	UI::SET_TEXT_WRAP(0.f, x);
	UI::SET_TEXT_RIGHT_JUSTIFY(true);
	DrawLeftText(text, x, y, size, font, color, outline, shadow);
}

float GetTextHeight(Font font, float size)
{
	return UI::_GET_TEXT_SCALE_HEIGHT(size, static_cast<int>(font));
}

//menu settings
float Menu::Settings::menuWidth = 0.21f; //width of the menu, while open
float Menu::Settings::headerHeight = 0.085f;
float Menu::Settings::scrollbarWidthIndex = 0.135f; //0.12f
float Menu::Settings::textSize = 0.35f - 0.07f;
float yyyyy = 0.349f;
//Just know we draw it to the right places
void Menu::drawScrollbar(int max_options, int option_count) {
	int curopt = Settings::currentOption;
	float space = 0.035f;
	float scroll = ((((curopt * (max_options * space)) / option_count)));

	if (option_count > max_options) {
		Drawing::Rect({ 45, 45, 45, 165 }, { Settings::menuX + 0.112f, Settings::menuY + yyyyy }, { 0.012f, max_options * 0.035f });
		Drawing::Rect(Settings::scroller, { Settings::menuX + 0.112f, scroll + Settings::menuY + 0.138f }, { 0.007f, 0.035f });
	}
}

VECTOR2 GetSpriteScale(float size)
{
	int x;
	int y;
	GRAPHICS::_GET_ACTIVE_SCREEN_RESOLUTION(&x, &y);

	return { (static_cast<float>(y) / static_cast<float>(x)) * size, size };
}

//Smooth Scrolling
float Menu::Settings::ScrollerSpeed = 0.01f;
bool Menu::Settings::enable_smooth = false;
float prevf;
int prevOption = 0; //Add prevOption = 1 to open key on Menu::Checks::Controlls in gui.cpp and on numpad0 (back)
void Menu::scroll(int* prev, const int cur)
{
	if (prevf == NULL)
		prevf = *prev * 0.035f + 0.1415f + 0.035f;
	const auto curf = cur * 0.035f + 0.1415f + 0.035f;
	if (*prev != cur)
	{
		if (prevf < curf)
		{
			if (prevf + Settings::ScrollerSpeed > curf)
				prevf = prevf + (curf - prevf);
			else
				prevf = prevf + Settings::ScrollerSpeed;
			Drawing::Rect(Settings::scroller, { Settings::menuX, Settings::menuY + prevf }, { 0.21f, 0.035f }); //0.038f
			if (Settings::enable_scrollbar) {
				Drawing::Rect(Settings::scroller, { Settings::menuX - Settings::scrollbarWidthIndex, Settings::menuY + prevf }, { 0.008f, 0.035f });
			}
			if (prevf >= curf)
			{
				prevf = curf;
				*prev = cur;
			}
		}
		if (prevf > curf)
		{
			if (prevf - Settings::ScrollerSpeed < curf)
				prevf = prevf - (prevf - curf);
			prevf = prevf - Settings::ScrollerSpeed;
			Drawing::Rect(Settings::scroller, { Settings::menuX, Settings::menuY + prevf }, { 0.21f, 0.035f }); //0.038f
			if (Settings::enable_scrollbar) {
				Drawing::Rect(Settings::scroller, { Settings::menuX - Settings::scrollbarWidthIndex, Settings::menuY + prevf }, { 0.008f, 0.035f });
			}
			if (prevf <= curf)
			{
				prevf = curf;
				*prev = cur;
			}
		}
	}
	else
	{
		*prev = cur;
		Drawing::Rect(Settings::scroller, { Settings::menuX, Settings::menuY + (cur) * 0.035f + 0.1415f + 0.035f }, { Menu::Settings::menuWidth, 0.035f });
		if (Settings::enable_scrollbar) {
			Drawing::Rect(Settings::scroller, { Settings::menuX - Settings::scrollbarWidthIndex, Settings::menuY + (cur) * 0.035f + 0.1415f + 0.035f }, { 0.008f, 0.035f });
		}
	}
}
//the small header bar under the header
void Menu::Beg()
{
	int opcount = Settings::optionCount;
	int currop = Settings::currentOption;
	if (opcount >= 16) {
		Drawing::Text(Tools::StringToChar(std::to_string(currop) + " / " + std::to_string(opcount)), Settings::count, { Settings::menuX + 0.078f, 0.035f + 0.125f }, { 0.35f, 0.35f }, true);
		Drawing::Rect(Settings::optionRect2, { Settings::menuX, 0.035f + 0.1415f }, { 0.21f, 0.035f });
		Drawing::Rect(Settings::line, { Settings::menuX, 0.035f + 0.1235f }, { 0.21f, 0.002f });
		
	}
	else if (opcount > 0) {
		Drawing::Text(Tools::StringToChar(std::to_string(currop) + " / " + std::to_string(opcount)), Settings::count, { Settings::menuX + 0.078f, 0.035f + 0.125f }, { 0.35f, 0.35f }, true);
		Drawing::Rect(Settings::optionRect2, { Settings::menuX, 0.035f + 0.1415f }, { 0.21f, 0.035f });
		Drawing::Rect(Settings::line, { Settings::menuX,  0.035f + 0.1235f }, { 0.21f, 0.002f });
	}
}
void Menu::Beg(const char * option)
{
	Drawing::Text(option, Settings::count, { Settings::menuX , +0.035f + 0.125f }, { 0.45f, 0.45f }, true);
}
bool Menu::Option(const char * option)
{
	Settings::optionCount++;
	bool onThis = Settings::currentOption == Settings::optionCount ? true : false;
	if (Settings::currentOption <= 16 && Settings::optionCount <= 16)
	{
		Drawing::Text(option, Settings::optionText, { Settings::menuX - 0.100f, (Settings::optionCount)*0.035f + 0.125f + 0.035f }, { 0.45f, 0.45f }, false);
		Drawing::Rect(Settings::optionRect, { Settings::menuX, (Settings::optionCount)*0.035f + 0.1415f + 0.035f}, { 0.21f, 0.035f });
		if (Settings::enable_scrollbar) {
			Drawing::Rect(Settings::optionRect, { Settings::menuX - Settings::scrollbarWidthIndex, Settings::menuY + (Settings::optionCount) * 0.035f + 0.1415f + 0.035f }, { 0.01f, 0.035f });
		}
		if (Settings::enable_smooth) {
			if (Settings::optionCount >= 16) {
				if (onThis) {
					Drawing::Rect(Settings::scroller, { Settings::menuX, Settings::menuY + (Settings::optionCount) * 0.035f + 0.1415f + 0.035f }, { Menu::Settings::menuWidth, 0.035f });
					if (Settings::enable_scrollbar) {
						Drawing::Rect(Settings::scroller, { Settings::menuX - Settings::scrollbarWidthIndex, Settings::menuY + (Settings::optionCount) * 0.035f + 0.1415f + 0.035f }, { 0.008f, 0.035f });
					}
				}
			}
			else if (Settings::optionCount > 0) {
				onThis ? scroll(&prevOption, Menu::Settings::currentOption) : NULL;
			}
		}
		else {
			if (onThis) {
				Drawing::Rect(Settings::scroller, { Settings::menuX, Settings::menuY + (Settings::optionCount) * 0.035f + 0.1415f + 0.035f }, { Menu::Settings::menuWidth, 0.035f });
				if (Settings::enable_scrollbar) {
					Drawing::Rect(Settings::scroller, { Settings::menuX - Settings::scrollbarWidthIndex, Settings::menuY + (Settings::optionCount) * 0.035f + 0.1415f + 0.035f }, { 0.008f, 0.035f });
				}
			}
		}
	}
	else if (Settings::optionCount > (Settings::currentOption - 16) && Settings::optionCount <= Settings::currentOption)
	{
		Drawing::Text(option, Settings::optionText, { Settings::menuX - 0.100f, (Settings::optionCount - (Settings::currentOption - 16))*0.035f + 0.125f + 0.035f }, { 0.45f, 0.45f }, false);
		Drawing::Rect(Settings::optionRect, { Settings::menuX,  (Settings::optionCount - (Settings::currentOption - 16))*0.035f + 0.1415f + 0.035f }, { 0.21f, 0.035f });
		if (Settings::enable_scrollbar) {
			Drawing::Rect(Settings::optionRect, { Settings::menuX - Settings::scrollbarWidthIndex, Settings::menuY + (Settings::optionCount - (Settings::currentOption - 16)) * 0.035f + 0.125f + 0.035f }, { 0.01f, 0.035f });
		}
		if (Settings::enable_smooth) {
			if (Settings::optionCount >= 16) {
				if (onThis) {
					Drawing::Rect(Settings::scroller, { Settings::menuX, Settings::menuY + (Settings::optionCount - (Settings::currentOption - 16)) * 0.035f + 0.1415f + 0.035f }, { Menu::Settings::menuWidth, 0.035f });
					if (Settings::enable_scrollbar) {
						Drawing::Rect(Settings::scroller, { Settings::menuX - Settings::scrollbarWidthIndex, Settings::menuY + (Settings::optionCount - (Settings::currentOption - 16)) * 0.035f + 0.1415f + 0.035f }, { 0.008f, 0.035f });
					}
				}
			}
			else if (Settings::optionCount > 0) {
				onThis ? scroll(&prevOption, Menu::Settings::currentOption) : NULL;
			}
		}
		else {
			if (onThis) {
				Drawing::Rect(Settings::scroller, { Settings::menuX, Settings::menuY + (Settings::optionCount - (Settings::currentOption - 16)) * 0.035f + 0.1415f + 0.035f }, { Menu::Settings::menuWidth, 0.035f });
				if (Settings::enable_scrollbar) {
					Drawing::Rect(Settings::scroller, { Settings::menuX - Settings::scrollbarWidthIndex, Settings::menuY + (Settings::optionCount - (Settings::currentOption - 16)) * 0.035f + 0.1415f + 0.035f }, { 0.008f, 0.035f });
				}
			}
		}
	}
	if (Settings::currentOption == Settings::optionCount)
	{
		if (Settings::selectPressed)
		{
			return true;
		}
	}
	return false;
}
bool Menu::Option(const char * option, std::function<void()> function)
{
	Option(option);

	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) {
		function();
		return true;
	}
	return false;
}
//you call this smooth scrolling well i call it gay, owo
void Menu::SimpleSmoothScrolling() {
	float toPos;
	if (Settings::currentOption <= 16 && Settings::optionCount <= 16) {
		if (Menu::Settings::currentOption > Menu::Settings::maxVisOptions) {
			toPos = ((Menu::Settings::maxVisOptions * 0.035f) + 0.1415f + 0.035f);
		}
		else {
			toPos = ((Menu::Settings::currentOption * 0.035f) + 0.1415f + 0.035f);
		}
	}
	else if (Settings::optionCount > (Settings::currentOption - 16) && Settings::optionCount <= Settings::currentOption) {
		toPos = (Settings::optionCount - (Settings::currentOption - 16)) *0.035f + 0.1415f + 0.035f;
	}
	if (Menu::Settings::scrollBarPos > toPos || Settings::currentOption > 16) {
		Menu::Settings::scrollBarPos -= 0.005f;
	}
	if (Menu::Settings::scrollBarPos < toPos) {
		Menu::Settings::scrollBarPos += 0.005f;
	}
}
float Menu::Settings::scrollBarPos = 0.0f;

bool Menu::Break(const char * title)
{
	Settings::optionCount++;
	bool onThis = Settings::currentOption == Settings::optionCount ? true : false;
	if (Settings::currentOption <= 16 && Settings::optionCount <= 16)
	{
		Drawing::Text(title, Settings::breakText, { Settings::menuX, (Settings::optionCount)*0.035f + 0.125f + 0.035f }, { 0.45f, 0.45f }, true);
		Drawing::Rect(Settings::optionRect, { Settings::menuX, (Settings::optionCount)*0.035f + 0.1415f + 0.035f}, { 0.21f, 0.035f });
	}
	else if (Settings::optionCount > (Settings::currentOption - 16) && Settings::optionCount <= Settings::currentOption)
	{
		Drawing::Text(title, Settings::breakText, { Settings::menuX, (Settings::optionCount - (Settings::currentOption - 16))*0.035f + 0.125f + 0.035f }, { 0.45f, 0.45f }, true);
		Drawing::Rect(Settings::optionRect, { Settings::menuX,  (Settings::optionCount - (Settings::currentOption - 16))*0.035f + 0.1415f + 0.035f }, { 0.21f, 0.035f });
	}
	return false;
}
bool Menu::MenuOption(const char * option, SubMenus newSub)
{
	Option(option);
	if (option)
	{
		if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
			Drawing::Text("~b~>~r~>", Settings::optionText, { Settings::menuX + 0.092f, (Settings::optionCount)*0.035f + 0.125f + 0.035f }, { 0.45f, 0.45f }, false);
		else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
			Drawing::Text("~b~>~r~>", Settings::optionText, { Settings::menuX + 0.092f, (Settings::optionCount - (Settings::currentOption - 16))*0.035f + 0.125f + 0.035f }, { 0.45f, 0.45f }, false);	}
	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) {
		MenuLevelHandler::MoveMenu(newSub);
		return true;
	}
	return false;
}

bool Menu::Toggle(const char * option, bool & b00l)
{
	Option(option);
	if (b00l)
	{
		if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
			Drawing::Spriter("commonmenu", "common_medal", Settings::menuX + 0.095f, (Settings::optionCount * 0.035f + 0.141f+ 0.035f), 0.02f, 0.03f, 0, 4, 101, 247, 255);
		else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
			Drawing::Spriter("commonmenu", "common_medal", Settings::menuX + 0.095f, ((Settings::optionCount - (Settings::currentOption - 16)) * 0.035f + 0.141f+ 0.035f), 0.02f, 0.03f, 0, 4, 101, 247, 255); //4, 101, 247
	}
	else
	{
		if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
			Drawing::Spriter("commonmenu", "common_medal", Settings::menuX + 0.095f, (Settings::optionCount * 0.035f + 0.141f+ 0.035f), 0.02f, 0.03f, 0, 255, 0, 70, 255);
		else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
			Drawing::Spriter("commonmenu", "common_medal", Settings::menuX + 0.095f, ((Settings::optionCount - (Settings::currentOption - 16)) * 0.035f + 0.141f+ 0.035f), 0.02f, 0.03f, 0, 255, 0, 70, 255);
	}
	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) {
		b00l ^= 1;
		return true;
	}
	return false;
}

bool Menu::Toggle(const char * option, bool & b00l, std::function<void()> function)
{
	Toggle(option, b00l);

	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) {
		function();
		return true;
	}
	return false;
}

bool Menu::Int(const char * option, int & _int, int min, int max)
{
	Option(option);

	if (Settings::optionCount == Settings::currentOption) {
		if (Settings::leftPressed) {
			_int < max ? _int++ : _int = min;
		}
		if (Settings::rightPressed) {
			_int >= min ? _int-- : _int = max;
		}
	}

	if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
		Drawing::Text(Tools::StringToChar("< " + std::to_string(_int) + " >"), Settings::integre, { Settings::menuX + 0.085f, Settings::optionCount * 0.035f + 0.125f+ 0.035f }, { 0.32f, 0.32f }, true);
	else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
		Drawing::Text(Tools::StringToChar("< " + std::to_string(_int) + " >"), Settings::integre, { Settings::menuX +  0.085f, (Settings::optionCount - (Settings::currentOption - 16))*0.035f + 0.125f + 0.035f }, { 0.32f, 0.32f }, true);

	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) return true;
	else if (Settings::optionCount == Settings::currentOption && Settings::leftPressed) return true;
	else if (Settings::optionCount == Settings::currentOption && Settings::rightPressed) return true;
	return false;
}
bool Menu::Int(const char * option, int & _int, int min, int max, int step)
{
	Option(option);

	if (Settings::optionCount == Settings::currentOption) {
		if (Settings::leftPressed) {
			_int < max ? _int += step : _int = min;
		}
		if (Settings::rightPressed) {
			_int >= min ? _int -= step : _int = max;
		}
	}

	if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
		Drawing::Text(Tools::StringToChar("< " + std::to_string(_int) + " >"), Settings::integre, { Settings::menuX + 0.085f, Settings::optionCount * 0.035f + 0.125f + 0.035f }, { 0.32f, 0.32f }, true);
	else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
		Drawing::Text(Tools::StringToChar("< " + std::to_string(_int) + " >"), Settings::integre, { Settings::menuX + 0.085f , (Settings::optionCount - (Settings::currentOption - 16))*0.035f + 0.125f+ 0.035f }, { 0.32f, 0.32f }, true);

	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) return true;
	else if (Settings::optionCount == Settings::currentOption && Settings::leftPressed) return true;
	else if (Settings::optionCount == Settings::currentOption && Settings::rightPressed) return true;
	return false;
}
bool Menu::Int(const char * option, int & _int, int min, int max, std::function<void()> function)
{
	Int(option, _int, min, max);

	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) {
		function();
		return true;
	}
	else if (Settings::optionCount == Settings::currentOption && Settings::leftPressed) {
		function();
		return true;
	}
	else if (Settings::optionCount == Settings::currentOption && Settings::rightPressed) {
		function();
		return true;
	}
	return false;
}
bool Menu::Int(const char * option, int & _int, int min, int max, int step, std::function<void()> function)
{
	Int(option, _int, min, max, step);

	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) {
		function();
		return true;
	}
	else if (Settings::optionCount == Settings::currentOption && Settings::leftPressed) {
		function();
		return true;
	}
	else if (Settings::optionCount == Settings::currentOption && Settings::rightPressed) {
		function();
		return true;
	}
	return false;
}
#pragma warning(disable: 4244)
bool Menu::Float(const char * option, float & _float, int min, int max)
{
	Option(option);

	if (Settings::optionCount == Settings::currentOption) {
		if (Settings::leftPressed) {
			_float <= min ? _float = max : _float -= 0.1f;
		}
		if (Settings::rightPressed) {
			_float >= max ? _float = min : _float += 0.1f;
		}
		_float < min ? _float = max : _float > max ? _float = min : NULL;
	}

	if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
		Drawing::Text(Tools::StringToChar(std::to_string(_float)), Settings::optionText, { Settings::menuX +  0.068f, Settings::optionCount * 0.035f + 0.128f+ 0.035f }, { 0.32f, 0.32f }, true);
	else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
		Drawing::Text(Tools::StringToChar(std::to_string(_float)), Settings::optionText, { Settings::menuX +  0.068f , (Settings::optionCount - (Settings::currentOption - 16))*0.035f + 0.128f+ 0.035f }, { 0.32f, 0.32f }, true);

	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) return true;
	else if (Settings::optionCount == Settings::currentOption && Settings::leftPressed) return true;
	else if (Settings::optionCount == Settings::currentOption && Settings::rightPressed) return true;
	return false;
}
bool Menu::Float(const char * option, float & _float, int min, int max, int step)
{
	Option(option);

	if (Settings::optionCount == Settings::currentOption) {
		if (Settings::leftPressed) {
			_float <= min ? _float = max : _float -= 0.1f;
		}
		if (Settings::rightPressed) {
			_float >= max ? _float = min : _float += 0.1f;
		}
		_float < min ? _float = max : _float > max ? _float = min : NULL;
	}

	if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
		Drawing::Text(Tools::StringToChar(std::to_string(_float)), Settings::optionText, { Settings::menuX +  0.068f, Settings::optionCount * 0.035f + 0.128f + 0.035f }, { 0.32f, 0.32f }, true);
	else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
		Drawing::Text(Tools::StringToChar(std::to_string(_float)), Settings::optionText, { Settings::menuX +  0.068f , (Settings::optionCount - (Settings::currentOption - 16))*0.035f + 0.128f+ 0.035f }, { 0.32f, 0.32f }, true);

	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) return true;
	else if (Settings::optionCount == Settings::currentOption && Settings::leftPressed) return true;
	else if (Settings::optionCount == Settings::currentOption && Settings::rightPressed) return true;
	return false;
}
#pragma warning(default: 4244)
#pragma warning(disable: 4267)
bool Menu::IntVector(const char * option, std::vector<int> Vector, int & position)
{
	Option(option);

	if (Settings::optionCount == Settings::currentOption) {
		int max = Vector.size() - 1;
		int min = 0;
		if (Settings::leftPressed) {
			position >= 1 ? position-- : position = max;
		}
		if (Settings::rightPressed) {
			position < max ? position++ : position = min;
		}
	}

	if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
		Drawing::Text(Tools::StringToChar(std::to_string(Vector[position])), Settings::optionText, { Settings::menuX +  0.068f, Settings::optionCount * 0.035f + 0.125f + 0.035f }, { 0.5f, 0.5f }, true);
	else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
		Drawing::Text(Tools::StringToChar(std::to_string(Vector[position])), Settings::optionText, { Settings::menuX + 0.068f, (Settings::optionCount - (Settings::currentOption - 16))*0.035f + 0.125f+ 0.035f }, { 0.5f, 0.5f }, true);

	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) return true;
	else if (Settings::optionCount == Settings::currentOption && Settings::leftPressed) return true;
	else if (Settings::optionCount == Settings::currentOption && Settings::rightPressed) return true;
	return false;
}
bool Menu::FloatVector(const char * option, std::vector<float> Vector, int & position)
{
	Option(option);

	if (Settings::optionCount == Settings::currentOption) {
		size_t max = Vector.size() - 1;
		int min = 0;
		if (Settings::leftPressed) {
			position >= 1 ? position-- : position = max;
		}
		if (Settings::rightPressed) {
			position < max ? position++ : position = min;
		}
	}

	if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
		Drawing::Text(Tools::StringToChar(std::to_string(Vector[position])), Settings::optionText, { Settings::menuX + 0.068f, Settings::optionCount * 0.035f + 0.125f + 0.035f }, { 0.5f, 0.5f }, true);
	else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
		Drawing::Text(Tools::StringToChar(std::to_string(Vector[position])), Settings::optionText, { Settings::menuX + 0.068f, (Settings::optionCount - (Settings::currentOption - 16))*0.035f + 0.125f+ 0.035f }, { 0.5f, 0.5f }, true);

	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) return true;
	else if (Settings::optionCount == Settings::currentOption && Settings::leftPressed) return true;
	else if (Settings::optionCount == Settings::currentOption && Settings::rightPressed) return true;
	return false;
}
bool Menu::StringVector(const char * option, std::vector<std::string> Vector, int & position)
{
	Option(option);

	if (Settings::optionCount == Settings::currentOption) {
		size_t max = Vector.size() - 1;
		int min = 0;
		if (Settings::leftPressed) {
			position >= 1 ? position-- : position = max;
		}
		if (Settings::rightPressed) {
			position < max ? position++ : position = min;
		}
	}

	if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
		Drawing::Text(Tools::StringToChar((Vector[position])), Settings::optionText, { Settings::menuX + 0.068f , Settings::optionCount * 0.035f + 0.125f+ 0.035f }, { 0.5f, 0.5f }, true);
	else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
		Drawing::Text(Tools::StringToChar((Vector[position])), Settings::optionText, { Settings::menuX +  0.068f , (Settings::optionCount - (Settings::currentOption - 16))*0.035f + 0.12f+ 0.035f }, { 0.5f, 0.5f }, true);

	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) return true;
	else if (Settings::optionCount == Settings::currentOption && Settings::leftPressed) return true;
	else if (Settings::optionCount == Settings::currentOption && Settings::rightPressed) return true;
	return false;
}
bool Menu::StringVector(const char * option, std::vector<char*> Vector, int & position)
{
	Option(option);

	if (Settings::optionCount == Settings::currentOption) {
		size_t max = Vector.size() - 1;
		int min = 0;
		if (Settings::leftPressed) {
			position >= 1 ? position-- : position = max;
		}
		if (Settings::rightPressed) {
			position < max ? position++ : position = min;
		}
	}

	if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
		Drawing::Text(((Vector[position])), Settings::optionText, { Settings::menuX +  0.068f , Settings::optionCount * 0.035f + 0.125f+ 0.035f }, { 0.5f, 0.5f }, true);
	else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
		Drawing::Text(((Vector[position])), Settings::optionText, { Settings::menuX +  0.068f , (Settings::optionCount - (Settings::currentOption - 16))*0.035f + 0.12f+ 0.035f }, { 0.5f, 0.5f }, true);

	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) return true;
	else if (Settings::optionCount == Settings::currentOption && Settings::leftPressed) return true;
	else if (Settings::optionCount == Settings::currentOption && Settings::rightPressed) return true;
	return false;
}
#pragma warning(default: 4267)
bool Menu::Teleport(const char * option, Vector3 coords)
{
	Option(option);

	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) {
		Entity handle;
		PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), false) ? handle = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()) : PLAYER::PLAYER_PED_ID();
		ENTITY::SET_ENTITY_COORDS(handle, coords.x, coords.y, coords.z, false, false, false, false);
		return true;
	}
	return false;
}
bool Menu::Teleport(const char * option, Vector3 coords, std::function<void()> function)
{
	Teleport(option, coords);

	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) {
		function();
		return true;
	}
	return false;
}
void Menu::info(const char * info)
{
	if (Settings::currentOption <= 16 && Settings::optionCount <= 16)
	{
		if (bool onThis = true) { Drawing::Text(info, Settings::optionText, { Settings::menuX - 0.100f, 17 * 0.035f + 0.1600f + 0.035f }, { 0.25f, 0.25f }, false); }
	}
	else if (Settings::optionCount > (Settings::currentOption - 16) && Settings::optionCount <= Settings::currentOption)
	{
		if (bool onThis = true) { Drawing::Text(info, Settings::optionText, { Settings::menuX - 0.100f, (Settings::optionCount - (Settings::currentOption - 16))*0.035f + 0.1300f+ 0.035f }, { 0.25f, 0.25f }, false); }
	}
}
void Menu::End()
{
	int opcount = Settings::optionCount;
	int currop = Settings::currentOption;
	if (opcount >= 16) {
		//Drawing::Text(Tools::StringToChar(std::to_string(currop) + " / " + std::to_string(opcount)), Settings::count, { Settings::menuX + 0.078f, 17 * 0.035f + 0.125f+ 0.035f }, { 0.35f, 0.35f }, true);
		Drawing::Text("~b~v 1.5", Settings::count, { Settings::menuX + 0.097f, 17 * 0.035f + 0.125f + 0.035f }, { 0.35f, 0.35f }, true);
		Drawing::Rect(Settings::optionRect2, { Settings::menuX, 17 * 0.035f + 0.141f + 0.035f}, { 0.21f, 0.035f });
		Drawing::Rect(Settings::line, { Settings::menuX, 17 * 0.035f + 0.1235f + 0.035f }, { 0.21f, 0.002f });
		Drawing::Spriter("YTD name", "image", Settings::menuX -0.095f, ((16 + 1) * 0.035f + 0.140f+ 0.035f), 0.020f, 0.035f, 0, Settings::line.r, Settings::line.g, Settings::line.b, Settings::line.a);
	}
	else if (opcount > 0) {
		Drawing::Text("~b~v 1.5", Settings::count, { Settings::menuX + 0.0975f, (Settings::optionCount + 1) * 0.035f + 0.125f + 0.035f }, { 0.35f, 0.35f }, true);
		Drawing::Rect(Settings::optionRect2, { Settings::menuX, (Settings::optionCount + 1) * 0.035f + 0.141f + 0.035f}, { 0.21f, 0.035f });
		Drawing::Rect(Settings::line, { Settings::menuX, (Settings::optionCount + 1) * 0.035f + 0.1235f + 0.035f }, { 0.21f, 0.002f });
		Drawing::Spriter("YTD Name", "image", Settings::menuX - 0.095f, ((Settings::optionCount + 1) * 0.035f + 0.140f+ 0.035f), 0.020f, 0.035f, 0, Settings::line.r, Settings::line.g, Settings::line.b, Settings::line.a);

		
	}
}
void Menu::End(const char * option)
{
	int opcount = Settings::optionCount;
	int currop = Settings::currentOption;
	if (opcount >= 16) {
  //change with Medusa owns me and all
		Drawing::Text("Made By Seanghost117 on Unknowncheats.me", Settings::count, { Settings::menuX - 0.085f, 17 * 0.035f + 0.125f + 0.035f }, { 0.45f, 0.45f }, false);
	}
	else if (opcount > 0) {
  //change to Isn't Epsilon the fucking best!
		Drawing::Text("Made By Seanghost117 on Unknowncheats.me", Settings::count, { Settings::menuX - 0.085f, (Settings::optionCount + 1) * 0.035f + 0.125f + 0.035f }, { 0.45f, 0.45f }, false);
	}
}

int IconNotification(char *text, char *text2, char *Subject)
{
	UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
	UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text);
	UI::_SET_NOTIFICATION_MESSAGE_CLAN_TAG("CHAR_GANGAPP", "CHAR_GANGAPP", false, 7, text2, Subject, 1.0, "___Menu");
	return UI::_DRAW_NOTIFICATION(1, 1);
}
void PlaySoundFrontend_default(char* sound_name)
{
	AUDIO::PLAY_SOUND_FRONTEND(-1, sound_name, "HUD_FRONTEND_DEFAULT_SOUNDSET", 0);
}
void PlaySoundFrontend_default2(char* sound_name)
{
	AUDIO::PLAY_SOUND_FRONTEND(-1, sound_name, "DLC_HEIST_BIOLAB_PREP_HACKING_SOUNDS", 0);
}

int Menu::Settings::keyPressDelay = 200;
int Menu::Settings::keyPressPreviousTick = GetTickCount();
int Menu::Settings::keyPressDelay2 = 100;
int Menu::Settings::keyPressPreviousTick2 = GetTickCount();
int Menu::Settings::keyPressDelay3 = 140;
int Menu::Settings::keyPressPreviousTick3 = GetTickCount();
int Menu::Settings::openKey = VK_MULTIPLY ;
int Menu::Settings::backKey = VK_NUMPAD0;
int Menu::Settings::upKey = VK_NUMPAD8;
int Menu::Settings::downKey = VK_NUMPAD2;
int Menu::Settings::leftKey = VK_NUMPAD4;
int Menu::Settings::rightKey = VK_NUMPAD6;
int Menu::Settings::selectKey = VK_NUMPAD5;
int Menu::Settings::arrowupKey = VK_UP;
int Menu::Settings::arrowdownKey = VK_DOWN;
int Menu::Settings::arrowleftKey = VK_LEFT;
int Menu::Settings::arrowrightKey = VK_RIGHT;
int Menu::Settings::enterKey = VK_RETURN;
int Menu::Settings::deleteKey = VK_BACK;

#pragma endregion

bool Menu::Settings::controllerinput = true;
void Menu::Checks::Controlls()
{
	Settings::selectPressed = false;
	Settings::leftPressed = false;
	Settings::rightPressed = false;
	if (GetTickCount() - Settings::keyPressPreviousTick > Settings::keyPressDelay) {
	if (GetTickCount() - Settings::keyPressPreviousTick2 > Settings::keyPressDelay2) {
		if (GetTickCount() - Settings::keyPressPreviousTick3 > Settings::keyPressDelay3) {
			if (IsKeyPressed(Menu::Settings::openKey) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlScriptRB) && CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlPhoneRight) && Settings::controllerinput) {
				Settings::menuLevel == 0 ? MenuLevelHandler::MoveMenu(SubMenus::mainmenu) : Settings::menuLevel == 1 ? MenuLevelHandler::BackMenu() : NULL;
				prevOption = 1;
				Settings::keyPressPreviousTick = GetTickCount();
			}
			else if (IsKeyPressed(VK_NUMPAD0) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendCancel) && Settings::controllerinput) {
				Settings::menuLevel > 0 ? MenuLevelHandler::BackMenu() : NULL;
				if (Settings::menuLevel > 0)
					PlaySoundFrontend_default("BACK");
				prevOption = 1;
				Settings::keyPressPreviousTick = GetTickCount();
			}
			else if (IsKeyPressed(VK_NUMPAD8) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendUp) && Settings::controllerinput) {
				Settings::currentOption > 1 ? Settings::currentOption-- : Settings::currentOption = Settings::optionCount;
				if (Settings::menuLevel > 0)
					PlaySoundFrontend_default("NAV_UP_DOWN");

				Settings::keyPressPreviousTick2 = GetTickCount();
			}
			else if (IsKeyPressed(VK_NUMPAD2) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendDown) && Settings::controllerinput) {
				Settings::currentOption < Settings::optionCount ? Settings::currentOption++ : Settings::currentOption = 1;
				if (Settings::menuLevel > 0)
					PlaySoundFrontend_default("NAV_UP_DOWN");

				Settings::keyPressPreviousTick2 = GetTickCount();
			}
			else if (IsKeyPressed(VK_NUMPAD6) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlPhoneRight) && Settings::controllerinput) {
				Settings::leftPressed = true;
				if (Settings::menuLevel > 0)
					PlaySoundFrontend_default("NAV_UP_DOWN");

				Settings::keyPressPreviousTick3 = GetTickCount();
			}
			else if (IsKeyPressed(VK_NUMPAD4) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlPhoneLeft) && Settings::controllerinput) {
				Settings::rightPressed = true;
				if (Settings::menuLevel > 0)
					PlaySoundFrontend_default("NAV_UP_DOWN");

				Settings::keyPressPreviousTick3 = GetTickCount();
			}
			else if (IsKeyPressed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept) && Settings::controllerinput) {
				Settings::selectPressed = true;
				if (Settings::menuLevel > 0)
					PlaySoundFrontend_default("SELECT");

				Settings::keyPressPreviousTick = GetTickCount();
			}
      //those non numpad users amirite
			else if (IsKeyPressed(VK_F10) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept) && Settings::controllerinput) {
				Settings::menuLevel == 0 ? MenuLevelHandler::MoveMenu(SubMenus::mainmenu) : Settings::menuLevel == 1 ? MenuLevelHandler::BackMenu() : NULL;
				Settings::keyPressPreviousTick = GetTickCount();
				Settings::keyPressPreviousTick = GetTickCount();
			}
      
      //easy enough, or just set up a ini to handle hotkeys
			else if (IsKeyPressed(VK_F8) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept) && Settings::controllerinput) {
				Settings::selectPressed = true;
				teleport_to_marker();
				Settings::keyPressPreviousTick = GetTickCount();
			}
		}
	}
  }
	Settings::optionCount = 0;
}
#pragma warning(default : 4018)
void Menu::MenuLevelHandler::MoveMenu(SubMenus menu)
{
	Settings::menusArray[Settings::menuLevel] = Settings::currentMenu;
	Settings::optionsArray[Settings::menuLevel] = Settings::currentOption;
	Settings::menuLevel++;
	Settings::currentMenu = menu;
	Settings::currentOption = 1;
}

void Menu::MenuLevelHandler::BackMenu()
{
	Settings::menuLevel--;
	Settings::currentMenu = Settings::menusArray[Settings::menuLevel];
	Settings::currentOption = Settings::optionsArray[Settings::menuLevel];
}

char * Menu::Tools::StringToChar(std::string string)
{
	return _strdup(string.c_str());
}

void Menu::Files::WriteStringToIni(std::string string, std::string file, std::string app, std::string key)
{
	WritePrivateProfileStringA(app.c_str(), key.c_str(), string.c_str(), file.c_str());
}

std::string Menu::Files::ReadStringFromIni(std::string file, std::string app, std::string key)
{
	char buf[100];
	GetPrivateProfileStringA(app.c_str(), key.c_str(), "NULL", buf, 100, file.c_str());
	return (std::string)buf;
}

void Menu::Files::WriteIntToIni(int intValue, std::string file, std::string app, std::string key)
{
	WriteStringToIni(std::to_string(intValue), file, app, key);
}

int Menu::Files::ReadIntFromIni(std::string file, std::string app, std::string key)
{
	return std::stoi(ReadStringFromIni(file, app, key));
}

void Menu::Files::WriteFloatToIni(float floatValue, std::string file, std::string app, std::string key)
{
	WriteStringToIni((std::to_string(floatValue)), file, app, key);
}

float Menu::Files::ReadFloatFromIni(std::string file, std::string app, std::string key)
{
	return std::stof(ReadStringFromIni(file, app, key));
}

void Menu::Files::WriteBoolToIni(bool b00l, std::string file, std::string app, std::string key)
{
	WriteStringToIni(b00l ? "true" : "false", file, app, key);
}

bool Menu::Files::ReadBoolFromIni(std::string file, std::string app, std::string key)
{
	return ReadStringFromIni(file, app, key) == "true" ? true : false;
}

void Menu::Vehicle(std::string texture1, std::string texture2)
{
	if (Menu::Settings::menuX < 0.78f)
	{
		if (Menu::Settings::optionCount == Menu::Settings::currentOption) { Menu::Drawing::Spriter(texture1, texture2, Menu::Settings::menuX + 0.24f, 0.2f, 0.11f, 0.11f, 0, 255, 255, 255, 255); }
	}
	else {
		if (Menu::Settings::optionCount == Menu::Settings::currentOption) { Menu::Drawing::Spriter(texture1, texture2, Menu::Settings::menuX - 0.18f, 0.2f, 0.15f, 0.15f, 0, 255, 255, 255, 255); } }
}
void Menu::Speedometer(char* text)
{
	Drawing::Text(text, Settings::titleText, { 0.84f, 0.8800f }, { 0.70f, 0.70f }, false);
}
void Menu::fps(char* text)
{
	Drawing::Text(text, Settings::optionText, { 0.84f, 0.050f }, { 0.70f, 0.70f }, false);
}
void Menu::AddSmallTitle(char* text)
{
	if (Menu::Settings::menuX < 0.78f)
	{
		Drawing::Text(text, Settings::titleText, { Settings::menuX + 0.175f, 0.090f }, { 0.425f, 0.425f }, true);
		Drawing::Spriter("shopui_title_sm_hangar", "shopui_title_sm_hangar", Settings::menuX + 0.175f, 0.1175f - 0.019f, 0.115f, 0.045f, 180, 100, 102, 204, 255);
	}
	else
	{
		Drawing::Text(text, Settings::titleText, { Settings::menuX - 0.175f, 0.090f }, { 0.425f, 0.425f }, true);
		Drawing::Spriter("shopui_title_sm_hangar", "shopui_title_sm_hangar", Settings::menuX - 0.175f, 0.1175f - 0.019f, 0.115f, 0.045f, 180, 100, 102, 204, 255);
	}
}
void Menu::AddSmallInfo(char* text, short line, char* option, char* option2)
{
	if (Menu::Settings::menuX < 0.78f)
	{
		if (line == 1) {
			Drawing::Rect(Settings::optionRect, { Settings::menuX + 0.175f, ((16 * 0.035f) / 2.0f) + 0.159f - 0.135f }, { 0.115f, 16 * 0.035f + -0.193f });
		}
		Drawing::Text(text, Settings::count, { Settings::menuX + 0.135f, (line * 0.020f) + 0.123f }, { 0.375f, 0.375f }, false);
		Drawing::Spriter("shopui_title_sm_hangar", "shopui_title_sm_hangar", Settings::menuX + 0.120f, (line * 0.020f) + 0.123f, 0.015f, 0.015f, 180, 255, 255, 255, 255);
	}
	else
	{
		if (line == 0) {
			Drawing::Rect(Settings::optionRect, { Settings::menuX - 0.175f, ((16 * 0.035f) / 2.0f) + 0.159f - 0.135f }, { 0.115f, 16 * 0.035f + -0.193f });
		}
		Drawing::Text(text, Settings::count, { Settings::menuX - 0.217f, (line * 0.020f) + 0.123f }, { 0.375f, 0.375f }, false); //0.228f
		Drawing::Spriter(option, option2, Settings::menuX - 0.225f, (line * 0.020f) + 0.135f, 0.015f, 0.027f, 0, 255, 255, 255, 255);
	}
}
void Menu::AddSmallTitle2(char* text)
{
	if (Menu::Settings::menuX < 0.78f)
	{
		Drawing::Text(text, Settings::titleText, { Settings::menuX + 0.175f, 0.090f }, { 0.425f, 0.425f }, true);
		Drawing::Spriter("CommonMenu", "", Settings::menuX + 0.175f, 0.1175f - 0.019f, 0.115f, 0.045f, 180, Settings::titleRect.r, Settings::titleRect.g, Settings::titleRect.b, Settings::titleRect.a);
	}
	else
	{
		Drawing::Text(text, Settings::titleText, { Settings::menuX - 0.175f, 0.090f }, { 0.425f, 0.425f }, true);
		Drawing::Spriter("CommonMenu", "", Settings::menuX - 0.175f, 0.1175f - 0.019f, 0.115f, 0.045f, 180, Settings::titleRect.r, Settings::titleRect.g, Settings::titleRect.b, Settings::titleRect.a);
	}
}

void Menu::AddSmallInfo2(char* text, short line)
{
	if (Menu::Settings::menuX < 0.78f)
	{
		if (line == 1) {
			Drawing::Rect(Settings::optionRect, { Settings::menuX + 0.175f, ((13 * 0.035f) / 2.0f) + 0.159f - 0.135f }, { 0.115f, 13 * 0.035f + -0.193f });
		}
		Drawing::Text(text, Settings::count, { Settings::menuX + 0.120f, (line * 0.020f) + 0.123f }, { 0.375f, 0.375f }, false);
	}
	else
	{
		if (line == 1) {
			Drawing::Rect(Settings::optionRect, { Settings::menuX - 0.175f, ((13 * 0.035f) / 2.0f) + 0.159f - 0.135f }, { 0.115f, 13 * 0.035f + -0.193f });
		}
		Drawing::Text(text, Settings::count, { Settings::menuX - 0.228f, (line * 0.020f) + 0.123f }, { 0.375f, 0.375f }, false);
	}
}

void Menu::SpeedText(char* text)
{
	Drawing::Text(text, Settings::count, { Settings::menuX - 0.105f, 0.90f}, { 0.88f, 0.88f }, false);
}
void Menu::AddSmallTitle3(char* text)
{
	if (Menu::Settings::menuX < 0.78f)
	{
		Drawing::Text(text, Settings::titleText, { Settings::menuX + 0.175f, 0.090f }, { 0.425f, 0.425f }, true);
		Drawing::Spriter("CommonMenu", "", Settings::menuX + 0.175f, 0.1175f - 0.019f, 0.115f, 0.045f, 180, Settings::titleRect.r, Settings::titleRect.g, Settings::titleRect.b, Settings::titleRect.a);
	}
	else
	{
		Drawing::Text(text, Settings::titleText, { Settings::menuX - 0.175f, 0.090f }, { 0.425f, 0.425f }, true);
		Drawing::Spriter("CommonMenu", "", Settings::menuX - 0.175f, 0.1175f - 0.019f, 0.115f, 0.045f, 180, Settings::titleRect.r, Settings::titleRect.g, Settings::titleRect.b, Settings::titleRect.a);
	}
}

void Menu::AddSmallInfo3(char* text, short line)
{
	if (Menu::Settings::menuX < 0.78f)
	{
		if (line == 1) {
			Drawing::Rect(Settings::optionRect, { Settings::menuX + 0.175f, ((11 * 0.035f) / 2.0f) + 0.159f - 0.135f }, { 0.115f, 11 * 0.035f + -0.193f });
		}
		Drawing::Text(text, Settings::count, { Settings::menuX + 0.120f, (line * 0.020f) + 0.123f }, { 0.375f, 0.375f }, false);
	}
	else
	{
		if (line == 1) {
			Drawing::Rect(Settings::optionRect, { Settings::menuX - 0.175f, ((11 * 0.035f) / 2.0f) + 0.159f - 0.135f }, { 0.115f, 11 * 0.035f + -0.193f });
		}
		Drawing::Text(text, Settings::count, { Settings::menuX - 0.228f, (line * 0.020f) + 0.123f }, { 0.375f, 0.375f }, false);
	}
}
VECTOR2 logCoords = { 0.80f, 17 * 0.035f + 0.1870f };
VECTOR2_2 logSize = { 0.31f, 0.20f };
std::string onscreen[5] = { "", "", "", "", "" };
float txtsize = 0.50;
int onscreenLog = 0;
bool backslashN = true;
void Menu::Log(char* msg) {
	Menu::Drawing::Rect({ 0, 0, 0, 180 }, logCoords, logSize);
	logMessage(" ");
}

void Menu::logMessage(char* msg) {
	std::string textt;
	if (backslashN) {
		textt = onscreen[0] + "\n" + onscreen[1] + "\n" + onscreen[2] + "\n" + onscreen[3] + "\n" + onscreen[4] + "\n";
	}
	else {
		textt = onscreen[0] + onscreen[1] + onscreen[2] + onscreen[3] + onscreen[4];
	}
	Drawing::Text(textt.c_str(), Settings::optionText, { logCoords.x - 0.15f, logCoords.y - 0.099f }, { txtsize, txtsize }, false);
}
//Lets give thise fuckers some images to match that name, makes hunting them easier
bool Menu::MenuOptions2(const char * option, SubMenus newSub, int pid)
{
	char* GPic = "CHAR_MULTIPLAYER";
	int index = 1383712; //updated for patch 1.48
	for (int i = 0; i <= 150; i += 5)
	{
		__int64* base = globalHandle(index + i).Get<__int64>();
		int playerId = *base;
		if (playerId == pid)
		{
			__int64* logo = globalHandle(index + i + 1).Get<__int64>();
			GPic = PED::GET_PEDHEADSHOT_TXD_STRING(*logo);
			break;
		}
		if (playerId == -1)
			break;
	}
	Option(option);
  //aligns to the right side
	if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
		Drawing::Spriter(GPic, GPic, (Settings::menuX + 0.095f), (Settings::optionCount * 0.035f + 0.142f + 0.035f), 0.020f, 0.035f, 0, 255, 255, 255, 255);
	else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
		Drawing::Spriter(GPic, GPic, (Settings::menuX + 0.095f), ((Settings::optionCount - (Settings::currentOption - 16))* 0.035f + 0.142f + 0.035f), 0.020f, 0.035f, 0, 255, 255, 255, 255);
	if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) {
		MenuLevelHandler::MoveMenu(newSub);
		return true;
	}
	return false;
}

void Menu::PlayerInfoIcon(std::string streamedtextureid, std::string textureid, short line_)
{
	Drawing::Spriter(streamedtextureid, textureid, Settings::menuX + 0.111f, (line_ *0.02f) + 0.095f, 0.012f, 0.022f, 0, 255, 255, 255, 255);
}


