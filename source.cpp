#include "header.h"
string sourceFilename;

void show_introduction() {
	system("cls");

	cout << " Welcome to the Program User Manual!\n";
	cout << " \n";

	cout << "Purpose:\n";
	cout << "- The program sorts a provided dataset based on a chosen column.\n";
	cout << "- It then prints the sorted data to the console.\n";
	cout << "\n";

	cout << "Features:\n";
	cout << "- Sorts data in ascending or descending order.\n";
	cout << "- Prints the sorted data with formatted columns.\n";
	cout << "\n";

	cout << "Instructions:\n";
	cout << "1. Running the Program:\n";
	cout << "   - Execute the program from your command line or terminal.\n";
	cout << "\n";

	cout << "2. Input:\n";
	cout << "   - The program typically takes user input to specify the column for sorting.\n";
	cout << "   - Follow the program's prompts or instructions to provide the necessary input.\n";
	cout << "\n";

	cout << "3. Output:\n";
	cout << "   - The program displays the sorted data on the console.\n";
	cout << "   - It is possible to save data in file with the name containing current date and time.\n";
	cout << "\n";

	cout << "Additional Notes:\n";
	cout << "- The specific details of input and output may vary depending on the program's implementation.\n";
	cout << "- Refer to any additional prompts or messages within the program for further guidance.\n";

	system("pause");
}

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
	int column = getFieldOrder();
	int order = getSortOrder();
	// Perform the sorting using the insertionSort function
	vector<vector<string>> sortedData = insertionSort(filename, column, order);
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
	switch (choice) {
	case 1:
		saveData(sortedData, column, order);
	case 2:
		break;
	}
	system("pause");
}

string getCurrentDateTime() {
	// Get current time point
	auto now = chrono::system_clock::now();
	// Convert to time_t for local time conversion
	time_t tt = chrono::system_clock::to_time_t(now);
	// Local time structure
	tm local_time;
	localtime_s(&local_time, &tt);
	// Create string stream for formatted output
	stringstream ss;
	ss << put_time(&local_time, "%Y-%m-%d_%H-%M-%S");
	return ss.str();
}

void saveData(vector<vector<string>> sortedData, int column, int order) {
	string OutFilename = getCurrentDateTime() + ".txt";
	// Open the file in write mode with error handling
	ofstream file(OutFilename, ios::out | ios::trunc);
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
	file << "INSERTION SORT. SORTED BY " << textcolumn << ". SORT ORDER " << (order == 1 ? "ASCENDING" : "DESCENDING") << "\n";
	// Write the sorted data
	vector<string> headerNames = { "CITY", "POPULATION", "COUNTRY", "CAPITAL", "CONTINENT" };
	file << setw(15) << headerNames[column];
	for (int i = 0; i < headerNames.size(); i++) {
		if (i != column) {
			file << setw(15) << headerNames[i];
		}
	}	file << "\n";
	for (const auto& row : sortedData) {
		file << setw(15) << row[column];
		// Write the rest of the columns excluding the sorted one
		for (int i = 0; i < row.size(); i++) {
			if (i != column) {
				file << setw(15) << row[i];
			}		}
		file << '\n';
	}
	file.close();
	cout << "Data was succesfuly saved to " << OutFilename << endl;
}

void printData(const vector<vector<string>>& data, int sortColumn) {
	// Iterate over each row
	for (const auto& row : data) {
		// Print the sorted column first with a fixed width
		cout << setw(15) << row[sortColumn];
		// Iterate over each column in the row
		for (int i = 0; i < row.size(); i++) {
			// Skip the sorted column since it's already printed
			if (i != sortColumn) {
				// Print other columns with a fixed width
				cout << setw(15) << row[i];
			}		}
		// Print a newline at the end of each row
		cout << '\n';
	}
}

// Function to read data from a file and sort it by a specified column
vector<vector<string>> insertionSort(string& filename, int sortColumn, int order) {
	ifstream file(filename);	// Create an input file stream with the given filename
	string line; 	// Declare a string to hold each line of the file
	getline(file, line); // Skip the first line
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
				// Remove trailing spaces from the word
				word.erase(word.find_last_not_of(" ") + 1);
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
	int perm_count(0);
	// Insertion sort
	for (int i = 1; i < data.size(); i++) {
		vector<string> key = data[i];
		// Check if sortColumn is 1 and replace "!NODATA!" with -1
		if (sortColumn == 1 && key[sortColumn] == "!NODATA!") {
			if (order == 1) {
				key[sortColumn] = "60000000";
			}
			else {
				key[sortColumn] = "-1";
			}
		}
		else if (sortColumn != 1 && key[sortColumn] == "!NODATA!") {
			if (order == 1) {
				key[sortColumn] = "zzz";
			}
			else {
				key[sortColumn] = "AAA";
			}
		}
		int j = i - 1;

		switch (order) {
		case 1: // Ascending order
			if (sortColumn == 1) {
				// Integer comparison using stoi
				while (j >= 0 && stoi(data[j][sortColumn]) > stoi(key[sortColumn])) {
					perm_count++;
					data[j + 1] = data[j];
					j = j - 1;
				}			}
			else {
				// String comparison
				while (j >= 0 && data[j][sortColumn] > key[sortColumn]) {
					perm_count++;
					data[j + 1] = data[j];
					j = j - 1;
				}			}
			break;
		case 2: // Descending order
			if (sortColumn == 1) {
				// Integer comparison using stoi
				while (j >= 0 && stoi(data[j][sortColumn]) < stoi(key[sortColumn])) {
					perm_count++;
					data[j + 1] = data[j];
					j = j - 1;
				}			}
			else {
				// String comparison
				while (j >= 0 && data[j][sortColumn] < key[sortColumn]) {
					perm_count++;
					data[j + 1] = data[j];
					j = j - 1;
				}			}
			break;
		}

		data[j + 1] = key;
	}

	for (int i = 0; i < data.size(); ++i) {
		if (data[i][sortColumn] == "-1" || data[i][sortColumn] == "60000000" || data[i][sortColumn] == "zzz" || data[i][sortColumn] == "AAA") {
			data[i][sortColumn] = "!NODATA!";
		}
	}

	//now all the invalid data is stored in one format as !NODATA!

	cout << "Number of permutations: " << perm_count << endl;
	file.close();
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
	return choice - 1;
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
	choice = _getch() - '0';
	while ((choice < 1 || choice > 4)) {
		choice = _getch() - '0';
	}
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
	else {		return false;	}
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
			}		}	}
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
		}	}
	return false;
}

bool isReservedName(string name) {
	// Check if the name matches any of the reserved names
	static const string reserved_names[] = { "CON","PRN","AUX","NUL",
	"COM1","COM2","COM3","COM4","COM5","COM6","COM7","COM8","COM9","LPT1","LPT2","LPT3","LPT4","LPT5","LPT6","LPT7","LPT8","LPT9" };
	for (const auto& reserved : reserved_names) {
		if (name == reserved) {
			setColor(12);
			cout << "It is a reserved name.\n";
			resetColor();
			return true; // Name matches a reserved name
		}	}
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
		break;
	}
	return filename;
}

void setColor(int colorCode) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, colorCode);
}
void resetColor() {
	setColor(7); // 7 is the default color (white on black)
}