#pragma once

#define OnMenuClicked1		1
#define OnMenuClicked2		2
#define OnMenuClicked3		3
#define OnExitSoftware		4
#define OnClearField		5
#define OnReadColor			6

#define TextBufferSize		256

#define DlgIndexColorR		200
#define DlgIndexColorG		201
#define DlgIndexColorB		202

#define OnSaveFile			7
#define OnLoadFile			8

unsigned  num;

char Buffer[TextBufferSize];
//int CharsRead;

HWND hStaticControl;

HWND hEditControl;
HWND hNumberControl;

char filename[260];
OPENFILENAMEA ofn;


HFONT fontRectangle;
COLORREF fontColor;
int colorR, colorG, colorB;


HBRUSH brushRectangle;
RECT windowRectangle;
PAINTSTRUCT ps;

LRESULT CALLBACK SoftwareMainProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);
WNDCLASS NewWindowClass(HBRUSH BGColor, HCURSOR Cursor, HINSTANCE hInst, HICON Icon, LPCWSTR Name, WNDPROC Procedure);

void MainWndAddMenus(HWND hWnd);
void MainWndAddWidgets(HWND hWnd);
void SaveData(LPCSTR path);
void LoadData(LPCSTR path);
void SetOpenFileParams(HWND hWnd);