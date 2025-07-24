/*
SEHH2042 Group Project - Student Management System - Group X
Lecture Group: XXX
Group Members:
1. XXXXX YYYY ZZZ
2. XXXXX YYYY ZZZ
3. XXXXX YYYY ZZZ
4. XXXXX YYYY ZZZ
5. XXXXX YYYY ZZZ
6. XXXXX YYYY ZZZ
*/

// Header files
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <random>
#include <string>
#include <vector>

// System headers (Compatible with Windows/Linux/MacOS)
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

// Namespace
using namespace std;

// Function prototypes
class Student;
class Subject;
class Systemsubject;
string formatStudentName(string name);
string formatMajor(string major);
string formatsubjectName(string subjectName);
string generateStudentID(int studentCohort);
bool checkNameLength(string studentName);
bool checkMajorLength(string studentMajor);
bool checkCohortYear(int cohortYear);
bool checkSubjectNameLength(string subjectName);
bool checkSubjectNameUnique(string subjectName);
bool checkCreditRange(int credits);
bool studentIDVaildCheck(string studentID);
bool checkStudentID(string studentID);
void clearScreen();
void waitForSecond(int seconds);
void printLine(string ch, int count);
void defaultData();
void defaultSubject();
void loadStartingData();
void checkLoaded();
void showStudentRecords();
void displayStudentRecord(vector<Student> sortedStudent);

void editStudents_entrance();
void editStudents_menu(string studentID);
void editStudents_Name(string studentID);
void editStudents_Major(string studentID);
void editStudents_SubjectList(string studentID);

void addDeleteStudents();
void generateTranscript();
void creditsAndExit();
void mainMenu();

// Global variables
bool dataLoaded = false;
const int currentYear = 2024;
vector<Student> students;
vector<Subject> subjects;
vector<Systemsubject> systemsubject;

// Subject's class
class Subject
{
public:
	string subjectCode;
	string subjectName;
	int subjectCredits;
	string subjectGrade;
	bool inProgress;

	Subject(string code, string name, int credits, string grade = "--", bool progress = false)
	{
		subjectCode = code;
		subjectName = name;
		subjectCredits = credits;
		subjectGrade = grade;
		inProgress = progress;
	}
};

// Global subject
class Systemsubject
{
public:
	string subjectCode;
	string subjectName;
	int subjectCredit;

	Systemsubject(string code, string name, int credit)
	{
		subjectCode = code;
		subjectName = name;
		subjectCredit = credit;
	}
};

// Student's class
class Student
{
public:
	string studentName;
	string studentID;
	string studentMajor;
	int studentYear;
	double studentGPA;
	int studentCohort;
	string studentsubjectcode;
	vector<Subject> subjectsTaken;

	Student(string name, string id, string major, int year, double gpa)
	{
		// Everything should check if the data is valid or not
		studentName = formatStudentName(name);
		studentID = id;
		studentMajor = major;
		studentYear = year;
		studentGPA = gpa;
		studentCohort = currentYear - year + 1;
		calculateGPA();
	}

	Student(string name, string id, string major, int cohort)
	{
		// Everything should check if the data is valid or not
		studentName = formatStudentName(name);
		studentID = id;
		studentMajor = major;
		studentYear = currentYear + 1 - cohort;
		studentCohort = cohort;
		studentGPA = -1.0;
	}

	void addSubject(const Subject &subject)
	{
		subjectsTaken.push_back(subject);
		if (subject.inProgress)
		{
			subjectsTaken.back().subjectGrade = "--";
		}
		else
		{
			calculateGPA();
		}
	}

	void calculateGPA()
	{
		double totalPoints = 0.0;
		int totalCredits = 0;

		for (const auto &subject : subjectsTaken)
		{
			if (subject.inProgress || subject.subjectGrade == "--")
			{
				continue;
			}
			if (!subject.inProgress)
			{
				double gradePoint = 0.0;
				if (subject.subjectGrade == "A+")
					gradePoint = 4.3;
				else if (subject.subjectGrade == "A")
					gradePoint = 4.0;
				else if (subject.subjectGrade == "A-")
					gradePoint = 3.7;
				else if (subject.subjectGrade == "B+")
					gradePoint = 3.3;
				else if (subject.subjectGrade == "B")
					gradePoint = 3.0;
				else if (subject.subjectGrade == "B-")
					gradePoint = 2.7;
				else if (subject.subjectGrade == "C+")
					gradePoint = 2.3;
				else if (subject.subjectGrade == "C")
					gradePoint = 2.0;
				else if (subject.subjectGrade == "C-")
					gradePoint = 1.7;
				else if (subject.subjectGrade == "D+")
					gradePoint = 1.3;
				else if (subject.subjectGrade == "D")
					gradePoint = 1.0;
				else if (subject.subjectGrade == "F")
					gradePoint = 0.0;

				totalPoints += gradePoint * subject.subjectCredits;
				totalCredits += subject.subjectCredits;
			}
		}

		if (totalCredits > 0)
		{
			studentGPA = totalPoints / totalCredits;
		}
		else
		{
			studentGPA = 0.0; // No completed subjects
		}
	}
};

// Format students name
string formatStudentName(string name)
{
	name.erase(0, name.find_first_not_of(" \t"));
	name.erase(name.find_last_not_of(" \t") + 1);

	if (name.empty())
	{
		return "";
	}

	string formattedFullName;
	size_t surnameSpacePos = name.find(' ');

	if (surnameSpacePos == string::npos)
	{
		string singleName = name;
		transform(singleName.begin(), singleName.end(), singleName.begin(), ::toupper);
		return singleName;
	}

	string surname = name.substr(0, surnameSpacePos);
	string givenName = name.substr(surnameSpacePos + 1);

	transform(surname.begin(), surname.end(), surname.begin(), ::toupper);

	if (!givenName.empty())
	{
		bool newWord = true;
		for (char &c : givenName)
		{
			if (newWord)
			{
				c = toupper(c);
				newWord = false;
			}
			else if (isspace(c))
			{
				newWord = true;
			}
			else
			{
				c = tolower(c);
			}
		}
	}

	formattedFullName = surname + " " + givenName;
	return formattedFullName;
}

// UPPERCASE
string toUpper(const string &s)
{
	string result = s;
	transform(result.begin(), result.end(), result.begin(), ::toupper);
	return result;
}

// Major first letter capitalize
string formatMajor(string major)
{
	string formattedMajor;
	bool capitalizeNext = true;

	for (char ch : major)
	{
		if (isspace(ch))
		{
			capitalizeNext = true;
			formattedMajor += ch;
		}
		else if (capitalizeNext)
		{
			formattedMajor += toupper(ch);
			capitalizeNext = false;
		}
		else
		{
			formattedMajor += tolower(ch);
		}
	}
	return formattedMajor;
}

// Subject name first letter capitalize
string formatsubjectName(string subjectName)
{
	string formatsubjectName;
	bool capitalizeNext = true;

	for (char ch : subjectName)
	{
		if (isspace(ch))
		{
			capitalizeNext = true;
			formatsubjectName += ch;
		}
		else if (capitalizeNext)
		{
			formatsubjectName += toupper(ch);
			capitalizeNext = false;
		}
		else
		{
			formatsubjectName += tolower(ch);
		}
	}
	return formatsubjectName;
}

// Remove space and capitalize first letter
string formatStudentID(const string &input)
{
	string formatted = input;

	formatted.erase(remove_if(formatted.begin(), formatted.end(), ::isspace), formatted.end());

	transform(formatted.begin(), formatted.end(), formatted.begin(), ::toupper);

	return formatted;
}

// Generate random StudentID
string generateStudentID(int studentCohort)
{
	string studentID;
	int checkdigit = 0;

	// Set random seed with current time
	unsigned seed;
	seed = (unsigned)time(NULL);
	srand(seed);

	int randomNumber = rand() % 1000;
	studentID = to_string(studentCohort - 2000) + (randomNumber < 100 ? (randomNumber < 10 ? "00" : "0") : "") +
				to_string(randomNumber);
	for (int i = 0; i <= 4; i++)
	{
		checkdigit += studentID[i] - '0';
	}
	checkdigit = checkdigit % 10;
	studentID = "S" + studentID + to_string(checkdigit);
	if (checkStudentID(studentID))
	{
		waitForSecond(1);
		return generateStudentID(studentCohort);
	}
	return studentID;
}

// Check if name length > 30
bool checkNameLength(string studentName)
{
	if (studentName.length() > 30)
	{
		return false;
	}
	else
	{
		return true;
	}
}

// Check if major length > 30
bool checkMajorLength(string studentMajor)
{
	if (studentMajor.length() > 30)
	{
		return false;
	}
	else
	{
		return true;
	}
}

// Check cohort year invaild or not
bool checkCohortYear(int cohortYear)
{
	if (cohortYear < 2021 || cohortYear > currentYear)
	{
		return false;
	}
	else
	{
		return true;
	}
}

// Check if subject name length > 40
bool checkSubjectNameLength(string subjectName)
{
	if (subjectName.length() > 40)
	{
		return false;
	}
	else
	{
		return true;
	}
}

// Check if duplicate subject name
bool checkSubjectNameUnique(string subjectName)
{
	for (const auto &subj : systemsubject)
	{
		if (subj.subjectName == subjectName)
		{
			return false;
		}
	}
	return true;
}

// Check if duplicate studentID
bool studentExists(const string &inputId)
{
	string upperId = toUpper(inputId);
	for (const auto &student : students)
	{
		if (student.studentID == upperId)
		{
			return true;
		}
	}
	return false;
}

// Check if credit range available
bool checkCreditRange(int credits)
{
	if (credits < 2 || credits > 5)
	{
		return false;
	}
	else
	{
		return true;
	}
}

// Clear screen (Compatible with Windows/Linux/MacOS)
void clearScreen()
{
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}

// Wait for second (Compatible with Windows/Linux/MacOS)
void waitForSecond(int seconds)
{
#ifdef _WIN32
	Sleep(seconds * 1000);
#else
	sleep(seconds);
#endif
}

// Default data in student record
void defaultData()
{
	students.push_back(Student("CHAN Tai Man", "S243560", "Information Engineering", 1, 4.00));
	students.push_back(Student("CHEUNG Jacky", "S232210", "Civil Engineering", 2, 2.48));
	students.push_back(Student("PAN Peter", "S222343", "Global Business", 3, 3.42));
	students.push_back(Student("WONG Kam", "S244617", "Educational Psychology", 1, 2.86));

	students[0].addSubject(Subject("ENG2042", "Introduction to C++", 3, "A"));
	students[0].addSubject(Subject("ENG2219", "Signal Processing", 3, "A"));
	students[0].addSubject(Subject("LCH1302", "Professional English Writing", 2, "A"));
	students[0].addSubject(Subject("LCH1019", "Japanese I", 2, "--", true));

	students[1].addSubject(Subject("ENG1113", "Structural Fundamental", 3, "B"));
	students[1].addSubject(Subject("ENG2250", "Engineering Mathematics", 3, "B+"));
	students[1].addSubject(Subject("ENG2041", "Applied Computing", 3, "F"));
	students[1].addSubject(Subject("LCH1302", "Professional English Writing", 2, "A-"));
	students[1].addSubject(Subject("LCH1019", "Japanese I", 2, "B"));
	students[1].addSubject(Subject("BUS1021", "Personal Financial Planning", 3, "--", true));
	students[1].addSubject(Subject("ENG2042", "Introduction to C++", 3, "--", true));

	students[2].addSubject(Subject("BUS1021", "Personal Financial Planning", 3, "A"));
	students[2].addSubject(Subject("BUS2002", "Introduction to Economics", 3, "A+"));
	students[2].addSubject(Subject("BUS3006", "Understanding Globalization", 3, "B-"));
	students[2].addSubject(Subject("BUS4510", "Business Project Management", 4, "A-"));
	students[2].addSubject(Subject("BUS5523", "Final Year Project", 5, "B+"));
	students[2].addSubject(Subject("LCH1019", "Japanese I", 2, "C"));

	students[3].addSubject(Subject("PSY1234", "Introduction to Psychology", 2, "C"));
	students[3].addSubject(Subject("PSY2345", "Sociology", 3, "B"));
	students[3].addSubject(Subject("PSY2190", "Human Behavior", 3, "B+"));
	waitForSecond(1);
}

// Default subject list in global list
void defaultSubject()
{
	systemsubject.push_back(Systemsubject("ENG2042", "Introduction to C++", 3));
	systemsubject.push_back(Systemsubject("ENG2219", "Signal Processing", 3));
	systemsubject.push_back(Systemsubject("LCH1302", "Professional English Writing", 2));
	systemsubject.push_back(Systemsubject("LCH1019", "Japanese I", 2));
	systemsubject.push_back(Systemsubject("ENG1113", "Structural Fundamental", 3));
	systemsubject.push_back(Systemsubject("ENG2250", "Engineering Mathematics", 3));
	systemsubject.push_back(Systemsubject("ENG2041", "Applied Computing", 3));
	systemsubject.push_back(Systemsubject("BUS1021", "Personal Financial Planning", 3));
	systemsubject.push_back(Systemsubject("BUS2002", "Introduction to Economics", 3));
	systemsubject.push_back(Systemsubject("BUS3006", "Understanding Globalization", 3));
	systemsubject.push_back(Systemsubject("BUS4510", "Business Project Management", 4));
	systemsubject.push_back(Systemsubject("BUS5523", "Final Year Project", 5));
	systemsubject.push_back(Systemsubject("PSY1234", "Introduction to Psychology", 2));
	systemsubject.push_back(Systemsubject("PSY2233", "Sociology", 3));
	systemsubject.push_back(Systemsubject("PSY2190", "Human Behavior", 3));
	sort(systemsubject.begin(), systemsubject.end(),
		 [](const Systemsubject &a, const Systemsubject &b)
		 { return a.subjectCode < b.subjectCode; });
}

// Check data loaded or not
void checkLoaded()
{
	if (!dataLoaded)
	{
		cout << "Data not loaded!" << endl;
		waitForSecond(1);
	}
}

// Check studentID vaild
bool studentIDVaildCheck(string studentID)
{
	int checkdigit;
	if (studentID.length() != 7)
	{
		cout << "Invalid Student ID length! (The length must be \'7\'!)" << endl;
		return false;
	}
	if (studentID[0] != 'S')
	{
		cout << "Invalid Student ID format! (The first character must be \'S\'!)" << endl;
		return false;
	}
	if (!isdigit(studentID[1]) || !isdigit(studentID[2]) || !isdigit(studentID[3]) || !isdigit(studentID[4]) ||
		!isdigit(studentID[5]) || !isdigit(studentID[6]))
	{
		cout << "Invalid Student ID format! (The 2nd to 6th character must be decimal intger!)" << endl;
		return false;
	}
	checkdigit = ((studentID[1]) + (studentID[2]) + (studentID[3]) + (studentID[4]) + (studentID[5])) % 10;
	if (checkdigit != stoi(studentID.substr(6, 1)))
	{
		cout << "Invalid Student ID check digit!" << endl;
		return false;
	}
	return true;
}

// Check Student ID is valid or not
bool checkStudentID(string studentID)
{
	if (!studentID.empty() && studentID[0] == 's')
	{
		studentID[0] = 'S';
	}
	for (const auto &student : students)
	{
		if (student.studentID == studentID)
		{
			return true;
		}
	}
	return false;
}

// Load starting data
void loadStartingData()
{
	if (dataLoaded)
	{
		cout << "Data already loaded!" << endl;
		waitForSecond(1);
		return;
	}
	cout << "Loading data..." << endl;
	waitForSecond(1);
	defaultData();
	defaultSubject();
	dataLoaded = true;
	// Load data here
	cout << "Data loaded successfully!" << endl;
	waitForSecond(1);
}

// Print table's line (Nice)
void printLine(string ch, int count)
{
	for (int i = 0; i < count; i++)
	{
		cout << ch;
	}
}

// Show student records
void showStudentRecords()
{
	checkLoaded();
	if (!dataLoaded)
		return;
	string inputOption;
	vector<Student> sortedStudents = students;
	do
	{
		clearScreen();
		displayStudentRecord(sortedStudents);
		cout << endl;
		cout << "********** Students Records **********" << endl;
		cout << "[1] Sort by Students name (Ascending)" << endl;
		cout << "[2] Sort by GPA (Descending)" << endl;
		cout << "[3] Return to Main Menu" << endl;
		cout << "**************************************" << endl;
		cout << "Option (1 - 3): ";
		getline(cin, inputOption);
		cout << endl;
		if (inputOption.empty())
		{
			cout << "Empty input! Please try again." << endl;
			waitForSecond(1);
			continue;
		}
		if (inputOption == "1")
		{
			sort(sortedStudents.begin(), sortedStudents.end(),
				 [](const Student &a, const Student &b)
				 { return a.studentName < b.studentName; });
		}
		if (inputOption == "2")
		{
			sort(sortedStudents.begin(), sortedStudents.end(),
				 [](const Student &a, const Student &b)
				 { return a.studentGPA > b.studentGPA; });
		}
		if (inputOption == "3")
		{
			cout << "Returning to main menu..." << endl;
			waitForSecond(1);
			return;
		}
		if (inputOption != "1" && inputOption != "2" && inputOption != "3")
		{
			cout << "Invalid input! Please try again." << endl;
			waitForSecond(1);
			continue;
		}
	} while (inputOption != "1" && inputOption != "2");
	clearScreen();
	cout << "Student Records sort by " << ((inputOption != "1") ? "GPA" : "Name") << endl;
	displayStudentRecord(sortedStudents);
	cout << endl;
	cout << "Press Enter to continue...";
	cin.get();
}

// Print student record table
void displayStudentRecord(vector<Student> sortedStudents)
{
	cout << "+";
	printLine("-", 32);
	cout << "+";
	printLine("-", 12);
	cout << "+";
	printLine("-", 32);
	cout << "+";
	printLine("-", 6);
	cout << "+";
	printLine("-", 6);
	cout << "+" << endl;

	cout << "| " << setw(31) << left << "Student Name"
		 << "| " << setw(11) << left << "Student ID"
		 << "| " << setw(31) << left << "Major"
		 << "| " << setw(5) << left << "Year"
		 << "| " << setw(5) << left << "GPA"
		 << "|" << endl;

	cout << "+";
	printLine("-", 32);
	cout << "+";
	printLine("-", 12);
	cout << "+";
	printLine("-", 32);
	cout << "+";
	printLine("-", 6);
	cout << "+";
	printLine("-", 6);
	cout << "+" << endl;

	for (const auto &student : sortedStudents)
	{
		cout << "| " << setw(31) << left << student.studentName << "| " << setw(11) << left << student.studentID << "| "
			 << setw(31) << left << student.studentMajor << "| " << setw(5) << left << student.studentYear << "| ";
		if (student.studentGPA == -1.0)
		{
			cout << setw(5) << left << "N/A" << "| " << endl;
		}
		else
		{
			cout << setw(5) << left << fixed << setprecision(2) << student.studentGPA << "| " << endl;
		}
	}

	cout << "+";
	printLine("-", 32);
	cout << "+";
	printLine("-", 12);
	cout << "+";
	printLine("-", 32);
	cout << "+";
	printLine("-", 6);
	cout << "+";
	printLine("-", 6);
	cout << "+" << endl;
}

// Edit Students records
void editStudents_entrance()
{
	checkLoaded();
	if (!dataLoaded)
		return;
	string studentID;

	int retryCount = 0;
	while (true)
	{
		clearScreen();
		displayStudentRecord(students);
		cout << "Enter the Student ID (Type \'quit\' to return main menu): ";
		getline(cin, studentID);
		studentID.erase(remove_if(studentID.begin(), studentID.end(), ::isspace), studentID.end());
		cout << endl;
		if (studentID.empty())
		{
			retryCount++;
			if (retryCount <= 2)
			{
				cout << "Invalid input! Student ID cannot be empty." << endl;
				cout << "You have " << (2 - retryCount + 1) << " more attempt(s)." << endl;
				waitForSecond(2);
				continue;
			}
			else
			{
				cout << "Maximum invalid input attempts reached. Returning to main menu..." << endl;
				waitForSecond(2);
				return;
			}
		}
		if (studentID == "quit")
		{
			cout << "Returning to main menu..." << endl;
			waitForSecond(2);
			return;
		}
		if (!studentIDVaildCheck(studentID))
		{
			retryCount++;
			if (retryCount <= 2)
			{
				cout << "You have " << (2 - retryCount + 1) << " more attempt(s)." << endl;
				waitForSecond(2);
				continue;
			}
			else
			{
				cout << "Maximum invalid input attempts reached. Returning to main menu..." << endl;
				waitForSecond(2);
				return;
			}
		}
		if (!checkStudentID(studentID))
		{
			retryCount++;
			if (retryCount <= 2)
			{
				cout << "Student ID not found! Please try again." << endl;
				cout << "You have " << (2 - retryCount + 1) << " more attempt(s)." << endl;
				waitForSecond(2);
				continue;
			}
			else
			{
				cout << "Maximum invalid input attempts reached. Returning to main menu..." << endl;
				waitForSecond(2);
				return;
			}
		}
		break;
	}
	editStudents_menu(studentID);
}

// Edit students menu
void editStudents_menu(string studentID)
{
	while (true)
	{
		clearScreen();
		cout << "Action for Student ID: " << studentID << endl;
		cout << "***** Edit Student Menu *****" << endl;
		cout << "[1] Edit Student Name" << endl;
		cout << "[2] Edit Major" << endl;
		cout << "[3] Edit Subject List" << endl;
		cout << "[4] Return to Main Menu" << endl;
		cout << "*****************************" << endl;
		cout << "Option (1 - 4): ";
		string editStudentOption;
		cin.clear();
		getline(cin, editStudentOption);
		cout << endl;
		if (editStudentOption.empty())
		{
			cout << "Empty input! Please try again." << endl;
			waitForSecond(1);
			continue;
		}
		if (editStudentOption == "1")
		{
			editStudents_Name(studentID);
		}
		if (editStudentOption == "2")
		{
			editStudents_Major(studentID);
		}
		if (editStudentOption == "3")
		{
			editStudents_SubjectList(studentID);
		}
		if (editStudentOption == "4")
		{
			cout << "Returning to main menu..." << endl;
			waitForSecond(1);
			mainMenu();
		}
		if (editStudentOption != "1" && editStudentOption != "2" && editStudentOption != "3" &&
			editStudentOption != "4")
		{
			cout << "Invalid input! Please try again." << endl;
			waitForSecond(1);
			return;
		}
	}
}

// Edit students menu -- Edit name
void editStudents_Name(string studentID)
{
	Student *studentToEdit = nullptr;
	for (auto &student : students)
	{
		if (student.studentID == studentID)
		{
			studentToEdit = &student;
			break;
		}
	}

	if (studentToEdit == nullptr)
	{
		cout << "Error: Student with ID " << studentID << " not found!" << endl;
		waitForSecond(2);
		return;
	}

	int retryCount = 0;
	int retryCount2 = 0;
	const int maxRetries = 2;
	while (retryCount <= maxRetries && retryCount2 <= maxRetries)
	{
		clearScreen();
		cout << "Current Student name: " << studentToEdit->studentName << endl;
		string newName;
		cout << "Enter new Student name: ";
		cin.clear();
		getline(cin, newName);
		cout << endl;
		if (newName.empty())
		{
			retryCount++;
			if (retryCount <= maxRetries)
			{
				cout << "Invalid input! Name cannot be empty." << endl;
				cout << "You have " << (maxRetries - retryCount + 1) << " more attempt(s)." << endl;
				waitForSecond(2);
				continue;
			}
			else
			{
				cout << endl;
				cout << "Maximum invalid attempts reached. Returning to Edit Student Menu..." << endl;
				waitForSecond(2);
				return;
			}
		}
		if (any_of(newName.begin(), newName.end(), ::isdigit))
		{
			retryCount++;
			if (retryCount <= maxRetries)
			{
				cout << "Invalid name format! Name should not contain numbers." << endl;
				cout << "You have " << (maxRetries - retryCount + 1) << " more attempt(s)." << endl;
				waitForSecond(2);
				continue;
			}
			else
			{
				cout << endl;
				cout << "Maximum invalid attempts reached. Returning to Edit Student Menu..." << endl;
				waitForSecond(2);
				return;
			}
		}
		if (newName.find(" ") == string::npos)
		{
			retryCount++;
			if (retryCount <= maxRetries)
			{
				cout << "Invalid name format! Please include both surname and given name." << endl;
				cout << "You have " << (maxRetries - retryCount + 1) << " more attempt(s)." << endl;
				waitForSecond(2);
				continue;
			}
			else
			{
				cout << endl;
				cout << "Maximum invalid attempts reached. Returning to Edit Student Menu..." << endl;
				waitForSecond(2);
				return;
			}
		}
		if (!checkNameLength(newName))
		{
			retryCount++;
			if (retryCount <= maxRetries)
			{
				cout << "Invalid name length! (The length must be less than 30 characters.)" << endl;
				cout << "You have " << (maxRetries - retryCount + 1) << " more attempt(s)." << endl;
				waitForSecond(2);
				continue;
			}
			else
			{
				cout << endl;
				cout << "Maximum invalid attempts reached. Returning to Edit Student Menu..." << endl;
				waitForSecond(2);
				return;
			}
		}
		string formattedName = formatStudentName(newName);
		retryCount = 0;
		string confirm;
		cout << "Change name from '" << studentToEdit->studentName << "' to '" << formattedName << "'? (Y/N): ";
		getline(cin, confirm);
		cout << endl;
		// Yes/No
		if (confirm == "y" || confirm == "Y")
		{
			studentToEdit->studentName = formattedName;
			cout << "Student name updated successfully!" << endl;
			waitForSecond(2);
			return;
		}
		else if (confirm == "n" || confirm == "N")
		{
			cout << "Name change cancelled." << endl;
			waitForSecond(2);
			return;
		}
		else if (confirm.empty())
		{
			retryCount2++;
			if (retryCount2 <= maxRetries)
			{
				cout << "Empty input! Please try again." << endl;
				waitForSecond(2);
			}
			else
			{
				cout << "Maximum empty input attempts reached. Returning to Edit Student Menu..." << endl;
				waitForSecond(2);
				return;
			}
		}
		else
		{
			retryCount2++;
			if (retryCount2 <= maxRetries)
			{
				cout << "Invalid option! Please try again." << endl;
				cout << "You have " << (maxRetries - retryCount2 + 1) << " more attempt(s)." << endl;
				waitForSecond(2);
			}
			else
			{
				cout << "Maximum invalid attempts reached. Returning to Edit Student Menu..." << endl;
				waitForSecond(2);
				return;
			}
		}
	}
}

// Edit students menu -- Edit major
void editStudents_Major(string studentID)
{
	Student *studentToEdit = nullptr;
	for (auto &student : students)
	{
		if (student.studentID == studentID)
		{
			studentToEdit = &student;
			break;
		}
	}

	if (studentToEdit == nullptr)
	{
		cout << "Error: Student with ID " << studentID << " not found!" << endl;
		waitForSecond(2);
		return;
	}

	int retryCount = 0;
	int retryCount2 = 0;
	const int maxRetries = 2;
	while (retryCount <= maxRetries && retryCount2 <= maxRetries)
	{
		clearScreen();
		cout << "Current Student Major: " << studentToEdit->studentMajor << endl;
		string newMajor;
		cout << "Enter new Student Major: ";
		cout << "Enter new Student name: ";
		cin.clear();
		getline(cin, newMajor);
		cout << endl;
		if (newMajor.empty())
		{
			retryCount++;
			if (retryCount <= maxRetries)
			{
				cout << "Major cannot be empty! Please try again." << endl;
				cout << "You have " << (maxRetries - retryCount + 1) << " more attempt(s)." << endl;
				waitForSecond(2);
				continue;
			}
			else
			{
				cout << "Maximum empty input attempts reached. Returning to Edit Student Menu..." << endl;
				waitForSecond(2);
				return;
			}
		}
		if (!checkMajorLength(newMajor))
		{
			retryCount++;
			if (retryCount <= maxRetries)
			{
				cout << "Invalid major length! (The length must be less than 30 characters.)" << endl;
				cout << "You have " << (maxRetries - retryCount + 1) << " more attempt(s)." << endl;
				waitForSecond(2);
				continue;
			}
			else
			{
				cout << "Maximum invalid attempts reached. Returning to Edit Student Menu..." << endl;
				waitForSecond(2);
				return;
			}
		}
		string formattedMajor = formatMajor(newMajor);
		retryCount = 0;
		string confirm;
		cout << "Change major from '" << studentToEdit->studentMajor << "' to '" << formattedMajor << "'? (Y/N): ";
		getline(cin, confirm);
		cout << endl;
		// Yes/No
		if (confirm == "y" || confirm == "Y")
		{
			studentToEdit->studentMajor = formattedMajor;
			cout << "Student Major updated successfully!" << endl;
			waitForSecond(2);
			return;
		}
		else if (confirm == "n" || confirm == "N")
		{
			cout << "Name change cancelled." << endl;
			waitForSecond(2);
			return;
		}
		else if (confirm.empty())
		{
			retryCount2++;
			if (retryCount2 <= maxRetries)
			{
				cout << "Empty input! Please try again." << endl;
				waitForSecond(2);
			}
			else
			{
				cout << "Maximum empty input attempts reached. Returning to Edit Student Menu..." << endl;
				waitForSecond(2);
				return;
			}
		}
		else
		{
			retryCount2++;
			if (retryCount2 <= maxRetries)
			{
				cout << "Invalid option! Please try again." << endl;
				cout << "You have " << (maxRetries - retryCount2 + 1) << " more attempt(s)." << endl;
				waitForSecond(2);
			}
			else
			{
				cout << "Maximum invalid attempts reached. Returning to Edit Student Menu..." << endl;
				waitForSecond(2);
				return;
			}
		}
	}
}

// Edit students menu -- Edit subject list
void editStudents_SubjectList(string studentID) // idk wat happened
{
	clearScreen();

	Student *studentToEdit = nullptr;
	for (auto &student : students)
	{
		if (student.studentID == studentID)
		{
			studentToEdit = &student;
			break;
		}
	}

	if (studentToEdit == nullptr)
	{
		cout << "Error: Student with ID " << studentID << " not found!" << endl;
		waitForSecond(2);
		return;
	}

	int retryCount = 0;
	int retryCount1 = 0;
	int retryCount2 = 0;
	int retryCount3 = 0;
	const int maxRetries = 2;

	while (retryCount <= maxRetries && retryCount1 <= maxRetries && retryCount2 <= maxRetries && retryCount3 <= maxRetries)
	{
		string subjectCode;
		while (true)
		{
			string displayOption;
			clearScreen();
			cout << "The subject list for " << studentToEdit->studentName << " is " << endl;
			cout << "+";
			printLine("-", 14);
			cout << "+";
			printLine("-", 41);
			cout << "+";
			printLine("-", 8);
			cout << "+";
			printLine("-", 7);
			cout << "+" << endl;

			cout << "| " << setw(13) << left << "Subject Code"
				 << "| " << setw(40) << left << "Subject Name"
				 << "| " << setw(7) << left << "Credit"
				 << "| " << setw(6) << left << "Grade"
				 << "|" << endl;

			cout << "+";
			printLine("-", 14);
			cout << "+";
			printLine("-", 41);
			cout << "+";
			printLine("-", 8);
			cout << "+";
			printLine("-", 7);
			cout << "+" << endl;

			for (const auto &subject : studentToEdit->subjectsTaken)
			{
				cout << "| " << setw(13) << subject.subjectCode
					 << "| " << setw(40) << subject.subjectName
					 << "| " << setw(7) << subject.subjectCredits
					 << "| " << setw(6) << subject.subjectGrade << "|" << endl;
			}
			cout << "+";
			printLine("-", 14);
			cout << "+";
			printLine("-", 41);
			cout << "+";
			printLine("-", 8);
			cout << "+";
			printLine("-", 7);
			cout << "+" << endl;

			cout << "System Subject List " << endl;
			cout << "+";
			printLine("-", 14);
			cout << "+";
			printLine("-", 41);
			cout << "+";
			printLine("-", 8);
			cout << "+" << endl;

			cout << "| " << setw(13) << left << "Subject Code"
				 << "| " << setw(40) << left << "Subject Name"
				 << "| " << setw(7) << left << "Credit"
				 << "|" << endl;

			cout << "+";
			printLine("-", 14);
			cout << "+";
			printLine("-", 41);
			cout << "+";
			printLine("-", 8);
			cout << "+" << endl;

			for (const auto &systemsubject : systemsubject)
			{
				cout << "| " << setw(13) << systemsubject.subjectCode
					 << "| " << setw(40) << systemsubject.subjectName
					 << "| " << setw(7) << systemsubject.subjectCredit << "|" << endl;
			}
			cout << "+";
			printLine("-", 14);
			cout << "+";
			printLine("-", 41);
			cout << "+";
			printLine("-", 8);
			cout << "+" << endl;

			cout << "Enter subject code: ";
			getline(cin, subjectCode);
			cout << endl;
			if (subjectCode.empty())
			{
				retryCount1++;
				if (retryCount1 <= maxRetries)
				{
					cout << "Empty input! Please try again." << endl;
					cout << "You have " << (maxRetries - retryCount1 + 1) << " more attempt(s)." << endl;
					waitForSecond(2);
					continue;
				}
				else
				{
					cout << "Maximum empty input attempts reached. Returning to Edit Student Menu..." << endl;
					waitForSecond(2);
					return;
				}
			}

			if (subjectCode.length() != 7)
			{
				cout << "Invalid subject code length! (The length must be exactly 7 characters.)" << endl;
				retryCount++;
				if (retryCount <= maxRetries)
				{
					cout << "You have " << (maxRetries - retryCount + 1) << " more attempt(s)." << endl;
					waitForSecond(2);
					continue;
				}
				else
				{
					cout << "Maximum invalid attempts reached. Returning to Edit Student Menu..." << endl;
					waitForSecond(2);
					return;
				}
			}
			bool isValid = true;
			for (int i = 0; i < 3; i++)
			{
				if (!isupper(subjectCode[i]))
				{
					isValid = false;
					break;
				}
			}
			for (int i = 3; i < 7; i++)
			{
				if (!isdigit(subjectCode[i]))
				{
					isValid = false;
					break;
				}
			}
			if (!isValid)
			{
				cout << "Invalid subject code format! The first 3 characters must be uppercase letters (A-Z), and "
						"the "
						"last "
						"4 characters must be digits (0-9)."
					 << endl;
				retryCount++;
				if (retryCount <= maxRetries)
				{
					cout << "You have " << (maxRetries - retryCount + 1) << " more attempt(s)." << endl;
					waitForSecond(2);
					continue;
				}
				else
				{
					cout << "Maximum invalid attempts reached. Returning to Edit Student Menu..." << endl;
					waitForSecond(2);
					return;
				}
			}
			// Check Student Subject List
			auto studentSubjectList = find_if(studentToEdit->subjectsTaken.begin(), studentToEdit->subjectsTaken.end(),
											  [&subjectCode](const Subject &s)
											  { return s.subjectCode == subjectCode; });
			bool systemSubjectList = false;
			int systemSubjectArray = 0;
			int studentArray = 0;
			for (int i = 0; i < systemsubject.size(); i++)
			{
				if (subjectCode == systemsubject[i].subjectCode)
				{
					systemSubjectList = true;
					systemSubjectArray = i;
				}
			}
			for (int i = 0; i < students.size(); i++)
			{
				if (students[i].studentID == studentID)
				{
					studentArray = i;
				}
			}
			// Case 1
			if (studentSubjectList != studentToEdit->subjectsTaken.end())
			{
				while (retryCount2 <= maxRetries && retryCount3 <= maxRetries)
				{
					cout << "Subject already exists in Student's subject list!" << endl;
					cout << "Current Grade: " << studentSubjectList->subjectGrade << endl;
					const string validGrades[12] = {"A+", "A", "A-", "B+", "B", "B-", "C+", "C", "C-", "D+", "D", "F"};
					cout << "Enter new grade (A+, A, A-, B+, B, B-, C+, C, C-, D+, D, F): ";
					string newGrade;
					getline(cin, newGrade);
					if (newGrade.empty())
					{
						retryCount2++;
						if (retryCount2 <= maxRetries)
						{
							cout << "Empty input! Please try again." << endl;
							waitForSecond(2);
						}
						else
						{
							cout << "Maximum empty input attempts reached. Returning to Edit Student Menu..." << endl;
							waitForSecond(2);
							return;
						}
					}
					if (find(begin(validGrades), end(validGrades), newGrade) != end(validGrades))
					{
						studentSubjectList->subjectGrade = newGrade;
						studentToEdit->calculateGPA();
						cout << "Grade updated successfully!" << endl;
						waitForSecond(2);
						return;
					}
					else
					{
						retryCount2++;
						if (retryCount2 <= maxRetries)
						{
							cout << "Invalid grade! Please try again." << endl;
							cout << "You have " << (maxRetries - retryCount2 + 1) << " more attempt(s)." << endl;
							waitForSecond(2);
							continue;
						}
						else
						{
							cout << "Maximum invalid attempts reached. Returning to Edit Student Menu..." << endl;
							waitForSecond(2);
							return;
						}
					}
					string confirm;
					cout << "Change grade from " << studentSubjectList->subjectGrade << " to " << newGrade << "? (Y/N): ";
					getline(cin, confirm);
					cout << endl;
					// Yes/No
					if (confirm == "y" || confirm == "Y")
					{
						studentSubjectList->subjectGrade = newGrade;
						studentSubjectList->inProgress = false;
						studentToEdit->calculateGPA();
						cout << "Grade updated successfully!";
						waitForSecond(2);
						return;
					}
					else if (confirm == "n" || confirm == "N")
					{
						cout << "Grade change cancelled. No changes made." << endl;
						waitForSecond(2);
						return;
					}
					else if (confirm.empty())
					{
						retryCount3++;
						if (retryCount3 <= maxRetries)
						{
							cout << "Empty input! Please try again." << endl;
							cout << "You have " << (maxRetries - retryCount3 + 1) << " more attempt(s)." << endl;
							waitForSecond(2);
						}
						else
						{
							cout << "Maximum empty input attempts reached. Returning to Edit Student Menu..." << endl;
							waitForSecond(2);
							return;
						}
					}
					else
					{
						retryCount3++;
						if (retryCount3 <= maxRetries)
						{
							cout << "Invalid option! Please try again." << endl;
							cout << "You have " << (maxRetries - retryCount3 + 1) << " more attempt(s)." << endl;
							waitForSecond(2);
							continue;
						}
						else
						{
							cout << "Maximum invalid attempts reached. Returning to Edit Student Menu..." << endl;
							waitForSecond(2);
							return;
						}
					}
				}
			}
			// Case 2
			if (studentSubjectList == studentToEdit->subjectsTaken.end() && systemSubjectList == true)
			{
				while (retryCount2 <= maxRetries && retryCount3 <= maxRetries)
				{
					cout << "Subject already exists in System's subject list!" << endl;
					const string validGrades[13] = {"A+", "A", "A-", "B+", "B", "B-", "C+", "C", "C-", "D+", "D", "F", "--"};
					cout << "Enter new grade (A+, A, A-, B+, B, B-, C+, C, C-, D+, D, F, --): ";
					string newGrade;
					getline(cin, newGrade);
					if (newGrade.empty())
					{
						retryCount2++;
						if (retryCount2 <= maxRetries)
						{
							cout << "Empty input! Please try again." << endl;
							waitForSecond(2);
						}
						else
						{
							cout << "Maximum empty input attempts reached. Returning to Edit Student Menu..." << endl;
							waitForSecond(2);
							return;
						}
					}
					bool checkGrade = false;
					for (int i = 0; i < 13; i++)
					{
						if (validGrades[i] == newGrade)
						{
							checkGrade = true;
							break;
						}
					}
					if (checkGrade == true)
					{
						students[studentArray].addSubject(Subject(systemsubject[systemSubjectArray].subjectCode, systemsubject[systemSubjectArray].subjectName, systemsubject[systemSubjectArray].subjectCredit, newGrade));
						studentToEdit->calculateGPA();
						cout << "Grade updated successfully!" << endl;
						waitForSecond(2);
						return;
					}
					else
					{
						retryCount2++;
						if (retryCount2 <= maxRetries)
						{
							cout << "Invalid grade! Please try again." << endl;
							cout << "You have " << (maxRetries - retryCount2 + 1) << " more attempt(s)." << endl;
							waitForSecond(2);
							continue;
						}
						else
						{
							cout << "Maximum invalid attempts reached. Returning to Edit Student Menu..." << endl;
							waitForSecond(2);
							return;
						}
					}
					string confirm;
					cout << "Change grade from " << studentSubjectList->subjectGrade << " to " << newGrade << "? (Y/N): ";
					getline(cin, confirm);
					cout << endl;
					// Yes/No
					if (confirm == "y" || confirm == "Y")
					{
						studentSubjectList->subjectGrade = newGrade;
						studentSubjectList->inProgress = false;
						studentToEdit->calculateGPA();
						cout << "Grade updated successfully!";
						waitForSecond(2);
						cin.clear();
						return;
					}
					else if (confirm == "n" || confirm == "N")
					{
						cout << "Grade change cancelled. No changes made." << endl;
						waitForSecond(2);
						return;
					}
					else if (confirm.empty())
					{
						retryCount3++;
						if (retryCount3 <= maxRetries)
						{
							cout << "Empty input! Please try again." << endl;
							waitForSecond(2);
						}
						else
						{
							cout << "Maximum empty input attempts reached. Returning to Edit Student Menu..." << endl;
							waitForSecond(2);
							return;
						}
					}
					else
					{
						retryCount3++;
						if (retryCount3 <= maxRetries)
						{
							cout << "Invalid option! Please try again." << endl;
							cout << "You have " << (maxRetries - retryCount3 + 1) << " more attempt(s)." << endl;
							waitForSecond(2);
							continue;
						}
						else
						{
							cout << "Maximum invalid attempts reached. Returning to Edit Student Menu..." << endl;
							waitForSecond(2);
							return;
						}
					}
				}
			}
			// Case 3
			if (studentSubjectList == studentToEdit->subjectsTaken.end() && systemSubjectList == false)
			{
				retryCount = 0;
				retryCount2 = 0;
				retryCount3 = 0;
				string newSubjectName;
				string newSubjectCredit;
				while (retryCount2 <= maxRetries)
				{
					cout << "Enter Subject Name: ";
					getline(cin, newSubjectName);
					if (newSubjectName.empty())
					{
						retryCount2++;
						if (retryCount2 <= maxRetries)
						{
							cout << "Empty input! Please try again." << endl;
							cout << "You have " << (maxRetries - retryCount2 + 1) << " more attempt(s)." << endl;
							waitForSecond(2);
							continue;
						}
						else
						{
							cout << "Maximum empty input attempts reached. Returning to main menu..." << endl;
							waitForSecond(2);
							return;
						}
					}
					if (!checkSubjectNameLength(newSubjectName))
					{
						retryCount2++;
						if (retryCount2 <= maxRetries)
						{
							cout << "Invalid input! Name length must be less than 30 characters." << endl;
							cout << "You have " << (maxRetries - retryCount2 + 1) << " more attempt(s)." << endl;
							waitForSecond(2);
							continue;
						}
						else
						{
							cout << "Maximum invalid input attempts reached. Returning to main menu..." << endl;
							waitForSecond(2);
							return;
						}
					}
					if (!checkSubjectNameUnique(newSubjectName))
					{
						retryCount2++;
						if (retryCount2 <= maxRetries)
						{
							cout << "Invalid input! Subject Name already appear in Subject list" << endl;
							cout << "You have " << (maxRetries - retryCount2 + 1) << " more attempt(s)." << endl;
							waitForSecond(2);
							continue;
						}
						else
						{
							cout << "Maximum invalid input attempts reached. Returning to main menu..." << endl;
							waitForSecond(2);
							return;
						}
					}
					break;
				}
				while (retryCount3 <= maxRetries)
				{
					cout << "Type Subject Credit: ";
					getline(cin, newSubjectCredit);
					if (newSubjectCredit.empty())
					{
						retryCount3++;
						if (retryCount3 <= maxRetries)
						{
							cout << "Empty input! Please try again." << endl;
							cout << "You have " << (maxRetries - retryCount3 + 1) << " more attempt(s)." << endl;
							waitForSecond(2);
							continue;
						}
						else
						{
							cout << "Maximum empty input attempts reached. Returning to main menu..." << endl;
							waitForSecond(2);
							return;
						}
					}
					bool validCredit = true;
					for (char c : newSubjectCredit)
					{
						if (!isdigit(c))
						{
							validCredit = false;
							break;
						}
					}
					if (!validCredit)
					{
						retryCount3++;
						if (retryCount3 <= maxRetries)
						{
							cout << "Invalid input! Credit must be a number." << endl;
							cout << "You have " << (maxRetries - retryCount3 + 1) << " more attempt(s)." << endl;
							waitForSecond(2);
							continue;
						}
						else
						{
							cout << "Maximum empty input attempts reached. Returning to main menu..." << endl;
							waitForSecond(2);
							return;
						}
					}
					if (!checkCreditRange(stoi(newSubjectCredit)))
					{
						retryCount3++;
						if (retryCount3 <= maxRetries)
						{
							cout << "Invalid input! Subject Credit is 2 - 5" << endl;
							cout << "You have " << (maxRetries - retryCount3 + 1) << " more attempt(s)." << endl;
							waitForSecond(2);
							continue;
						}
						else
						{
							cout << "Maximum invalid input attempts reached. Returning to main menu..." << endl;
							waitForSecond(2);
							return;
						}
					}
					break;
				}
				systemsubject.push_back(Systemsubject(subjectCode, formatsubjectName(newSubjectName), stoi(newSubjectCredit)));
				sort(systemsubject.begin(), systemsubject.end(),
					 [](const Systemsubject &a, const Systemsubject &b)
					 { return a.subjectCode < b.subjectCode; });
				cout << "New Subject successfully added. ";
				retryCount2 = 0;
				while (retryCount2 <= maxRetries)
				{
					const string validGrades[13] = {"A+", "A", "A-", "B+", "B", "B-", "C+", "C", "C-", "D+", "D", "F", "--"};
					cout << "Enter new grade (A+, A, A-, B+, B, B-, C+, C, C-, D+, D, F, --): ";
					string newGrade;
					getline(cin, newGrade);
					if (newGrade.empty())
					{
						retryCount2++;
						if (retryCount2 <= maxRetries)
						{
							cout << "Invalid input! Year cannot be empty." << endl;
							cout << "You have " << (maxRetries - retryCount2 + 1) << " more attempt(s)." << endl;
							newGrade.clear();
							waitForSecond(2);
							continue;
						}
						else
						{
							cout << "Maximum invalid input attempts reached. Returning to main menu..." << endl;
							waitForSecond(2);
							return;
						}
					}
					bool checkGrade = false;
					for (int i = 0; i < 13; i++)
					{
						if (validGrades[i] == newGrade)
						{
							checkGrade = true;
							break;
						}
					}
					if (checkGrade)

					{
						students[studentArray].addSubject(Subject(subjectCode, newSubjectName, stoi(newSubjectCredit), newGrade));
						studentToEdit->calculateGPA();
						cout << "Grade updated successfully!" << endl;
						waitForSecond(2);
						return;
					}

					else
					{
						retryCount2++;
						if (retryCount2 <= maxRetries)
						{
							cout << "Invalid grade! Please try again." << endl;
							cout << "You have " << (maxRetries - retryCount2 + 1) << " more attempt(s)." << endl;
							waitForSecond(2);
							continue;
						}
						else
						{
							cout << "Maximum invalid attempts reached. Returning to Edit Student Menu..." << endl;
							waitForSecond(2);
							return;
						}
					}
					string confirm;
					cout << "Change grade from " << studentSubjectList->subjectGrade << " to " << newGrade << "? (Y/N): ";
					getline(cin, confirm);
					cout << endl;
					// Yes/No
					if (confirm == "y" || confirm == "Y")
					{
						studentSubjectList->subjectGrade = newGrade;
						studentSubjectList->inProgress = false;
						studentToEdit->calculateGPA();
						cout << "Grade updated successfully!";
						waitForSecond(2);
						return;
					}
					else if (confirm == "n" || confirm == "N")
					{
						cout << "Grade change cancelled. No changes made." << endl;
						waitForSecond(2);
						return;
					}
					else if (confirm.empty())
					{
						retryCount3++;
						if (retryCount3 <= maxRetries)
						{
							cout << "Empty input! Please try again." << endl;
							waitForSecond(2);
						}
						else
						{
							cout << "Maximum empty input attempts reached. Returning to Edit Student Menu..." << endl;
							waitForSecond(2);
							return;
						}
					}
					else
					{
						retryCount3++;
						if (retryCount3 <= maxRetries)
						{
							cout << "Invalid option! Please try again." << endl;
							cout << "You have " << (maxRetries - retryCount3 + 1) << " more attempt(s)." << endl;
							waitForSecond(2);
							continue;
						}
						else
						{
							cout << "Maximum invalid attempts reached. Returning to Edit Student Menu..." << endl;
							waitForSecond(2);
							return;
						}
					}
				}
			}
		}
	}
}

// Add or delete (new) students
void addDeleteStudents() // Not completed (Completed)
{
	checkLoaded();
	if (!dataLoaded)
		return;
	bool deleteOnly = false;
	if (students.size() >= 100)
	{
		cout << "Mazimum student Limit (100) reached. Cannot add new student." << endl;
		cout << "You can only delete students" << endl;
		waitForSecond(2);
		deleteOnly = true;
	}
	int retryCount = 0;
	int retryCount2 = 0;
	int retryCount3 = 0;
	int retryCount4 = 0;
	int retryCount5 = 0;
	const int maxRetries = 2;
	while (retryCount <= maxRetries && retryCount2 <= maxRetries && retryCount3 <= maxRetries && retryCount4 <= maxRetries && retryCount5 <= maxRetries)
	{
		clearScreen();
		displayStudentRecord(students);
		if (deleteOnly)
		{
			cout << "Enter student ID to delete (Type \'quit\' to return main menu): ";
		}
		else
		{
			cout << "Enter the Student ID to delete or enter \'add\' to add new student (Type \'quit\' to return main menu): ";
		}
		string studentID;
		getline(cin, studentID);
		cout << endl;
		studentID = toUpper(studentID);
		studentID.erase(remove_if(studentID.begin(), studentID.end(), ::isspace), studentID.end());
		if (studentID.empty())
		{
			retryCount++;

			if (retryCount <= maxRetries)
			{
				cout << "Invalid input! Name cannot be empty." << endl;
				cout << "You have " << (maxRetries - retryCount + 1) << " more attempt(s)." << endl;
				waitForSecond(2);
				continue;
			}
			else
			{
				cout << "Maximum invalid input attempts reached. Returning to main menu..." << endl;
				waitForSecond(2);
				return;
			}
		}
		if (studentID == "quit")
		{
			cout << "Returning to main menu..." << endl;
			waitForSecond(2);
			return;
		}
		if (checkStudentID(studentID))
		{
			clearScreen();
			Student *studentToEdit = nullptr;
			for (auto &student : students)
			{
				if (student.studentID == studentID)
				{
					studentToEdit = &student;
					break;
				}
			}

			if (studentToEdit == nullptr)
			{
				cout << "Error: Student with ID " << studentID << " not found!" << endl;
				waitForSecond(2);
				return;
			}
			vector<Student> listStudents;
			if (studentToEdit != nullptr)
			{
				listStudents.push_back(*studentToEdit);
			}
			displayStudentRecord(listStudents);
			cout << endl;
			cout << "Are you sure to delete this student? (Y/N): ";
			string confirm;
			getline(cin, confirm);
			cout << endl;
			// Yes/No
			if (confirm == "y" || confirm == "Y")
			{
				students.erase(remove_if(students.begin(), students.end(),
										 [&studentID](const Student &student)
										 { return student.studentID == studentID; }),
							   students.end());
				cout << "Student deleted successfully!" << endl;
				waitForSecond(2);
				return;
			}
			else if (confirm == "n" || confirm == "N")
			{
				cout << "Student deletion cancelled." << endl;
				waitForSecond(2);
				return;
			}
			else if (confirm.empty())
			{
				retryCount2++;
				if (retryCount2 <= maxRetries)
				{
					cout << "Empty input! Please try again." << endl;
					waitForSecond(2);
				}
				else
				{
					cout << "Maximum empty input attempts reached. Returning to Edit Student Menu..." << endl;
					waitForSecond(2);
					return;
				}
			}
			return;
		}
		else if (!deleteOnly)
		{
			string studentName;
			string cohortYear;
			string studentMajor;
			while (true)
			{
				if (studentName.empty())
				{
					while (retryCount2 <= maxRetries)
					{
						clearScreen();
						cout << "*** Adding new student ***" << endl;
						cout << "Enter Student Name: ";
						getline(cin, studentName);
						cout << endl;
						if (studentName.empty())
						{
							retryCount2++;
							if (retryCount2 <= maxRetries)
							{
								cout << "Invalid input! Name cannot be empty." << endl;
								cout << "You have " << (maxRetries - retryCount2 + 1) << " more attempt(s)." << endl;
								waitForSecond(2);
							}
							else
							{
								cout << "Maximum invalid input attempts reached. Returning to main menu..." << endl;
								waitForSecond(2);
								cout << endl;
								return;
							}
							studentName.clear();
							continue;
						}
						if (!checkSubjectNameLength(studentName))
						{
							retryCount2++;
							if (retryCount2 <= maxRetries)
							{
								cout << "Invalid input! Name length must be less than 30 characters." << endl;
								cout << "You have " << (maxRetries - retryCount2 + 1) << " more attempt(s)." << endl;
								waitForSecond(2);
								continue;
							}
							else
							{
								cout << "Maximum invalid input attempts reached. Returning to main menu..." << endl;
								waitForSecond(2);
								return;
							}
							studentName.clear();
							continue;
						}
						break;
					}
					if (retryCount2 > maxRetries)
					{
						cout << "Maximum invalid input attempts reached. Returning to main menu..." << endl;
						waitForSecond(2);
						return;
					}
					studentName = formatStudentName(studentName);
				}
				if (cohortYear.empty())
				{
					while (retryCount3 <= maxRetries)
					{
						clearScreen();
						cout << "*** Adding new student ***" << endl;
						cout << "Student Name: " << studentName << endl;
						cout << "Enter Student\'s Cohort Year (2021 - 2024): ";
						getline(cin, cohortYear);
						cout << endl;
						if (cohortYear.empty())
						{
							retryCount3++;
							if (retryCount3 <= maxRetries)
							{
								cout << "Invalid input! Year cannot be empty." << endl;
								cout << "You have " << (maxRetries - retryCount3 + 1) << " more attempt(s)." << endl;
								cohortYear.clear();
								waitForSecond(2);
								continue;
							}
							else
							{
								cout << "Maximum invalid input attempts reached. Returning to main menu..." << endl;
								waitForSecond(2);
								return;
							}
						}
						bool validYear = true;
						for (char c : cohortYear)
						{
							if (!isdigit(c))
							{
								validYear = false;
								break;
							}
						}
						if (!validYear)
						{
							retryCount3++;
							if (retryCount3 <= maxRetries)
							{
								cout << "Invalid input! Year must be a number." << endl;
								cout << "You have " << (maxRetries - retryCount3 + 1) << " more attempt(s)." << endl;
								waitForSecond(2);
								continue;
							}
							else
							{
								cout << "Maximum invalid input attempts reached. Returning to main menu..." << endl;
								waitForSecond(2);
								return;
							}
						}
						if (!checkCohortYear(stoi(cohortYear)))
						{
							retryCount3++;
							if (retryCount3 <= maxRetries)
							{
								cout << "Invalid input! Year must be between 2021 and 2024." << endl;
								cout << "You have " << (maxRetries - retryCount3 + 1) << " more attempt(s)." << endl;
								waitForSecond(2);
								continue;
							}
							else
							{
								cout << "Maximum invalid input attempts reached. Returning to main menu..." << endl;
								waitForSecond(2);
								return;
							}
						}
						break;
					}
					continue;
				}
				if (studentMajor.empty())
				{
					while (retryCount4 <= maxRetries)
					{
						clearScreen();
						cout << "*** Adding new student ***" << endl;
						cout << "Student Name: " << studentName << endl;
						cout << "Cohort Year: " << cohortYear << endl;
						cout << "Enter Student Major: ";
						getline(cin, studentMajor);
						cout << endl;
						if (studentMajor.empty())
						{
							retryCount4++;
							if (retryCount4 <= maxRetries)
							{
								cout << "Invalid input! Major cannot be empty." << endl;
								cout << "You have " << (maxRetries - retryCount4 + 1) << " more attempt(s)." << endl;
								waitForSecond(2);
								continue;
							}
							else
							{
								cout << "Maximum invalid input attempts reached. Returning to main menu..." << endl;
								waitForSecond(2);
								return;
							}
						}
						if (!checkMajorLength(studentMajor))
						{
							retryCount4++;
							if (retryCount4 <= maxRetries)
							{
								cout << "Invalid input! Major length must be less than 30 characters." << endl;
								cout << "You have " << (maxRetries - retryCount4 + 1) << " more attempt(s)." << endl;
								waitForSecond(2);
								continue;
							}
							else
							{
								cout << "Maximum invalid input attempts reached. Returning to main menu..." << endl;
								waitForSecond(2);
								return;
							}
						}
						break;
					}
					continue;
				}
				if (!studentName.empty() && !cohortYear.empty() && !studentMajor.empty())
				{
					clearScreen();
					string newStudentID = generateStudentID(stoi(cohortYear));
					cout << "*** Adding new student ***" << endl;
					cout << "Student Name: " << studentName << endl;
					cout << "Cohort Year: " << cohortYear << endl;
					cout << "Student Major: " << studentMajor << endl;
					cout << "Student ID: " << newStudentID << endl;
					cout << "Are you sure to add this student? (Y/N): ";
					string confirm;
					getline(cin, confirm);
					cout << endl;
					// Yes/No
					if (confirm == "y" || confirm == "Y")
					{
						students.push_back(Student(studentName, newStudentID, studentMajor, stoi(cohortYear)));
						cout << "Student added successfully!" << endl;
						waitForSecond(2);
						return;
					}
					else if (confirm == "n" || confirm == "N")
					{
						cout << "Cancel to add new Student." << endl;
						waitForSecond(2);
						return;
					}
					else if (confirm.empty())
					{
						retryCount5++;
						if (retryCount5 <= maxRetries)
						{
							cout << "Empty input! Please try again." << endl;
							cout << "You have " << (maxRetries - retryCount5 + 1) << " more attempt(s)." << endl;
							waitForSecond(2);
							continue;
						}
						else
						{
							cout << "Maximum empty input attempts reached. Returning to main menu..." << endl;
							waitForSecond(2);
							return;
						}
					}
					else
					{
						retryCount4++;
						if (retryCount4 <= maxRetries)
						{
							cout << "Invalid option! Please try again." << endl;
							cout << "You have " << (maxRetries - retryCount4 + 1) << " more attempt(s)." << endl;
							waitForSecond(2);
							continue;
						}
						else
						{
							cout << "Maximum invalid attempts reached. Returning to main menu..." << endl;
							waitForSecond(2);
							return;
						}
					}
				}
			}
		}
		else if (deleteOnly)
		{
			retryCount2++;
			if (retryCount2 <= maxRetries)
			{
				cout << "Invalid student ID! Please try again." << endl;
				cout << "You have " << (maxRetries - retryCount2 + 1) << " more attempt(s)." << endl;
				waitForSecond(2);
				continue;
			}
			else
			{
				cout << "Maximum invalid attempts reached. Returning to main menu..." << endl;
				waitForSecond(2);
				return;
			}
		}
	}
}

// Generate transcript for students
void generateTranscript()
{
	checkLoaded();
	if (!dataLoaded)
		return;
	string studentID;
	int retryCount = 0;
	while (true)
	{
		clearScreen();
		displayStudentRecord(students);
		cout << "Enter the Student ID (Type \'quit\' to return main menu): ";
		getline(cin, studentID);
		studentID.erase(remove_if(studentID.begin(), studentID.end(), ::isspace), studentID.end());
		cout << endl;
		if (studentID.empty())
		{
			retryCount++;
			if (retryCount <= 2)
			{
				cout << "Invalid input! Student ID cannot be empty." << endl;
				cout << "You have " << (2 - retryCount + 1) << " more attempt(s)." << endl;
				waitForSecond(2);
				continue;
			}
			else
			{
				cout << "Maximum invalid input attempts reached. Returning to main menu..." << endl;
				waitForSecond(2);
				return;
			}
		}
		if (studentID == "quit")
		{
			cout << "Returning to main menu..." << endl;
			waitForSecond(2);
			return;
		}
		break;
	}
	Student *targetStudent = nullptr;
	for (auto &student : students)
	{
		if (student.studentID == studentID)
		{
			targetStudent = &student;
			break;
		}
	}

	if (targetStudent == nullptr)
	{
		cout << "Error: Student with ID " << studentID << " not found!" << endl;
		waitForSecond(1);
		return;
	}

	clearScreen();

	cout << "Name      : " << targetStudent->studentName << endl;
	cout << "Student ID: " << targetStudent->studentID << endl;
	cout << "Major     : " << targetStudent->studentMajor << endl;
	cout << "Year      : " << targetStudent->studentYear << endl;
	cout << endl;
	cout << "Subject" << setw(52) << right << "Credit  " << "Grade" << endl;
	cout << "----------------------------------------------------------------" << endl;

	sort(targetStudent->subjectsTaken.begin(), targetStudent->subjectsTaken.end(),
		 [](const Subject &a, const Subject &b)
		 { return a.subjectCode < b.subjectCode; });
	int creditsAttained = 0;
	for (const auto &subject : targetStudent->subjectsTaken)
	{
		cout << subject.subjectCode << " " << left << setw(40) << subject.subjectName << right << setw(4)
			 << subject.subjectCredits << setw(7) << " " << left << subject.subjectGrade << endl;

		if (subject.subjectGrade >= "A" && subject.subjectGrade <= "D")
		{
			creditsAttained += subject.subjectCredits;
		}
	}

	cout << "----------------------------------------------------------------" << endl;
	cout << "Credits attained: " << creditsAttained << endl;
	if (targetStudent->studentGPA == -1.00)
	{
		cout << "GPA: " << fixed << setprecision(2) << "N/A" << endl;
	}
	else
	{
		cout << "GPA: " << fixed << setprecision(2) << targetStudent->studentGPA << endl;
	}
	cout << "Press Enter to continue...";
	cin.get();
}

// Credits and exit
void creditsAndExit()
{
	string exitOption = "n";
	cout << "Are you sure you want to exit? (Y/N): ";
	getline(cin, exitOption);
	cout << endl;
	// Yes/No
	if (exitOption == "y" || exitOption == "Y")
	{
		cout << left << setw(25) << "Group members: " << setw(20) << "Student ID: " << setw(20)
			 << "Tutorial Group: " << endl;
		cout << left << setw(25) << "XXXXX" << setw(20) << "YYYY" << setw(20) << "ZZZ" << endl;
		cout << left << setw(25) << "XXXXX" << setw(20) << "YYYY" << setw(20) << "ZZZ" << endl;
		cout << left << setw(25) << "XXXXX" << setw(20) << "YYYY" << setw(20) << "ZZZ" << endl;
		cout << left << setw(25) << "XXXXX" << setw(20) << "YYYY" << setw(20) << "ZZZ" << endl;
		cout << left << setw(25) << "XXXXX" << setw(20) << "YYYY" << setw(20) << "ZZZ" << endl;
		cout << left << setw(25) << "XXXXX" << setw(20) << "YYYY" << setw(20) << "ZZZ" << endl;
		waitForSecond(1);
		exit(0);
	}
	else if (exitOption == "n" || exitOption == "N")
	{
		cout << "Returning to main menu..." << endl;
		waitForSecond(1);
	}
	else if (exitOption.empty())
	{
		cout << "Empty input! Please try again." << endl;
		waitForSecond(1);
	}
	else
	{
		cout << "Invalid option! Returning to main menu..." << endl;
		waitForSecond(1);
	}
}

// THE MAIN MENU
void mainMenu()
{
	while (true)
	{
		clearScreen();
		cout << "Welcome Message designed by Group 8" << endl;
		cout << "*** SMS Main Menu ***" << endl;
		cout << "[1] Load Starting Data" << endl;
		cout << "[2] Show Student Records" << endl;
		cout << "[3] Add/Delete Students" << endl;
		cout << "[4] Edit Students" << endl;
		cout << "[5] Generate Transcript" << endl;
		cout << "[6] Credits and Exit" << endl;
		cout << "*********************" << endl;
		cout << "Option (1 - 6): ";
		string mainMenuOption;
		getline(cin, mainMenuOption);
		cout << endl;
		if (mainMenuOption.empty())
		{
			cout << "Empty input! Please try again." << endl;
			waitForSecond(1);
			continue;
		}
		if (mainMenuOption == "1")
		{
			loadStartingData();
		}
		if (mainMenuOption == "2")
		{
			showStudentRecords();
		}
		if (mainMenuOption == "3")
		{
			addDeleteStudents();
		}
		if (mainMenuOption == "4")
		{
			editStudents_entrance();
		}
		if (mainMenuOption == "5")
		{
			generateTranscript();
		}
		if (mainMenuOption == "6")
		{
			creditsAndExit();
		}
		if (mainMenuOption != "1" && mainMenuOption != "2" && mainMenuOption != "3" && mainMenuOption != "4" &&
			mainMenuOption != "5" && mainMenuOption != "6")
		{
			cout << "Invalid option! Please try again." << endl;
			waitForSecond(1);
		}
	}
}

// Noob main() function
int main()
{
	mainMenu();
	return 0;
}
