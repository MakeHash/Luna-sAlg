#include <Windows.h>
#include <string>
#include <algorithm>
#include <regex>
#include <CommCtrl.h>
#define OnCheckClicked 0
#define OnClearClicked 1
#define Progress 2
#include "resource1.h"
HFONT hFont;

HWND hWnd;

HWND hEdit;

HWND hRes;

HWND hCheck;

HWND hClearResAndEdit;

HWND hProgress;

HWND hTimer;

DWORD IDC_TIMER;

DWORD Ncounter;

WNDCLASS NewWindowClass(HBRUSH BGColor, HCURSOR Curs, HINSTANCE hInst, HICON Icon, LPCWSTR Name, WNDPROC Procedure);

LRESULT CALLBACK SoftwareMainProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);

inline bool prdct(std::string i);

inline bool LunasAlgorithm(std::string card);

void AddMainWidgets(HWND hWnd);

void AddMainWidgets(HWND hWnd)
{
	hCheck = CreateWindowA("button", "CHECK", WS_VISIBLE | WS_CHILD, 37, 110, 76, 20, hWnd, (HMENU)OnCheckClicked, NULL, NULL);
	hEdit = CreateWindowA("edit", "", WS_VISIBLE | WS_CHILD, 37, 80, 158, 20, hWnd, NULL, NULL, NULL);
	hRes = CreateWindowEx(WS_EX_TRANSPARENT, L"static", L"CardNumber correctness checker. C++ program. ", WS_VISIBLE | WS_CHILD | ES_CENTER, 150, 5, 215, 25, hWnd, NULL, NULL, NULL);
	hClearResAndEdit = CreateWindowA("button", "CLEAR", WS_VISIBLE | WS_CHILD, 120, 110, 76, 20, hWnd, (HMENU)OnClearClicked, NULL, NULL);

}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow)
{
	WNDCLASS SoftwareMainClass = NewWindowClass(CreateSolidBrush(RGB(216, 217, 249)), LoadCursor(NULL, IDC_ARROW), hInst, LoadIcon(hInst, MAKEINTRESOURCE(IDB_PNG1)),
		L"MainWndClass", SoftwareMainProcedure);

	if (!RegisterClassW(&SoftwareMainClass)) { return -1; }
	MSG SoftwareMainMessage = { 0 };

	hWnd = CreateWindow(L"MainWndClass", L"Checker(MXMLN)", WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME | WS_VISIBLE, 100, 100, 500, 180, NULL, NULL, NULL, NULL);



	SendMessage(hWnd, WM_NCPAINT, NULL, NULL);

	while (GetMessage(&SoftwareMainMessage, NULL, NULL, NULL))
	{
		TranslateMessage(&SoftwareMainMessage);
		DispatchMessage(&SoftwareMainMessage);
	}
	return 0;
}

void WINAPI SoftADditionalProc()
{
	while (Ncounter < 10)
	{
	}
}
WNDCLASS NewWindowClass(HBRUSH BGColor, HCURSOR Curs, HINSTANCE hInst, HICON Icon, LPCWSTR Name, WNDPROC Procedure)
{
	WNDCLASS NWC = { 0 };
	NWC.hIcon = Icon;
	NWC.hCursor = Curs;
	NWC.hInstance = hInst;
	NWC.lpszClassName = Name;
	NWC.lpfnWndProc = Procedure;
	NWC.hbrBackground = BGColor;
	return NWC;
}
LRESULT CALLBACK SoftwareMainProcedure(HWND hWnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
	case WM_COMMAND:
		switch (wparam)
		{
		case OnCheckClicked:
		{

			std::smatch mtch;
			std::regex reg("[^\\s\\d]");
			int textLen = GetWindowTextLengthA(hEdit);
			LPSTR crd = (PSTR)VirtualAlloc((LPVOID)NULL,
				(DWORD)(textLen + 1), MEM_COMMIT,
				PAGE_READWRITE);
			std::string card = crd;
			GetWindowTextA(hEdit, crd, textLen + 1);
			if (textLen > 19)
			{
				std::string wrong = "Too much symbols -- Try again!";
				SetWindowTextA(hRes, wrong.c_str());
				VirtualFree(&crd, (DWORD)(textLen + 1), MEM_RELEASE);
			}
			else
			{
				bool answ = LunasAlgorithm(card);
				std::string show = (answ == true ? "CARD IS VALID!" : "CARD IS INVALID!");
				Sleep(3000);
				SetWindowTextA(hRes, show.c_str());
				VirtualFree(&crd, (DWORD)(textLen + 1), MEM_RELEASE);
			}

		}break;
		case OnClearClicked:
		{
			std::string dlt = "";
			SetWindowTextA(hRes, dlt.c_str());
			SetWindowTextA(hEdit, dlt.c_str());
		}
		}break;
	case WM_CREATE:
	{
		hFont = CreateFont(11, 0, 0, 0, FW_LIGHT, FALSE, FALSE, FALSE, ANSI_CHARSET,
			OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
			DEFAULT_PITCH | FF_DONTCARE, L"Cooper Black");

		AddMainWidgets(hWnd);
		SendMessage(hClearResAndEdit, WM_SETFONT, (WPARAM)hFont, TRUE);
		SendMessage(hCheck, WM_SETFONT, (WPARAM)hFont, TRUE);
		SendMessage(hEdit, WM_SETFONT, (WPARAM)hFont, TRUE);
		SendMessage(hRes, WM_SETFONT, (WPARAM)hFont, TRUE);

	}break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default: return DefWindowProc(hWnd, msg, wparam, lparam);
	}
}

inline bool LunasAlgorithm(std::string card)
{
	card.erase(std::remove_if(card.begin(), card.end(), ::isspace),
		card.end());
	int crdsz = card.size() - 1;
	int sum = 0;
	bool IsEven = (crdsz % 2 == 0 ? true : false);
	if (IsEven == true)
	{
		int i = 1;
		while (i < crdsz + 1)
		{
			if ((i == 1) || (i % 2 != 0))
			{
				std::string obj(1, card[i]);
				int num = std::atoi(obj.c_str());
				num *= 2;
				if (num > 9)
				{
					num -= 9;
				}
				else
				{
				}
				sum += num;
				++i;
			}
			else
			{
				std::string obj(1, card[i]);
				int num = std::atoi(obj.c_str());
				sum += num;
				++i;
			}
		}
	}
	else
	{
		int i = 0;
		while (i < crdsz + 1)
		{
			if ((i == 0) || (i % 2 == 0))
			{
				std::string obj(1, card[i]);
				int num = std::atoi(obj.c_str());
				num *= 2;
				if (num > 9)
				{
					num -= 9;
				}
				else
				{
				}
				sum += num;
				++i;
			}
			else
			{
				std::string obj(1, card[i]);
				int num = std::atoi(obj.c_str());
				sum += num;
				++i;
			}
		}
	}
	return (sum % 10 == 0 ? true : false);
}