#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <array>
#include <vector>
#include <cstring>
#include <ctime>
#include <string>

using namespace std;

typedef char* CharArrayPtr; // typedef for 2D dynamic array for the word search grid

string* getWords(int number); // number of words is passed as an argument and it returns a dynamic array of strings
char getRandomLetter(); // gets a random letter based on ASCII codes
string* deleteEntry(string *dynamicArray, int &size, string entryToDelete);
bool placeWord(CharArrayPtr *grid, string *wordArray, int row, int col, int direction, int numRows, int numCols); // helper function for grander while loop
void openReadFile(ifstream& inStream, string path); // open file to read from
void closeReadFile(ifstream& inStream); // closes file to read from
void openWriteFile(ofstream& outStream, string path); // opens file to write to
void closeWriteFile(ofstream& outStream); // closes file to write to
int mainMenu(); // displays and loops the main menu for the switch function in the main method
int getNumWords(); // gets the number of words from user
void savePuzzle(ofstream& outStream, CharArrayPtr *grid, int numRows, int numCols, string* wordList, int numWords); // writes the puzzle to a file.
void openPuzzle(); // opens a saved puzzle
void solvePuzzle(CharArrayPtr *grid, string* wordList, int numWords, int numRows, int numCols);
string getWordFromArray(string* wordArray, int index);
bool checkUp(CharArrayPtr *grid, string target, int row, int col);
bool checkUR(CharArrayPtr *grid, string target, int row, int col, int numCols);
bool checkRight(CharArrayPtr *grid, string target, int row, int col, int numCols);
bool checkDR(CharArrayPtr *grid, string target, int row, int col, int numCols, int numRows);
bool checkDown(CharArrayPtr *grid, string target, int row, int col, int numRows);
bool checkDL(CharArrayPtr *grid, string target, int row, int col, int numRows);
bool checkLeft(CharArrayPtr *grid, string target, int row, int col);
bool checkUL(CharArrayPtr *grid, string target, int row, int col);
void addToSolution(CharArrayPtr *grid, string target, int row, int col, string direction);

int main()
{
    srand(time(NULL));
    int numWords, numRows, numCols, numWordsInArray, counter = 0;
    ifstream readFile;
    ofstream writeFile;
    
    
    while (true)
    {
        int menuChoice;
        menuChoice = mainMenu();
        switch (menuChoice)
        {
        case 1: // create a new puzzle
        {
            numWords = getNumWords();
            numWordsInArray = numWords;
            numRows = numWords * 3;
            numCols = numWords * 6;

            string* words = new string[numWordsInArray]; // dynamic array of strings to store the words with a different variable so list can be shortened when creating the puzzle
            string* wordsSave = new string[numWords];

            CharArrayPtr *wordSearchGrid = new CharArrayPtr[numRows]; // creating the 2D array (needs to happen just once for the whole program so no function)
            for (int i = 0; i < numRows; i++)
            {
                wordSearchGrid[i] = new char[numCols];
            }

            for (int i = 0; i < numRows; i++)
            {
                for (int j = 0; j < numCols; j++)
                {
                    wordSearchGrid[i][j] = ' ';
                }
            }

            words = getWords(numWords);
            for (int i = 0; i < numWords; i++)
            {
                wordsSave[i] = words[i];
            }

            while (counter < numWords) // putting word into the puzzle
            {
                int randCol = rand() % numCols;
                int randRow = rand() % numRows;
                int randDir = 1 + (rand() % 8);
                bool isInPuzzle;

                isInPuzzle = placeWord(wordSearchGrid, words, randRow, randCol, randDir, numRows, numCols);
                if (isInPuzzle)
                {
                    words = deleteEntry(words, numWordsInArray, words[0]);
                    counter++;
                }
            }

            for (int i = 0; i < numRows; i++)
            {
                for (int j = 0; j < numCols; j++)
                {
                    if (wordSearchGrid[i][j] == ' ')
                    {
                        wordSearchGrid[i][j] = getRandomLetter();
                    }
                    std::cout << wordSearchGrid[i][j] << " ";
                }
                std::cout << endl;
            }


            string pathName;


            std::cout << "Where would you like to save this puzzle?: ";
            std::cin >> pathName;
            openWriteFile(writeFile, pathName);
            savePuzzle(writeFile, wordSearchGrid, numRows, numCols, wordsSave, numWords);
            closeWriteFile(writeFile);
        }        
            break;
        case 2: // open a puzzle
        {
            openPuzzle();
        }
            break;
        case 3:
        {
            openPuzzle();
        }    
            break;
        case 4:
            std::cout << "\nEnd of Program.";
            return 0;
        default:
            std::cout << "Default Case.";
            break;
        }
    }
    

    
    
    std::cout << "\nEnd of Program.";
    return 0;
}

string* getWords(int number)
{
    string* temp = new string[number];
    for (int i = 0; i < number; i++)
    {
        std::cout << "Enter word " << i + 1 << ": ";
        std::cin >> temp[i];
    }
    return temp;
}

char getRandomLetter()
{
    int randASCII = 97 + (rand() % 26);
    char randLetter = (char)randASCII;
    return randLetter;
} 

string getWordFromArray(string* wordArray, int index) // tester function to get word from array
{
    string temp;
    temp = wordArray[index];  
    return temp;
}

bool placeWord(CharArrayPtr *grid, string *wordArray, int row, int col, int direction, int numRows, int numCols) // helper function for grander while loop
{
    string getWord;
    
    getWord = wordArray[0];

    if (direction == 1) // up
    {
        for (int i = 0; i < getWord.length(); i++)
        {
            if((row - i) >= 0 && grid[row - i][col] == ' ')
            {
                continue;
            } else
            {
                return false;
            }
        }
        for (int i = 0; i < getWord.length(); i++)
        {
            grid[row - i][col] = getWord[i];
        }
        return true;
    }

    if (direction == 2) // diag UR
    {
        for (int i = 0; i < getWord.length(); i++)
        {
            if(((col + i) < numCols) && ((row - i) >= 0) && grid[row - i][col + i] == ' ')
            {
                continue;
            } else
            {
                //cout << "I am returning false" << endl;
                return false;
            }
        }
        for (int i = 0; i < getWord.length(); i++)
        {
            grid[row - i][col + i] = getWord[i];
        }
        return true;
    }
    
    
    if (direction == 3) // right
    {
        for (int i = 0; i < getWord.length(); i++)
        {
            if((col + i) < numCols && grid[row][col + i] == ' ')
            {
                continue;
            } else
            {
                //cout << "I am returning false" << endl;
                return false;
            }
            
        }
        for (int i = 0; i < getWord.length(); i++)
        {
            grid[row][col + i] = getWord[i];
        }
        return true;
    }

    if (direction == 4) // diag DR
    {
        for (int i = 0; i < getWord.length(); i++)
        {
            if(((col + i) < numCols) && ((row + i) < numRows) && grid[row + i][col + i] == ' ')
            {
                continue;
            } else
            {
                //cout << "I am returning false" << endl;
                return false;
            }
        }
        for (int i = 0; i < getWord.length(); i++)
        {
            grid[row + i][col + i] = getWord[i];
        }
        return true;
    }

    if (direction == 5) // down
    {
        for (int i = 0; i < getWord.length(); i++)
        {
            if((row + i) < numRows && grid[row + i][col] == ' ')
            {
                continue;
            } else
            {
                //cout << "I am returning false" << endl;
                return false;
            }
        }
        for (int i = 0; i < getWord.length(); i++)
        {
            grid[row + i][col] = getWord[i];
        }
        return true;
    }

    if (direction == 6) // diag DL
    {
        for (int i = 0; i < getWord.length(); i++)
        {
            if(((col - i) >= 0) && ((row + i) < numRows) && grid[row + i][col - i] == ' ')
            {
                continue;
            } else
            {
                //cout << "I am returning false" << endl;
                return false;
            }
        }
        for (int i = 0; i < getWord.length(); i++)
        {
            grid[row + i][col - i] = getWord[i];
        }
        return true;
    }

    if (direction == 7) // left
    {
        for (int i = 0; i < getWord.length(); i++)
        {
            if((col - i) >= 0 && grid[row][col - i] == ' ')
            {
                continue;
            } else
            {
                //cout << "I am returning false" << endl;
                return false;
            }
        }
        for (int i = 0; i < getWord.length(); i++)
        {
            grid[row][col - i] = getWord[i];
        }
        return true;
    }

    if (direction == 8) // diag UL
    {
        for (int i = 0; i < getWord.length(); i++)
        {
            if(((col - i) >= 0) && ((row - i) >= 0) && grid[row - i][col - i] == ' ')
            {
                continue;
            } else
            {
                //cout << "I am returning false" << endl;
                return false;
            }
        }
        for (int i = 0; i < getWord.length(); i++)
        {
            grid[row - i][col - i] = getWord[i];
        }
        return true;
    }
}

string* deleteEntry(string *dynamicArray, int &size, string entryToDelete)
{
    for (int i = 0; i < size; i++)
    {
        if (entryToDelete == dynamicArray[i])
        {
            string* temp = new string[size - 1];
            int toDelete = i;
            for (int j = 0; j < size - 1; j++)
            {
                if (dynamicArray[j] == entryToDelete)
                {
                    temp[j] = dynamicArray[j + 1];
                    for (int newIndex = j + 1; newIndex < size - 1; newIndex++)
                    {
                        temp[newIndex] = dynamicArray[newIndex + 1];
                    }
                    size--;
                    delete [] dynamicArray;
                    return temp; 
                } else
                {
                    temp[j] = dynamicArray[j];
                }
                
            }
            size--;
            delete [] dynamicArray;
            return temp;   
        }
    }
   return dynamicArray; 
}

void openReadFile(ifstream& inStream, string path)
{
    inStream.open(path);
    if (inStream.fail())
    {
        std::cout << "The file failed to open\n";
        exit(1);
    }   
}

void closeReadFile(ifstream& inStream)
{
    inStream.close();
}

void openWriteFile(ofstream& outStream, string path)
{
    outStream.open(path);
    if (outStream.fail())
    {
        std::cout << "The file failed to open.\n";
        exit(1);
    }
    
}

void closeWriteFile(ofstream& outStream)
{
    outStream.close();
}

int mainMenu() // displays and loops the main menu for the switch function in the main method
{
    while (true)
    {
        int choice;
        std::cout << "MAIN MENU" << endl;
        std::cout << "Choose an option: " << endl;
        std::cout << "(1) Create a new puzzle" << endl;
        std::cout << "(2) Open an existing puzzle" << endl;
        std::cout << "(3) Solve an existing puzzle (must have a saved puzzle.)" << endl;
        std::cout << "(4) Exit" << endl;
        std::cin >> choice;
        if (choice < 1 || choice > 4)
        {
            std::cout << "Invalid Choice! Try again." << endl;
        } else
        {
            return choice;
        }
    }
}

int getNumWords()
{
    int numWords;
    std::cout << "How many words would you like in your puzzle?: "; // get number of words from user
    std::cin >> numWords;
    return numWords;
}

void savePuzzle(ofstream& outStream, CharArrayPtr *grid, int numRows, int numCols, string* wordList, int numWords)
{
    for (int k = 0; k < numWords; k++)
    {
        for (int l = 0; l < wordList[k].length(); l++)
        {
            outStream.put(wordList[k][l]);
        }
       outStream.put('\n'); 
    }
    
    outStream.put('$');
    outStream.put('\n');
    outStream.put('\n');

    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numCols; j++)
        {
            outStream.put(grid[i][j]);
        }
        outStream.put('\n');
    }
    
    
}

void openPuzzle()
{
    ifstream readFile;
    string pathToFile;
    int numWords = 0 , i = 0;
    string next = "";

    cout << "Where is the file saved?: ";
    cin >> pathToFile;

    openReadFile(readFile, pathToFile);

    while (true)
    {   
        getline(readFile, next);
        if (next == "$")
        {
            break;
        }
        //wordList[i] = next;
        next = "";
        numWords++;
        i++;
    }
    closeReadFile(readFile);

    string* importWordList = new string[numWords];

    openReadFile(readFile, pathToFile);

    for (int i = 0; i < numWords; i++)
    {
        next = "";
        getline(readFile, next);
        importWordList[i] = next;
    }

    int numRows = numWords * 3;
    int numCols = numWords * 6;
    CharArrayPtr *wordSearchGrid = new CharArrayPtr[numRows]; // creating the 2D array (needs to happen just once for the whole program so no function)
        for (int i = 0; i < numRows; i++)
        {
            wordSearchGrid[i] = new char[numCols];
        }

        for (int i = 0; i < numRows; i++)
        {
            for (int j = 0; j < numCols; j++)
            {
                wordSearchGrid[i][j] = ' ';
            }
        }

    char nextLetter;
    readFile.get(nextLetter);
    readFile.get(nextLetter);
    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numCols; j++)
        {
            readFile.get(nextLetter);
            if (nextLetter == '\n')
            {
                readFile.get(nextLetter);
            }
            wordSearchGrid[i][j] = nextLetter;
        }
    }

    for (int i = 0; i < numWords; i++)
    {
        cout << importWordList[i] << endl;
    }

    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numCols; j++)
        {
            cout << wordSearchGrid[i][j] << " ";
        }
        cout << endl;
    }
    closeReadFile(readFile);
    char solve;
    cout << "Would you like to solve this puzzle? (Y / N): ";
    cin >> solve;  
    if (solve == 'y' || solve == 'Y')
    {
        solvePuzzle(wordSearchGrid, importWordList, numWords, numRows, numCols);
    }
      
}

void solvePuzzle(CharArrayPtr *grid, string* wordList, int numWords, int numRows, int numCols)
{
    bool check;
    int index = 0;
    string temp;
    CharArrayPtr *solvedGrid = new CharArrayPtr[numRows]; // creating the 2D array (needs to happen just once for the whole program so no function)
    for (int i = 0; i < numRows; i++)
    {
        solvedGrid[i] = new char[numCols];
    }
    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numCols; j++)
        {
            solvedGrid[i][j] = ' ';
        }
        
    }

    for (int h = 0; h < numWords; h++)
    {
        std::cout << "Entering word " << h << endl;
        temp = getWordFromArray(wordList, index);
        for (int i = 0; i < numRows; i++)
        {
            for (int j = 0; j < numCols; j++)
            {
                check = checkUp(grid, temp, i, j);
                if (check)
                {
                    addToSolution(solvedGrid, temp, i, j, "up");
                    goto nextWord;
                }
                check = checkUR(grid, temp, i, j, numCols);
                if (check)
                {
                    addToSolution(solvedGrid, temp, i, j, "upRight");
                    goto nextWord;
                }
                check = checkRight(grid, temp, i, j, numCols);
                if (check)
                {
                    addToSolution(solvedGrid, temp, i, j, "right");
                    goto nextWord;
                }
                check = checkDR(grid, temp, i, j, numCols, numRows);
                if (check)
                {
                    addToSolution(solvedGrid, temp, i, j, "downRight");
                    goto nextWord;
                }
                check = checkDown(grid, temp, i, j, numRows);
                if (check)
                {
                    addToSolution(solvedGrid, temp, i, j, "down");
                    goto nextWord;
                }
                check = checkDL(grid, temp, i, j, numRows);
                if (check)
                {
                    addToSolution(solvedGrid, temp, i, j, "downLeft");
                    goto nextWord;
                }
                check = checkLeft(grid, temp, i, j);
                if (check)
                {
                    addToSolution(solvedGrid, temp, i, j, "left");
                    goto nextWord;
                }
                check = checkUL(grid, temp, i, j);
                if (check)
                {
                    addToSolution(solvedGrid, temp, i, j, "upLeft");
                    goto nextWord;
                } 
            }
        }
        nextWord:
        index++;
    }

    for (int y = 0; y < numRows; y++)
    {
        for (int z = 0; z < numCols; z++)
        {
            std::cout << solvedGrid[y][z] << " ";
        }
        std::cout << endl;
    }
      
}

bool checkUp(CharArrayPtr *grid, string target, int row, int col)
{
    for (int i = 0; i < target.length(); i++)
    {
        if ((row - i) >= 0 && grid[row - i][col] == target[i])
        {
            continue;
        } else
        {
            return false;
        }     
    }
    return true;
}

bool checkUR(CharArrayPtr *grid, string target, int row, int col, int numCols)
{
    for (int i = 0; i < target.length(); i++)
    {
        if ((row - i) >= 0 && (col + i) < numCols && grid[row - i][col + i] == target[i])
        {
            continue;
        } else
        {
            return false;
        }     
    }
    return true;
}

bool checkRight(CharArrayPtr *grid, string target, int row, int col, int numCols)
{
    for (int i = 0; i < target.length(); i++)
    {
        if ((col + i) < numCols && grid[row][col + i] == target[i])
        {
            continue;
        } else
        {
            return false;
        }     
    }
    return true;
}

bool checkDR(CharArrayPtr *grid, string target, int row, int col, int numCols, int numRows)
{
    for (int i = 0; i < target.length(); i++)
    {
        if ((row + i) < numRows && (col + i) < numCols && grid[row + i][col + i] == target[i])
        {
            continue;
        } else
        {
            return false;
        }     
    }
    return true;
}

bool checkDown(CharArrayPtr *grid, string target, int row, int col, int numRows)
{
    for (int i = 0; i < target.length(); i++)
    {
        if ((row + i) < numRows && grid[row + i][col] == target[i])
        {
            continue;
        } else
        {
            return false;
        }     
    }
    return true;
}

bool checkDL(CharArrayPtr *grid, string target, int row, int col, int numRows)
{
    for (int i = 0; i < target.length(); i++)
    {
        if ((row + i) < numRows && (col - i) >= 0 && grid[row + i][col - i] == target[i])
        {
            continue;
        } else
        {
            return false;
        }     
    }
    return true;
}

bool checkLeft(CharArrayPtr *grid, string target, int row, int col)
{
    for (int i = 0; i < target.length(); i++)
    {
        if ((col - i) >= 0 && grid[row][col - i] == target[i])
        {
            continue;
        } else
        {
            return false;
        }     
    }
    return true;
}

bool checkUL(CharArrayPtr *grid, string target, int row, int col)
{
    for (int i = 0; i < target.length(); i++)
    {
        if ((row - i) >= 0 && (col - i) >= 0 && grid[row - i][col - i] == target[i])
        {
            continue;
        } else
        {
            return false;
        }     
    }
    return true;
}

void addToSolution(CharArrayPtr *grid, string target, int row, int col, string direction)
{
    for (int i = 0; i < target.length(); i++)
    {
        if (direction == "up")
        {
            grid[row - i][col] = target[i];
        }
        if (direction == "upRight")
        {
            grid[row - i][col + i] = target[i];
        }
        if (direction == "right")
        {
            grid[row][col + i] = target[i];
        }
        if (direction == "downRight")
        {
            grid[row + i][col + i] = target[i];
        }
        if (direction == "down")
        {
            grid[row + i][col] = target[i];
        }
        if (direction == "downLeft")
        {
            grid[row + i][col - i] = target[i];
        }
        if (direction == "left")
        {
            grid[row][col - i] = target[i];
        }
        if (direction == "upLeft")
        {
            grid[row - i][col - i] = target[i];
        }
        
    }
    
}








