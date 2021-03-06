﻿// lemon02.cpp : 定义控制台应用程序的入口点。
//
#define  _CRT_SECURE_NO_WARNINGS
#include "utils.h"
#include "MacAddress.h"
#include "stdafx.h"
#include <direct.h>
#include <windows.h> 
#include <cstdio>
#include "utn.h"  
#include <iostream>
#include <fstream>
#include <string>
//#include "Python.h"

using namespace std;


//class PyThreadStateLock
//{
//public:
//	PyThreadStateLock(void)
//	{
//		state = PyGILState_Ensure();
//	}
//	~PyThreadStateLock(void)
//	{
//		PyGILState_Release(state);
//	}
//private:
//	PyGILState_STATE state;
//};

char account[200];
char password[200];
char currentDir[200];
char input[200];
char filepath[200];
char execdir[200];
char icoPath[200];
char macaddress[100];
float percent = 0;
float lowwer = 0;
int show[20];
int hide[32];
int _hide[32];
int decode[32];
char endTime[20];
DWORD endtime;
int total;
int lastret;
int maxtimes;
float maxtprice;
int mode;
int minute;

//PyObject* StringToPy(std::string p_obj)
//{
//	int wlen = ::MultiByteToWideChar(CP_ACP, NULL, p_obj.c_str(), int(p_obj.size()), NULL, 0);
//	wchar_t* wszString = new wchar_t[wlen + 1];
//	::MultiByteToWideChar(CP_ACP, NULL, p_obj.c_str(), int(p_obj.size()), wszString, wlen);
//	wszString[wlen] = '\0';
//	PyObject* pb = PyUnicode_FromUnicode((const Py_UNICODE*)wszString, wlen);
//	delete []wszString;
//	return pb;
//}
/***
123456789ABC
ABCDEFGHIJKL

0 :	H*2+D	10: L*5
1 :	D*8		11: B*4+C
2 :	D*3+B	12: C*6
3 :	J+7		13: I*5+E
4 :	F+6		14: B*3
5 :	E*4		15: E+8+K
6 :	F+8+G	16: K*2
7 :	A*4		17: I*6
8 :	K*4+I	18: J*3+A
9 :	G*7		19: H*8

0 :	G*2+I	10: L+5		20:	A*C+D	30: H*L+D
1 :	D+8		11: F*4+H	21:	B*D+F	31: H*G+F
2 :	L*3+C	12: C+6		22: I*J+H
3 :	J*7		13: L+5+F	23: C*K+E
4 :	F*6		14: B+3		24: D*E+G
5 :	E+4		15: B+8+C	25: A*K+L
6 :	K+8+J	16: K+2		26: J*D+I
7 :	A+4		17: I+6		27: G*F+A
8 :	D*4+E	18: D*3+A	28: F*K+C
9 :	G+7		19: H+8		29: G*J+B


***/
void ab(std::string& str, int day, int total){
	int i = 0;
	DWORD seconds = day * 3600 * 24;
	DWORD nowtime = GetTime();
	endtime = nowtime + seconds - 1996111725;
	memset(endTime, 0, sizeof(endTime));
	for (i = 9; i >= 0; --i){
		int part = endtime % 10;
		endTime[i] = part;
		endtime /= 10;
	}
	endTime[10] = total / 10;
	endTime[11] = total % 10;

	int tmp = 0;
	i = 0;
	for (auto it : str){
		if (it >= '0' && it <= '9')	tmp = it - '0';
		else if (it >= 'A' && it <= 'Z') tmp = it - 'A' + 10;
		decode[i] = tmp;
		i++;
	}
	decode[1] = decode[1] - 9;
	decode[3] = decode[3] - 4;
	decode[4] = decode[4] - 4;
	decode[5] = decode[5] / 2;
	decode[7] = decode[7] - 5;
	decode[9] = decode[9] - 13;
	decode[10] = decode[10] - 1;
	decode[12] = decode[12] - 4;
	decode[14] = decode[14] - 6;
	decode[16] = decode[16] - 3;
	decode[19] = decode[19] / 2;

	decode[0] = decode[19] * 2 + decode[1];
	decode[2] = decode[1] * 3 + decode[12];
	decode[6] = decode[16] + 8 + decode[3];
	decode[8] = decode[1] * 4 + decode[5];
	decode[11] = decode[4] * 4 + decode[19];
	decode[13] = decode[10] + 5 + decode[4];
	decode[15] = decode[14] + 8 + decode[12];
	decode[18] = decode[1] * 3 + decode[7];
	decode[20] = decode[7] * decode[12] + decode[1];
	decode[21] = decode[14] * decode[1] + decode[4];
	decode[22] = decode[17] * decode[3] + decode[19];
	decode[23] = decode[12] * decode[16] + decode[5];
	decode[24] = decode[1] * decode[5] + decode[9];
	decode[25] = decode[7] * decode[16] + decode[10];
	decode[26] = decode[3] * decode[1] + decode[17];
	decode[27] = decode[9] * decode[4] + decode[7];
	decode[28] = decode[4] * decode[16] + decode[12];
	decode[29] = decode[9] * decode[3] + decode[14];
	decode[30] = decode[19] * decode[10] + decode[1];
	decode[31] = decode[19] * decode[9] + decode[4];

	decode[7] += 4; decode[14] += 3; decode[12] += 6;
	decode[1] += 8; decode[5] += 4; decode[4] *= 6;
	decode[9] += 7; decode[19] += 8; decode[17] += 6;
	decode[3] *= 7; decode[16] += 2; decode[10] += 5;

	decode[2] = endTime[4] * 3;
	decode[0] = endTime[5] * 2 + 3;
	decode[31] = endTime[6];
	decode[26] = endTime[7] * 2 + 4;
	decode[25] = endTime[1] * 2 + endTime[7];
	decode[15] = endTime[8] + 4;
	decode[20] = endTime[3] * 2 + endTime[8];
	decode[28] = endTime[9] + 7;
	decode[23] = endTime[2] + endTime[9];
	decode[11] = endTime[10] + endTime[5];
	decode[6] = endTime[11] * 2 + 2;
	decode[29] = endTime[0] + endTime[3] + endTime[11];

	decode[1] += endTime[5];
	decode[3] += endTime[6];
	decode[4] += endTime[7];
	decode[5] += endTime[8];
	decode[7] += endTime[9];
	decode[8] += endTime[6];
	decode[9] += endTime[7];
	decode[10] += endTime[8];
	decode[12] += endTime[8];
	decode[13] += endTime[5];
	decode[14] += endTime[7];
	decode[16] += endTime[9];
	decode[17] += endTime[7];
	decode[18] += endTime[6];
	decode[19] += endTime[6];
	decode[21] += endTime[5];
	decode[22] += endTime[8];
	decode[24] += endTime[9];
	decode[27] += endTime[7];
	decode[30] += endTime[5];


	for (i = 0; i < 32; ++i)
		decode[i] %= 36;
	str.clear();
	char c;
	for (i = 0; i < 32; ++i){
		if (decode[i] >= 0 && decode[i] <= 9) c = '0' + decode[i];
		else c = 'A' + decode[i] - 10;
		str.push_back(c);
	}
}
void aabb(int i){
	printf("\n%d----------对不起，数据有误-----------%d\n", i, i);
	system("PAUSE");
	exit(0);
}
int aaaab(){
	std::vector<std::string> vtMacAddress;

	CTemporary temporary;
	temporary.GetMacAddress(vtMacAddress);
	memset(macaddress, 0, sizeof(macaddress));
	int i = 0;
	int tmp = 0;
	for (auto it : vtMacAddress[0]){
		i++;
		if (it >= '0' && it <= '9')	tmp = it - '0';
		else if (it >= 'A' && it <= 'Z') tmp = it - 'A' + 10;
		tmp++;
		switch (i){
		case 1:  show[7] = tmp; hide[7] = tmp; break;//A
		case 2:  show[14] = tmp; hide[14] = tmp; break;//B
		case 3:  show[12] = tmp; hide[12] = tmp; break;//C
		case 4:  show[1] = tmp; hide[1] = tmp; break;//D
		case 5:  show[5] = tmp; hide[5] = tmp; break;//E
		case 6:  show[4] = tmp; hide[4] = tmp; break;//F
		case 7:  show[9] = tmp; hide[9] = tmp; break;//G
		case 8:  show[19] = tmp; hide[19] = tmp; break;//H
		case 9:  show[17] = tmp; hide[17] = tmp; break;//I
		case 10: show[3] = tmp; hide[3] = tmp; break;//J
		case 11: show[16] = tmp; hide[16] = tmp; break;//K
		case 12: show[10] = tmp; hide[10] = tmp; break;//L
		}
	}
	show[0] = show[9] * 2 + show[17];
	show[2] = show[10]  * 3 + show[12];
	show[6] = show[4] + 8 + show[9];
	show[8] = show[16] * 4 + show[17];
	show[11] = show[14] * 4 + show[12];
	show[13] = show[17] * 5 + show[5];
	show[15] = show[5] + 8 + show[16];
	show[18] = show[3] * 3 + show[7];
	
	hide[0] = hide[19] * 2 + hide[1];
	hide[2] = hide[1] * 3 + hide[12];
	hide[6] = hide[16] + 8 + hide[3];
	hide[8] = hide[1] * 4 + hide[5];
	hide[11] = hide[4] * 4 + hide[19];
	hide[13] = hide[10] + 5 + hide[4];
	hide[15] = hide[14] + 8 + hide[12];
	hide[18] = hide[1] * 3 + hide[7];
	hide[20] = hide[7] * hide[12] + hide[1];
	hide[21] = hide[14] * hide[1] + hide[4];
	hide[22] = hide[17] * hide[3] + hide[19];
	hide[23] = hide[12] * hide[16] + hide[5];
	hide[24] = hide[1] * hide[5] + hide[9];
	hide[25] = hide[7] * hide[16] + hide[10];
	hide[26] = hide[3] * hide[1] + hide[17];
	hide[27] = hide[9] * hide[4] + hide[7];
	hide[28] = hide[4] * hide[16] + hide[12];
	hide[29] = hide[9] * hide[3] + hide[14];
	hide[30] = hide[19] * hide[10] + hide[1];
	hide[31] = hide[19] * hide[9] + hide[4];

	hide[7] += 4; hide[14] += 3; hide[12] += 6;
	hide[1] += 8; hide[5] += 4; hide[4] *= 6;
	hide[9] += 7; hide[19] += 8; hide[17] += 6;
	hide[3] *= 7; hide[16] += 2; hide[10] += 5;
	for (i = 0; i < 20; ++i)
		show[i] %= 16;
	for (i = 0; i < 32; ++i)
		_hide[i] = hide[i];

	//读取文件currentdir\\DNCAT\\ulfkeileaif.dat
	fstream file;
	memset(input, 0, sizeof(input));
	memset(filepath, 0, sizeof(filepath));
	strcat(filepath, currentDir);
	strcat(filepath, "/DNCAT");
	strcat(filepath, "/ulfkeileaif.pyc");
	locale loc = locale::global(locale(""));
	file.open(filepath, ios::in);
	bool fileExist = false;
	if (file){
		fileExist = true;
		file.read(input, sizeof(input));
		string input_tmp(input);
		auto iter = input_tmp.begin();
		for (; iter != input_tmp.end();)
		{
			if (*iter == ' ' || *iter == '-')
				iter = input_tmp.erase(iter);
			else{
				if (*iter >= 'a' && *iter <= 'z')
					*iter = *iter - ('a' - 'A');
				iter++;
			}
		}
		memset(input, 0, sizeof(input));
		strncpy(input, input_tmp.c_str(), sizeof(input));
		if (strlen(input) == 32){

			int tmp = 0;
			for (int i = 0; i < 32; i++){

				if (input[i] >= '0' && input[i] <= '9')	input[i] = input[i] - '0';
				else if (input[i] >= 'A' && input[i] <= 'Z') input[i] = input[i] - 'A' + 10;
			}
			{
				memset(endTime, 0, sizeof(endTime));
				endTime[4] = input[2] / 3;
				endTime[5] = (input[0] - 3) / 2;
				endTime[6] = input[31];
				endTime[7] = (input[26] - 4) / 2;
				endTime[1] = (input[25] - endTime[7]) / 2;
				endTime[8] = input[15] - 4;
				endTime[3] = (input[20] - endTime[8]) / 2;
				endTime[9] = input[28] - 7;
				endTime[2] = input[23] - endTime[9];
				endTime[10] = input[11] - endTime[5];
				endTime[11] = (input[6] - 2) / 2;
				endTime[0] = input[29] - endTime[3] - endTime[11];
				endtime = 0;
				for (int j = 0; j <= 9; ++j){
					endtime = endtime * 10 + endTime[j];
				}
				endtime = endtime + 1996111725;
				total = 0;
				for (int j = 10; j <= 11; ++j){
					total = total * 10 + endTime[j];
				}
				hide[2] = input[2];
				hide[0] = input[0];
				hide[31] = input[31];
				hide[26] = input[26];
				hide[25] = input[25];
				hide[15] = input[15];
				hide[20] = input[20];
				hide[28] = input[28];
				hide[23] = input[23];
				hide[11] = input[11];
				hide[6] = input[6];
				hide[29] = input[29];
				hide[1] = _hide[1] + endTime[5];
				hide[3] = _hide[3] + endTime[6];
				hide[4] = _hide[4] + endTime[7];
				hide[5] = _hide[5] + endTime[8];
				hide[7] = _hide[7] + endTime[9];
				hide[8] = _hide[8] + endTime[6];
				hide[9] = _hide[9] + endTime[7];
				hide[10] = _hide[10] + endTime[8];
				hide[12] = _hide[12] + endTime[8];
				hide[13] = _hide[13] + endTime[5];
				hide[14] = _hide[14] + endTime[7];
				hide[16] = _hide[16] + endTime[9];
				hide[17] = _hide[17] + endTime[7];
				hide[18] = _hide[18] + endTime[6];
				hide[19] = _hide[19] + endTime[6];
				hide[21] = _hide[21] + endTime[5];
				hide[22] = _hide[22] + endTime[8];
				hide[24] = _hide[24] + endTime[9];
				hide[27] = _hide[27] + endTime[7];
				hide[30] = _hide[30] + endTime[5];
				for (int i = 0; i < 32; ++i)
					hide[i] %= 36;
			}
			{
				for (int i = 0; i < 32; i++){
					if (input[i] != hide[i]){
						file.close();
						fileExist = false;
						aabb(12);
					}
				}
			}
			int ret = ::CompareTime(endtime);
			if (ret == 300 || ret == 302) aabb(13);
		}
		else{
			file.close();
			aabb(14);
		}
	}
	locale::global(loc);
	return 0;
}
int aaabb(char **argv){
	memset(account, 0, sizeof(account));
	memset(password, 0, sizeof(password));
	memset(currentDir, 0, sizeof(currentDir));
	memset(execdir, 0, sizeof(execdir));
	
	char* tmp0 = argv[1];
	memcpy(account, tmp0, strlen(tmp0));
	char* tmp1 = argv[2];
	percent = std::stof(string(argv[3]));
	lowwer = std::stof(string(argv[4]));
	maxtimes = std::stoi(string(argv[5]));
	maxtprice = std::stof(string(argv[6]));
	mode = std::stoi(string(argv[7]));
	minute = std::stoi(string(argv[8]));
	memcpy(password, tmp1, strlen(tmp1));
	char* tmp2 = "sys.path.append('";
	memcpy(execdir, tmp2, strlen(tmp2));

	GetModuleFileNameA(NULL, currentDir, 200);
	int i = 0;
	int j = 0;
	while(currentDir[i] != '\0'){
		if (currentDir[i] == '\\'){
			currentDir[i] = '/';
			j = i;
		}
		i++;
	}
	currentDir[j] = '\0';

	strncat(execdir, currentDir, strlen(currentDir));
	strncat(execdir, "/DNCAT", 6);
	strncat(execdir, "')", 2);

	return 0;
}
void aaaabb(){
	memset(icoPath, 0, sizeof(icoPath));
	strncat(icoPath, currentDir, strlen(currentDir));
	strncat(icoPath, "/DNCAT/title.ico", 16);
	HANDLE handle;
	HICON hIcon;
	SetConsoleTitleA("adksjflaksjdflaksdjflaksjdflkasjdflkasjflkajsdflkasjf");
	handle = FindWindowA("ConsoleWindowClass", "adksjflaksjdflaksdjflaksjdflkasjdflkasjflkajsdflkasjf");
	hIcon = (HICON)LoadImageA(NULL, icoPath, IMAGE_ICON, 0, 0, LR_LOADFROMFILE);
	SendMessage((HWND)handle, WM_SETICON, (WPARAM)ICON_BIG, (LPARAM)hIcon);
	SendMessage((HWND)handle, WM_SETICON, (WPARAM)ICON_SMALL, (LPARAM)hIcon);
	SetConsoleTitleA(account);
	system("color 3f");
}
void aaaabbb(){

}
void aaabbb(){
	//try{
	//	Py_Initialize();
	//	if (!Py_IsInitialized()){
	//		printf("错误1\n");
	//		return;
	//	}
	//	std::string a;
	//	a.reserve();
	//	PyObject * pModule = NULL;
	//	PyObject * pFunc = NULL;
	//	PyObject * pRet = NULL;
	//	PyRun_SimpleString("import sys");
	//	PyRun_SimpleString(AsciiToUtf8(execdir).c_str());
	//	PyObject* pyArgv = PyTuple_New(8);
	//	PyObject* pArg1 = Py_BuildValue("s", account);
	//	PyObject* pArg2 = Py_BuildValue("s", password);
	//	PyObject* pArg3 = StringToPy(currentDir);
	//	PyObject* pArg4 = Py_BuildValue("f", percent);
	//	PyObject* pArg5 = Py_BuildValue("f", lowwer);
	//	PyObject* pArg6 = Py_BuildValue("i", maxtimes);
	//	PyObject* pArg7 = Py_BuildValue("f", maxtprice);
	//	PyObject* pArg8 = Py_BuildValue("i", minute);

	//	PyTuple_SetItem(pyArgv, 0, pArg1);
	//	PyTuple_SetItem(pyArgv, 1, pArg2);
	//	PyTuple_SetItem(pyArgv, 2, pArg3);
	//	PyTuple_SetItem(pyArgv, 3, pArg4);
	//	PyTuple_SetItem(pyArgv, 4, pArg5);
	//	PyTuple_SetItem(pyArgv, 5, pArg6);
	//	PyTuple_SetItem(pyArgv, 6, pArg7);
	//	PyTuple_SetItem(pyArgv, 7, pArg8);
	//	if (mode == 0)
	//		pModule = PyImport_ImportModule("skrintreenode"); //修改所有的产品。获取相同ean的所有产品的价格，取其中最低价（除去自己的价格）
	//	else if (mode == 1)
	//		pModule = PyImport_ImportModule("pointcetpets");  //修改所有的产品。如果有更低价，则取更低的价格为最低价；否则以自己的价格作为最低价
	//	else if (mode == 2)
	//		pModule = PyImport_ImportModule("teenlifeeasy");  //只修改有更低价的产品。以更低价为最低价
	//	else if (mode == 3)
	//		pModule = PyImport_ImportModule("carrymapstory"); //只修改没有更低价的产品。以自己的价格作为最低价

	//	if (pModule == nullptr){
	//		printf("错误2\n");
	//		return;
	//	}
	//	pFunc = PyObject_GetAttrString(pModule, "skr");
	//	if (pFunc == nullptr){
	//		printf("错误3\n");
	//		return;
	//	}
	//	PyEval_CallObject(pFunc, pyArgv);
	//	Py_Finalize();
	//}
	//catch(...){
	//	printf("错误4\n");
	//}
}
//Administrator
// C:\Users\Administrator\AppData\Local\Google\Chrome\User Data
// 1 :GDND409AIE7D9Y894EWS DH90584GPDF5FGA8APQVKD0G8JEAEAL9 +
// 2 :7DQ640MA3R8D938E9FBA DH9N584IPQG5FHA8HQQMKD3INJEAGA89 +
// 3 :VD8D40NAHS2D958C71WS DH90594APRB5GBA97CQVLDSAGJEA8AN9 +
// 4 :RD8740HATM2D998D89ES DH9U594CPLB5GBA9AKQVLDACCJEAAAN9 +
// 5 :YD5740NA8SDD9K8944EC DH9U594EPRM5GMA98FQNLDNEKJEACA99 +
// 6 :SD8E40JAEOED9U8A56ZE DH97594GPNN5GNA9BHQOLD0GIJEAEAS9 +
// 7 :QDHB40KA6P5D9A8942QS DH9M594IPOE5GEA9CDQVLDXILJEAGAT9 +
// 8 :BDE640DAPIGD958E91BG DH9N5A4APHQ5HPAA9CQPMDGA6JEA8AL9 +
// 9 :BD5A409AHEDD998A59NK DH9F5A4CPDN5HMAA7KQRMDYC4JEAAAL9 +
// 10:5DEJ40NAZSGD9J8NIBEM DH965A4EPRQ5HPAAMMQSMD2EKJEACAU9 +
// 11:FDN640AAVF7D9J8D8BBK DH9N5A4GPEH5HGAAEMQRMD2G9JEAEAX9 +
// 12:NDZC40JA5OBD958941TQ DH9T5A4IPNL5HKAACCQUMDRIKJEAGAV9 +
// 13:FD2D40BATGCD998MH9WO DH905B4APFN5ILABHKQTNDSA4JEA8AX9 +
// 14:JDEJ40AABFGD938GBFEU DH965B4CPER5IPABDQQWNDVC5JEAAAI9 +
// 15:ODNH40FA6K7D9E8GBA86 DH9S5B4EPJI5IGABFLQKNDWECJEACAR9 + 
// 16:GDW840CAOHAD948C78HC DH915B4GPGL5IJABDJQNND9GBJEAEAR9 +
// za:IDTG40FAGK9D9K8KF45U DH9L5B4IPJK5IIABNFQWNDYIGJEAGAL9 +
// ba:JDK640BAHG6D9T8IDDBU DH9N5C4APFI5JFACDOQWODDA4JEA8AC9 +
// ne:4DT5408A8D9D9K894486 DH9G5C4CPCL5JIAC6FQKODFC3JEAAAX9 +


#define STRCAT(a, b) a##b

class base{
public:
	virtual int a() = 0;
	static int b(){
		printf("test\n");
		return 1;
	}
};

class base1 : public base{
	
};
class base2 : public base{
public:
	virtual int a(){
		printf("adsfsdf\n");
		return 1;
	}
	static int b1(){
		printf("test\n");
		return 1;
	}
};

// Admin
static jmp_buf env;
int main(int argc, char** argv)
{
#if 1
	string str;
	/*str = "GDND409AIE7D9Y894EWS"; ab(str, 356, 1); printf("%s\n", str.c_str());
	str = "7DQ640MA3R8D938E9FBA"; ab(str, 356, 1); printf("%s\n", str.c_str());
	str = "VD8D40NAHS2D958C71WS"; ab(str, 356, 1); printf("%s\n", str.c_str());
	str = "RD8740HATM2D998D89ES"; ab(str, 356, 1); printf("%s\n", str.c_str());
	str = "YD5740NA8SDD9K8944EC"; ab(str, 356, 1); printf("%s\n", str.c_str());
	str = "SD8E40JAEOED9U8A56ZE"; ab(str, 356, 1); printf("%s\n", str.c_str());
	str = "QDHB40KA6P5D9A8942QS"; ab(str, 356, 1); printf("%s\n", str.c_str());
	str = "BDE640DAPIGD958E91BG"; ab(str, 356, 1); printf("%s\n", str.c_str());
	str = "BD5A409AHEDD998A59NK"; ab(str, 356, 1); printf("%s\n", str.c_str());
	str = "5DEJ40NAZSGD9J8NIBEM"; ab(str, 356, 1); printf("%s\n", str.c_str());
	str = "FDN640AAVF7D9J8D8BBK"; ab(str, 356, 1); printf("%s\n", str.c_str());
	str = "NDZC40JA5OBD958941TQ"; ab(str, 356, 1); printf("%s\n", str.c_str());
	str = "FD2D40BATGCD998MH9WO"; ab(str, 356, 1); printf("%s\n", str.c_str());
	str = "JDEJ40AABFGD938GBFEU"; ab(str, 356, 1); printf("%s\n", str.c_str());
	str = "ODNH40FA6K7D9E8GBA86"; ab(str, 356, 1); printf("%s\n", str.c_str());
	str = "GDW840CAOHAD948C78HC"; ab(str, 356, 1); printf("%s\n", str.c_str());
	str = "IDTG40FAGK9D9K8KF45U"; ab(str, 356, 1); printf("%s\n", str.c_str());
	str = "JDK640BAHG6D9T8IDDBU"; ab(str, 356, 1); printf("%s\n", str.c_str());
	str = "4DT5408A8D9D9K894486"; ab(str, 356, 1); printf("%s\n", str.c_str());*///nancy 4/10
	//str = "9GZGG4N6JG9NFHIE7314"; ab(str, 30, 1); printf("%s\n", str.c_str());  //夏天  4/23
	//str = "EFE84A8DMD1EI36F5EKE"; ab(str, 30, 1); printf("%s\n", str.c_str());  //夏天  4/26
	//str = "FA0GHAS6HK8JJA7QG11I"; ab(str, 185, 1); printf("%s\n", str.c_str()); tina 本地电脑  已经删除
	//str = "UE9G52LB2P2IAV9HB668"; ab(str, 185, 1); printf("%s\n", str.c_str());
	//str = "LE3K52HBTLCIAQ9OI5IG"; ab(str, 185, 1); printf("%s\n", str.c_str());
	//str = "4ES6IA0JWR6DHT6I8CKU"; ab(str, 170, 1); printf("%s\n", str.c_str());
	//str = "FGLHBGJHVHGWG7BM97F2"; ab(str, 31, 1); printf("%s\n", str.c_str());
	//str = "AERD52CBSG8IAL9F94XO"; ab(str, 335, 1); printf("%s\n", str.c_str());
	str = "VL6BBCRIRPC5D5EJ87YA"; ab(str, 93, 1); printf("%s\n", str.c_str());
	str = "QEAIIATJWKCDHT6RHCKG"; ab(str, 93, 1); printf("%s\n", str.c_str());
	str = "RBF5A4R5TQ3PD7AHA136"; ab(str, 93, 1); printf("%s\n", str.c_str());
	
	system("PAUSE");
	return 0;
#else
	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
	DWORD mode;
	GetConsoleMode(hStdin, &mode);
	mode &= ~ENABLE_QUICK_EDIT_MODE;  //移除快速编辑模式
	mode &= ~ENABLE_INSERT_MODE;      //移除插入模式
	mode &= ~ENABLE_MOUSE_INPUT;
	SetConsoleMode(hStdin, mode);
	if (argc != 9)
		exit(0);
	aaabb(argv);
	aaaab();
	aaaabb();
	aaaabbb();
	aaabbb();
	system("PAUSE");
	return 0;
#endif
}

