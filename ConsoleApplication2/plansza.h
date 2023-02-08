using namespace std;
#include <iostream>
#include <ctime>
#include <string>
#include <vector>

class Display {
public:
    virtual void display() = 0;
};

class board : public Display {

    //prywatne dane takie jak podpowiedzi oraz tablica kodu
private:
    char w, x, y, z;
    char cipher[4];
    char tempArray[4];
    char tempCipher[4];
    bool toggleDuplicates = false;
    char firstPos, secondPos, thirdPos, fourthPos; //pozycje
    int count; //licznik
    int blackCounter;//licznik dobrych znak�w na dobrych pozycjach
    int whiteCounter;//licznik dobrych znak�w na z�ych pozycjach


public:
    
    board() : count(10) {} //10 pr�b zgadniecia kolorow

    void operator -- () {

        --count;

    }

    void display() override{
        cout << count << endl;
    }
    //------------------------------------//


    void boardBuilder(char firstPos, char secondPos, char thirdPos, char fourthPos) {
        this->firstPos = firstPos;
        this->secondPos = secondPos;
        this->thirdPos = thirdPos;
        this->fourthPos = fourthPos; //wpisanie liter koloru

       
        determineHints();//odpowiada za podpowiedzi na dan� runde

        
        genBoardLine(); //tworzenie lini do �adniejszego wy�wietlania
        cout << "| " << firstPos << " | " << secondPos
            << " | " << thirdPos << " | " << fourthPos << " | ";
        cout << w << " | " << x << " | " <<
            y << " | " << z << " |" << endl;
        genBoardLine();//zamkniecie rundy

        cout << endl << "White Pegs: " << whiteCounter;
        cout << endl << "Black Pegs: " << blackCounter;
        cout << endl;//wyswietla nowe podpowiedzi
        return;
    };

    void determineHints() { //metoda usatlajaca podpowiedzi dla uzytkownika
        //pocz�tkowo ustawia wszystkie "pegi" do stanu domyslnego oraz nadpisuje jak jest to potrzebne
        w = 'X';
        x = 'X';
        y = 'X';
        z = 'X';

        //licznik "peg�w"
        blackCounter = 0;
        whiteCounter = 0;

        //wstawienie wybranych przez gracza kolorow do tymczasowego arraya
        tempArray[0] = std::move(firstPos);
        tempArray[1] = std::move(secondPos);
        tempArray[2] = std::move(thirdPos);
        tempArray[3] = std::move(fourthPos);
        int wlk1 = sizeof(tempArray) / sizeof(tempArray[0]);
        std::vector<char> vec1(tempArray, tempArray + wlk1);


        //wstawienie wybranych przez gracza kolorow do tymczasowego arraya
        tempCipher[0] = cipher[0];
        tempCipher[1] = cipher[1];
        tempCipher[2] = cipher[2];
        tempCipher[3] = cipher[3];

        int wlk2 = sizeof(tempCipher) / sizeof(tempCipher[0]);
        std::vector<char> vec2(tempCipher, tempCipher + wlk2);

        //tymczasowe arraye stworzone by mo�na by�o nadpisywac dane
        //podczas obliczania bia�ych i czarnych "peg�w"

        // Upewniienie si�, �e "pegi" nie s� liczone podw�jnie,
        // wi�cej ni� jeden "peg" tego samego koloru,
        // sprawdzenie, czy znaleziono jakie� prawid�owe kolory nie na miejscu

        //zagnie�d�ona p�tla for w celu okre�lenia zar�wno czarnych, jak i bia�ych "peg�w"
        for (int i = 0; i < 4; i++) {

            // liczenie czarnych "peg�w" na podstawie tego, czy dane wprowadzone przez u�ytkownika pasuj� do kodu
            // dok�adnie w tej samej pozycji i w tablicach o tym samym rozmiarze
            if (vec1[i] == vec2[i]) {
                blackCounter++;

                //po policzeniu zamieniaj� si� w nonsens, zapewnia to �e nie zostan� policzone jeszcze raz
                //zliczone ponownie przez wykrywacz bia�ych "peg�w"
                vec1[i] = 'Q';
                vec2[i] = 'Z';
            }
            else {

                //szukanie bia�ych "peg�w"
                //checks if position is wrong but color is correct
                for (int m = 0; m < 4; m++) {
                    if (vec1[i] == vec2[m] &&
                        vec1[m] != vec2[m]) {
                        whiteCounter++;

                        //po policzeniu zamieniaj� si� w nonsens, zapewnia to �e nie zostan� policzone jeszcze raz
                        //zliczone ponownie przez wykrywacz bia�ych "peg�w"
                        vec1[m] = 'Q';
                        vec2[i] = 'Z';
                        break;
                    }
                   
                }
                for (int q = 0; q < 4; q++) {
                    if (vec1[i] == vec2[q] &&
                        vec1[q] != vec2[q]) {
                        whiteCounter++;

                        //po policzeniu zamieniaj� si� w nonsens, zapewnia to �e nie zostan� policzone jeszcze raz
                        //zliczone ponownie przez wykrywacz bia�ych "peg�w"
                        vec1[q] = 'Q';
                        vec2[i] = 'Z';
                        break;
                    }

                }
            }

        }


        //nadpisuje domy�lne "pegi" kolorem bia�ym dla ka�dego obliczonego bia�ego "pega"

        //bia�e "pegi" wyswietlane sa z prawej do lewej
        if (whiteCounter > 0) {
            z = 'W';
        }
        if (whiteCounter > 1) {
            y = 'W';
        }
        if (whiteCounter > 2) {
            x = 'W';
        }
        if (whiteCounter > 3) {
            w = 'W';
        }

        //czarne "pegi" maj� pierwsze�stwo przed bia�ymi "pegami", a czarny mo�e by� prawdziwy
        //dla jednego, podczas gdy bia�y jest r�wnie� prawdziwy, wi�c drukowanie na bia�ym jest przydatne
        //czarne "pegi" wyswietlane sa z lewej do prawej
        if (blackCounter > 0) {
            w = 'B';
        }
        if (blackCounter > 1) {
            x = 'B';
        }
        if (blackCounter > 2) {
            y = 'B';
        }
        if (blackCounter > 3) {
            z = 'B';
        }

    };
    //koniec metody wyznaczania podpowiedzi


    //metoda sprawdzania wygranej przez sprawdzenie, czy ka�da pozycja odpowiada pozycji w szyfrze
    bool checkWin() {
        if (firstPos == cipher[0] && secondPos == cipher[1] && thirdPos == cipher[2] && fourthPos == cipher[3]) {
            return true;
        }
        else {
            return false;
        }
    }

    //og�lna metoda linii planszy om�wiona powy�ej
    void genBoardLine() {
        cout << "|---------------|---------------|" << endl;
        return;
    };


    //generuje losowe liczby dla kodu za pomoc� ctime
    //ka�da liczba ca�kowita 1 - 6 odpowiada mo�liwemu kolorowi
    void genCipher() {

        int num;
        srand(time(0));

        for (int i = 0; i < 4; i++) {

            num = rand() % 6 + 1;

            if (num == 1) {
                cipher[i] = 'b';
            }
            else if (num == 2) {
                cipher[i] = 'g';
            }
            else if (num == 3) {
                cipher[i] = 'o';
            }
            else if (num == 4) {
                cipher[i] = 'p';
            }
            else if (num == 5) {
                cipher[i] = 'r';
            }
            else if (num == 6) {
                cipher[i] = 'y';
            }
        }

       // DEBUG
      //sluzy do wyawietlenia szyfru na poczatku gry, uzywane do testow
      // cout << endl << "DEBUG" << endl;
      // for (int i = 0; i < 4; i++) {
     //       cout << cipher[i];
    //   }

        return;
   };


    //metoda ujawniania kodu zar�wno dla warunk�w wygranej, jak i przegranej
    //resetuje r�wnie� warto�ci "peg�w" podpowiedzi do powt�rki od tego czasu
    //nie mo�na tego zrobi� z main.cpp
    //nie ma jednak wp�ywu na warunek wygranej
    void revealCode() {

        cout << endl << "The code was..." << endl << endl;

        for (int i = 0; i < 4; i++) {

            cout << (cipher[i]);

        }

        //ustawia "pegi" po prawej stronie w domy�lnym stanie do nast�pnej gry
        //mo�na to zrobi� tylko w tej klasie
        w = 'X';
        x = 'X';
        y = 'X';
        z = 'X';

        return;
    }
    //koniec klasy plansza
};