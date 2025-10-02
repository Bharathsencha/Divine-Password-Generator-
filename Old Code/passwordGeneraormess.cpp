#include <iostream>
#include <ctime>
using namespace std;

// Function to generate random numeric characters
void characters(int a) {
    for(int i = 0; i < a/7; i++) {
        cout << static_cast<char>('0' + (rand() % 10)); // Random number (0-9)
    }
}

// Function to generate random lowercase characters
void realcharacterslower(int a) {
    char b[12] = {'n','g','u','i','a','m','}','l','b','v','h','c'};
    for(int j = 0; j < a/7; j++) {
        cout << b[rand() % 12]; // Random lowercase character
    }
}

// Function to generate random uppercase characters
void realcharacters(int a) {
    char b[17] = {'R','G','V','J','X',':','(','Y','S','L','W','Q','T','K','U','H','Z'};
    for(int k = 0; k < a/7; k++) {
        cout << b[rand() % 17]; // Random uppercase character
    }
}

// Function to generate random special characters
void realcharacterslower2(int a) {
    char b[16] = {';',')','d','j','k','e','o','#','r','s','t','x','y','C','~'};
    for(int j = 0; j < a/7; j++) {
        cout << b[rand() % 16]; // Random special character
    }
}

// Function to generate random symbols
void symbols(int a) {
    const char* symbols[] = {
        ">", ",", ".", "?", "-", "_", "^", "&", "$", "%", "[", "]", ":", ";", 
        "@", "*", "(", ")", "+", "'", "<", "/", "=", "{", "}", "!", "`"
    };
    int numSymbols = sizeof(symbols) / sizeof(symbols[0]);
    for(int i = 0; i < a/7; i++) {
        cout << symbols[rand() % numSymbols]; // Random symbol
    }
}

// Function to generate random mixed characters
void realcharacters2(int a) {
    char b[11] = {';', 'E', '>', '=', 'P', 'W', 'z', 'O', 'D', 'N', 'O'};
    for(int k = 0; k < a/7; k++) {
        cout << b[rand() % 11]; // Random mixed character
    }
}

// Function to generate additional random symbols
void symbols2(int a) {
    const char* symbols[] = {
        "-I-", "O_o", "B<-", "{", "g", "!", "^", "&", "#", "$", "%",
        "[", "]", ":", ";", "/", ",", "@", "*", "(", ")", "+", "'", "<", 
        "P:)", ":P", ";)", "I", "M", ":D", "A", ">o^", "o_<", "-o", "_-"
    };
    int numSymbols = sizeof(symbols) / sizeof(symbols[0]);
    for(int i = 0; i < a/7; i++) {
        cout << symbols[rand() % numSymbols]; // Random symbol
    }
}

int main() {
    srand(time(0)); // Seed the random number generator

    // Array of possible password sizes
    int sizes[] = {9, 14, 22, 11, 16, 21, 12, 19, 20, 2, 25, 13, 10, 7, 18, 15, 17};
    int* ptr = sizes; // Pointer to the array
    int numin = ptr[rand() % (sizeof(sizes)/sizeof(sizes[0]))]; // Randomly select a size
    numin = numin < 10 ? 10 : (numin > 22 ? 22 : numin); // Clamp size between 10 and 22

    // Generate the password
    characters(numin); // Numbers
    realcharacters(numin); // Uppercase
    realcharacterslower(numin); // Lowercase
    symbols(numin); // Symbols
    realcharacters2(numin); // Mixed characters
    realcharacterslower2(numin); // Additional lowercase
    symbols2(numin); // Additional symbols

    return 0;
}
