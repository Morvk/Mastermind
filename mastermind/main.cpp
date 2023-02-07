#include <iostream>
#include <iomanip>
#include <ctime>
#include <iomanip>
using namespace std;

//Function Prototypes
void strgen(char[], int, int);                                  //Actual Hidden pattern generator
void nodupli(char[], int, const char[], int);                  //No-duplicate pattern generator
void rules();                                                   //Print rules of the game
void count(char[], char&, char&, const char[], const int);    //To count absolute right guesses and partial right guesses
void prnt(const char[], const char, const char, const int);    //To print the game design      
void output(const char[], const  char, const  char, const char); //To output the final result
void guessin(char[], const int);                                //To input the correct guess pattern

//Main Execution
int main(int argc, char** argv) {

    srand(static_cast<unsigned int>(time(0)));                  //Random number seed

    //Declare all variables
    int  len;                       //Code Length
    int  dupli;                     //Option of if user wants duplicates or not 
    char RCWP, RCRP;                //RCWP: Right color, wrong position
    //RCRP: Right color, right position
    char guesses;                   //Total number of guesses

    //Initializing variables
    RCWP = '\0'; RCRP = '\0'; guesses = '\0';

    //Printing the rules of the game
    rules();

    //Code Length Input
    do {
        cout << endl << "Enter the code length (1-8): ";
        cin >> len;
    } while (len <= 0 || len > 8);

    //Duplicate colors allowance
    do {
        cout << "Allow duplicates?" << " Enter 1 for Yes OR 0 for No."
            << endl << "Your Input: ";
        cin >> dupli;
    } while (dupli != 0 && dupli != 1);


    char ptrn[len + 1];            //To store actual hidden pattern

    strgen(ptrn, len, dupli);    //Finding the actual hidden pattern

    char guess[len + 1];           //To store guessed patterns by the user

    //Hidden Code Print
    cout << endl << "HIDDEN COLOR PATTEN: " << endl;
    for (int i = 0; i < len; i++)
        guess[i] = '?';
    prnt(guess, RCRP, RCWP, len);

    do {
        RCWP = '\0'; RCRP = '\0';  //Making count 0 for next loop

        //Asking user for the guess and 
        //counting total Right-Color-Right-Position(RCRP) guesses
        //and total Right-Color-Wrong-Position(RCWP) guesses
        count(guess, RCWP, RCRP, ptrn, len);

        prnt(guess, RCRP, RCWP, len);           //Printing the guess

        guesses = static_cast<int>(guesses + 1);  //Counting total guesses

    } while (static_cast<int>(guesses) < 10 && RCRP != len);

    //Print the output
    output(ptrn, guesses, RCRP, len);

    return 0;
}

//______________________________________________________________________________

//Generate hidden color pattern/code
void strgen(char chArr[], int len, int dupli)
{
    //Domain of possible colors
    //R: RED | G: GREEN | B: BLACK | P: PINK | O: ORANGE | W: WHITE | Y: YELLOW | V: VOILET
    const char domain[] = { 'R','G','B','P','O','W','Y','V' };
    const int dsize = 8;            //Domain size

    chArr[len] = '\0';

    //Generating the Actual Hidden Pattern
    if (dupli == 1)
        for (int i = 0; i < len; i++)
            chArr[i] = domain[rand() % dsize];
    else nodupli(chArr, len, domain, dsize);
}

//______________________________________________________________________________

//Generating color pattern with no duplicates
void nodupli(char chArr[], int len, const char domain[], int dsize)
{
    bool check;     //Flag to check if there is any same color in the pattern

    for (int i = 0; i < len; i++)
    {
        do {
            chArr[i] = domain[rand() % dsize];
            check = true;

            for (int j = i - 1; j >= 0; j--)
                if (chArr[i] == chArr[j])
                    check = false;

            if (check) break;
        } while (true);
    }
}

//______________________________________________________________________________

//Printing rules
void rules()
{
    cout << "HELLO, WELCOME TO MASTERMIND!" << endl
        << "Your mission is to crack the secret hidden color pattern by making guesses." << endl
        << "With each guess the game will tell you that in your guessed pattern,"
        << endl << "how many colors are in the actual pattern and how many are not." << endl
        << "-If a guessed color is wrong, on the side you will see: -" << endl
        << "-If a guessed color is right but is at wrong position, on the side you will see: X" << endl
        << "-If a guessed color is right and also at the correct position, on the side you will see: O" << endl;


    cout << endl << "INSTRUCTIONS:" << endl << "1) You have maximum of 10 guesses to crack the pattern." << endl
        << "2) To input your guessed pattern, type the first letter IN CAPITAL LETTERS "
        << endl << "of the colors all together in the order you guessed them." << endl
        << "For eg. If you want to guess RED-GREEN-YELLOW-ORANGE for a 4 code length pattern, type only RGYO." << endl << endl

        << "Available colors to chose from:" << endl
        << "| R : RED    | G: GREEN | B: BLACK  | P: PINK   |" << endl
        << "| O : ORANGE | W: WHITE | Y: YELLOW | V: VOILET |" << endl;
}

//______________________________________________________________________________

//Counting total right guessed, partial guessed colors in the pattern
void count(char guess[], char& RCWP, char& RCRP, const char ptrn[], int len)
{
    bool check = false;                                    //Flag
    const char dsize = 8;                                  //Colors domain size

    //Declaration and Initialization of blockG (Block Guess) array to block 
    //all those position in Guess array which already had been matched.
    char blockG[len + 1];
    char blkGlen = '\0';                               //blockG array length

    //Declaration and Initialization of blockP (Block Pattern) array to block 
    //all those position in actual Pattern array which already had been matched.
    char blockP[len + 1];
    char blkPlen = '\0';                              //blockP array length

    //Asking user for Guess
    guessin(guess, len);

    //Checking for all Right-Color-Right-Position(RCRP) guesses
    for (int i = 0; i < len; i++)
    {
        if (ptrn[i] == guess[i])
        {
            RCRP = static_cast<char>(RCRP + 1);               //1+ RCRP
            blockP[static_cast<int>(blkPlen)] = static_cast<char>(i);
            blkPlen = static_cast<char>(blkPlen + 1);
            blockG[static_cast<int>(blkGlen)] = static_cast<char>(i);
            blkGlen = static_cast<char>(blkGlen + 1);
        }
    }

    //Checking for all Right-Color-Wrong-Position (RCWP) guesses
    for (int i = 0; i < len; i++)
    {
        //Checking if a position for an element in actual pattern is blocked.
        for (int a = 0; a < blkPlen; a++)
        {
            if (i == static_cast<int>(blockP[a]))
                check = true;
        }

        //Only proceed if the position (i) of an element 
        //in actual pattern is not blocked
        if (check == false)
        {
            for (int j = 0; j < len; j++)
            {
                check = false;

                //Checking if color matches
                if (ptrn[i] == guess[j])
                {

                    //Checking if the position of the
                    //matched element in Guess is blocked
                    for (int k = 0; k < blkGlen; k++)
                    {
                        if (blockG[k] == j)
                        {
                            check = true; break;
                        }
                    }

                    //Only proceed if the position of the match element
                    //in Guess isn't blocked
                    if (check == false)
                    {
                        RCWP = static_cast<char>(RCWP + 1);           //+1 RCWP

                        //Blocking the position of the matched guess array element 
                        blockG[static_cast<int>(blkGlen)] = static_cast<char>(j);
                        blkGlen = static_cast<char>(blkGlen + 1);
                        break;
                    }
                }
            }
        }
        check = false;
    }
}

//______________________________________________________________________________

//Inputting a valid guess from player
void guessin(char guess[], const int len)
{
    bool check;                    //Check if Guess pattern in invalid
    char size = '\0';              //Size of actual entered guessed pattern

    do {
        check = false; size = '\0';
        cout << endl << "YOUR GUESS: " << endl;
        cin >> guess;

        //Counting the actual size of the guessed pattern
        while (guess[static_cast<int>(size)] != '\0')
            size = static_cast<char>(size + 1);

        //Checking the validity of guess pattern colors
        for (int i = 0; i < len; i++)
        {
            if (!(guess[i] == 'R' || guess[i] == 'G' || guess[i] == 'B' || guess[i] == 'P' ||
                guess[i] == 'O' || guess[i] == 'W' || guess[i] == 'Y' || guess[i] == 'V'))
            {
                check = true; break;
            }
        }
        if (check == true || static_cast<int>(size) > len) cout << "ENTER A VALID GUESS! ";
    } while (check == true || static_cast<int>(size) > len);
}

//______________________________________________________________________________

//Print the game layout/design
void prnt(const char guess[], const char RCRP, const char RCWP, const int len)
{
    for (int i = 0; i < len; i++)
        cout << "----";
    cout << endl;

    for (int i = 0; i < len; i++)
        cout << "| " << *(guess + i) << " ";
    cout << "|" << setw(6);

    for (int i = 0; i < static_cast<int>(RCRP); i++)
        cout << "O ";

    for (int i = 0; i < static_cast<int>(RCWP); i++)
        cout << "X ";

    for (int i = 0; i < (len - static_cast<int>(RCRP + RCWP)); i++)
        cout << "- ";
    cout << endl;

    for (int i = 0; i < len; i++)
        cout << "----";
    cout << endl;
}

//______________________________________________________________________________

//Print the winning and losing - end status of the game
void output(const char ptrn[], const char guesses, const char RCRP, const char len)
{

    //Notify user if he won or lost
    if (guesses == 10)
        cout << "YOU LOST! You ran out of guesses." << endl;
    if (RCRP == len)
        cout << "YOU WON! CONGRATULATIONS." << endl << endl;

    //Printing the Correct pattern
    cout << "THE CORRECT PATTERN WAS: " << endl;
    for (int i = 0; i < len; i++)
        cout << "----";
    cout << endl;
    for (int i = 0; i < len; i++)
        cout << "| " << *(ptrn + i) << " ";
    cout << "|" << endl;
    for (int i = 0; i < len; i++)
        cout << "----";
    cout << endl;
}