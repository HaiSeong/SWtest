#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>

char blockModel[][4][4] =
{
	{
		{0, 0, 0, 0},
		{1, 0, 0, 0},
		{1, 1, 1, 0},
		{0, 0, 0, 0} },
	{
		{0, 1, 0, 0},
		{0, 1, 0, 0},
		{1, 1, 0, 0},
		{0, 0, 0, 0} },
	{
		{0, 0, 0, 0},
		{1, 1, 1, 0},
		{0, 0, 1, 0},
		{0, 0, 0, 0} },
	{
		{0, 0, 0, 0},
		{1, 1, 0, 0},
		{1, 0, 0, 0},
		{1, 0, 0, 0} },
	{
		{0, 0, 0, 0},
		{0, 0, 1, 0},
		{1, 1, 1, 0},
		{0, 0, 0, 0} },
	{
		{0, 0, 0, 0},
		{0, 1, 1, 0},
		{0, 0, 1, 0},
		{0, 0, 1, 0} },
	{
		{0, 0, 0, 0},
		{0, 1, 1, 1},
		{0, 1, 0, 0},
		{0, 0, 0, 0} },
	{
		{0, 1, 0, 0},
		{0, 1, 0, 0},
		{0, 1, 1, 0},
		{0, 0, 0, 0} },
	{
		{0, 0, 0, 0},
		{0, 1, 0, 0},
		{1, 1, 1, 0},
		{0, 0, 0, 0} },
	{
		{0, 0, 0, 0},
		{0, 1, 0, 0},
		{1, 1, 0, 0},
		{0, 1, 0, 0} },
	{
		{0, 0, 0, 0},
		{0, 0, 0, 0},
		{1, 1, 1, 0},
		{0, 1, 0, 0} },
	{
		{0, 0, 0, 0},
		{0, 1, 0, 0},
		{0, 1, 1, 0},
		{0, 1, 0, 0} },
	{
		{0, 1, 0, 0},
		{0, 1, 0, 0},
		{0, 1, 0, 0},
		{0, 1, 0, 0} },
	{
		{0, 0, 0, 0},
		{0, 0, 0, 0},
		{1, 1, 1, 1},
		{0, 0, 0, 0} },
	{
		{0, 1, 0, 0},
		{0, 1, 0, 0},
		{0, 1, 0, 0},
		{0, 1, 0, 0} },
	{
		{0, 0, 0, 0},
		{0, 0, 0, 0},
		{1, 1, 1, 1},
		{0, 0, 0, 0} },
	{
		{1, 1, 0, 0},
		{1, 1, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0} },
	{
		{1, 1, 0, 0},
		{1, 1, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0} },
	{
		{1, 1, 0, 0},
		{1, 1, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0} },
	{
		{1, 1, 0, 0},
		{1, 1, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0} },
	{
		{0, 0, 0, 0},
		{0, 1, 1, 0},
		{1, 1, 0, 0},
		{0, 0, 0, 0} },
	{
		{0, 1, 0, 0},
		{0, 1, 1, 0},
		{0, 0, 1, 0},
		{0, 0, 0, 0} },
	{
		{0, 0, 0, 0},
		{0, 1, 1, 0},
		{1, 1, 0, 0},
		{0, 0, 0, 0} },
	{
		{0, 1, 0, 0},
		{0, 1, 1, 0},
		{0, 0, 1, 0},
		{0, 0, 0, 0} },
	{
		{0, 0, 0, 0},
		{1, 1, 0, 0},
		{0, 1, 1, 0},
		{0, 0, 0, 0} },
	{
		{0, 1, 0, 0},
		{1, 1, 0, 0},
		{1, 0, 0, 0},
		{0, 0, 0, 0} },
	{
		{0, 0, 0, 0},
		{1, 1, 0, 0},
		{0, 1, 1, 0},
		{0, 0, 0, 0} },
	{
		{0, 1, 0, 0},
		{1, 1, 0, 0},
		{1, 0, 0, 0},
		{0, 0, 0, 0} }
};
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define SPACE 32
// Size of gameboard
#define  GBOARD_WIDTH    16
#define  GBOARD_HEIGHT   12
// Starting point of gameboard
#define  GBOARD_ORIGIN_X  4
#define  GBOARD_ORIGIN_Y  2
int curPosX = 0;
int curPosY = 0;
int block_id;
int speed = 50; // speed : 50
int gameBoardInfo[GBOARD_HEIGHT + 2][GBOARD_WIDTH + 1] = { 0 };
int score = 0;

void SetCurrentCursorPos(int x, int y);
COORD GetCurrentCursorPos(void);
void RemoveCursor(void);
void ShowBlock(char blockInfo[4][4]);
void DeleteBlock(char blockInfo[4][4]);
int ShiftRight();
int ShiftLeft();
int RotateBlock();
int BlockDown();
int BlockUp();
void SpaceDown();
void ProcessKeyInput();
void DrawGameBoard();
int DetectCollision(int posX, int posY, char blockInfo[4][4]);
void AddBlockToBoard(void);
int IsGameOver(void);
void RemoveFillUpLine(void);
void RedrawBlocks(void);

int main()
{
	for (int x = 0; x < GBOARD_WIDTH; x++)
	{
		gameBoardInfo[0][x] = 1;
		gameBoardInfo[GBOARD_HEIGHT+1][x] = 1;
	}
	for (int y = 0; y < GBOARD_HEIGHT + 2; y++)
		gameBoardInfo[y][GBOARD_WIDTH] = 1;
	SetCurrentCursorPos((GBOARD_ORIGIN_X + GBOARD_WIDTH + 2) * 2, GBOARD_ORIGIN_Y);
	printf("Score : %d", score);
	srand((unsigned int)time(NULL));
	block_id = (rand() % 7) * 4;
	RemoveCursor();
	DrawGameBoard();
	curPosX = GBOARD_ORIGIN_X;
	curPosY = GBOARD_HEIGHT / 2;
	while (1)
	{
		if (IsGameOver())
			break;
		while (1)
		{
			if (ShiftRight() == 0)
			{
				AddBlockToBoard();
				srand((unsigned int)time(NULL));
				block_id = (rand() % 7) * 4;
				curPosX = GBOARD_ORIGIN_X;
				curPosY = GBOARD_HEIGHT / 2;
				SetCurrentCursorPos(curPosX, curPosY);
				ShowBlock(blockModel[block_id]);
				break;
			}
			ProcessKeyInput();
		}
		RemoveFillUpLine();
		SetCurrentCursorPos((GBOARD_ORIGIN_X + GBOARD_WIDTH + 2) * 2, GBOARD_ORIGIN_Y);
		printf("Score : %d", score);
	}
	SetCurrentCursorPos((GBOARD_ORIGIN_X + GBOARD_WIDTH + 2) * 2, GBOARD_ORIGIN_Y + 2);
	puts("Game Over!!");
	getchar();
	return 0;
}

void SetCurrentCursorPos(int x, int y) // move cursor to x, y
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

COORD GetCurrentCursorPos(void) // return COORD(curPoint.x, curPoint.y)
{
	COORD curPoint;
	CONSOLE_SCREEN_BUFFER_INFO curInfo;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	curPoint.X = curInfo.dwCursorPosition.X;
	curPoint.Y = curInfo.dwCursorPosition.Y;
	return curPoint;
}

void RemoveCursor(void) // hide cursor
{
	CONSOLE_CURSOR_INFO curInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	curInfo.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}

void ShowBlock(char blockInfo[4][4]) // draw block
{
	COORD curPos = GetCurrentCursorPos();
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			SetCurrentCursorPos(curPos.X + x * 2, curPos.Y + y);
			if (blockInfo[y][x] == 1)
				printf("■");
		}
	}
	SetCurrentCursorPos(curPos.X, curPos.Y); // reset cursor
}

void DeleteBlock(char blockInfo[4][4]) // delete block
{
	COORD curPos = GetCurrentCursorPos();
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			SetCurrentCursorPos(curPos.X + x * 2, curPos.Y + y);
			if (blockInfo[y][x] == 1)
				printf("  ");
		}
	}
	SetCurrentCursorPos(curPos.X, curPos.Y); // reset cursor
}

int ShiftRight() // move right | if can go : 1, cannot go : 0
{
	// DetectCollision() -> if there is collosion : 0, no collision : 1
	if (!DetectCollision(curPosX + 2, curPosY, blockModel[block_id]))
		return 0;
	DeleteBlock(blockModel[block_id]); // delete before block
	curPosX += 2;
	SetCurrentCursorPos(curPosX, curPosY); // move cursor
	ShowBlock(blockModel[block_id]); // show block
	return 1;
}

int ShiftLeft() // move left | if can go : 1, cannot go : 0
{
	// DetectCollision() -> if there is collosion : 0, no collision : 1
	if (!DetectCollision(curPosX - 2, curPosY, blockModel[block_id]))
		return 0;
	DeleteBlock(blockModel[block_id]); // delete before block
	curPosX -= 2;
	SetCurrentCursorPos(curPosX, curPosY); // move cursor
	ShowBlock(blockModel[block_id]); // show block
	return 1;
}

int RotateBlock() // rotate blcok | if can : 1, cannot go : 0
{
	int block_base = block_id - block_id % 4; // 0, 4, 8, 12 ... first block of 4 blocks
	int block_rotated = block_base + (block_id + 1) % 4; // rotated block
	// DetectCollision() -> if there is collosion : 0, no collision : 1
	if (!DetectCollision(curPosX, curPosY, blockModel[block_rotated]))
		return 0;
	DeleteBlock(blockModel[block_id]); // delete before block
	block_id = block_rotated; // change block_id
	ShowBlock(blockModel[block_id]); // show block
	return 1;
}

int BlockDown() // move down | if can go : 1, cannot go : 0
{
	// DetectCollision() -> if there is collosion : 0, no collision : 1
	if (!DetectCollision(curPosX, curPosY + 1, blockModel[block_id]))
		return 0;
	DeleteBlock(blockModel[block_id]); // delete before block
	curPosY += 1;
	SetCurrentCursorPos(curPosX, curPosY); // move cursor
	ShowBlock(blockModel[block_id]); // show block
	return 1;
}

int BlockUp() // move down | if can go : 1, cannot go : 0
{
	// DetectCollision() -> if there is collosion : 0, no collision : 1
	if (!DetectCollision(curPosX, curPosY - 1, blockModel[block_id]))
		return 0;
	DeleteBlock(blockModel[block_id]); // delete before block
	curPosY -= 1;
	SetCurrentCursorPos(curPosX, curPosY); // move cursor
	ShowBlock(blockModel[block_id]); // show block
	return 1;
}

void SpaceDown() // block goes to bottom
{
	while (ShiftRight()); // while BlockDown == 1 do BlockDown
}

void ProcessKeyInput() // get input
{
	for (int i = 0; i < 20; i++) // 20 input / 1 sec
	{
		if (_kbhit() != 0) // if there was keyboard hit
		{
			int key = _getch(); // get key
			switch (key)
			{
			case LEFT: RotateBlock(); break;
			case RIGHT: RotateBlock(); break;
			case UP: BlockUp(); break;
			case DOWN: BlockDown(); break;
			case SPACE: SpaceDown(); break;
			}
		}
		Sleep(speed); // speed : 50
	} // speed * times = 50 * 20 = 1000 -> 1sec
}

void DrawGameBoard() // draw game board
{
	for (int x = 0; x <= GBOARD_WIDTH; x++) // Repeat GBOARD_HEIGHT times
	{
		SetCurrentCursorPos(GBOARD_ORIGIN_X + x * 2, GBOARD_ORIGIN_Y); // move y
		if (x == GBOARD_WIDTH) // last positon
			printf("┐");
		else
			printf("─");
	}
	for (int x = 0; x <= GBOARD_WIDTH; x++) // Repeat GBOARD_HEIGHT times
	{
		SetCurrentCursorPos(GBOARD_ORIGIN_X + x * 2, GBOARD_ORIGIN_Y + (GBOARD_HEIGHT + 1)); // move y
		if (x == GBOARD_WIDTH) // last positon
			printf("┘");
		else
			printf("─");
	}
	for (int y = 1; y <= GBOARD_HEIGHT; y++) // Repeat GBOARD_WIDTH times
	{
		SetCurrentCursorPos(GBOARD_ORIGIN_X + GBOARD_WIDTH * 2, GBOARD_ORIGIN_Y + y); // move x
		printf("│");
	}
	SetCurrentCursorPos(GBOARD_ORIGIN_X + GBOARD_WIDTH, GBOARD_ORIGIN_Y); // reset cursor
}

int DetectCollision(int posX, int posY, char blockInfo[4][4]) // if there is Collision : 0, no Collision : 1
{
	// posX, posY : cursor position on terminal
	// arrX, arrY : cursor position on gameboard
	int arrX = (posX - GBOARD_ORIGIN_X) / 2;
	int arrY = (posY - GBOARD_ORIGIN_Y);
	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{	//	If the gameBoardInfo already has 1 in its place
			if ((blockInfo[y][x] == 1) && (gameBoardInfo[arrY + y][arrX + x] == 1))
				return 0; // Collision : 0
		}
	}
	return 1; // No Collision : 1
}

void AddBlockToBoard(void) //  fix the position of the block
{
	// arrX, arrY : metrix of gameboard
	int arrX = (curPosX - GBOARD_ORIGIN_X) / 2;
	int arrY = (curPosY - GBOARD_ORIGIN_Y);
	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			if (blockModel[block_id][y][x] == 1)
				gameBoardInfo[arrY + y][arrX + x] = 1; // 
		}
	}
}

int IsGameOver(void) // if gameover : 1, not gameover : 0
{
	if (!DetectCollision(curPosX, curPosY, blockModel[block_id])) {
		return 1;
	}
	return 0;
}

void RemoveFillUpLine(void) // remove filled line
{
	int y;
	for (int x = GBOARD_WIDTH - 1; x > 0; x--) // from bottom to top
	{
		for (y = 1; y <= GBOARD_HEIGHT; y++)
		{
			if (gameBoardInfo[y][x] == 0) // if line has 0 -> not filled
				break;
		}
		if (y == GBOARD_HEIGHT + 1) // if filled line
		{
			for (int line = x; line > 0; line--) // Copy the top line below
			{
				for (int i = 1; i < GBOARD_HEIGHT + 1; i++)
				{
					gameBoardInfo[i][line] = gameBoardInfo[i][line - 1];
				}
			}
			x++; // Check the line again
			score += 10; // Score up
		}
	}
	RedrawBlocks(); // redraw blocks
}

void RedrawBlocks(void) // redraw blocks
{
	for (int y = 1; y < GBOARD_HEIGHT + 1; y++)
	{
		for (int x = 0; x < GBOARD_WIDTH; x++)
		{
			int cursX = x * 2 + GBOARD_ORIGIN_X;
			int cursY = y + GBOARD_ORIGIN_Y;
			SetCurrentCursorPos(cursX, cursY);
			if (gameBoardInfo[y][x] == 1) // draw block
			{
				printf("■");
			}
			else printf("  ");
		}
	}
}