#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

using namespace std;

// Function to check if a character is a letter
bool isLetter(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

// Function to convert letter preceded by "_" sign to lowercase
void convertToLower(string& str) {
    for (size_t i = 1; i < str.length(); ++i) {
        if (str[i - 1] == '_' && isLetter(str[i])) {
            str[i] = tolower(str[i]);
            str.erase(i - 1, 1);
        }
    }
}

// Function to convert lowercase letter to uppercase
void convertToUpper(string& str) {
    for (size_t i = 0; i < str.length(); ++i) {
        if (isLetter(str[i]) && islower(str[i])) {
            str.insert(i, "_");
            str[i + 1] = toupper(str[i + 1]);
            ++i;
        }
    }
}

// Function to process the text according to the task
string processText(const string& input) {
    string result = input;
    if (result.empty())
        return "";

    // Splitting the string into words
    size_t pos = 0;
    while ((pos = result.find(' ', pos)) != string::npos) {
        result.insert(pos, "_");
        pos += 2; // Incrementing pos to skip the added "_" and the space
    }

    // Checking for errors
    for (size_t i = 1; i < result.length(); ++i) {
        if (result[i] == '_' && !isLetter(result[i - 1])) {
            return "error";
        }
    }

    convertToLower(result);
    convertToUpper(result);

    return result;
}

int main() {
    ifstream inputFile(R"(C:\Users\ReFlex\Documents\GitHub\c_lab\labs_masha\input.txt)");
    ofstream outputFile(R"(C:\Users\ReFlex\Documents\GitHub\c_lab\labs_masha\output.txt)");

    if (!inputFile || !outputFile) {
        cerr << "Error: Unable to open files!" << endl;
        return 1;
    }

    string line;
    while (getline(inputFile, line)) {
        string processedLine = processText(line);
        outputFile << processedLine << endl;
    }

    inputFile.close();
    outputFile.close();

    cout << "Text processing completed." << endl;

    return 0;
}
