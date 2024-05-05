#pragma once

#include <algorithm>
#include <cctype>
#include <conio.h>
#include <ctype.h>
#include <fstream>
#include <iomanip> 
#include <iostream>
#include <istream>
#include <limits>
#include <list>
#include <sstream>
#include <string>
#include <windows.h>
#include <chrono>
#include <vector>
#include <ctime>

using namespace std;
void show_introduction();                  // ������� ������ ����������������� ����������� ���������
void menu();                                 // ������� ������ ���� ���������
int selection();                              // ������� ������ ������ ����
vector<vector<string>> insertionSort(string& filename, int sortColumn, int order); // ������� ���������� ���������� �������� ������ �� ���������� �����
void saveData(vector<vector<string>> sortedData, int column, int order); // ������� ���������� ��������������� ������ � ����� ��������� ����
void printData(const vector<vector<string>>& data, int sortColumn); // ������� ������ ��������������� ������ � �������
void processData(string& filename);          // ������� ��������� ������ �� ���������� �����
int getFieldOrder();                          // ������� ��������� ������� ���������� (�� ������ �������)
int getSortOrder();                          // ������� ��������� ������� ���������� (�� �����������/��������)
string getFilename();                        // ������� ��������� ����������� ����� ����� �� ������������
string getCurrentDateTime();                  // ������� ��������� ������� ���� � ������� � �������� �������
void add_txt(string& filename);              // ������� ���������� ���������� �����
bool txt_check(string filename);       // ������� ��������, �������� �� ���� ���������� ��������� ������
bool isReservedName(string name);       // ������� ��������, �������� �� ��� ����� ����������������� � Windows
bool check_file_exists(string filename); // ������� �������� ������������� �����
bool hasWindowsSpecChar(string filename); // ������� �������� ������� ������������ �������� Windows � ����� �����
void setColor(int colorCode);                // ������� ��������� ����� ������ � �������
void resetColor();                          // ������� ������ ����� ������ ������� �� �������� �� ���������