#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <ctime>
using namespace std;

enum Status {FLAG = 'F', BOMB = 'B', MARSHAL = '1', GENERAL = '2', COLONEL = '3', MAJOR = '4', CAPTAIN = '5', LIEUTENANT = '6', SERGEANT = '7', MINER = '8', SPY = 'S', BLANK = ' ', NONE = '0', RED = 'r', BLUE = 'u'};
const int boardSize = 5;

void init(Status gameBoard[][boardSize], Status color[][boardSize]);
void populate(Status gameBoard[][boardSize], Status color[][boardSize], Status team);
bool check(Status gameBoard[][boardSize], int col, int row);
void print(Status gameBoard[][boardSize]);

int main()
{
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
	cout << endl << "Jason Armitage" << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
	cout << endl << "GENERAL RULES:\n For the most part, the game will follow the standard Stratego rules, although there are some exceptions.\n 1. Both players (BLUE and RED) will have all of their 10 game pieces assigned randomly with the only requirement being that the FLAG must be placed in the back row. RED will start the game first.\n 2. Higher ranked pieces can capture lower ranked pieces in the following order: 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7 -> 8 -> S, meaning that 1 (the MARSHAL) can remove 2 (the GENERAL) and so forth. The MINER (8) piece may strike a BOMB and remove it to occupy the now unoccupied space. A SPY (S), although the lowest ranked piece, may remove the MARSHAL (1) or the GENERAL (2).\n 3. The FLAG and BOMBs are not moveable while all of the other pieces may move one square at a time forward, backward, or sideward, but not diagonally to an open square.\n 4. A player must either move or strike on their turn.\n 5. The game ends when a player strikes their opponents flag.\n ------------------------------------------------------------------------ \n" << endl << endl;
	//seed random number generator	
	srand(time(NULL));
	//initialize arrays
	Status color[boardSize][boardSize];
	Status gameBoard[boardSize][boardSize];
	//clear arrays
	cout << "Initializing game board...\n";
	init(gameBoard, color);
	//set up blue team board
	cout << "Preparing blue team...\n";
	populate(gameBoard, color, BLUE);
	//set up red team board
	cout << "Preparing red team...\n";
	populate(gameBoard, color, RED);
	//print out the game board
	print(gameBoard);

        return 0;
}

void print(Status gameBoard[][boardSize]){

	cout << "+------------+\n";
	//loop through arrays to print out row by row
	for(int i=0; i<boardSize; i++){
		cout << "| ";
		for(int j=0; j<boardSize; j++){
			//if its the first two rows print it out in blue, else if last two rows print it in red, otherwise do not print in color
			if(i<2){
				printf("\033[1;34m%c\033[0m ", static_cast<char>(gameBoard[j][i]));
			}else if(i>2){
				printf("\033[1;31m%c\033[0m ", static_cast<char>(gameBoard[j][i]));
			}else{
				cout << static_cast<char>(gameBoard[j][i]) << " ";
			}
		}
		cout << " |" << endl;
	}

	cout << "+------------+\n";
}

void init(Status gameBoard[][boardSize], Status color[][boardSize]){
	//set the two arrays to default values
	for(int i=0;i<boardSize;i++){
		for(int j=0;j<boardSize;j++){
			gameBoard[j][i] = BLANK;
			if(i == 0 || i == 1){
				color[j][i] = BLUE;
			}else if(i == 3 || i == 4){
				color[j][i] = RED;
			}else{
				color[j][i] = NONE;
			}
		}
	}

}

void populate(Status gameBoard[][boardSize], Status color[][boardSize], Status team){
	//places a single flag on the top and bottom rows randomly
	int flagPos = rand() % boardSize;
	if(team == RED){
		while(!check(gameBoard, flagPos, 4)){
			flagPos = rand() % boardSize;
		}
		gameBoard[flagPos][4] = FLAG;
	}else if(team == BLUE){
		while(!check(gameBoard, flagPos, 0)){
                        flagPos = rand() % boardSize;
                }
		gameBoard[flagPos][0] = FLAG;
	}
	//Randomly Place 3 bombs
	for(int i=0;i<3;i++){
		int bombCol = rand() % boardSize;
	        if(team == RED){
			int bombRow = rand() % 2 + 3;
			while(!check(gameBoard, bombCol, bombRow)){
                        	bombRow = rand() % 2 + 3;
				bombCol = rand() % boardSize;
	                }
        	        gameBoard[bombCol][bombRow] = BOMB;
	        }else if(team == BLUE){
			int bombRow = rand() % 2;
			while(!check(gameBoard, bombCol, bombRow)){
                                bombRow = rand() % 2;
                                bombCol = rand() % boardSize;
                        }
        	        gameBoard[bombCol][bombRow] = BOMB;
	        }

	}

	//randomly place miner
	int minerCol = rand() % boardSize;
        if(team == RED){
                int minerRow = rand() % 2 + 3;
                while(!check(gameBoard, minerCol, minerRow)){
                        minerRow = rand() % 2 + 3;
                        minerCol = rand() % boardSize;
                }
                gameBoard[minerCol][minerRow] = MINER;
        }else if(team == BLUE){
                int minerRow = rand() % 2;
                while(!check(gameBoard, minerCol, minerRow)){
                        minerRow = rand() % 2;
                        minerCol = rand() % boardSize;
                }
                gameBoard[minerCol][minerRow] = MINER;
        }


	//randomly place spy
	int spyCol = rand() % boardSize;
        if(team == RED){
                int spyRow = rand() % 2 + 3;
                while(!check(gameBoard, spyCol, spyRow)){
                        spyRow = rand() % 2 + 3;
                        spyCol = rand() % boardSize;
                }
                gameBoard[spyCol][spyRow] = SPY;
        }else if(team == BLUE){
                int spyRow = rand() % 2;
                while(!check(gameBoard, spyCol, spyRow)){
                        spyRow = rand() % 2;
                        spyCol = rand() % boardSize;
                }
                gameBoard[spyCol][spyRow] = SPY;
        }

	//randomly plac either marshall(1) or general(2)
	int cmdCol = rand() % boardSize;
	int cmdPiece = rand() % 2 + 1;
        if(team == RED){
                int cmdRow = rand() % 2 + 3;
                while(!check(gameBoard, cmdCol, cmdRow)){
                        cmdRow = rand() % 2 + 3;
                        cmdCol = rand() % boardSize;
                }
		if(cmdPiece == MARSHAL){
	                gameBoard[cmdCol][cmdRow] = MARSHAL;
		}else{
			gameBoard[cmdCol][cmdRow] = GENERAL;
		}
        }else if(team == BLUE){
                int cmdRow = rand() % 2;
                while(!check(gameBoard, cmdCol, cmdRow)){
                        cmdRow = rand() % 2;
                        cmdCol = rand() % boardSize;
                }
                if(cmdPiece == MARSHAL){
                        gameBoard[cmdCol][cmdRow] = MARSHAL;
                }else{
                        gameBoard[cmdCol][cmdRow] = GENERAL;
                }

        }

	//randomly assign 3 of colonel major capitan or sergeant
	for(int i=0;i<3;i++){
		int solPiece = rand() % 4;
                int solCol = rand() % boardSize;
                if(team == RED){
                        int solRow = rand() % 2 + 3;
                        while(!check(gameBoard, solCol, solRow)){
                                solRow = rand() % 2 + 3;
                                solCol = rand() % boardSize;
                        }
			switch(solPiece){
				case 0:
					gameBoard[solCol][solRow] = COLONEL;
					break;
				case 1:
                                        gameBoard[solCol][solRow] = MAJOR;
                                        break;
				case 2:
                                        gameBoard[solCol][solRow] = CAPTAIN;
                                        break;
				case 3:
                                        gameBoard[solCol][solRow] = SERGEANT;
                                        break;

			}
                }else if(team == BLUE){
                        int solRow = rand() % 2;
                        while(!check(gameBoard, solCol, solRow)){
                                solRow = rand() % 2;
                                solCol = rand() % boardSize;
                        }
			switch(solPiece){
                                case 0:
                                        gameBoard[solCol][solRow] = COLONEL;
                                        break;
                                case 1:
                                        gameBoard[solCol][solRow] = MAJOR;
                                        break;
                                case 2:
                                        gameBoard[solCol][solRow] = CAPTAIN;
                                        break;
                                case 3:
                                        gameBoard[solCol][solRow] = SERGEANT;
                                        break;

                        }
                }
        }
}
//used to check to see if the current array position has been filled or not
bool check(Status gameBoard[][boardSize], int col, int row){
	if(gameBoard[col][row] == BLANK){
		return true;
	}else{
		return false;
	}
}























