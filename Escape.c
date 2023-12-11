/*
  Name: Yuvraj Saini
  Date: 20/04/2021
  Purpose: This is a text based adventure game which also includes visual aids like a map. It is space themed and your main goal is to get
  three keys in various locations of the ship you are on. You are also meant to find the location on the ship that contains the escape pods.
  Once all keys are obtained you are allowed to escape and the game has been completed. However escape isn't guaranteed because there are
  certain scenarios you will encounter which will require you to make a choice that can cause you to die and lose the game.
*/

//Includes all necessary libraries required by this program.
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <curses.h>

//Function prototypes for the map, key data and the rooms
char keydata(void);
char map(void);
char records(void);
char cafeteria(void);
char cargobay(void);
char armory(void);
char storagetwo(void);
char lounge(void);

int key = 0;                //Stores the amount of keys you have
int keycountertwo = 0;      //Counter that prevents you from getting key two twice
int keycounterthree = 0;    //Counter that prevents you from getting key one twice
char movechoice = 0;        //Stores the character that determines you direction of travel
char crewchoice = 0;        //Stores your choice descision in the scenario with the injured crewmember
char gunchoice = 0;         //Stores your choice descision in the scenario about attacking the enemy ship
int injured = 0;            //Determines if you saved the crewmember
int crowbar = 0;            //Determines if you have gotten the crowbar

int main(void)
{
  initscr();				//Initializes curses library
  cbreak();					//Will take input chars one at a time
  timeout(1);				//Waits 1ms for keypress,otherwise continues
  noecho();        	//Makes it so the input is not echo-ed

  int counter = 0;
  int countertwo = 0;
  int keycounterone = 0;

  while(1)      //Waits for user to chose where they want to go from communications which is the starting room
  {
    movechoice = getch();     //Gets the direction of travel from the user
    if (counter == 0)         //Only allows the clear to run once everytime you visit communications
    {
      clear();
      if (countertwo == 0)    //Only allows the instructions and introduction to print once in the beginning game
      {
        printw("Welcome to Space Escape.\n");
        printw("Press w,a,s,d to move from room to room.\n");
        printw(" W = north\n A = west\n S = south\n D = east\n");
        printw("\nYour aboard a battle ship the UNN Athens on a routine fly around the inner planets on your way back to earth.\n"
        "Your a journalist given special access into the life of a UNN soldier. Its been a uneventful journey so far.\n"
        "That is up until the last 10 minutes. You were headed to the lower deck when a ubrupt explosion rocks the ship.\n"
        "You were thrown against the wall but aren't hurt. You head to the communications room of the lower deck and assess the damage.\n"
        "A message from the ships automated system tells you that the ship has suffered a torpedo hit from an enemy ship.\n"
        "The lower deck hasn't been hit and is stable for now. All access to above levels has been blocked due to safety protocols.\n"
        "Each level has escape pods, you have to find the ones on this floor.\n"
        "Access to the pods will require 3 keys allocated to 3 crewmembers on this floor. Find them and the pods to escape.\n");
        countertwo ++;
      }
      map();        //Prints map
      printw("\nYou are in communications (COM on map). Travel in all 4 directions is possible.\n");
      keydata();    //Prints number of keys required and obtained
      refresh();    //Updates screen
      counter ++;
    }

    if (movechoice == 'w')      //If user presses w, they are moved north into electrial and information on that room is displayed
    {
      clear();
      map();
      printw("\nYou've entered electrial (E on map).\n");
      printw("Press q to investigate the room.\n");
      keydata();
      refresh();
      while(1)      //Waits for user to either move or investigate the room
      {
        movechoice = getch();       //Gets the direction of travel or the request to investigate room from user
        if (movechoice == 'q')      //If user presses q, a description of the room and the absence of a key is displayed
        {
          printw("\nThere is no key or person in this room. Electrical wires from the roof have been dislocated\n"
          "during the exlposion and are dangling down. You carefully make your way aroud them avoiding the sparks.");
          refresh();
        }
        if (movechoice == 'w')      //If user presses w, they are moved north into cargo bay
        {
          cargobay();
        }
        if (movechoice == 's')      //if user presses s, they are moved south into communications
        {
          movechoice = 0;           //movechoice is reset to be used again later
          counter --;               //Counter is lowered by 1 to allow the information in communications to be displayed again
          break;                    //Breaks out of the loop allowing you to leave the current room
        }
      }
    }

    if (movechoice == 'a')      //If user presses a, they are moved west into viewing deck and the info on that room is displayed
    {
      clear();
      map();
      printw("\nYou've entered the viewing deck (V on map).\n");
      printw("Press q to investigate the room.\n");
      keydata();
      refresh();
      while(1)      //Waits for user to either move or investigate the room
      {
        movechoice = getch();       //Gets the direction of travel or the request to investigate room from user
        if (movechoice == 'q')      //If user presses q, a description of the room and the absence of a key is displayed
        {
          printw("\nThere is a window in this room and you decide to have look outside.\n"
          "You see what must be the enemy ship that fired on you. It's guns are still pointed in this direction.\n"
          "You scream at the ship in anger knowing that it will do nothing. There is no on else in this room and no key.");
          refresh();
        }
        if (movechoice == 'w')      //if user presses w, they are moved north into storage room two
        {
          storagetwo();
        }
        if (movechoice == 's')      //if user presses s, they are moved south into armory
        {
          armory();
        }
        if (movechoice == 'd')      //if user presses d, they are moved east into communications
        {
          movechoice = 0;
          counter --;
          break;
        }
      }
    }

    if (movechoice == 's')      //if user presses s, they are moved south into storage room one and the info on that room is displayed
    {
      clear();
      map();
      printw("\nYou've entered storage room 1 (ST1 on map).\n");
      printw("Press q to investigate the room.\n");
      keydata();
      refresh();
      while(1)       //Waits for user to either move or investigate the room
      {
        movechoice = getch();       //Gets the direction of travel or the request to investigate room from user
        if (movechoice == 'q')      //If user presses q, they are given info on the room based on the conditions below
        {
          if (keycounterone == 0)     //Runs if the user hasn't gotten the key from this room yet
          {
            if (crowbar == 1)         //If the user has gotten the crowbar, a description of the room and a message telling you have obtained a key is displayed
            {
              key ++;                 //Your obtained keys increases by 1
              keycounterone ++;       //Prevents this from being run again
              printw("\nYou walk into the storage room and near the back you find a door. It doesn't budge.\n"
              "You decide to use the crowbar that you found in the lounge and jam it into the side. After much effort, the door jerks free.\n"
              "You walk in to find the body of a crewmember lying on the ground. You check for a pulse but it isn't there.\n"
              "They seem to have suffered fatal head trauma during the blast. You take the key form their belt and carry on.\n");
              keydata();
              refresh();
            }
            else        //If the user hasn't gotten the crowbar, a description of the room is given and they are told to return with the crowbar
            {
              printw("\nYou walk into a storage room. At first it seems like there is nothing here until you move closer to the back.\n"
              "There's another door but when you attempt to open it, it doesn't budge. There must be a tool somewhere on this ship that might help get this door open.\n");
              refresh();
            }
          }
          else      //If the user has already gotten the key from this room a message telling them this is displayed
          {
            printw("\nThe crewmember is still there just as you left them. You already have their key.\n");
          }
        }
        if (movechoice == 'w')      //If the user presses w, they are moved north into communications
        {
          movechoice = 0;
          counter --;
          break;
        }
      }
    }

    if (movechoice == 'd')      //If the user presses d, they are moved east into engine room and the info on that room is displayed
    {
      clear();
      map();
      printw("\nYou've entered the engine room (ER on map).\n");
      printw("Press q to investigate the room.\n");
      keydata();
      refresh();
      while(1)      //Waits for user to either move or investigate the room
      {
        movechoice = getch();      //Gets the direction of travel or the request to investigate room from user
        if (movechoice == 'q')     //If user presses q, a description of the room and the absence of a key is displayed
        {
          printw("\nYou walk into the room, it seems to be intact with no key or person around.\n");
          refresh();
        }
        if (movechoice == 'd')     //If the uer presses d, they are moved east into cafeteria
        {
          cafeteria();
        }
        if (movechoice == 'a')     //If the user presses a, they are moved east into communications
        {
          movechoice = 0;
          counter --;
          break;
        }
      }
    }
  }
}

char keydata(void)      //Displays the amount of keys obtained and required by the user
{
  mvprintw(0, 53, "Keys obtained: %i", key);
  mvprintw(1, 53, "Keys required: 3");
  move(18, 0);          //Moves the cursor under the map
  curs_set(0);          //Removes the cursor from the screen
}

char map(void)      //Displays a map of the lower deck of the ship you are on
{
  printw("                    _______                                       \n");
  printw("                   |       |                                      \n");
  printw("                   |   C   |                                      \n");
  printw("                   |__   __|                                      \n");
  printw("        _______     __| |__                  _______              \n");
  printw("       |       |   |       |                |       |             \n");
  printw("       |  ST2  |   |   E   |                |   R   |             \n");
  printw("       |__   __|   |__   __|                |__   __|             \n");
  printw("        __| |__     __| |__      _______     __| |__     _______  \n");
  printw("       |       |___|       |____|       |___|       |___|       | \n");
  printw("       |   V    ___   COM   ____    ER   ___   CAF   ___    L   | \n");
  printw("       |__   __|   |__   __|    |_______|   |_______|   |_______| \n");
  printw("        __| |__     __| |__                                       \n");
  printw("       |       |   |       |                                      \n");
  printw("       |   A   |   |  ST1  |                                      \n");
  printw("       |_______|   |_______|                                      \n");
}

char storagetwo(void)      //Dislpays the information for storage room two
{
  clear();
  map();
  printw("\nYou've entered storage room 2 (ST2 on map).\n");
  printw("Press q to investigate the room.\n");
  keydata();
  refresh();
  while(1)      //Waits for user to either move or investigate the room
  {
    movechoice = getch();       //Gets the direction of travel or the request to investigate room from user
    if (movechoice == 'q')      //If the user presses q, a message is displayed depending on if the user has already gotten this key or not
    {
      if (keycounterthree == 0)     //If the user hasn't gotten the key from this room yet, a description of the room and a message telling them they have got the key is displayed
      {
        keycounterthree ++;         //Prevents this from being run again
        key ++;                     //Your obtained keys increases by 1
        printw("\nYou walk into a storage room containing mostly food supplies. A crewmember is laying there dead.\n"
        "They seem to have suffered a fatal shock. You see an electrial panel open with exposed wires and a toolbox strapped to the wall.\n"
        "You conclude that this person was likely working on electrial repairs when the torpedo hit. You take their key and move on.");
        keydata();
        refresh();
      }
      else        //If the user has gotten this key already, a message saying so is displayed
      {
        printw("\nYou walk in and stare at the food crates as your stomach grumbles. You realize you've already got the key from this room.\n");
      }
    }
    if (movechoice == 's')      //If the user presses s, they are moved south to the viewing deck
    {
      clear();
      map();
      printw("\nYou've entered the viewing deck (V on map).\n");
      printw("Press q to investigate the room.\n");
      keydata();
      refresh();
      movechoice = 0;
      break;
    }
  }
}

char armory(void)     //Displays the information for the armory
{
  clear();
  map();
  printw("\nYou've entered the armory (A on map).\n");
  printw("Press q to investigate the room.\n");
  keydata();
  refresh();
  while(1)      //Waits for user to either move or investigate the room
  {
    movechoice = getch();      //Gets the direction of travel or the request to investigate room from user
    if (movechoice == 'q')     //If the user presses q, a scenario and the absense of a key is displayed
    {
      //A scenario is displayed to the user asking if they would choose to attack the enemy ship
      printw("\nThere is no key or person in this room. However, there is a rail gun station.\n"
      "You can see the enemy ship off to the distance and it is in range according to the radar display.\n"
      "You don't know how to operate the gun but it seems very straightforward.\n"
      "Do you A) attempt to fire the weapon or B) Squash your anger and focus on saving yourself.\n");
      printw("Answer with the letter a or b.");
      refresh();
      scanf("%c", &gunchoice);      //Gets the user's choice on the scenario
      if (gunchoice == 'a')         //If the user presses a, they lose the game and a message saying so is displayed
      {
        mvprintw(25, 0, "Out of anger you decide to attack the cruiser. You use the digital panel next to the gun and manage to aim it at the ship.\n"
        "You press fire sending a high velocity tungsten round on its way. In response, the ship fires multiple torpedos\n"
        "that break apart your tungsten round into harmless pieces that are absorbed by the ships plasma sheild.\n"
        "Now aware of your presence the enemy cruiser fires a volley of torpedos at your location. Theres nothing you can do\n"
        "but watch as everything around you is disintegrated. You died.");
        printw(" Restart the game.");
        refresh();
        sleep(20);      //Gives user time to read the message before ending the game
        endwin();
      }
      else if (gunchoice == 'b')     //If the user presses b, the game continues and a message saying so is displayed
      {
        mvprintw(25, 0, "You decide its not worth the risk of attacking a fully prepared enemy cruiser.\n"
        "Escaping this ship is your top priority. Im just a journalist not a marine you think to yourself.\n");
        refresh();
      }
    }
    if (movechoice == 'w')      //If the user presses w, they are moved north into the viewing deck
    {
      clear();
      map();
      printw("\nYou've entered viewing deck (V on map).\n");
      printw("Press q to investigate the room.\n");
      keydata();
      refresh();
      movechoice = 0;
      break;
    }
  }
}

char cargobay(void)      //Displays the information for the cargo bay
{
  clear();
  map();
  printw("\nYou've entered the cargo bay (C on map).\n");
  printw("Press q to investigate the room.\n");
  keydata();
  refresh();
  while(1)       //Waits for user to either move or investigate the room
  {
    movechoice = getch();      //Gets the direction of travel or the request to investigate room from user
    if (movechoice == 'q')     //If the user presses q, they are given info on the room based on the conditions below
    {
      if (key == 3 && injured == 1)     //If the user has gotten all the 3 keys and saved the crewmember, they lose the game and a message saying so is displayed
      {
        printw("\nYou have found the door behind which the escape pods are located.\n");
        printw("You walk into the escape pod bay to see that all but one has survived the initial explosion.\n"
        "You realize that there is only room for one person. Unfortunately for you the crewmember your helping realizes this first\n"
        "and before you now it he pulls out a knife and stabs you. I shouldn't have saved him you think to yourself in your final moments.\n"
        "You watch stunned as he drags himself into the escape pod and leaves you on the ship with no escape.\n");
        printw("Restart the game.");
        refresh();
        sleep(30);      //Gives user time to read the message before ending the game
        endwin();
      }
      else if (key == 3)      //If the user has gotten all 3 keys and hasn't saved the crewmember, they win the game and a message saying so is displayed
      {
        printw("\nYou have found the door behind which the escape pods are located.\n"
        "You walk into the escape pod bay to see that all but one has survived the initial explosion.\n"
        "You get in, start up the pod and let the autopilot take over. You've escaped.");
        refresh();
        sleep(12);
        endwin();
      }
      else      //If the user hasn't gotten all the keys yet, a message saying to come back with all the keys is displayed
      {
        printw("\nYou have found the door to the escape pods but it is locked. Return here when you have all the keys.\n");
        refresh();
      }
    }
    if (movechoice == 's' )     //If the user presses s, they are moved south into electrial
    {
      clear();
      map();
      printw("\nYou've entered electrial (E on map).\n");
      printw("Press q to investigate the room.\n");
      keydata();
      refresh();
      movechoice = 0;
      break;
    }
  }
  return 0;
}

char cafeteria(void)      //Dislpays the information on the cafeteria
{
  clear();
  map();
  printw("\nYou've entered the cafeteria (CAF on map).\n");
  printw("Press q to investigate the room.\n");
  keydata();
  refresh();
  while(1)      //Waits for user to either move or investigate the room
  {
    movechoice = getch();      //Gets the direction of travel or the request to investigate room from user
    if (movechoice == 'q')     //If user presses q, a description of the room and the absence of a key is displayed
    {
      printw("\nYou walk into the cafeteria and see no key or person around. You grab a granola bar hoping its not the last one you ever eat.\n");
      refresh();
    }
    if (movechoice == 'w')      //If the user presses w, they are moved north into records
    {
      records();
    }
    if (movechoice == 'd')      //If the user presses d, they are moved east into the lounge
    {
      lounge();
    }
    if (movechoice == 'a')      //If the user presses a, they are moved west into the engine room
    {
      clear();
      map();
      printw("\nYou've entered the engine room (ER on map).\n");
      printw("Press q to investigate the room.\n");
      keydata();
      refresh();
      movechoice = 0;
      break;
    }
  }
}

char records(void)     //Displays the information on the records room
{
  clear();
  map();
  printw("\nYou've entered records (R on map).\n");
  printw("Press q to investigate the room.\n");
  keydata();
  refresh();
  while(1)      //Waits for user to either move or investigate the room
  {
    movechoice = getch();       //Gets the direction of travel or the request to investigate room from user
    if (movechoice == 'q')      //If q is pressed, a scenario and a message is displayed depending on if the user has already gotten this key or not
    {
      if (keycountertwo == 0)     //If the user hasn't been in this room yet, the scenario is given and a message saying they have gotten the key is displayed
      {
        keycountertwo ++;         //Prevents this from being run again
        key ++;                   //Your obtained keys increases by 1
        //The scenario thats displayed asks if the user wants to help a trapped and injured crewmember
        printw("\nYou find a crewmember. This person is alive but has serious injuries to their leg that is trapped under a fallen crate.\n"
        "They hand over their key and ask for you to help them.\n"
        "Do you A) help the injured crewmember and take them with you or B) leave them there.\n");
        printw("Answer with the letter a or b.\n");
        keydata();
        refresh();
        scanf("%c", &crewchoice);     //Gets the user's choice on the scenario
        if (crewchoice == 'a')        //If the user presses a, they save the crewmember and a message is displayed
        {
          mvprintw(24, 0, "You remove the crate off the crewmember's leg. He uses a first aid kit to treat the injury as best as he can.\n"
          "You put your arm under the crewmembers shoulder and help carry him out.\n");
          refresh();
          injured ++;
        }
        else if (crewchoice == 'b')     //If the user presses b, they leave the crewmember and a message is displayed
        {
          mvprintw(24, 0, "You leave the crewmember in the room knowing you couldn't have saved them.\n");
          refresh();
        }
      }
      else      //If the user has already been in this room, a message is displayed depending on if they saved the crewmember
      {
        if (injured == 0)     //If they didn't save the crewmember a message is displayed saying that he died
        {
          printw("\nYou walk in and see the crewmember has bled out. At least you got the key right?\n");
          refresh();
        }
        else                  //If they did save the crewmember a message saying they have already gotten this key is displayed
        {
          printw("\nYou've already got the key from this room there's nothing else to see.\n");
          refresh();
        }
      }
    }
    if (movechoice == 's')      //If the user presses s, they are moved south into the cafeteria
    {
      clear();
      map();
      printw("\nYou've entered the cafeteria (CAF on map).\n");
      printw("Press q to the investigate room.\n");
      keydata();
      refresh();
      movechoice = 0;
      break;
    }
  }
}

char lounge(void)       //Displays the information on the lounge
{
  clear();
  map();
  printw("\nYou've entered the lounge (L on map).\n");
  printw("Press q to investigate the room.\n");
  keydata();
  refresh();
  while(1)      //Waits for user to either move or investigate the room
  {
    movechoice = getch();       //Gets the direction of travel or the request to investigate room from user
    if (movechoice == 'q')      //If the user presses q, a message saying they have aquired the crowbar and the absence of a key is displayed
    {
      crowbar ++;     //Crowbar is aquired
      printw("\nYou walk into the room and dont find a person or key inside.\n"
      "However, after looking through some of the cabinets you find a crowbar. You decide to take it as it might be useful.\n");
      refresh();
    }
    if (movechoice == 'a')      //If the user presses a, they are moved west into the cafeteria
    {
      clear();
      map();
      printw("\nYou've entered the cafeteria (CAF on map).\n");
      printw("Press q to investigate the room.\n");
      keydata();
      refresh();
      movechoice = 0;
      break;
    }
  }
}
