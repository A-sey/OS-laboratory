// LR1_2.cpp: определяет точку входа для консольного приложения.
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
	// Константы
	const DWORD pcName_length = MAX_COMPUTERNAME_LENGTH + 1;
	const DWORD userName_length = UNLEN + 1;
	const DWORD folder_length = 100;
	// Буферы строк
	TCHAR pcName[pcName_length];
	TCHAR userName[userName_length];
	TCHAR sysFolder[folder_length];
	TCHAR winFolder[folder_length];
	TCHAR tempFolder[folder_length];
	// Структура, содержащая информацию об ОС
	OSVERSIONINFOA version_info;
	version_info.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	// Переменные для метрик
	int cursor_width;
	int cursor_height;
	int min_window_width;
	int min_window_height;
	// Переменные для параметров
	int keyboard_speed;
	int alt_tab;
	// Цвета
	int col[] = { COLOR_HIGHLIGHT, COLOR_INACTIVEBORDER, COLOR_ACTIVECAPTION };
	int size = sizeof(col) / sizeof(int);
	int* color;
	int* invert;
	color = new int[size];
	invert = new int[size];
	// Время
	int session_time;
	SYSTEMTIME sm;

	// Получение информации
	// Имя компьютера
	GetComputerName(pcName, (LPDWORD)&pcName_length);
	Prnt("Имя компьютера: ", pcName, pcName_length);
	// Имя пользователя
	GetUserName(userName, (LPDWORD)&userName_length);
	Prnt("Имя пользователя: ", userName, userName_length);
	// Адрес системного каталога
	GetSystemDirectory(sysFolder, folder_length);
	Prnt("Адрес системного каталога: ", sysFolder, folder_length);
	// Адрес каталога Windows
	GetWindowsDirectory(winFolder, folder_length);
	Prnt("Адрес каталога Windows: ", winFolder, folder_length);
	// Адрес каталога временных файлов
	GetTempPath(folder_length, tempFolder);
	Prnt("Адрес каталога временных файлов: ", tempFolder, folder_length);
	// Информация о версии ОС
	GetVersionEx((OSVERSIONINFO*)&version_info);
	Prnt(version_info);

	// Системные метрики
	// Максимальные размеры курсора
	cursor_width = GetSystemMetrics(SM_CXCURSOR);
	Prnt("Максимальная ширина курсора, px: ", cursor_width);
	cursor_height = GetSystemMetrics(SM_CYCURSOR);
	Prnt("Максимальная высота курсора, px: ", cursor_height);
	// Минимальные размеры окна
	min_window_width = GetSystemMetrics(SM_CXMIN);
	Prnt("Минимальная ширина окна, px: ", min_window_width);
	min_window_height = GetSystemMetrics(SM_CYMIN);
	Prnt("Минимальная высота окна, px: ", min_window_height);

	// Системные параметры
	// Скорость печати символов при нажатой клавише
	SystemParametersInfo(SPI_GETKEYBOARDSPEED, 0, &keyboard_speed, 0);
	Prnt("Скорость печати символов при нажатой клавише: ", keyboard_speed);
	// Активна ли комбинация Alt+Tab
	SystemParametersInfo(SPI_GETFASTTASKSWITCH, 0, &alt_tab, 0);
	Prnt("Активность комбинации Alt+Tab: ", alt_tab);

	// Цвета
	// Получаем цвета	
	for (int i = 0; i < size; i++)
		color[i] = GetSysColor(col[i]);
	// Изменяем их
	for (int i = 0; i < size; i++)
		invert[i] = (color[i] >> 16 & 255) | ((color[i] >> 8 & 255) << 8) | ((color[i] & 255) << 16);
	// Применяем новые
	if (SetSysColors(1, col, (COLORREF*)invert))
		Prnt(size, col, color, invert);

	// Работа со временем
	// Продолжительность сеанса:
	session_time = GetTickCount();
	// Информация по системному времени:
	GetSystemTime(&sm);
	Prnt("Продолжительность сеанса: ", session_time);
	Prnt("Год: ", sm.wYear);
	Prnt("Месяц: ", sm.wMonth);
	Prnt("День: ", sm.wDay);
	Prnt("Час: ", sm.wHour);
	Prnt("Минута: ", sm.wMinute);
	Prnt("Секунда: ", sm.wSecond);

	system("timeout -1");
	return 0;
}

// Вывод произвольного буфера
void Prnt(string str, TCHAR* text, int length)
{
	cout << str;
	for (int i = 0; i < length && text[i] != 0; i++)
		cout << (char)(text[i]);
	cout << "\n";
}

// Вывод информации об ОС
void Prnt(OSVERSIONINFOA ver)
{
	cout << "Основной номер версии: " << ver.dwMajorVersion << "\n";
	cout << "Дополнительный номер версии: " << ver.dwMinorVersion << "\n";
	cout << "Номер сборки ОС: " << ver.dwBuildNumber << "\n";
	cout << "Номер платформы: " << ver.dwPlatformId << "\n";
}

// Вывод числовых параметров
void Prnt(string str, int num)
{
	cout << str << num << "\n";
}

// Вывод цветовых параметров
void Prnt(int size, int* num, int* old, int* mod)
{
	for (int i = 0; i < size; i++)
	{
		cout << "Старый цвет " << num[i] << " параметра в RGB: ";
		cout << (old[i] & 255) << ":" << (old[i] >> 8 & 255) << ":" << (old[i] >> 16 & 255) << "\n";
		cout << "Новый цвет " << num[i] << " параметра в RGB: ";
		cout << (mod[i] & 255) << ":" << (mod[i] >> 8 & 255) << ":" << (mod[i] >> 16 & 255) << "\n";
	}
}