#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <memory> // for smart pointers
#include <time.h>
using namespace std;

#define INFINITY std::numeric_limits<int>::max()

class GameBoard
{
public:
    static const int BSIZE = 3;
    static const int maxMoves = 9;
    static const int minMovesToWin = 5;

    GameBoard()
    {
        fill_board();
    }

    void displayBoard() const
    {
        cout << "\n\t\t------------------------\n";
        for (int row = 0; row < BSIZE; row++)
        {
            cout << "\t\t| ";
            for (int col = 0; col < BSIZE; col++)
            {
                cout << board[row][col] << " \t| ";
            }
            cout << "\n\t\t------------------------\n";
        }
    }

    bool placeMove(char player, int row, int col)
    {
        if (board[row][col] == ' ')
        {
            board[row][col] = player;
            totalMoves++;
            return true;
        }
        return false;
    }

    bool checkForWins(char player) const
    {
        if (totalMoves >= minMovesToWin)
        {
            for (int i = 0; i < BSIZE; i++)
            {
                if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) ||
                    (board[0][i] == player && board[1][i] == player && board[2][i] == player))
                    return true;
            }
            if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
                (board[0][2] == player && board[1][1] == player && board[2][0] == player))
                return true;
        }
        return false;
    }

    bool checkForDraw() const
    {
        return totalMoves == maxMoves;
    }

    vector<vector<char>> getBoard() const
    {
        vector<vector<char>> b(BSIZE, vector<char>(BSIZE));
        for (int i = 0; i < BSIZE; i++)
        {
            for (int j = 0; j < BSIZE; j++)
            {
                b[i][j] = board[i][j];
            }
        }
        return b;
    }

    // For AI use: simulate an external board without affecting original
    void simulateBoard(const vector<vector<char>> &b)
    {
        totalMoves = 0;
        for (int i = 0; i < BSIZE; i++)
        {
            for (int j = 0; j < BSIZE; j++)
            {
                board[i][j] = b[i][j];
                if (board[i][j] == 'X' || board[i][j] == 'O')
                    totalMoves++;
            }
        }
    }

private:
    char board[BSIZE][BSIZE];
    int totalMoves = 0;

    void fill_board()
    {
        for (int i = 0; i < BSIZE; i++)
            for (int j = 0; j < BSIZE; j++)
                board[i][j] = ' ';
        totalMoves = 0;
    }
};

// Abstract player class
class Player
{
protected:
    char player;

public:
    Player(char p) : player(p) {}
    virtual void makeMove(GameBoard &board) = 0;
    char getPlayerChar() const { return player; }
};

class HumanPlayer : public Player
{
public:
    HumanPlayer(char p) : Player(p) {}

    void makeMove(GameBoard &board) override
    {
        string input;
        while (true)
        {
            cout << "PLAYER " << player << ", select a number from 1-9: ";
            getline(cin, input);

            if (!input.empty() && input.size() == 1 && isdigit(input[0]))
            {
                int num = input[0] - '0';
                if (num >= 1 && num <= 9)
                {
                    int row = (num - 1) / 3;
                    int col = (num - 1) % 3;
                    if (board.placeMove(player, row, col))
                        break;
                    else
                        cout << "Position already taken. Try again.\n";
                }
                else
                    cout << "Please enter a number between 1-9.\n";
            }
            else
            {
                cout << "Invalid input. Try again.\n";
            }
        }
    }
};

class AIPlayer : public Player
{
public:
    AIPlayer(char p) : Player(p) {}

    void makeMove(GameBoard &board) override
    {
        int bestScore = -INFINITY;
        int moveRow = -1, moveCol = -1;

        auto current = board.getBoard();

        for (int i = 0; i < GameBoard::BSIZE; ++i)
        {
            for (int j = 0; j < GameBoard::BSIZE; ++j)
            {
                if (current[i][j] == ' ')
                {
                    current[i][j] = player;
                    int score = minimax(current, false, 0, -INFINITY, INFINITY);
                    current[i][j] = ' ';
                    if (score > bestScore)
                    {
                        bestScore = score;
                        moveRow = i;
                        moveCol = j;
                    }
                }
            }
        }

        board.placeMove(player, moveRow, moveCol);
    }

private:
    int minimax(vector<vector<char>> &b, bool isMax, int depth, int alpha, int beta)
    {
        char opponent = (player == 'X') ? 'O' : 'X';
        GameBoard temp;
        temp.simulateBoard(b);

        if (temp.checkForWins(player)) return 10 - depth;
        if (temp.checkForWins(opponent)) return depth - 10;
        if (temp.checkForDraw()) return 0;

        if (isMax)
        {
            int maxEval = -INFINITY;
            for (int i = 0; i < GameBoard::BSIZE; ++i)
            {
                for (int j = 0; j < GameBoard::BSIZE; ++j)
                {
                    if (b[i][j] == ' ')
                    {
                        b[i][j] = player;
                        int eval = minimax(b, false, depth + 1, alpha, beta);
                        b[i][j] = ' ';
                        maxEval = max(maxEval, eval);
                        alpha = max(alpha, eval);
                        if (beta <= alpha)
                            return maxEval;
                    }
                }
            }
            return maxEval;
        }
        else
        {
            int minEval = INFINITY;
            for (int i = 0; i < GameBoard::BSIZE; ++i)
            {
                for (int j = 0; j < GameBoard::BSIZE; ++j)
                {
                    if (b[i][j] == ' ')
                    {
                        b[i][j] = opponent;
                        int eval = minimax(b, true, depth + 1, alpha, beta);
                        b[i][j] = ' ';
                        minEval = min(minEval, eval);
                        beta = min(beta, eval);
                        if (beta <= alpha)
                            return minEval;
                    }
                }
            }
            return minEval;
        }
    }
};

class TicTacToe
{
public:
    void displayBoard_numbering() const
    {
        cout << "\n\t\t----------------------\n";
        cout << "\t\t|  1  |  2  |  3  |\n";
        cout << "\t\t----------------------\n";
        cout << "\t\t|  4  |  5  |  6  |\n";
        cout << "\t\t----------------------\n";
        cout << "\t\t|  7  |  8  |  9  |\n";
        cout << "\t\t----------------------\n";
    }

    void playGame()
    {
        char choice;
        cout << "Do you want to play against AI? (y/n): ";
        cin >> choice;
        cin.ignore();

        if (choice == 'y' || choice == 'Y')
        {
            humanPlayerX = make_unique<HumanPlayer>('X');
            aiPlayerO = make_unique<AIPlayer>('O');
            currentPlayer = humanPlayerX.get();
        }
        else
        {
            humanPlayerX = make_unique<HumanPlayer>('X');
            humanPlayerO = make_unique<HumanPlayer>('O');
            currentPlayer = humanPlayerX.get();
        }

        displayBoard_numbering();

        bool gameOver = false;

        do
        {
            board.displayBoard();
            currentPlayer->makeMove(board);

            if (board.checkForWins(currentPlayer->getPlayerChar()))
            {
                board.displayBoard();
                cout << "\n\t** " << currentPlayer->getPlayerChar() << " WINS! **\n";
                gameOver = true;
            }
            else if (board.checkForDraw())
            {
                board.displayBoard();
                cout << "\n\t** It's a DRAW! **\n";
                gameOver = true;
            }

            if (!gameOver)
            {
                currentPlayer = (currentPlayer == humanPlayerX.get()) 
                    ? (aiPlayerO ? aiPlayerO.get() : humanPlayerO.get())
                    : humanPlayerX.get();
            }

        } while (!gameOver);
    }

private:
    GameBoard board;
    unique_ptr<Player> humanPlayerX;
    unique_ptr<Player> humanPlayerO;
    unique_ptr<Player> aiPlayerO;
    Player *currentPlayer = nullptr;
};

int main()
{
    srand(static_cast<unsigned int>(time(nullptr)));
    TicTacToe game;
    game.playGame();
    return 0;
}
