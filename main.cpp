#include <iostream>
#include <fstream>
#include <time.h>
#include <stdlib.h>

using namespace std;

void readWords(string *wordArray, char *fileName);
int getNumberOfWords(char *fileName);

void displayWrong1() {
    cout << "________" << endl;
    cout << "|      |" << endl;
    cout << "|" << endl;
    cout << "|" << endl;
    cout << "|" << endl;
    cout << "|" << endl;
}

void displayWrong2() {
    cout << "________" << endl;
    cout << "|      |" << endl;
    cout << "|      O" << endl;
    cout << "|" << endl;
    cout << "|" << endl;
    cout << "|" << endl;
}

void displayWrong3() {
    cout << "________" << endl;
    cout << "|      |" << endl;
    cout << "|      O" << endl;
    cout << "|      |" << endl;
    cout << "|" << endl;
    cout << "|" << endl;
}

void displayWrong4() {
    cout << "________" << endl;
    cout << "|      |" << endl;
    cout << "|      O" << endl;
    cout << "|     /|" << endl;
    cout << "|" << endl;
    cout << "|" << endl;
}

void displayWrong5() {
    cout << "________" << endl;
    cout << "|      |" << endl;
    cout << "|      O" << endl;
    cout << "|     /|\\" << endl;
    cout << "|" << endl;
    cout << "|" << endl;
}

void displayWrong6() {
    cout << "________" << endl;
    cout << "|      |" << endl;
    cout << "|      O" << endl;
    cout << "|     /|\\" << endl;
    cout << "|     /" << endl;
    cout << "|" << endl;
}

void displayWrong7() {
    cout << "________" << endl;
    cout << "|      |" << endl;
    cout << "|      O" << endl;
    cout << "|     /|\\" << endl;
    cout << "|     / \\" << endl;
    cout << "|" << endl;
}

int main(int argc, char* argv[])
{

    int numberOfWords = getNumberOfWords(argv[1]);

    cout << "Number of words: " << numberOfWords << endl;
    string *wArr = new string[numberOfWords];
    readWords(wArr, argv[1]);

    srand(time(NULL));

    void (*fPointer[]) () = {
        displayWrong1, displayWrong2,
        displayWrong3, displayWrong4,
        displayWrong5, displayWrong6, displayWrong7
    };

    bool guessedWord = false;
    bool gameOver = false;

    while(true) {
        // get a random word from txt file
        int wordChoice = (rand() % numberOfWords);
        string &currentWord = wArr[wordChoice];
        const unsigned int currentWordNumber = currentWord.length();

        // create a boolean for each letter
        bool *isGuessed = new bool[currentWordNumber];
        // make each boolean false -> because no letters are revealed yet
        for (int i = 0; i < currentWordNumber; i++) {
            isGuessed[i] = false;
        }

        unsigned int wrongGuesses = 0;

        while (!gameOver) {
            system("cls");
            fPointer[wrongGuesses]();
            cout << "WRONG GUESSES: " << wrongGuesses << endl;

            if (wrongGuesses > 5) {
                cout << "You lost!" << endl;
                gameOver = true;
            }

            if (guessedWord) {
                cout << "You won!" << endl;
                gameOver = true;
            }


            for (int i = 0; i < currentWordNumber; i++) {
                if (isGuessed[i]) {
                    cout << currentWord[i];
                } else {
                    cout << "*";
                }
            }
            cout << endl;

            if (gameOver == false) {

                cout << "What's your guess?" << endl;
                char guess;
                cin >> guess;

                bool letterGuessed = false;
                for (int i = 0; i < currentWordNumber; i++) {
                    if (!guessedWord && (currentWord[i] == guess)) {
                        isGuessed[i] = true;
                        letterGuessed = true;
                    }
                }

                if (!letterGuessed) {
                    wrongGuesses++;
                }

                guessedWord = true;
                for (int i = 0; i < currentWordNumber; i++) {
                    if (!isGuessed[i]) {
                        guessedWord = false;
                    }
                }

            }

        }

        cout << "Do you want to play again? (y/n)" << endl;
        char decision;
        cin >> decision;

        if (decision == 'y') {
            guessedWord = false;
            gameOver = false;
        } else {
            break;
        }


    }


}

int getNumberOfWords(char *fileName) {
    ifstream inputFile;
    inputFile.open(fileName);
    string word;
    int number = 0;

    if (inputFile.is_open()) {
        while (!inputFile.eof()) {
            inputFile >> word;
            if (!word.empty()) {
                number++;
            }
            inputFile >> ws;
        }
        inputFile.close();
    } else {
        cerr << "Couldn't open the file: " << fileName << endl;
    }
    return number;
}

void readWords(string *wordArray, char *fileName) {
    ifstream inputFile;
    inputFile.open(fileName);

    string word;
    int arrayIndex = 0;

    if (inputFile.is_open()) {
        while (!inputFile.eof()) {
            inputFile >> word;
            if (!word.empty()) {
                wordArray[arrayIndex] = word;
                arrayIndex++;
            }
            inputFile >> ws;
        }
        inputFile.close();
    } else {
        cerr << "Couldn't open the file: " << fileName << endl;
    }
}
