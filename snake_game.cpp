#include <iostream>
#include <cstdlib>
#include <ctime>

#if defined(_WIN32) || defined(_WIN64)
#include <conio.h>
#include <windows.h>
#define CLEAR "cls"

#else
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#define CLEAR "clear"

int _kbhit()
{
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF)
    {
        ungetc(ch, stdin);
        return 1;
    }
    return 0;
}

int _getch()
{
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

#endif

using namespace std;
enum Direction
{
    STOP = 0,
    UP,
    DOWN,
    RIGHT,
    LEFT
};

class game
{
protected:
    int width;
    int height;
    int score;
    Direction dir;
    bool gameIsOver;

public:
    game()
    {
        this->width = 70;
        this->height = 20;
        this->score = 0;
        this->dir = Direction::STOP;
        this->gameIsOver = false;
    }
};

class snake : protected game
{
protected:
    int snakeX;
    int snakeY;
    int *TailX;
    int *TailY;
    int Tail_length;

public:
    snake()
    {
        snakeX = width / 2;
        snakeY = height / 2;
        Tail_length = 0;
        TailX = new int[100];
        TailY = new int[100];
    }
};

class fruit : protected snake
{
protected:
    int fruitX;
    int fruitY;

public:
    fruit()
    {
        fruitX = rand() % (width - 1);
        fruitY = rand() % (height - 1);
    }
};

class Main : protected fruit
{
public:
    void MainGame(string playerName)
    {
        system(CLEAR);

        for (int i = 0; i < width + 2; i++)
            cout << "-";
        cout << endl;

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j <= width + 1; j++)
            {
                if (j == 0 || j == width + 1)
                    cout << "|";

                else if (j == snakeX && i == snakeY)
                    cout << "O";

                else if (j == fruitX && i == fruitY)
                    cout << "$";

                else
                {
                    bool find = false;
                    for (int k = 0; k < Tail_length; k++)
                    {
                        if (TailX[k] == j && TailY[k] == i)
                        {
                            cout << "o";
                            find = true;
                        }
                    }
                    if (!find)
                        cout << " ";
                }
            }
            cout << endl;
        }
        for (int i = 0; i <= width + 1; i++)
            cout << "-";
        cout << endl;

        cout << playerName << "'s Score: " << score << endl;
    }

    void updateGame()
    {
        if (dir == STOP)
        {
            return;
        }

        int prevX = TailX[0];
        int prevY = TailY[0];

        int prevXX, prevYY;
        TailX[0] = snakeX;
        TailY[0] = snakeY;

        for (int i = 1; i < Tail_length; i++)
        {
            prevXX = TailX[i];
            prevYY = TailY[i];

            TailX[i] = prevX;
            TailY[i] = prevY;

            prevX = prevXX;
            prevY = prevYY;
        }

        if (dir == LEFT)
        {
            snakeX--;
        }
        else if (dir == RIGHT)
        {
            snakeX++;
        }
        else if (dir == UP)
        {
            snakeY--;
        }
        else
        {
            snakeY++;
        }

        if (snakeX >= width || snakeX <= 0 || snakeY >= height || snakeY <= 0)
            gameIsOver = true;

        for (int i = 0; i < Tail_length; i++)
        {
            if (TailX[i] == snakeX && TailY[i] == snakeY)
                gameIsOver = true;
        }

        if (snakeX == fruitX && snakeY == fruitY)
        {
            score += 10;
            fruitX = rand() % (width - 1);
            fruitY = rand() % (height - 1);
            Tail_length++;
        }
    }

    void input()
    {
        if (_kbhit())
        {
            switch (_getch())
            {
            case 'a':
                dir = LEFT;
                break;
            case 'd':
                dir = RIGHT;
                break;
            case 'w':
                dir = UP;
                break;
            case 's':
                dir = DOWN;
                break;
            case 'x':
                gameIsOver = true;
                break;
            }
        }
    }
    bool isGameOver()
    {
        return gameIsOver;
    }
};

int difficulty()
{
    int dif, choice;
    cout << "\n SET DIFFICULTY \n 1 : EASY\n 2 : MEDIUM\n 3 : HARD "
            "\n NOTE : If not chosen any key then difficulty will be automatically set to medium."
            "\n Choose difficulty : ";

    cin >> choice;

    switch (choice)
    {
    case 1:
        dif = 100;
        break;
    case 2:
        dif = 150;
        break;
    case 3:
        dif = 200;
        break;
    default:
        dif = 150;
    }
    return dif;
}

int main()
{
    string playerName;
    cout << "enter your name: ";
    cin >> playerName;
    int dif = difficulty();

    Main snakeGame;
    int play = 0;
    while (!snakeGame.isGameOver())
    {

        snakeGame.MainGame(playerName);
        snakeGame.input();
        snakeGame.updateGame();

         #if defined(_WIN32) || defined(_WIN64)
                Sleep(dif);
        #else
                usleep(dif * 900);
        #endif
    }
    cout << "Do you want to restart the game?" << endl;
    cout << "Press 1 to start again." << endl;
    cout << endl;
    cin >> play;
    if (play == 1)
    {
        main();
    }
    
    return 0;
}
