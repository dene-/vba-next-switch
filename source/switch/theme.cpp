#include "theme.h"

static SDL_Texture* btnADark;
static SDL_Texture* btnALight;
static SDL_Texture* btnBDark;
static SDL_Texture* btnBLight;
static SDL_Texture* btnXDark;
static SDL_Texture* btnXLight;
static SDL_Texture* btnYDark;
static SDL_Texture* btnYLight;
static SDL_Texture* splashWhite;
static SDL_Texture* splashBlack;

void themeInit() {
	SDLH_LoadImage(&btnADark, "romfs:/btnADark.png");
	SDLH_LoadImage(&btnALight, "romfs:/btnALight.png");
	SDLH_LoadImage(&btnBDark, "romfs:/btnBDark.png");
	SDLH_LoadImage(&btnBLight, "romfs:/btnBLight.png");
	SDLH_LoadImage(&btnXDark, "romfs:/btnXDark.png");
	SDLH_LoadImage(&btnXLight, "romfs:/btnXLight.png");
	SDLH_LoadImage(&btnYDark, "romfs:/btnYDark.png");
	SDLH_LoadImage(&btnYLight, "romfs:/btnYLight.png");

	SDLH_LoadImage(&splashWhite, "romfs:/splashWhite.png");
	SDLH_LoadImage(&splashBlack, "romfs:/splashBlack.png");
}

void themeDeinit() {
	SDL_DestroyTexture(splashWhite);
	SDL_DestroyTexture(splashBlack);

	SDL_DestroyTexture(btnADark);
	SDL_DestroyTexture(btnALight);
	SDL_DestroyTexture(btnBDark);
	SDL_DestroyTexture(btnBLight);
	SDL_DestroyTexture(btnXDark);
	SDL_DestroyTexture(btnXLight);
	SDL_DestroyTexture(btnYDark);
	SDL_DestroyTexture(btnYLight);
}

void themeSet(themeMode_t t) {
	switch (t) {
		case modeLight:
			currentTheme.backgroundColor = FC_MakeColor(239, 239, 239, 255);
			currentTheme.textColor = FC_MakeColor(45, 45, 45, 255);
			currentTheme.textActiveColor = FC_MakeColor(50, 80, 240, 255);
			currentTheme.textActiveBGColor = FC_MakeColor(253, 253, 253, 255);
			currentTheme.keyboardBackgroundColor = FC_MakeColor(240, 240, 240, 255);
			currentTheme.keyboardKeyBackgroundColor = FC_MakeColor(231, 231, 231, 255);
			currentTheme.keyboardSPKeyTextColor = FC_MakeColor(155, 155, 155, 255);
			currentTheme.keyboardSPKeyBackgroundColor = FC_MakeColor(218, 218, 218, 255);
			currentTheme.keyboardOKKeyTextColor = FC_MakeColor(253, 253, 253, 255);
			currentTheme.keyboardOKKeyBackgroundColor = FC_MakeColor(50, 80, 240, 255);
			currentTheme.keyboardHighlightColor = FC_MakeColor(16, 178, 203, 255);
			currentTheme.btnA = btnADark;
			currentTheme.btnB = btnBDark;
			currentTheme.btnX = btnXDark;
			currentTheme.btnY = btnYDark;
			currentTheme.splashImage = splashWhite;
			break;
		case modeDark:
			currentTheme.backgroundColor = FC_MakeColor(45, 45, 45, 255);
			currentTheme.textColor = FC_MakeColor(255, 255, 255, 255);
			currentTheme.textActiveColor = FC_MakeColor(0, 255, 197, 255);
			currentTheme.textActiveBGColor = FC_MakeColor(33, 34, 39, 255);
			currentTheme.keyboardBackgroundColor = FC_MakeColor(70, 70, 70, 255);
			currentTheme.keyboardKeyBackgroundColor = FC_MakeColor(79, 79, 79, 255);
			currentTheme.keyboardSPKeyTextColor = FC_MakeColor(150, 150, 150, 255);
			currentTheme.keyboardSPKeyBackgroundColor = FC_MakeColor(96, 96, 96, 255);
			currentTheme.keyboardOKKeyTextColor = FC_MakeColor(33, 77, 90, 255);
			currentTheme.keyboardOKKeyBackgroundColor = FC_MakeColor(0, 248, 211, 255);
			currentTheme.keyboardHighlightColor = FC_MakeColor(134, 241, 247, 255);
			currentTheme.btnA = btnALight;
			currentTheme.btnB = btnBLight;
			currentTheme.btnX = btnXLight;
			currentTheme.btnY = btnYLight;
			currentTheme.splashImage = splashBlack;
			break;
	}
}

theme_t currentTheme;