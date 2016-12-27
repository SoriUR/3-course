#include "stdafx.h"
#include "header.h" 

bool registerClasses(HINSTANCE hInstance) {

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

	WNDCLASS playClass;
	playClass.lpszClassName = "play";
	playClass.hInstance = hInstance;
	playClass.lpfnWndProc = customButtonProc;
	playClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	playClass.hIcon = NULL;
	playClass.lpszMenuName = NULL;
	playClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	playClass.style = CS_HREDRAW | CS_VREDRAW;
	playClass.cbClsExtra = 0;
	playClass.cbWndExtra = 0;

	WNDCLASS pauseClass;
	pauseClass.lpszClassName = "pause";
	pauseClass.hInstance = hInstance;
	pauseClass.lpfnWndProc = customButtonProc;
	pauseClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	pauseClass.hIcon = NULL;
	pauseClass.lpszMenuName = NULL;
	pauseClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	pauseClass.style = CS_HREDRAW | CS_VREDRAW;
	pauseClass.cbClsExtra = 0;
	pauseClass.cbWndExtra = 0;

	WNDCLASS nextClass;
	nextClass.lpszClassName = "next";
	nextClass.hInstance = hInstance;
	nextClass.lpfnWndProc = customButtonProc;
	nextClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	nextClass.hIcon = NULL;
	nextClass.lpszMenuName = NULL;
	nextClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	nextClass.style = CS_HREDRAW | CS_VREDRAW;
	nextClass.cbClsExtra = 0;
	nextClass.cbWndExtra = 0;

	WNDCLASS prevClass;
	prevClass.lpszClassName = "prev";
	prevClass.hInstance = hInstance;
	prevClass.lpfnWndProc = customButtonProc;
	prevClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	prevClass.hIcon = NULL;
	prevClass.lpszMenuName = NULL;
	prevClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	prevClass.style = CS_HREDRAW | CS_VREDRAW;
	prevClass.cbClsExtra = 0;
	prevClass.cbWndExtra = 0;
	return (RegisterClass(&w) && RegisterClass(&playClass) && RegisterClass(&pauseClass)
		 && RegisterClass(&nextClass) && RegisterClass(&prevClass));
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
	if (!registerClasses(hInstance)){
		return 0;
	}

	mainBmp = (HBITMAP)LoadImage(NULL, mainBmpPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	mainMask = (HBITMAP)LoadImage(NULL, mainMaskPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	pauseMask = (HBITMAP)LoadImage(NULL, pauseMaskPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	playMask = (HBITMAP)LoadImage(NULL, playMaskPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	nextMask = (HBITMAP)LoadImage(NULL, nextMaskPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	prevMask = (HBITMAP)LoadImage(NULL, prevMaskPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	GetObject(mainMask, sizeof(BITMAP), &bi);

	if (!mainMask || !playMask || !pauseMask || !mainBmp || !nextMask || !prevMask) {
		MessageBox(hWnd, "Cannot find mask", "Missing file", MB_OK);
		return NULL;
	}

	if (!BASS_Init(-1, 44100, 0, 0, NULL)) {
		MessageBox(hWnd, "Cannot init Bass library", "Load library", MB_OK);
		return NULL;
	}

	hWnd = CreateWindow(szProgName,
		"Zadanie_6",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		bi.bmWidth,
		bi.bmHeight,
		NULL,
		NULL,
		hInstance,
		NULL);

	int Style;
	Style = GetWindowLong(hWnd, GWL_STYLE);
	Style = Style || WS_CAPTION;
	Style = Style || WS_SYSMENU;
	SetWindowLong(hWnd, GWL_STYLE, Style);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	HICON hIcon = LoadIcon(hInstance, "C:/Users/Þðà/Documents/Visual Studio 2013/Projects/ConsoleApplication1/Resources/bmp/icon.ico");
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

HRGN createRgnFromBitmap(HBITMAP mask) {
	BYTE bpp;
	DWORD TransPixel;
	DWORD pixel;
	int startx;
	INT i, j;
	HRGN Rgn, ResRgn = CreateRectRgn(0, 0, 0, 0);
	BITMAP bm;
	GetObject(mask, sizeof(BITMAP), &bm);
	bpp = bm.bmBitsPixel >> 3;
	BYTE *pBits = new BYTE[bm.bmWidth * bm.bmHeight * bpp];

	int  p = GetBitmapBits(mask, bm.bmWidth * bm.bmHeight * bpp, pBits);

	TransPixel = *(DWORD*)pBits;

	TransPixel <<= 32 - bm.bmBitsPixel;
	for (i = 0; i < bm.bmHeight; i++)
	{
		startx = -1;
		for (j = 0; j < bm.bmWidth; j++)
		{
			pixel = *(DWORD*)(pBits + (i * bm.bmWidth +
				j) * bpp) << (32 - bm.bmBitsPixel);
			if (pixel != TransPixel)
			{
				if (startx<0)
				{
					startx = j;
				}
				else if (j == (bm.bmWidth - 1))
				{
					Rgn = CreateRectRgn(startx, i, j, i + 1);
					CombineRgn(ResRgn, ResRgn, Rgn, RGN_OR);
					startx = -1;
				}
			}
			else if (startx >= 0)
			{
				Rgn = CreateRectRgn(startx, i, j, i + 1);
				CombineRgn(ResRgn, ResRgn, Rgn, RGN_OR);
				startx = -1;
			}
		}
	}
	delete pBits;
	return ResRgn;
}

void CALLBACK UpdateSpectrum(UINT uTimerID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2)
{
	HDC dc;
	int x, y, y1;

	float fft[1024];
	BASS_ChannelGetData(streamHandle, fft, BASS_DATA_FFT2048);

	int b0 = 0;
	memset(specbuf, 0, visWidth*visHeight);
#define BANDS 10
	for (x = 0; x<BANDS; x++) {
		float peak = 0;
		int b1 = pow(2, x*10.0 / (BANDS - 1));
		if (b1 <= b0) b1 = b0 + 1;
		if (b1>1023) b1 = 1023;
		for (; b0<b1; b0++)
			if (peak<fft[1 + b0]) peak = fft[1 + b0];
		y = sqrt(peak) * 3 * visHeight - 4;
		if (y>visHeight) y = visHeight;
		while (--y >= 0)
			memset(specbuf + y*visWidth + x*(visWidth / BANDS), y + 1, visWidth / BANDS - 2);
	}

	dc = GetDC(hWnd);
	BitBlt(dc, visPosLeft, visPosTop, visWidth, visHeight, specDC, 0, 0, SRCCOPY);
	BitBlt(dc, visPosLeft+74, visPosTop, visWidth, visHeight, specDC, 0, 0, SRCCOPY);
	ReleaseDC(hWnd, dc);
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
	PAINTSTRUCT ps;
	HDC hdc;
	HDC hdcBits;
	RECT wndrect;
	POINT point;
	switch (msg) {
	case WM_CREATE:
		SetWindowRgn(hWnd, createRgnFromBitmap(mainMask), TRUE);
		playButton = CreateWindow("play",	 0,
			WS_CHILD | BS_BITMAP | BS_OWNERDRAW,
			271	,380, 40, 40, hWnd, (HMENU)ID_BUTTONPLAY, NULL, NULL);
		SetWindowRgn(playButton, createRgnFromBitmap(playMask), TRUE);
		pauseButton = CreateWindow("pause", 0,
			WS_CHILD | BS_BITMAP | BS_OWNERDRAW,
			493, 387, 100, 100, hWnd, (HMENU)ID_BUTTONPAUSE, NULL, NULL);
		SetWindowRgn(pauseButton, createRgnFromBitmap(pauseMask), TRUE);

		nextButton = CreateWindow("next", 0,
			WS_CHILD | BS_BITMAP | BS_OWNERDRAW,
			268, 380, 100, 100, hWnd, NULL, NULL, NULL);
		SetWindowRgn(nextButton, createRgnFromBitmap(nextMask), TRUE);
		prevButton = CreateWindow("prev", 0,
			WS_CHILD | BS_BITMAP | BS_OWNERDRAW,
			492, 387, 100, 100, hWnd, NULL, NULL, NULL);
		SetWindowRgn(prevButton, createRgnFromBitmap(prevMask), TRUE);

		streamHandle = BASS_StreamCreateFile(FALSE, sound, 0, 0, BASS_SAMPLE_LOOP);
		{
			BYTE data[2000] = { 0 };
			BITMAPINFOHEADER *bh = (BITMAPINFOHEADER*)data;
			RGBQUAD *pal = (RGBQUAD*)(data + sizeof(*bh));
			int a;
			bh->biSize = sizeof(*bh);
			bh->biWidth = visWidth;
			bh->biHeight = visHeight;
			bh->biPlanes = 1;
			bh->biBitCount = 8;
			bh->biClrUsed = bh->biClrImportant = 256;

			for (a = 1; a<128; a++) {
				pal[a].rgbGreen = 256 - 2 * a;
				pal[a].rgbRed = 2 * a;
			}
			for (a = 0; a<32; a++) {
				pal[128 + a].rgbBlue = 8 * a;
				pal[128 + 32 + a].rgbBlue = 255;
				pal[128 + 32 + a].rgbRed = 8 * a;
				pal[128 + 64 + a].rgbRed = 255;
				pal[128 + 64 + a].rgbBlue = 8 * (31 - a);
				pal[128 + 64 + a].rgbGreen = 8 * a;
				pal[128 + 96 + a].rgbRed = 255;
				pal[128 + 96 + a].rgbGreen = 255;
				pal[128 + 96 + a].rgbBlue = 8 * a;
			}

			specbmp = CreateDIBSection(0, (BITMAPINFO*)bh, DIB_RGB_COLORS, (void**)&specbuf, NULL, 0);
			specDC = CreateCompatibleDC(0);
			SelectObject(specDC, specbmp);
		}
		break;
	case WM_PAINT:
		if (isPlayingNow)
		{
			ShowWindow(prevButton, SW_SHOW);
			ShowWindow(nextButton, SW_HIDE);
			EnableWindow(pauseButton, true);
			EnableWindow(playButton, false);
			UpdateWindow(pauseButton);
		}
		else
		{
			ShowWindow(prevButton, SW_HIDE);
			ShowWindow(nextButton, SW_SHOW);
			EnableWindow(pauseButton, false);
			EnableWindow(playButton, true);
			UpdateWindow(playButton);
		}

		ShowWindow(playButton, SW_SHOW);
		ShowWindow(pauseButton, SW_SHOW);
		hdc = BeginPaint(hWnd, &ps);
		hdcBits = ::CreateCompatibleDC(hdc);
		SelectObject(hdcBits, mainBmp);
		BitBlt(hdc, 0, 0, bi.bmWidth, bi.bmHeight, hdcBits, 0, 0, SRCCOPY);
		DeleteDC(hdcBits);
		EndPaint(hWnd, &ps);
		break;

	case WM_LBUTTONDOWN:
		GetCursorPos(&MousePnt);
		dragging = true;
		SetCapture(hWnd);
		break;

	case WM_MOUSEMOVE:
		if (dragging)
		{
			GetCursorPos(&point);
			GetWindowRect(hWnd, &wndrect);
			wndrect.left = wndrect.left + (point.x - MousePnt.x);
			wndrect.top = wndrect.top + (point.y - MousePnt.y);
			SetWindowPos(hWnd, NULL, wndrect.left, wndrect.top, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
			MousePnt = point;
		}
		break;
	case WM_LBUTTONUP:
		if (dragging)
		{
			dragging = false;
			ReleaseCapture();
		}
		break;

	case WM_KEYUP:
		if (wp == VK_SPACE) {
			if (isPlayingNow)
			{
				KillTimer(hWnd, 25);
				isPlayingNow = false;
				BASS_ChannelPause(streamHandle);
			}
			else {
				SetTimer(hWnd, 25, 25, (TIMERPROC)&UpdateSpectrum);
				BASS_ChannelPlay(streamHandle, FALSE);
				isPlayingNow = true;
			}
			SendMessage(hWnd, WM_PAINT, GetWindowLong(hWnd, GWL_ID), (LPARAM)hWnd);
		}
		break;
	case WM_COMMAND:
		switch (LOWORD(wp))
		{
		case ID_BUTTONPLAY:
			SetTimer(hWnd, 25, 25, (TIMERPROC)&UpdateSpectrum);
			BASS_ChannelPlay(streamHandle, FALSE);
			isPlayingNow = true;
			break;
		case ID_BUTTONPAUSE:
			KillTimer(hWnd, 25);
			BASS_ChannelPause(streamHandle);
			isPlayingNow = false;
			break;
		case ID_BUTTONEXIT:
			PostMessage(hWnd, WM_CLOSE, wp, lp);
			break;
		default:
			break;
		}

		break;
	case WM_DESTROY:
		BASS_Free();
		DeleteObject(mainMask);
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, msg, wp, lp);
}


LRESULT CALLBACK customButtonProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
	HDC hdc, h;
	PAINTSTRUCT ps;
	BITMAP bm;
	HBITMAP mask;
	char text[maxCustomButtonClassName];
	switch (msg)
	{
	case WM_PAINT:
		RealGetWindowClass(hWnd, text, maxCustomButtonClassName);
		if (strcmp(text, "play") == 0)
		{
			mask = (HBITMAP)LoadImage(NULL, playMaskPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		}
		else if (strcmp(text, "paus") == 0)
		{
			mask = (HBITMAP)LoadImage(NULL, pauseMaskPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		}
		else if (strcmp(text, "next") == 0)
		{
			mask = (HBITMAP)LoadImage(NULL, nextMaskPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		}
		else if (strcmp(text, "prev") == 0)
		{
			mask = (HBITMAP)LoadImage(NULL, prevMaskPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		}

		GetObject(mask, sizeof(BITMAP), &bm);
		hdc = BeginPaint(hWnd, &ps);
		h = ::CreateCompatibleDC(hdc);
		SelectObject(h, mask);
		BitBlt(hdc, 0, 0, bm.bmWidth, bm.bmHeight, h, 0, 0, SRCCOPY);
		DeleteDC(h);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_LBUTTONUP:
		SendMessage(GetParent(hWnd), WM_COMMAND, GetWindowLong(hWnd, GWL_ID), (LPARAM)hWnd);
		SendMessage(GetParent(hWnd), WM_PAINT, GetWindowLong(hWnd, GWL_ID), (LPARAM)hWnd);
		return 0;
	}
	return DefWindowProc(hWnd, msg, wp, lp);
}
