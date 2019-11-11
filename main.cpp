#include "head.h"






int main()
{
    SetConsoleTitle("SNAKE 0.5");
    HideCursor();
    char tab[SIZE][SIZE]= {(0,0)};
    int x = SIZE/2, y=SIZE/2 -1, x_fruit=-1, y_fruit=-1, count = 0;
    int length = START_LENGTH;
    int Xhistory[100000];
    int Yhistory[100000];
    int direction= UP;
    int super_fruit_count=0;
    int x_super_fruit=-1;
    int y_super_fruit=-1;
    int score=0;
    bool super_fruit_exists = false;
    bool fruit_exists = false;
    bool game=true;
    srand(time(NULL));
    main_menu();
    clean(tab);
    tab[x][y]='h';
    tab[x][y-1]='s';
    speed = 3;
    mode = BORDERLESS_MODE;
    while(game==true)
    {
        count++;
        tab[x][y]='h';
        Xhistory[count]=x;
        Yhistory[count]=y;
        for(int i=1; i<length; i++)
        {
            tab[Xhistory[count-i]][Yhistory[count-i]] = 's';
        }
        tab[Xhistory[count-length]][Yhistory[count-length]]='b';
        if(fruit_exists==false)
        {
            do
            {
                generate_fruit(&x_fruit,&y_fruit,&fruit_exists);
                if(fruit_check(x_fruit, y_fruit, Xhistory, Yhistory, length, count)==true)
                {
                    tab[x_fruit][y_fruit]='f';
                }
            }while(fruit_check(x_fruit, y_fruit, Xhistory, Yhistory, length, count)==false);
        }
        if(count-super_fruit_count==30)
        {
            super_fruit_count=count;
         do
            {
                generate_super_fruit(&x_super_fruit,&y_super_fruit);
                if(fruit_check(x_super_fruit, y_super_fruit, Xhistory, Yhistory, length, count)==true)
                {
                    tab[x_super_fruit][y_super_fruit]='+';
                }
            }while(fruit_check(x_super_fruit, y_super_fruit, Xhistory, Yhistory, length, count)==false);
        }
        if((count-super_fruit_count)>=20 && check_super_fruit_near(x,y,x_super_fruit,y_super_fruit)==false)
        {
            tab[x_super_fruit][y_super_fruit]='b';
            x_super_fruit=-1;
            y_super_fruit=-1;
        }
            gotoxy(0,0);
            write(tab, score);
            Kierunek_change(direction);
        if(direction == -1 || movement(x,y,direction)==false || colision(Xhistory,Yhistory,x,y,count,length)==true)
            {
                delete[] Xhistory;
                delete[] Yhistory;
                delete[] tab;
                x = SIZE/2;
                y = SIZE/2 -1;
                count = 0;
                length = 2;
                fruit_exists=false;
                x_fruit = -1;
                game_over(score);
                game=false;
                main();
            }

            if(x==x_fruit && y==y_fruit)
            {
                length+=1;
                score+=FRUIT_VALUE;
                fruit_exists=false;
            }
             if(x==x_super_fruit && y==y_super_fruit)
            {
                length+=1;
                score+=SUPER_FRUIT_VALUE;
                super_fruit_count=count;
            }
            sleep(250-(speed*50));
        }
    }
