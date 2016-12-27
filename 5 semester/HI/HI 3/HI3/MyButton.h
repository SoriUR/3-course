#pragma once
#include <Windows.h>

#define ClassName "button"
#define MB_CLASSIC WS_CHILD | WS_BORDER 
#define STD_WIDTH 200
#define STD_HEIGHT 50
#define STD_ID -1
#define STD_TITLE "Button"


class MyButton
{
public:
	MyButton::MyButton(int = STD_ID, HWND = NULL, LPSTR = STD_TITLE, DWORD = MB_CLASSIC, int = 0, int = 0, int = 100, int = 50);
	void setOwner(HWND);
	void setPozition(int = 0, int = 0);
	void setID(int);
	~MyButton();
private:
	LPSTR _title;
	DWORD _style;
	int _left, _top, _width, _height;
	HMENU _id;
	HWND _owner;
	HWND hButton;
};
