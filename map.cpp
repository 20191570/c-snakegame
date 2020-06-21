#include <ncurses.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

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
  {1,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2},
};
WINDOW *create_newwin(int height, int width, int starty, int startx);
void set_snake(int &headDirection);
void map_reset(int map_arr[21][21], int &gate1, int &gate2);
int headDirectionWeight[5][2] = {
  {0, 0},
  {-1, 0},
  {1, 0},
  {0, -1},
  {0, 1}
};

int moveSnakeHead(int &current_x, int &current_y, int headDirection, int map_arr[21][21]){
  int preX = current_x + headDirectionWeight[headDirection][0];
  int preY = current_y + headDirectionWeight[headDirection][1];

  map_arr[current_x][current_y] = 0;
  current_x = preX;
  current_y = preY;
  if(map_arr[current_x][current_y] == 1 || map_arr[current_x][current_y] == 6) return -1;
  else if(map_arr[current_x][current_y] == 7){
    for(int i = 0;i<21;i++){
      for(int j = 0;j<21;j++){
        if(map_arr[i][j] == 8){
          if(i == 0){
            map_arr[i+1][j] = 3;
            preX = i+1;
            preY = j;
            current_x = preX;
            current_y = preY;
            return 0;
          }
          else if(i == 20){
            map_arr[i-1][j] = 3;
            preX = i-1;
            preY = j;
            current_x = preX;
            current_y = preY;
            return 0;
          }
          else if(j == 0){
            map_arr[i][j+1] = 3;
            preX = i;
            preY = j+1;
            current_x = preX;
            current_y = preY;
            return 0;
          }
          else if(j == 20){
            map_arr[i][j-1] = 3;
            preX = i;
            preY = j-1;
            current_x = preX;
            current_y = preY;
            return 0;
          }
        }
      }
    }
  }
  else if(map_arr[current_x][current_y] == 8){
    for(int i = 0;i<21;i++){
      for(int j = 0;j<21;j++){
        if(map_arr[i][j] == 7){
          if(i == 0){
            map_arr[i+1][j] = 3;
            preX = i+1;
            preY = j;
            current_x = preX;
            current_y = preY;
            return 0;
          }
          else if(i == 20){
            map_arr[i-1][j] = 3;
            preX = i-1;
            preY = j;
            current_x = preX;
            current_y = preY;
            return 0;
          }
          else if(j == 0){
            map_arr[i][j+1] = 3;
            preX = i;
            preY = j+1;
            current_x = preX;
            current_y = preY;
            return 0;
          }
          else if(j == 20){
            map_arr[i][j-1] = 3;
            preX = i;
            preY = j-1;
            current_x = preX;
            current_y = preY;
            return 0;
          }
        }
      }
    }
  }
  else{
    map_arr[current_x][current_y] = 3;
    return 0;
  }

}

int main(){
  srand((unsigned int)time(NULL));
  WINDOW *my_win;
  WINDOW *my_win2;
  int height = 7;
  int width = 25;
  int starty = 2;
  int startx = 48;
  int starty2 = 10;
  int startx2 = 48;
  int headDirection = 0;
  int current_x = 9;
  int current_y = 9;
  int gate1;
  int gate2;
  while(true){
    gate1 = rand()%76;
    gate2 = rand()%76;
    if(gate1 != gate2) break;
  }
  setlocale(LC_ALL, "");
  initscr();
  keypad(stdscr, TRUE);
  noecho();
  curs_set(FALSE);
  map_reset(map_arr, gate1, gate2);
  refresh();
  while(1){
    set_snake(headDirection);
    int ans = moveSnakeHead(current_x, current_y, headDirection, map_arr);
    map_reset(map_arr, gate1, gate2);
    refresh();
    if (ans == -1) break;
    if(getch() == 'q') break;
  }
  my_win = create_newwin(height, width, starty, startx);
  my_win2 = create_newwin(height, width, starty2, startx2);

  refresh();
  getch();
  endwin();
  return 0;
}
void map_reset(int map_arr[21][21], int &gate1, int &gate2){
  int cnt = 0;
  for(int i = 0;i<21;i++){
    for(int j = 0;j<21;j++){

      if(map_arr[i][j] == 2){
        mvprintw(i,j,"\u2B1B");
      }
      else if(map_arr[i][j] == 1 || map_arr[i][j] == 7 || map_arr[i][j] == 8){
        if(cnt == gate1){
          mvprintw(i,j,"\u2B55");
          map_arr[i][j] = 7;
        }
        else if(cnt == gate2){
          mvprintw(i,j,"\u2B55");
          map_arr[i][j] = 8;
        }
        else mvprintw(i,j,"\u2B1C");
        cnt++;
      }
      else if(map_arr[i][j] == 0){
        mvprintw(i,j,"\u3000");
      }
      else if(map_arr[i][j] == 3){
        mvprintw(i,j,"\u2B50");
      }
      else if(map_arr[i][j] == 4){
        mvprintw(i,j,"\u26D4");
      }
      else if(map_arr[i][j] == 5){
        mvprintw(i,j,"\u264D");
      }
      else if(map_arr[i][j] == 6){
        mvprintw(i,j,"\u2651");
      }
    }
  }
}

void set_snake(int &headDirection){
  int input = getch();
  clear();
  switch(input){
      case KEY_UP:
        headDirection = 1;
        break;
      case KEY_DOWN:
        headDirection = 2;
        break;
      case KEY_LEFT:
        headDirection = 3;
        break;
      case KEY_RIGHT:
        headDirection = 4;
        break;
  }

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
