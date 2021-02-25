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
HWND hEdit;
HFONT hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
HWND hFontSize;

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
	
	hInst = hInstance;
	HWND hWnd = CreateWindow(
		szWindowClass,
		szTitle,
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT,
		1000, 600,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	HWND dhWnd = CreateWindow(
		"",
		"",
		WS_TABSTOP | WS_BORDER | WS_VISIBLE | WS_CHILD,
		500,500,
		10,10,
		hWnd,
		NULL,
		(HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
		NULL
	);

	if(!hWnd)
	{
		MessageBox(NULL,
			_T("Call to CreateWindow failed!"),
			_T("Neonpad"),
			NULL);

		return 1;
	}


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
		AppendMenu(view, MF_STRING, NULL, nodata);
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
		AppendMenu(editSubMenu, MF_STRING, FONT_ARIAL, "Arial");
		AppendMenu(editSubMenu, MF_STRING, FONT_CSMS, "Comic Sans MS");
		AppendMenu(editSubMenu, MF_STRING, FONT_TNR, "Times New Roman");
		AppendMenu(editSubMenu, MF_STRING, FONT_CONSOLAS, "Consolas");
		SEPARATOR(editSubMenu);
		AppendMenu(editSubMenu, MF_POPUP | MF_STRING, (UINT_PTR)fontSize, "Font Size");
		AppendMenu(fontSize, MF_STRING, FONT_12, "12");
		AppendMenu(fontSize, MF_STRING, FONT_16, "16");
		AppendMenu(fontSize, MF_STRING, FONT_20, "20");
		AppendMenu(fontSize, MF_STRING, FONT_24, "24");
		AppendMenu(fontSize, MF_STRING, FONT_28, "28");
		AppendMenu(fontSize, MF_STRING, FONT_32, "32");
		AppendMenu(fontSize, MF_STRING, FONT_64, "64");
		// help
		AppendMenu(help, MF_STRING, HELP_DOC, "Documentation");
		AppendMenu(help, MF_STRING, HELP_GITHUB, "GitHub Repository");
		SEPARATOR(help);
		AppendMenu(help, MF_STRING, HELP_ABOUT, "About");
		SetMenu(hWnd, menubar);
		
		// TextBox
		hEdit = CreateWindow(ename, "", WS_VISIBLE | WS_CHILD | ES_MULTILINE | WS_EX_LAYERED | WS_VSCROLL | WS_HSCROLL, 0, 1, 985, 540, hWnd, (HMENU)ID_TEXT, NULL, hFont);
		break;
	}	
	case WM_COMMAND:
		switch (wParam)
		{
		case FONT_ARIAL: changeFont(hEdit, arial); break;
		case FONT_CSMS: changeFont(hEdit, csMS); break;
		case FONT_TNR: changeFont(hEdit, TNR); break;
		case FONT_CONSOLAS: changeFont(hEdit, Consolas); break;
		// not working font size
		case FONT_12: szFont = 12; break;
		case FONT_16: szFont = 16; break;
		case FONT_20: szFont = 20; break;
		case FONT_24: szFont = 24; break;
		case FONT_28: szFont = 28; break;
		case FONT_32: szFont = 32; break;
		case FONT_64: szFont = 64; break;
		case HELP_GITHUB:
			// TODO: HyperLink
		case EDIT_COPY:
		{
			SetClipboardData(CF_TEXT, hWnd);
		
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

			fileNewOption(hWnd);
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
			ofn.lpstrFilter = "All files\0*.*\0Source Files\0*.CPP\0Text Files\0*.TXT\0";
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
			ofn.lpstrFilter = "All files\0*.*\0Source Files\0*.CPP\0Text Files\0*.TXT\0";
			ofn.nFilterIndex = 1;

			GetSaveFileName(&ofn);

			char* path = ofn.lpstrFile;

			FILE* file;
			errno_t err;

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
			ofn.lpstrFilter = "All files\0*.*\0Source Files\0*.CPP\0Text Files\0*.TXT\0";
			ofn.nFilterIndex = 1;

			GetSaveFileName(&ofn);

			char* path = ofn.lpstrFile;

			FILE* file;
			errno_t err;

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