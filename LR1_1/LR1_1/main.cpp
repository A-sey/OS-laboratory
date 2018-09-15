// LR1_2.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "windows.h"
#include "iostream"
#include "conio.h"
#include "string"
#include "Lmcons.h"
#pragma warning(disable : 4996)
using namespace std;

void Prnt(string str, TCHAR* text, int length);
void Prnt(OSVERSIONINFOA ver);
void Prnt(string str, int num);
void Prnt(int size, int* num, int* old, int* mod);
int main()
{
	setlocale(LC_ALL, "rus");
	// ���������
	const DWORD pcName_length = MAX_COMPUTERNAME_LENGTH + 1;
	const DWORD userName_length = UNLEN + 1;
	const DWORD folder_length = 100;
	// ������ �����
	TCHAR pcName[pcName_length];
	TCHAR userName[userName_length];
	TCHAR sysFolder[folder_length];
	TCHAR winFolder[folder_length];
	TCHAR tempFolder[folder_length];
	// ���������, ���������� ���������� �� ��
	OSVERSIONINFOA version_info;
	version_info.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	// ���������� ��� ������
	int cursor_width;
	int cursor_height;
	int min_window_width;
	int min_window_height;
	// ���������� ��� ����������
	int keyboard_speed;
	int alt_tab;
	// �����
	int col[] = { COLOR_HIGHLIGHT, COLOR_INACTIVEBORDER, COLOR_ACTIVECAPTION };
	int size = sizeof(col) / sizeof(int);
	int* color;
	int* invert;
	color = new int[size];
	invert = new int[size];
	// �����
	int session_time;
	SYSTEMTIME sm;

	// ��������� ����������
	// ��� ����������
	GetComputerName(pcName, (LPDWORD)&pcName_length);
	Prnt("��� ����������: ", pcName, pcName_length);
	// ��� ������������
	GetUserName(userName, (LPDWORD)&userName_length);
	Prnt("��� ������������: ", userName, userName_length);
	// ����� ���������� ��������
	GetSystemDirectory(sysFolder, folder_length);
	Prnt("����� ���������� ��������: ", sysFolder, folder_length);
	// ����� �������� Windows
	GetWindowsDirectory(winFolder, folder_length);
	Prnt("����� �������� Windows: ", winFolder, folder_length);
	// ����� �������� ��������� ������
	GetTempPath(folder_length, tempFolder);
	Prnt("����� �������� ��������� ������: ", tempFolder, folder_length);
	// ���������� � ������ ��
	GetVersionEx((OSVERSIONINFO*)&version_info);
	Prnt(version_info);

	// ��������� �������
	// ������������ ������� �������
	cursor_width = GetSystemMetrics(SM_CXCURSOR);
	Prnt("������������ ������ �������, px: ", cursor_width);
	cursor_height = GetSystemMetrics(SM_CYCURSOR);
	Prnt("������������ ������ �������, px: ", cursor_height);
	// ����������� ������� ����
	min_window_width = GetSystemMetrics(SM_CXMIN);
	Prnt("����������� ������ ����, px: ", min_window_width);
	min_window_height = GetSystemMetrics(SM_CYMIN);
	Prnt("����������� ������ ����, px: ", min_window_height);

	// ��������� ���������
	// �������� ������ �������� ��� ������� �������
	SystemParametersInfo(SPI_GETKEYBOARDSPEED, 0, &keyboard_speed, 0);
	Prnt("�������� ������ �������� ��� ������� �������: ", keyboard_speed);
	// ������� �� ���������� Alt+Tab
	SystemParametersInfo(SPI_GETFASTTASKSWITCH, 0, &alt_tab, 0);
	Prnt("���������� ���������� Alt+Tab: ", alt_tab);

	// �����
	// �������� �����	
	for (int i = 0; i < size; i++)
		color[i] = GetSysColor(col[i]);
	// �������� ��
	for (int i = 0; i < size; i++)
		invert[i] = (color[i] >> 16 & 255) | ((color[i] >> 8 & 255) << 8) | ((color[i] & 255) << 16);
	// ��������� �����
	if (SetSysColors(1, col, (COLORREF*)invert))
		Prnt(size, col, color, invert);

	// ������ �� ��������
	// ����������������� ������:
	session_time = GetTickCount();
	// ���������� �� ���������� �������:
	GetSystemTime(&sm);
	Prnt("����������������� ������: ", session_time);
	Prnt("���: ", sm.wYear);
	Prnt("�����: ", sm.wMonth);
	Prnt("����: ", sm.wDay);
	Prnt("���: ", sm.wHour);
	Prnt("������: ", sm.wMinute);
	Prnt("�������: ", sm.wSecond);

	system("timeout -1");
	return 0;
}

// ����� ������������� ������
void Prnt(string str, TCHAR* text, int length)
{
	cout << str;
	for (int i = 0; i < length && text[i] != 0; i++)
		cout << (char)(text[i]);
	cout << "\n";
}

// ����� ���������� �� ��
void Prnt(OSVERSIONINFOA ver)
{
	cout << "�������� ����� ������: " << ver.dwMajorVersion << "\n";
	cout << "�������������� ����� ������: " << ver.dwMinorVersion << "\n";
	cout << "����� ������ ��: " << ver.dwBuildNumber << "\n";
	cout << "����� ���������: " << ver.dwPlatformId << "\n";
}

// ����� �������� ����������
void Prnt(string str, int num)
{
	cout << str << num << "\n";
}

// ����� �������� ����������
void Prnt(int size, int* num, int* old, int* mod)
{
	for (int i = 0; i < size; i++)
	{
		cout << "������ ���� " << num[i] << " ��������� � RGB: ";
		cout << (old[i] & 255) << ":" << (old[i] >> 8 & 255) << ":" << (old[i] >> 16 & 255) << "\n";
		cout << "����� ���� " << num[i] << " ��������� � RGB: ";
		cout << (mod[i] & 255) << ":" << (mod[i] >> 8 & 255) << ":" << (mod[i] >> 16 & 255) << "\n";
	}
}