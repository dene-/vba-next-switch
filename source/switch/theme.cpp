#include "theme.h"

void setTheme(themeMode t) {
    switch (t) {
        case LIGHT:
            THEME.backgroundColor = MakeColor(239, 239, 239, 255);
            THEME.textColor = MakeColor(45, 45, 45, 255);
            THEME.textActiveColor = MakeColor(50, 80, 240, 255);
            THEME.textActiveBGColor = MakeColor(253, 253, 253, 255);
            break;
        case DARK:
            THEME.backgroundColor = MakeColor(45, 45, 45, 255);
            THEME.textColor = MakeColor(255, 255, 255, 255);
            THEME.textActiveColor = MakeColor(0, 255, 197, 255);
            THEME.textActiveBGColor = MakeColor(33, 34, 39, 255);
            break;        
    }
}

theme_t THEME;