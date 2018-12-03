#pragma once
#include "stdafx.h"
#include "notes.h"

class Piano
{
private:
	vector<int> keyMap = { 'Q', '2', 'W', '3', 'E', 'R', '5', 'T', '6', 'Y', '7', 'U',
	'I', '9', 'O', '0', 'P', VK_OEM_4, VK_OEM_PLUS, VK_OEM_6, 'A', 'Z', 'S', 'X',
	'C', 'F', 'V', 'G', 'B', 'N', 'J', 'M', 'K', VK_OEM_COMMA, 'L', VK_OEM_PERIOD, VK_OEM_2 };
	vector<Note> notes;
	string keyboardDisplay;

	void loadKeyboard();

	bool previousKeyboardState[256];
	bool isKeyDown(int key);
	bool isKeyPressed(int key);
	bool isKeyReleased(int key);
	int pressedKey;

	int cols, rows;
public:
	Piano();
	~Piano();

	void checkInput();
	void updateKeyboardDisplay();
	void showKeyboard();
};

