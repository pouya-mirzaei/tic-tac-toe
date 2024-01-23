#include <iostream>
#include <fstream>
using namespace std;

#define X 1
#define O -1
#define EMPTY 0

#define CENTRAL_HOME 10
#define CORNER_HOME 9
#define MIDDLE_HOME 8
#define NEAR_HOME 14
#define BIG_BOARD_VALUE 3

#define BOARD_SIZE 3

void makeMove(int board[][3], int player, int row, int col);
void removeMove(int board[][3], int row, int col);
int checkWinner(int board[][3]);
void displayBoard(int board[][3]);
bool isMoveValid(int board[][3], int row, int col);
bool isBoardFull(int board[][3]);
int minimax(int board[][3], int depth, bool maximizingPlayer);
void export_board(int board[][3], int turn, int i, int j);
void clearTextFile(string fileName);
int board_score_plus(int board[BOARD_SIZE][BOARD_SIZE]);
int board_score(int board[BOARD_SIZE][BOARD_SIZE]);

int board[3][3] = {{1, 0, 0}, {-1, -1, 0}, {1, 0, 1}};
int arr[2];

int main()
{

    int currentPlayer = -1;

    while (true)
    {
        displayBoard(board);

        if (currentPlayer == X)
        {
            int row, col;
            cin >> row >> col;
            makeMove(board, currentPlayer, row, col);
        }
        else
        {
            clearTextFile("board.txt");
            if (board[1][1] == EMPTY)
            {
                makeMove(board, O, 1, 1);
            }
            else
            {
                cout << endl
                     << minimax(board, 4, false);
                int a;
                cin >> a;
                makeMove(board, currentPlayer, arr[0], arr[1]);
            }
        }

        if (checkWinner(board) != 0)
        {
            displayBoard(board);
            if (checkWinner(board) == X)
                cout << "X wins!";
            else
                cout << "O wins!";

            break;
        }

        if (isBoardFull(board))
        {
            displayBoard(board);
            cout << endl
                 << "It's a Tie!";
            break;
        }

        currentPlayer = (currentPlayer == X) ? -1 : 1;
    }

    return 0;
}

void displayBoard(int board[][3])
{
    system("cls");

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            switch (board[i][j])
            {
            case X:
                cout << 'X';
                break;
            case O:
                cout << 'O';
                break;
            case EMPTY:
                cout << '-';
                break;
            }
            cout << "\t";
        }
        cout << endl;
    }
}

void makeMove(int board[][3], int player, int row, int col)
{
    if (board[row][col] == EMPTY)
    {
        board[row][col] = player;
    }
    else
    {
        cout << "eroorrrrrrrr";
    }
}
void removeMove(int board[][3], int row, int col)
{
    board[row][col] = EMPTY;
}

bool isMoveValid(int board[][3], int row, int col)
{
    if (board[row][col] == EMPTY)
        return 1;

    return 0;
}

int checkWinner(int board[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != 0)
        {
            return board[i][0];
        }
        else if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != 0)
        {
            return board[0][i];
        }
    }

    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != 0)
    {
        return board[0][0];
    }
    else if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ')
    {
        return board[0][2];
    }

    return EMPTY;
}

bool isBoardFull(int board[][3])
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == EMPTY)
                return false;

    return true;
}

int minimax(int board[][3], int depth, bool maximizingPlayer)
{
    if (depth == 0 || checkWinner(board) != 0 || isBoardFull(board))
    {
        return board_score(board) + board_score_plus(board);
    }

    int maxScore = -999999;
    int minScore = 999999;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            int player = maximizingPlayer ? 1 : -1;
            if (board[i][j] == EMPTY)
            {
                makeMove(board, player, i, j);
                export_board(board, player, i, j);

                if (maximizingPlayer)
                {
                    int score = minimax(board, depth - 1, false);
                    if (score > maxScore)
                    {
                        maxScore = score;
                        arr[0] = i;
                        arr[1] = j;
                    }
                    removeMove(board, i, j);
                }
                else
                {
                    int score = minimax(board, depth - 1, true);
                    if (score < minScore)
                    {
                        minScore = score;
                        arr[0] = i;
                        arr[1] = j;
                    }
                    removeMove(board, i, j);
                }
            }
        }
    }

    if (maximizingPlayer)
    {
        return maxScore;
    }
    else
    {
        return minScore;
    }
}

void export_board(int board[][3], int turn, int i, int j)
{
    fstream file;
    file.open("board.txt", ios::app);
    if (file.is_open())
    {
        if (turn == X)
        {
            file << "X";
        }
        else
        {
            file << "O";
        }
        file << "'s choose : \n";
        for (int i = 0; i < 3; i += 1)
        {
            for (int j = 0; j < 3; j++)
            {
                if (board[i][j] == X)
                {
                    file << "X ";
                }
                else if (board[i][j] == O)
                {
                    file << "O ";
                }
                else
                {
                    file << "- ";
                }
            }
            file << endl;
        }

        file << "board score : " << board_score(board) << endl;
        file << "board score plus: " << board_score_plus(board) << endl;
        file << "final score : " << board_score_plus(board) + board_score(board) << endl;
        file << "final score : " << i << " " << j;
        file << endl;

        file
            << "--------------------------------------------------------------"
            << endl
            << endl;
        file.close();
    }
}
void clearTextFile(string fileName)
{
    fstream file;
    file.open(fileName, ios::out);
    file.close();
}

// -------------------------------------------------------------------

int board_score(int board[BOARD_SIZE][BOARD_SIZE])
{
    int sum = 0;
    int k;

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            k = 3 * i + j;
            if (k == 4)
            {
                sum += board[i][j] * CENTRAL_HOME;
            }
            else if (k == 0 || k == 2 || k == 6 || k == 8)
            {
                sum += board[i][j] * CORNER_HOME;
            }
            else if (k == 1 || k == 3 || k == 5 || k == 7)
            {
                sum += board[i][j] * MIDDLE_HOME;
            }
        }
    }

    sum += checkWinner(board) * 100;

    return sum;
}

int board_score_plus(int board[BOARD_SIZE][BOARD_SIZE])
{
    int sum = 0, row = 0, col = 0;

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        row = board[i][0] + board[i][1] + board[i][2];
        col = board[0][i] + board[1][i] + board[2][i];

        if (row == 2)
        {
            sum += NEAR_HOME;
        }
        else if (row == -2)
        {
            sum -= NEAR_HOME;
        }
        if (col == 2)
        {
            sum += NEAR_HOME;
        }
        else if (col == -2)
        {
            sum -= NEAR_HOME;
        }
    }

    row = board[0][0] + board[1][1] + board[2][2];
    col = board[2][0] + board[1][1] + board[0][2];
    if (row == 2)
    {
        sum += NEAR_HOME;
    }
    else if (row == -2)
    {
        sum -= NEAR_HOME;
    }
    if (col == 2)
    {
        sum += NEAR_HOME;
    }
    else if (col == -2) // +2 or -2 for each player (first or second ) can be different .
    {
        sum -= NEAR_HOME;
    }
    return sum;
}
