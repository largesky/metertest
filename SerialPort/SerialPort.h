#ifndef SERIALPORT_H
#define SERIALPORT_H

#include "..\Include\SerialPort\SerialPortComm.h"

#include "..\Include\MeterBase\Connection.h"

class SERIALPORT_API SerialPort : public Connection
{
private :
	int state;

public :

	/*
	从注册表中获取所有的 串口
	**/
	static std::vector<const wchar_t *> *GetSerialPorts();

	/*
	使用指定的字符填充 DCB结构
	lpDef 字符串 : COM x[:][baud= b][parity= p][data= d][stop= s][to={on|off}][xon={on|off}][odsr={on|off}][octs={on|off}][dtr={on|off|hs}][rts={on|off|hs|tg}][idsr={on|off}] 
	例如一个合法的格式: baud=1200 parity=N data=8 stop=1
	lpDCB指向一个 DCB结构

	返回值:
	成功 非0
	失败 0
	*/

	static BOOL WINAPI BuildCommDCB( __in LPCTSTR lpDef,__out  LPDCB lpDCB);

	/*
	获取设备的 默认配置值

	返回值:
	成功 非0
	失败 0
	*/
	static BOOL WINAPI GetDefaultCommConfig(__in LPCTSTR lpszName,__out LPCOMMCONFIG lpCC, __inout LPDWORD lpdwSize);

	/*
	设置设备的 默认配置信息

	返回值:
	成功 非0
	失败 0
	*/
	static	BOOL WINAPI SetDefaultCommConfig(__in  LPCTSTR lpszName,__in  LPCOMMCONFIG lpCC,__in  DWORD dwSize);

protected :
	
	HANDLE hSerialPort;
	

	/*
	初始化端口
	返回值:
	成功 非0
	失败 0
	*/
	int InitSerialPort();

	/*
	是否使用异步
	*/
	bool overLaped;

public :
	
	TCHAR PortName[MAX_PATH];

	DCB SerialPortConfig;

	const wchar_t * GetName();

	const wchar_t *GetDes();

	int GetType();

	bool ShowConfigWindow(HWND parent);

	bool Open();

	bool Close();

	SerialPort();

	~SerialPort();
	/*
	生成一个实例
	portNumber serialport 端口

	返回值:
	成功 非0
	失败 0
	*/
	SerialPort(int portNumber);

	/*
	生成一个实例
	portName serialport 端口名称

	返回值:
	成功 非0
	失败 0
	*/
	SerialPort(const TCHAR * portName);

	/*
	打开串口

	返回值:
	成功 非0
	失败 0
	*/
	int OpenFile(bool overLaped);

	/*
	暂停 数据读取，清空现有的输入缓存
	非0 成功
	0 失败
	*/
	int Pause();

	/*
	恢复数据读取

	返回值:
	成功 非0
	失败 0
	*/
	int Resume();

	/*
	关闭串口

	返回值:
	成功 非0
	失败 0
	*/
	int CloseFile();

	/*
	读取数据

	返回值:
	成功 非0
	失败 0
	*/
	BOOL WINAPI ReadFile(__out LPVOID lpBuffer, __in  DWORD nNumberOfBytesToRead,__out_opt LPDWORD lpNumberOfBytesRead,__inout_opt  LPOVERLAPPED lpOverlapped);

	/*
	读取数据，
	使用指定超时时间与帧字节间隔进行读取
	*/
	int ReadData(void * lpBuffer,int len);

	/*
	写入数据

	返回值:
	成功 非0
	失败 0
	*/
	BOOL WINAPI WriteFile(__in LPCVOID lpBuffer, __in DWORD nNumberOfBytesToWrite,__out_opt LPDWORD lpNumberOfBytesWritten, __inout_opt LPOVERLAPPED lpOverlapped);

	/*
	写入数据
	*/
	int WriteData(void *lpBuffer,int off, int len);

	/*
	重置设备传输状态，并且线路设置成 nobreak 状态
	返回值:
	成功 非0
	失败 0
	*/
	BOOL WINAPI ClearCommBreak();

	/*
	清空设备错误状态
	lpErrors 用来接收错误的代码
	lpStat 用来接收 设备状态,如果为空则不接收

	返回值:
	成功 非0
	失败 0
	*/
	BOOL WINAPI ClearCommError( __out_opt  LPDWORD lpErrors, __out_opt  LPCOMSTAT lpStat);

	/*
	获取设备的配置信息
	lpCC 接收设备配置信息
	lpdwSize lpCC的大小

	返回值:
	成功 非0
	失败 0
	*/
	BOOL WINAPI GetCommConfig( __out LPCOMMCONFIG lpCC,__inout  LPDWORD lpdwSize);

	/*
	获取事件的掩码值
	lpEvtMask 用来接收事件的掩码值

	返回值:
	成功 非0
	失败 0
	*/
	BOOL WINAPI GetCommMask( __out  LPDWORD lpEvtMask);

	/*
	获取设备的状态

	返回值:
	成功 非0
	失败 0
	*/
	BOOL WINAPI GetCommModemStatus(__out  LPDWORD lpModemStat);

	/*
	获取设备的属性

	返回值:
	成功 非0
	失败 0
	*/
	BOOL WINAPI GetCommProperties(__out  LPCOMMPROP lpCommProp);

	/*
	获取设备的 超时时间

	返回值:
	成功 非0
	失败 0
	*/
	BOOL WINAPI GetCommTimeouts(__out  LPCOMMTIMEOUTS lpCommTimeouts);

	BOOL WINAPI GetCommState(__out LPDCB lpDCB); 
	/*
	清空设备中的输入，输出缓冲区，取消正在执行输入，输出

	返回值:
	成功 非0
	失败 0
	*/
	BOOL WINAPI PurgeComm( __in  DWORD dwFlags);

	/*
	挂起设备，不执行数据传输，将线程设置成 break 状态，至到 调用 ClearCommBreak 方法

	返回值:
	成功 非0
	失败 0
	*/
	BOOL WINAPI SetCommBreak();

	/*
	设置设备当前的配置信息

	返回值:
	成功 非0
	失败 0
	*/
	BOOL WINAPI SetCommConfig(__in  LPCOMMCONFIG lpCC, __in  DWORD dwSize);

	/*
	设置设置当前要触发事件类型

	返回值:
	成功 非0
	失败 0
	*/
	BOOL WINAPI SetCommMask(__in  DWORD dwEvtMask);

	/*
	设置设备当前的 状态

	返回值:
	成功 非0
	失败 0
	*/
	BOOL WINAPI SetCommState(__in  LPDCB lpDCB);

	/*
	设置设置的超时时间

	返回值:
	成功 非0
	失败 0
	*/
	BOOL WINAPI SetCommTimeouts(__in  LPCOMMTIMEOUTS lpCommTimeouts);

	/*
	设置 设备的输入与输出缓冲区大小 

	返回值:
	成功 非0
	失败 0
	*/
	BOOL WINAPI SetupComm(__in  DWORD dwInQueue,__in  DWORD dwOutQueue);

	/*
	将一个 字符插入到输出缓冲区首部

	返回值:
	成功 非0
	失败 0
	*/
	BOOL WINAPI TransmitCommChar(__in  char cChar);

	/*
	等待一个特定事件的发生

	返回值:
	成功 非0
	失败 0
	*/
	BOOL WINAPI WaitCommEvent( __out  LPDWORD lpEvtMask, __in   LPOVERLAPPED lpOverlapped);
};
INT_PTR CALLBACK CONFIGPROC(HWND,UINT,WPARAM,LPARAM);

#endif