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


void show_introduction();
void menu();


bool check_file_exists(string filename);
bool hasWindowsSpecChar(string filename);
bool isReservedName(string name);
string getFilename();
int selection();
bool txt_check(string filename);
void add_txt(string& filename);
void processData(string& filename);
void setColor(int colorCode);
void resetColor();



void printData(const vector<vector<string>>& data, int sortColumn);
vector<vector<string>> insertionSort(string& filename, int sortColumn, int order);
void saveData(vector<vector<string>> sortedData, int column, int order);
string getCurrentDateTime();



int getFieldOrder();
int getSortOrder();