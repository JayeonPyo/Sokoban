#include<stdio.h>
#include<conio.h>
#include<Windows.h>
#include<time.h>




int map[18][18] = {           //좌표
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
	{ 1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1 },
	{ 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
	{ 1, 0, 0, 1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 1, 0, 0, 1, 1 },
	{ 1, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 1, 0, 2, 0, 1 },
	{ 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1 },
	{ 1, 0, 0, 1, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 1 },
	{ 1, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1 },
	{ 1, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1 },
	{ 1, 0, 0, 2, 0, 0, 1, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1 },
	{ 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 3, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
};
//0. "  " 빈공간
//1. "■" 벽
//2. "●" 공
//3. "○" 구멍
//4. "♥" 공을 넣은 구멍
//9. "★"

int playerx, playery;

void printmap()//맵 전체를 출력시켜주는 함수
{
	int i, j;

	for (i = 0; i < 18; i++)
	{
	for (j = 0; j < 18; j++)
	{
	switch (map[i][j])
	{
	case 0:
	printf("  ");
	break;
	case 1:
	printf("■");
	break;
	case 2:
	printf("●");
	break;
	case 3:
	printf("○");
	break;
	case 9:
	printf("★");
	playerx = j;  //가로 == x축
	playery = i; // 세로 == y축
	}
	}
	printf("\n");
	}
}

void gotoxy(int x, int y)//마우스 커서를 (x,y)좌표로 이동시켜주는 함수
{
	COORD pos = { x * 2, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void draw(int x, int y, char c[])//(x,y)좌표에 c를 출력시켜주는 함수
{
	gotoxy(x, y);
	printf("%s", c);
}

void moveplayer(int dx, int dy)
{
	int nextx = playerx + dx, nexty = playery + dy;
	int nextnextx = nextx + dx, nextnexty = nexty + dy;


	if (map[nexty][nextx] == 0 || map[nexty][nextx] == 2)    //0(빈 공간)과 2(채워진 공)일 때만 움직일 수 있게 하는 조건문 <벽 뚫지 못하게 해줌>
	{
	if (map[nexty][nextx] == 2)
	{
	if (map[nextnexty][nextnextx] == 1)
	return;
	if (map[nextnexty][nextnextx] == 3)
	{
	draw(nextnextx, nextnexty, "♥");
	map[nextnexty][nextnextx] = 4;
	}
	else
	{
	draw(nextnextx, nextnexty, "●");
	map[nextnexty][nextnextx] = 2;
	}
	}

	draw(playerx, playery, "  ");  //원래 있던 자리는 빈 공간으로 만들어줌
	map[playery][playerx] = 0;     //배열은 [y좌표][x좌표]

	draw(nextx, nexty, "★");
	map[nexty][nextx] = 9;
	playerx += dx;
	playery += dy;
	}
}

int getballcount()  //남은 공이 몇 개인 지 알려주는 함수, 종류
{
	int i, j, cnt = 0;
	for (i = 0; i < 18; i++){
	for (j = 0; j < 18; j++)
	{
	if (map[i][j] == 2)
	cnt += 1;   //0개가 될 시 실행을 멈춘다.
	}
	}
	return cnt;
}

int main()
{
	char input;

	printmap();

	while (getballcount()>0)
	{

	input = _getch();

	if (input == 'w' || input == 'w')
	{
	moveplayer(0, -1);     //y축이 올라가려면 -1을 해줘야 한다.
	}
	else if (input == 's' || input == 's')
	{
	moveplayer(0, 1);
	}
	else if (input == 'a' || input == 'a')
	{
	moveplayer(-1, 0);
	}
	else if (input == 'd' || input == 'd')
	{
	moveplayer(1, 0);
	}
	}

	draw(2, 4, "game clear");
	printf("종류하려면 아무 키나 누르세요.");
	_getch();


	return 0;
}