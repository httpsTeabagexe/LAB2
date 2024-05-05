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
void show_introduction();                  // Функция вывода пользовательского руководства программы
void menu();                                 // Функция вывода меню программы
int selection();                              // Функция выбора пункта меню
vector<vector<string>> insertionSort(string& filename, int sortColumn, int order); // Функция выполнения сортировки вставкой данных из текстового файла
void saveData(vector<vector<string>> sortedData, int column, int order); // Функция сохранения отсортированных данных в новый текстовый файл
void printData(const vector<vector<string>>& data, int sortColumn); // Функция вывода отсортированных данных в консоль
void processData(string& filename);          // Функция обработки данных из текстового файла
int getFieldOrder();                          // Функция получения порядка сортировки (по какому столбцу)
int getSortOrder();                          // Функция получения порядка сортировки (по возрастанию/убыванию)
string getFilename();                        // Функция получения допустимого имени файла от пользователя
string getCurrentDateTime();                  // Функция получения текущей даты и времени в заданном формате
void add_txt(string& filename);              // Функция добавления расширения файла
bool txt_check(string filename);       // Функция проверки, является ли файл допустимым текстовым файлом
bool isReservedName(string name);       // Функция проверки, является ли имя файла зарезервированным в Windows
bool check_file_exists(string filename); // Функция проверки существования файла
bool hasWindowsSpecChar(string filename); // Функция проверки наличия недопустимых символов Windows в имени файла
void setColor(int colorCode);                // Функция установки цвета текста в консоли
void resetColor();                          // Функция сброса цвета текста консоли на значение по умолчанию