#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "block.h"
#include <time.h>
#include <conio.h>
#define Q_KEY 113
#define W_KEY 119
#define E_KEY 101
#define A_KEY 97
#define S_KEY 115
#define D_KEY 100
#define Z_KEY 122
#define X_KEY 120
#define C_KEY 99
#define J_KEY 106
#define K_KEY 107
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define SPACE 32
#define GBOARD_WIDTH 10
#define GBOARD_HEIGHT 20
#define GBOARD_ORIGIN_X 4
#define GBOARD_ORIGIN_Y 2

int ProcessKeyInput();	//키 입력받기
void SetCurrentCursorPos(int x, int y); //커서 위치 설정
COORD GetCurrentCursorPos(); //현재 커서 위치 리턴
void ShowBlock(char blockModel[4][4]); //blcok 프린트하기
void DeleteBlock(char blockModel[4][4]); //프린트 된 block 지우기
void RemoveCursor(); //커서 안 보이게 바꾸기
void ShiftRight(); //block을 오른쪽 이동
void ShiftLeft(); //block을 왼쪽 이동
int BlockDown(); //block을 아래로 이동
int RotateBlock(); //block을 반시계 방향으로 회전
void ReverseRotateBlock(); //block을 시계 방향으로 회전
void DrawGameBoard(); //게임판 그리기
int DetectCollision(int posX, int posY, char blockModel[4][4]); //충돌 시 1 return ; 커서가 (posX, posY)에 위치할 때, block의 충돌 여부
void SpaceDown(); //block이 가장 아래로 바로 이동
void AddBlockToBoard(); //block을 논리적 게임판에 추가
int IsGameOver(); //Gameover시 1 return ; Gameover 기준 -> 더이상 block을 출력할 수 없을 때 -> 블록 출력하기 전에 이미 Collision이 일어날 때
void RedrawBlocks(); //논리적 게임판에 따라서 게임판 재출력
void RemoveFillUpLine(); //한 라인이 채워지면, 그 라인 없애기
void printGameboardInfo(); //논리적 게임판을 그대로 출력
void printScore(); //스코어 출력
int *randomBlockList();
void showNextBlock();
int saveBlock();
//void predict();

//전역 변수
int score = 0;
int blockId;
int speed = 20;
int gameBoardInfo[GBOARD_HEIGHT + 1][GBOARD_WIDTH + 2];
int level = 1;
int goal = 100;
int combo = 1;
int flag = 0;
int *blockList;
int blockIndex = 0;
int saveBlockNum = 7;
int flagButtonC = 0;

int main() {
	RemoveCursor();
	DrawGameBoard();

	srand((unsigned int)time(NULL));
	blockList = randomBlockList();
	blockId = blockList[blockIndex] * 4;
	ShowBlock(blockModel[blockId]);
	printScore();
	showNextBlock();

	while (1) {
		COORD p = GetCurrentCursorPos();
		SetCurrentCursorPos(p.X, p.Y);
		if (IsGameOver()) {
			break;
		}
		ShowBlock(blockModel[blockId]);
		while (1) {

			if (BlockDown() == 0) {
				AddBlockToBoard();
				RemoveFillUpLine();
				//printGameboardInfo();
				printScore();
				flagButtonC = 0;
				break;
			}
			if (ProcessKeyInput()) {
				break;
			}

		}
		blockIndex = (blockIndex+1)%7;
		blockId = blockList[blockIndex] * 4;
		if (blockIndex == 6) {
			free(blockList);
			blockList = randomBlockList();
		}
		showNextBlock();
		SetCurrentCursorPos((GBOARD_ORIGIN_X + GBOARD_WIDTH * 2) / 2, GBOARD_ORIGIN_Y);

	}
	SetCurrentCursorPos(0, 0);
	printf("Game Over!");

	system("pause");
	return 0;
}
int ProcessKeyInput() {
	int key = -1;
	int re = 0;
	for (int i = 0; i < 20; i++) {
		if (_kbhit() != 0) {
			key = _getch();
			switch (key)
			{
			case LEFT:
				ShiftLeft();
				fflush(stdin); //버퍼 없애기
				break;
			case RIGHT:
				ShiftRight();
				fflush(stdin); //버퍼 없애기
				break;
			case UP:
				RotateBlock();
				fflush(stdin); //버퍼 없애기
				break;
			case SPACE:
				SpaceDown();
				fflush(stdin); //버퍼 없애기
				break;
			case C_KEY:
				if (!flagButtonC) {
					re = saveBlock();
					flagButtonC = 1;
					return re;
				}
				break;
			case DOWN:
				break;
			default:
				break;
			}
		}
		if (key == SPACE || key == DOWN) {
			break;
			key = -1;
		}
		Sleep(speed);
	}
	return re;
}
void SetCurrentCursorPos(int x, int y) {
	COORD p = { (short)x,(short)y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}
COORD GetCurrentCursorPos() {
	COORD p;
	CONSOLE_SCREEN_BUFFER_INFO curInfo;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	p.X = curInfo.dwCursorPosition.X;
	p.Y = curInfo.dwCursorPosition.Y;

	return p;
}
void ShowBlock(char blockModel[4][4]) {
	COORD currentPos = GetCurrentCursorPos();
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			SetCurrentCursorPos(currentPos.X + x * 2, currentPos.Y + y);
			if (blockModel[y][x] == 1) {
				printf("■");
			}
		}
	}
	SetCurrentCursorPos(currentPos.X, currentPos.Y);
}
void DeleteBlock(char blockModel[4][4]) {
	COORD currentPos = GetCurrentCursorPos();
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			SetCurrentCursorPos(currentPos.X + x * 2, currentPos.Y + y);
			if (blockModel[y][x] == 1) {
				printf("  ");
			}
		}
	}
	SetCurrentCursorPos(currentPos.X, currentPos.Y);
}
void RemoveCursor(void)
{
	CONSOLE_CURSOR_INFO curInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	curInfo.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}
void ShiftRight() {
	COORD p = GetCurrentCursorPos();
	if (DetectCollision(p.X + 2, p.Y, blockModel[blockId])) {
		return;
	}
	DeleteBlock(blockModel[blockId]);
	SetCurrentCursorPos(p.X + 2, p.Y);
	ShowBlock(blockModel[blockId]);
}
void ShiftLeft() {
	COORD p = GetCurrentCursorPos();
	if (DetectCollision(p.X - 2, p.Y, blockModel[blockId])) {
		return;
	}
	DeleteBlock(blockModel[blockId]);
	if (p.X - 2 >= 0) {
		SetCurrentCursorPos(p.X - 2, p.Y);
	}
	ShowBlock(blockModel[blockId]);
}

int BlockDown() {
	COORD p = GetCurrentCursorPos();
	if (DetectCollision(p.X, p.Y + 1, blockModel[blockId])) {
		return 0;
	}
	DeleteBlock(blockModel[blockId]);
	SetCurrentCursorPos(p.X, p.Y + 1);
	ShowBlock(blockModel[blockId]);
	return 1;
}

int RotateBlock() {
	COORD p = GetCurrentCursorPos();
	int newblock;
	newblock = (blockId + 1) % 4 + (blockId / 4) * 4;
	if (DetectCollision(p.X, p.Y, blockModel[newblock])) {
		return 0;
	}
	DeleteBlock(blockModel[blockId]);
	blockId = newblock;
	ShowBlock(blockModel[newblock]);
	return 1;
}
void ReverseRotateBlock() {
	COORD p = GetCurrentCursorPos();
	int newblock;
	newblock = (blockId + 3) % 4 + (blockId / 4) * 4;
	if (DetectCollision(p.X, p.Y, blockModel[newblock])) {
		return;
	}
	DeleteBlock(blockModel[blockId]);
	blockId = newblock;
	ShowBlock(blockModel[newblock]);
}
void DrawGameBoard() {
	int x, y;
	for (y = 0; y <= GBOARD_HEIGHT; y++) {

		SetCurrentCursorPos(GBOARD_ORIGIN_X, GBOARD_ORIGIN_Y + y);
		if (y == GBOARD_HEIGHT)printf("┗");
		else printf("┃");
	}
	for (x = 0; x < GBOARD_WIDTH; x++) {
		SetCurrentCursorPos(GBOARD_ORIGIN_X + 2 * x + 2, GBOARD_ORIGIN_Y + GBOARD_HEIGHT);
		printf("━");
	}
	for (y = 0; y <= GBOARD_HEIGHT; y++) {
		SetCurrentCursorPos(GBOARD_ORIGIN_X + GBOARD_WIDTH * 2 + 2, GBOARD_ORIGIN_Y + y);
		if (y == GBOARD_HEIGHT)printf("┛");
		else printf("┃");
	}

	for (y = 0; y < GBOARD_HEIGHT + 1; y++) {
		gameBoardInfo[y][0] = 1;
		gameBoardInfo[y][GBOARD_WIDTH + 1] = 1;
	}
	for (x = 0; x < GBOARD_WIDTH + 2; x++) {
		gameBoardInfo[GBOARD_HEIGHT][x] = 1;
	}
	SetCurrentCursorPos((GBOARD_ORIGIN_X + GBOARD_WIDTH * 2) / 2, GBOARD_ORIGIN_Y);
}
int DetectCollision(int posX, int posY, char blockModel[4][4]) {
	int x, y;
	int arrX = (posX - GBOARD_ORIGIN_X) / 2;
	int arrY = posY - GBOARD_ORIGIN_Y;
	for (x = 0; x < 4; x++) {
		for (y = 0; y < 4; y++) {
			if (blockModel[y][x] == 1 && gameBoardInfo[arrY + y][arrX + x] == 1) {
				return 1;
			}
		}
	}
	return 0;
}

void SpaceDown()
{
	while (BlockDown());
}
void AddBlockToBoard() {
	COORD p = GetCurrentCursorPos();
	int x, y;
	int arrX = (p.X - GBOARD_ORIGIN_X) / 2;
	int arrY = p.Y - GBOARD_ORIGIN_Y;
	for (x = 0; x < 4; x++) {
		for (y = 0; y < 4; y++) {
			if (blockModel[blockId][y][x] == 1) {
				gameBoardInfo[arrY + y][arrX + x] = 1;
			}
		}
	}
}
int IsGameOver() {
	COORD p = GetCurrentCursorPos();
	if (DetectCollision(p.X, p.Y, blockModel[blockId]))
		return 1;
	return 0;
}
void RedrawBlocks() {
	int x, y;
	int curX, curY;
	for (y = 0; y < GBOARD_HEIGHT; y++) {
		for (x = 1; x < GBOARD_WIDTH + 1; x++) {
			curX = x * 2 + GBOARD_ORIGIN_X;
			curY = y + GBOARD_ORIGIN_Y;
			SetCurrentCursorPos(curX, curY);
			if (gameBoardInfo[y][x] != 1) {
				printf("  ");
			}
			else {
				printf("■");
			}
		}
	}
}
void RemoveFillUpLine() {
	int line, x, y;
	int flag2 = 0;
	for (y = GBOARD_HEIGHT - 1; y > 0; y--) {
		for (x = 1; x < GBOARD_WIDTH + 1; x++) {
			if (gameBoardInfo[y][x] != 1) {
				break;
			}
		}
		if (x == (GBOARD_WIDTH + 1)) {
			if (flag) combo++;
			flag = 1;
			flag2 = 1;
			for (line = y; line > 0; line--) {
				memcpy(&gameBoardInfo[line][1], &gameBoardInfo[line - 1][1], sizeof(int) * GBOARD_WIDTH);
			}
			y++;
			for (x = 1; x < GBOARD_WIDTH + 1; x++) {
				gameBoardInfo[0][x] = 0;
			}
			score += 10 * combo;
		}
	}
	if (!flag2) {
		combo = 1;
		flag = 0;
	}
	RedrawBlocks();
}
void printGameboardInfo() {
	COORD p = GetCurrentCursorPos();
	for (int y = 0; y < GBOARD_HEIGHT + 1; y++) {
		SetCurrentCursorPos(GBOARD_ORIGIN_X + GBOARD_WIDTH * 2 + 4 + 4, y);
		for (int x = 0; x < GBOARD_WIDTH + 2; x++) {
			printf("%d ", gameBoardInfo[y][x]);
		}
	}
	SetCurrentCursorPos(p.X, p.Y);
}
void printScore() {
	COORD p = GetCurrentCursorPos();
	if (goal <= score) {
		goal *= 2;
		score = 0;
		SetCurrentCursorPos(GBOARD_ORIGIN_X + GBOARD_WIDTH * 2 + 6, (GBOARD_ORIGIN_Y + GBOARD_HEIGHT) / 2 + 1);
		printf("Score :                      ");
		level += 1;
		speed -= 1;
	}
	
	SetCurrentCursorPos(GBOARD_ORIGIN_X + GBOARD_WIDTH * 2 + 6, (GBOARD_ORIGIN_Y + GBOARD_HEIGHT) / 2 - 1);
	printf("Level.%d", level);
	SetCurrentCursorPos(GBOARD_ORIGIN_X + GBOARD_WIDTH * 2 + 6, (GBOARD_ORIGIN_Y + GBOARD_HEIGHT) / 2);
	printf("Goal : %d", goal);
	SetCurrentCursorPos(GBOARD_ORIGIN_X + GBOARD_WIDTH * 2 + 6, (GBOARD_ORIGIN_Y + GBOARD_HEIGHT) / 2 + 1);
	printf("Score : %d", score);
	SetCurrentCursorPos(p.X, p.Y);
}
int* randomBlockList() {
	int *List;
	List = (int*)malloc(sizeof(int) * 7);
	for (int i = 0; i < 7; i++) {
		List[i] = i;
	}
	for (int i = 6; i > 0; i--) {
		int index = rand() % (i+1);
		int tmp = List[index];
		List[index] = List[i];
		List[i] = tmp;
	}
	return List;
}
void showNextBlock() {
	COORD p = GetCurrentCursorPos();
	SetCurrentCursorPos(GBOARD_ORIGIN_X + GBOARD_WIDTH * 2 + 6, GBOARD_ORIGIN_Y);
	printf("next block");
	SetCurrentCursorPos(GBOARD_ORIGIN_X + GBOARD_WIDTH * 2 + 6, GBOARD_ORIGIN_Y+1);
	DeleteBlock(blockModel[blockId]);
	ShowBlock(blockModel[blockList[(blockIndex + 1) % 7] * 4]);
	SetCurrentCursorPos(p.X, p.Y);
}
int saveBlock() {
	DeleteBlock(blockModel[blockId]);
	int num;
	if (saveBlockNum != 7) {
		num = 0;
		int tmp = blockId;
		blockId = saveBlockNum;
		saveBlockNum = tmp/4 * 4;
		SetCurrentCursorPos((GBOARD_ORIGIN_X + GBOARD_WIDTH * 2) / 2, GBOARD_ORIGIN_Y);
		ShowBlock(blockModel[blockId]);
	}
	else {
		num = 1;
		saveBlockNum = blockId;
	}
	SetCurrentCursorPos(GBOARD_ORIGIN_X + GBOARD_WIDTH * 2 + 6 + 4*2 + 6, GBOARD_ORIGIN_Y);
	printf("saved block");
	if (!num) {
		SetCurrentCursorPos(GBOARD_ORIGIN_X + GBOARD_WIDTH * 2 + 6 + 4 * 2 + 6, GBOARD_ORIGIN_Y+1);
		DeleteBlock(blockModel[blockId]);
	}
	SetCurrentCursorPos(GBOARD_ORIGIN_X + GBOARD_WIDTH * 2 + 6 + 4 * 2 + 6, GBOARD_ORIGIN_Y);
	printf("saved block");
	SetCurrentCursorPos(GBOARD_ORIGIN_X + GBOARD_WIDTH * 2 + 6 + 4 * 2 + 6, GBOARD_ORIGIN_Y+1);
	ShowBlock(blockModel[saveBlockNum]);

	SetCurrentCursorPos((GBOARD_ORIGIN_X + GBOARD_WIDTH * 2) / 2, GBOARD_ORIGIN_Y);
	return num;
}
//void predict() {
//	COORD p = GetCurrentCursorPos();
//	int i = 0;
//	while (!DetectCollision(p.X, p.Y + i, blockModel[blockId])) {
//		i++;
//	}
//
//}