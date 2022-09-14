#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

std::vector<int> attackedRows;
std::vector<int> attackedCols;
std::vector<int> leftDiagonals;
std::vector<int> rigthDiagonals;

int counter;
int limitPrint;
bool printBool = false;

void PrintBoard(bool** board , int &size)
{
        for (int row = 0; row < size; row++)
        {
            for (int col = 0; col < size; col++)
            {
                if (board[row][col] == true) std::cout << "X ";
                else std::cout << "- ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
}

bool foundIdx(std::vector<int> &numbers , int row)
{
    if (find(numbers.begin(), numbers.end(), row) != numbers.end()) return false;
    return true;
}


bool CanPlaceQueen(int row, int col , int leftDiag, int rigthDiag )
{
    return (foundIdx(attackedRows , row) && foundIdx(attackedCols , col) && foundIdx(leftDiagonals , leftDiag) && foundIdx(rigthDiagonals , rigthDiag));
}


int GetIndex(std::vector<int> vector, int value)
{
    int idx = 0;
    for (auto u : vector)
    {
        if (u == value) return idx;
        idx++;
    }
}

void removeAttackedRow(int row){ attackedRows.erase(attackedRows.begin()     + GetIndex(attackedRows, row));}

void removeAttackedCol(int col){ attackedCols.erase(attackedCols.begin()     + GetIndex(attackedCols, col));}

void removeLeftDiag(int n)     { leftDiagonals.erase(leftDiagonals.begin()   + GetIndex(leftDiagonals, n));}

void removeRightDiag(int n)    { rigthDiagonals.erase(rigthDiagonals.begin() + GetIndex(rigthDiagonals, n));}

void PlaceQueens(bool** board,int row , int &size)
{
    if (row >= size)
    {
        if (size < limitPrint || printBool) PrintBoard(board ,size);
        counter++;
        return;
    }

    for (int col = 0; col < size; col++)
    {
        int leftDiag = row - col;
        int rigthDiag = row + col;

        if (CanPlaceQueen(row, col , leftDiag , rigthDiag))// if I can place queen
        {
            attackedRows.push_back(row);
            attackedCols.push_back(col);
            leftDiagonals.push_back(leftDiag);
            rigthDiagonals.push_back(rigthDiag);

            board[row][col] = true;

            PlaceQueens(board, row + 1,size);

            removeAttackedRow(row);
            removeAttackedCol(col);
            removeLeftDiag(leftDiag);
            removeRightDiag(rigthDiag);

            board[row][col] = false;
        }
    }
    
}


int main(void)
{
    int size = 0;
    limitPrint = 11;
    std::cout << std::endl;
    std::cout << "Welcome to my Queens puzzle calculator! " << std::endl;
    std::cout << std::endl;
    std::cout << "Enter the size of the board : ";
    std::cin >> size;
    std::cout << std::endl;

    if (size >= limitPrint) {
        std::cout << "There are too many solutions to be printed , are you sure you want them all? " << std::endl;
        std::cout << "If Yes then type Y , else N " << std::endl;
        char answer;
        std::cin >> answer;
        if(answer == 'Y') printBool = true;
        else { std::cout << "Please wait untill I get the possible sollutions_" << std::endl; }
    }
    bool** board = new bool* [size];
    for (int i = 0; i < size; i++) board[i] = new bool[size];

    for (int i = 0; i < size; i++) 
        for (int k = 0; k < size; k++) 
            board[i][k] = false;
    
    PlaceQueens(board, 0 , size);

    delete[]board;
    board = NULL;
    
    std::cout << "Total solutions found : " << counter << std::endl;
    system("pause");
    return 0;
}

