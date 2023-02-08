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
    int blackCounter;//licznik dobrych znaków na dobrych pozycjach
    int whiteCounter;//licznik dobrych znaków na z³ych pozycjach


public:
    
    board() : count(10) {} //10 prób zgadniecia kolorow

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

       
        determineHints();//odpowiada za podpowiedzi na dan¹ runde

        
        genBoardLine(); //tworzenie lini do ³adniejszego wyœwietlania
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
        //pocz¹tkowo ustawia wszystkie "pegi" do stanu domyslnego oraz nadpisuje jak jest to potrzebne
        w = 'X';
        x = 'X';
        y = 'X';
        z = 'X';

        //licznik "pegów"
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

        //tymczasowe arraye stworzone by mo¿na by³o nadpisywac dane
        //podczas obliczania bia³ych i czarnych "pegów"

        // Upewniienie siê, ¿e "pegi" nie s¹ liczone podwójnie,
        // wiêcej ni¿ jeden "peg" tego samego koloru,
        // sprawdzenie, czy znaleziono jakieœ prawid³owe kolory nie na miejscu

        //zagnie¿d¿ona pêtla for w celu okreœlenia zarówno czarnych, jak i bia³ych "pegów"
        for (int i = 0; i < 4; i++) {

            // liczenie czarnych "pegów" na podstawie tego, czy dane wprowadzone przez u¿ytkownika pasuj¹ do kodu
            // dok³adnie w tej samej pozycji i w tablicach o tym samym rozmiarze
            if (vec1[i] == vec2[i]) {
                blackCounter++;

                //po policzeniu zamieniaj¹ siê w nonsens, zapewnia to ¿e nie zostan¹ policzone jeszcze raz
                //zliczone ponownie przez wykrywacz bia³ych "pegów"
                vec1[i] = 'Q';
                vec2[i] = 'Z';
            }
            else {

                //szukanie bia³ych "pegów"
                //checks if position is wrong but color is correct
                for (int m = 0; m < 4; m++) {
                    if (vec1[i] == vec2[m] &&
                        vec1[m] != vec2[m]) {
                        whiteCounter++;

                        //po policzeniu zamieniaj¹ siê w nonsens, zapewnia to ¿e nie zostan¹ policzone jeszcze raz
                        //zliczone ponownie przez wykrywacz bia³ych "pegów"
                        vec1[m] = 'Q';
                        vec2[i] = 'Z';
                        break;
                    }
                   
                }
                for (int q = 0; q < 4; q++) {
                    if (vec1[i] == vec2[q] &&
                        vec1[q] != vec2[q]) {
                        whiteCounter++;

                        //po policzeniu zamieniaj¹ siê w nonsens, zapewnia to ¿e nie zostan¹ policzone jeszcze raz
                        //zliczone ponownie przez wykrywacz bia³ych "pegów"
                        vec1[q] = 'Q';
                        vec2[i] = 'Z';
                        break;
                    }

                }
            }

        }


        //nadpisuje domyœlne "pegi" kolorem bia³ym dla ka¿dego obliczonego bia³ego "pega"

        //bia³e "pegi" wyswietlane sa z prawej do lewej
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

        //czarne "pegi" maj¹ pierwszeñstwo przed bia³ymi "pegami", a czarny mo¿e byæ prawdziwy
        //dla jednego, podczas gdy bia³y jest równie¿ prawdziwy, wiêc drukowanie na bia³ym jest przydatne
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


    //metoda sprawdzania wygranej przez sprawdzenie, czy ka¿da pozycja odpowiada pozycji w szyfrze
    bool checkWin() {
        if (firstPos == cipher[0] && secondPos == cipher[1] && thirdPos == cipher[2] && fourthPos == cipher[3]) {
            return true;
        }
        else {
            return false;
        }
    }

    //ogólna metoda linii planszy omówiona powy¿ej
    void genBoardLine() {
        cout << "|---------------|---------------|" << endl;
        return;
    };


    //generuje losowe liczby dla kodu za pomoc¹ ctime
    //ka¿da liczba ca³kowita 1 - 6 odpowiada mo¿liwemu kolorowi
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


    //metoda ujawniania kodu zarówno dla warunków wygranej, jak i przegranej
    //resetuje równie¿ wartoœci "pegów" podpowiedzi do powtórki od tego czasu
    //nie mo¿na tego zrobiæ z main.cpp
    //nie ma jednak wp³ywu na warunek wygranej
    void revealCode() {

        cout << endl << "The code was..." << endl << endl;

        for (int i = 0; i < 4; i++) {

            cout << (cipher[i]);

        }

        //ustawia "pegi" po prawej stronie w domyœlnym stanie do nastêpnej gry
        //mo¿na to zrobiæ tylko w tej klasie
        w = 'X';
        x = 'X';
        y = 'X';
        z = 'X';

        return;
    }
    //koniec klasy plansza
};