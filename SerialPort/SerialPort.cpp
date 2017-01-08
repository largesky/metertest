
#include "SerialPort.h"
#include "..\Include\MeterBase\ConnectionManager.h"
#include "..\SerialPort\resource.h"
#include <Windowsx.h>
SerialPort * sp=0;

SerialPort::SerialPort()
{
}

SerialPort::SerialPort(int portNumber)
{
	wsprintf(this->PortName,_T("\\\\.\\COM%d"),portNumber);
}

SerialPort::SerialPort(const TCHAR *portName)
{
	assert(portName);
	wsprintf(this->PortName,_T("\\\\.\\%s"),portName);
}

SerialPort::~SerialPort()
{
}
int SerialPort::InitSerialPort()
{
	this->state=Connection::STATE_CLOSE;
	this->hSerialPort =CreateFile(PortName,//COM1口
		GENERIC_READ|GENERIC_WRITE, //允许读和写
		0, //独占方式
		NULL,
		OPEN_EXISTING, //打开而不是创建
		(int)(this->overLaped), //同步方式
		NULL);
	if(this->hSerialPort != INVALID_HANDLE_VALUE)
	{
		COMMTIMEOUTS timeOut;
		if(this->GetCommTimeouts(&timeOut)==TRUE)
		{
			timeOut.ReadIntervalTimeout=this->GetBitReadTimeOut();
			timeOut.ReadTotalTimeoutConstant=this->GetFrameReadTimeOut();
			timeOut.ReadTotalTimeoutMultiplier=0;
			timeOut.WriteTotalTimeoutConstant=this->GetBitWriteTimeOut();
			timeOut.WriteTotalTimeoutMultiplier=0;
			if(this->SetCommTimeouts(&timeOut)==FALSE)
			{
				//处理错误
				assert(0);
			}
		}

		//设置DCB
		DCB currentDCB={sizeof(DCB)};
		if(this->GetCommState(&currentDCB) ==FALSE)
		{
			int id=GetLastError();
			assert(0);
		}
		currentDCB.BaudRate=this->SerialPortConfig.BaudRate;
		currentDCB.ByteSize=this->SerialPortConfig.ByteSize;
		currentDCB.Parity=this->SerialPortConfig.Parity;
		currentDCB.StopBits=this->SerialPortConfig.StopBits;

		if(this->SetCommState(&currentDCB) ==FALSE)
		{
			int id=GetLastError();
			assert(0);
		}
		this->state=SerialPort::STATE_OPEN;
	}
	else
	{
		DWORD id=GetLastError();
		this->state=SerialPort::STATE_CLOSE;
	}
	return (int) (this->hSerialPort);
}

int SerialPort::OpenFile(bool overLaped)
{
	this->overLaped = overLaped;
	return this->InitSerialPort();
}

int SerialPort::Pause()
{
	return this->SetCommBreak();
}

int SerialPort::Resume()
{
	return this->ClearCommBreak();
}

int SerialPort::CloseFile()
{
	BOOL ret=CloseHandle(this->hSerialPort);
	if(ret==TRUE)
	{
		this->hSerialPort=0;
		this->state=SerialPort::STATE_CLOSE;
	}
	return ret;
}

BOOL WINAPI SerialPort::ReadFile(__out LPVOID lpBuffer, __in  DWORD nNumberOfBytesToRead,__out_opt LPDWORD lpNumberOfBytesRead,__inout_opt  LPOVERLAPPED lpOverlapped)
{
	return ::ReadFile(this->hSerialPort,lpBuffer,nNumberOfBytesToRead,lpNumberOfBytesRead,lpOverlapped);
}

int SerialPort::ReadData(void * lpBuffer,int len)
{
	DWORD readed=0;
	this->ReadFile(lpBuffer,len,&readed,NULL);
	return readed;
}

BOOL WINAPI SerialPort::WriteFile(__in LPCVOID lpBuffer, __in DWORD nNumberOfBytesToWrite,__out_opt LPDWORD lpNumberOfBytesWritten, __inout_opt LPOVERLAPPED lpOverlapped)
{
	return ::WriteFile(this->hSerialPort,lpBuffer,nNumberOfBytesToWrite,lpNumberOfBytesWritten,lpOverlapped);
}

int SerialPort::WriteData(void *lpBuffer,int off, int len)
{
	DWORD writed=0;
	
	if(this->bitWriteIntervalTime==0)
	{
		this->WriteFile((char *)lpBuffer+off,len,&writed,NULL);
	}
	else
	{
		DWORD isWrited=0;
		for(int i=0;i<len;i++)
		{
			::Sleep(this->bitWriteIntervalTime);
			if(this->WriteFile(((char *)lpBuffer)+off+i,1,&isWrited,NULL)==TRUE)
			{
				writed+=isWrited;
			}
			else
			{
				writed=-1;
				break;
			}
		}
	}
	return writed;
}

BOOL WINAPI SerialPort::ClearCommBreak()
{
	return ::ClearCommBreak(this->hSerialPort);
}

BOOL WINAPI SerialPort::ClearCommError( __out_opt  LPDWORD lpErrors, __out_opt  LPCOMSTAT lpStat)
{
	return ::ClearCommError(this->hSerialPort,lpErrors,lpStat);
}

BOOL WINAPI SerialPort::GetCommConfig( __out LPCOMMCONFIG lpCC,__inout  LPDWORD lpdwSize)
{
	return ::GetCommConfig(this->hSerialPort,lpCC,lpdwSize);
}

BOOL WINAPI  SerialPort::GetCommMask( __out  LPDWORD lpEvtMask)
{
	return ::GetCommMask(this->hSerialPort,lpEvtMask);
}

BOOL WINAPI  SerialPort::GetCommModemStatus(__out  LPDWORD lpModemStat)
{
	return ::GetCommModemStatus(this->hSerialPort,lpModemStat);
}

BOOL WINAPI  SerialPort::GetCommProperties(__out  LPCOMMPROP lpCommProp)
{
	return ::GetCommProperties(this->hSerialPort,lpCommProp);
}

BOOL WINAPI SerialPort::GetCommTimeouts(__out  LPCOMMTIMEOUTS lpCommTimeouts)
{
	return ::GetCommTimeouts(this->hSerialPort,lpCommTimeouts);
}

BOOL WINAPI SerialPort::GetCommState( __out LPDCB lpDCB)
{
	return ::GetCommState(this->hSerialPort,lpDCB);
}

BOOL WINAPI SerialPort::PurgeComm( __in  DWORD dwFlags)
{
	return ::PurgeComm(this->hSerialPort,dwFlags);
}

BOOL WINAPI SerialPort::SetCommBreak()
{
	return ::SetCommBreak(this->hSerialPort);
}

BOOL WINAPI SerialPort::SetCommConfig(__in  LPCOMMCONFIG lpCC, __in  DWORD dwSize)
{
	return ::SetCommConfig(this->hSerialPort,lpCC,dwSize);
}

BOOL WINAPI SerialPort::SetCommMask(__in  DWORD dwEvtMask)
{
	return ::SetCommMask(this->hSerialPort,dwEvtMask);
}

BOOL WINAPI SerialPort::SetCommState(__in  LPDCB lpDCB)
{
	return ::SetCommState(this->hSerialPort,lpDCB);
}

BOOL WINAPI SerialPort::SetCommTimeouts(__in  LPCOMMTIMEOUTS lpCommTimeouts)
{
	return ::SetCommTimeouts(this->hSerialPort,lpCommTimeouts);
}

BOOL WINAPI SerialPort::SetupComm(__in  DWORD dwInQueue,__in  DWORD dwOutQueue)
{
	return ::SetupComm(this->hSerialPort,dwInQueue,dwOutQueue);
}

BOOL WINAPI SerialPort::TransmitCommChar(__in  char cChar)
{
	return ::TransmitCommChar(this->hSerialPort,cChar);
}

BOOL WINAPI SerialPort::WaitCommEvent( __out  LPDWORD lpEvtMask, __in   LPOVERLAPPED lpOverlapped)
{
	return ::WaitCommEvent(this->hSerialPort,lpEvtMask,lpOverlapped);
}

BOOL WINAPI SerialPort::BuildCommDCB( __in LPCTSTR lpDef,__out  LPDCB lpDCB)
{
	return ::BuildCommDCB(lpDef,lpDCB);
}

BOOL WINAPI SerialPort::GetDefaultCommConfig(__in LPCTSTR lpszName,__out LPCOMMCONFIG lpCC, __inout LPDWORD lpdwSize)
{
	return ::GetDefaultCommConfig(lpszName,lpCC,lpdwSize);
}

BOOL WINAPI SerialPort::SetDefaultCommConfig(__in  LPCTSTR lpszName,__in  LPCOMMCONFIG lpCC,__in  DWORD dwSize)
{
	return ::SetDefaultCommConfig(lpszName,lpCC,dwSize);
}

const wchar_t * SerialPort::GetName()
{
	return L"SerialPortConnection";
}

const wchar_t *SerialPort::GetDes()
{
	return L"串口通信组件";
}

bool SerialPort::ShowConfigWindow(HWND parent)
{
	INT_PTR ret=DialogBoxParam((HINSTANCE)g_HModule,MAKEINTRESOURCE(IDD_SERIALPORTCONFIG),parent,CONFIGPROC,(LPARAM)this);
	return ret==IDOK;
}

bool SerialPort::Open()
{
	this->OpenFile(false);
	return this->state == SerialPort::STATE_OPEN;
}

bool SerialPort::Close()
{
	return this->CloseFile()==0;
}

int SerialPort::GetType()
{
	return Connection::STREAM_TYPE_COMM;
}

std::vector<const wchar_t *> *SerialPort::GetSerialPorts()
{
	HKEY keyPorts=0;
	LONG ret=0;
	std::vector<const wchar_t*> *ports=new std::vector<const wchar_t *>();
#ifdef _WIN64
	ret=RegOpenKeyEx(HKEY_LOCAL_MACHINE,L"HARDWARE\\DEVICEMAP\\SERIALCOMM",0,KEY_READ,&keyPorts);
#else
	ret=RegOpenKeyEx(HKEY_LOCAL_MACHINE,L"HARDWARE\\DEVICEMAP\\SERIALCOMM",0,KEY_READ |KEY_WOW64_32KEY,&keyPorts);
#endif
	if(ret!=ERROR_SUCCESS)
	{
		return ports;
	}
	int index=0;
	wchar_t name[500]={0};
	BYTE value[50]={0};
	DWORD type=0;
	while(true)
	{
		DWORD nameLen=500;
		DWORD valueLen=50;
		SecureZeroMemory(value,sizeof(value));
		ret=RegEnumValue(keyPorts,index,name,&nameLen,NULL,&type,value,&valueLen);
		if(ret != ERROR_SUCCESS)
		{
			break;
		}
		else
		{
			wchar_t * data=new wchar_t[valueLen/2+1];
			::SecureZeroMemory(data,(valueLen/2+1)*sizeof(wchar_t));
			::memcpy((void *)data,value,valueLen);
			ports->push_back(data);
		}
		index++;
	}
	RegCloseKey(keyPorts);
	return ports;
}

SerialPort *serialPort;
INT_PTR CALLBACK CONFIGPROC(HWND hDlg,UINT message,WPARAM wParam,LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		{
			int ret=0;
			serialPort=(SerialPort *)lParam;
			SetDlgItemInt(hDlg,IDC_READINTERVALTIMEOUT,serialPort->GetBitReadTimeOut(),FALSE);
			SetDlgItemInt(hDlg,IDC_READTOTALTIMECONSTTANT,serialPort->GetFrameReadTimeOut(),FALSE);
			SetDlgItemInt(hDlg,IDC_WRITETIMEOUT,serialPort->GetBitWriteTimeOut(),FALSE);
			SetDlgItemInt(hDlg,IDC_WRITEBITPERTIME,serialPort->GetBitWriteIntervalTime(),FALSE);

			//串口
			std::vector<const wchar_t *> *ports=SerialPort::GetSerialPorts();
			for(int i=0;i<ports->size();i++)
			{
				ret=ComboBox_AddString(GetDlgItem(hDlg,IDC_SERIALPORTS),ports->at(i));
			}
			if(ports->size()>0)
			{
				ComboBox_SetCurSel(GetDlgItem(hDlg,IDC_SERIALPORTS),0);
			}
			for(int i=0;i<ports->size();i++)
			{
				delete ports->at(i);
			}
			delete ports;
			//速率
			ret=ComboBox_AddString(GetDlgItem(hDlg,IDC_BOUNDRATE),L"400");
			ret=ComboBox_AddString(GetDlgItem(hDlg,IDC_BOUNDRATE),L"600");
			ret=ComboBox_AddString(GetDlgItem(hDlg,IDC_BOUNDRATE),L"800");
			ret=ComboBox_AddString(GetDlgItem(hDlg,IDC_BOUNDRATE),L"1200");
			ret=ComboBox_AddString(GetDlgItem(hDlg,IDC_BOUNDRATE),L"1600");
			ret=ComboBox_AddString(GetDlgItem(hDlg,IDC_BOUNDRATE),L"2400");
			ComboBox_SetCurSel(GetDlgItem(hDlg,IDC_BOUNDRATE),5);

			//数据位
			wchar_t tmpStr[10]={0};
			for(int j=4;j<9;j++)
			{
				wsprintf(tmpStr,L"%d",j);
				ret=ComboBox_AddString(GetDlgItem(hDlg,IDC_DATABITS),tmpStr);
			}
			ComboBox_SetCurSel(GetDlgItem(hDlg,IDC_DATABITS),4);

			//停止位
			ret=ComboBox_AddString(GetDlgItem(hDlg,IDC_STOPBITS),L"1");
			ret=ComboBox_AddString(GetDlgItem(hDlg,IDC_STOPBITS),L"1.5");
			ret=ComboBox_AddString(GetDlgItem(hDlg,IDC_STOPBITS),L"2");
			ComboBox_SetCurSel(GetDlgItem(hDlg,IDC_STOPBITS),0);

			//校验
			ret=ComboBox_AddString(GetDlgItem(hDlg,IDC_CS),L"奇 Odd");
			ret=ComboBox_AddString(GetDlgItem(hDlg,IDC_CS),L"偶 Even");
			ret=ComboBox_AddString(GetDlgItem(hDlg,IDC_CS),L"无 None");
			ComboBox_SetCurSel(GetDlgItem(hDlg,IDC_CS),1);

			//流控制
			ret=ComboBox_AddString(GetDlgItem(hDlg,IDC_CONTROL),L"Xon/Xoff");
			ret=ComboBox_AddString(GetDlgItem(hDlg,IDC_CONTROL),L"硬件");
			ret=ComboBox_AddString(GetDlgItem(hDlg,IDC_CONTROL),L"无");
			ComboBox_SetCurSel(GetDlgItem(hDlg,IDC_CONTROL),2);
			return (INT_PTR)TRUE;
		}
	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			//从界面读取数据
			BOOL translated=0;
			sp->SetBitReadTimeOut(::GetDlgItemInt(hDlg,IDC_READINTERVALTIMEOUT,&translated,false));
			sp->SetFrameReadTimeOut(::GetDlgItemInt(hDlg,IDC_READTOTALTIMECONSTTANT,&translated,false));
			sp->SetBitWriteTimeOut(::GetDlgItemInt(hDlg,IDC_WRITETIMEOUT,&translated,FALSE));
			sp->SetBitWriteIntervalTime(GetDlgItemInt(hDlg,IDC_WRITEBITPERTIME,&translated,FALSE));

			wchar_t strTmp[100];

			//串口
			GetWindowText(GetDlgItem(hDlg,IDC_SERIALPORTS),strTmp,10);
			if(wcslen(strTmp) < 1)
			{
				MessageBox(hDlg,L"请选择串口",L"提示",MB_OK);
				return TRUE;
			}
			wsprintf(sp->PortName,_T("\\\\.\\%s"),strTmp);
			
			//速率
			GetWindowText(GetDlgItem(hDlg,IDC_BOUNDRATE),strTmp,100);
			sp->SerialPortConfig.BaudRate=_ttoi(strTmp);

			//数据位
			GetWindowText(GetDlgItem(hDlg,IDC_DATABITS),strTmp,100);
			sp->SerialPortConfig.ByteSize=_ttoi(strTmp);

			//校验位
			GetWindowText(GetDlgItem(hDlg,IDC_CS),strTmp,100);
			if(strTmp[0]==L'奇')
			{
				sp->SerialPortConfig.Parity=ODDPARITY;
			}
			else if(strTmp[0]==L'偶')
			{
				sp->SerialPortConfig.Parity=EVENPARITY;
			}
			else
			{
				sp->SerialPortConfig.Parity=NOPARITY;
			}

			//停止位
			GetWindowText(GetDlgItem(hDlg,IDC_STOPBITS),strTmp,100);
			if(::_tccmp(strTmp,L"1")==0 && _tcslen(strTmp)==1)
			{
				sp->SerialPortConfig.StopBits=0;
			}
			else if(_tccmp(strTmp,L"2")==0&& _tcslen(strTmp)==1)
			{
				sp->SerialPortConfig.StopBits=2;
			}
			else
			{
				sp->SerialPortConfig.StopBits=1;
			}

			//流控制
			GetWindowText(GetDlgItem(hDlg,IDC_CONTROL),strTmp,100);
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		if(LOWORD(wParam) ==IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
extern "C"
{
	//获取插件 类型
	const wchar_t * GETPLUGINTYPE()
	{
		return L"Connection";
	}

	//获取插件名称
	const wchar_t * GETPLUGINNAME()
	{
		return L"SerialPort";
	}

	//获取插件描述
	const wchar_t * GETPLUGINDES()
	{
		return L"串口通信";
	}

	//安装插件
	DWORD INSTALL()
	{
		sp=new SerialPort(0);
		ConnectionManager::GetInstance()->InstallItem(sp);
		return 0;
	}

	//移出插件
	DWORD UNINSTALL()
	{
		ConnectionManager::GetInstance()->UninstallItem(sp->GetName());
		delete sp;
		return 0;
	}
}