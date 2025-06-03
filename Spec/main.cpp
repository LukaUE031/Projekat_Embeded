#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <ctime>
#include <fstream>
#include<vector>
#include <stdint.h>


using namespace std;
bool provocation = false; // used to display a provocative screen
char input[43]; // There are 42 places to play in the board .. this array represent them
void Board();
int PlayOut = 0;
int EVA = 0;
// EVA and PlayOut are working while NegaMax Function is working .. in NegaMax's way it will definitely make any winning move
// as it goes deep so when this happens PlayOut increases by 1 and EVA increases by 1 if its a winnning move or decreases by 1 if it the opposite
// so we can evaluate neutral moves for MiniMax by dividing EVA / PlayOut * 100 so we get a percentage
uint8_t winning();
int GetValue(int t);
int AIManager();
int NegaMax(int Depth);
void clean()
{
    provocation = false;
    for(int i = 0 ; i<= 80 ; i++)
        input[i]=' ';
}

int GetValue(int column) // pass this function a column that you want to play in and it will return its value in input array ..
{
    if(column > 7)
        return 0;
    int n;
    for(int i = 0 ; i<= 6 ; i++)
    {
        if( input[column+7*i] == ' '  )
        {
            n = column+7*i;
            break;
        }
    }
    if ( n > 42 )
        return 0;
    return n;
}
/*
uint8_t winning() // Winning algorithm
{
    int temp=0;
    for(int i = 1 ; i<= 42 ; i++)
    {
        if(input[i] != ' ')
        {
            temp++;
            if( i - ((i-1)/7) * 7 <= 4  )
                if( input[i] == input [i+1] && input[i] == input[i+2] && input[i] == input[i+3] )
                    if(input[i] == 'X' )
                        return 1 ;
                    else
                        return 2;
            if( i <= 21 )
                if ( input[i] == input[i+7] && input[i] == input[i+14] && input[i] == input[i+21]  )
                    if(input[i] == 'X' )
                        return 1 ;
                    else
                        return 2;
            if( i - ((i-1)/7) * 7 <= 4 && i<=18  )
                if(input[i] == input[i+8] && input[i] == input[i+16] && input[i]==input[i+24])
                    if(input[i] == 'X' )
                        return 1 ;
                    else
                        return 2;
            if( i - ((i-1)/7) * 7 >= 4 && i <= 21   )
                if(input[i] == input[i+6] && input[i] == input[i+12] && input[i]==input[i+18])
                    if(input[i] == 'X' )
                        return 1 ;
                    else
                        return 2;
        }

    }
    if (temp == 42)
        return 3;
    return 0;
}*/

uint8_t winning() {
    //Pravljanje log fajla 
    std::ofstream logfile("game_log.txt",std::ios_base::app);
    int iteration_counter=0;//Promenljiva za upis vrednosti u fajl


    // Provera horizontalnih linija
    for (int row = 0; row < 6; row++) { // 6 redova
        for (int col = 0; col <= 3; col++) { // Maksimalno 4 startne tačke po redu
            char symbol = input[row * 7 + col];
            if (symbol != ' ' &&
                symbol == input[row * 7 + col + 1] &&
                symbol == input[row * 7 + col + 2] &&
                symbol == input[row * 7 + col + 3]) {
                if(symbol== 'X'){
                    iteration_counter=1;
                    logfile<<iteration_counter<<"\n";
                    return 1;
                }else {
                    iteration_counter=2;
                    logfile<<iteration_counter<<"\n";
                    return 2;
                }
            }
        }
    }

    // Provera vertikalnih linija
    for (int col = 0; col < 7; col++) { // 7 kolona
        for (int row = 0; row <= 2; row++) { // Maksimalno 3 startne tačke po koloni
            char symbol = input[row * 7 + col];
            if (symbol != ' ' &&
                symbol == input[(row + 1) * 7 + col] &&
                symbol == input[(row + 2) * 7 + col] &&
                symbol == input[(row + 3) * 7 + col]) {
                if(symbol== 'X'){
                    iteration_counter=1;
                    logfile<<iteration_counter<<"\n";
                    return 1;
                }else {
                    iteration_counter=2;
                    logfile<<iteration_counter<<"\n";
                    return 2;
                }
            }
        }
    }

    // Provera dijagonala (desno-nadole)
    for (int row = 0; row <= 2; row++) { // 3 startne tačke po redu
        for (int col = 0; col <= 3; col++) { // 4 startne tačke po koloni
            char symbol = input[row * 7 + col];
            if (symbol != ' ' &&
                symbol == input[(row + 1) * 7 + col + 1] &&
                symbol == input[(row + 2) * 7 + col + 2] &&
                symbol == input[(row + 3) * 7 + col + 3]) {
                 if(symbol== 'X'){
                    iteration_counter=1;
                    logfile<<iteration_counter<<"\n";
                    return 1;
                }else {
                    iteration_counter=2;
                    logfile<<iteration_counter<<"\n";
                    return 2;
                }
            }
        }
    }

    // Provera dijagonala (levo-nadole)
    for (int row = 0; row <= 2; row++) { // 3 startne tačke po redu
        for (int col = 3; col < 7; col++) { // 4 startne tačke po koloni
            char symbol = input[row * 7 + col];
            if (symbol != ' ' &&
                symbol == input[(row + 1) * 7 + col - 1] &&
                symbol == input[(row + 2) * 7 + col - 2] &&
                symbol == input[(row + 3) * 7 + col - 3]) {
               if(symbol== 'X'){
                    iteration_counter=1;
                    logfile<<iteration_counter<<"\n";
                    return 1;
                }else {
                    iteration_counter=2;
                    logfile<<iteration_counter<<"\n";
                    return 2;
                }
            }
        }
    }

    // Provera da li je tabla puna
    for (int i = 0; i < 42; i++) { // 42 pozicije
        if (input[i] == ' ') {
            return 0; // Igra se nastavlja
        }
    }

    return 3; // Nerešeno
}




void Board() // Draw board
{
    cout<<endl<<"    1   "<<"    2   "<<"    3   "<<"    4   "<<"    5   "<<"    6   "<<"    7   "<<endl;

    int j = 42;
    for(int i = 0 ; i<= 23 ; i++)
    {
        if(i % 4 == 0)
            cout<<string(57,'-');
        else
        {
            if( (i - 2) % 4 == 0)
            {
                j=42-(0.25*i+0.5)*6-((0.25*i+0.5)-1) ;
                for(int i = 0 ; i<=6 ; i++)
                {
                    cout<<"|"<<"   "<<input[j]<<"   ";
                    j++;
                }
                cout<<"|";
            }
            else
            {
                for(int i = 0 ; i<=6 ; i++)
                    cout<<"|"<<string(7,' ');
                cout<<"|";
            }
        }
        cout<<endl;
    }
    cout<<string(57,'-');
    if(provocation == true)
        cout<<endl<<"Hehe I'm sure of my winning :D "<<endl;
}




void PlayPosition(char XO)
{
    static std::vector<int> moves;
    static size_t currentMoveIndex = 0;

    if (moves.empty() || currentMoveIndex >= moves.size())
    {
        moves.clear();
        int move;

        ifstream inputFile("input.txt");
        if (!inputFile.is_open())
        {
            cerr << "Can't open file" << endl;
            exit(1);
        }

        while (inputFile >> move)
        {
            moves.push_back(move);
        }
        inputFile.close();
        currentMoveIndex = 0;
    }

    if (currentMoveIndex < moves.size())
    {
        int sth = GetValue(moves[currentMoveIndex++]);
        while (sth == 0 || input[sth] != ' ')
        {
            cout << "WARNING: Invalid move or position already taken. Taking the next available position." << endl;
            sth = GetValue(moves[currentMoveIndex++]);
        }

        if (sth != 0)
        {
            input[sth] = XO;
        }
        else
        {
            cout << "ERROR: Invalid move or position already taken." << endl;
            // You might want to handle this error more gracefully, e.g., ask the user for a valid move.
        }
    }
}





/*int main() // main funkcija u kojoj se prvo igra potez Igraca(u ovom slucaju potezi zadati datotekom input.txt)
{
    srand(time(0));
    clean();
    while (true)
    {
        PlayPosition('X');  // Korisnik bira potez
        system("clear");
        Board();
        int winningtemp = winning();
        if (winningtemp != 0)
        {
            if (winningtemp == 1){
                cout << endl << "Player 2 WON !";
                return 0;}
            else if (winningtemp == 2){
                cout << endl << "Player 1 WON ! ";
                return 0;}
            else if (winningtemp == 3){
                cout << "You Tie ! ";
                return 0;}
            getch();
            clean();
        }
        else
        {
            input[AIManager()] = 'O';  // AI bira potez
        }
    }
}
*/
int main() // main funkcija gde AI ima prvi potez
{
    srand(time(0));
    clean();
    while (true)
    {
        input[AIManager()] = 'O';  // AI bira potez prvi
        system("clear");
        Board();
        uint8_t winningtemp = winning();
		//cout << "Velicina winning() je: " << sizeof(winning()) << endl;
        if (winningtemp != 0)
        {
            if (winningtemp == 1){
                cout << endl << "Player 2 WON !";
                return 0;}
            else if (winningtemp == 2){
                cout << endl << "Player 1 WON ! ";
                return 0;}
            else if (winningtemp == 3){
                cout << "You Tie ! ";
                return 0;}
            getch();
            clean();
        }
        else
        {
            PlayPosition('X');  // Korisnik bira potez
        }
    }
    return 0;
}



int AIManager() // AI Algorithm
{
    float chance[2] = {9999999 , 0 };
    for(int column = 1 ; column <= 7 ; column ++)
    {
        PlayOut = 0;
        EVA=0;
        int PlayNumber = GetValue(column);
        if( PlayNumber != 0 )
        {

            input[PlayNumber] = 'O';
            if(winning()==2)
               {
                   input[PlayNumber]=' ';
                   return PlayNumber ;
               }
            float temp = -(100*NegaMax(1));
            if(PlayOut != 0)
                temp -= ((100*EVA)/PlayOut);
            if(-temp >= 100)
                provocation = true;
            if( chance[0] > temp  )
            {
                chance[0] = temp  ;
                chance[1] = PlayNumber;
            }
             //  cout<<endl<<-temp<<"   "<<EVA << "   " <<PlayOut;
            input[PlayNumber] = ' ';
        }
    }
    return chance[1];
}


int NegaMax(int Depth) // MiniMax algorithm in NegaMax form
{
    char XO;
    int PlayNumber[8] = {0,0,0,0,0,0,0,0}; // The values of the input[] for every column
    int chance=0;
    if(Depth % 2 != 0)
        XO='X';
    else
        XO='O';
    for(int column = 1 ; column <= 7 ; column ++)
        PlayNumber[column]=GetValue(column);
    for(int column = 1 ; column <= 7 ; column++)
    {
        if(PlayNumber[column] != 0)
        {
            input[PlayNumber[column]]=XO;
            if( winning() != 0 )
            {
                PlayOut ++;
                if(XO=='O')
                    EVA ++;
                else
                    EVA --;
                input[PlayNumber[column]]=' ';
                return -1;
            }
            input[PlayNumber[column]]=' ';
        }
    }
    if(Depth <= 6)
    {

        for(int column = 1 ; column <= 7 ; column ++)
        {
            int temp=0;
            if( PlayNumber[column] != 0 )
            {
                input[PlayNumber[column]]=XO;
                if( winning() != 0 )
                {
                    PlayOut++;
                    if(XO=='O')
                        EVA++;
                    else
                        EVA--;
                    input[PlayNumber[column]]=' ';
                    return -1;
                }
                temp = NegaMax(Depth+1);
                if(column == 1)
                    chance = temp;
                if(chance < temp)
                    chance = temp;
                input[PlayNumber[column]]=' ';
            }
        }
    }
    return -chance;

}