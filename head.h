#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <cstdlib>
#include <time.h>
#include <iostream>
#include <conio.h>
#include <fstream>
#include <string>
#include <string.h>
#include <stdlib.h>

using namespace std;

#define SIZE 20
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

#define FRUIT_VALUE 1
#define SUPER_FRUIT_VALUE 5
#define START_LENGTH 2

#define BOX_MODE 1
#define BORDERLESS_MODE 2

int speed;
int mode;

struct highscore_table{
int score;
string name;
};

void gotoxy(int x, int y)
{
    COORD cord;
    cord.X = x;
    cord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);
}

void HideCursor()
{
    ::HANDLE hConsoleOut =::GetStdHandle( STD_OUTPUT_HANDLE );
    ::CONSOLE_CURSOR_INFO hCCI;
    ::GetConsoleCursorInfo( hConsoleOut, & hCCI );
    hCCI.bVisible = FALSE;
    ::SetConsoleCursorInfo( hConsoleOut, & hCCI );
}

void ShowCursor()
{
    ::HANDLE hConsoleOut =::GetStdHandle( STD_OUTPUT_HANDLE );
    ::CONSOLE_CURSOR_INFO hCCI;
    ::GetConsoleCursorInfo( hConsoleOut, & hCCI );
    if( hCCI.bVisible != TRUE )
    {
        hCCI.bVisible = TRUE;
        ::SetConsoleCursorInfo( hConsoleOut, & hCCI );
    }
}

void write_border(int Xstart, int Ystart, int length, int height)
{
    for(int i=0; i<length+1; i++)
    {
        gotoxy(Xstart+i,Ystart);
        cout << "-";
        gotoxy(Xstart+i,Ystart+height-1);
        cout << "-";
    }
    for(int i=0; i<height-2; i++)
    {
        gotoxy(Xstart,Ystart+i+1);
        cout << "|";
        gotoxy(Xstart+length,Ystart+i+1);
        cout << "|";
    }
}

void sleep(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock());
}

int count_lines(string nazwa)
{
	string line;
	int lines = 0;
	fstream plik;
	plik.open(nazwa);
	while (getline(plik, line)) lines++;
	plik.close();
	return lines;
}

void write_highscore(highscore_table table[], int lines)
{
    int limit;
    if(lines>10) limit = 10;
    else limit = lines;
    write_border(0,0,40,12);
    cout<<endl;
    for(int i=0; i<limit; i++)
        {
            gotoxy(1,i+1);
            if(i<9)
            {
                cout << i+1 <<".  " << table[i].score;
                if(table[i].score<10)cout<< "      ";
                else if(table[i].score<100)cout<< "     ";
                else if(table[i].score>999)cout<< "   ";
                else if(table[i].score>99)cout<< "    ";
                cout << table[i].name << endl;
            }
            else if(i==9)
            {
                cout << i+1 <<". " << table[i].score;
                if(table[i].score<10)cout<< "      ";
                else if(table[i].score<100)cout<< "     ";
                else if(table[i].score>999)cout<< "   ";
                else if(table[i].score>99)cout<< "    ";
                cout<< table[i].name << endl;
             }
        }
        gotoxy(3,13);
        delete[] table;
        system("PAUSE");
}

void load_and_write(string filename)
{
	int lines = count_lines(filename);
	int name_length = 0;
	string hashstring;
	string hashname;
	system("cls");
	highscore_table* table = { 0 };
	table = new (nothrow) highscore_table[lines];
	fstream highscore;
	highscore.open(filename);
	int skip;
	for (int i = 0; i < lines; i++)
	{
        skip = 0;
        hashname.clear();
        highscore >> name_length;
		highscore >> hashstring;
		highscore >> table[i].score;
		table[i].score /= 13;
		while(name_length>0)
		{
			hashname.push_back(hashstring[skip]);
			skip += ((int)hashstring[skip] - 60 + 1);
			name_length--;
		}
		table[i].name = hashname;
	}
	highscore.close();

	int b = 0;
	for (int i = 0; i < lines; i++)
	{
		for (int j = 0; j < (lines - b); j++)
		{
			if (table[j].score < table[j + 1].score)
			{
				swap(table[j], table[j + 1]);
			}
		}
		b++;
	}
	write_highscore(table, lines);
}

void main_menu()
{
    system("cls");
    write_border(10,0,10,3);
    gotoxy(11,1);
    printf("MAIN MENU\n\n\n");
    write_border(0,2,30,6);
    gotoxy(10,3);
    printf("1. NEW GAME\n");
    gotoxy(10,4);
    printf("2. OPTIONS\n");
    gotoxy(10,5);
    printf("3. HIGHSCORE\n");
    gotoxy(10,6);
    printf("ESC. EXIT\n");
    gotoxy(0,8);
    cout << "Copyright, Grzegorz Gojska 2018";

    char sign=getch();

    switch(sign)
    {
    case '1':
    {
        system("cls");
        printf("Wait\n");
        system("cls");
        cout << "\n\n\n          .";
        sleep(260);
        system("cls");
        cout << "\n\n\n          ..";
        sleep(260);
        system("cls");
        cout << "\n\n\n          ...";
        sleep(260);
        system("cls");
        cout << "\n\n\n          ....";
        sleep(260);
        system("cls");
        break;
    }

    case '2':
    {
        system("cls");
        cout << "1. GAME SPEED \n";
        cout << "2. MODE\n\n";
        cout << "3. MAIN MENU\n\n";
        char options = getch();
        switch(options)
        {
        case '1':
        {
            system("cls");
            int speed;
            cout <<"Please choose speed from 1 to 4.";
            cin >> speed;
            if (speed < 1)
            {
                speed = 1;
            }
            else if(speed >4)
            {
                speed = 4;
            }
            fstream config;
            config.open("config.txt",ios::out);
            config<<speed;
            config.close();
            main_menu();
        }
        break;
        case '2':
        {
            cout << "1 - With borders \n 2 - Borderless \n\n";
            cin >> mode;
            if(mode<1)
                mode = 1;
            else if(mode > 2)
                mode = 2;
            main_menu();
            break;
        }
        case '3':
            main_menu();
            break;
        }
        system("pause");
        break;
    }

    case '3':
        {
        load_and_write("highscore.txt");
        main_menu();
        break;
        }
    case 27:
        {
        system("cls");
        printf("\n\n\n         BYE \n\n\n\n");
        exit(0);
        break;
        }
    default:
        {
        main_menu();
        break;
        }
    }
}

void clean(char tab[SIZE][SIZE])
{
    for(int i=0; i<SIZE; i++)
    {
        for(int j=0; j<SIZE; j++)
            tab[j][i]='b';
    }
}

void write(char tab[][SIZE],int score)
{
    for(int k=0; k<=SIZE; k++)
    {
        printf("--");
    }
    printf("\n");
    for(int i=0; i<SIZE; i++)
    {
        printf("|");
        for(int j=0; j<SIZE; j++)
        {
            if (tab[j][i]=='b')
                printf("  ");
            if (tab[j][i]=='h')
                printf("O ");
            if (tab[j][i]=='f')
                printf("@ ");
            if (tab[j][i]=='s')
                printf("o ");
            if (tab[j][i]=='+')
                printf("# ");
        }
        printf("|\n");
    }
    for(int k=0; k<=SIZE; k++)
    {
        printf("--");
    }
    write_border(SIZE+24,0,20,5);
    gotoxy(SIZE+25,1);
    printf("SCORE: %i \n",score);
    gotoxy(SIZE+25,2);
    cout << "Game speed = " << speed;
    gotoxy(SIZE+25,3);
    if(mode==2)
        cout << "MODE = Borderless";
    if(mode==1)
        cout << "MODE = Box";
    write_border(SIZE+24,5,14,8);
    gotoxy(SIZE+25,6);
    cout<< "Instruction:";
    gotoxy(SIZE+25,7);
    cout<< "w - > UP";
    gotoxy(SIZE+25,8);
    cout<< "s - > DOWN";
    gotoxy(SIZE+25,9);
    cout<< "a - > LEFT";
    gotoxy(SIZE+25,10);
    cout<< "d - > RIGHT";
    gotoxy(SIZE+25,11);
    cout<< "ESC - > EXIT";
    write_border(SIZE+24,12,15,4);
    gotoxy(SIZE+25,13);
    cout<< "@ -> 1 point";
    gotoxy(SIZE+25,14);
    cout<< "# -> 5 points";
    gotoxy(0,SIZE+2);
    cout << "Copyright, Grzegorz Gojska 2018";
}

bool fruit_check(int x_fruit, int y_fruit, int Xhistory[], int Yhistory[], int length, int count)
{
    int check=0;
        for(int i=0;i<length;i++)
        {
            if(x_fruit == Xhistory[count - i] && y_fruit == Yhistory[count - i])
            {
                check+=1;
            }
        }
        if(check==0)
        {
            return true;
        }
    return false;
}

void generate_fruit(int *x_fruit, int *y_fruit, bool *fruit_exists)
{
            *x_fruit=rand()%SIZE;
            *y_fruit=rand()%SIZE;
            *fruit_exists=true;
}

void generate_super_fruit(int *x_super_fruit, int *y_super_fruit)
{
            *x_super_fruit=rand()%SIZE;
            *y_super_fruit=rand()%SIZE;
}

bool check_super_fruit_near(int x,int y,int x_super_fruit,int y_super_fruit)
{
    if(abs(x-x_super_fruit)<2 && abs(y-y_super_fruit)<2)
    {
        return true;
    }
    else
        {
    return false;
    }
}

void save(int score, string filename, string nickname)
{
	srand(time(NULL));
	fstream highscore;
	highscore.open(filename, ios::app);
	highscore << nickname.length();
	highscore << " ";
	for (int i = 0; i < nickname.length(); i++)
	{
		int liczba = (int)(nickname[i]) - 60;
		highscore << nickname[i];
		for (int j = 0; j < liczba; j++)
		{
			int znak = rand()%92 + 33;
			highscore << (char)znak;
		}
	}
	highscore << " " << score*13 << "\n";
	highscore.close();
}

void game_over(int score)
{
    int a;
    system("cls");
    cout << endl << endl << endl << "          GAME OVER \n    DO YOU WANT TO SAVE SCORE?\n          1.Yes\n          2.No" << endl << endl << endl;
    do
    {
    a = getch();
    if(a=='1' || a=='2')break;
    }while(1);
    if(a=='2');
    else if(a=='1')
    {
            system("cls");
            string name;
            cout<<"SCORE =  " << score <<endl;
            cout<<"Write your nickname: \n";
            cin>>name;
            save(score,"highscore.txt", name);
    }
}

bool colision(int Xhistory[], int Yhistory[], int x, int y, int count, int length)
{
    for(int i=1; i<length; i++)
    {
        if(x==Xhistory[count-i] && y==Yhistory[count-i])
        {
            return true;
        }
    }
    return false;
}

void Kierunek_change(int &Kierunek)
{
    if(kbhit()==true)
    {
        Kierunek = getch();
        if(Kierunek == '\033' || Kierunek == 224)
        {
           Kierunek=getch();
        }
        switch(Kierunek)
        {
        case 'w':
        case UP:
            if(Kierunek!=DOWN)
                Kierunek = UP;
            break;
        case 's':
        case DOWN:
            if(Kierunek!=UP)
                Kierunek = DOWN;
            break;
        case 'a':
        case LEFT:
            if(Kierunek!=RIGHT)
                Kierunek = LEFT;
            break;
        case 'd':
            case RIGHT:
            if(Kierunek!=LEFT)
                Kierunek = RIGHT;
            break;
        case 27:
            Kierunek=-1;
            break;
        default:
            break;

        }
    }
}

bool movement(int & x, int & y, int Kierunek)
{
    switch(Kierunek)  //movement
        {
        case UP:
            if(y==0)
            {
                if(mode==2)
                {
                    y=SIZE;
                }
                else
                {
                    return false;
                }
            }
            y--;
            return true;
            break;
        case DOWN:
            if(y==SIZE-1)
            {
                if(mode==2)
                {
                    y=-1;
                }
                else
                {
                    return false;
                }
            }
            y++;
            return true;
            break;
        case LEFT:
            if(x==0)
            {
                if(mode==2)
                {
                    x=SIZE;
                }
                else
                {
                    return false;
                }
            }
            x--;
            return true;
            break;
        case RIGHT:
            if(x==SIZE-1)
            {
                if(mode==2)
                {
                    x=-1;
                }
                else
                {
                    return false;
                }
            }
            x++;
            return true;
            break;
        }
}

