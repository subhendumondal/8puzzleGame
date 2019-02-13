#include<graphics.h>
#include<conio.h>
#include<dos.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void graphics_open()
{
     clrscr();
     int gd = DETECT, gm;
     initgraph(&gd,&gm,"");
}

void mksound()
{
    sound(600);
    delay(50);
    nosound();
}

void scoreupdate(int moves,char user[100])
{
    FILE *fs;

    fs = fopen("SCORE.TXT","a");

    if ( fs == NULL )
    {
	 puts("File can't be open");
	 exit(0);
    }
	fprintf(fs,"\n\n");
	fputs("Score:",fs);
	fprintf(fs,"\t %d\n",moves);
	fputs("User: ",fs);
	fputs(user,fs);

    outtextxy(100,430,"Score is update to SCORE.TXT file in same directory");
    fclose(fs);
}

void instractions(int moves,char name[200])
{

    char tempq[300];
    outtextxy(400,40,"Developed by SUBHENDU MONDAL");
    outtextxy(460,70,"INSTRACTIONS");
    outtextxy(400,100,"1.Use arrow key to move box.");
    outtextxy(400,120,"2.To Quit the Game Press ESC.");
    outtextxy(400,140,"3.Score will count by how ");
    outtextxy(416,160,"many moves you did as well");
    outtextxy(416,180,"as time is taken to");
    outtextxy(416,200,"complete the game.");

    sprintf(tempq,"%d",moves);
    outtextxy(400,240,"Total Moves:");
    outtextxy(500,240,tempq);
    outtextxy(400,280,"User: ");
    outtextxy(450,280,name);
}

int compare(int c[3][3])
{
    int i,j,flg=0,r,p,k=1;
    for( i = 0; i < 3; i++)
     {
	  for(j = 0; j < 3; j++)
	  {
	      if(c[i][j] == k)
	      {
		  flg = 1;
		  k++;
	      }
	      else
	      {
		   flg = 0;
		   break;
	      }
	  }
	  if( flg == 0 )
	  {
	      break;
	  }
     }

     return flg;
}
int check(int b[3][3],int n)
{
     int i,j,temp=1;
     for(i = 0; i < 3; i++)
     {
	 for( j = 0 ; b[i][j] != '\0' && j < 3; j++)
	 {
		if ( b[i][j] == '\0')
		{
		   temp = 1;
		}
		else if( b[i][j] != n)
		{
		   temp = 1;
		}
		else
		{
		    temp = 0;
		    break;
		}
	 }
	 if( temp == 0 )
	 {
	    break;
	 }
     }
     return temp;
}

int a[3][3];

int statecheck(int i,int j,int val,int a[3][3])
{
       int temp=0,temp2=0,k,l;

       for( k = i; k < 3; k++)
       {
	    for( l = j; l < 3; l++)
	    {
		if( a[k][l] != temp2 && val > a[k][l] )
		{
		    if(a[k][l] == 9)
		    {
			continue;
		    }
		    else
		    {
			temp++;
			temp2 = a[k][l];
		    }
		}
	    }
	    j=0;
       }
       return temp;
}

void matrix_creation()
{
   int i,j,temp,count,kl=1;
   srand ( time(NULL) );
   while(kl == 1)
   {
     for( i = 0; i < 3; i++)
     {
	  for(j = 0; j < 3; j++)
	  {
	      a[i][j] = 0;
	  }
     }
      for(i = 0; i < 3; i++)
      {
	  for( j = 0 ; j < 3 ; j++)
	  {
	       while(1)
	       {
			temp = rand() % 10 + 1;

			if(temp < 9 && temp > 0 && check(a,temp) == 1)
			{
			    if( i == 1 && j == 1)
			    {
				 a[i][j] = 9;
			    }
			    else
			    {
				 a[i][j] = temp;
			    }
			    break;
			}
	       }

	  }
      }// for end loop of matrix creation

      count = 0;
      kl = 1;

      for( i = 0; i < 3; i++)
      {
	  for(j = 0; j < 3; j++)
	  {
	      if( i != 0 && i == j)
	      {
		 continue;
	      }
	      else
	      {
		 count = count + statecheck(i,j,a[i][j],a);
	      }
	  }
       }
       if( count % 2 == 0)
       {
	    kl = 2;
       }
   }// end of master while;
}

void print_matrix()
{
      int i,j,x=12,y=7,temp;

      gotoxy(x,y);
      for(i = 0; i < 3; i++)
      {
	  for( j = 0 ; j < 3 ; j++)
	  {
	       if(a[i][j] == 9)
	       {
		   printf("");
	       }
	       else
	       {
		   printf("%d",a[i][j]);
	       }
	       x = x + 13;
	       gotoxy(x,y);
	  }
	  printf("\n");
	  y = y + 6;
	  x = 12;
	  gotoxy(x,y);
      }
}

void exchange(int x, int y,int i, int j)
{
      int temp;

      temp =  a[x][y];
      a[x][y]  = a[i][j];
      a[i][j] = temp;
}

void draw()
{
    {/* Drwaing the cube here*/

	 rectangle(50,50,150,150);
	 rectangle(50,150,150,250);
	 rectangle(50,250,150,350);
	 rectangle(150,50,250,150);
	 rectangle(150,150,250,250);
	 rectangle(150,250,250,350);
	 rectangle(250,50,350,150);
	 rectangle(250,150,350,250);
	 rectangle(250,250,350,350);
      }
}
void main()
{
      int left=151,top=151,right=249,bottom=249,ffx=160,ffy=160;
      int r=1,c=1,dr=1,dc=1;
      int moves = 0,b;
      char tempq[345];
      char name[200];

      clrscr();

      b=1;

      while( b== 1)
      {
	 printf("\n\n\t\t\t\t 8 PUZZEL GAME");
	 printf("\n\n\n\n\n\n\n\n\n\t\t\t");
	 printf("Enter Your Name : ");
	 gets(name);
	 clrscr();
	 if( strlen(name) == 0 )
	 {
	      printf("\n\n\t\t\t\t 8 PUZZEL GAME");
	      printf("\n\n\n\n\n\n\n\n\n\t\t");
	      printf(" Please Enter Your Name To Continue The game");
	      delay(2000);
	      clrscr();
	      gotoxy(0,0);
	 }
	 else
	 {
	      b = 2;
	 }
      }
      clrscr();

      graphics_open();
      matrix_creation();

	      draw();
	      setfillstyle(1,9);
	      rectangle(left+100,top+100,right+100,bottom+100);
	      floodfill(160,160,15);

	       instractions(moves,name);

	      print_matrix();
	      while(getch() != 27)
	      {
		   while(kbhit())
		   {
			switch(getch())
			{
			    case 72: if( top != 51)
				     {
					 mksound();
					 setfillstyle(1,0);
					 floodfill(ffx,ffy,15);
					 top = top - 100;
					 bottom = bottom - 100;
					 ffy = ffy - 100;
					 setfillstyle(1,9);
					 rectangle(left,top,right,bottom);
					 floodfill(ffx,ffy,15);
					 if( dr > 0 )
					 {
					     r = r - 1;
					     exchange(r,c,dr,dc);
					     dr = r;
					 }
				     }
				     break;
			    case 80: if( bottom != 349)
				     {
					 mksound();
					 setfillstyle(1,0);
					 floodfill(ffx,ffy,15);
					 top = top + 100;
					 bottom = bottom + 100;
					 ffy = ffy + 100;
					 setfillstyle(1,9);
					 rectangle(left,top,right,bottom);
					 floodfill(ffx,ffy,15);

					 if( dr < 2 )
					 {
					     r = r + 1;
					     exchange(r,c,dr,dc);
					     dr = r;
					 }
				     }
				     break;
			    case 75: if( left != 51)
				     {
					 mksound();
					 setfillstyle(1,0);
					 floodfill(ffx,ffy,15);
					 left = left - 100;
					 right = right - 100;
					 ffx = ffx - 100;
					 setfillstyle(1,9);
					 rectangle(left,top,right,bottom);
					 floodfill(ffx,ffy,15);

					 if( dc > 0 )
					 {
					     c = c - 1;
					     exchange(r,c,dr,dc);
					     dc = c;
					 }
				     }
				     break;
			    case 77: if( right != 349)
				     {
					 mksound();
					 setfillstyle(1,0);
					 floodfill(ffx,ffy,15);
					 left = left + 100;
					 right = right + 100;
					 ffx = ffx + 100;
					 setfillstyle(1,9);
					 rectangle(left,top,right,bottom);
					 floodfill(ffx,ffy,15);
					 if( dc < 2 )
					 {
					     c = c + 1;
					     exchange(r,c,dr,dc);
					     dc = c;
					 }
				     }
				     break;
			}
			moves++;
			cleardevice();
			draw();
			setfillstyle(1,9);
			rectangle(left,top,right,bottom);
			floodfill(ffx,ffy,15);

			 instractions(moves,name);

			print_matrix();

			if( compare(a) == 1)
			{
			    b = 1;
			    break;
			}
		   }
		   if( b == 1)
		   {
			break;
		   }
	      }
      if(b == 1)
      {
	   setcolor(RED);
	   outtextxy(400,300,"YOU WIN ! Thank You");
	   sprintf(tempq,"%d",moves);
	   outtextxy(400,330,"Score is:");
	   outtextxy(500,330,tempq);
	   outtextxy(250,400,"Press any key to exit");
	   scoreupdate(moves,name);
      }
      getch();
      closegraph();
}
