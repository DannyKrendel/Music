#include "stdafx.h"
#include "piano.h"
#include "utility.h"

Piano::Piano()
{
	notes = createNotes(37, 4);
	loadKeyboard();
}

Piano::~Piano()
{
}

void Piano::loadKeyboard()
{
	ifstream fin("keyboardGraphics.txt");

	rows = count((istreambuf_iterator<char>(fin)), istreambuf_iterator<char>(), '\n') - 1;
	fin.seekg(0, ios::beg);

	string buf;
	getline(fin, buf);
	cols = buf.length() + 1;

	fin.seekg(0, ios::end);
	keyboardDisplay.reserve(fin.tellg());
	fin.seekg(0, ios::beg);

	keyboardDisplay.assign((istreambuf_iterator<char>(fin)), istreambuf_iterator<char>());

	fin.close();
}

bool Piano::isKeyDown(int key)
{
	return (GetAsyncKeyState(key) & (1 << 16));
}

bool Piano::isKeyPressed(int key)
{
	bool previousState = previousKeyboardState[key];

	previousKeyboardState[key] = isKeyDown(key);

	return (previousKeyboardState[key] && !previousState);
}

bool Piano::isKeyReleased(int key)
{
	bool previousState = previousKeyboardState[key];

	previousKeyboardState[key] = isKeyDown(key);

	return (!previousKeyboardState[key] && previousState);
}

void Piano::checkInput()
{
	for (int i = 0; i < keyMap.size() && i < notes.size(); i++)
	{
		if (isKeyPressed(keyMap[i]))
		{
			pressedKey = keyMap[i];
			updateKeyboardDisplay();
			notes[i].play(110);
		}
		if (isKeyReleased(pressedKey))
		{
			pressedKey = '\0';
			updateKeyboardDisplay();
		}
	}
}

void Piano::updateKeyboardDisplay()
{
	for (int i = 0; i < keyboardDisplay.length() - 131; i++)
	{
		char c = keyboardDisplay[i];

		if (c == '[')
			c = VK_OEM_4;
		else if (c == '=')
			c = VK_OEM_PLUS;
		else if (c == ']')
			c = VK_OEM_6;
		else if (c == ',')
			c = VK_OEM_COMMA;
		else if (c == '.')
			c = VK_OEM_PERIOD;
		else if (c == '/')
			c = VK_OEM_2;

		if (c != '|' && c != '+' && c != '-' && c != ' ' && c != '\n')
		{
			// Для черных клавиш
			if (i - 1 >= 0 && i + 1 < keyboardDisplay.size() && keyboardDisplay[i - 1] == '|' && keyboardDisplay[i + 1] == '|')
				writeCharAt(' ', i - (i / cols) * cols, i / cols);
			// Для белых клавиш
			else
				writeCharAt('#', i - (i / cols) * cols, i / cols);

			if (c == (char)pressedKey)
				writeCharAt('/', i - (i / cols) * cols, i / cols);
		}
	}
}

void Piano::showKeyboard()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	cout << keyboardDisplay.substr(0, cols * (rows + 1));
	SetConsoleTextAttribute(hConsole, 13);
	cout << keyboardDisplay.substr(cols * (rows + 1), cols);
	SetConsoleTextAttribute(hConsole, 15);
}
