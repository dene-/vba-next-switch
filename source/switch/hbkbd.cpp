/*
 *   This file is part of Checkpoint
 *   Copyright (C) 2017-2018 Bernardo Giordano
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *   Additional Terms 7.b and 7.c of GPLv3 apply to this file:
 *       * Requiring preservation of specified reasonable legal notices or
 *         author attributions in that material or in the Appropriate Legal
 *         Notices displayed by works containing it.
 *       * Prohibiting misrepresentation of the origin of that material,
 *         or requiring that modified versions of such material be marked in
 *         reasonable ways as different from the original version.
 */

#include "hbkbd.h"
#include "theme.h"
#include "ui.h"

static const u32 buttonSpacing = 4;
static const u32 normalWidth = 92;
static const u32 bigWidth = 116;
static const u32 height = 60;
static const u32 margintb = 63;
static const u32 marginlr = 54;
static const u32 starty = 720 - 450 + margintb;

static const std::string letters = "1234567890@qwertyuiop+asdfghjkl_:zxcvbnm,.-/";
static std::vector<HbkbdButton*> buttons;
static size_t prevSelectedButtonIndex;

static float keyRepeatWait;
static float keyRepeatWaitLength;

size_t hbkbd::count(void) { return buttons.size(); }

void hbkbd::hid(size_t& currentEntry, float dt) {
	static const size_t columns = 11;

	u64 kHeld = hidKeysHeld(CONTROLLER_P1_AUTO);
	bool sleep = false;

	u64 kUp = hidKeysUp(CONTROLLER_P1_AUTO);
	if (kUp & KEY_LEFT || kUp & KEY_RIGHT || kUp & KEY_DOWN || kUp & KEY_UP) {
		keyRepeatWaitLength = FASTSCROLL_WAIT;
		keyRepeatWait = 0.f;
	}

	keyRepeatWait -= dt;

	if (keyRepeatWait <= 0.f) {
		if (kHeld & KEY_LEFT) {
			switch (currentEntry) {
				case 0:		   // 1
				case columns:      // q
				case columns * 2:  // a
				case columns * 3:  // z
				case INDEX_CAPS:
					break;
				case INDEX_BACK:  // back -> @
					currentEntry = columns - 1;
					break;
				case INDEX_RETURN:  // return -> +
					currentEntry = columns * 2 - 1;
					break;
				case INDEX_OK:  // OK -> space
					currentEntry = INDEX_SPACE;
					break;
				case INDEX_SPACE:  // space -> caps
					currentEntry = INDEX_CAPS;
					break;
				default:
					currentEntry--;
			}
			sleep = true;
		} else if (kHeld & KEY_RIGHT) {
			switch (currentEntry) {
				case 10:  // @ -> back
					currentEntry = INDEX_BACK;
					break;
				case 21:  // + -> return
				case 32:  // : -> return
					currentEntry = INDEX_RETURN;
					break;
				case 43:	   // /-> OK
				case INDEX_SPACE:  // space -> OK
					currentEntry = INDEX_OK;
					break;
				case INDEX_CAPS:  // caps -> space
					currentEntry = INDEX_SPACE;
					break;
				case INDEX_BACK:
				case INDEX_RETURN:
				case INDEX_OK:
					break;
				default:
					currentEntry++;
			}
			sleep = true;
		} else if (kHeld & KEY_UP) {
			switch (currentEntry) {
				case 0 ... 10:  // 1 to @
				case INDEX_BACK:
					break;
				case INDEX_CAPS:  // caps -> x
					currentEntry = 34;
					break;
				case INDEX_SPACE:  // space -> .
					currentEntry = 41;
					break;
				case INDEX_RETURN:  // return -> back
					currentEntry = INDEX_BACK;
					break;
				case INDEX_OK:  // OK -> return
					currentEntry = INDEX_RETURN;
					break;
				default:
					currentEntry -= 11;
			}
			sleep = true;
		} else if (kHeld & KEY_DOWN) {
			switch (currentEntry) {
				case INDEX_CAPS:
				case INDEX_SPACE:
				case INDEX_OK:
					break;
				case 33 ... 35:  // z x c -> caps
					currentEntry = INDEX_CAPS;
					break;
				case 36 ... 43:  // v b n m , . - / -> space
					currentEntry = INDEX_SPACE;
					break;
				case INDEX_BACK:  // back -> return
					currentEntry = INDEX_RETURN;
					break;
				case INDEX_RETURN:  // return -> OK
					currentEntry = INDEX_OK;
					break;
				default:
					currentEntry += 11;
			}
			sleep = true;
		}
	}

	if (sleep) {
		keyRepeatWait = keyRepeatWaitLength;
		keyRepeatWaitLength *= FASTSCROLL_ACCL;
		if(keyRepeatWaitLength < FASTSCROLL_MAX_VEL) keyRepeatWait = FASTSCROLL_MAX_VEL;
	}
}

void hbkbd::init(void) {
	buttons.clear();

	// fill with the above characters
	for (size_t i = 0; i < 4; i++) {
		for (size_t j = 0; j < 11; j++) {
			HbkbdButton* button = new HbkbdButton(
			    marginlr + (buttonSpacing + normalWidth) * j, starty + (buttonSpacing + height) * i, normalWidth, height,
			    currentTheme.keyboardKeyBackgroundColor, currentTheme.textColor, letters.substr(i * 11 + j, 1), true);
			buttons.push_back(button);
		}
	}

	HbkbdButton* backspace = new HbkbdButton(marginlr + (buttonSpacing + normalWidth) * 11, starty, bigWidth, height,
						 currentTheme.keyboardSPKeyBackgroundColor, currentTheme.keyboardSPKeyTextColor, "←", true);
	buttons.push_back(backspace);

	HbkbdButton* returnb =
	    new HbkbdButton(marginlr + (buttonSpacing + normalWidth) * 11, starty + height + 4, bigWidth, height * 2 + 4,
			    currentTheme.keyboardSPKeyBackgroundColor, currentTheme.keyboardSPKeyTextColor, "return", true);
	buttons.push_back(returnb);

	HbkbdButton* ok =
	    new HbkbdButton(marginlr + (buttonSpacing + normalWidth) * 11, starty + height * 3 + 4 * 3, bigWidth, height * 2 + 4,
			    currentTheme.keyboardOKKeyBackgroundColor, currentTheme.keyboardOKKeyTextColor, "OK", true);
	buttons.push_back(ok);

	HbkbdButton* caps = new HbkbdButton(marginlr + buttonSpacing + normalWidth, starty + height * 4 + 4 * 4, normalWidth, height,
					    currentTheme.keyboardSPKeyBackgroundColor, currentTheme.textColor, "⇧", true);
	buttons.push_back(caps);

	HbkbdButton* spacebar =
	    new HbkbdButton(marginlr + (buttonSpacing + normalWidth) * 3, starty + height * 4 + 4 * 4, normalWidth * 8 + buttonSpacing * 7,
			    height, currentTheme.keyboardSPKeyBackgroundColor, currentTheme.textColor, "space", true);
	buttons.push_back(spacebar);

	// set first button as selected
	buttons.at(0)->selected(true);
	buttons.at(0)->invertColors();
	prevSelectedButtonIndex = 0;
}

void hbkbd::exit(void) {
	for (size_t i = 0, sz = buttons.size(); i < sz; i++) {
		delete buttons[i];
	}
}

static bool logic(std::string& str, size_t i) {
	if (buttons.at(i)->text().compare("⇧") == 0) {
		std::locale loc;
		bool islower = std::islower(buttons.at(11)->text()[0], loc);
		for (size_t t = 0; t < letters.length(); t++) {
			std::string l =
			    islower ? std::string(1, std::toupper(letters[t], loc)) : std::string(1, std::tolower(letters[t], loc));
			buttons.at(t)->text(l);
		}
	} else if (buttons.at(i)->text().compare("←") == 0) {
		if (!str.empty()) {
			str.erase(str.length() - 1);
		}
	} else if (buttons.at(i)->text().compare("space") == 0) {
		if (str.length() < CUSTOM_PATH_LEN) {
			str.append(" ");
		}
	} else if (buttons.at(i)->text().compare("return") == 0) {
		// str.append("\n");
	} else if (buttons.at(i)->text().compare("OK") == 0) {
		return true;
	} else if (str.length() < CUSTOM_PATH_LEN) {
		str.append(buttons.at(i)->text());
	}

	return false;
}

#define SECONDS_PER_TICKS (1.0 / 19200000)

std::string hbkbd::keyboard(const std::string& suggestion) {
	size_t index;
	std::string str;

	keyRepeatWait = 0.0;
	keyRepeatWaitLength = FASTSCROLL_WAIT;

	double lastTime = (double)svcGetSystemTick() * SECONDS_PER_TICKS;
	while (appletMainLoop() && !(hidKeysDown(CONTROLLER_P1_AUTO) & KEY_B)) {
		double time = (double)svcGetSystemTick() * SECONDS_PER_TICKS;
		double dt = time - lastTime;
		lastTime = time;

		hidScanInput();
		index = prevSelectedButtonIndex;

		// handle keys
		hid(index, dt);
		if (index != prevSelectedButtonIndex) {
			buttons.at(prevSelectedButtonIndex)->selected(false);
			buttons.at(prevSelectedButtonIndex)->invertColors();
			prevSelectedButtonIndex = index;
			buttons.at(index)->selected(true);
			buttons.at(prevSelectedButtonIndex)->invertColors();
		}

		if (hidKeysDown(CONTROLLER_P1_AUTO) & KEY_A) {
			bool ret = logic(str, index);
			if (ret) {
				return str.empty() ? suggestion : str;
			}
		}

		currentFB = gfxGetFramebuffer(&currentFBWidth, NULL);

		SDLH_DrawRect(0, 0, 1280, 270, COLOR_GREY_DARK);

		SDLH_DrawRect(marginlr, 140, 1280 - marginlr * 2, 84, COLOR_GREY_MEDIUM);		  // Text input background
		SDLH_DrawRect(0, starty - margintb, 1280, 450, currentTheme.keyboardBackgroundColor);  // Keyboard background

		u32 texth;
		getTextDimensions(font24, " ", NULL, &texth);
		if (str.empty()) {
			SDLH_DrawText(24, marginlr * 2, 140 + (84 - texth) / 2, COLOR_GREY_LIGHT,
				 suggestion.c_str());  // Text input placeholder
		} else {
			SDLH_DrawText(24, marginlr * 2, 140 + (84 - texth) / 2, COLOR_WHITE, str.c_str());  // Text input value
		}

		for (size_t i = 0, sz = buttons.size(); i < sz; i++) {
			if (buttons.at(i)->released()) {
				bool ret = logic(str, i);
				if (ret) {
					return str.empty() ? suggestion : str;
				}
			}

			// selection logic
			if (buttons.at(i)->held() && i != prevSelectedButtonIndex) {
				buttons.at(prevSelectedButtonIndex)->selected(false);
				buttons.at(prevSelectedButtonIndex)->invertColors();
				prevSelectedButtonIndex = i;
				buttons.at(i)->selected(true);
				buttons.at(i)->invertColors();
			}

			buttons.at(i)->draw();
		}

		uiDrawTipButton(buttonB, 1, "Cancel");
		uiDrawTipButton(buttonA, 2, "Enter");

		//gfxFlushBuffers();
		//gfxSwapBuffers();
		//gfxWaitForVsync();
	}

	return suggestion;
}