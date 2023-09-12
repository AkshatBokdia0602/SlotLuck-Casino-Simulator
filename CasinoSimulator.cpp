#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <cctype>
#include <vector>
#include <map>
#include <iterator>
#include <algorithm>
using namespace std;

int num;

class Player;

void Final(int , Player * , vector <Player> & , int , map <string, int> &);

class Player
{
    private:
        int Bank_Balance;
        int Wallet;
        int Wins;
        int Losses;
        friend void Random_Number(Player *);
        friend void Random_Card(Player *);
        friend void Random_Number(vector <Player> &, int, bool & , map <string, int>);
        friend void Random_Card(vector <Player> &, int, bool & , map <string, int>);
        friend int Check(Player *);
        friend void Map_Update(Player *, map <string, int> &);

    public:
        string Name;

        Player() {}

        Player(string Name, int Bank_Balance, int Wallet) : Name(Name), Bank_Balance(Bank_Balance), Wallet(Wallet) {}

        void Set();

        void Set(int);

        void Update();

        void Display();

        void Quit();
};

void Player :: Set()
{
    cout << "Enter Player Name: ";
    cin >> Name;
    cout << "Enter Bank Balance: ";
    cin >> Bank_Balance;
    cout << "Enter amount to be added in your wallet: ";
    cin >> Wallet;
    while (Bank_Balance < Wallet)
    {
        cout << "\nYou do not have enough balance to add into your wallet!" << endl;
        cout << "Try Again!" << endl;
        cout << "\nEnter amount to be added in your wallet: ";
        cin >> Wallet;
    }
    Bank_Balance -= Wallet;
    Wins = 0, Losses = 0;
}

void Player :: Set(int i)
{
    cout << "Enter Player "<< i << " Name: ";
    cin >> Name;
    cout << "Enter Bank Balance: ";
    cin >> Bank_Balance;
    cout << "Enter amount to be added in your wallet: ";
    cin >> Wallet;
    while (Bank_Balance < Wallet)
    {
        cout << "\nYou do not have enough balance to add into your wallet!" << endl;
        cout << "Try Again!" << endl;
        cout << "\nEnter amount to be added in your wallet: ";
        cin >> Wallet;
    }
    Bank_Balance -= Wallet;
    Wins = 0, Losses = 0;
}

void Player :: Update()
{
    int Add;
    do
    {
        cout << "\n" << Name << ", You have a Bank Balance of Rs." << Bank_Balance << "\nEnter amount to be added to your Wallet: ";
        cin >> Add;
        if (Bank_Balance - Add < 0)
            cout << "\nInsufficient Bank Balance!!\n" << "Transaction Failed...\n" << "Try Again!!" << endl;
    } while(Bank_Balance - Add < 0);
    
    cout << "\nTransaction Succesful!!" << endl;
    Bank_Balance -= Add;
    Wallet += Add;
}

void Player :: Display()
{
    cout << "Player Name: " << Name << endl;
    cout << "Player Bank Balance: " << Bank_Balance << endl;
    cout << "Player Wallet Balance: " << Wallet << endl;
    cout << "Player has won " << Wins << " times and lost " << Losses << " times.\n" << endl;
}

void Player :: Quit()
{
    cout << "\n" << Name << " has quit." << endl;
    cout << "\nPrinting Final Stats..." << endl;
    Display();
    num -= 1;
    if (num <= 0)
    {
        cout << "All Players have left!!\n" << endl;
    }
    else
        cout << num << " Players Remain!\n" << endl;
}

void Random_Number(Player * a)
{
    srand(time(0));
    int bet, guess;
    cout << "\n\t\t======CASINO RANDOM NUMBER GUESSER RULES!======" << endl;
    cout << "\t1. Choose a number between 1 to 15." << endl;
    cout << "\t2. Winner gets 15 times of the money bet." << endl;
    cout << "\t3. Wrong bet, and you lose the amount you bet.\n" << endl;
    do
    {
        cout << "Enter amount to bet: ";
        cin >> bet;
        if(bet > a->Wallet)
            cout << "\nBetting balance can't be more than current balance!!" << "\nRe-enter balance!!\n" << endl;
    } while(bet > a->Wallet);
    
    do
    {
        cout << "Guess any betting number between 1 & 15: ";
        cin >> guess;
        if (guess <= 0 || guess > 15)
            cout << "\nNumber should be between 1 and 15!!!" << "\nRe-enter number!!\n" << endl;
    } while(guess <= 0 || guess > 15);

    int dice = rand() % 15 + 1;

    if (dice == guess)
    {
        cout << "\nIt is you LUCKY DAY!!! You guessed the right Card!! You have won Rs." << bet * 15 << "!!!!" << endl;
        a->Wins++;
        a->Wallet += bet * 15;
    }
    else if(abs(dice - guess) < 2)
    {
        cout << "\nSo Close!!! The winning number was " << dice << "!" << endl;
        cout << "Better Luck Next Time :(" << endl;
        a->Losses++;
        a->Wallet -= bet;
    }

    else
    {
        cout << "\nUh oh!! The winning number was " << dice << "!" << endl;
        cout << "Better Luck Next Time :(" << endl;
        a->Losses++;
        a->Wallet -= bet;
    }
    cout << "\nPlayer " << a->Name << ", you have a remaining balance of Rs." << a->Wallet << endl;
    cout << "See you Next Time!!" << endl;
}

void Random_Card(Player * a)
{
    srand(time(0));
    int bet, guess_num;
    char guess_suit;
    cout << "\n\t\t======CASINO RANDOM CARD GUESSER RULES!======" << endl;
    cout << "\t1. Choose a card of a particular Suits and Number." << endl;
    cout << "\t2. Player gets 52 times of the money bet if he/she gets the right Card." << endl;
    cout << "\t3. Player gets 13 times the money bet if he/she gets the right Number." << endl;
    cout << "\t4. Player gets 4 times the money bet if he/she gets the right Suite." << endl;
    cout << "\t5. Wrong bet, and you lose the amount you bet.\n" << endl;

    do
    {
        cout << "Enter amount to bet: ";
        cin >> bet;
        if(bet > a->Wallet)
            cout << "\nBetting balance can't be more than current balance!!" << "\nRe-enter balance!!\n" << endl;
    } while(bet > a->Wallet);

    do
    {
        cout << "Guess any suite(C/c -> Clubs, D/d -> Diamonds, H/h -> Hearts, S/s -> Spades): ";
        cin >> guess_suit;
        guess_suit = toupper(guess_suit);
        if (guess_suit != 'C' && guess_suit != 'D' && guess_suit != 'H' && guess_suit != 'S')
            cout << "\nInput should be either C/c or D/d or H/h or S/s!!!" << "Re-enter Character!!\n" << endl;
    } while(guess_suit != 'C' && guess_suit != 'D' && guess_suit != 'H' && guess_suit != 'S');

    do
    {
        cout << "Guess any betting number between 1 & 13(Ace -> 1, 2-10, Jack -> 11, Queen -> 12, King -> 13): ";
        cin >> guess_num;
        if (guess_num <= 0 || guess_num > 13)
            cout << "\nNumber should be between 1 and 13!!!" << "Re-enter number!!\n" << endl;
    } while(guess_num <= 0 || guess_num > 13);

    int num_dice = rand() % 13 + 1;
    int suit = rand() % 4 + 1;

    char suit_dice = (suit == 1) ? 'C' : (suit == 2) ? 'D': (suit == 3) ? 'H' : 'S';

    if (num_dice == guess_num && suit_dice == guess_suit)
    {
        cout << "\nIt is you LUCKY DAY!!! You guessed the right Card!! You have won Rs." << bet * 52 << "!!!!" << endl;
        a->Wins++;
        a->Wallet += bet * 52;
    }
    else if(num_dice == guess_num)
    {
        cout << "\nGG!! You guessed the right Number!! You have won Rs." << bet * 13 << "!!!!" << endl;
        cout << "The winning card was " << suit_dice << num_dice << "!" << endl;
        a->Wins++;
        a->Wallet += bet * 13;
    }
    else if(suit_dice == guess_suit)
    {
        cout << "\nWohoo!! You guessed the right Suit!! You have won Rs." << bet * 4 << "!!!!" << endl;
        cout << "The winning card was " << suit_dice << num_dice << "!" << endl;
        a->Wins++;
        a->Wallet += bet * 4;
    }
    else
    {
        cout << "\nUh oh!! The winning card was " << suit_dice << num_dice << "!" << endl;
        cout << "Better Luck Next Time :(" << endl;
        a->Losses++;
        a->Wallet -= bet;
    }

    cout << "\nPlayer " << a->Name << ", you have a remaining balance of Rs." << a->Wallet << endl;
    cout << "See you Next Time!!" << endl;
}

void Random_Number(vector <Player> & a, int num, bool & c, map <string, int> m)
{
    srand(time(0));
    int bet[num], guess[num];
    cout << "\n\t\t======CASINO RANDOM NUMBER GUESSER RULES!======" << endl;
    cout << "\t1. Choose a number between 1 to 15." << endl;
    cout << "\t2. Winner gets 15 times of the money bet." << endl;
    cout << "\t3. Wrong bet, and you lose the amount you bet.\n" << endl;
    for(int i = 0; i < num; i++)
    {
        do
        {
            cout << "Player " << a[i].Name << ", Enter amount to bet (You can also enter 0 if you don't want to bet): ";
            cin >> bet[i];
            if(bet[i] > a[i].Wallet)
                cout << "\nBetting balance can't be more than current balance!!" << "\nRe-enter balance!!\n" << endl;
        } while(bet[i] > a[i].Wallet);
        
        do
        {
            cout << "Player " << a[i].Name << ", Guess any betting number between 1 & 15: ";
            cin >> guess[i];
            if (guess[i] <= 0 || guess[i] > 15)
                cout << "\nNumber should be between 1 and 15!!!" << "\nRe-enter number!!\n" << endl;
        } while(guess[i] <= 0 || guess[i] > 15);
    }

    int dice = rand() % 15 + 1;

    for(int i = 0; i < num; i++)
    {
        if (dice == guess[i])
        {
            cout << "\nPlayer " << a[i].Name << ", It is you LUCKY DAY!!! You guessed the right Card!! You have won Rs." << bet[i] * 15 << "!!!!" << endl;
            a[i].Wins++;
            a[i].Wallet += bet[i] * 15;
        }
        else if(abs(dice - guess[i]) < 2)
        {
            cout << "\nPlayer " << a[i].Name << ", So Close!!! The winning number was " << dice << "!" << endl;
            cout << "Better Luck Next Time :(" << endl;
            a[i].Losses++;
            a[i].Wallet -= bet[i];
        }

        else
        {
            cout << "\nPlayer " << a[i].Name << ", Uh oh!! The winning number was " << dice << "!" << endl;
            cout << "Better Luck Next Time :(" << endl;
            a[i].Losses++;
            a[i].Wallet -= bet[i];
        }
        cout << "\nPlayer " << a[i].Name << ", you have a remaining balance of Rs." << a[i].Wallet << endl;
        cout << "See you Next Time!!" << endl;
    }
}

void Random_Card(vector <Player> & a, int num, bool & c, map <string, int> m)
{
    srand(time(0));
    int bet[num], guess_num[num];
    char guess_suit[num];
    cout << "\n\t\t======CASINO RANDOM CARD GUESSER RULES!======" << endl;
    cout << "\t1. Choose a card of a particular Suits and Number." << endl;
    cout << "\t2. Player gets 52 times of the money bet if he/she gets the right Card." << endl;
    cout << "\t3. Player gets 13 times the money bet if he/she gets the right Number." << endl;
    cout << "\t4. Player gets 4 times the money bet if he/she gets the right Suite." << endl;
    cout << "\t5. Wrong bet, and you lose the amount you bet.\n" << endl;

    for(int i = 0; i < num; i++)
    {
        do
        {
            cout << "Player " << a[i].Name << ", Enter amount to bet (You can also enter 0 if you don't want to bet): ";
            cin >> bet[i];
            if(bet[i] > a[i].Wallet)
                cout << "\nBetting balance can't be more than current balance!!" << "\nRe-enter balance!!\n" << endl;
        } while(bet[i] > a[i].Wallet);

        do
        {
            cout << "Player " << a[i].Name << ", Guess any suite(C/c -> Clubs, D/d -> Diamonds, H/h -> Hearts, S/s -> Spades): ";
            cin >> guess_suit[i];
            guess_suit[i] = toupper(guess_suit[i]);
            if (guess_suit[i] != 'C' && guess_suit[i] != 'D' && guess_suit[i] != 'H' && guess_suit[i] != 'S')
                cout << "\nInput should be either C/c or D/d or H/h or S/s!!!" << "Re-enter Character!!\n" << endl;
        } while(guess_suit[i] != 'C' && guess_suit[i] != 'D' && guess_suit[i] != 'H' && guess_suit[i] != 'S');

        do
        {
            cout << "Player " << a[i].Name << ", Guess any betting number between 1 & 13(Ace -> 1, 2-10, Jack -> 11, Queen -> 12, King -> 13): ";
            cin >> guess_num[i];
            if (guess_num[i] <= 0 || guess_num[i] > 13)
                cout << "\nNumber should be between 1 and 13!!!" << "Re-enter number!!\n" << endl;
        } while(guess_num[i] <= 0 || guess_num[i] > 13);
    }

    int num_dice = rand() % 13 + 1;
    int suit = rand() % 4 + 1;

    char suit_dice = (suit == 1) ? 'C' : (suit == 2) ? 'D': (suit == 3) ? 'H' : 'S';

    for(int i = 0; i < num; i++)
    {
        if (num_dice == guess_num[i] && suit_dice == guess_suit[i])
        {
            cout << "\nPlayer " << a[i].Name << ", It is you LUCKY DAY!!! You guessed the right Card!! You have won Rs." << bet[i] * 52 << "!!!!" << endl;
            a[i].Wins++;
            a[i].Wallet += bet[i] * 52;
        }
        else if(num_dice == guess_num[i])
        {
            cout << "\nPlayer " << a[i].Name << ", GG!! You guessed the right Number!! You have won Rs." << bet[i] * 13 << "!!!!" << endl;
            cout << "The winning card was " << suit_dice << num_dice << "!" << endl;
            a[i].Wins++;
            a[i].Wallet += bet[i] * 13;
        }
        else if(suit_dice == guess_suit[i])
        {
            cout << "\nPlayer " << a[i].Name << ", Wohoo!! You guessed the right Suit!! You have won Rs." << bet[i] * 4 << "!!!!" << endl;
            cout << "The winning card was " << suit_dice << num_dice << "!" << endl;
            a[i].Wins++;
            a[i].Wallet += bet[i] * 4;
        }
        else
        {
            cout << "\nPlayer " << a[i].Name << ", Uh oh!! The winning card was " << suit_dice << num_dice << "!" << endl;
            cout << "Better Luck Next Time :(" << endl;
            a[i].Losses++;
            a[i].Wallet -= bet[i];
        }
        cout << "\nPlayer " << a[i].Name << ", you have a remaining balance of Rs." << a[i].Wallet << endl;
        cout << "See you Next Time!!" << endl;
    }
}

int Check(Player * ply)
{
    if (ply->Wallet == 0)
    {
        if (ply->Bank_Balance == 0) 
        {
            cout << "\nPlayer " << ply->Name << ", you have no money to play and are forced to quit!!" << endl;
            return 0;
        }
        else
        {
            cout << "\nPlayer " << ply->Name << ", you have no money in your wallet!!" << endl;
            cout << "Transfer money from your bank to continue or you can quit!!" << endl;
            return 1;
        }
    }
    else
        return 2;
}

void Final(int n, Player * ply)
{
    int choice;
    if (n == 1)
    {
        cout << "\nEnter 1 to add money to wallet or 0 to quit: ";
        cin >> choice;
        if (choice == 1)
            ply->Update();
        else
        {
            ply->Quit();
            delete ply;
        }
            
    }
    else if (n == 0)
    {
        ply->Quit();
        delete ply;
    }
}

void Final(int n, Player * ply, vector <Player> & a, int i, map <string, int> & m)
{
    int choice;
    if (n == 1)
    {
        cout << "\nEnter 1 to add money to wallet or 0 to quit: ";
        cin >> choice;
        if (choice == 1)
        {
            ply->Update();
        }
        else
        {
            Map_Update(ply, m);
            ply->Quit();
            vector <Player> :: iterator it = a.begin();
            a.erase(it + i);
            i--;
        }
    }
    else if (n == 0)
    {
        Map_Update(ply, m);
        ply->Quit();
        vector <Player> :: iterator it = a.begin();
        a.erase(it + i);
        i--;
    }
}

inline bool End()
{
    if (num == 0) 
        return false;
    else
        return true;
}

void InitialCondition(int num)
{
    if (num < 1 || num > 3)
    {   
        cout << "\nNumber of Players selected does not match the REQUIRED CONDITION!!\n" << endl;
        cout << "Exiting...\n" << endl;
        exit(0);
    }
    else if (num == 1)
        cout << "\n1 Player Selected!!\n" << endl;
    else
        cout << "\n" << num << " Number of Players Selected!!\n" << endl;
}

void Map_Update(Player * a, map <string, int> & m)
{
    m[a->Name] = a->Wins;
}

bool Comp(pair<string, int> a, pair<string, int> b)
{
    return (a.second > b.second);
}

void LeaderBoard(map <string, int> m)
{
    cout << "\nLEADERBOARD!!!\n" << endl;

    vector<pair<string, int> > vec;
    map <string, int> :: iterator it;

    for (it = m.begin(); it!= m.end(); it++) 
    {
        vec.push_back(make_pair(it->first, it->second));
    }

    sort(vec.begin(), vec.end(), Comp);

    cout << "Player Name" << "\t\t" << "Wins" << endl; 
    for (int i = 0; i < vec.size(); i++)
	{
		cout << vec[i].first << "\t\t\t" << vec[i].second << endl;
	}
}

int main()
{
    bool flag = true, c = false;
    cout << "\t!!!!!!!!!!!! Welcome to SlotLuck - One of the finest Casino Simulator !!!!!!!!!!!!" << endl;
    cout << "\t\t\tWe Offer An Eclectic Mix Of Casino Games!!!" << endl;
    cout << "\tChoose wisely and Remember - “The best throw of the dice is to throw them away." << endl;
    cout << "\nEnter No. of Players(1-3): ";
    cin >> num;
    int temp = num;

    InitialCondition(num);

    Player * ply = (num == 1) ? new Player() : new Player[3];

    if (num == 1)
        ply->Set();
    
    else
    {
        for (int i = 0; i < num; i++) { (ply + i)->Set(i+1);}
    }

    static vector <Player> plys(ply, ply + num);
    map <string, int> lb;

    if (num != 1)
        delete [] ply;

    while (flag == true)
    {
        if(num == 1 && c == false)
        {
            int choice, final;
            cout << "\nLet's Play, Player 1!!!\n" << endl;
            cout << "1. Random Number Guesser" << endl;
            cout << "2. Random Card Guesser" << endl;
            cout << "3. Add Money to Wallet" << endl;
            cout << "4. Exit\n" << endl;
            cout << "Enter your choice: ";
            cin >> choice;

            switch(choice)
            {
                case 1:
                    {
                        Random_Number(ply);
                        Final(Check(ply), ply);
                    }
                    break;
                case 2:
                    {
                        Random_Card(ply);
                        Final(Check(ply), ply);
                    }
                    break;
                case 3:
                    ply->Update();
                    break;
                case 4:
                    {
                        cout << "\nYou have decided to quit! Enter 1 to confirm or any other digit to not confirm: ";
                        cin >> final;
                        if (final == 1)
                        {
                            ply->Quit();
                            delete ply;
                        }
                        else
                            cout << "\nYou have decided to continue!!" << endl;
                    }
                    break;
                default:
                    cout << "\nWrong choice!!" << endl;
                    break;
            }
        }
        else
        {
            int choice, final, opt;
            cout << "\nLet's Play, Players!!!\n" << endl;
            cout << "1. Random Number Guesser" << endl;
            cout << "2. Random Card Guesser" << endl;                
            cout << "3. Add Money to Wallet" << endl;
            cout << "4. Exit\n" << endl;
            cout << "Enter your choice: " << endl;
            cin >> choice;

            switch(choice)
            {
                case 1:
                    {
                        Random_Number(plys, num, c, lb);
                        int i = 0;
                        while(i < num)
                        {
                            int next = Check(&plys[i]);
                            Final(next, &plys[i], plys, i, lb);
                            c = true;
                            i++;
                        }
                    }
                    break;
                case 2:
                    {
                        Random_Card(plys, num, c, lb);
                        int i = 0;
                        while(i < num)
                        {
                            int next = Check(&plys[i]);
                            Final(next, &plys[i], plys, i, lb);
                            c = true;
                            i++;
                        }
                    }
                    break;
                case 3:
                    {
                        for(int i = 0; i < num; i++)
                        {
                            cout << "\nPlayer " <<  plys[i].Name << ", Enter 1 to Add Money to Wallet or any other digit if you don't want to!" << endl;
                            cin >> opt;
                            if (opt == 1)
                                (&plys[i])->Update();
                            else
                                cout << "\nPlayer " <<  plys[i].Name << ", you have decided to not add money to your wallet!" << endl;
                        }
                    } 
                    break;
                case 4:
                    {
                        int i = 0;
                        while(i < num)
                        {
                            cout << "\nPlayer " << plys[i].Name << ", Do you wish to quit? Enter 1 to confirm or any other digit to not confirm!!" << endl;
                            cin >> final;
                            if (final == 1)
                                {
                                    Final(0, &plys[i], plys, i, lb);
                                    c = true;
                                    i--;
                                }
                            else
                                cout << "\nPlayer " << plys[i].Name << ", you have decided to continue!!" << endl;
                            i++;
                        }
                    }
                    break;
                default:
                    cout << "Wrong choice!!\n" << endl;
                    break;
            }
        }
        flag = End();
    }
    if (temp != 1)
        LeaderBoard(lb);
    cout << "\t\t\t\t\t============= THANKS FOR PLAYING!!! =============\n\n" << endl;
    return 0;
}