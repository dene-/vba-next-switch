#pragma once

#include "colors.h"
#include "image.h"

#define COLOR_WHITE FC_MakeColor(255, 255, 255, 255)
#define COLOR_BLACK FC_MakeColor(0, 0, 0, 255)
#define COLOR_BLUE  FC_MakeColor(29, 50, 243, 255)
#define COLOR_GREEN FC_MakeColor(0, 254, 197, 255)
#define COLOR_RED   FC_MakeColor(255, 81, 48, 255)
#define COLOR_GOLD  FC_MakeColor(255, 215, 0, 255)

#define COLOR_GREY_BG     FC_MakeColor(51, 51, 51, 255)
#define COLOR_GREY_DARKER FC_MakeColor(70, 70, 70, 255)
#define COLOR_GREY_DARK   FC_MakeColor(79, 79, 79, 255)
#define COLOR_GREY_MEDIUM FC_MakeColor(94, 94, 94, 255)
#define COLOR_GREY_LIGHT  FC_MakeColor(138, 138, 138, 255)

typedef struct {
	SDL_Color backgroundColor;
	SDL_Color textColor;
	SDL_Color textActiveColor;
	SDL_Color textActiveBGColor;
	SDL_Color keyboardBackgroundColor;
	SDL_Color keyboardKeyBackgroundColor;
	SDL_Color keyboardSPKeyTextColor;
	SDL_Color keyboardSPKeyBackgroundColor;
	SDL_Color keyboardOKKeyTextColor;
	SDL_Color keyboardOKKeyBackgroundColor;
	SDL_Color keyboardHighlightColor;
	SDL_Texture* btnA;
	SDL_Texture* btnB;
	SDL_Texture* btnX;
	SDL_Texture* btnY;
	SDL_Texture* splashImage;
} theme_t;

typedef enum {
	modeLight,
	modeDark,
} themeMode_t;

enum { switchTheme, darkTheme, lightTheme };

void themeInit();
void themeDeinit();

void themeSet(themeMode_t t);

extern theme_t currentTheme;