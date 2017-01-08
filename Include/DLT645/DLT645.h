#ifndef DLT645_H
#define DLT645_H

#include "DLT645Comm.h"

class DLT645Cmd;
class DLT645DI;

class DLT645_API DLT645 : public MeterProtocol
{
protected :
	static INT_PTR __stdcall DLT645WindowProc(HWND,UINT,WPARAM,LPARAM);
	bool SendData(char * data,int offset,int len);
	HWND hWnd;
	bool isStop;
	std::map<const wchar_t *,std::vector<DLT645DI *> *> diGroups;
protected :
	bool LoadCmdFile(const wchar_t *cmdFile);
	bool LoadDIFile(const wchar_t *diFile);

public :
	HWND hWndRecvied;
	HWND hWndSended;
public :
	DLT645();

	std::vector<DLT645Cmd *> cmds;
	const wchar_t* GetName();

	const wchar_t* GetDes();

	int  Init()=0;

	int Unload();

	HWND CreateTargetWindow(HWND hWndParent);

	bool SetConnection(Connection *connection);

	int Stop();

	bool AndCmd(DLT645Cmd *cmd);

	DLT645Cmd * GetCmd(const wchar_t *name);

	virtual ~DLT645();
};


#endif