
#include <ncurses.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <time.h>

int screenSetUp();

  typedef struct Position{
    int x;
    int y;
    //TILE_TYPE tile;
  }Position;


  typedef struct Player {
    Position position;
    int xPosition;
    int yPosition;
    int health;
  } Player;

  typedef struct Room {
    Position position;
    Position door[4];
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


int main()
{
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
rooms[1] = createRoom(20,23,9,12);
drawRoom(rooms[1]);
rooms[2] = createRoom(40,10,6,20);
drawRoom(rooms[2]);
rooms[3] = createRoom(77,15,10,10);
drawRoom(rooms[3]);



return rooms;
}

//Room Functions - Also I'm starting to believe that maybe C wasn't the best language for this.
//I should've used Java


  Room * createRoom(int x, int y, int height, int width)
    {
      Room * newRoom;
      newRoom = malloc(sizeof(Room));

      newRoom->position.x = x;
      newRoom->position.y = y;
      newRoom->height = height;
      newRoom->width = width;

      srand(time(NULL));

      //Top door
      newRoom -> door[0].x = rand() % width;
      newRoom -> door[0].y = newRoom -> position.y;
      //bottom door
      newRoom -> door[0].x = rand() % width;
      newRoom -> door[0].y = newRoom->position.y + newRoom->height;



      return newRoom;
    }





  int drawRoom(Room * room)
    {
      int x, y;

      for(x = room->position.x; x< (room->position.x + room->width); x++)
      {
        mvprintw(room->position.y,x,"-");
        mvprintw((room->position.y + room->height), x, "-");
      }

      for (y = room->position.y + 1; y < room->position.y+ room->height; y++)
      {
        mvprintw(y,room->position.x, "|");
        mvprintw(y, room->position.x + room->width - 1, "|");
        for (x = room->position.x+1; x < room->position.x + room->width-1; x++)
        {
          mvprintw(y,x,".");
        }
      }
    }



Player* playerSetUp()
{
  Player * newPlayer;
  newPlayer = malloc(sizeof(Player));
  newPlayer->position.x = 14;
  newPlayer->position.y = 14;
  newPlayer->health = 20;


  mvprintw(newPlayer->position.y, newPlayer->position.x, "@");
  move(newPlayer->position.y, newPlayer->position.x);
  return newPlayer;
}

int handleInput(int input, Player* user)
{
  int newX, newY;
  int tempInput = tolower(input);
  switch(tempInput)
  {
    case 'w':
      newX = user->position.x;
      newY = user->position.y -1;

    break;

    case 's':
    newX = user->position.x;
    newY = user->position.y +1;

    break;

    case 'a':
    newX = user->position.x -1;
    newY = user->position.y;

    break;

    case 'd':
    newX = user->position.x+1;
    newY = user->position.y;

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

    case ' ':
    case '.':
      playerMove(newY,newX,user);
      break;

    default:
    move(user->position.y, user->position.x);
    break;
  }

}

int playerMove(int y, int x, Player* user)
{
  mvprintw(user->position.y, user->position.x, ".");
  user->position.y = y;
  user->position.x= x;
  mvprintw(user->position.y, user->position.x, "@");
  move(user->position.y, user->position.x);

}
