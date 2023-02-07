#include <iostream>
#include "plansza.h"
using namespace std;

//zmienne do przekazywania danych użytkownika do plansza.h w celu sprawdzenia szyfru
//używając szyfru(cipher) zamiast kodu(code), ponieważ jest to mniej mylące
char a;
char b;
char c;
char d;

bool winFlag = false;

void startUp();

int main() {
   
    //generuje obiekt tablicy z pliku plansza.h i klasy tablicy
    board boardObject;
    //generowanie szyfru do gry
    boardObject.genCipher();
  
    startUp();

    //instrukcje gry
    cout << endl << endl << "Welcome to MASTERMIND";

    //ustawienie vars na stan domyślny, głównie do resetowania powtórek
    a = 'O';
    b = 'O';
    c = 'O';
    d = 'O';
    
    cout << endl << endl << "Here is your game board" << endl << endl;

    //tworzenie typu planszy z wartościami znaków do wykorzystania w grze
    // inicjuje z 'O', aby reprezentować puste miejsca na "pegu"
    boardObject.boardBuilder(a, b, c, d);

  //główna pętla gry
  //--------------------------------------------------------//
  //--------------------------------------------------------//
    for (int n = 1; n < 11; n++) {

        //Wyjaśnienie, w jaki sposób użytkownik może wprowadzać swoje domysły do ​​gry
        cout << "\nEnter a letter to guess: (r)ed, (o)range, (y)ellow, (g)reen, (b)lue, (p)urple\n";
        cout << "Or type 'c' to check your number of guesses left\n\n";

        char input;
        bool inputFlag = true;


        //for pętla dla każdego z czterech wejść dla szyfru
        for (int i = 0; i < 4; i++) {
            //do pętla do działania w nieskończoność, aż do poprawnego wprowadzenia danych
            do {
                cin >> input;
                //założenie że dane wejsciowe są prawidłowe
                inputFlag = true;

                //sprawdzanie, czy dane wejściowe mają znak, który odpowiada kolorowi
                if (input == 'r' || input == 'o' || input == 'y'
                    || input == 'g' || input == 'b' || input == 'p'
                    || input == 'c' || input == 'C') {
                    break;
                }

                //pasywno-agresywny przekaz dla osób, które łamią zasady
                cout << "Please enter a character respective of a color ONLY" << endl;
                cin.clear();
                cin.ignore(10000, '\n');

                //brak prawdziwego warunku końcowego, ponieważ inputFlag jest zawsze prawdziwy
                //jedynym sposobem zakończenia jest aktywacja instrukcji if i przerwanie;
            } while (inputFlag == true);

            if (input == 'c' || input == 'C') {
                cout << "Your number of guesses left is ";
                boardObject.display();
                i = i - 1;
                cout << "\nEnter a letter to guess: (R)ed, (O)range, (Y)ellow, (G)reen, (B)lue, (P)urple\n";
                cout << "Or type 'c' to check your number of guesses left\n\n";
                continue;
            }

            //if w celu przypomnienia użytkownikowi, aby kontynuował wprowadzanie do czterech wejść
            if (i != 3) {
                cout << endl << "Thanks, please enter another character" << endl;
            }
            cin.clear();
            cin.ignore(10000, '\n');

            //ustawia dane wejściowe na rzeczywiste wartości dla obiektu planszy podczas jego działania
            if (i == 0) {
                a = input;
            }if (i == 1) {
                b = input;
            }if (i == 2) {
                c = input;
            }if (i == 3) {
                d = input;
            }

        }

        //pozwala użytkownikowi kontynuować, gdy jest gotowy i usuwa planszę z wyborów w tej rundzie
        cout << endl;
        system("read -p 'Press Enter to continue...' var");
        cout << endl << endl;
        

        //wysyła wybrane przez użytkownika wartości do sprawdzenia w klasie tablicy
        boardObject.boardBuilder(a, b, c, d);

        cout << endl;

        //po wygenerowaniu planszy sprawdza warunek wygranej
        //w przypadku wygranej, wyświetlony kod i zamknięcie systemu

        if (boardObject.checkWin() == true) {
            cout << "Congratulations! YOU WIN!" << endl;
            cout << "You successfully cracked the code!" << endl;
            boardObject.revealCode();
            cout << endl;
            winFlag = true;
            break;
        }

        //używa przeciążonego operatora
        --boardObject;

        //używa funkcji wyświetlania dla przeciążonego operatora do
        //pokazania pozostałych prób
        cout << "You have ";
        boardObject.display();
        cout << "Guesses remaining" << endl;

    }

    //pozwala użytkownikowi na ponowną rozgrywkę jeśli przegrał
    char again;

    if (winFlag == false) {//---------
        //wyswietla gdy przegra sie gre
        cout << "Sorry thats the max number of guesses..." << endl << endl;
        cout << "YOU LOSE!" << endl << endl;

        //ujawnia kod za pomocą metody w klasie plansza
        //nie może uzyskać bezpośredniego dostępu do cipher[], ponieważ jest to prywatna tablica znaków
        boardObject.revealCode();
        cout << endl << endl << endl;
    }//---------

    //pozwala użytkownikowi zresetować grę i spróbować ponownie lub całkowicie wyjść z systemu
    cout << endl;
    system("echo 'Press Enter to continue...'");
    cout << "Play Again? (y/n)" << endl;

    //skopiowane z góry, nie zezwala żadnemu użytkownikowi na zabawne interesy
    //dane wejściowe użytkownika, dopuszcza tylko char y lub n
    bool inputFlagEnd = true;
    do {
        cin >> again;
        //załóżenie, że dane wejściowe są prawidłowe
        inputFlagEnd = true;

        //sprawdza, czy dane wejściowe mają znak, który odpowiada kolorowi
        if (again == 'y' || again == 'Y'
            || again == 'n' || again == 'N')
        {
            if (again == 'y' || again == 'Y') {
                main();
            }
            else if (again == 'n' || again == 'N') {
                exit(0);
            }

        }
        //pasywno - agresywny przekaz dla osób, które łamią zasady
        cout << "Please enter correct input (y/n)" << endl;
        cin.clear();
        cin.ignore(10000, '\n');
        //brak prawdziwego warunku końcowego, ponieważ inputFlag jest zawsze prawdziwy
        //jedynym sposobem zakończenia jest aktywacja instrukcji if i przerwanie;
    } while (inputFlagEnd == true);
    //koniec main
}

//napis mastermind dla lepszego wygladu
void startUp() {
    cout << " __  __           _                      _           _ " << endl;
    cout << "|  \\/  | __ _ ___| |_ ___ _ __ _ __ ___ (_)_ __   __| |" << endl;
    cout << "| |\\/| |/ _` / __| __/ _ \\ '__| '_ ` _ \\| | '_ \\ / _` |" << endl;
    cout << "| |  | | (_| \\__ \\ ||  __/ |  | | | | | | | | | | (_| |" << endl;
    cout << "|_|  |_|\\__,_|___/\\__\\___|_|  |_| |_| |_|_|_| |_|\\__,_|" << endl;
    cout << "-------------------------------------------------------";

}