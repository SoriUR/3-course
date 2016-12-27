// HI3.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "MyButton.h"
#include <Windows.h>

#define FIRST_ID 1
#define SECOND_ID 2
#define THIRD_ID 3

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

HWND		hWnd;
MyButton*	Third;
MyButton*	Second;
MyButton*	First;
char		szProgName[] = "Classy & WinAPI";


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
	WNDCLASS w;
	w.lpszClassName = szProgName;
	w.hInstance = hInstance;
	w.lpfnWndProc = WndProc;
	w.hCursor = LoadCursor(NULL, IDC_ARROW);
	w.hIcon = 0;
	w.lpszMenuName = 0;
	w.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	w.style = CS_HREDRAW | CS_VREDRAW;
	w.cbClsExtra = 0;
	w.cbWndExtra = 0;


	if (!RegisterClass(&w))
		return 0;

	hWnd = CreateWindow(szProgName,
		"Test for Button class",
		WS_OVERLAPPEDWINDOW,
		300,
		100,
		600,
		150,
		(HWND)NULL,
		(HMENU)NULL,
		(HINSTANCE)hInstance,
		(HINSTANCE)NULL);



	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	DestroyWindow(hWnd);
	UnregisterClass(szProgName, NULL);
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
	switch (msg) {
	case WM_CREATE: {
		First = new MyButton(FIRST_ID, hWnd, "Full init", MB_CLASSIC, STD_WIDTH * 2 + 20, 20, 150, 50);

		Third = new MyButton();
		(*Third).setID(THIRD_ID);
		(*Third).setPozition(10, 20);

		return 0;
	}
	case WM_COMMAND:
		switch (LOWORD(wp))
		{
		case THIRD_ID:
		{
			MessageBox(hWnd, "Button with id = 3 has beed pressed.\n Owner for second button deleated", "Button pressed", MB_OK | MB_ICONINFORMATION);
			MyButton * pointer = Second;
			delete pointer;
		}
			break;
		case SECOND_ID:
		{
			MessageBox(hWnd, "Button with id = 2 has beed pressed.\n  Owner for first button setted", "Button pressed", MB_OK | MB_ICONINFORMATION);
			(*Third).setOwner(hWnd);
			break;
		}
		case FIRST_ID:
		{
			MessageBox(hWnd, "Button with id = 1 has beed pressed.\n Owner for second button setted", "Button pressed", MB_OK | MB_ICONINFORMATION);
			Second = new MyButton();
			(*Second).setID(SECOND_ID);
			(*Second).setPozition(STD_WIDTH + 10, 20);
			(*Second).setOwner(hWnd);
		}
		default:
			break;
		}
		return 0;
	case WM_DESTROY:
		/* ... */
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, msg, wp, lp);
}

