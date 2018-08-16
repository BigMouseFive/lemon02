#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#include <time.h>
#pragma comment(lib, "WS2_32.lib")
DWORD GetTimeFromServer(char *ip_addr)
{
	// ����ip_addr:��ʾָ����ʱ�������IP��ַ
	// ���أ���1900��1��1����0ʱ0��0������ĺ����� �� 0����ʾ��ȡʧ�ܣ�
	// Ĭ�ϵ�ʱ�������Ϊ"������ʱ����"
	// ����WSADATA�ṹ�����
	WSADATA date;
	WORD w = MAKEWORD(2, 0);// ����汾����
	if (::WSAStartup(w, &date) != 0)// ��ʼ���׽��ֿ�
		return 0;
	SOCKET s;// ���������׽��־��
	DWORD  m_serverTime;// ���������Ϣ�������
	s = ::socket(AF_INET, SOCK_STREAM, 0);// ����TCP�׽���
	if (INVALID_SOCKET == s)
	{
		::closesocket(s);// �ر��׽��־��
		::WSACleanup();// �ͷ��׽��ֿ�
		return 0;
	}
	sockaddr_in addr;// �����׽��ֵ�ַ�ṹ
	addr.sin_family = AF_INET;// ��ʼ����ַ�ṹ
	addr.sin_port = htons(37);
	addr.sin_addr.S_un.S_addr = inet_addr(ip_addr);
	if (::connect(s, (sockaddr*)&addr, sizeof(addr)) != 0)// ����
	{
		::closesocket(s);// �ر��׽��־��
		::WSACleanup();// �ͷ��׽��ֿ�
		return 0;
	}
	if (::recv(s, (char *)&m_serverTime, 4, MSG_PEEK) <= 0)// ����
	{
		::closesocket(s);// �ر��׽��־��
		::WSACleanup();// �ͷ��׽��ֿ�
		return 0;
	}

	::closesocket(s);// �ر��׽��־��
	::WSACleanup();// �ͷ��׽��ֿ�
	m_serverTime = ::ntohl(m_serverTime);// �����ֽ�˳��ת��Ϊ�����ֽ�˳��
	return m_serverTime;
}
DWORD GetTimeFromSystem(){
	time_t t = time(nullptr);
	DWORD nowTime = 0;
	nowTime = t + 2208988800;
	return nowTime;
}
DWORD GetTime(){
	char a[20][20];
	DWORD time;
	strcpy(a[0], "129.6.15.29");
	strcpy(a[1], "128.138.140.44");
	strcpy(a[2], "129.6.15.28");
	strcpy(a[3], "210.72.145.8");
	for (int i = 3; i >= 0; --i){
		time = GetTimeFromServer(a[i]);
		if (time != 0) return time;
	}
	time = GetTimeFromSystem();
	return time;
}

SYSTEMTIME FormatServerTime(DWORD serverTime = 0)
{
	FILETIME      ftNew;
	SYSTEMTIME    stNew;

	stNew.wYear = 1900;
	stNew.wMonth = 1;
	stNew.wDay = 1;
	stNew.wHour = 0;
	stNew.wMinute = 0;
	stNew.wSecond = 0;
	stNew.wMilliseconds = 0;
	::SystemTimeToFileTime(&stNew, &ftNew);

	/*  ��SYSTEMTIME�ṹ�趨Ϊ1900��1��1����ҹ��0ʱ����
	�������SYSTEMTIME�ṹ���ݸ�SystemTimeToFileTime�����˽ṹת��ΪFILETIME�ṹ��
	FILETIMEʵ����ֻ��������32λԪ��DWORDһ�����64λԪ��������
	������ʾ��1601��1��1��������Ϊ100���루nanosecond���ļ������ */

	LARGE_INTEGER li;			//64λ������
	li = *(LARGE_INTEGER *)&ftNew;
	if (serverTime == 0)
		serverTime = GetTime();
	li.QuadPart += (LONGLONG)10000000 * serverTime;
	ftNew = *(FILETIME *)&li;
	::FileTimeToSystemTime(&ftNew, &stNew);

	// ����ʱ�䣨ע�⣺���ﷵ�ص��Ǹ�������ʱ�䣬�뱱��ʱ�����8Сʱ��
	return stNew;
}

bool firstflag = true;
int CompareTime(DWORD endtime){
	DWORD nowtime = GetTime();
	if (nowtime == 0){
		return 300;
	}
	else{
		DWORD difftime;
		if (endtime <= nowtime){
			difftime = nowtime - endtime;
			difftime = difftime / 3600;
			if (difftime >= 48)
				return 302;
			if (firstflag) return difftime;
			else if (difftime == 12)
				return difftime;
			else if (difftime == 24)
				return difftime;
			else if (difftime == 36)
				return difftime;
		}
		return 301;
	}
}