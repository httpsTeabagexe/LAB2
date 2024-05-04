#include "header.h"

string sourceFilename;

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
			sourceFilename = getFilename();
			add_txt(sourceFilename);
			if (!check_file_exists(sourceFilename)) {
				setColor(12);
				cerr << "Error: File " << sourceFilename << " does not exist in the current working folder." << endl;
				resetColor();
				sourceFilename.clear();
				system("pause");
				break;
			}
			break;

		case 2:
			if (sourceFilename != "") {
				processData(sourceFilename);
				break;
			}
			else {
				setColor(12);
				cerr << "Error: No file selected. Please select a file first." << endl;
				resetColor();
				system("pause");
				break;
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

void processData(string& filename) {
	// 1. Load data from file into vector
	//done in 4.
	// 2. Ask user to choose by what field to sort (1-5)
	int column = getFieldOrder();
	// 3. Ask user order of sorting (ascending/descending)
	int order = getSortOrder();

	// 4. Sort data by chosen vector column

	vector<vector<string>> sortedData = insertionSort(filename, column, order);

	//5. Display results
	printData(sortedData, column);

	int choice;
	cout << "Save sorted data into file?" << endl;
	cout << "(1) Yes" << endl;
	cout << "(2) No" << endl;
	cout << "Enter your choice: ";
	choice = _getch() - '0';
	while ((choice < 1 || choice > 2)) {
		choice = _getch() - '0';
	}
	cout << choice << endl;
	switch (choice){
	case 1:
		saveData(sortedData, column, order);
	case 2:
		break;
	}

	system("pause");
}

string getCurrentDateTime() {
	time_t now = time(0);
	tm ltm;
	localtime_s(&ltm, &now);
	char buf[80];
	strftime(buf, sizeof(buf), "%Y-%m-%d_%X", &ltm);
	return buf;
}


void saveData(vector<vector<string>> sortedData, int column, int order) {

	string OutFilename = getCurrentDateTime() + ".txt";

	// Open the file
	ofstream file(OutFilename);

	// Check if the file is open
	if (!file.is_open()) {
		cerr << "Unable to open file" << endl;
		return;
	}
	string textcolumn;
	switch (column) {
	case 0:
		textcolumn = "CITY";
		break;
	case 1:
		textcolumn = "POPULATION";
		break;
	case 2:
		textcolumn = "COUNTRY";
		break;
	case 3:
		textcolumn = "CAPITAL";
		break;
	case 4:
		textcolumn = "CONTINENT";
		break;
	}

	file << "INSERTION SORT. SORTED BY " << textcolumn << ". SORT ORDER " << (order == 0 ? "ASCENDING" : "DESCENDING") << "\n";
	// Write the sorted data
	for (const auto& row : sortedData) {
		// Write the sorted column first
		file << row[column] << '\t';

		// Write the rest of the columns excluding the sorted one
		for (int i = 0; i < row.size(); i++) {
			if (i != column) {
				file << row[i] << '\t';
			}
		}

		file << '\n';
	}

	// Close the file
	file.close();
}

void printData(const vector<vector<string>>& data, int sortColumn) {
	// Iterate over each row
	for (const auto& row : data) {
		// Print the sorted column first
		cout << row[sortColumn] << '\t';

		// Iterate over each column in the row
		for (int i = 0; i < row.size(); i++) {
			// Skip the sorted column since it's already printed
			if (i != sortColumn) {
				cout << row[i] << '\t';
			}
		}
		// Print a newline at the end of each row
		cout << '\n';
	}
}

// Function to read data from a file and sort it by a specified column
vector<vector<string>> insertionSort(string& filename, int sortColumn, int order) {
	ifstream file(filename);	// Create an input file stream with the given filename
	string line; 	// Declare a string to hold each line of the file
	vector<vector<string>> data; 	// Declare a 2D vector to hold all the data from the file
	// Check if the file was successfully opened
	if (file.is_open()) {
		// Read the file line by line
		while (getline(file, line)) {
			// Declare a vector to hold the data of each row
			vector<string> row;
			// Create a stringstream from the line
			stringstream ss(line);
			// Declare a string to hold each word in the line
			string word;
			// Read the line word by word, using '|' as the delimiter
			while (getline(ss, word, '|')) {
				// Add the word to the row vector
				row.push_back(word);
			}
			// Add the row to the data vector
			data.push_back(row);
		}
		// Close the file after reading
		file.close();
	}
	else {
		// Print an error message if the file couldn't be opened
		cout << "Unable to open file";
		// Return the data even if it's not sorted
		return data;
	}

	// Insertion sort
	//i = 2 to skip the first line containing the header
	for (int i = 1; i < data.size(); i++) {
		vector<string> key = data[i];
		int j = i - 1;
		switch (order) {
		case 1: // Ascending order
			//while (j >= 0 && (sortColumn == 1 ? stoi(data[j][sortColumn]) > stoi(key[sortColumn]) : data[j][sortColumn] > key[sortColumn])) {
			while (j >= 0 && data[j][sortColumn] > key[sortColumn]) {
				data[j + 1] = data[j];
				j = j - 1;
			}
			break;
		case 2: // Descending order
			//while (j >= 0 && (sortColumn == 1 ? stoi(data[j][sortColumn]) < stoi(key[sortColumn]) : data[j][sortColumn] < key[sortColumn])) {
			while (j >= 0 && data[j][sortColumn] < key[sortColumn]) {
				data[j + 1] = data[j];
				j = j - 1;
			}
			break;
		}

		data[j + 1] = key;
	}

	// Return the sorted data
	return data;
}

int getFieldOrder() {
	int choice;
	cout << "Sort by:\n";
	cout << "(1) City Name\n";
	cout << "(2) Population\n";
	cout << "(3) Country\n";
	cout << "(4) Capital\n";
	cout << "(5) Continent\n";
	cout << "Enter your choice: ";
	choice = _getch() - '0';
	while ((choice < 1 || choice > 5)) {
		choice = _getch() - '0';
	}
	cout << choice << endl;
	return choice-1;
}

int getSortOrder() {
	int choice;
	cout << "Choose sorting order:\n";
	cout << "(1) Ascending\n";
	cout << "(2) Descending\n";
	cout << "Enter your choice: ";
	choice = _getch() - '0';
	while (choice < 1 || choice > 2) {
		choice = _getch() - '0';
	}
	cout << choice << endl;
	return choice;
}

int selection() {
	int choice;
	cout << "List of .txt files in current folder" << endl;
	setColor(2);
	system("dir /b *.txt");
	resetColor();

	cout << "Select an option: " << endl;
	cout << "(1) Set/Change source filename "; setColor(2); cout << sourceFilename << endl; resetColor();
	cout << "(2) Sort and output data" << endl;
	cout << "(3) Exit Program " << endl;
	cout << "(4) Show introduction" << endl;

	//cout << "Enter your choice: ";

	choice = _getch() - '0';
	while ((choice < 1 || choice > 4)) {
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