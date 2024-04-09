#include "header.h"

string filename;

void show_introduction() {
	system("cls");
	cout << "  Welcome to the Program User Manual!\n";
	cout << "  \n";

	//resetColor(); // Assuming this resets console color, uncomment if needed
	system("pause");
};

void menu() {
	while (true) {
		system("cls");
		int flag = selection();
		cout << flag << endl;
		switch (flag) {
		case 1:
			filename = getFilename();
			add_txt(filename);
			if (!check_file_exists(filename)) {
				setColor(12);
				cerr << "Error: File " << filename << " does not exist in the current working folder." << endl;
				resetColor();
				filename.clear();
				system("pause");
				break;
			}
			break;

		case 2:
			if (filename != "") {
				process_data(filename);
			}
		case 3:
			exit(0); // Exit the program
		case 4:
			//show introduction
			show_introduction();
			break;
		}
	}
}

void process_data(string& filename) {
	//open file for reading and check if it is not empty
	ifstream infile;
	infile.open(filename.c_str());
}

bool check_file_exists(string filename) {
	ifstream file(filename);
	bool exists = file.good();
	file.close();
	return exists;
}

bool hasWindowsSpecChar(string filename) {
	// List of characters not allowed in Windows filenames
	list<char> prohibited_chars = { '<', '>', ':', '\"', '/', '\\', '|', '?', '*' };

	for (char c : filename) {
		if (find(prohibited_chars.begin(), prohibited_chars.end(), c) != prohibited_chars.end()) {
			setColor(12);
			cout << "Name of the file contains prohibited characters.\n";
			resetColor();
			return true;
		}
	}

	return false;
}

bool isReservedName(string name) {
	// Check if the name matches any of the reserved names
	static const string reserved_names[] = { "CON","PRN","AUX","NUL","COM1","COM2","COM3","COM4","COM5","COM6","COM7","COM8","COM9","LPT1","LPT2"
	,"LPT3","LPT4","LPT5","LPT6","LPT7","LPT8","LPT9" };
	for (const auto& reserved : reserved_names) {
		if (name == reserved) {
			setColor(12);
			cout << "It is a reserved name.\n";
			resetColor();
			return true; // Name matches a reserved name
		}
	}
	return false; // Name is not reserved
}

string getFilename() {
	string filename;
	cout << "Type '~' and press ENTER to exit to main menu\n";
	while (true) {
		cout << ">>";
		getline(cin, filename);
		if (filename == "~") {
			menu();
			break;
		}
		if (filename.empty()) {
			setColor(12);
			cout << "File name cannot be empty.\n";
			resetColor();
			continue;
		}
		if (hasWindowsSpecChar(filename)) {
			continue;
		}
		if (isReservedName(filename)) {
			continue;
		}
		// If all checks pass, break out of the loop and return the filename
		break;
	}
	return filename;
}

int selection() {
	int choice;
	cout << "List of .txt files cin current folder" << endl;
	setColor(2);
	system("dir /b *.txt");
	resetColor();

	cout << "Select an option: " << endl;
	cout << "(1) Set/Change source filename "; setColor(2); cout << filename << endl; resetColor();
	cout << "(2) Sort and output data"; setColor(2);
	cout << "(3) Exit Program " << endl;
	cout << "(4) Show introduction" << endl;

	//cout << "Enter your choice: ";

	choice = _getch() - '0';
	while ((choice < 1 || choice > 6)) { // Modified condition for new option
		choice = _getch() - '0';
	}
	//cout << choice << endl;

	return choice;
}

bool txt_check(string filename) {
	// Check if the filename ends with ".cty" (case insensitive)
	if (filename.length() >= 4 && equal(filename.end() - 4, filename.end(), ".txt", [](char a, char b) {
		return tolower(a) == b;
		})) {

		setColor(2); cout << "File extension is valid." << endl; resetColor();
		system("pause"); system("cls");
		return true;
	}
	else {
		//setColor(12); cout << "INVALID FILE EXTENSION" << endl; resetColor();
		return false;
	}
}

void add_txt(string& filename) {
	if (!txt_check(filename)) {
		char choice;
		while (true) {
			cout << "The filename doesn't have .txt extension. Do you want to add it? (y/n): ";
			choice = _getch();
			cout << choice << endl;
			choice = tolower(choice);
			if (choice == 'y') {
				filename += ".txt"; // Add .txt extension to the filename
				return; // Return after modifying the filename
			}
			if (choice == 'n') {
				cout << "\nFile wasn't modified." << endl;
				return; // Return without modifying the filename
			}
		}
	}
}

void setColor(int colorCode) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, colorCode);
	//  0 - Black //  1 - Blue //  2 - GREEN
	//  3 - Aqua //  4 - Red //  5 - Purple
	//  6 - Yellow //  7 - White //  8 - Gray
	//  9 - Light Blue //  10 - Light Green //  11 - Light Aqua
	//  12 - LIGHT RED //  13 - Light Purple //  14 - Light Yellow
	//  15 - Bright White

}
void resetColor() {
	setColor(7); // 7 is the default color (white on black)
}