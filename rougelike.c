
#include <ncurses.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>


int screenSetUp();
int mapSetUp();


typedef struct Player {
  int xPosition;
  int yPosition;
  int health;
} Player;

typedef struct Room {
  int xPosition;
  int yPosition;
  Monster ** monsters;
  Item ** items;
} Room;


Player * playerSetUp();
int handleInput(int input, Player* user);
int checkPosition(int newY,int newX,Player * user);
int playerMove(int y, int x, Player* user);


int main() {

    int ch;
    Player * user;
    user = playerSetUp();

    screenSetUp();
    mapSetUp();
    playerSetUp();

    while ((ch = getch()) != 'q')
    {
      handleInput(ch,user);

    }

    endwin();
    return 0;
}

int screenSetUp()
{
  initscr();
  noecho();
  refresh();

  return 1;
}

int mapSetUp()
{

mvprintw(13,13, "--------");
mvprintw(14,13, "|......|");
mvprintw(15,13, "|......|");
mvprintw(16,13, "|......|");
mvprintw(17,13, "--------");

mvprintw(13,40, "--------");
mvprintw(14,40, "|......|");
mvprintw(15,40, "|......|");
mvprintw(16,40, "|......|");
mvprintw(17,40, "|......|");
mvprintw(18,40, "|......|");
mvprintw(19,40, "--------");

mvprintw(5,50, "-----------");
mvprintw(6,50, "|.........|");
mvprintw(7,50, "|.........|");
mvprintw(8,50, "|.........|");
mvprintw(9,50, "-----------");
}


Player* playerSetUp()
{
  Player * newPlayer;
  newPlayer = malloc(sizeof(Player));
  newPlayer->xPosition = 14;
  newPlayer->yPosition = 14;
  newPlayer->health = 20;


  mvprintw(newPlayer->yPosition, newPlayer->xPosition, "@");
  move(newPlayer->yPosition, newPlayer->xPosition);
  return newPlayer;
}

int handleInput(int input, Player* user)
{
  int newX, newY;
  int tempInput = tolower(input);
  switch(tempInput)
  {
    case 'w':
      newX = user->xPosition;
      newY = user->yPosition -1;

    break;

    case 's':
    newX = user->xPosition;
    newY = user->yPosition +1;

    break;

    case 'a':
    newX = user->xPosition -1;
    newY = user->yPosition;

    break;

    case 'd':
    newX = user->xPosition+1;
    newY = user->yPosition;

    break;

    default:
    break;

  }
  checkPosition(newY,newX, user);

}


int checkPosition(int newY, int newX, Player* user)
{
  int space;
  switch(mvinch(newY, newX))
  {

    case '.':
      playerMove(newY,newX,user);
      break;

    default:
    move(user->yPosition, user->xPosition);
    break;
  }

}

int playerMove(int y, int x, Player* user)
{
  mvprintw(user->yPosition, user->xPosition, ".");
  user->yPosition = y;
  user->xPosition = x;
  mvprintw(user->yPosition, user->xPosition, "@");
  move(user->yPosition, user->xPosition);

}
