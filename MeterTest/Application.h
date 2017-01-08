
#include "stdafx.h"


#ifndef APPLICATION_H
#define APPLICATION_H

class Application
{
	MeterProtocolManager *meterProtocolManager;
	ConnectionManager *connectionManager;

	MeterProtocol *currentMeterProtocol;
	Connection *currentConnection;

	// 应用程序主窗体
	HWND hMainWindow;

	//当前协议的窗体
	HWND hCurrentWindow;

	//状态窗体
	HWND hStatusBarWindow;
public:
	Application()
	{
		this->meterProtocolManager=new MeterProtocolManager();
		this->connectionManager =new ConnectionManager();
		this->currentMeterProtocol=0;
		this->hCurrentWindow=0;
		this->hStatusBarWindow=0;
		this->hMainWindow=0;
	}

	void SetCurrentMeterProtocol(MeterProtocol * protocol)
	{
		this->currentMeterProtocol=protocol;
		HWND hWnd=this->currentMeterProtocol->CreateTargetWindow(this->hMainWindow);
		this->SetCurrentWindow(hWnd);
		this->currentMeterProtocol->SetConnection(this->currentConnection);
	}

	HWND GetMainWindow()
	{
		return this->hMainWindow;
	}

	void SetMainWindow(HWND hWnd)
	{
		this->hMainWindow=hWnd;
	}

	HWND GetCurrentWindow()
	{
		return this->hCurrentWindow;
	}

	HWND GetStatusBarWindow()
	{
		return this->hStatusBarWindow;
	}

	void SetStatusBarWindow(HWND hWnd)
	{
		this->hStatusBarWindow=hWnd;
	}

	void SetCurrentWindow(HWND hWnd)
	{
		this->hCurrentWindow=hWnd;
		RECT workArea;
		::GetClientRect(this->hMainWindow,&workArea);
		RECT statusBarRECT={0};
		::GetClientRect(this->hStatusBarWindow,&statusBarRECT);
		BOOL ret=MoveWindow(this->hCurrentWindow,0,0,workArea.right,workArea.bottom-(statusBarRECT.bottom-statusBarRECT.top) ,true);
		::ShowWindow(hWnd,SW_SHOW | SW_SHOWNORMAL);
	}

	void SetCurrentConnection(Connection *connection)
	{
		if(this->currentConnection !=0)
		{
			if(this->currentConnection->Close()==false)
			{
			}
		}
		this->currentConnection=connection;
		if(this->currentConnection->ShowConfigWindow(this->hMainWindow) ==false)
		{
			return ;
		}
		if(this->currentConnection->Open()==false)
		{
		}
		else
		{
			if(this->currentMeterProtocol !=0)
			{
				this->currentMeterProtocol->SetConnection(this->currentConnection);
			}
			/*char buf[2]={'a'};
			int ret=this->currentConnection->WriteData(buf,0,1);
			ret=this->currentConnection->ReadData(buf,1);
			int i=0;*/
		}
	}

	void ShutDown()
	{
		if(this->currentMeterProtocol!=0)
		{
			this->currentMeterProtocol->Stop();
		}
		if(this->currentConnection!=0)
		{
			this->currentConnection->Close();
		}
	}
};
#endif
