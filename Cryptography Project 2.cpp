// Abigail Spencer
// Project Two - due 02/15/2023
// Vigenère Cipher Encryption and Decryption
// Decryption is based on Friedman's method

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

string encryption();
string decryption();
string getActualEncryptionKey(string, string);
void writeResultsToFile(string);
void displayResultsOnScreen(string);

// ---------------------------------------------------------------------------------------------------------------

int main()
{
    int optionSelect = 0;
    int displaySelect = 0;
    string encryptedText;
    string decryptedText;

    while (optionSelect != 3) {
        cout << "------------------- VIGENERE CIPHER -------------------" << endl << endl;

        cout << "Encryption: press 1" << endl << "Decryption: press 2" << endl << "Exit: press 3" << endl << endl << "Enter your selection: ";
        cin >> optionSelect;

        if (optionSelect == 1) {
            encryptedText = encryption();

            if (encryptedText != "Error :(") {

                cout << endl << "Encryption complete! Would you like to display the text to the screen or write the results to a file?" << endl << endl;
                cout << "File: press 1" << endl << "Screen: press 2" << endl << endl << "Enter your selection: ";
                cin >> displaySelect;

                while (displaySelect != 1 && displaySelect != 2) {
                    cout << "Please select 1 for file or 2 for screen: ";
                    cin >> displaySelect;
                }

                if (displaySelect == 1) {
                    writeResultsToFile(encryptedText);
                }
                else {
                    displayResultsOnScreen(encryptedText);
                }
            }

            cout << endl << "-------------------------------------------------------" << endl << endl;
        }
        else if (optionSelect == 2) {
            decryptedText = decryption();

            if (decryptedText != "Error :(") {
                cout << endl << "Would you like to display the text to the screen or write the results to a file?" << endl << endl;
                cout << "File: press 1" << endl << "Screen: press 2" << endl << endl << "Enter your selection: ";
                cin >> displaySelect;

                while (displaySelect != 1 && displaySelect != 2) {
                    cout << "Please select 1 for file or 2 for screen: ";
                    cin >> displaySelect;
                }

                if (displaySelect == 1) {
                    writeResultsToFile(decryptedText);
                }
                else {
                    displayResultsOnScreen(decryptedText);
                }
            }
        }
    }

    if (optionSelect == 3) {
        cout << endl << "-------------------------------------------------------" << endl << endl;
    }
}

// ---------------------------------------------------------------------------------------------------------------

string decryption() {

    string userFileName;
    string line;
    string temp;
    string allLines;
    string keyword;
    string fixedDecryptionKey;
    string decryptedText;
    string displayText;
    ifstream userFile;
    int keywordLength;
    int charFrequencies[26];
    int numKeywordCharsFound = 0;
    int position = 0;
    int startingPosition = 0;
    int userChoice = 9;
    int displaySelect = 9;
    double indexOfCoincedence = 0;
    bool manualKeyword = false;
    char alphabet[26] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };

    // initialize frequencies array to 0
    for (int i = 0; i < 26; i++) {
        charFrequencies[i] = 0;
    }

    cout << endl << "--- Decryption ---" << endl << endl;
    cout << "Please enter the name of the file you want to decrypt (with extention): ";
    cin >> userFileName;
    userFile.open(userFileName);

    if (userFile.is_open()) {

        // get the text from the file
        while (getline(userFile, line)) {
            allLines += line;
        }
        userFile.close();

        // remove special characters (just in case)
        for (int i = 0; i < allLines.size(); ++i) {

            if ((allLines[i] >= 'a' && allLines[i] <= 'z') || (allLines[i] >= 'A' && allLines[i] <= 'Z')) {
                temp = temp + allLines[i];
            }
        }

        allLines = temp;

        // count character frequencies
        for (int i = 0; i < allLines.size(); i++) {
            charFrequencies[static_cast<int>(tolower(allLines[i])) - 'a']++;
        }

        // display the character frequencies
        cout << endl << "Overall Character Frequencies of the Input Text:" << endl << endl;

        int charCount = 0;
        for (int i = 0; i < 26; i++) {

            // make them into rows
            if (charCount == 4) {
                charCount = 0;
                cout << endl;
            }

            // evenly space them out
            if (charFrequencies[i] >= 100) {
                cout << alphabet[i] << ": " << charFrequencies[i] << "  ";
            } 
            else if (charFrequencies[i] >= 10) {
                cout << alphabet[i] << ": " << charFrequencies[i] << "   ";
            }
            else {
                cout << alphabet[i] << ": " << charFrequencies[i] << "    ";
            }

            charCount++;
        }

        cout << endl << endl;

        // calculate index of coincedence
        for (int i = 0; i < 26; i++) {
            indexOfCoincedence += ((float)charFrequencies[i] * ((float)charFrequencies[i] - 1.0)) / ((float)allLines.size() * ((float)allLines.size() - 1.0));
        }

        cout << "The index of coincedence is: " << indexOfCoincedence << endl << endl;
        
        // find the length of the keyword
        keywordLength = (0.027 * allLines.size()) / (((allLines.size() - 1) * indexOfCoincedence) - (0.038 * allLines.size()) + 0.065);
        keywordLength += 1;         // round it up
        cout << "The estimated keyword length is: " << keywordLength << endl << endl << "---------------------------";

        // loop
        while (userChoice != 3) {

            userChoice = 0;

            if (!manualKeyword) {

                // find keyword
                while (numKeywordCharsFound < keywordLength) {

                    // clear frequency table
                    for (int i = 0; i < 26; i++) {
                        charFrequencies[i] = 0;
                    }

                    // get frequencies
                    while (position < allLines.size()) {

                        charFrequencies[static_cast<int>(tolower(allLines[position])) - 'a']++; // add it to the frequency table
                        position += keywordLength;
                    }

                    // display the character frequencies
                    cout << endl << endl << "Character Frequencies of " << numKeywordCharsFound + 1 << endl << endl;

                    int charCount = 0;
                    for (int i = 0; i < 26; i++) {

                        // make into rows
                        if (charCount == 4) {
                            charCount = 0;
                            cout << endl;
                        }

                        // evenly space it
                        if (charFrequencies[i] >= 100) {
                            cout << alphabet[i] << ": " << charFrequencies[i] << "  ";
                        }
                        else if (charFrequencies[i] >= 10) {
                            cout << alphabet[i] << ": " << charFrequencies[i] << "   ";
                        }
                        else {
                            cout << alphabet[i] << ": " << charFrequencies[i] << "    ";
                        }

                        charCount++;
                    }

                    // find the most frequent letter
                    int max = -1;
                    int index;

                    for (int i = 0; i < 26; i++) {
                        if (charFrequencies[i] > max) {
                            max = charFrequencies[i];
                            index = i;
                        }
                    }

                    // subtract the most frequent letter from E and find the distance from A to get the letter
                    int charShift = index - 4;                  // minus E
                    charShift = (charShift % 26 + 26) % 26;     // c++ doesn't like modding negative numbers
                    char keywordChar = 'A' + charShift;

                    keyword += keywordChar;
                    cout << endl << endl << "Calculated letter of keyword: " << keywordChar << endl << endl << "---------------------------";

                    max = 0;

                    numKeywordCharsFound++;
                    startingPosition++;
                    position = startingPosition;
                }

                cout << endl << endl << "The calculated keyword is: " << keyword << endl << endl;
            }

            // make the encryption key the same length as the text
            fixedDecryptionKey = getActualEncryptionKey(allLines, keyword);

            // decrypt the ciphertext
            for (int i = 0; i < fixedDecryptionKey.size(); i++)
            {
                // make the chars integers to do the encryption formula
                int lineInt = static_cast<int>(toupper(allLines[i]));
                int keyInt = static_cast<int>(toupper(fixedDecryptionKey[i]));
                int x = (lineInt - keyInt + 26) % 26 + 'A';

                // make an ASCII char
                char decryptedChar = (char)x;

                // add to encryption result
                decryptedText.push_back(tolower(decryptedChar));
            }

            if (decryptedText.size() > 60) {
                displayText = decryptedText.substr(0, 600);
            }

            displayResultsOnScreen(displayText);
            manualKeyword = false;

            while (userChoice != 1 && userChoice != 2 && userChoice != 3) {
                cout << endl << "--- Options: ---" << endl << endl;

                cout << "Change Keyword: press 1" << endl << "Change Length of Keyword: press 2" << endl << "Satisfied with Results: press 3" << endl << endl;
                cout << "Enter your selection: ";
                cin >> userChoice;
            }

            if (userChoice == 1) {
                cout << endl << "Enter new keyword: ";
                cin >> keyword;

                keywordLength = keyword.size();
                manualKeyword = true;
                decryptedText = "";
            }
            else if (userChoice == 2) {
                cout << endl << "Enter keyword length: ";
                cin >> keywordLength;

                numKeywordCharsFound = 0;
                startingPosition = 0;
                position = 0;
                decryptedText = "";
                keyword = "";
            }
        }

        cout << endl << "-------------------------------------------------------" << endl << endl;

        return decryptedText;
    }
    else {
        cout << "Error opening file :(" << endl << endl;
        cout << endl << "-------------------------------------------------------" << endl << endl;
        return "Error :(";
    }
}

// ---------------------------------------------------------------------------------------------------------------

string encryption() {

    string encryptionKey;
    string userFileName;
    string line;
    string fixedEncryptionKey;
    string temp;
    string encryptedText;
    string allLines;
    ifstream userFile;

    cout << endl << "--- Encryption ---" << endl << endl;

    cout << "Please enter your encryption key (no spaces): ";
    cin >> encryptionKey;

    cout << "Please enter the name of the file you want to encrypt (with extention): ";
    cin >> userFileName;
    userFile.open(userFileName);

    if (userFile.is_open()) {

        // get the text from the file
        while (getline(userFile, line)) { 
            allLines += line;
        }

        userFile.close();

        // remove special characters
        for (int i = 0; i < allLines.size(); ++i) {

            if ((allLines[i] >= 'a' && allLines[i] <= 'z') || (allLines[i] >= 'A' && allLines[i] <= 'Z')) {
                temp = temp + allLines[i];
            }
        }

        allLines = temp;

        // make the encryption key the same length as the text
        fixedEncryptionKey = getActualEncryptionKey(allLines, encryptionKey);

        for (int i = 0; i < fixedEncryptionKey.size(); i++)
        {
            // make the chars integers to do the encryption formula
            int lineInt = static_cast<int>(toupper(allLines[i]));
            int keyInt = static_cast<int>(toupper(fixedEncryptionKey[i]));
            int x = (lineInt + keyInt - 2 * 65) % 26;

            // make an ASCII char
            char encryptedChar = x + 'A';

            // add to encryption result
            encryptedText.push_back(encryptedChar);
        }

        return encryptedText;
    } 
    else {
        cout << "Error opening file :(" << endl << endl;
        return "Error :(";
    }

    cout << endl << "-------------------------------------------------------" << endl << endl;
}

// ---------------------------------------------------------------------------------------------------------------

// makes the encryption key repeat until it's the same length as the text
string getActualEncryptionKey(string fileText, string encryptionKey) {

    int fileLength = fileText.size();
    int keyLength = encryptionKey.size();
    int i = 0;
    int j = 0;

    string actualKey;

    while (i < fileLength) {

        if (j >= keyLength) {                       // reset counter to 0 if it's reached the length of the key
            j = 0;
        }

        actualKey += encryptionKey[j];              // add the next letter of the encryption key to the extended key

        i++;
        j++;
    }

    return actualKey;
}

// ---------------------------------------------------------------------------------------------------------------

void displayResultsOnScreen(string message) {

    cout << endl << "Encrypted/Decrypted Message: " << endl;

    int characterCounter = 0;
    for (int i = 0; i < message.size(); i++) {
        if (characterCounter == 5) {
            cout << "  ";
            characterCounter = 0;
        }

        if (i % 50 == 0) {
            cout << endl;
        }

        cout << message[i];
        characterCounter++;
    }

    cout << endl << endl;

}

// ---------------------------------------------------------------------------------------------------------------

void writeResultsToFile(string message) {
    
    string fileName;
    char answer = 'P';
    ofstream myFile;
    int characterCounter;

    cout << endl << "Please enter the name of the file to write to: ";
    cin >> fileName;

    // while the file does exist, make sure the user is ok with contents being deleted
    ifstream testFile(fileName);
    while (testFile.good()) {

        testFile.close();

        cout << endl << "File already exists, it will be overwritten. Do you want to proceed? (Y/N) ";
        cin >> answer;

        answer = toupper(answer);

        while (answer != 'Y' && answer != 'N') {
            cout << endl << "Please enter Y or N: ";
            cin >> answer;
        }

        if (answer == 'Y') {
            myFile.open(fileName, ios::trunc);

            characterCounter = 0;
            for (int i = 0; i < message.size(); i++) {
                if (characterCounter == 5) {
                    myFile << "  ";
                    characterCounter = 0;
                }

                myFile << message[i];
                characterCounter++;
            }

            myFile.close();
            testFile.close();
        }
        else {
            cout << endl << "Please enter the name of the file to write to: ";
            cin >> fileName;
            testFile.open(fileName);
        }
    }

    // if file doesn't already exist
    if (!testFile.good()) {

        testFile.close();
        myFile.open(fileName, ios::trunc);

        characterCounter = 0;
        for (int i = 0; i < message.size(); i++) {
            if (characterCounter == 5) {
                myFile << "  ";
                characterCounter = 0;
            }

            myFile << message[i];
            characterCounter++;
        }

        myFile.close();

        cout << endl << "Writing Complete!" << endl << endl;
    }

}

// ---------------------------------------------------------------------------------------------------------------
