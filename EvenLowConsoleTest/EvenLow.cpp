// Henri Grant
// https://stackoverflow.com/questions/17335816/clear-screen-using-c
// ^ to clear screen
// https://stackoverflow.com/questions/10918206/cross-platform-sleep-function-for-c
// ^ to sleep
// https://stackoverflow.com/questions/2971254/c-sleep-and-loops
// ^ cout.flush();
// https://stackoverflow.com/questions/14668326/iterate-through-string-char-by-char
// https://stackoverflow.com/questions/9438209/for-every-character-in-string
// ^ print char for char
// https://stackoverflow.com/questions/6051865/how-to-read-and-write-to-a-text-file-in-c
// ^ use txt file as "database" to have user's money/score store.
#include <iostream>
#include <stdlib.h>
#include <chrono>  // for sleep
#include <thread>  // for sleep
#include <fstream> // File stream
#include <string>
using namespace std;
// this function will output any string to the screen character by character
void print(const string& infix)
{
    for (unsigned int i = 0; i < infix.length(); i++)
    {

        char c = infix[i]; // this is your character
        cout << c;
        this_thread::sleep_for(chrono::milliseconds(30));
        cout.flush(); // flushes the buffer
    }
}

// This function sets up db.txt to store the user's data.
int set_up_txt()
{
    int money_from_db;
    ifstream moneyfile; //input file stream monefile
    moneyfile.open("db.txt");
    // if db.text exists, put the data into money_from_db
    if (moneyfile)
    {
        moneyfile >> money_from_db;
    }
    // if db.txt does not exist, then create it and insert 100
    else
    {
        ofstream dbfile("db.txt");
        if (dbfile.is_open())
        {
            dbfile << 100;
        }
        dbfile.close();
    }
    return money_from_db;
}
// this void will take money from the gamefunc and output it to the txt file :D
void money_to_db(int moneyout)
{
    ofstream dbfile("db.txt"); // output file stream db.txt
    if (dbfile.is_open()) // why is this an if statement?!
    {
        dbfile << moneyout;
    }
    dbfile.close();
    return;
}

void game_func()
{
    int money = set_up_txt();
    int wager;
    int gen_num;
    int guess_even;
    int guess_low;
    bool low;
    bool even;
    bool correct1;
    bool correct2;
    int cont_game = 1;
    while (cont_game == 1)
    {
        correct1 = false;
        correct2 = false;
        gen_num = rand() % 100 + 1;
        if (gen_num < 50)
        {
            low = true;
        }
        if (gen_num >= 50)
        {
            low = false;
        }
        if (gen_num % 2 == 0)
        {
            even = true;
        }
        if (gen_num % 2 != 0)
        {
            even = false;
        }

        do
        {
            print("How much do you want to wager?");
            cin >> wager;
            if (wager > money)
                print("Your wager has to be LESS than your money.");
            else if (wager <= 0)
                print("Your wager has to be greater than 0");
            else if (!cin) // check to see if user inputted an integer
            {
                cin.clear();                                                   // "Reset the state of the stream" -greyfade on StackOverflow
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // "Expunge the remaining input" -greyfade on StackOverflow
                print("Please enter an integer.\n");
                cin >> wager;
            }
            else
            {
                cout << "Your wager is:" << wager << endl;
            }

        } while ((wager > money) || (wager <= 0) || (!cin));
        do
        {
            print("'0': high '1': low\n");
            cin >> guess_low;
            if (!cin) // check to see if user inputted an integer
            {
                cin.clear();                                                   // "Reset the state of the stream" -greyfade on StackOverflow
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // "Expunge the remaining input" -greyfade on StackOverflow
                print("Please enter 0 or 1\n");
                print("Please enter again\n");
                cin >> guess_low;
            }
        } while (((guess_low != 0) && (guess_low != 1)) || !cin);
        do
        {
            print("'0': odd '1': even\n");
            cin >> guess_even;
            if (!cin) // check to see if user inputted an integer
            {
                cin.clear();                                                   // "Reset the state of the stream" -greyfade on StackOverflow
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // "Expunge the remaining input" -greyfade on StackOverflow
                print("Please enter 0 or 1\n");
                print("Please enter again\n");
                cin >> guess_even;
            }
        } while ((guess_even != 0) && (guess_even != 1));

        if ((low == true && guess_low == 1) || (low == false && guess_low == 0))
        {
            correct1 = true;
        }
        if ((even == true && guess_even == 1) || (even == false && guess_even == 0))
        {
            correct2 = true;
        }

        print("The number is:\n");

        this_thread::sleep_for(chrono::seconds(1));

        for (int x = 1; x <= 3; x++)
        {
            cout << x << endl;
            this_thread::sleep_for(chrono::seconds(1));
        }

        cout << gen_num << endl;

        if (correct1 == true && correct2 == true)
        {
            money += wager;
            cout << "Your new amount of cash is:    $" << money << endl;
            print("Congrats! Do you want an award?\n");
        }

        else
        {
            money -= wager;
            money_to_db(money);
            print("You lose!\n");
            cout << "Your new amount of cash is:    $" << money << endl;
        }

        print("Do you want to continue?\n");
        print("Enter 1 for yes and 0 for no:  ");
        cin >> cont_game;
    }
}

int main()
{
    set_up_txt();

    cout << "\n";

    print("You will guess if the number is odd or even, high or low!\n");
    this_thread::sleep_for(chrono::seconds(1));

    string startingmoney = to_string(set_up_txt());
    print(startingmoney);
    cout << endl;
    this_thread::sleep_for(chrono::seconds(1));

    game_func();
}