#include<bits/stdc++.h>
using namespace std;

#define COMPUTER 1
#define HUMAN 2

#define SIDE 3

#define COMPUTERMOVE '0'
#define HUMANMOVE 'x'

void initialise(char board[][SIDE])
{
    //Initially fill the board with *
    for(int i=0;i<SIDE;i++)
    {
        for(int j=0;j<SIDE;j++)
            board[i][j]='*';
    }
}

void showInstruction()
{
    cout<<"Choose a cell number from 1 to 9"<<endl<<endl;
    cout<<"\t\t\t 1 | 2 | 3"<<endl;
    cout<<"\t\t\t 4 | 5 | 6"<<endl;
    cout<<"\t\t\t 7 | 8 | 9"<<endl<<endl;
}
bool rowCrossed(char board[][SIDE])
{
    for(int i=0;i<SIDE;i++)
    {
        if(board[i][0]==board[i][1] && board[i][1]==board[i][2] && board[i][0]!='*')
            return true;
    }
    return false;
}
bool colCrossed(char board[][SIDE])
{
    for(int i=0;i<SIDE;i++)
    {
        if(board[0][i]==board[1][i] && board[1][i]==board[2][i] && board[0][i]!='*')
            return true;
    }
    return false;
}
bool diagonalCrossed(char board[][SIDE])
{
    if(board[0][0]==board[1][1] && board[1][1]==board[2][2] && board[0][0]!='*')
        return true;
    if(board[0][2]==board[1][1] && board[1][1]==board[2][0] && board[0][2]!='*')
        return true;
    return false;
}
bool gameOver(char board[][SIDE])
{
    return (rowCrossed(board) || colCrossed(board) || diagonalCrossed(board));
}
int minimax(char board[][SIDE], int depth, bool isAI)
{
	int score=0;
	int bestScore=0;
	if (gameOver(board)==true)
	{
		if(isAI==true)
			return -10;
		if(isAI==false)
			return 10;
	}
	else
	{
		if(depth<9)
		{
			if(isAI==true)
			{
				bestScore=INT_MIN;
				for(int i=0;i<SIDE;i++)
				{
					for(int j=0;j<SIDE;j++)
					{
						if(board[i][j]=='*')
						{
							board[i][j]=COMPUTERMOVE;
							score=minimax(board,depth+1,false);
							board[i][j]='*';
							if(score>bestScore)
								bestScore=score;
						}
					}
				}
				return bestScore;
			}
			else
			{
				bestScore=INT_MAX;
				for (int i=0;i<SIDE;i++)
				{
					for(int j=0;j<SIDE;j++)
					{
						if(board[i][j]=='*')
						{
							board[i][j]=HUMANMOVE;
							score=minimax(board,depth+1,true);
							board[i][j]='*';
							if (score<bestScore)
								bestScore=score;
						}
					}
				}
				return bestScore;
			}
		}
		else
          return 0;
	}
}
int bestMove(char board[][SIDE],int moveIndex)
{
    int x=-1,y=-1,score=0,bestScore=INT_MIN;
    for(int i=0;i<SIDE;i++)
    {
        for(int j=0;j<SIDE;j++)
        {
            if(board[i][j]=='*')
            {
                board[i][j]=COMPUTERMOVE;
                score=minimax(board,moveIndex+1,false);
                board[i][j]='*';
                if(score>bestScore)
                {
                    bestScore=score;
                    x=i;
                    y=j;
                }
            }
        }
    }
    return x*3+y;
}
void declareWinner(int whoseTurn)
{
	if(whoseTurn==COMPUTER)
		cout<<"COMPUTER has won"<<endl;
	else
		cout<<"HUMAN has won"<<endl;
}
void showBoard(char board[][SIDE])
{
	cout<<"\t\t\t "<<board[0][0]<<" | "<<board[0][1]<<" | "<<board[0][2]<<endl;
	cout<<"\t\t\t "<<board[1][0]<<" | "<<board[1][1]<<" | "<<board[1][2]<<endl;
	cout<<"\t\t\t "<<board[2][0]<<" | "<<board[2][1]<<" | "<<board[2][2]<<endl;
}

void playTicTacToe(int whoseTurn)
{
    char board[SIDE][SIDE];
    int moveIndex=0,x=0,y=0;

    initialise(board);
    showInstruction();

    while(gameOver(board)==false && moveIndex!=SIDE*SIDE)
    {
        int n;
        if(whoseTurn==COMPUTER)
        {
           n=bestMove(board,moveIndex);
           x=n/SIDE;
           y=n%SIDE;
           board[x][y]=COMPUTERMOVE;
           cout<<endl<<"COMPUTER has put a "<<COMPUTERMOVE<<" at cell "<<n+1<<endl;
           showBoard(board);
           moveIndex++;
           whoseTurn=HUMAN;
        }

        else if(whoseTurn==HUMAN)
        {
            cout<<"You can insert following Positions : ";
            for(int i=0;i<SIDE;i++)
            {
                for(int j=0;j<SIDE;j++)
                {
                    if(board[i][j]=='*')
                        cout<<(i*3+j+1)<<" ";
                }
            }
            cout<<endl<<endl<<"Enter Position : ";
            cin>>n;
            n--;
            x=n/SIDE;
            y=n%SIDE;
            if(board[x][y]=='*' && n<9 && n>=0)
            {
                board[x][y]=HUMANMOVE;
                cout<<endl<<"HUMAN has put a "<<HUMANMOVE<<" in cell "<<n+1<<endl;
                showBoard(board);
                moveIndex++;
                whoseTurn=COMPUTER;
            }
            else if(board[x][y]!='*' && n<9 && n>=0)
                cout<<endl<<"Position is occupied, select any one place from available places ";
            else if(n<0 || n>8)
                cout<<endl<<"Invalid Position";
        }
    }
    if (gameOver(board)==false && moveIndex==SIDE*SIDE)
		cout<<"It's a draw"<<endl;
	else
	{
		if(whoseTurn==COMPUTER)
			whoseTurn=HUMAN;
		else if(whoseTurn==HUMAN)
			whoseTurn=COMPUTER;

		declareWinner(whoseTurn);
	}
}
int main()
{
    cout<<"------------------------------------------------------"<<endl<<endl;
    cout<<"\t\t\t Tic Tac Toe"<<endl<<endl;
    cout<<"------------------------------------------------------"<<endl<<endl;
    char cont='y';
    do{
        char choice;
        cout<<"Do you want to start first?(y/n) : ";
        cin>>choice;
        if(choice=='n')
            playTicTacToe(COMPUTER);
        else if(choice=='y')
            playTicTacToe(HUMAN);
        else
            cout<<"Invalid Choice"<<endl;

        cout<<"Do you want to quit?(y/n) : ";
        cin>>cont;
    }while(cont=='n');
    return 0;
}
