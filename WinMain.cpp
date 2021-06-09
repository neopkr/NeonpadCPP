#include <iostream>
#include <windows.h>
#include <tchar.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "Text.h"
#include <Commctrl.h>
#include <errno.h>

#pragma warning(disable : 4996)

static TCHAR szWindowClass[] = _T("DesktopApp");
static TCHAR szTitle[] = _T("Neonpad");

HINSTANCE hInst;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

void textBox(HWND);
int g_scrollY = 0;
HWND hWndStatusBar;
HWND hEdit;
HWND hFontMenu;
HFONT hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
HFONT hDefault;
HWND hFontSize;
HWND hAbout;

int	   iWidth = 1000;
int	   iHeight = 600;

void frame_real(int w, int h, int& rw, int& rh)
{
	RECT frame = { 0,0,w,h };
	AdjustWindowRect(&frame, WS_OVERLAPPED, FALSE);
	rw = frame.right - frame.left;
	rh = frame.bottom - frame.top;
}

int CALLBACK WinMain(
	_In_	 HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_	 LPSTR	   lpCmdLine,
	_In_	 int	   nCmdShow
)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL,
			_T("Call to register class failed!"),
			_T("Neonpad"),
			NULL);
		return 1;
	}
	int sbHeight = 800;
	int w, h;
	frame_real(iWidth, iHeight, w, h);
	hInst = hInstance;
	HWND hWnd = CreateWindow(
		szWindowClass,
		szTitle,
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT,
		w, h,
		HWND_DESKTOP,
		NULL,
		hInstance,
		NULL
	);



	/*
	if (!hFontMenu)
	{
		MessageBox(NULL, "UNABLE TO CALL HFONTMENU", "NeonpadCPP", NULL);
		return 1;
	}
	*/
	if(!hWnd)
	{
		MessageBox(NULL,
			_T("Call to CreateWindow failed!"),
			_T("Neonpad"),
			NULL);

		return 1;
	}

	// default font
	hDefault = CreateFont(17, 0, 0, 0, FW_NORMAL, false, false, false, ANSI_CHARSET, 0, 0, DEFAULT_QUALITY, DEFAULT_PITCH, "Arial");
	SendMessage(hEdit, WM_SETFONT, (WPARAM)hDefault, 0);
	SendMessage(hWnd, WM_SETFONT, (WPARAM)hDefault, 0);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	TCHAR greeting[] = _T("Hello, welcome! pog");
	TCHAR button[] = _T("yeah");
	TCHAR Alert[] = _T("THIS IS A CONSTRUCTOR FASE APP! @author: neokr");
	TCHAR Cap[] = _T("Warning");
	TCHAR fileName[] = _T("docx.txt already exists. \n Do You want to replace it?");

	switch (message)
	{
	case WM_CREATE:
	{		
		
		HMENU menubar = CreateMenu();
		HMENU file = CreateMenu();
		HMENU edit = CreateMenu();
		HMENU view = CreateMenu();
		HMENU help = CreateMenu();
		HMENU format = CreateMenu();
		HMENU editSubMenu = CreatePopupMenu();
		HMENU fontSize = CreatePopupMenu();
		HMENU subArial = CreatePopupMenu();
		HMENU subCS = CreatePopupMenu();
		HMENU subTNR = CreatePopupMenu();
		HMENU subConsolas = CreatePopupMenu();
		HMENU viewSubMenu = CreatePopupMenu();
		HMENU barState = CreatePopupMenu();

		AppendMenu(menubar, MF_POPUP, (UINT_PTR)file, fname);
		AppendMenu(menubar, MF_POPUP, (UINT_PTR)edit, ename);
		AppendMenu(menubar, MF_POPUP, (UINT_PTR)format, "Format");
		AppendMenu(menubar, MF_POPUP, (UINT_PTR)view, vname);
		AppendMenu(menubar, MF_POPUP, (UINT_PTR)help, hname);
		// file
		AppendMenu(file, MF_STRING, FILE_MENU_NEW, fileNew);
		AppendMenu(file, MF_STRING, FILE_MENU_OPEN, fileOpen);
		AppendMenu(file, MF_STRING, FILE_MENU_SAVE, fileSave);
		AppendMenu(file, MF_STRING, FILE_MENU_SAVE_OVERWRITE | NULL, fileSaveAs);
		SEPARATOR(file);
		AppendMenu(file, MF_STRING, FILE_MENU_EXIT, fileExit);
		// view
		AppendMenu(view, MF_POPUP| MF_STRING, (UINT_PTR)viewSubMenu, "Zoom");
		AppendMenu(viewSubMenu, MF_STRING, VIEW_ZOOM_IN, "In			NULL");
		AppendMenu(viewSubMenu, MF_STRING, VIEW_ZOOM_OUT, "Out			NULL");
		AppendMenu(viewSubMenu, MF_STRING, VIEW_ZOOM_DEFAULT, "Default Zoom			NULL");
		AppendMenu(view, MF_STRING, NULL, "Bar State");
		// edit
		AppendMenu(edit, MF_STRING, NULL, "Undo			Ctrl+Z");
		SEPARATOR(edit);
		AppendMenu(edit, MF_STRING, EDIT_CUT, editCut);
		AppendMenu(edit, MF_STRING, EDIT_COPY, editCopy);
		AppendMenu(edit, MF_STRING, EDIT_PASTE, "Paste		Ctrl+V");
		AppendMenu(edit, MF_STRING, EDIT_DELETE, "Delete		Supr");
		// format
		AppendMenu(format, MF_STRING, FORMAT_WW, helpWW);
		AppendMenu(format, MF_STRING | MF_POPUP, (UINT_PTR)editSubMenu, subFont);
		AppendMenu(editSubMenu, MF_POPUP |  MF_STRING, (UINT_PTR)subArial, "Arial");
		AppendMenu(subArial, MF_STRING, FONT_12A, "12");
		AppendMenu(subArial, MF_STRING, FONT_16A, "16");
		AppendMenu(subArial, MF_STRING, FONT_20A, "20");
		AppendMenu(subArial, MF_STRING, FONT_24A, "24");
		AppendMenu(subArial, MF_STRING, FONT_28A, "28");
		AppendMenu(subArial, MF_STRING, FONT_32A, "32");
		AppendMenu(subArial, MF_STRING, FONT_64A, "64");
		AppendMenu(editSubMenu, MF_POPUP | MF_STRING, (UINT_PTR)subCS, "Comic Sans MS");
		AppendMenu(subCS, MF_STRING, FONT_12B, "12");
		AppendMenu(subCS, MF_STRING, FONT_16B, "16");
		AppendMenu(subCS, MF_STRING, FONT_20B, "20");
		AppendMenu(subCS, MF_STRING, FONT_24B, "24");
		AppendMenu(subCS, MF_STRING, FONT_28B, "28");
		AppendMenu(subCS, MF_STRING, FONT_32B, "32");
		AppendMenu(subCS, MF_STRING, FONT_64B, "64");
		AppendMenu(editSubMenu, MF_POPUP | MF_STRING, (UINT_PTR)subTNR, "Times New Roman");
		AppendMenu(subTNR, MF_STRING, FONT_12C, "12");
		AppendMenu(subTNR, MF_STRING, FONT_16C, "16");
		AppendMenu(subTNR, MF_STRING, FONT_20C, "20");
		AppendMenu(subTNR, MF_STRING, FONT_24C, "24");
		AppendMenu(subTNR, MF_STRING, FONT_28C, "28");
		AppendMenu(subTNR, MF_STRING, FONT_32C, "32");
		AppendMenu(subTNR, MF_STRING, FONT_64C, "64");
		AppendMenu(editSubMenu, MF_POPUP | MF_STRING, (UINT_PTR)subConsolas, "Consolas");
		AppendMenu(subConsolas, MF_STRING, FONT_12D, "12");
		AppendMenu(subConsolas, MF_STRING, FONT_16D, "16");
		AppendMenu(subConsolas, MF_STRING, FONT_20D, "20");
		AppendMenu(subConsolas, MF_STRING, FONT_24D, "24");
		AppendMenu(subConsolas, MF_STRING, FONT_28D, "28");
		AppendMenu(subConsolas, MF_STRING, FONT_32D, "32");
		AppendMenu(subConsolas, MF_STRING, FONT_64D, "64");
		SEPARATOR(editSubMenu);
		AppendMenu(editSubMenu, MF_STRING, FONT_SIZE, "NULL");
		/*
		AppendMenu(fontSize, MF_STRING, NULL, "12");
		AppendMenu(fontSize, MF_STRING, NULL, "16");
		AppendMenu(fontSize, MF_STRING, NULL, "20");
		AppendMenu(fontSize, MF_STRING, NULL, "24");
		AppendMenu(fontSize, MF_STRING, NULL, "28");
		AppendMenu(fontSize, MF_STRING, NULL, "32");
		AppendMenu(fontSize, MF_STRING, NULL, "64");
		*/
		// help
		AppendMenu(help, MF_STRING, HELP_DOC, "Documentation");
		AppendMenu(help, MF_STRING, HELP_GITHUB, "GitHub Repository");
		SEPARATOR(help);
		AppendMenu(help, MF_STRING, HELP_ABOUT, "About");
		SetMenu(hWnd, menubar);
		
		// TextBox
		hEdit = CreateWindow(ename, "", WS_VISIBLE | WS_CHILD | ES_MULTILINE | WS_EX_LAYERED | WS_VSCROLL | WS_HSCROLL, 0, 1, iWidth - 15, iHeight - 60, hWnd, (HMENU)ID_TEXT, NULL, hFont);
		//hFontMenu = CreateWindow(ename, "", WS_VISIBLE | WS_CHILD | WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX, 500, 500, 200, 200, hWnd, (HMENU)ID_FONT, NULL, hFont);
		
		hWndStatusBar = CreateWindowEx(
			0,
			STATUSCLASSNAME,
			NULL,
			WS_CHILD | WS_VISIBLE | SBARS_SIZEGRIP,
			0,
			0,
			0,
			0,
			hWnd,
			(HMENU)IDC_STATUSBAR,
			(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
			NULL
		);
		
		if (!hWndStatusBar)
		{
			MessageBox(NULL, "Failed to create the status bar", "Error", MB_OK | MB_ICONERROR);
			return 0;
		}
		bool on = false;
		int iStatusWidths[] = { 100, 200, -1 };
		char text[256];
		int number = GetWindowTextLength(hEdit);
		SendMessage(hWndStatusBar, SB_SETPARTS, 3, (LPARAM)iStatusWidths);
		SendMessage(hWndStatusBar, SB_SETTEXT, 0, (LPARAM)"Status Bar");
		SendMessage(hWndStatusBar, SB_SETTEXT, 1, (LPARAM)"Cells");
		sprintf(text, "%d", 0);
		SendMessage(hWndStatusBar, SB_GETTEXT, 2, (LPARAM)text);
		ShowWindow(hWndStatusBar, SW_SHOW);

		break;
	}
	case WM_SIZE:
		SendMessage(hWndStatusBar, WM_SIZE, 0, 0);
		break;
	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;
	case WM_COMMAND:
		switch (wParam)
		{
		case FONT_SIZE:
		{

		}
		case FONT_ARIAL: changeFont(hEdit, arial); break;
		case FONT_CSMS: changeFont(hEdit, csMS); break;
		case FONT_TNR: changeFont(hEdit, TNR); break;
		case FONT_CONSOLAS: changeFont(hEdit, Consolas); break;
		// not working font size
		case FONT_12A: 
		{ HFONT a12 = CreateFont(12, 0, 0, 0, FW_NORMAL, false, false, false, ANSI_CHARSET, 0, 0, DEFAULT_QUALITY, DEFAULT_PITCH, "Arial"); SendMessage(hEdit, WM_SETFONT, (WPARAM)a12, 0); break; }
		case FONT_16A:
		{ HFONT a16 = CreateFont(16, 0, 0, 0, FW_NORMAL, false, false, false, ANSI_CHARSET, 0, 0, DEFAULT_QUALITY, DEFAULT_PITCH, "Arial"); SendMessage(hEdit, WM_SETFONT, (WPARAM)a16, 0); break; }
		case FONT_20A:
		{ HFONT a20 = CreateFont(20, 0, 0, 0, FW_NORMAL, false, false, false, ANSI_CHARSET, 0, 0, DEFAULT_QUALITY, DEFAULT_PITCH, "Arial"); SendMessage(hEdit, WM_SETFONT, (WPARAM)a20, 0); break; }
		case FONT_24A:
		{ HFONT a24 = CreateFont(24, 0, 0, 0, FW_NORMAL, false, false, false, ANSI_CHARSET, 0, 0, DEFAULT_QUALITY, DEFAULT_PITCH, "Arial"); SendMessage(hEdit, WM_SETFONT, (WPARAM)a24, 0); break; }
		case FONT_28A:
		{ HFONT a28 = CreateFont(28, 0, 0, 0, FW_NORMAL, false, false, false, ANSI_CHARSET, 0, 0, DEFAULT_QUALITY, DEFAULT_PITCH, "Arial"); SendMessage(hEdit, WM_SETFONT, (WPARAM)a28, 0); break; }
		case FONT_32A:
		{ HFONT a32 = CreateFont(32, 0, 0, 0, FW_NORMAL, false, false, false, ANSI_CHARSET, 0, 0, DEFAULT_QUALITY, DEFAULT_PITCH, "Arial"); SendMessage(hEdit, WM_SETFONT, (WPARAM)a32, 0); break; }
		case FONT_64A:
		{ HFONT a64 = CreateFont(64, 0, 0, 0, FW_NORMAL, false, false, false, ANSI_CHARSET, 0, 0, DEFAULT_QUALITY, DEFAULT_PITCH, "Arial"); SendMessage(hEdit, WM_SETFONT, (WPARAM)a64, 0); break; }
		case FONT_12B:
		{ HFONT b12 = CreateFont(12, 0, 0, 0, FW_NORMAL, false, false, false, ANSI_CHARSET, 0, 0, DEFAULT_QUALITY, DEFAULT_PITCH, "Comic Sans MS"); SendMessage(hEdit, WM_SETFONT, (WPARAM)b12, 0); break; }
		case FONT_16B:
		{ HFONT b16 = CreateFont(16, 0, 0, 0, FW_NORMAL, false, false, false, ANSI_CHARSET, 0, 0, DEFAULT_QUALITY, DEFAULT_PITCH, "Comic Sans MS"); SendMessage(hEdit, WM_SETFONT, (WPARAM)b16, 0); break; }
		case FONT_20B:
		{ HFONT b20 = CreateFont(20, 0, 0, 0, FW_NORMAL, false, false, false, ANSI_CHARSET, 0, 0, DEFAULT_QUALITY, DEFAULT_PITCH, "Comic Sans MS"); SendMessage(hEdit, WM_SETFONT, (WPARAM)b20, 0); break; }
		case FONT_24B:
		{ HFONT b24 = CreateFont(24, 0, 0, 0, FW_NORMAL, false, false, false, ANSI_CHARSET, 0, 0, DEFAULT_QUALITY, DEFAULT_PITCH, "Comic Sans MS"); SendMessage(hEdit, WM_SETFONT, (WPARAM)b24, 0); break; }
		case FONT_28B:
		{ HFONT b28 = CreateFont(28, 0, 0, 0, FW_NORMAL, false, false, false, ANSI_CHARSET, 0, 0, DEFAULT_QUALITY, DEFAULT_PITCH, "Comic Sans MS"); SendMessage(hEdit, WM_SETFONT, (WPARAM)b28, 0); break; }
		case FONT_32B:
		{ HFONT b32 = CreateFont(32, 0, 0, 0, FW_NORMAL, false, false, false, ANSI_CHARSET, 0, 0, DEFAULT_QUALITY, DEFAULT_PITCH, "Comic Sans MS"); SendMessage(hEdit, WM_SETFONT, (WPARAM)b32, 0); break; }
		case FONT_64B:
		{ HFONT b64 = CreateFont(64, 0, 0, 0, FW_NORMAL, false, false, false, ANSI_CHARSET, 0, 0, DEFAULT_QUALITY, DEFAULT_PITCH, "Comic Sans MS"); SendMessage(hEdit, WM_SETFONT, (WPARAM)b64, 0); break; }
		case FONT_12C:
		{ HFONT c12 = CreateFont(12, 0, 0, 0, FW_NORMAL, false, false, false, ANSI_CHARSET, 0, 0, DEFAULT_QUALITY, DEFAULT_PITCH, "Times New Roman"); SendMessage(hEdit, WM_SETFONT, (WPARAM)c12, 0); break; }
		case FONT_16C:
		{ HFONT c16 = CreateFont(16, 0, 0, 0, FW_NORMAL, false, false, false, ANSI_CHARSET, 0, 0, DEFAULT_QUALITY, DEFAULT_PITCH, "Times New Roman"); SendMessage(hEdit, WM_SETFONT, (WPARAM)c16, 0); break; }
		case FONT_20C:
		{ HFONT c20 = CreateFont(20, 0, 0, 0, FW_NORMAL, false, false, false, ANSI_CHARSET, 0, 0, DEFAULT_QUALITY, DEFAULT_PITCH, "Times New Roman"); SendMessage(hEdit, WM_SETFONT, (WPARAM)c20, 0); break; }
		case FONT_24C:
		{ HFONT c24 = CreateFont(24, 0, 0, 0, FW_NORMAL, false, false, false, ANSI_CHARSET, 0, 0, DEFAULT_QUALITY, DEFAULT_PITCH, "Times New Roman"); SendMessage(hEdit, WM_SETFONT, (WPARAM)c24, 0); break; }
		case FONT_28C:
		{ HFONT c28 = CreateFont(28, 0, 0, 0, FW_NORMAL, false, false, false, ANSI_CHARSET, 0, 0, DEFAULT_QUALITY, DEFAULT_PITCH, "Times New Roman"); SendMessage(hEdit, WM_SETFONT, (WPARAM)c28, 0); break; }
		case FONT_32C:
		{ HFONT c32 = CreateFont(32, 0, 0, 0, FW_NORMAL, false, false, false, ANSI_CHARSET, 0, 0, DEFAULT_QUALITY, DEFAULT_PITCH, "Times New Roman"); SendMessage(hEdit, WM_SETFONT, (WPARAM)c32, 0); break; }
		case FONT_64C:
		{ HFONT c64 = CreateFont(64, 0, 0, 0, FW_NORMAL, false, false, false, ANSI_CHARSET, 0, 0, DEFAULT_QUALITY, DEFAULT_PITCH, "Times New Roman"); SendMessage(hEdit, WM_SETFONT, (WPARAM)c64, 0); break; }
		case FONT_12D:
		{ HFONT d12 = CreateFont(12, 0, 0, 0, FW_NORMAL, false, false, false, ANSI_CHARSET, 0, 0, DEFAULT_QUALITY, DEFAULT_PITCH, "Consolas"); SendMessage(hEdit, WM_SETFONT, (WPARAM)d12, 0); break; }
		case FONT_16D:
		{ HFONT d16 = CreateFont(16, 0, 0, 0, FW_NORMAL, false, false, false, ANSI_CHARSET, 0, 0, DEFAULT_QUALITY, DEFAULT_PITCH, "Consolas"); SendMessage(hEdit, WM_SETFONT, (WPARAM)d16, 0); break; }
		case FONT_20D:
		{ HFONT d20 = CreateFont(20, 0, 0, 0, FW_NORMAL, false, false, false, ANSI_CHARSET, 0, 0, DEFAULT_QUALITY, DEFAULT_PITCH, "Consolas"); SendMessage(hEdit, WM_SETFONT, (WPARAM)d20, 0); break; }
		case FONT_24D:
		{ HFONT d24 = CreateFont(24, 0, 0, 0, FW_NORMAL, false, false, false, ANSI_CHARSET, 0, 0, DEFAULT_QUALITY, DEFAULT_PITCH, "Consolas"); SendMessage(hEdit, WM_SETFONT, (WPARAM)d24, 0); break; }
		case FONT_28D:
		{ HFONT d28 = CreateFont(28, 0, 0, 0, FW_NORMAL, false, false, false, ANSI_CHARSET, 0, 0, DEFAULT_QUALITY, DEFAULT_PITCH, "Consolas"); SendMessage(hEdit, WM_SETFONT, (WPARAM)d28, 0); break; }
		case FONT_32D:
		{ HFONT d32 = CreateFont(32, 0, 0, 0, FW_NORMAL, false, false, false, ANSI_CHARSET, 0, 0, DEFAULT_QUALITY, DEFAULT_PITCH, "Consolas"); SendMessage(hEdit, WM_SETFONT, (WPARAM)d32, 0); break; }
		case FONT_64D:
		{ HFONT d64 = CreateFont(64, 0, 0, 0, FW_NORMAL, false, false, false, ANSI_CHARSET, 0, 0, DEFAULT_QUALITY, DEFAULT_PITCH, "Consolas"); SendMessage(hEdit, WM_SETFONT, (WPARAM)d64, 0); break; }
		case HELP_GITHUB:
			DebugLog("HELP_GITHUB CALLED");
			WOpenWebsite("https://github.com/neopkr/NeonpadCPP");
			break;
		case HELP_DOC:
			WOpenWebsite("https://github.com/neopkr/NeonpadCPP#neonpadcpp");
			break;
			break;
		case HELP_ABOUT:
			hAbout = CreateWindowEx(0, STATUSCLASSNAME, NULL, WS_CHILD | WS_VISIBLE | SBARS_SIZEGRIP, 0, 0, 100, 200, NULL, NULL, NULL, NULL);
			ShowWindow(hAbout, SW_SHOW);
			break;
		case EDIT_COPY:
		{
			SetClipboardData(CF_TEXT, hEdit);
		
			IsClipboardFormatAvailable(CF_TEXT); // success
			IsClipboardFormatAvailable(CF_UNICODETEXT); // success
			GetClipboardData(CF_TEXT); // success and read right string
			GetClipboardData(CF_UNICODETEXT); // success and read right string
			// unicode string also can test passed
		}
		case EDIT_PASTE:
		{
			if (!IsClipboardFormatAvailable(CF_TEXT)) return wParam;
			if (!OpenClipboard(GetDesktopWindow())) return wParam;
			HGLOBAL hg = GetClipboardData(CF_TEXT);
			if (hg)
			{
				LPSTR strData = (LPSTR)GlobalLock(hg);
				if (strData)
				{
					GlobalUnlock(hg);
					GetWindowText(hEdit, strData, 256);
				}
			}
			CloseClipboard();
		}
		case ID_TEXT:
		{
			SetWindowText(hEdit, "");
			break;
		}
		case FILE_MENU_OPEN:
		{
			switch (wParam)
			{
				case VK_CONTROL:
				{
					::MessageBox(hWnd, _T("Control Button"), _T("Key Pressed"), NULL);
				}
			}
			OPENFILENAME ofn;
			char file_name[1000];
			ZeroMemory(&ofn, sizeof(OPENFILENAME));
			ofn.lStructSize = sizeof(OPENFILENAME);
			ofn.hwndOwner = hWnd;
			ofn.lpstrFile = file_name;
			ofn.lpstrFile[0] = '\0';
			ofn.nMaxFile = 1000;
			ofn.lpstrFilter = "NPDX\0*.npdx*\0Source Files\0*.CPP\0Text Files\0*.TXT\0";
			ofn.nFilterIndex = 1;

			GetOpenFileName(&ofn);

			char* path = ofn.lpstrFile;

			FILE* file;
			errno_t err;

			if ((err = fopen_s(&file, path, "rb")) != NULL)
			{
				fprintf(stderr, "cannot open file '%s' : %s\n",
					path, strerror(err));
			}
			else
			{
				fseek(file, 0, SEEK_END);
				int _size = ftell(file);
				rewind(file);
				char* data = new char(_size + 1);
				fread(data, _size, 1, file);
				data[_size] = '\0';

				SetWindowText(hEdit, data);

				fclose(file);
			}
			break;
		}
		case FORMAT_WW:
		{
			auto action = LOWORD(wParam);
			if (action == WS_HSCROLL || action == CBS_AUTOHSCROLL)
				break;
			break;
		}
		case FILE_MENU_SAVE:
		{
			OPENFILENAME ofn;
			char file_name[1000];
			ZeroMemory(&ofn, sizeof(OPENFILENAME));

			ofn.lStructSize = sizeof(OPENFILENAME);
			ofn.hwndOwner = hWnd;
			ofn.lpstrFile = file_name;
			ofn.lpstrFile[0] = '\0';
			ofn.nMaxFile = 1000;
			ofn.lpstrFilter = "NPDX\0*.npdx*\0Source Files\0*.CPP\0Text Files\0*.TXT\0";
			ofn.nFilterIndex = 1;

			int tex1 = GetWindowTextLength(hEdit);


			char* path = ofn.lpstrFile;

			FILE* file;
			errno_t err;

			if (tex1 == 0)
			{
				MessageBox(NULL, "No se puede guardar un texto vacio!", "Neonpad", NULL);
				break;
			}
			else
			{
				
			GetSaveFileName(&ofn);
			if ((err = fopen_s(&file, path, "w")) != NULL)
			{
				fprintf(stderr, "cannot open file '%s' : %s\n",
					path, strerror(err));
			}
			else
			{
				int _size = GetWindowTextLength(hEdit);
				char* data = new char[_size + 1];
				GetWindowText(hEdit, data, _size + 1);
				fwrite(data, _size + 1, 1, file);
				fclose(file);

			}
			break;
			}
		}
		case FILE_MENU_NEW:
		{
			SetWindowText(hEdit, "");
			SetWindowTextW(hWnd, L"Neonpad - New");
			break;
		}
		case FILE_MENU_EXIT:
			DestroyWindow(hWnd);
			break;
		case EDIT_FONT:
			break;
		case FILE_MENU_SAVE_OVERWRITE:
			OPENFILENAME ofn;
			char file_name[1000];
			ZeroMemory(&ofn, sizeof(OPENFILENAME));

			ofn.lStructSize = sizeof(OPENFILENAME);
			ofn.hwndOwner = hWnd;
			ofn.lpstrFile = file_name;
			ofn.lpstrFile[0] = '\0';
			ofn.nMaxFile = 1000;
			ofn.lpstrFilter = "NPDX\0*.npdx*\0Source Files\0*.CPP\0Text Files\0*.TXT\0";
			ofn.nFilterIndex = 1;

			char* path = ofn.lpstrFile;

			FILE* file;
			errno_t err;

			int tex = GetWindowTextLength(hEdit);

			if (tex == 0)
			{
				MessageBox(NULL, "No se puede guardar un archivo vacio!", "Neonpad", NULL);
				break;
			}
			else
			{
				GetSaveFileName(&ofn);
			if ((err = fopen_s(&file, path, "w")) != NULL)
			{
				fprintf(stderr, "cannot open file '%s' : %s\n",
					path, strerror(err));
			}
			else
			{
				int _size = GetWindowTextLength(hEdit);
				char* data = new char[_size + 1];
				GetWindowText(hEdit, data, _size + 1);
				fwrite(data, _size + 1, 1, file);
				fclose(file);

			}
			break;
			}
		}
	/*
	case WM_VSCROLL:
	{
		auto action = LOWORD(wParam);
		HWND hScroll = (HWND)lParam;
		int pos = -1;
		if (action == SB_THUMBPOSITION || action == SB_THUMBTRACK)
		{
			pos = HIWORD(wParam);
		}
		else if (action == SB_LINEDOWN)
		{
			pos = g_scrollY + 0;
		}
		else if (action == SB_LINEUP)
		{
			pos = g_scrollY - 0;
		}
		if (pos == -1)
			break;
		WCHAR buf[20];
		SCROLLINFO si = { 0 };
		si.cbSize = sizeof(SCROLLINFO);
		si.fMask = SIF_POS;
		si.nPos = pos;
		si.nTrackPos = 0;
		SetScrollInfo(hWnd, SB_VERT, &si, true);
		GetScrollInfo(hWnd, SB_VERT, &si);
		pos = si.nPos;
		POINT pt;
		pt.x = 0;
		pt.y = pos - g_scrollY;
		auto hdc = GetDC(hWnd);
		LPtoDP(hdc, &pt, 1);
		ReleaseDC(hWnd, hdc);
		ScrollWindow(hWnd, 0, -pt.y, NULL, NULL);
		g_scrollY = pos;
		return 0;
	}
	case WM_SIZE:
	{
		RECT rc = { 0 };
		GetClientRect(hWnd, &rc);
		SCROLLINFO si = { 0 };
		si.cbSize = sizeof(SCROLLINFO);
		si.fMask = SIF_ALL;
		si.nMin = 0;
		si.nMax = 30 * 99 + 21;
		si.nPage = (rc.bottom - rc.top);
		si.nPos = 0;
		si.nTrackPos = 0;
		SetScrollInfo(hWnd, SB_VERT, &si, true);
		break;
	}
	*/
	case WM_PAINT:
		RECT rect;
		hdc = BeginPaint(hWnd, &ps);
		hFont = CreateFont(0, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, TEXT("Arial"));
		SelectObject(hdc, hFont);
		SetRect(&rect, 100, 100, 700, 200);
		SetTextColor(hdc, RGB(255, 0, 0));
		DrawText(hdc, TEXT("dw arial"), -1, &rect, DT_NOCLIP);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}
	return 0;
}