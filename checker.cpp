#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
using namespace std;

int captureflag = 0;
int counter = 0;
int status = 0;
int temprow1, tempcol1;
int playerRound = 0;
int temp1 = 0;
char board[10][10] = {
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
void printBoard();
void playerMovement(char, int, char, int);
bool movementLogic(char, int, char, int);
bool playerCapture(int, int, int, int);
bool multiCapture(int, int);
bool crownCapture(int, int, int, int);
bool crownMultiCapture(int, int, int, int);
void swapPiece(int, int, int, int);
bool determineCapture(int, int, int, int);
void helpMenu();
void calculatePiece();
void playerInput();
void save();
void load();


int main()
{
	char startingMenu;
	while (true)
	{
		cout << "Do you wish to load previous game?\nEnter 1 if yes\nEnter 2 if no" << endl;
		cin >> startingMenu;
		switch (startingMenu)//determine if input if correct
		{
		case '1':  load();

		case '2':  break;

		default:   cout << "Invalid input!" << endl;
			continue;
		}
		break;
	}
	clear();
	cout << "\nWelcome to my International draught game, in this draught game, \n"
		<< "'a' stands for light,\n'b'stands for black.\n";

	cout << "\n***********************************************************\n";
	cout << "*RULES*\n"
		<< "1. Rules are similar to international draught with a twist.\n"
		<< "2. Player are only allowed to capture 1 pieces per move.\n"
		<< "3. Player are given a choice to stop moving after a capturing a piece(if condition are met).\n"
		<< "4. Force capture is disabled for this game because forcing stuff is bad.\n"
		<< "5. If you choose to continue capture, you must be responsible and not change ur mind after u move(force capture applied after first choice).\n"
		<< "6. If the piece is crowned, you can move anywhere u wan if the rule is right(but still wont force u to capture).\n"
		<< "7. The input format shall be \"a1 b3\" (without quotes and 1 space between a1 and a3).\n"
		<< "8. Player may choose to surrender or fight to the end until last piece is taken down."
		<< "9. By the rule of international draught, player 1(a) will start first.\n"
		<< "***********************************************************\n\n";

	cout << "If you want to save game, enter s1s1\n"
		<< "If you want to load game, enter d2d2\n"
		<< "If you want to surrender, enter g3g3\n"
		<< "If you want to exit program, enter b4b4\n\n"
		<< "(above menu is accessible in game using \'h999 h999\' (without quotes))\n";

	pause();
	clear();
	printBoard();
	playerInput();

	return 0;
}

void printBoard() //print a board
{
	int rowCount = 1;
	for (int row = 0; row < 10; ++row)
		for (int col = 0; col < 10; ++col)
			if (row == 0 && board[row][col] == 'a')  //replace the piece(a) as crown
				board[row][col] = 'A';
			else if (row == 9 && board[row][col] == 'b')//replace the piece(b) as crown
				board[row][col] = 'B';

	for (int row = 0; row < 10; ++row)//prints the board
	{
		cout << "   |---+---+---+---+---+---+---+---+---+---| " << endl;
		cout << setw(3) << rowCount++ << "|";
		for (int col = 0; col < 10; ++col)
			if (row < 10)
				cout << " " << board[row][col] << " |";
			else
				cout << board[row][col] << " ";
		cout << endl;
	}
	cout << "   |---+---+---+---+---+---+---+---+---+---| " << endl;
	cout << "     a   b   c   d   e   f   g   h   i   j   " << endl;
	cout << "\ninput \"h999 h999\"(without quotes) for help menu" << endl;
	cout << endl;
	calculatePiece();

	//determine each player's round
	if (playerRound % 2 == 0)
		cout << "Player 1(a)'s turn.." << endl;
	else if (playerRound % 2 == 1)
		cout << "Player 2(b)'s turn.." << endl;
}

void playerInput()
{
	int row1, row2;
	char col1, col2;
	cout << "Please enter your move:\n";
	cin >> col1 >> row1 >> col2 >> row2;
	playerMovement(col1, row1, col2, row2);
}

void playerMovement(char col1, int row1, char col2, int row2) //determine player movement
{
	while (true)
	{
		int newrow1 = row1 - 1;
		int newcol1 = col1 - 97;//refer to ASCII table
		int newrow2 = row2 - 1;
		int newcol2 = col2 - 97;//refer to ASCII table

		if (col1 == 'h' && row1 == 999 && col2 == 'h' && row2 == 999)//call help menu
			helpMenu();
		else if (col1 == 's' && row1 == 1 && col2 == 's' && row2 == 1) //save game
		{
			clear();
			save();
			cout << "Game saved" << endl;
			pause();
			printBoard();
			playerInput();
			continue;
		}
		else if (col1 == 'd' && row1 == 2 && col2 == 'd' && row2 == 2)//load game
		{
			load();
			printBoard();
			playerInput();
			continue;
		}
		else if (col1 == 'g' && row1 == 3 && col2 == 'g' && row2 == 3)//surrender
		{
			if (playerRound % 2 == 0)
				cout << "Player 2(b)'s has won the game!" << endl;
			else
				cout << "Player 1(a)'s has won the game!" << endl;
			exit(0);
		}
		else if (col1 == 'b' && row1 == 4 && col2 == 'b' && row2 == 4)//quit game
		{
			exit(0);
		}
		else if (movementLogic(col1, row1, col2, row2)) //detect player error and movement logic
		{
			clear();
			cout << "Invalid input! Try again." << endl;
			pause();
			printBoard();
			playerInput();
			continue;
		}
		else
		{
			playerRound++;
			//check if piece swaps already happened
			if (counter == 0 && status == 0 && !playerCapture(newcol1, newrow1, newcol2, newrow2) && !(board[newrow2][newcol2] == 'A' || board[newrow2][newcol2] == 'B'))
				swapPiece(newrow1, newcol1, newrow2, newcol2);
			clear();
			printBoard();
			playerInput();
		}
	}
}


void clear()
{
	system("cls");
}

void pause()
{
	char temp;
	cout << "Press any key to continue..." << endl;
	cin >> temp;
}

//capture logic is handled here
bool movementLogic(char col1, int row1, char col2, int row2)//detect player error and movement logic
{
	int newrow1 = row1 - 1;
	int newcol1 = col1 - 97;
	int newrow2 = row2 - 1;
	int newcol2 = col2 - 97;

	// if player input non interger value for row
	if (cin.fail())
	{
		cin.clear();
		cin.ignore(99999999, '\n');
		return true;
	}

	if (abs(newrow2 - newrow1) != abs(newcol2 - newcol1))
		return true;

	//catches input that were not in the scope              || destination != '#'
	else if (row1 > 10 || row1 < 1 || row2 > 10 || row2 < 1 || board[newrow2][newcol2] != '#')
		return true;

	//catches input that were not in the scope 
	else if (newcol1 > 9 || newcol1 < 0 || newcol2 > 9 || newcol2 < 0)
		return true;

	//counter != 0 means we are in process of multi-capturing
	if (counter != 0 && (newrow1 != temprow1 || newcol1 != tempcol1))//determine if player trying to move other piece when multi capture
	{
		clear();
		cout << "you cannot move the other pieces!! Please try again" << endl;
		pause();
		playerRound++;
		printBoard();
		playerInput();
		counter = 1;
		goto jump;
	}

	//determine if player didnt capture after multi capture mode is turned on
	if (counter != 0 && determineCapture(newcol1, newrow1, newcol2, newrow2) && !playerCapture(newcol1, newrow1, newcol2, newrow2))
	{
		clear();
		cout << "you must capture the pieces!! Please try again" << endl;
		pause();
		playerRound++;
		printBoard();
		playerInput();
		counter = 1;
		goto jump;
	}

	// check the movement logic of crown
	if (crownCapture(newcol1, newrow1, newcol2, newrow2))
	{
		counter = 0;
	jump:
		if (crownMultiCapture(newcol1, newrow1, newcol2, newrow2))
		{
			char temp;
			printBoard();
			while (true)
			{
				cout << "You can still capture, do u want to capture?\n"
					<< "Enter '1' if yes and '2' for no" << endl;
				cin >> temp;

				if (temp == '1')
				{
					playerRound--;
					counter = 1;
					temprow1 = newrow2;
					tempcol1 = newcol2;
					break;
				}
				else if (temp == '2')
				{
					status = 1;
					counter = 0;
					break;
				}
				else
				{
					clear();
					cout << "Invalid input! Please try again1" << endl;
					pause();
					printBoard();
					playerInput();
				}
			}
		}




		return false;
	}

	// if player does multiple capture, make sure it is the same pieces that capture
	if (counter != 0 && (newrow1 != temprow1 || newcol1 != tempcol1)) // here is the problem
	{
		clear();
		cout << "you cannot move the other pieces!! Please try again" << endl;
		pause();
		playerRound++;
		printBoard();
		playerInput();
		counter = 1;
		goto jump2;
	}

	if (counter != 0 && !playerCapture(newcol1, newrow1, newcol2, newrow2))
	{
		clear();
		cout << "you must capture the pieces!! Please try again" << endl;
		pause();
		playerRound++;
		printBoard();
		playerInput();
		counter = 1;
		goto jump2;
	}

	else if (!multiCapture(newcol2, newrow2) && !playerCapture(newcol1, newrow1, newcol2, newrow2)) // before swap status restart point**
		status = 0;

	//                  allows player to capture       && players move 2 space (handle capture logic)
	if (playerCapture(newcol1, newrow1, newcol2, newrow2) && abs(col2 - col1) == 2)
	{
		counter = 0;
	jump2:
		if (counter == 0)
		{
			swapPiece(newrow1, newcol1, newrow2, newcol2);
			status = 1;
		}

		if (multiCapture(newcol2, newrow2)) // check if still can move
		{
			char temp;
			printBoard();
			while (true)
			{
				cout << "You can still capture, do u want to capture?\n"
					<< "Enter '1' if yes and '2' for no" << endl;
				cin >> temp;

				if (temp == '1')
				{
					playerRound--;
					counter = 1;
					temprow1 = newrow2;
					tempcol1 = newcol2;
					break;
				}
				else if (temp == '2')
				{
					status = 1;
					counter = 0;
					break;
				}
				else
				{
					clear();
					cout << "Invalid input! Please try again" << endl;
					pause();
					printBoard();
					playerInput();
				}
			}
		}

		// else if (!multiCapture(newcol2, newrow2) && playerCapture(newcol1, newrow1, newcol2, newrow2))
			// status = 0;
		return false;
	}

	//   move left/right  || move up/down
	else if (row1 == row2 || col1 == col2 || abs(col2 - col1) != 1)
		return true;

	if (playerRound % 2 == 0) //a's turn
	{
		// 					origin  != a   || doesnt move upward by 1
		if (board[newrow1][newcol1] != 'a' || row2 - row1 != -1)
			return true;
	}
	else if (playerRound % 2 == 1)//b's turn
	{
		//                  origin != b    || doesnt move downward by 1
		if (board[newrow1][newcol1] != 'b' || row2 - row1 != 1)
			return true;
	}

	else if (col2 - col1 != 1 && col2 - col1 != -1)
		return true;

	return false;
}

//allows player to capture 1 piece
bool playerCapture(int newcol1, int newrow1, int newcol2, int newrow2)
{
	//	player 1(a)'s turn   && check if moves exactly 2    && origin == 'a'
	if (playerRound % 2 == 0 && abs(newrow2 - newrow1) == 2 && board[newrow1][newcol1] == 'a')
	{
		// top left == 'b'						  && move left by 2			 && eat upwards
		if ((board[newrow1 - 1][newcol1 - 1] == 'b' || board[newrow1 - 1][newcol1 - 1] == 'B') && newcol2 - newcol1 == -2 && newrow2 - newrow1 == -2)
		{
			captureflag = 1;
			return true;
		}
		// top right == 'b'							   &&	move right by 2 &&  eat upwards
		if ((board[newrow1 - 1][newcol1 + 1] == 'b' || board[newrow1 - 1][newcol1 + 1] == 'B') && newcol2 - newcol1 == 2 && newrow2 - newrow1 == -2)
		{
			captureflag = 2;
			return true;
		}
		// bottom left == 'b'					  &&	move left by 2	     && eat downwards
		if ((board[newrow1 + 1][newcol1 - 1] == 'b' || board[newrow1 + 1][newcol1 - 1] == 'B') && newcol2 - newcol1 == -2 && newrow2 - newrow1 == 2)
		{
			captureflag = 3;
			return true;
		}
		// bottom right == 'b'					  &&	move right by 2		&& eat downwards
		if ((board[newrow1 + 1][newcol1 + 1] == 'b' || board[newrow1 + 1][newcol1 + 1] == 'B') && newcol2 - newcol1 == 2 && newrow2 - newrow1 == 2)
		{
			captureflag = 4;
			return true;
		}
	}
	//	player 2(b)'s turn   && check if moves exactly 2    && origin == 'b'
	if (playerRound % 2 == 1 && abs(newrow2 - newrow1) == 2 && board[newrow1][newcol1] == 'b') // player 2(b)'s turn
	{
		// bottom left == 'a'					  && move left by 2
		if ((board[newrow1 + 1][newcol1 - 1] == 'a' || board[newrow1 + 1][newcol1 - 1] == 'A') && newcol2 - newcol1 == -2 && newrow2 - newrow1 == 2)
		{
			captureflag = 5;
			return true;
		}
		// bottom right == 'a'						   && move right by 2
		if ((board[newrow1 + 1][newcol1 + 1] == 'a' || board[newrow1 + 1][newcol1 + 1] == 'A') && newcol2 - newcol1 == 2 && newrow2 - newrow1 == 2)
		{
			captureflag = 6;
			return true;
		}
		// top left == 'a'					  && move left by 2
		if ((board[newrow1 - 1][newcol1 - 1] == 'a' || board[newrow1 - 1][newcol1 - 1] == 'A') && newcol2 - newcol1 == -2 && newrow2 - newrow1 == -2)
		{
			captureflag = 7;
			return true;
		}
		// top right == 'a'						   && move right by 2
		if ((board[newrow1 - 1][newcol1 + 1] == 'a' || board[newrow1 - 1][newcol1 + 1] == 'A') && newcol2 - newcol1 == 2 && newrow2 - newrow1 == -2)
		{
			captureflag = 8;
			return true;
		}
	}
	return false;
}

//allows player to capture multiple piece
bool multiCapture(int newcol2, int newrow2)
{
	if (playerRound % 2 == 0)
	{
		// check the surrounding of 'a' if it is capturable
		if (board[newrow2][newcol2] == 'a' &&
			      (((board[newrow2 - 1][newcol2 + 1] == 'b' || board[newrow2 - 1][newcol2 - 1] == 'B') && board[newrow2 - 2][newcol2 + 2] == '#')
				|| ((board[newrow2 - 1][newcol2 - 1] == 'b' || board[newrow2 - 1][newcol2 - 1] == 'B') && board[newrow2 - 2][newcol2 - 2] == '#')
				|| ((board[newrow2 + 1][newcol2 + 1] == 'b' || board[newrow2 + 1][newcol2 + 1] == 'B') && board[newrow2 + 2][newcol2 + 2] == '#')
				|| ((board[newrow2 + 1][newcol2 - 1] == 'b' || board[newrow2 + 1][newcol2 - 1] == 'B') && board[newrow2 + 2][newcol2 - 2] == '#')
				))
			return true;
	}
	else
	{
		// check the surrounding of 'b' if it is capturable
		if (board[newrow2][newcol2] == 'b' &&
				  (((board[newrow2 - 1][newcol2 + 1] == 'a' || board[newrow2 - 1][newcol2 - 1] == 'A') && board[newrow2 - 2][newcol2 + 2] == '#')
				|| ((board[newrow2 - 1][newcol2 - 1] == 'a' || board[newrow2 - 1][newcol2 - 1] == 'A') && board[newrow2 - 2][newcol2 - 2] == '#')
				|| ((board[newrow2 + 1][newcol2 + 1] == 'a' || board[newrow2 + 1][newcol2 + 1] == 'A') && board[newrow2 + 2][newcol2 + 2] == '#')
				|| ((board[newrow2 + 1][newcol2 - 1] == 'a' || board[newrow2 + 1][newcol2 - 1] == 'A') && board[newrow2 + 2][newcol2 - 2] == '#')
				))
			return true;
	}
	return false;
}

bool crownCapture(int newcol1, int newrow1, int newcol2, int newrow2)
{
	int temp_a = 0;
	int temp_b = 0;
	int temp_junk = 0;
	int col1;
	int row1;

	if (playerRound % 2 == 0 && board[newrow1][newcol1] == 'A')
	{
		//moves towards bottom right
		if (newcol2 - newcol1 > 0 && newrow2 - newrow1 > 0)
			for (int i = 1; newrow1 + i != newrow2 && newcol1 + i != newcol2; i++)
			{
				if (board[newrow1 + i][newcol1 + i] == 'b' || board[newrow1 + i][newcol1 + i] == 'B')
				{
					temp_b++;
					row1 = newrow1 + i;
					col1 = newcol1 + i;
				}
				else if (board[newrow1 + i][newcol1 + i] == 'a' || board[newrow1 + i][newcol1 + i] == ' ')
					temp_junk++;
			}
		//moves towards top left
		if (newcol2 - newcol1 < 0 && newrow2 - newrow1 < 0)
			for (int i = 1; newrow1 - i != newrow2 && newcol1 - i != newcol2; i++)
			{
				if (board[newrow1 - i][newcol1 - i] == 'b' || board[newrow1 - i][newcol1 - i] == 'B')
				{
					temp_b++;
					row1 = newrow1 - i;
					col1 = newcol1 - i;
				}
				else if (board[newrow1 - i][newcol1 - i] == 'a' || board[newrow1 - i][newcol1 - i] == ' ')
					temp_junk++;
			}
		//moves toward top right
		if (newcol2 - newcol1 > 0 && newrow2 - newrow1 < 0)
			for (int i = 1; newrow1 - i != newrow2 && newcol1 + i != newcol2; i++)
			{
				if (board[newrow1 - i][newcol1 + i] == 'b' || board[newrow1 - i][newcol1 + i] == 'B')
				{
					temp_b++;
					row1 = newrow1 - i;
					col1 = newcol1 + i;
				}
				else if (board[newrow1 - i][newcol1 + i] == 'a' || board[newrow1 - i][newcol1 + i] == ' ')
					temp_junk++;
			}
		//moves towards bottom left
		if (newcol2 - newcol1 < 0 && newrow2 - newrow1 > 0)
			for (int i = 1; newrow1 + i != newrow2 && newcol1 - i != newcol2; i++)
			{
				if (board[newrow1 + i][newcol1 - i] == 'b' || board[newrow1 + i][newcol1 - i] == 'B')
				{
					temp_b++;
					row1 = newrow1 + i;
					col1 = newcol1 - i;
				}
				else if (board[newrow1 + i][newcol1 - i] == 'a' || board[newrow1 + i][newcol1 - i] == ' ')
					temp_junk++;

			}
	}

	if (playerRound % 2 == 1 && board[newrow1][newcol1] == 'B')
	{
		//moves towards bottom right
		if (newcol2 - newcol1 > 0 && newrow2 - newrow1 > 0)
			for (int i = 1; newrow1 + i != newrow2 && newcol1 + i != newcol2; i++)
			{
				if (board[newrow1 + i][newcol1 + i] == 'a' || board[newrow1 + i][newcol1 + i] == 'a')
				{
					temp_b++;
					row1 = newrow1 + i;
					col1 = newcol1 + i;
				}
				else if (board[newrow1 + i][newcol1 + i] == 'b' || board[newrow1 + i][newcol1 + i] == ' ')
					temp_junk++;
			}
		//moves towards top left
		if (newcol2 - newcol1 < 0 && newrow2 - newrow1 < 0)
			for (int i = 1; newrow1 - i != newrow2 && newcol1 - i != newcol2; i++)
			{
				if (board[newrow1 - i][newcol1 - i] == 'a' || board[newrow1 + i][newcol1 - i] == 'A')
				{
					temp_b++;
					row1 = newrow1 - i;
					col1 = newcol1 - i;

				}
				else if (board[newrow1 - i][newcol1 - i] == 'b' || board[newrow1 + i][newcol1 + i] == ' ')
					temp_junk++;
			}
		//moves toward top right
		if (newcol2 - newcol1 > 0 && newrow2 - newrow1 < 0)
			for (int i = 1; newrow1 - i != newrow2 && newcol1 + i != newcol2; i++)
			{
				if (board[newrow1 - i][newcol1 + i] == 'a' || board[newrow1 - i][newcol1 + i] == 'A')
				{
					temp_b++;
					row1 = newrow1 - i;
					col1 = newcol1 + i;
				}
				else if (board[newrow1 - i][newcol1 + i] == 'b' || board[newrow1 - i][newcol1 + i] == ' ')
					temp_junk++;
			}
		//moves towards bottom left
		if (newcol2 - newcol1 < 0 && newrow2 - newrow1 > 0)
			for (int i = 1; newrow1 + i != newrow2 && newcol1 - i != newcol2; i++)
			{
				if (board[newrow1 + i][newcol1 - i] == 'a' || board[newrow1 + i][newcol1 - i] == 'A')
				{
					temp_b++;
					row1 = newrow1 + i;
					col1 = newcol1 - i;
				}
				else if (board[newrow1 + i][newcol1 - i] == 'b' || board[newrow1 + i][newcol1 - i] == ' ')
					temp_junk++;
			}
	}

	//means there is no pieces in the middle of origin and destination
	if (temp_junk == 0 && temp_a == 0 && temp_b == 0 && board[newrow1][newcol1] != 'a' && board[newrow1][newcol1] != 'b')
	{
		swapPiece(newrow1, newcol1, newrow2, newcol2);
		return true;
	}
	// temp_junk == 0 means there is nothing in middle of origin
	else if (temp_junk != 0)
		return false;

	else if (temp_a == 1)
	{
		swapPiece(newrow1, newcol1, newrow2, newcol2);
		board[row1][col1] = '#';
		return true;
	}
	else if (temp_b == 1)
	{
		swapPiece(newrow1, newcol1, newrow2, newcol2);
		board[row1][col1] = '#';
		return true;
	}

	return false;
}

bool crownMultiCapture(int newcol1, int newrow1, int newcol2, int newrow2)
{
	if (playerRound % 2 == 0)
		for (int i = 1; i < 10; i++)
		{
			if ((board[newrow2 + i][newcol2 + i] == 'b' || board[newrow2 + i][newcol2 + i] == 'B') && board[newrow2 + i + 1][newcol2 + i + 1] == '#')
				return true;
			if ((board[newrow2 - i][newcol2 - i] == 'b' || board[newrow2 - i][newcol2 - i] == 'B') && board[newrow2 - i - 1][newcol2 - i - 1] == '#')
				return true;
			if ((board[newrow2 + i][newcol2 - i] == 'b' || board[newrow2 + i][newcol2 - i] == 'B') && board[newrow2 + i + 1][newcol2 - i - 1] == '#')
				return true;
			if ((board[newrow2 - i][newcol2 + i] == 'b' || board[newrow2 - i][newcol2 + i] == 'B') && board[newrow2 - i - 1][newcol2 + i + 1] == '#')
				return true;
		}
	if (playerRound % 2 == 1)
		for (int i = 1; i < 10; i++)
		{
			if ((board[newrow2 + i][newcol2 + i] == 'a' || board[newrow2 + i][newcol2 + i] == 'A') && board[newrow2 + i + 1][newcol2 + i + 1] == '#')
				return true;
			if ((board[newrow2 - i][newcol2 - i] == 'a' || board[newrow2 - i][newcol2 - i] == 'A') && board[newrow2 - i - 1][newcol2 - i - 1] == '#')
				return true;
			if ((board[newrow2 + i][newcol2 - i] == 'a' || board[newrow2 + i][newcol2 - i] == 'A') && board[newrow2 + i + 1][newcol2 - i - 1] == '#')
				return true;
			if ((board[newrow2 - i][newcol2 + i] == 'a' || board[newrow2 - i][newcol2 + i] == 'A') && board[newrow2 - i - 1][newcol2 + i + 1] == '#')
				return true;
		}
	return false;
}

bool determineCapture(int newcol1, int newrow1, int newcol2, int newrow2)
{
	int temp_a = 0;
	int temp_b = 0;
	int temp_junk = 0;
	int col1;
	int row1;
	if (playerRound % 2 == 0)
	{
		if (board[newrow1][newcol1] == 'A')
		{
			//moves towards bottom right
			if (newcol2 - newcol1 > 0 && newrow2 - newrow1 > 0)
				for (int i = 1; newrow1 + i != newrow2 && newcol1 + i != newcol2; i++)
				{
					if (board[newrow1 + i][newcol1 + i] == 'b')
						temp_b++;
					else if (board[newrow1 + i][newcol1 + i] == 'a' || board[newrow1 + i][newcol1 + i] == ' ')
						temp_junk++;
				}
			//moves towards top left
			if (newcol2 - newcol1 < 0 && newrow2 - newrow1 < 0)
				for (int i = 1; newrow1 - i != newrow2 && newcol1 - i != newcol2; i++)
				{
					if (board[newrow1 - i][newcol1 - i] == 'b')
						temp_b++;
					else if (board[newrow1 - i][newcol1 - i] == 'a' || board[newrow1 + i][newcol1 + i] == ' ')
						temp_junk++;
				}
			//moves toward top right
			if (newcol2 - newcol1 > 0 && newrow2 - newrow1 < 0)
				for (int i = 1; newrow1 - i != newrow2 && newcol1 + i != newcol2; i++)
				{
					if (board[newrow1 - i][newcol1 + i] == 'b')
						temp_b++;
					else if (board[newrow1 - i][newcol1 + i] == 'a' || board[newrow1 - i][newcol1 + i] == ' ')
						temp_junk++;
				}
			//moves towards bottom left
			if (newcol2 - newcol1 < 0 && newrow2 - newrow1 > 0)
				for (int i = 1; newrow1 + i != newrow2 && newcol1 - i != newcol2; i++)
				{
					if (board[newrow1 + i][newcol1 - i] == 'b')
						temp_b++;
					else if (board[newrow1 + i][newcol1 - i] == 'a' || board[newrow1 + i][newcol1 - i] == ' ')
						temp_junk++;

				}
		}
	}
	if (playerRound % 2 == 1)
	{
		if (board[newrow1][newcol1] == 'B')
		{
			//moves towards bottom right
			if (newcol2 - newcol1 > 0 && newrow2 - newrow1 > 0)
				for (int i = 1; newrow1 + i != newrow2 && newcol1 + i != newcol2; i++)
				{
					if (board[newrow1 + i][newcol1 + i] == 'a')
						temp_b++;
					else if (board[newrow1 + i][newcol1 + i] == 'b' || board[newrow1 + i][newcol1 + i] == ' ')
						temp_junk++;
				}
			//moves towards top left
			if (newcol2 - newcol1 < 0 && newrow2 - newrow1 < 0)
				for (int i = 1; newrow1 - i != newrow2 && newcol1 - i != newcol2; i++)
				{
					if (board[newrow1 - i][newcol1 - i] == 'a')
						temp_b++;
					else if (board[newrow1 - i][newcol1 - i] == 'b' || board[newrow1 + i][newcol1 + i] == ' ')
						temp_junk++;
				}
			//moves toward top right
			if (newcol2 - newcol1 > 0 && newrow2 - newrow1 < 0)
				for (int i = 1; newrow1 - i != newrow2 && newcol1 + i != newcol2; i++)
				{
					if (board[newrow1 - i][newcol1 + i] == 'a')
						temp_b++;
					else if (board[newrow1 - i][newcol1 + i] == 'b' || board[newrow1 - i][newcol1 + i] == ' ')
						temp_junk++;
				}
			//moves towards bottom left
			if (newcol2 - newcol1 < 0 && newrow2 - newrow1 > 0)
				for (int i = 1; newrow1 + i != newrow2 && newcol1 - i != newcol2; i++)
				{
					if (board[newrow1 + i][newcol1 - i] == 'a')
						temp_b++;
					else if (board[newrow1 + i][newcol1 - i] == 'b' || board[newrow1 + i][newcol1 - i] == ' ')
						temp_junk++;
				}
		}
	}
	if (temp_junk == 0 && temp_a == 0 && temp_b == 0)
		return true;

	return false;
}

void swapPiece(int row1, int col1, int row2, int col2) //take input from playerMovement() and do the swap logic
{
	char temp = board[row1][col1];
	board[row1][col1] = board[row2][col2];
	board[row2][col2] = temp;
	if (playerCapture)
	{
		switch (captureflag)
		{
		case 1: board[row1 - 1][col1 - 1] = '#';
			break;
		case 2: board[row1 - 1][col1 + 1] = '#';
			break;
		case 3: board[row1 + 1][col1 - 1] = '#';
			break;
		case 4: board[row1 + 1][col1 + 1] = '#';
			break;
		case 5: board[row1 + 1][col1 - 1] = '#';
			break;
		case 6: board[row1 + 1][col1 + 1] = '#';
			break;
		case 7: board[row1 - 1][col1 - 1] = '#';
			break;
		case 8: board[row1 - 1][col1 + 1] = '#';
			break;
		default:
			break;
		}
		captureflag = 0;
	}
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
		<< "If you want to exit program, enter b4b4\n\n";
	pause();
	printBoard();
	playerInput();
}

void calculatePiece()//determine pieces that is left in the game
{
	int total_a = 0;
	int total_b = 0;
	for (int row = 0; row < 10; ++row)//prints the board
		for (int col = 0; col < 10; ++col)
			if (board[row][col] == 'a' || board[row][col] == 'A')//check the amount of 'a' and 'A'
				total_a++;
			else if (board[row][col] == 'b' || board[row][col] == 'B')//check the amount of 'b' and 'B'
				total_b++;
	cout << "Remaining a: " << total_a << endl;
	cout << "Remaining b: " << total_b << endl;
	if (total_a == 0)
	{
		cout << "Player 2(b) victory!!" << endl;
		exit(0);
	}
	else if (total_b == 0)
	{
		cout << "Player 1(a) victory!!" << endl;
		exit(0);
	}
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
	if (playerRound % 2 == 1)
		fout << "Next player: b" << endl;
	else
		fout << "Next player: a" << endl;

	fout << playerRound << endl;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
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
	string temp;
	ifstream fin;
	fin.open("save.txt");
	clear();
	getline(fin, temp);
	fin >> playerRound;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			fin >> board[i][j];
			if (board[i][j] == '-')
				board[i][j] = ' ';
		}
	}
	fin.close();
}
















