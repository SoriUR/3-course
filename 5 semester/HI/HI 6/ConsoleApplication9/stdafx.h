// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

LRESULT CALLBACK kbProc(INT, WPARAM, LPARAM);

void moveWindow(HWND, bool, RECT, RECT);
LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK KeyboardProc(int, WPARAM, LPARAM);
LRESULT CALLBACK MsgBoxProc(int nCode, WPARAM wParam, LPARAM lParam);


// TODO: reference additional headers your program requires here
