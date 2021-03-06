
#include "Game.h"

using namespace std;

// Contructor 
Game :: Game() 
{
    for(auto &row : board)
        for(auto &val : row)
            val = 0;
    this->cpu = 'c';
}

// Function for getting input
void Game :: initialize()
{
    cout << "Choose your character HUMAN: ";
    cin >> this->player;

    char colors[6] = {'r', 'g', 'y', 'b', 'm', 'c'};
    int color;

    cout << "Available Colors are" << endl;
    cout << getColor('r') << "1. Red" << endl;
    cout << getColor('g') << "2. Green" << endl;
    cout << getColor('y') << "3. Yellow" << endl;
    cout << getColor('b') << "4. Blue" << endl;
    cout << getColor('m') << "5. Megenta" << endl;
    cout << getColor('c') << "6. Cyan" << getColor('n') << endl;
     cout << "Choose your Color: ";
    cin >> color;
    this->playerColor = colors[color-1];

}

// Function for returns color
string Game :: getColor(char color)
{
    switch (color)
    {
        case 'r': return "\u001b[31m";
        case 'g': return "\u001b[32;1m";
        case 'y': return "\u001b[33;1m";
        case 'b': return "\u001b[34;1m";
        case 'm': return "\u001b[35;1m";
        case 'c': return "\u001b[36;1m";
        default: return "\u001b[0m";
    }
}

// Prints the board
void Game :: printBoard()
{
    cout << "| ";
    for (int i = 0; i < ROW; i++)
        cout << i << " | ";

    cout << endl << " ";
    for (int i = 0; i < ROW; i++)
        cout << " |  ";
    cout << endl;

    cout << " ";
    for (int i = 0; i < ROW; i++)
        cout << " v  ";
    cout << endl;


    for(auto &rows : board)
    {
        cout << "| ";
        for(auto &val : rows)
        {
            if(val == 1)
                cout << getColor(playerColor) << player << getColor('n') << " | ";
            else if(val == -1)
                cout << getColor('g') << cpu << getColor('n') << " | ";
            else
                cout << getColor('c') << "." << getColor('n') << " | ";
        }
        cout << endl << "-----------------" << endl;
    }


}

// Registers the move made by the players
void Game :: makeMove(int col, bool player)
{
    for (int i = ROW-1; i >= 0; i--)
    {
        if(board[i][col] == 0)
        {
            if(player)
                board[i][col] = 1;
            else
                board[i][col] = -1;
            break;
        } 
    }

}

// Removes the move made by the players
void Game :: removeMove(int col)
{
    for (int i = 0; i < ROW; i++)
    {
        if(board[i][col] != 0)
        {
           board[i][col] = 0;
           break;
        } 
    }

}

// Check of anyone won and if won returns the winning player char
int Game :: didWin()
{
    bool flag = true;
    int won = 0;

    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < ROW; j++)
        {

            if (board[i][j] != 0)
            {
                flag = true;
                int val = board[i][j];

                // loop for 12:00
                for (int k = 1; k < 4; k++)
                {
                    if(i - 3 >= 0)
                    {
                        if(board[i-k][j] != val)
                        {
                            flag = false;
                            break;
                        }
                    }
                    else
                    {
                        flag = false;
                    }
                    
                    
                }

                if(flag)
                {
                    won = board[i][j];
                    break;
                }
                
                flag = true;
                
                // loop for 3:00 
                for (int k = 1; k < 4; k++)
                {
                    if(j + 3 <= ROW - 1 )
                    {
                        if(board[i][j+k] != val)
                        {
                            flag = false;
                            break;
                        }
                    }
                    else
                    {
                        flag = false;
                    }
                    
                }
                
                if(flag)
                {
                    won = board[i][j];
                    break;
                }

                flag = true;

                // loop for 1:30
                for (int k = 1; k < 4; k++)
                {
                    if(j + 3 <= ROW - 1  && i - 3 >= 0)
                    {
                        if(board[i-k][j+k] != val)
                        {
                            flag = false;
                            break;
                        }
                    }
                    else
                    {
                        flag = false;
                    }
                    
                }

                if(flag)
                {
                    won = board[i][j];
                    break;
                }

                flag = true;

                // loop for 5:30
                for (int k = 1; k < 4; k++)
                {
                    if(j + 3 <= ROW - 1  && i + 3 >= ROW - 1 )
                    {
                        if(board[i+k][j+k] != val)
                        {
                            flag = false;
                            break;
                        }
                    }
                    else
                    {
                        flag = false;
                    }
                    
                }

                if(flag)
                {
                    won = board[i][j];
                    break;
                }

                flag = true;

                
            }

            if(won != 0)
                return won;
            
        }
        
    }

    return won;
    
}

// Returns if the present board is a tied 
bool Game :: isTie()
{
    for(auto &rows : board)
        for(auto &val : rows)
            if(val == 0)
                return false;

    // the board is filled, nobody won => tie
    if(didWin() == 0)
        return true;
    else //the board is filled, somebody won
        return false;
}

int Game  :: minimax(int depth, bool player)
{
    int won = didWin();
    
    if(isTie())
    {
        return 0;
    }
    if(won != 0)
        return won;
    
    // Maximizing player
    if(player)
    {
        int presentScore = 0, bestScore = -9999999;
        for (int i = 0; i < ROW; i++)
        {
            // Checking if the position is free
            if(board[0][i] == 0)
            {
                makeMove(i, true);
                presentScore = minimax(depth+1, false);
                removeMove(i);
                bestScore = max(presentScore, bestScore);
            }
        }

        return bestScore;
    }

    // Minimizing player
    else
    {
        int presentScore = 0, bestScore = 9999999;
        for (int i = 0; i < ROW; i++)
        {
            // Checking if the position is free
            if(board[0][i] == 0)
            {
                makeMove(i, false);
                presentScore = minimax(depth+1, true);
                removeMove(i);
                bestScore = min(presentScore, bestScore);
            }
        }
        return bestScore;
    }
    
}

int Game :: getCompMove()
{
    int bestScore = 99999;
    int bestMove = 0;
    int presentScore;
    cout << "The Computer is thinking...." << endl;
    for (int i = 0; i < ROW; i++)
    {
        // Checking if the position is free
        if(board[0][i] == 0)
        {
            makeMove(i, false);
            presentScore = minimax(0, true);
            removeMove(i);

            if(presentScore <= bestScore)
            {
                bestMove = i;
                bestScore = presentScore;
            }
            //cout << "PresentScore for i: " << i << " is " << presentScore << endl;
        }
        
    }
    cout << "Thinking done. " << endl << "Best Move to be played now is: " << bestMove << endl;
    return bestMove;
}



// Skeleton of the Game
void Game :: start()
{
    int playerMove, compMove, won = 0;
    
    while (won == 0 & !isTie())
    {
        cout << "Please enter the move you are about to play: ";
        cin >> playerMove;
        makeMove(playerMove, true);
        printBoard();
        compMove = getCompMove();
        makeMove(compMove,false);
        printBoard();
        won = didWin();
    }
    
    if(won == 1)
        cout << "HUMAN won !!!!" << endl << "Congrats you won with a machine" << endl;
    else if (won == -1)
        cout << "The COMPUTER won." << endl << "Better luck next time !!" << endl;
    else
        cout << "The game is a tie." << endl;

}