/**********|**********|**********|
Program: TC01.1191302553.Loo.Wei.Xiong.cpp
Course: Programming Fundamantals
Year: 2019/2020 Trimester 2
Name: Theerapob Loo @ Loo Wei Xiong
ID: 1191302553
Lecture Section: TC01
Tutorial Section: TT01
Email: weixiong8489@gmail.com
Phone: 017-2047243
**********|**********|**********/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
using namespace std;

int playerRound = 0;
char board[10][10]= {
						{' ','b',' ','b',' ','b',' ','b',' ','b'},
						{'b',' ','b',' ','b',' ','b',' ','b',' '},
						{' ','b',' ','b',' ','b',' ','b',' ','b'},
						{'b',' ','b',' ','b',' ','b',' ','b',' '},
						{' ','#',' ','#',' ','#',' ','#',' ','#'},
						{'#',' ','#',' ','#',' ','#',' ','#',' '},
						{' ','a',' ','a',' ','a',' ','a',' ','a'},
						{'a',' ','a',' ','a',' ','a',' ','a',' '},
						{' ','a',' ','a',' ','a',' ','a',' ','a'},
						{'a',' ','a',' ','a',' ','a',' ','a',' '},
                    };

void clear();
void pause();
void save();
void load();
void printBoard();
void helpMenu();
void playerMovement();
bool playerError(char,int,char,int);
void coordinate();
void swapPiece(int&,int&,int&,int&);


int main()
{
  int startingMenu;
  cout << "Do you wish to load previous game?\nEnter 1 if yes\nEnter 2 if no"<<endl;
  cin >> startingMenu;
  if (startingMenu == 1)
	  load();
  clear();                              
  cout << "\nWelcome to my International draught game, in this draught game, \n\n"
       << "'a' stands for light,\n'b'stands for black,\n"
       << "\n\nPlayer input shall be in a format such as:\n\n \"a1 b3\" (without quotes and 1 space between a1 and a3)"
       << "\n with \'a1\' as origin and \'b3\' as destination.\n\n";
  pause();
  clear();
  printBoard();
  playerMovement();

  return 0;
}

void clear()//(system cls)
{
	system("cls");
}
void pause()//(system pause)
{
	char temp;
	cout << "Press any key to continue..."<<endl;
	cin >> temp;	
}

void printBoard() //print a board
{
  int rowCount = 1;
      for (int row = 0; row < 10; ++row)//prints the board
      {
        cout << "   |---+---+---+---+---+---+---+---+---+---| " << endl;
        cout << setw(3) << rowCount++ << "|";
            for (int col = 0; col < 10; ++col)
                 {
                    if (row < 10)
                    cout << " " << board[row][col] << " |";
                    else
                    cout << board[row][col] << " ";
                 }
            cout << endl;
      }
      cout << "   |---+---+---+---+---+---+---+---+---+---| " << endl;
      cout << "     a   b   c   d   e   f   g   h   i   j   " << endl;
      cout << "\ninput \"h999 h999\"(without quotes) for help menu" << endl;
      cout << endl;
}

void playerMovement() //determine player movement
{
  while(true)
  {
	int row1,row2;
	char col1,col2;
    if (playerRound % 2 == 0)
      cout << "Player 1(a)'s turn.." << endl;
    else
      cout << "Player 2(b)'s turn.."<< endl;
  
    cout << "Please enter your move:\n";
    cin >> col1 >> row1 >> col2 >> row2;
    int newrow1 = row1-1;
    int newcol1 = col1-97;
    int newrow2 = row2-1;
    int newcol2 = col2-97;
    if (col1 == 'h' && row1 == 999 && col2 == 'h' && row2 == 999)
      helpMenu();
	else if (col1 == 's' && row1 == 1 && col2== 's' && row2 == 1) //save game
	{
		clear();
		save();
		cout << "Game saved" << endl;
		pause();
		printBoard();
		continue;
	}
	else if(col1 == 'd' && row1 == 2 && col2 == 'd' && row2 == 2)//load game
	{
		load();
		printBoard();
		continue;
	}
	else if(col1 == 'g' && row1 == 3 && col2 == 'g' && row2 == 3)//surrender
	{
		if (playerRound % 2 == 0)
			cout << "Player 2(b)'s has won the game!" << endl;
		else
			cout << "Player 1(a)'s has won the game!"<< endl;
		exit(0);
	}
	else if(col1 == 'b' && row1 == 4 && col2 == 'b' && row2 == 4)//quit game
	{
		exit(0);
	}
	else if (playerError(col1,row1,col2,row2)) //detect player error
		continue;
	else
	{
		playerRound++;
		swapPiece(newrow1,newcol1,newrow2,newcol2);
		clear();
		printBoard();
	}
		
  }
}

bool playerError(char col1,int row1,char col2,int row2)
{
	int newrow1 = row1-1;
    int newcol1 = col1-97;
    int newrow2 = row2-1;
    int newcol2 = col2-97;
	
	// if player inpuut non interger value for row
	if (cin.fail())
	{
		cout << "Invalid input!!. Try again."<<endl;
		cin.clear();
		return true;
	}
	
	//catches input that were not in the scope
	else if(row1 > 10 || row1 < 1 || row2 > 10 || row2 < 1) 
	{
        cout << "Invalid input!!. Try again."<<endl;
		return true;
	}
	
	else if(newcol1 > 9 || newcol1 < 0 || newcol2 > 9 || newcol2 < 0) 
	{
        cout << "Invalid input!!. Try again."<<endl;
		return true;
	}

   //move left/right || move up/down || move more then 1 moves
	else if (row1 == row2 || col1 == col2 || row2 - row1 < -1 || row2-row1 > 1)
	{
        cout << "Invalid input!!. Try again."<<endl;
        return true;
	}
	  
	if(playerRound % 2 == 0) //a's turn
			// 					origin != a    ||        destination == a        || move downward
		    if (board[newrow1][newcol1] != 'a' || board[newrow2][newcol2] == 'a' || row2-row1 != -1)
			{
				cout << "Invalid input!!. Try again."<<endl;
				return true;;

			}
			
	if (playerRound % 2 == 1)//b's turn
			//                  origin != b    ||        destination == b        || move upward
		    if (board[newrow1][newcol1] != 'b' || board[newrow2][newcol2] == 'b' || row2-row1 != 1)
			{
				cout << "Invalid input!!. Try again."<<endl;
				return true;;
			}
			
	return false;
}

void swapPiece(int& row1,int& col1,int& row2,int& col2) //take input from playerMovement() and do the swap logic
{
  char temp = board[row1][col1];
  board[row1][col1] = board[row2][col2];
  board[row2][col2] = temp;

}

void helpMenu()//help menu that teaches user to save etc
{
	clear();
	cout << "\n'a' stands for white,\nand\n'b'stands for black,\n"
		<< "\n\nPlayer input shall be in a format such as:\n\n \"a1 b3\" (without quotes and 1 space between a1 and a3)"
		<< "\nand with \'a1\' as origin and \'b3\' as destination.\n\n"
		<< "If you want to save game, enter s1s1\n"
		<< "If you want to load game, enter d2d2\n"
		<< "If you want to surrender, enter g3g3\n"
		<< "If you want to exit program, enter b4b4\n";
	pause();
    printBoard();
}

void save()
{
	ofstream fout;
	char temp;
	fout.open("save.txt");
	// if (playerRound % 2 == 0)
      // fout << "Next player: a" << endl;
    // else
      // fout << "Next player: b"<< endl;
	fout << playerRound;
	for(int i = 0;i < 10; i++)
	{
		for(int j = 0;j < 10;j++)
		{
			if (board[i][j] == ' ')
				fout << '-';
			else
				fout << board[i][j];
		}
		fout << endl;
	}
	fout.close();
}

void load()
{
	ifstream fin;
	fin.open("save.txt");
	clear();
	fin >> playerRound;
	for(int i = 0;i < 10; i++)
	{
		for(int j = 0;j < 10;j++)
		{
				fin >> board[i][j];
				if (board[i][j] == '-')
					board[i][j] = ' ';
		}
	}
	fin.close();
}
















