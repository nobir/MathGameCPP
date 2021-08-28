#include <iostream>
#include <ctime>

#define NUMBER 51

using namespace std;

class Random
{
private:
    int r = time(NULL);
    char opr[4] = {'+', '-', 'X', '/'};

    char randOpr(void);

protected:
    int point = 0,
        lives = 2,
        randNum1 = (r % (NUMBER + 1)),            /// Generate 1 to 50 random number
        randNum2 = ((r % NUMBER) + (NUMBER + 1)), /// Generate 51 to 100 random number
        randOprator = (r % 4);                    /// Generate 1 to 4 number for randomly display Operator
    char oprChar = randOpr(),
         info[60] = "If you want to exit the game Then input 0 and hit Entered\n";

    void resetAll(void);
};

void Random::resetAll(void)
{
    r = time(NULL);
    randNum1 = (r % 51);
    randNum2 = ((r % 50) + 51);
    randOprator = (r % 4);
    oprChar = randOpr();
}

char Random::randOpr(void)
{
    return opr[randOprator];
}

class Game : public Random
{
private:
    int x,
        res;

    int isExit(void);
    int result(void);
    int checkResult(void);
    void showResult(void);
    void randEquation(void);

public:
    void init(void);
};

int Game::isExit(void)
{
    if (x == 0 || lives == 0)
    {
        if (point < 0)
            point = 0;
        cout << "\n\tThanks for playing Math Game :D\n";
        cout << "\tYou don't have any live :(\n";
        cout << "\tYour Total Point is: " << point << "\n\n";
        return 1;
    }
    else
    {
        return 0;
    }
}

int Game::result()
{
    if (oprChar == '+')
        res = randNum1 + randNum2;
    else if (oprChar == '-')
        res = randNum2 - randNum1;
    else if (oprChar == 'X')
        res = randNum1 * randNum2;
    else if (oprChar == '/')
        res = randNum2 / randNum1;

    return res;
}

int Game::checkResult()
{
    if (x == result())
        return 1;
    else if (x != result())
        return 0;
    return 0;
}

void Game::showResult(void)
{
    if (checkResult())
    {
        point++;
        cout << "\n\tCorrect !!\n";
        cout << "\tYou have " << lives + 1 << " Live to go\n";
        cout << "\tYour Point is: " << point << "\n\n";
    }
    else if (!checkResult())
    {
        lives--;
        point--;
        cout << "\n\tWrong Answer :(\n\tAnswer is: " << result() << "\n\ttry again.\n\n";

        if (point < 0)
            point = 0;
        cout << "\tYou have " << lives + 1 << " Live to go\n";
        cout << "\tYour Point is: " << point << "\n\n";
    }
}

void Game::randEquation(void)
{
    if (oprChar == '-' || oprChar == '/')
    {
        cout << randNum2 << " "
             << oprChar << " "
             << randNum1 << " = ??\n"
             << info;
        if (oprChar == '/')
            cout << "** Remember You have to floor the Answer eg. 1.54556 as 1 **\n";
        cout << "=> ";
        cin >> x;
    }
    else
    {
        cout << randNum1 << " "
             << oprChar << " "
             << randNum2 << " = ??\n"
             << info
             << "=> ";
        cin >> x;
    }
}

void Game::init()
{
    resetAll();
    randEquation();

    if (isExit())
        return;

    showResult();
    init();
}

int main()
{
    // User Points
    Game mathGame;

    // Initialize The Math Game
    mathGame.init();

    return 0;
}
