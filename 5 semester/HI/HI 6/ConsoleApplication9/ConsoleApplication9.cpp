#include "stdafx.h"
#include <tchar.h>
#include "math.h"
#define PLUS 0x6B
#define MINUS 0x6D

char szProgName[] = "lab 4";
int const r = 320;
int const pointscount = r*2;
int c = 0;
int k = pointscount/2;
double mas[pointscount];
POINT points[pointscount];
COLORREF curColor = RGB(255, 255, 255);
HBRUSH bckBrush = CreateSolidBrush(curColor);
int speed = 4;
HWND hWnd;
HHOOK hook;
HHOOK mouseHook;
HHOOK msgBoxHook;
RECT wRect, dRect;
TCHAR szContents[] = _T("Hello, I'm MessageBox");
TCHAR szHookedContents[] = _T("Hooked!");
TCHAR szTitle[] = _T("Hello MessageBox");
TCHAR szHookedTitle[] = _T("Hooked MessageBox");


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
	WNDCLASS w;
	w.lpszClassName = szProgName;
	w.hInstance = hInstance;
	w.lpfnWndProc = WndProc;
	w.hCursor = LoadCursor(NULL, IDC_ARROW);
	w.hIcon = 0;
	w.lpszMenuName = 0;
	w.hbrBackground = bckBrush;
	w.style = CS_HREDRAW | CS_VREDRAW;
	w.cbClsExtra = 0;
	w.cbWndExtra = 0;


	if (!RegisterClass(&w))
		return 0;

	hWnd = CreateWindow(szProgName,
		"lab 4",
		WS_POPUP,
		0,
		0,
		2*r,
		2*r,
		(HWND)NULL,
		(HMENU)NULL,
		(HINSTANCE)hInstance,
		(HINSTANCE)NULL);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	hook = SetWindowsHookEx(WH_KEYBOARD_LL, (HOOKPROC)KeyboardProc, hInstance, NULL);
	mouseHook = SetWindowsHookEx(WH_MOUSE_LL, (HOOKPROC)MouseProc, hInstance, NULL);
	msgBoxHook = SetWindowsHookEx(WH_CBT, (HOOKPROC)MsgBoxProc,NULL,GetCurrentThreadId());
	MessageBox(NULL, szContents, szTitle, MB_OK | MB_ICONSTOP);
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	DestroyWindow(hWnd);
	UnregisterClass(szProgName, NULL);
	return (int)msg.wParam;
}

void moveWindow(HWND hWnd, bool Right, RECT wRect, RECT dRect) {
	if (wRect.right + speed >= dRect.right+2*r) {
		wRect.left = dRect.left-2*r;
		SetWindowPos(hWnd,
			HWND_TOPMOST,
			wRect.left,
			wRect.top,
			0,
			0,
			SWP_NOSIZE);
	}
	SetWindowPos(hWnd,
		HWND_TOPMOST,
		wRect.left + speed,
		wRect.top,
		0,
		0,
		SWP_NOSIZE);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT messg, WPARAM wParam, LPARAM lParam)
{
	HWND dWnd, speedLabel;
	HRGN hRegn;
	GetClientRect(GetDesktopWindow(), &dRect);
	switch (messg)
	{
	case WM_CREATE:
		for (int i = 0; i <= r; i += r * 4 / pointscount){
			double a = sqrt((double)(r*r - i*i));
			if (c == 0){
				points[i].x = a + r;
				points[i].y = i + r;
				points[k].x = -a + r;
				points[k].y = i + r;
			}
			else{
				if (c == k / 2){
					points[c].x = a + r;
					points[c].y = i + r;
					points[k + c].x = a + r;
					points[k + c].y = -i + r;
				}
				else{
					points[c].x = a + r;
					points[c].y = i + r;
					points[k - c].x = -a + r;
					points[k - c].y = i + r;
					points[k + c].x = -a + r;
					points[k + c].y = -i + r;
					points[2 * k - c].x = a + r;
					points[2 * k - c].y = -i + r;
				}
			}
			c++;
		}
		GetClientRect(hWnd, &wRect);

		hRegn = CreatePolygonRgn(points, pointscount, 2);

		SetWindowRgn(hWnd, hRegn, TRUE);
		SetWindowPos(hWnd,
			HWND_TOPMOST,
			(dRect.right - dRect.left - wRect.right + wRect.left) / 2,
			(dRect.bottom - dRect.top - wRect.bottom + wRect.top) / 2,
			0,
			0,
			SWP_NOSIZE);
		SetForegroundWindow(hWnd);
		SetTimer(hWnd, 1, 10, NULL);
		break;

	case WM_TIMER:
		GetWindowRect(hWnd, &wRect);
		moveWindow(hWnd, true, wRect, dRect);
		break;
	case WM_DESTROY:
		UnhookWindowsHookEx(hook);
		UnhookWindowsHookEx(mouseHook);
		UnhookWindowsHookEx(msgBoxHook);
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hWnd, messg, wParam, lParam));
}

LRESULT  CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	KBDLLHOOKSTRUCT hooked_key = *((KBDLLHOOKSTRUCT*)lParam);
	GetWindowRect(hWnd, &wRect);
	if (WM_KEYDOWN){
		switch (hooked_key.vkCode)
		{
		case PLUS:
			if (speed < 256)
				speed += 1;
			break;
		case MINUS:
			if (speed > 0)
				speed -= 1;
			break;
		default:
			break;
		}
	}
	return CallNextHookEx(hook, nCode, wParam, lParam);
}

LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam){

	PKBDLLHOOKSTRUCT k = (PKBDLLHOOKSTRUCT)(lParam);
	POINT p;


	if (wParam == WM_RBUTTONDOWN)//right button
	{
		if (speed > 0)
			speed -= 1;
	}
	if (wParam == WM_LBUTTONDOWN)//left button
	{
		if (speed < 256)
			speed += 1;
	}
	return CallNextHookEx(mouseHook, nCode, wParam, lParam);
}

LRESULT CALLBACK MsgBoxProc(int nCode, WPARAM wParam, LPARAM lParam){
	HWND hwnd;
	HWND hwndButton;

	switch (nCode)
	{
	case HCBT_CREATEWND:
		// Get handle to the message box!
		hwnd = (HWND)wParam;
		//MessageBox(hwnd, szHookedContents, szHookedTitle, MB_OK | MB_ICONSTOP);
		return 0;

	}

	return CallNextHookEx(msgBoxHook, nCode, wParam, lParam);
}