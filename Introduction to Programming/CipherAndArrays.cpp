#include <iostream>
using namespace std;

// Caesar cipher
int codeTheText(char* theMainText, char* theCodedText, int step) {
    int i = 0;

    while (theMainText[i] != '\0') {
        char ch = theMainText[i];

        if (ch >= 'a' && ch <= 'z') {
            theCodedText[i] = ((ch - 'a' + step + 26) % 26) + 'a';
        } else if (ch >= 'A' && ch <= 'Z') {
            theCodedText[i] = ((ch - 'A' + step + 26) % 26) + 'A';
        } else {
            theCodedText[i] = ch;
        }
        i++;
    }
    theCodedText[i] = '\0';
    return 0;
}

// Check if second_array is a subset of first_array
bool isSubset(int* first_array, int* second_array, int first_size, int second_size) {
    for (int i = 0; i < second_size; i++) {
        bool found = false;
        for (int j = 0; j < first_size; j++) {
            if (second_array[i] == first_array[j]) {
                found = true;
                break;
            }
        }
        if (!found) return false;
    }
    return true;
}

void printArray(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    cout << "Task 1: Enter text to encode: ";
    char theMainText[3100];
    char theCodedText[3100];
    cin.getline(theMainText, 3100);

    int step;
    cout << "Enter shift step: ";
    cin >> step;

    codeTheText(theMainText, theCodedText, step);
    cout << "Original text: " << theMainText << endl;
    cout << "Coded text: " << theCodedText << endl;

    cout << "\nTask 2: " << endl;

    int A[] = { 1,2,3,4,5,6,7,8,9,10 };
    int B[] = { 2,3,5,7 };

    int fir_size = sizeof(A) / sizeof(A[0]);
    int sec_size = sizeof(B) / sizeof(B[0]);

    if (isSubset(A, B, fir_size, sec_size)) {
        cout << "B is a subset of A." << endl;
    } else {
        cout << "B is not a subset of A." << endl;
    }

    cout << "\nTask 3: " << endl;

    int f_size, s_size;
    cout << "Enter size of first array: ";
    cin >> f_size;
    cout << "Enter size of second array: ";
    cin >> s_size;

    int* second_A = new int[f_size];
    int* second_B = new int[s_size];

    cout << "Enter elements for first array: ";
    for (int i = 0; i < f_size; i++) {
        cin >> second_A[i];
    }

    cout << "Enter elements for second array: ";
    for (int i = 0; i < s_size; i++) {
        cin >> second_B[i];
    }

    cout << "Common elements: ";
    for (int i = 0; i < f_size; i++) {
        for (int j = 0; j < s_size; j++) {
            if (second_A[i] == second_B[j]) {
                cout << second_A[i] << " ";
                break;
            }
        }
    }

    cout << "\nAll elements:\nFirst: ";
    printArray(second_A, f_size);
    cout << "Second: ";
    printArray(second_B, s_size);

    delete[] second_A;
    delete[] second_B;

    return 0;
}
