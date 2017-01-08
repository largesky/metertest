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
	��ע����л�ȡ���е� ����
	**/
	static std::vector<const wchar_t *> *GetSerialPorts();

	/*
	ʹ��ָ�����ַ���� DCB�ṹ
	lpDef �ַ��� : COM x[:][baud= b][parity= p][data= d][stop= s][to={on|off}][xon={on|off}][odsr={on|off}][octs={on|off}][dtr={on|off|hs}][rts={on|off|hs|tg}][idsr={on|off}] 
	����һ���Ϸ��ĸ�ʽ: baud=1200 parity=N data=8 stop=1
	lpDCBָ��һ�� DCB�ṹ

	����ֵ:
	�ɹ� ��0
	ʧ�� 0
	*/

	static BOOL WINAPI BuildCommDCB( __in LPCTSTR lpDef,__out  LPDCB lpDCB);

	/*
	��ȡ�豸�� Ĭ������ֵ

	����ֵ:
	�ɹ� ��0
	ʧ�� 0
	*/
	static BOOL WINAPI GetDefaultCommConfig(__in LPCTSTR lpszName,__out LPCOMMCONFIG lpCC, __inout LPDWORD lpdwSize);

	/*
	�����豸�� Ĭ��������Ϣ

	����ֵ:
	�ɹ� ��0
	ʧ�� 0
	*/
	static	BOOL WINAPI SetDefaultCommConfig(__in  LPCTSTR lpszName,__in  LPCOMMCONFIG lpCC,__in  DWORD dwSize);

protected :
	
	HANDLE hSerialPort;
	

	/*
	��ʼ���˿�
	����ֵ:
	�ɹ� ��0
	ʧ�� 0
	*/
	int InitSerialPort();

	/*
	�Ƿ�ʹ���첽
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
	����һ��ʵ��
	portNumber serialport �˿�

	����ֵ:
	�ɹ� ��0
	ʧ�� 0
	*/
	SerialPort(int portNumber);

	/*
	����һ��ʵ��
	portName serialport �˿�����

	����ֵ:
	�ɹ� ��0
	ʧ�� 0
	*/
	SerialPort(const TCHAR * portName);

	/*
	�򿪴���

	����ֵ:
	�ɹ� ��0
	ʧ�� 0
	*/
	int OpenFile(bool overLaped);

	/*
	��ͣ ���ݶ�ȡ��������е����뻺��
	��0 �ɹ�
	0 ʧ��
	*/
	int Pause();

	/*
	�ָ����ݶ�ȡ

	����ֵ:
	�ɹ� ��0
	ʧ�� 0
	*/
	int Resume();

	/*
	�رմ���

	����ֵ:
	�ɹ� ��0
	ʧ�� 0
	*/
	int CloseFile();

	/*
	��ȡ����

	����ֵ:
	�ɹ� ��0
	ʧ�� 0
	*/
	BOOL WINAPI ReadFile(__out LPVOID lpBuffer, __in  DWORD nNumberOfBytesToRead,__out_opt LPDWORD lpNumberOfBytesRead,__inout_opt  LPOVERLAPPED lpOverlapped);

	/*
	��ȡ���ݣ�
	ʹ��ָ����ʱʱ����֡�ֽڼ�����ж�ȡ
	*/
	int ReadData(void * lpBuffer,int len);

	/*
	д������

	����ֵ:
	�ɹ� ��0
	ʧ�� 0
	*/
	BOOL WINAPI WriteFile(__in LPCVOID lpBuffer, __in DWORD nNumberOfBytesToWrite,__out_opt LPDWORD lpNumberOfBytesWritten, __inout_opt LPOVERLAPPED lpOverlapped);

	/*
	д������
	*/
	int WriteData(void *lpBuffer,int off, int len);

	/*
	�����豸����״̬��������·���ó� nobreak ״̬
	����ֵ:
	�ɹ� ��0
	ʧ�� 0
	*/
	BOOL WINAPI ClearCommBreak();

	/*
	����豸����״̬
	lpErrors �������մ���Ĵ���
	lpStat �������� �豸״̬,���Ϊ���򲻽���

	����ֵ:
	�ɹ� ��0
	ʧ�� 0
	*/
	BOOL WINAPI ClearCommError( __out_opt  LPDWORD lpErrors, __out_opt  LPCOMSTAT lpStat);

	/*
	��ȡ�豸��������Ϣ
	lpCC �����豸������Ϣ
	lpdwSize lpCC�Ĵ�С

	����ֵ:
	�ɹ� ��0
	ʧ�� 0
	*/
	BOOL WINAPI GetCommConfig( __out LPCOMMCONFIG lpCC,__inout  LPDWORD lpdwSize);

	/*
	��ȡ�¼�������ֵ
	lpEvtMask ���������¼�������ֵ

	����ֵ:
	�ɹ� ��0
	ʧ�� 0
	*/
	BOOL WINAPI GetCommMask( __out  LPDWORD lpEvtMask);

	/*
	��ȡ�豸��״̬

	����ֵ:
	�ɹ� ��0
	ʧ�� 0
	*/
	BOOL WINAPI GetCommModemStatus(__out  LPDWORD lpModemStat);

	/*
	��ȡ�豸������

	����ֵ:
	�ɹ� ��0
	ʧ�� 0
	*/
	BOOL WINAPI GetCommProperties(__out  LPCOMMPROP lpCommProp);

	/*
	��ȡ�豸�� ��ʱʱ��

	����ֵ:
	�ɹ� ��0
	ʧ�� 0
	*/
	BOOL WINAPI GetCommTimeouts(__out  LPCOMMTIMEOUTS lpCommTimeouts);

	BOOL WINAPI GetCommState(__out LPDCB lpDCB); 
	/*
	����豸�е����룬�����������ȡ������ִ�����룬���

	����ֵ:
	�ɹ� ��0
	ʧ�� 0
	*/
	BOOL WINAPI PurgeComm( __in  DWORD dwFlags);

	/*
	�����豸����ִ�����ݴ��䣬���߳����ó� break ״̬������ ���� ClearCommBreak ����

	����ֵ:
	�ɹ� ��0
	ʧ�� 0
	*/
	BOOL WINAPI SetCommBreak();

	/*
	�����豸��ǰ��������Ϣ

	����ֵ:
	�ɹ� ��0
	ʧ�� 0
	*/
	BOOL WINAPI SetCommConfig(__in  LPCOMMCONFIG lpCC, __in  DWORD dwSize);

	/*
	�������õ�ǰҪ�����¼�����

	����ֵ:
	�ɹ� ��0
	ʧ�� 0
	*/
	BOOL WINAPI SetCommMask(__in  DWORD dwEvtMask);

	/*
	�����豸��ǰ�� ״̬

	����ֵ:
	�ɹ� ��0
	ʧ�� 0
	*/
	BOOL WINAPI SetCommState(__in  LPDCB lpDCB);

	/*
	�������õĳ�ʱʱ��

	����ֵ:
	�ɹ� ��0
	ʧ�� 0
	*/
	BOOL WINAPI SetCommTimeouts(__in  LPCOMMTIMEOUTS lpCommTimeouts);

	/*
	���� �豸�������������������С 

	����ֵ:
	�ɹ� ��0
	ʧ�� 0
	*/
	BOOL WINAPI SetupComm(__in  DWORD dwInQueue,__in  DWORD dwOutQueue);

	/*
	��һ�� �ַ����뵽����������ײ�

	����ֵ:
	�ɹ� ��0
	ʧ�� 0
	*/
	BOOL WINAPI TransmitCommChar(__in  char cChar);

	/*
	�ȴ�һ���ض��¼��ķ���

	����ֵ:
	�ɹ� ��0
	ʧ�� 0
	*/
	BOOL WINAPI WaitCommEvent( __out  LPDWORD lpEvtMask, __in   LPOVERLAPPED lpOverlapped);
};
INT_PTR CALLBACK CONFIGPROC(HWND,UINT,WPARAM,LPARAM);

#endif