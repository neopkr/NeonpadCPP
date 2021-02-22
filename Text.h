#include <iostream>
#include <windows.h>
#include <tchar.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <Commctrl.h>
#include <errno.h>

#define ID_TEXT 0
#define FILE_MENU_EXIT 3
#define EDIT_FONT 10
#define FILE_MENU_SAVE_OVERWRITE 22
#define HELP_MENU_WW 12
#define FILE_MENU_SAVE 4
#define FILE_MENU_NEW 5
#define FILE_MENU_OPEN 6
#define EDIT_PRINT 7
#define EDIT_COPY 8
#define EDIT_PASTE 9
#define EDIT_CUT 11
#define MAX 1000
#define iO 0x4F

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
TCHAR editCut[] = _T("Cut");
TCHAR editCopy[] = _T("Copy");
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
