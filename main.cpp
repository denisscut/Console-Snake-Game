#include <iostream>
#include <fstream>
#include <cstdlib>
#include <windows.h>
#include <conio.h>
#define DMAX 100
#define SMAX 1104
#define ever ;;

using namespace std;

ifstream in("Top_10.txt");
struct snakexy{
	int x, y;
}snake[SMAX], dir, predir, pdir, pizza;

struct top {
	char nume[30];
	int scor;
}top[100], aux;
bool game_over = 0;
const int width = 50;
const int height = 25;
int mat[DMAX][DMAX];
int snake_l = 1;
int k;

void system_clear() {
	Sleep(30);
	system("CLS");
}

void Start() {
	int i;
	system_clear();
	for (i = 1; i < width; i++)
		cout << '#';
	cout << '\n';
	cout << "#                                               #" << '\n';
	cout << "#                   SNAKE                       #" << '\n';
	cout << "#                                               #" << '\n';
	cout << "#   Options:                                    #" << '\n';
	cout << "#   1. Start the game.                          #" << '\n';
	cout << "#   2. Top 10 players.                          #" << '\n';
	cout << "#                                               #" << '\n';
	cout << "#     _________          _________              #" << '\n';
	cout << "#    /         \\        /         \\             #" << '\n';
	cout << "#   /  /~~~~~\\  \\      /  /~~~~~\\  \\            #" << '\n';
	cout << "#   |  |     |  |      |  |     |  |            #" << '\n';
	cout << "#   |  |     |  |      |  |     |  |         /  #" << '\n';
	cout << "#   |  |     |  |      |  |     |  |       //   #" << '\n';
	cout << "#  (o  o)    \\   \\_____/  /     \\  \\_____/ /    #" << '\n';
	cout << "#   \\__/      \\         /        \\        /     #" << '\n';
	cout << "#    |           ~~~~~~~~~        ~~~~~~~~      #" << '\n';
	cout << "#    ^                                          #" << '\n';
	cout << "#                                               #" << '\n';
	cout << "#                                               #" << '\n';
	cout << "#                GOOD LUCK                      #" << '\n';
	cout << "#                                               #" << '\n';
	cout << "#                                               #" << '\n';
	cout << "#                                               #" << '\n';
	for (i = 1; i < width; i++)
		cout << '#';
}

void surround() {
	// Cream terenul.
	int i;
	for (i = 1; i < width; i++)
		mat[0][i] = 1;
	for (i = 1; i < width; i++)
		mat[height][i] = 1;
	for (i = 0; i <= height; i++)
		mat[i][0] = 1;
	for (i = 0; i <= height; i++)
		mat[i][width] = 1;
}

void snake_clear() {
	int i, j;
	for (i = 1; i < height; i++)
		for (j = 1; j < width; j++)
			mat[i][j] = 0;
}

void make_pizza() {
	pizza.x = rand() % height ;
	pizza.y = rand() & width ;
	if (pizza.x <= 0)
		pizza.x = 1;
	if (pizza.x >= height)
		pizza.x = height - 1;
	if (pizza.y <= 0)
		pizza.y = 1;
	if (pizza.y  >= width)
		pizza.y = width -1;
}

void make_snake() {
	///Snake coordinates at the beginning of the game.
	snake[0].x = 1;
	snake[0].y = 1;
}

void move_snake() {
	if (snake[0].x == pizza.x && snake[0].y == pizza.y) {
		snake_l++;
		make_pizza();
	}
	int i;
	predir.x = snake[0].x;
	predir.y = snake[0].y;
	snake[0].x += dir.x;
	snake[0].y += dir.y;
	for (i = 1; i < snake_l; i++) {
		dir.x = snake[i].x;
		dir.y = snake[i].y;
		snake[i].x = predir.x;
		snake[i].y = predir.y;
		predir.x = dir.x;
		predir.y = dir.y;
	}
	if (snake[0].x == 0 || snake[0].x == height || snake[0].y == 0 || snake[0].y == width)
		game_over = 1;
	if (mat[snake[0].x][snake[0].y] == 2)
		game_over = 1;
}

void draw_snake() {
	int i;
	if (snake_l > 0) {
		mat[snake[0].x][snake[0].y] = 4;
		for (i = 1; i < snake_l; i++)
			mat[snake[i].x][snake[i].y] = 2;
	}
	else {
		for (i = 0; i < snake_l; i++)
			mat[snake[i].x][snake[i].y] = 2;
	}
	mat[pizza.x][pizza.y] = 3;
}

void input() {
	if (_kbhit()) {
		dir.x = dir.y = 0;
		switch (_getch()) {
		case 'w': dir.x = -1; break;
		case 's': dir.x = 1; break;
		case 'd': dir.y = 1; break;
		case 'a': dir.y = -1; break;
		case ' ': dir.x = 0, dir.y = 0; break;
		case 'x': game_over = 1; break;
		}
			if (snake_l > 1) {
				if ((pdir.x == dir.x && dir.y != pdir.y) || (pdir.x != dir.x && dir.y == pdir.y))
					dir.x = pdir.x, dir.y = pdir.y;
			}

			pdir.x = dir.x;
			pdir.y = dir.y;
		
	}
	else {
		dir.x = pdir.x;
		dir.y = pdir.y;
	}
	move_snake();
}

void print() {
	int i, j;
	cout << "<Score: " << snake_l - 1 << " >" << '\n' << "Press x to stop the game.";
	if (dir.x == 0 && dir.y == 0)
		cout << "   Status: Pause";
	else cout << "   Status: In game";
	cout << '\n';
	for (i = 0; i <= height; i++) {
		for (j = 0; j <= width; j++)
			if (mat[i][j] == 1)
				cout << '#';
			else if (mat[i][j] == 2)
				cout << 'o';
			else if (mat[i][j] == 3)
				cout << '+';
			else if (mat[i][j] == 4)
				cout << 'O';
			else
				cout << ' ';
		cout << endl;
	}
}

void sort() {
	int i, x;
	bool ik;
	do {
		ik = true;
		for(i = 0; i < k - 1; i++)
			if (top[i].scor < top[i + 1].scor) {
				aux = top[i];
				top[i] = top[i + 1];
				top[i + 1] = aux;
				ik = false;
			}
	} while (ik == false);
}

void add_Top_10() {
	int i;
	ofstream out("Top_10.txt");
	out << k << '\n';
	for (i = 0; i < k; i++)
		out << top[i].nume << ' ' << top[i].scor << '\n';
	out << '\n';
	out.close();
}

void Top_10() {

	Sleep(3);
	int i;
	cout << "Do you want to save your score? [Y/n]";
	char x;
	cin >> x;
	if (x == 'y' || x == 'Y') {
		in >> k;
		for (i = 0; i < k; i++)
			in >> top[i].nume >> top[i].scor;
		in.close();
		top[k].scor = snake_l;
		cout << "Name: ";
		cin >> top[k].nume;
		k++;
		add_Top_10();
	}
	else cout << '\n' <<  "Ok friend!" << '\n' << '\n' << '\n';
}

void Afis_Top_10() {
	system_clear();
	int i, maxim = 0;
	in >> k;
	for (int i = 0; i < k; i++) {
		in >> top[i].nume >> top[i].scor;
		int r = strlen(top[i].nume);
		if (r > maxim)
			maxim = r;
	}
	sort();
	for (i = 1; i < width; i++)
		cout << '-';
	cout << '\n';
	cout << "|       <Name>                <Score>           |" << '\n';
	for (i = 1; i < width; i++)
		cout << '-';
	cout << '\n';

	for (int i = 0; i < 10 && top[i].scor; i++) {
		cout << "       " << i+1 << '.' << top[i].nume;
		int r = strlen(top[i].nume);
		for (int j = 1; j <= maxim - r; j++)
			cout << ' ';
		cout << "                 " << top[i].scor - 1;
		cout << '\n';
	}
}

int main() {

	int x;
	Start();
	cout << '\n';
	cin >> x;
	if (x == 1)
	{
		surround();
		make_snake();
		make_pizza();
		for (ever) {
			draw_snake();
			print();
			input();
			system_clear();
			if (game_over == 1) {
				cout << "<Score: " << snake_l - 1 << " >" << '\n';
				cout << "GAME OVER!" << '\n';
				Top_10();
				break;
			}
			snake_clear();
		}
	}
	else if(x == 2){
		Afis_Top_10();
	}
	return 0;
}
