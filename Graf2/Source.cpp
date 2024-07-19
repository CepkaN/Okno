//#include<iostream>
//#include<string>
//#include<map>
//#include<algorithm>
#include<vector>
//#include<ranges>
//#include<sstream>
//#include <intrin.h>

//
//#define uc unsigned char
//#define lo long long
//auto q = [](int& a) {a += 1; return a; };
//
//
//
//int main() {
//	setlocale(LC_ALL, "Ru");
//
//	std::cout << (1 && 0) << '\n';
//
//
//	return 0;
//}
//
#include <thread>
#include <iostream>
#include <string>
#include<Windows.h>
#include"SoftwareDefinition.h"
#include"SoftwareColors.h"
#include"resource.h"

//void runA(bool value, int i) {
//    if (value) {
//        //значение всегда должно быть равным 1
//        std::string out = "[ " + std::to_string(i) + " ] value " + std::to_string(value) + "\n";
//        std::cout << out;
//    }
//}
//
//void runB(bool value) {
//    value = false;
//}
//int main() {
//    for (int i = 0; i < 20; i++) {
//        bool value = true; //1
//        std::thread tA(runA, value, i);
//        std::thread tB(runB, value);
//        tA.join();
//        tB.join();
//    }
//    int cou = 0;
//    std::vector<short>h{1,0,0,0,0};
//    for (auto& _ : h) {
//        cou++;
//    }
//    std::cout << cou << '\n';

//}





int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow) {
	fontRectangle = CreateFontA(
		80, 0, 0, 0, FW_MEDIUM,
		FALSE, FALSE, FALSE, DEFAULT_CHARSET,
		OUT_OUTLINE_PRECIS, CLIP_DFA_DISABLE, ANTIALIASED_QUALITY,
		FF_DECORATIVE, "MyFont"
	);

	WNDCLASS SoftwareMainClass = NewWindowClass((HBRUSH)COLOR_WINDOW, LoadCursor(NULL, IDC_HAND), hInst,
		LoadIcon(hInst,MAKEINTRESOURCE(IDI_ICON1)),
		L"MainWndClass", SoftwareMainProcedure);

	if (!RegisterClassW(&SoftwareMainClass)) { return -1; }
	MSG SoftwareMainMessage = { 0 };

	CreateWindow(L"MainWndClass", L"First c++ window", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 500, 250, NULL, NULL, NULL, NULL);

	while (GetMessage(&SoftwareMainMessage, NULL, NULL, NULL)) {
		TranslateMessage(&SoftwareMainMessage);
		DispatchMessage(&SoftwareMainMessage);
	}
	return 0;
}

WNDCLASS NewWindowClass(HBRUSH BGColor, HCURSOR Cursor, HINSTANCE hInst, HICON Icon, LPCWSTR Name, WNDPROC Procedure) {
	WNDCLASS NWC = { 0 };

	NWC.hIcon = Icon;
	NWC.hCursor = Cursor;
	NWC.hInstance = hInst;
	NWC.lpszClassName = Name;
	NWC.hbrBackground = BGColor;
	NWC.lpfnWndProc = Procedure;

	return NWC;
}

LRESULT CALLBACK SoftwareMainProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
	switch (msg) {
	case WM_COMMAND:
		switch (wp) {
		case OnMenuClicked1:
			MessageBoxA(hWnd, "Menu was 1 clicked", "Menu worked", MB_OK);
			break;
		case OnMenuClicked2:
			MessageBoxA(hWnd, "Menu was 2 clicked", "Menu worked", MB_OK);
			break;
		case OnMenuClicked3:
			MessageBoxA(hWnd, "Menu was 3 clicked", "Menu worked", MB_OK);
			break;
		case OnClearField:
			SetWindowTextA(hEditControl, "");
			//MessageBoxA(hWnd, "Thanks!", "Button clicked", MB_OK);
			break;
		case OnReadColor:
			colorR = GetDlgItemInt(hWnd, DlgIndexColorR, 0, false);
			colorG = GetDlgItemInt(hWnd, DlgIndexColorG, 0, false);
			colorB = GetDlgItemInt(hWnd, DlgIndexColorB, 0, false);
			brushRectangle=CreateSolidBrush(RGB(colorR,colorG,colorB));

			fontColor = RGB(255 - colorR, 255 - colorG, 255 - colorB);

			RedrawWindow(hWnd, NULL, NULL, RDW_UPDATENOW | RDW_INVALIDATE);
			//num = GetDlgItemInt(hWnd, DlgIndexNumber, NULL, false);
			//SetWindowTextA(hStaticControl, std::to_string(num).c_str());

			/*CharsRead= GetWindowTextA(hEditControl, Buffer, TextBufferSize);
			SetWindowTextA(hStaticControl, Buffer);
			SetWindowTextA(hEditControl, ("Symbols read : " + std::to_string(CharsRead)).c_str());
			*/break;
		case OnSaveFile:
			//SaveData("C:\\Users\\User\\Desktop\\C++kakoyto\\Graf2\\Graf2.txt");
			
			if (GetSaveFileNameA(&ofn)) { SaveData(filename); }
			break;
		case OnLoadFile:
			//LoadData("C:\\Users\\User\\Desktop\\C++kakoyto\\Graf2\\Graf2.txt");
			
			if (GetOpenFileNameA(&ofn)) { LoadData(filename); }
			break; 
		case OnExitSoftware:
			PostQuitMessage(0);
			break;
		default:break;
		}
		break;

	case WM_PAINT:
		BeginPaint(hWnd, &ps);
		//FillRect(ps.hdc,&windowRectangle,brushRectangle);
		GradientRect(ps.hdc, &windowRectangle, Color(100, 20, 20), Color(220, 20, 200), Color(250, 250, 220), Color(20, 250, 20));

		SetBkMode(ps.hdc, TRANSPARENT);
		SetTextColor(ps.hdc, fontColor);
		SelectObject(ps.hdc, fontRectangle);
		DrawTextA(ps.hdc, "МНОГОМНОГОБУКОВ", -1, &windowRectangle,
			DT_SINGLELINE | DT_CENTER | DT_VCENTER | DT_NOCLIP);

		EndPaint(hWnd, &ps);
		break;
	case WM_CREATE:
		MainWndAddMenus(hWnd);
		MainWndAddWidgets(hWnd);
		SetOpenFileParams(hWnd);

		//SendMessageA(hStaticControl, WM_SETFONT, (WPARAM)fontRectangle, TRUE);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:return DefWindowProc(hWnd, msg, wp, lp);
	}
}

void MainWndAddMenus(HWND hWnd) {
	HMENU RootMenu = CreateMenu();
	HMENU SubMenu = CreateMenu();
	HMENU SubActionMenu = CreateMenu();

	
	AppendMenu(SubActionMenu, MF_STRING, OnMenuClicked1, L"Menu 1");
	AppendMenu(SubActionMenu, MF_STRING, OnMenuClicked2, L"Menu 2");
	AppendMenu(SubActionMenu, MF_STRING, OnMenuClicked3, L"Menu 3");
	AppendMenu(SubMenu, MF_SEPARATOR, NULL, NULL);

	AppendMenu(SubMenu, MF_STRING, OnSaveFile, L"Сохранить");
	AppendMenu(SubMenu, MF_STRING, OnLoadFile, L"Загрузить");

	AppendMenu(SubMenu, MF_POPUP, (UINT_PTR)SubActionMenu, L"Action");
	AppendMenu(SubMenu, MF_STRING, OnClearField, L"Clear");
	AppendMenu(RootMenu, MF_STRING, (UINT_PTR)SubMenu, L"HELP");


	AppendMenu(SubMenu, MF_STRING, OnExitSoftware, L"Exit");


	AppendMenu(RootMenu, MF_POPUP, (UINT_PTR)SubMenu, L"File");

	SetMenu(hWnd, RootMenu);
}

void MainWndAddWidgets(HWND hWnd) {
	hStaticControl= CreateWindowA("static", "Приветики-конфетики!", WS_VISIBLE | WS_CHILD|ES_CENTER, 200, 5, 150, 30, hWnd, NULL, NULL, NULL);

	//hEditControl = CreateWindowA("edit","Это моё ооокно", WS_VISIBLE | WS_CHILD|ES_MULTILINE|WS_VSCROLL, 5, 40, 470, 120, hWnd, NULL, NULL, NULL);
	windowRectangle = { 5 + 470,+40,5,40 + 120 };

	CreateWindowA("edit", "0", WS_VISIBLE | WS_CHILD | ES_CENTER | ES_NUMBER, 5, 170, 120, 30, hWnd, (HMENU)DlgIndexColorR, NULL, NULL);
	CreateWindowA("edit", "0", WS_VISIBLE | WS_CHILD | ES_CENTER | ES_NUMBER, 110, 170, 120, 30, hWnd, (HMENU)DlgIndexColorG, NULL, NULL);
	CreateWindowA("edit", "0", WS_VISIBLE | WS_CHILD | ES_CENTER | ES_NUMBER, 215, 170, 120, 30, hWnd, (HMENU)DlgIndexColorB, NULL, NULL);

	CreateWindowA("button", "Ну нажми!", WS_VISIBLE | WS_CHILD | ES_CENTER, 5, 5, 120, 30, hWnd, (HMENU)OnClearField, NULL, NULL);

	CreateWindowA("button", "SetColor", WS_VISIBLE | WS_CHILD | ES_CENTER, 130, 5, 50, 30, hWnd, (HMENU)OnReadColor, NULL, NULL);

}

void SaveData(LPCSTR path) {
	HANDLE FileToSave = CreateFileA(
		path,
		GENERIC_WRITE,
		0,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	int saveLenth = GetWindowTextLength(hEditControl) + 1;
	char* data = new char[saveLenth];

	saveLenth = GetWindowTextA(hEditControl, data, saveLenth);
	DWORD bytesIterated;
	WriteFile(FileToSave, data, saveLenth, &bytesIterated, NULL);
	CloseHandle(FileToSave);
	delete[]data;


}

void LoadData(LPCSTR path) {
	HANDLE FileToLoad = CreateFileA(
		path,
		GENERIC_READ,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	DWORD bytesIterated;
	ReadFile(FileToLoad, Buffer, TextBufferSize, &bytesIterated, NULL);

	SetWindowTextA(hEditControl, Buffer);

	CloseHandle(FileToLoad);
}

void SetOpenFileParams(HWND hWnd) {
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hWnd;
	ofn.lpstrFile = filename;
	ofn.nMaxFile = sizeof(filename);
	ofn.lpstrFilter = ".txt";
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = "C:\\Users\\User\\Desktop\\C++kakoyto\\Graf2";
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

}