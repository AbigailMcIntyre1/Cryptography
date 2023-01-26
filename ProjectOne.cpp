// Abigail Spencer
// Caesar Cipher encryption and decryption
// Due: 02/01/2023

#include <iostream>
#include <ctype.h>

using namespace std;

const int ARRAY_SIZE = 1000;

void encryption();
void decryption();

int main() {
    int userChoice = 0;

    while (userChoice != 3) 
    {
        cout << "------------------- CAESAR CIPHER -------------------" << endl << endl;

        cout << "Encryption: press 1" << endl << "Decryption: press 2" << endl << "Exit: press 3" << endl << endl << "Enter your selection: ";
        cin >> userChoice;

        if (userChoice == 1) {
            encryption();
        } else if (userChoice == 2) {
            decryption();
        }
    }
}

// **************************************** ENCRYPTION ****************************************************************
void encryption() {

    int keyValue = 0;
    char userText[ARRAY_SIZE];

    for (int i = 0; i < ARRAY_SIZE; i++) {  // fill in the array with * since the user won't be using that and we have a char to stop at
        userText[i] = '*';
    }

    cout << endl << "--- Encryption ---" << endl << endl << "(please note that no special characters will be carried over)" << endl << endl;

    while (keyValue < 1 || keyValue > 25) {
        cout << "Please enter the key (any value between 1-25): ";
        cin >> keyValue;
    }

    cout << endl << "Please enter the text to be encrypted: ";
    cin.ignore();
    cin.getline(userText, sizeof(userText));

    cout << endl << endl << "MESSAGE:" << endl;

    int charCounter = 0;
    int ascii;

    for (int i = 0; i < ARRAY_SIZE; i++) {
        if (userText[i] != '*' && !isspace(userText[i]) && userText[i] != '\0' && userText[i] != '.' && userText[i] != '\r' && userText[i] != '\n') {

            ascii = static_cast<int>(tolower(userText[i])) + keyValue;
            ascii = ((ascii - 'a') % 26) + 'a';
            userText[i] = static_cast<char>(ascii);

            cout << char(toupper(userText[i]));

            charCounter++;
        }

        if (charCounter == 5 && !isspace(userText[i]) && userText[i] != '\0' && userText[i] != '.' && userText[i] != '\r' && userText[i] != '\n') {
            cout << "  ";
            charCounter = 0;
        }
    }

    cout << endl << endl;
}
// ********************************************************************************************************************

// **************************************** DECRYPTION ****************************************************************
void decryption() {

    int keyValue = 0;
    char userText[ARRAY_SIZE];

    for (int i = 0; i < ARRAY_SIZE; i++) {  // fill in the array with * since the user won't be using that and we have a char to stop at
        userText[i] = '*';
    }

    cout << endl << "--- Decryption ---" << endl << endl << "(please note that no special characters will be carried over)" << endl << endl;

    while (keyValue < 1 || keyValue > 25) {
        cout << "Please enter the key (any value between 1-25): ";
        cin >> keyValue;
    }

    cout << endl << "Please enter the text to be decrypted: ";
    cin.ignore();
    cin.getline(userText, sizeof(userText));

    cout << endl << endl << "MESSAGE:" << endl;

    int charCounter = 0;
    int ascii;

    for (int i = 0; i < ARRAY_SIZE; i++) {

        // there shouldn't be any special characters but just in case
        if (userText[i] != '*' && !isspace(userText[i]) && userText[i] != '\0' && userText[i] != '.' && userText[i] != '\r' && userText[i] != '\n') {

            ascii = static_cast<int>(tolower(userText[i])) - 'a';
            ascii = ((ascii + 26 - keyValue) % 26) + 'a';
            userText[i] = static_cast<char>(ascii);

            cout << userText[i];

            charCounter++;
        }

        if (charCounter == 5 && !isspace(userText[i]) && userText[i] != '\0' && userText[i] != '.' && userText[i] != '\r' && userText[i] != '\n') {
            cout << " ";
            charCounter = 0;
        }
    }

    cout << endl << endl;
}
// ********************************************************************************************************************