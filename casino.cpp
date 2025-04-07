#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <limits>

using namespace std;

class Player {
public:
    string name;
    int balance;

    Player(string playerName, int startingBalance = 1000) {
        name = playerName;
        balance = startingBalance;
    }

    bool canBet(int amount) {
        return balance >= amount;
    }

    void updateBalance(int amount) {
        balance += amount;
    }

    void displayStatus() {
        cout << "\nPlayer: " << name << " | Balance: $" << balance << endl;
    }
};

int generateRandomNumber(int lower, int upper) {
    return rand() % (upper - lower + 1) + lower;
}

void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void playGame(Player &player) {
    int lower = 1, upper = 10, maxTries = 5;
    cout << "\nSelect difficulty:\n1. Easy (1-10)\n2. Medium (1-50)\n3. Hard (1-100)\nEnter choice: ";
    int choice;
    cin >> choice;

    switch(choice) {
        case 1: lower = 1; upper = 10; maxTries = 5; break;
        case 2: lower = 1; upper = 50; maxTries = 7; break;
        case 3: lower = 1; upper = 100; maxTries = 10; break;
        default: cout << "Invalid choice. Defaulting to Easy.\n";
    }

    int bet;
    cout << "Enter your bet amount: $";
    cin >> bet;

    if (!player.canBet(bet)) {
        cout << "Insufficient balance! Current balance: $" << player.balance << "\n";
        return;
    }

    int numberToGuess = generateRandomNumber(lower, upper);
    int guess, attempts = 0;
    bool guessed = false;

    cout << "\nGuess the number between " << lower << " and " << upper << ". You have " << maxTries << " tries.\n";

    while (attempts < maxTries) {
        cout << "Attempt " << (attempts + 1) << ": ";
        cin >> guess;

        if (cin.fail()) {
            clearInput();
            cout << "Invalid input. Try again.\n";
            continue;
        }

        attempts++;
        if (guess == numberToGuess) {
            guessed = true;
            int winnings = bet * (maxTries - attempts + 1);
            cout << "🎉 Correct! You won $" << winnings << " in " << attempts << " attempts!\n";
            player.updateBalance(winnings);
            break;
        } else if (guess < numberToGuess) {
            cout << "Too low!\n";
        } else {
            cout << "Too high!\n";
        }
    }

    if (!guessed) {
        cout << "💀 Out of tries! The correct number was: " << numberToGuess << ". You lost $" << bet << "\n";
        player.updateBalance(-bet);
    }

    player.displayStatus();
}

int main() {
    srand(static_cast<unsigned int>(time(0)));
    cout << "🎲 Welcome to the Casino Number Guessing Game!\nEnter your name: ";
    string playerName;
    getline(cin, playerName);

    Player player(playerName);
    char playAgain;

    do {
        player.displayStatus();
        playGame(player);

        if (player.balance <= 0) {
            cout << "You've run out of balance! Game over.\n";
            break;
        }

        cout << "Do you want to play again? (Y/N): ";
        cin >> playAgain;
        clearInput();

    } while (toupper(playAgain) == 'Y');

    cout << "\n🎮 Thanks for playing, " << player.name << "! Final balance: $" << player.balance << endl;
    return 0;
}
