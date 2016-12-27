#include "stdafx.h"
#include "MyButton.h"


MyButton::~MyButton()
{
	DestroyWindow(hButton);
}

MyButton::MyButton(int id, HWND hOwner, LPSTR title, DWORD style, int left, int top, int width, int height)
	: _id((HMENU)id), _owner(hOwner), _title(title), _style(style), _left(left), _top(top), _width(width), _height(height)
{
	hButton = CreateWindow(ClassName, _title,
		_style,
		_left, _top, _width, _height,
		_owner,
		_id,
		NULL,
		NULL);
	if (_owner != NULL)
		ShowWindow(hButton, SW_SHOW);
}

void MyButton::setOwner(HWND owner) {
	_owner = owner;
	hButton = CreateWindow(ClassName, _title, _style, _left, _top, _width, _height, _owner, _id, NULL, NULL);

	if (_owner != NULL)
		ShowWindow(hButton, SW_SHOW);
}

void MyButton::setPozition(int x, int y) {
	_left = x;
	_top = y;
	SetWindowPos(hButton, NULL, _left, _top, 0, 0, SWP_NOZORDER | SWP_NOSIZE | SWP_SHOWWINDOW | SWP_NOOWNERZORDER);
}

void MyButton::setID(int newID) {
	_id = (HMENU)newID;
	hButton = CreateWindow(ClassName, _title, _style, _left, _top, _width, _height, _owner, _id, NULL, NULL);

	if (_owner != NULL)
		ShowWindow(hButton, SW_SHOW);
}