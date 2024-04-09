#include "header.h"

void main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Russian");

	show_introduction();

	menu();

	SetConsoleCP(866);
	SetConsoleOutputCP(866);
}