#ifndef DISELECTOR_H
#define DISELECTOR_H

#include "DLT645Comm.h"

class DLT645DI;

class DLT645_API DISelector
{
public :
	static INT_PTR CALLBACK DISelectorProc(HWND hDlg,UINT message,WPARAM wParam,LPARAM lParam);

private :
	std::map<const wchar_t *,std::vector<DLT645DI *> *> *diGroups;
public :
	wchar_t SelectedDI[8];

	DISelector(std::map<const wchar_t *,std::vector<DLT645DI *> *> *diGroups);

	bool ShowDialog(HWND hWnd);

};
#endif