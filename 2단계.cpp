#include <ncurses.h>
#include <unistd.h>
#include <iostream>

int headDirectionWeight[5][2] = {
  {0, 0},
  {0,-1},
  {0, 1},
  {-1, 0},
  {1, 0}
};
int currentHeadDirection = 0;
int current_x = 10;
int current_y = 10;
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
  {1,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,1},
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

void screen_set(){
  for(int i = 0;i<21;i++){
    for(int j = 0;j<21;j++){
      if(map_arr[i][j] == 2 or map_arr[i][j] == 3){
        mvprintw(i,j,"\u2B1B");
      }
      else if(map_arr[i][j] == 1){
        mvprintw(i,j,"\u2B1C");
      }
      else{
        mvprintw(i,j," ");
      }
    }
  }
}
int set_snake(){
  if(getch() == KEY_UP){
    return 1;
  }
  else if(getch() == KEY_DOWN){
    return 2;
  }
  else if(getch() == KEY_LEFT){
    return 3;
  }
  else if(getch() == KEY_RIGHT){
    return 4;
  }
}
void moveSnakeHead(int &current_x, int &current_y, int headDirection){
  int preX = current_x + headDirectionWeight[headDirection][0];
  int preY = current_y + headDirectionWeight[headDirection][1];
  map_arr[current_x][current_y] = 0;
  current_x = preX;
  current_y = preY;
  map_arr[current_x][current_y] = 3;
}
int main(){
  setlocale(LC_ALL, "");
  initscr();
  keypad(stdscr, TRUE);
  curs_set(0);
  noecho();
  screen_set();
  int key;
  while(true){
    currentHeadDirection = set_snake();
    moveSnakeHead(current_x, current_y, currentHeadDirection);
    screen_set();
    refresh();
    usleep(500);
  }
  getch();
  endwin();
  return 0;
}
