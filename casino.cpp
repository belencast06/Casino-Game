//Belen Castellanos Frederick
//Lauren Belvin
//Anthony Fieramusca

#include<iostream>
#include<iomanip> //for setw()
#include <fstream>//probs will use file somewhere
#include<string>//for getline()
#include <thread>//for slot spin display
#include<windows.h>//for console font change
#include<cwchar>//for wcscpy()
                //copies string of chars to other string
#include<ctime>// for srand();
#include <vector>//vector
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <random>
#include <chrono>
using namespace std;

//for test
string printColors(const string& text, int color)
{
    HANDLE colors = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(colors, color);
    cout << text;
    // Reset color to default after printing
    SetConsoleTextAttribute(colors,7);
    return text;
}

// struct holds starting credit values
// for user to choose from
struct Credit
{
    int hard=30000;
    int medium=50000;
    int easy=70000;

};

// struct holding player info
// that will used to update player status
struct Player
{

   int transactions=0;
   int userCred;            // could be a class ??? ( think about it later)
   string name;

};


class Card {
public:
    enum Suit { HEARTS, DIAMONDS, CLUBS, SPADES};
    enum Value { TWO = 2, THREE=3, FOUR=4, FIVE=5, SIX=6, SEVEN=7, EIGHT=8, NINE=9, TEN=10, JACK=11, QUEEN=12, KING=13, ACE=14 };

    Suit suit;
    Value value;

    void display() const
    {
         string suit_str;
    switch(suit) {
        case HEARTS:
            suit_str = "Hearts";
            break;
        case DIAMONDS:
            suit_str = "Diamonds";
            break;
        case CLUBS:
            suit_str = "Clubs";
            break;
        case SPADES:
            suit_str = "Spades";
            break;
    }

    string value_str;

    switch(value) {
        case TWO:
            value_str = "2";
            break;
        case THREE:
            value_str = "3";
            break;
        case FOUR:
            value_str = "4";
            break;
        case FIVE:
            value_str = "5";
            break;
        case SIX:
            value_str = "6";
            break;
        case SEVEN:
            value_str = "7";
            break;
        case EIGHT:
            value_str = "8";
            break;
        case NINE:
            value_str = "9";
            break;
        case TEN:
            value_str = "10";
            break;
        case JACK:
            value_str = "Jack";
            break;
        case QUEEN:
            value_str = "Queen";
            break;
        case KING:
            value_str = "King";
            break;
        case ACE:
            value_str = "Ace";
            break;
    }
    cout << value_str << " of " << suit_str << endl;
    }

};

class Deck {
    private:
        vector<Card> cards;
    public:
        Deck()
        {
            for (int suit = Card::HEARTS; suit <= Card::SPADES; ++suit){
                for (int value = Card::TWO; value <= Card::ACE; ++value) {
                    cards.push_back({ static_cast<Card::Suit>(suit), static_cast<Card::Value>(value) });
                }
            }
            shuffle();
        }

        void shuffle()
        {
            random_shuffle(cards.begin(), cards.end());
        }

        Card dealCard()
        {
            Card dealtCard = cards.back();
            cards.pop_back();
            return dealtCard;
        }
};

class Hand {
protected:
    vector<Card> cards;
public:
    const vector<Card>& getCards() const {
        return cards;
    }

    void addCard(const Card& card) {
        cards.push_back(card);
    }

    int getValue() const {
        int total = 0;
        int numAces = 0;
        for (const auto& card : cards) {
            if (card.value >= Card::TEN) {
                total += 10;
            } else if (card.value == Card::ACE) {
                total += 11;
                numAces++;
            } else {
                total += card.value;
            }
        }
        while (total > 21 && numAces > 0) {
            total -= 10;
            numAces--;
        }
        return total;
    }

    void clear() {
        cards.clear();
    }
};

class playerPoker{
    public:
    vector<Card> hand;

    void addCard(const Card& card) {
        hand.push_back(card);
    }

    void clearHand() {
        hand.clear();
    }
};

class PokerGame {
private:
    Player& _player;
    Deck deck;
    vector<Card> playerHand;
    vector<Card> computerHand;
public:

    PokerGame(Player& player): _player(player)
    {

        playerHand.reserve(5);
        for(int i = 0; i < 5; ++i) {
            playerHand.push_back(deck.dealCard());
        }
        computerHand.reserve(5);
        for(int i = 0; i < 5; ++i) {
            computerHand.push_back(deck.dealCard());
        }
    }

    void displayHand(const vector<Card>& hand) const {
        for(auto& card : hand) {
            card.display();
        }
    }

    void displayPlayerHand() const {
        cout << "Your hand:" << endl;
        displayHand(playerHand);
    }

    void displayComputerHand() const {
        cout << "Computer's hand:" << endl;
        displayHand(computerHand);
    }

    void discardAndDraw() {
        playerHand.clear();
        for(int i = 0; i < 5; ++i) {
            playerHand.push_back(deck.dealCard());
        }
    }

    void computerTurn() {
        // Computer randomly decides to discard and draw
        if(rand() % 2 == 0) {
            computerHand.clear();
            for(int i = 0; i < 5; ++i) {
                computerHand.push_back(deck.dealCard());
            }
        }
    }

    //void Poker();
    //void printCard(const Card& card);
    int evaluateHand(const vector<Card>& hand) const {
        int sum = 0;
        bool isDealer = false; // Assume player's hand by default
        for (const auto& card : hand) {
            if (isDealer) {
                // Increase dealer's hand value to be higher than player's hand value
                sum += rand() % 7 + 9; // Random value between 9 and 15
            } else {
                sum += card.value;
            }
        }
        return sum;
    }
    void simulateThinking(){
        // Simulate thinking by adding a delay
        this_thread::sleep_for(chrono::seconds(2));
    }

    void determineWinner(int bet) {
        int playerScore = evaluateHand(playerHand);
        int computerScore = evaluateHand(computerHand);

        cout << "\nYour hand's score: " << playerScore << endl;
        cout << "Computer's hand's score: " << computerScore << endl;

        if (playerScore > computerScore) {
            printColors("Congratulations! You win!\n\n\n",2);
            _player.userCred+=bet;
        } else if (playerScore < computerScore) {
            printColors("Sorry, you lose. Better luck next time!\n\n\n",1);
            _player.userCred-=bet;
        } else {
            cout << "\n\nIt's a tie!\n\n" << endl;
            _player.userCred+=(bet/2.0);
        }
        cout<<setw(100)<<"Credits:"<<_player.userCred<<endl;
    }
};

class PlayerHand : public Hand {
public:
    bool isBusted() const {
        return getValue() > 21;
    }
};

class DealerHand : public Hand {
public:
    bool isBusted() const {
        return getValue() > 21;
    }

    void revealFirstCard() const {
        cout << "Dealer's hand: ";
        switch (cards[1].suit) {
            case Card::HEARTS:
                 printCard(cards[1].value,'H');
                 break;
            case Card::DIAMONDS:
                 printCard(cards[1].value,'D');
                  break;
            case Card::CLUBS:
                printCard(cards[1].value,'C');
                 break;
            case Card::SPADES:
                 printCard(cards[1].value,'S');
                  break;
        }
        cout << "\n [Hidden Cards]   \n\n";
    }

    void printCard(int value,char suit) const
    {
        cout <<endl<< "  _______" << endl;
        cout << " |"<<value<<setw(7)<<"|"<<endl;
        cout << " |"<<setw(2)<< suit<< setw(3)<<suit<<setw(3)<<" |"<<endl;
        cout << " |"<<setw(8)<<"|"<<endl;
        cout << " |"<<setw(2)<<suit<< setw(3)<<suit<<setw(3)<<" |"<<endl;
        cout << " |"<<setw(7)<<value<<"|"<<endl;
        cout << "  -------"<<endl;
    }


};

class BlackjackGame {

private:
    Player& player;
    int bet=0;
    Deck deck;
    PlayerHand playerHand;
    DealerHand dealerHand;
    bool gameOver;

    void printCard(int value,char suit) const
    {
        cout <<endl<< "  _______" << endl;
        cout << " |"<<value<<setw(7)<<"|"<<endl;
        cout << " |"<<setw(2)<< suit<< setw(3)<<suit<<setw(3)<<" |"<<endl;
        cout << " |"<<setw(8)<<"|"<<endl;
        cout << " |"<<setw(2)<<suit<< setw(3)<<suit<<setw(3)<<" |"<<endl;
        cout << " |"<<setw(7)<<value<<"|"<<endl;
        cout << "  -------"<<endl;
    }

    void displayHands() const {
        cout << "Your hand: ";
        for (const auto& card : playerHand.getCards()) {
            switch (card.suit) {
                case Card::HEARTS:
                      printCard(card.value,'H');
                      break;
                case Card::DIAMONDS:
                     printCard(card.value,'D');
                      break;
                case Card::CLUBS:
                     printCard(card.value,'C');
                      break;
                case Card::SPADES:
                     printCard(card.value,'S');
                      break;
            }
        }
        cout <<setw(25) <<"(Total: " << playerHand.getValue() << ")\n\n";
        dealerHand.revealFirstCard();
    }

    void playerTurn() {
        char choice;

        cout<<setw(100)<<"Credit:"<<player.userCred<<endl;
        printColors("Enter bet amount: THEN->CLICK ENTER\n->",5);
        cin>>bet;
        while(bet<100||bet>player.userCred)
        {
            cin.clear();
            cin.ignore(256,'\n');
            cout<<"Invalid bet. MIN - 100 Credits..or low credits."<<endl;
            cin>>bet;
        }

        cout<<("\n\n*Note-> Royals are noted by numbers above ten (Ex. 11->Jack)\n");
        printColors("Do you want to [H]it or [S]tand?",27);
        cout<<endl<<endl;

        cin >> choice;
        if (toupper(choice) == 'H') {
            playerHand.addCard(deck.dealCard());
            if (playerHand.isBusted()) {
                cout << "Busted! You lose.\n" << endl;
                player.userCred-=bet;
                cout<<setw(100)<<"Credit:"<<player.userCred<<endl;
                gameOver = true;
            }
        } else if (toupper(choice) == 'S') {
            cout<<setw(100)<<"Credit:"<<player.userCred<<endl;
            cout << "You chose to stand." << endl;
        } else {
            cout << "Invalid choice. Please enter 'H' or 'S'." << endl;
            playerTurn();
        }
    }

    void dealerTurn() {
        cout<<setw(20);
        printColors("\nDealer's turn...\n\n",8);
        while (dealerHand.getValue() < 17) {
            dealerHand.addCard(deck.dealCard());
        }
        cout << "Dealer's hand: ";
        for (const auto& card : dealerHand.getCards()) {
            switch (card.suit) {
                case Card::HEARTS:
                     printCard(card.value,'H');
                      break;
                case Card::DIAMONDS:
                     printCard(card.value,'D');
                      break;
                case Card::CLUBS:
                     printCard(card.value,'C');
                      break;
                case Card::SPADES:
                     printCard(card.value,'S');
                      break;
            }
        }
        cout <<setw(30)<< "(Total: " << dealerHand.getValue() << ")" << endl;
        if (dealerHand.isBusted() || dealerHand.getValue() < playerHand.getValue()) {
            printColors("Dealer Busted, YOU WIN!\n",2);
            player.userCred+=bet;
        } else if (dealerHand.getValue() > playerHand.getValue()) {
            printColors("Dealer wins.\n\n\n",2);
            player.userCred-=bet;
        } else {
            printColors("It's a tie.\n\n\n",5);
            player.userCred+=(bet/2.0);
        }
        cout<<setw(100)<<"Credit:"<<player.userCred<<endl;
        gameOver = true;

}
public:
     BlackjackGame(Player& _player) : player(_player), gameOver(false) {}


    void play() {
        int bet=0;

        playerHand.addCard(deck.dealCard());
        dealerHand.addCard(deck.dealCard());
        playerHand.addCard(deck.dealCard());
        dealerHand.addCard(deck.dealCard());

        while (!gameOver) {
            displayHands();
            playerTurn();
            if (!playerHand.isBusted()) {
                dealerTurn();
            }
        }
    }

};



//Function Prototypes
void slotMachine(Player&);
//blackJack();
//Poker();
void setCredit(Player&);
void displayMenu();
void clearScreen();
void slotSpin(Player&,int);
void casinoStartPage();
string printColors(const string&, int);
bool playAgain();
void blackJack(Player&);
int randomNumber(int,int);
int evaluateHand(const vector<Card>&,bool);
void simulateThinking();
//Globals



int main()
{
    //messing with size of font study up on/probs switch for simpler
    //*
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(CONSOLE_FONT_INFOEX); //needed to run properly

    cfi.nFont = 0;                          // sets to default font
    cfi.dwFontSize.X = 10;                  // Width of each character in the font
    cfi.dwFontSize.Y = 20;                  // Height
    cfi.FontFamily = FF_DONTCARE;           // complier wont care what font family the font is from
    cfi.FontWeight = FW_BOLD;          // complier will print font weight
    //*/
    wcscpy(cfi.FaceName, L"Lucida Console"); // Choose your font
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);

    //changes screen color (also a play around)
    //system("color 97");

    //variables
    int menuOP;
    int gameEnd=5;
    Player player1;
    //Deck deck;
    //Card deck[52];

    //create good user interface
    //for now
    casinoStartPage();

    cout<<right<<setw(105);
    printColors("User, Please enter your first name to start playing with a more personalized interface!\n",13);
    cout<<setw(70);
    printColors("THEN -> CLICK ENTER\n",2);
    cout<<setw(50)<<"Name:";
    getline(cin,player1.name);
    clearScreen();

    cout<<"Hello, ";
    printColors(static_cast<string>(player1.name),5);
    cout<<"!\n";

    do{

        cout<<setw(105)<<"Credit: "<<player1.userCred<<endl;
        displayMenu();
        cin>>menuOP;

        while(!cin||menuOP>5){
        cin.clear();
        cin.ignore(256,'\n');
        printColors("NOT VALID MENU SELECTION\n->",4);
        cin>>menuOP;
        }

        clearScreen();
        switch(menuOP)
        {
            //Slot Machine
           case 1:
               slotMachine(player1);
                break;

            //BlackJack
           case 2:
               blackJack(player1);
                break;

            //Poker
           case 3: if((player1.userCred)>79000)
           {
               do{
                    int bet=0;
                    PokerGame game(player1);

                    cout<<setw(100)<<"Credit:"<<player1.userCred<<endl;
                    game.displayPlayerHand();
                    printColors("Enter bet : THEN -> CLICK ENTER\n",5);
                    cin>>bet;
                        while(bet<100||bet>player1.userCred)
                        {
                            cin.clear();
                            cin.ignore(256,'\n');
                            cout<<"Invalid bet. MIN - 100 Credits..or low credits."<<endl;
                            cin>>bet;
                        }


                    cout << "\nDo you want to call or fold? (c/f): ";
                    char choice;
                    cin >> choice;
                    if (toupper(choice) == 'F')
                        {
                        player1.userCred-=bet;
                        cout<<setw(100)<<"Credit:"<<player1.userCred<<endl;
                        printColors("You folded. Computer wins.\n\n\n",1);
                    }
                    else{
                    cout << "\nDiscarding and drawing new cards...\n" << endl;
                    game.discardAndDraw();

                    game.displayPlayerHand();

                    game.computerTurn();
                    cout << "\nComputer's turn...\n" << endl;
                    game.displayComputerHand();

                    game.determineWinner(bet);

                    }

                }while(playAgain());
           }else{
                printColors("PLAY MORE GAMES TO EARN SUFFICENT CREDITS NEEDED TO PLAY",4);
           }
                break;

           case 4: setCredit(player1);
               break;

            case 5:
                cout<<"LEAVING CASINO, GOODBYE!"<<endl;
                break;
        }

    }while(menuOP!=gameEnd);

    return 0;
}

void setCredit(Player &player)
{
    Credit level;

    if(player.transactions<1)
    {
        char startLevel;
        cout<<setw(80)<<"To begin play you must first determine at which credit level you wish to begin at...."<<endl;
        cout<<setw(50)<<"[ H ]ard - $30,000"<<endl;
        cout<<setw(52)<<"[ M ]edium - $50,000"<<endl;
        cout<<setw(50)<<"[ E ]asy - $70,000"<<endl;
        cout<<"Enter your start level (letter):";
        cout<<setw(20);
        printColors("THEN -> CLICK ENTER\nEnter Here>>",2);

        do{
        cin>>startLevel;
        if(toupper(startLevel)=='H')
            player.userCred=level.hard;
        else if(toupper(startLevel)=='M')
            player.userCred=level.medium;
        else if(toupper(startLevel)=='E')
            player.userCred=level.easy;
        else
        {
            cin.clear();
            cout<<"Credits system error. Credits not added.";
            cin.ignore(256,'\n');
            cout<<endl;
        }
    }while(player.userCred==0);

        clearScreen();
        cout<<setw(40);
        printColors(static_cast<string>(player.name),2);
        printColors(", your credits have been set. \n",2);

        player.transactions++;
    }else {printColors("Starting Credit has already been set. Continue playing to earn more credits!",4);}
    cout<<endl;
}

void displayMenu()
{
    cout<<"\n NOTE: a $80,000 minimum is required for POKER. Enter a # to selection an option:"<<endl;
    cout<<endl<<endl;

    cout<<setw(80);
    printColors("==========================================",3);
    cout<<endl;
    cout<<setw(80)<<"|             House Menu                 |"<<endl;
    cout<<setw(80);
    printColors("==========================================",3);
    cout<<endl;
    cout<<setw(80);
    printColors("==========================================",3);
    cout<<endl;
    cout<<setw(80)<<"|   1    | Slot Machine                  |"<<endl;
    cout<<setw(80)<<"|   2    | Blackjack                     |"<<endl;
    cout<<setw(80)<<"|   3    | Poker (Locked)                |"<<endl;
    cout<<setw(80)<<"|   4    | Set Credit                    |"<<endl;
    cout<<setw(80)<<"|   5    | Exit                          |"<<endl;
    cout<<setw(80);
    printColors("==========================================",3);
    cout<<endl<<endl;
    cout<<"Enter Menu selection: ";
    //add click enter
}


void slotMachine(Player &player)
{
   // bool spinAgain=false;
   do
    {
        int bet;
        //srand(time(0));

        cout<<setw(64);
        printColors("Slot Machine\n",5);

        cout<<setw(88)<<"___________________________________________________________\n"<<setw(40)<<endl;

        cout<<setw(110)<<"Credit: "<<player.userCred<<endl;

          for (int i = 0; i < 3; ++i) {
            cout << setw(50) << "| " << setw(2) << randomNumber(1, 10) << "  | " << setw(2) << randomNumber(1, 10) << "  | " << setw(2) << randomNumber(1, 10) << "  | " << endl;
            cout << setw(67) << "_________________\n" << endl;
        }


        /*
        for (int i = 0; i < 3; ++i) {
                cout<<setw(50)<< "| " << setw(2) << (i + 1) % 10 + 1 << "  | " << setw(2) << (i + 3) % 10 + 1 << "  | " << setw(2) << (i + 6) % 10 + 1 << "  | " << endl;
                cout<<setw(67)<< "_________________\n" << endl;
                //this_thread::sleep_for(chrono::milliseconds(100));
        }
    */
        cout<<"\n\nPlease enter your bet amount\n|Minimum ($)100 |\n";
        printColors("TO SPIN -> CLICK ENTER\nBET AMMOUNT->",2);
        cin>>bet;

        if(player.transactions!=0)
        {
            while (bet < 100 || bet > player.userCred)
            {
                    cout << "Invalid bet amount. Please enter a valid amount." << endl;
                    cin.clear();
                    cin.ignore(256,'\n');
                    cin>>bet;
            }
        }

            clearScreen();
            if(player.userCred>bet)
            {
            //char play;
            //player.userCred-=bet;
            cout<<setw(110)<<"Credit: "<<player.userCred;
            slotSpin(player,bet);
            }else{
                printColors("BUY MORE CREDIT -> THEN PROCEED TO GAME\n",4);
                break;
                }

        // Ask if the player wants to play again

    } while (playAgain());

}

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void slotSpin(Player& player,int bet)
{
    //srand(time(0));
    int spins = 10; // Number of spins
    int slot1,slot2,slot3;
    const bool winner=(rand()*100)<70;

    for (int spin = 0; spin < spins; ++spin)
    {


        if(spin<9)
        {
            cout<<endl<<setw(70);
            printColors("Spinning the slots...\n",5);
        }else{
            cout<<endl<<setw(65);
            printColors("Spin Results \n",5);
        }

        cout<<setw(88)<<"___________________________________________________________\n"<<setw(40)<<endl;

        if(winner)
        {
            for (int i=0; i < 3; ++i)
            {
            slot1=slot2=slot3=randomNumber(1,10);

            cout<<setw(50)<< "| " << setw(2) << slot1<< "  | " << setw(2) << slot2 << "  | " << setw(2) << slot3<< "  | " << endl;
            cout<<setw(67)<< "_________________\n" << endl;
            this_thread::sleep_for(chrono::milliseconds(100));
            }
        }
        else{
            for (int i=0; i < 3; ++i)
            {
                slot1=randomNumber(1,10);
                slot2=randomNumber(1,10);
                slot3=randomNumber(1,10);

                cout<<setw(50)<< "| " << setw(2) << slot1<< "  | " << setw(2) << slot2 << "  | " << setw(2) << slot3<< "  | " << endl;
                cout<<setw(67)<< "_________________\n" << endl;
                this_thread::sleep_for(chrono::milliseconds(100));
                }
        }



        if(spin!=9)
        clearScreen();
        if(spin==9)
        {
                if(slot1==slot2&&slot2==slot3)
                {
                    cout<<setw(63);
                    printColors("YOU WON!\n",2);
                    player.userCred+=bet;
                }else{
                    cout<<setw(63);
                    printColors("YOU LOST!\n",4);
                    player.userCred-=bet;
                }

        }
        cout<<setw(100)<<"Credit:"<<player.userCred<<endl;
    }
}

/*
string printColors(const string& text, int color)
{
    HANDLE colors = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(colors, color);
    cout << text;
    // Reset color to default after printing
    SetConsoleTextAttribute(colors,7);
    return text;
}
*/

void casinoStartPage()
{
    cout<<setw(76)<<"Welcome to the Casa Del Cordero!\n";
    cout<<setw(72)<<"Nuestro Casa Es Su Casa. \n"<<endl;
    cout<<setw(82);
    printColors("                 . . . . . . . .               \n",9);
    cout<<setw(82);
    printColors("___________ / .               . \\ ___________\n",9);
    cout<<setw(85);
    printColors("|. | . . . . . . Casa Del Cordeo . . . . . . | .| \n",6);
    cout<<setw(83);
    printColors("| .| * * * * * *  *  *  *  *  * * * * * *  |. |\n", 4);
    cout<<setw(83);
    printColors("|. |         * | CASINO & BAR | *          | .|\n",6);
    cout<<setw(83);
    printColors("| . ===========* . . . . . . . *=========== . |\n",9);
    cout<<setw(82)<<"|. |     _                            _    | .|"<<endl;
    cout<<setw(82)<<"| .|    _       _______________        _   |. |"<<endl;
    cout<<setw(82)<<"|. |     _     | |     |     | |      _    | .|"<<endl;
    cout<<setw(82)<<"| .|    _      | |   . | .   | |       _   |. |"<<endl;
    cout<<setw(82)<<"|. |     _     | |     |     | |      _    | .|"<<endl;
    cout<<setw(84);
    printColors("||. ========================================= .||\n", 6);
    cout<< setw(84);
    printColors("|-----------------------------------------------|\n", 4);
    cout << endl;
}

bool playAgain()
{
    char goA;
    cout << "Would you like to play again [letter]?  ";
    //cout<<setw(2);
    printColors("[Y]ES ",2);
    cout<<setw(2)<<"OR ";
    //cout<<setw();
    printColors("[N]O\n",4);
    //cout<<endl;
    cin>>goA;
    //playAgain(goA);
    if(toupper(goA)=='Y')
    {
        clearScreen();
        return true;
    }
    else{
        while(!cin||toupper(goA)!='N')
        {
                cout << "Invalid input. Please enter a valid charcter.\n";
                cin.clear();
                cin.ignore(256,'\n');
                cin>>goA;
        }
    }
    clearScreen();
    return false;
}

void blackJack(Player& player)
{
    if(player.userCred>0)
    {
        do{
            srand(static_cast<unsigned int>(time(0)));
            BlackjackGame game(player); //(game.player);
            game.play();
        } while(playAgain());
    }else{
            printColors("BUY MORE CREDIT -> THEN PROCEED TO GAME\n",4);
    }
}

int randomNumber(int min, int max) {
    static bool firstTime = true;
    if (firstTime) {
        srand(time(NULL));
        firstTime = false;
    }
    return min + rand() % (max - min + 1);
}

/*
void PokerGame::Poker()
{
    do {

        deck.shuffle();

        // Deal cards to dealer
        dealer.addCard(deck.dealCard());
        // Second card is hidden
        Card hiddenCard(Card::SPADES, Card::ACE);
        dealer.addCard(hiddenCard);

        cout << "Dealer's cards:" << endl;
        //printCard(dealer.hand[0]);
        cout << "+----------+" << endl;
        cout << "|  Hidden  |" << endl;
        cout << "|   Card   |" << endl;
        cout << "|          |" << endl;
        cout << "|          |" << endl;
        cout << "|   Hidden |" << endl;
        cout << "|    Card  |" << endl;
        cout << "+----------+" << endl;

        // Deal cards to player
        playerPoker.addCard(deck.dealCard());
        playerPoker.addCard(deck.dealCard());

        // Print player's cards
        cout << "Your cards:" << endl;
        for (const auto& card : playerPoker.hand) {
            //printCard(card);
            cout << endl;
        }

        // Ask player to call or fold
        cout << "Do you want to call or fold? (call/fold): ";
        this_thread::sleep_for(chrono::seconds(1));
        string playerDecision;
        cin >> playerDecision;
        this_thread::sleep_for(chrono::seconds(1));

        // Dealer's turn
        cout << "Dealer is thinking..." << endl;
        simulateThinking();
        cout << "Dealer has made its decision." << endl;
        this_thread::sleep_for(chrono::seconds(1));
        string dealerDecision = (evaluateHand(dealer.hand, true) > evaluateHand(player.hand, false)) ? "call" : "fold";
        cout << "Dealer decides to " << dealerDecision << "." << endl;
        this_thread::sleep_for(chrono::seconds(1));

        // If dealer calls, reveal its second card
        if (dealerDecision == "call") {
            cout << "Dealer's cards:" << endl;
            for (const auto& card : dealer.hand) {
                printCard(card);
                cout << endl;
            }
            cout << "Dealer draws a card:" << endl;
            Card dealerDrawnCard = deck.dealCard();
            dealer.addCard(dealerDrawnCard);
            printCard(dealerDrawnCard);
            cout << endl;
        }

        // Determine winner
        int playerHandValue = evaluateHand(player.hand, false);
        int dealerHandValue = evaluateHand(dealer.hand, true);

        cout << "Your hand value: " << playerHandValue << endl;
        if (dealerDecision == "call") {
            cout << "Dealer's hand value: " << dealerHandValue << endl;
        }
        this_thread::sleep_for(chrono::seconds(1));

        if (playerDecision == "fold") {
            cout << "You folded. Dealer wins!" << endl;
        } else {
            if (dealerDecision == "fold") {
                cout << "Dealer folded. You win!" << endl;
            } else {
                if (playerHandValue > dealerHandValue)
                cout << "You win!" << endl;
                else if (playerHandValue < dealerHandValue)
                    cout << "Dealer wins!" << endl;
                else
                    cout << "It's a tie!" << endl;
            }
        }
    }while (playAgain());
}
*/


/*
void Card::printCard(int value,char suit)
{
    cout << "  _______" << endl;
    cout << " |"<<value<<setw(7)<<"|"<<endl;
    cout << " |"<<setw(2)<< suit<< setw(3)<<suit<<setw(3)<<" |"<<endl;
    cout << " |"<<setw(8)<<"|"<<endl;
    cout << " |"<<setw(2)<<suit<< setw(3)<<suit<<setw(3)<<" |"<<endl;
    cout << " |"<<setw(7)<<value<<"|"<<endl;
    cout << "  -------"<<endl;

}
*/

/*NOTES::
        Functions needed:
        - error check
        - Poker
        - Slot Machine ( AI )
        - credit increase/decrease
        - Slot Machine --> determine win?

        More to fix:
        - fix playAgain in slot loop (probs make function)
            - call in switch
        - try to cut down code (pass some files??)
        - add blackjack
        - add poker
        - infinite loop in playAgain if not a Y or N

*/




