
#include <ncurses.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>


int screenSetUp();



typedef struct Player {
  int xPosition;
  int yPosition;
  int health;
} Player;

typedef struct Room {
  int xPosition;
  int yPosition;
  int height;
  int width;
  //Monster ** monsters;
  // Item ** items;
} Room;



Room ** mapSetUp();
Player * playerSetUp();
int handleInput(int input, Player* user);
int checkPosition(int newY,int newX,Player * user);
int playerMove(int y, int x, Player* user);
int drawRoom(Room * room);
Room * createRoom(int x, int y, int height, int width);


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

Room ** mapSetUp()
{

Room ** rooms;
rooms = malloc(sizeof(Room));

rooms[0] = createRoom(13,13,6,8);
drawRoom(rooms[0]);

return rooms;
}

//Room Functions - Also I'm starting to believe that maybe C wasn't the best language for this.
//I should've used Java
Room * createRoom(int x, int y, int height, int width)
{
Room * newRoom;
newRoom = malloc(sizeof(Room));

newRoom->xPosition = x;
newRoom->yPosition = y;
newRoom->height = height;
newRoom->width = width;

return newRoom;
}

int drawRoom(Room * room)
{
int x, y;

for(x = room->xPosition; x< (room->xPosition + room->width); x++)
{
  mvprintw(room->yPosition,x,"-");
  mvprintw((room->yPosition + room->height), x, "-");

}
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
