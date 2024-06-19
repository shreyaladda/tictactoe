#include<bits/stdc++.h>
using namespace std;

int side=3;
char humanmove='x';
char computermove='o';
int computer=1, human=0;


bool rowcrossed(vector<vector<char>> &board){
    for(int i=0;i<side;i++)
    {
        if(board[i][0]==board[i][1] && board[i][1]==board[i][2] && board[i][0]!='*')
        return true;
    }
    return false;
}
bool colcrossed(vector<vector<char>> &board){
    for(int i=0;i<side;i++)
    {
        if(board[0][i]==board[1][i] && board[1][i]==board[2][i] && board[0][i]!='*')
        return true;
    }
    return false;
}
bool diagcrossed(vector<vector<char>> &board){
    if(board[0][0]==board[1][1] && board[1][1]==board[2][2] && board[0][0] !='*')
    return true;
    if(board[0][2]==board[1][1] && board[1][1]==board[2][0] && board[0][2] !='*')
    return true;

    return false;
}

bool gameover(vector<vector<char>> &board)
{
    return (rowcrossed(board) || colcrossed(board) || diagcrossed(board));
}

int minimax(vector<vector<char>> &board, int depth ,bool iscomp){
    int curr=0, best=0;

    if(gameover(board)==true)
    {
        if(iscomp)
        return -10;
        else
        return +10;
    }
    else{
        if(depth<9)
        {
            if(iscomp)
            {
                best=INT_MIN;
                for(int i=0;i<side;i++)
                {
                    for(int j=0;j<side;j++)
                    {
                        if(board[i][j]=='*')
                        {
                            board[i][j]=computermove;
                            curr=minimax(board, depth+1, false);
                            board[i][j]='*';
                            if(curr>best)
                            best=curr;
                        }
                    }
                }
                return best;
            }
            else{
                best=INT_MAX;
                for(int i=0;i<side;i++)
                for(int j=0;j<side;j++)
                {
                    if(board[i][j]=='*'){
                        board[i][j]=humanmove;
                        curr=minimax(board, depth+1, true);
                        board[i][j]='*';
                        if(curr<best)
                        {
                            best=curr;
                        }
                    }
                }
                return best;
            }
        }
        else
        return 0;
    }
}
int bestopt(vector<vector<char>> &board, int moveIndex)
{
    int x=-1,y=-1;
    int curr=0, best=INT_MIN;
    for(int i=0;i<side;i++)
    {
        for(int j=0;j<side;j++)
        {
            if(board[i][j]=='*'){
                board[i][j]=computermove;
                curr=minimax(board,moveIndex+1,false);
                board[i][j]='*';
                if(curr>best)
                {
                    best=curr;
                    x=i;y=j;
                }
            }
        }
    }
    //return x*3 +y
    return x*3 + y;
}
void initialise(vector<vector<char>> &board){
    for(int i=0;i<side;i++)
    for(int j=0;j<side;j++)
    board[i][j]='*';
}

void showboard(vector<vector<char>> &board)
{
    for(int i=0;i<side;i++)
    {
        for(int j=0;j<side;j++)
        {
            if(j==side-1)
            cout<< board[i][j]<<endl;
            else
            cout<< board[i][j]<<" | ";
        }
    }
}
void showInstructions(){
    cout<<"The cells are numbered from 1-9 as shown below, choose a number to play your turn"<<endl;
    cout<<"\t\t\t 1 | 2 | 3"<<endl;
    cout<<"\t\t\t 4 | 5 | 6"<<endl;
    cout<<"\t\t\t 7 | 8 | 9"<<endl;
}

void declarewin(int whoseturn)
{
    if(whoseturn==computer)
    cout<<"COMPUTER has won!!"<<endl;
    else
    cout<<"YOU have won!!"<<endl;
}
void play(int whoseturn)
{
    vector<vector<char>> board(side, vector<char> (side));
    int moveIndex=0,x=0,y=0;

    initialise(board);
    showInstructions();

    while(gameover(board)==false && moveIndex < side*side)
    {
        int n;
        if(whoseturn==computer)
        {
            n=bestopt(board, moveIndex);
            x=n/side;
            y=n%side;
            board[x][y]=computermove;
            cout<<"COMPUTER has played his turn"<<endl;
            showboard(board);
            moveIndex++;
            whoseturn=human;
        }
        else if(whoseturn==human)
        {
            cout<<"Your turn!\nYou can play in the following positions"<<endl;
            for(int i=0;i<side;i++)
            {
                for(int j=0;j<side;j++)
                {
                    if(board[i][j]=='*')
                    {
                        cout<< i*3+ j +1 <<" ";
                    }
                }
            }
            cout<<endl;
            cout<<"Enter the position"<<endl;
            cin>> n;
            n--;
            x=n/side;
            y=n%side;
            if(board[x][y]=='*' && n<9 && n>=0)
            {
                board[x][y]=humanmove;
                cout<<"YOU have played your turn"<<endl;
                showboard(board);
                moveIndex++;
                whoseturn=computer;
            }
            else if(board[x][y]!='*' && n<9 && n>=0){
                cout<<"Positon is laready occupied, select valid position"<<endl;
            }
            else if(n<0 || n>8)
            {
                cout<<"Invalid position"<<endl;
            }
        }
    }
    
    if (gameover(board)) {
        declarewin(whoseturn == computer ? human : computer);
    } else {
        cout << "It's a draw!" << endl;
    }
    
}
int main(){
    cout<<"\t\t\tTic-Tac-Toe\n";
    cout<<endl;

    string choice;
    cout<<"Do you want to start first?"<<endl;
    cin >> choice;
    if(choice=="yes")
    play(human);
    else if(choice=="no")
    play(computer);
    else
    cout<<"Invalid input!\nRestart to play!"<<endl;
}