#pragma comment(lib,"C:\\Users\\Þðà\\Documents\\Visual Studio 2013\\Projects\\ConsoleApplication1\\SoundLib\\c\\bass.lib")

#include <Windows.h>
#include <conio.h>
#include <math.h>
#include "C:\Users\Þðà\Documents\Visual Studio 2013\Projects\ConsoleApplication1\SoundLib\c\bass.h"

#define ID_BUTTONPLAY	1
#define ID_BUTTONPAUSE	2
#define ID_BUTTONEXIT	3
#define ID_BUTTONNEXT	4
#define ID_BUTTONPREV	5

#define visWidth		40
#define visHeight		36
#define visPosLeft		351
#define visPosTop		206

#define maxCustomButtonClassName 5

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK customButtonProc(HWND, UINT, WPARAM, LPARAM);
void createButtons(HWND);
HRGN createRgnFromBitmap(HBITMAP);




HWND		hWnd, playButton, pauseButton, closeButton, nextButton, prevButton;
HDC			specDC;
HBITMAP		mainMask, mainBmp, pauseMask, playMask, closeMask, nextMask, prevMask, specbmp;
BITMAP		bi;
char		szProgName[] = "Exam Work";
char		sound[] = "C:/Users/Þðà/Documents/Visual Studio 2013/Projects/ConsoleApplication1/Resources/audio/matrix.mp3";
char		mainMaskPath[] = "C:/Users/Þðà/Documents/Visual Studio 2013/Projects/ConsoleApplication1/Resources/bmp/mask.bmp";
char		mainBmpPath[] = "C:/Users/Þðà/Documents/Visual Studio 2013/Projects/ConsoleApplication1/Resources/bmp/imag.bmp";
char		playMaskPath[] = "C:/Users/Þðà/Documents/Visual Studio 2013/Projects/ConsoleApplication1/Resources/bmp/play.bmp";
char		pauseMaskPath[] = "C:/Users/Þðà/Documents/Visual Studio 2013/Projects/ConsoleApplication1/Resources/bmp/pause.bmp";
char		closeMaskPath[] = "C:/Users/Þðà/Documents/Visual Studio 2013/Projects/ConsoleApplication1/Resources/bmp/close.bmp";
char		nextMaskPath[] = "C:/Users/Þðà/Documents/Visual Studio 2013/Projects/ConsoleApplication1/Resources/bmp/play_hover.bmp";
char		prevMaskPath[] = "C:/Users/Þðà/Documents/Visual Studio 2013/Projects/ConsoleApplication1/Resources/bmp/pause_hover.bmp";
bool		isPlayingNow = false;
bool		dragging = false;
POINT		MousePnt;
HSTREAM		streamHandle;
BYTE		*specbuf;