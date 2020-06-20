#include <ncurses.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

WINDOW *create_newwin(int height, int width, int starty, int startx);

int main(){
  srand((unsigned int)time(NULL));
  int map_arr[21][21] = {
    {2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2},
  };
  WINDOW *my_win;
  WINDOW *my_win2;
  int height = 7;
  int width = 25;
  int starty = 2;
  int startx = 48;
  int starty2 = 10;
  int startx2 = 48;
  int gate1;
  int gate2;
  while(true){
    gate1 = rand()%76;
    gate2 = rand()%76;
    if(gate1 != gate2) break;
  }
  int cnt = 0;

  setlocale(LC_ALL, "");
  initscr();
  for(int i = 0;i<21;i++){
    for(int j = 0;j<21;j++){

      if(map_arr[i][j] == 2){
        mvprintw(i,j,"\u2B1B");
      }
      else if(map_arr[i][j] == 1){
        if(cnt == gate1) mvprintw(i,j,"\u2B55");
        else if(cnt == gate2) mvprintw(i,j,"\u2B55");
        else mvprintw(i,j,"\u2B1C");
        cnt++;
      }
      else if(map_arr[i][j] == 0){
        mvprintw(i,j,"\u3000");
      }
    }
  }

  refresh();
  my_win = create_newwin(height, width, starty, startx);
  my_win2 = create_newwin(height, width, starty2, startx2);
  getch();
  endwin();
  return 0;
}

WINDOW *create_newwin(int height, int width, int starty, int startx)
{
        WINDOW *local_win;
        local_win = newwin(height, width, starty, startx);
        box(local_win, 0 , 0);
        mvprintw(3,49,"Score Board");
        mvprintw(4,49,"B: ");
        mvprintw(5,49,"+: ");
        mvprintw(6,49,"-: ");
        mvprintw(7,49,"G: ");

        mvprintw(11,49,"Misson");
        mvprintw(12,49,"B: ");
        mvprintw(13,49,"+: ");
        mvprintw(14,49,"-: ");
        mvprintw(15,49,"G: ");
        wrefresh(local_win);
        return local_win;
}
