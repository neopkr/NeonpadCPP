#include <iostream>
#include <windows.h>
#include <tchar.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <Commctrl.h>
#include <errno.h>

#define ID_TEXT 0
#define ID_FONT_SIZE 16
#define FILE_MENU_EXIT 3
#define EDIT_FONT 10
#define FILE_MENU_SAVE_OVERWRITE 22
#define FORMAT_WW 12
#define FILE_MENU_SAVE 4
#define FILE_MENU_NEW 5
#define FILE_MENU_OPEN 6
#define EDIT_DELETE 7
#define EDIT_COPY 8
#define EDIT_PASTE 9
#define EDIT_CUT 11
#define HELP_DOC 13
#define HELP_ABOUT 14
#define HELP_GITHUB 15
#define MAX 1000
#define iO 0x4F

// FONT SIZE - FONT CREATOR
#define FONT_ARIAL 100
#define FONT_CSMS 101
#define FONT_TNR 102
#define FONT_CONSOLAS 103

#define FONT_12A 200
#define FONT_16A 201
#define FONT_20A 202
#define FONT_24A 203
#define FONT_28A 204
#define FONT_32A 205
#define FONT_64A 230

#define FONT_12B 206
#define FONT_16B 207
#define FONT_20B 208
#define FONT_24B 209
#define FONT_28B 210
#define FONT_32B 211
#define FONT_64B 231

#define FONT_12C 212
#define FONT_16C 213
#define FONT_20C 214
#define FONT_24C 215
#define FONT_28C 216
#define FONT_32C 217
#define FONT_64C 232

#define FONT_12D 218
#define FONT_16D 219
#define FONT_20D 220
#define FONT_24D 221
#define FONT_28D 222
#define FONT_32D 223
#define FONT_64D 233

int szFont = 17;

HFONT arial = CreateFont(szFont, 0, 0, 0, FW_NORMAL, false, false, false, ANSI_CHARSET, 0, 0, DEFAULT_QUALITY, DEFAULT_PITCH, "Arial");
HFONT csMS = CreateFont(22, 0, 0, 0, FW_NORMAL, false, false, false, DEFAULT_CHARSET, 0, 0, DEFAULT_QUALITY, DEFAULT_PITCH, "Comic Sans MS"); // Comic Sans has a predefined Size for now
HFONT TNR = CreateFont(szFont, 0, 0, 0, FW_NORMAL, false, false, false, DEFAULT_CHARSET, 0, 0, DEFAULT_QUALITY, DEFAULT_PITCH, "Times New Roman");
HFONT Consolas = CreateFont(szFont, 0, 0, 0, FW_NORMAL, false, false, false, DEFAULT_CHARSET, 0, 0, DEFAULT_QUALITY, DEFAULT_PITCH, "Consolas");

HWND hText;
TCHAR save[] = _T("Save");
TCHAR subFont[] = _T("Font");
TCHAR nodata[] = _T("NULL");
// menu bar
TCHAR fname[] = _T("File");
TCHAR ename[] = _T("Edit");
TCHAR vname[] = _T("View");
TCHAR hname[] = _T("Help");
// file bar
TCHAR fileNew[] = _T("New");
TCHAR fileOpen[] = _T("Open");
TCHAR fileSave[] = _T("Save");
TCHAR fileSaveAs[] = _T("Save As");
TCHAR fileExit[] = _T("Exit");
// view

// edit
TCHAR editPrint[] = _T("Print");
TCHAR editCut[] = _T("Cut			Ctrl+X");
TCHAR editCopy[] = _T("Copy			Ctrl+C");
// help
TCHAR helpWW[] = _T("Word Wrap");

// functions

void SEPARATOR(HMENU hMenu)
{
	AppendMenu(hMenu, MF_SEPARATOR, NULL, NULL);
}
void setFont(HWND hWnd, int fontSize, HFONT font)
{
	// add 
}
int overwriteArchive(TCHAR* text, TCHAR* title);
void fileNewOption(HWND hWnd)
{
	//log
	
	//
	SendMessage(hWnd, WM_SETTEXT, 0, (LPARAM)L"");
}
void changeFont(HWND hWnd, HFONT font)
{
	SendMessage(hWnd, WM_SETFONT, (WPARAM)font, 0);
}
void exFont(int szFont, LPCSTR font)
{
	szFont = 16; // default
	CreateFont(szFont, 0, 0, 0, FW_NORMAL, false, false, false, ANSI_CHARSET, 0, 0, DEFAULT_QUALITY, DEFAULT_PITCH, font);
}