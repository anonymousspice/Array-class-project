/* 
   Group Members: [AARON MKANDAWIRE (BIS/24/ODL/094)]
   
   Design Decisions:
   - Names live in a separate 1D string array, parallel to the 2D marks array.
   - Totals are kept in a separate 1D integer array.
   - Pointer notation (*(*(m + i) + j)) is used in the display function as required.
*/
#include <iostream>
#include <string>

using namespace std;

// Naming constants
const int NUM_STUDENTS = 6;
const int NUM_TESTS = 4;

// Function prototypes
void calculateTotals(int marks[][NUM_TESTS], int totals[], int rows);
void displayStudents(string names[], int marks[][NUM_TESTS], int totals[], int rows);
void rankStudents(string names[], int marks[][NUM_TESTS], int totals[], int rows);
void searchStudent(string names[], int marks[][NUM_TESTS], int totals[], int rows);
void listAboveLimit(string names[], int totals[], int rows);




int main() {
    //Storing students names,marks
    string names[NUM_STUDENTS] = {"Chisomo", "Tadala", "Mphatso", "Yamikani", "Thoko", "Kondwani"};
    
    int marks[NUM_STUDENTS][NUM_TESTS] = {
        {18, 22, 15, 20},
        {24, 20, 23, 25},
        {10, 14, 12,  9},
        {20, 17, 19, 16},
        {13, 21, 18, 22},
        {8, 12, 15, 11}
    };
    
    int totals[NUM_STUDENTS] = {0};

    //Calculating total marks for the students
    calculateTotals(marks, totals, NUM_STUDENTS);

    // Displaying student records 
    cout << "=== INITIAL STUDENT RECORDS ===" << endl;
    displayStudents(names, marks, totals, NUM_STUDENTS);

    // Ranking the students totals from Highest to Lowest
    rankStudents(names, marks, totals, NUM_STUDENTS);
    cout << "\n=== RANKED STUDENT RECORDS (Highest to Lowest) ===" << endl;
    displayStudents(names, marks, totals, NUM_STUDENTS);

    //Searching for a student by name
    cout << "\n=== SEARCH FOR A STUDENT ===" << endl;
    searchStudent(names, marks, totals, NUM_STUDENTS);

    //Listing students above limit
    cout << "\n=== FILTER STUDENTS BY TOTAL MARK ===" << endl;
    listAboveLimit(names, totals, NUM_STUDENTS);

    return 0;
}

//Calculating the total mark for every student
void calculateTotals(int marks[][NUM_TESTS], int totals[], int rows) {
    for (int i = 0; i < rows; i++) {
        totals[i] = 0;
        for (int j = 0; j < NUM_TESTS; j++) {
            totals[i] += marks[i][j];
        }
    }
}

//Displaying records using array pointer notation
void displayStudents(string names[], int marks[][NUM_TESTS], int totals[], int rows) {
    cout << "Name\t\tTest 1\tTest 2\tTest 3\tTest 4\tTotal" << endl;
    cout << "-----------------------------------------------------------" << endl;
    for (int i = 0; i < rows; i++) {
        cout << names[i] << "\t\t";
        for (int j = 0; j < NUM_TESTS; j++) {
            // Using pointer notation
            cout << *(*(marks + i) + j) << "\t";
        }
        cout << totals[i] << endl;
    }
}

// Ranking students using Bubble Sort
void rankStudents(string names[], int marks[][NUM_TESTS], int totals[], int rows) {
    for (int i = 0; i < rows - 1; i++) {
        for (int j = 0; j < rows - i - 1; j++) {
            if (totals[j] < totals[j + 1]) { // Descending order
            
                // Swap totals
                int tempTotal = totals[j];
                totals[j] = totals[j + 1];
                totals[j + 1] = tempTotal;

                // Swap names
                string tempName = names[j];
                names[j] = names[j + 1];
                names[j + 1] = tempName;

                // Swap individual test marks across the 2D array row
                for (int k = 0; k < NUM_TESTS; k++) {
                    int tempMark = marks[j][k];
                    marks[j][k] = marks[j + 1][k];
                    marks[j + 1][k] = tempMark;
                }
            }
        }
    }
}

//Searching for a student by name
void searchStudent(string names[], int marks[][NUM_TESTS], int totals[], int rows) {
    string searchName;
    cout << "Enter student name to search: ";
    cin >> searchName;

    bool found = false;
    for (int i = 0; i < rows; i++) {
        if (names[i] == searchName) {
            found = true;
            cout << "Found! " << names[i] << " is at Rank " << (i + 1) 
                 << " with marks: ";
            for (int j = 0; j < NUM_TESTS; j++) {
                cout << marks[i][j] << " ";
            }
            cout << "| Total: " << totals[i] << endl;
            break;
        }
    }
    if (!found) {
        cout << "Student '" << searchName << "' does not exist in the record." << endl;
    }
}

//Listing every student whose total is above limit
void listAboveLimit(string names[], int totals[], int rows) {
    int limit;
    cout << "Enter the total mark limit: ";
    cin >> limit;

    bool anyMatch = false;
    cout << "Students with total above " << limit << ":" << endl;
    for (int i = 0; i < rows; i++) {
        if (totals[i] > limit) {
            cout << "- " << names[i] << " (Total: " << totals[i] << ")" << endl;
            anyMatch = true;
        }
    }
    if (!anyMatch) {
        cout << "Nobody qualifies." << endl;
    }
}
