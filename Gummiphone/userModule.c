#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include "display.c"


//#include "display.c"

#define MAX_CHAR 1000
#define MAX_MESSAGES 1000
#define MAX_USERS 30
#define MAX_PASS 20
#define MAX_QNA 100

typedef struct Message
{

  char sender[20];
  char receiver[20];
  char messageSubject[20];
  char content[1000];
  char messageType;
  char group[20][20];
  int countGroup;
  int isRead;
} MessageObj;

//typedef struct Message MessageObj;

typedef struct User
{

  char type[50];
  char name[50];
  char username[20];
  char password[20];
  char description[100];
  char friends[20][20];
  char status[20];
  char lockunlock[20];
  char securityQuestion[50];
  char securityAnswer[20];
  int countFriends;
  int countInbox;
  int countSent;
  MessageObj inbox[20];
  MessageObj sent[20];

} UserObj;

//typedef struct User UserObj;



/* <Description of function> Precondition: <precondition /
assumption>
@param <name> <purpose>
@return <description of returned result>
*/

/*
This function gets the index of the username
Precondition: the username given is existing
@param users - is the struct where the function will get the index of the username that the user inputs
@param username - input from the user
@param userAdded - total number of users
@return the resulting index number if the username exist.
*/
int getIndexUsername(UserObj users[20], char username[], int usersAdded)
{
  int i;
  for (i = 0; i < usersAdded; i++)
  {
    if (strcmp(users[i].username, username) == 0)
    {
      return i;
    }
  }
  return -1;
}

/* This function gets a random string from a file 
<Precondition: file exist or else it will return the default string
@param strQuestion stores the string from a file
@return returns an interrogative string
*/
void generateQuestion(char strQuestion[50])
{
  FILE *qna;
  qna = fopen("qnaQuestions.txt", "rt");
  char strQNA[100][MAX_QNA];
  int numPossible = 0, i = 0, randIndex;

  if (qna != NULL) // file exist
  {
    // read the file line by line
    while (fgets(strQNA[i], sizeof(strQNA[i]), qna)) // will return true if there is something to read
    {
      if (strQNA[i][strlen(strQNA[i] - 1)] == '\n')
        strQNA[i][strlen(strQNA[i] - 1)] = '\0';
      i++;
      numPossible++;
    }
    srand(time(NULL));
    randIndex = rand() % numPossible;
    strcpy(strQuestion, strQNA[randIndex]);

    fclose(qna);
  }
  else // file does not exist
    strcpy(strQuestion, "\t\t\t\t\tWhat is your Blood Type?\n");
}

/* This function uses the generateQuestion function and gives the user
a freedom to choose which question the user will answer 
<Precondition: file exist or else it will return the default string
@param strQuestion stores the string from a file
@param cTemp holder for the generated question of the previous function
@return returns an interrogative string
*/

void DisplayGenerateQuestion(char strQuestion[50], char cTemp[50]) {
    char cChoice;

    printf("\t\t\t\t\tSecurity Question:\n");
    generateQuestion(strQuestion);
    printf("\t\t\t\t\t\t%s", strQuestion);
    
    do {
        printf("\t\t\t\t\t[N]ext [A]nswer: ");
        fflush(stdin);
        cChoice = getchar();

        if (cChoice == 'n' || cChoice == 'N') {
            printf("\n");
            printf("\t\t\t\t\tSecurity Question:\n");
            generateQuestion(strQuestion);
            printf("\t\t\t\t\t\t%s", strQuestion);
        }
        else if (cChoice == 'a' || cChoice == 'A') {
            printf("\n");
            strcpy(cTemp, strQuestion);
        }
        else {
            printf("\n\t\t\t\t\tError: Invalid input. \n\t\t\t\t\tPlease enter [N] for Next Question and [A] if you want to answer the question.\n");
        }
    } while (cChoice != 'a' && cChoice != 'A');
}

/* This function creates a new account/ register
precondition: user must provide their information
@param users - array of registered users
@param ptr userAdded - number of users existing
@return the user information and stores it to the users array
*/
void CreateAccount(UserObj users[], int *usersAdded)
{

  UserObj newUser;
  int index = *usersAdded;
//  int i;

char reEnter[20];
  int usernameIndex;
  char strQuestion[50], cTemp[50];

  printf("\t\t\t\t\tEnter name: ");
  gets(newUser.name);
  do
  {
    printf("\t\t\t\t\tUsername: ");
    gets(newUser.username);
    usernameIndex = getIndexUsername(users, newUser.username, *usersAdded);
    if (usernameIndex != -1)
    {
      printf("\t\t\t\t\tUsername Already taken. Please Try Another One\n");
    }
  } while (usernameIndex != -1);

do
{
  printf("\t\t\t\t\tPassword: ");
  gets(newUser.password);
   printf("\t\t\t\t\tRe-Enter Password: ");
  gets(reEnter);
  if(strcmp(reEnter, newUser.password)!=0)
  {
  	printf("\t\t\t\t\tError! Passwords don't match...\n '");
  }
}while (strcmp(reEnter, newUser.password)!=0);
     
  // security question random
  DisplayGenerateQuestion(strQuestion, cTemp);
  strcpy(newUser.securityQuestion, cTemp);

	fflush(stdin);
  printf("\t\t\t\t\tAnswer to your security question[max of %d characters]:", MAX_QNA);
  gets(newUser.securityAnswer);
  fflush(stdin);

  newUser.countFriends = 0;
  newUser.countInbox = 0;
  newUser.countSent = 0;
  strcpy(newUser.status, "ACTIVE");
  strcpy(newUser.description, "DEFAULT USER");
  strcpy(newUser.lockunlock, "UNLOCKED");
  strcpy(users[index].lockunlock, newUser.lockunlock);
  users[index] = newUser;
  
  index = index + 1;
  *usersAdded = index;


  printf("\t\t\t\t\tUser successfully added.\n");
}

/* This function allows the user the ask the admin to refresh their passcode
<Precondition: the user must anser the security question correctly
@param users: array of users
@param usersAdded: number of users existing
@return the user's account will be locked and their login credentials will be invalidated
*/

void ForgotPassword(UserObj users[], int usersAdded)
{
  char temp[20];
  char username[20];
  UserObj user;
  int index;

  printf("\t\t\t\t\tEnter username: ");
  fgets(username, sizeof(username), stdin);
  username[strlen(username)-1] = '\0'; // remove newline character
  
  index = getIndexUsername(users, username, usersAdded);
    
  if (index == -1)
  {
    printf("\t\t\t\t\tAccount does not exist.\n");
  }

  else
  {
    user = users[index];
    printf("\t\t\t\t\t%s\n", users[index].securityQuestion);
    printf("\t\t\t\t\tAnswer for your security question: ");
    fgets(temp, sizeof(temp), stdin);
    temp[strlen(temp)-1] = '\0'; // remove newline character
    
    if (strcmp(temp, user.securityAnswer) == 0)
    {
      strcpy(users[index].lockunlock, "LOCKED");
      strcpy(users[index].password, "locked");
      printf("\n\t\t\t\t\tThe Admin will refresh your password to a default password in a while.\n\t\t\t\t\t\tNOTE: Make sure to change the default password for security purposes.\n");
      printf("\t\t\t\t\tYour new password is \"password\".\n");
    }
    else
    {
      printf("\t\t\t\t\tInvalid answer.\n");
    }
  }
}


/* This function checks if the input of the user is existing
Precondition:the inputs are correct
@param users: array of users
@param username: unser's username input
@param passwork: user's password input
@param usersAdded: number of users existing
@return -1 if the user is non existent or index of the user if inputs are existent
*/
int login(UserObj users[20], char username[], char password[], int usersAdded)
{
  int i;
  for (i = 0; i < usersAdded; i++)
  {
    if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0)
    {
      if (strcmp(users[i].status, "ACTIVE") == 0 && strcmp(users[i].lockunlock, "UNLOCKED")==0)
      {
        return i;
      }
    }
  }
  return -1;
}

/* This function gets the index of the username input
<Precondition/assumption>
@param friends is an array of user's friends
@param countfriends is the number of friends f the user
@param username is a string inputted by the user
@return <description of returned result>
*/
int getIndexFriendUsername(char friends[][20], int countFriends, char username[])
{
  int i;
  for (i = 0; i < countFriends; i++)
  {
    if (strcmp(friends[i], username) == 0)
    {
      return i;
    }
  }
  return -1;
}

/* This function copies the an array to an array
<Precondition/assumption>: array 1 and 2 exist
@param a is an array where copies are stored
@param b is an array to copy
@param count number of rows of param b
@returns a copy of param b
*/
void copyList(char a[][20], char b[][20], int count)
{
  int i;

  for (i = 0; i < count; i++)
  {
    strcpy(a[i], b[i]);
  }
}

/* This function allows the user to send message
<Precondition:  receiver is existing
@param ptr sender is the one who will send the message
@param receiver is the one who will receive the message
@param msg is an array of messages with struct
@return TODO: 
*/
void sendMessage(UserObj *sender, UserObj *receiver, MessageObj msg)
{

  UserObj a = *sender;
  UserObj b = *receiver;

  a.sent[a.countSent] = msg;
  b.inbox[b.countInbox] = msg;
  a.countSent += 1;
  b.countInbox += 1;

  *sender = a;
  *receiver = b;
}

/* This function allows the user to send message to a group
<Precondition/assumption>
@param users is an arrayy of registered user
@param usersAdded is the number of registered users
@param userIndex index of the user( used to identify who the user is among the registered users)
@returns a string that will be copied to an array of messeges
*/
void sendGroupMessage(UserObj users[], int usersAdded, int userIndex, MessageObj msg)
{

  int i, tempIndex;
  UserObj user = users[userIndex];
  int receiversIndeces[msg.countGroup];
  int index = 0;
  for (i = 0; i < usersAdded; i++)
  {
    tempIndex = getIndexUsername(users, msg.group[i], usersAdded);
    if (tempIndex != -1 && tempIndex != userIndex)
    {
      receiversIndeces[index] = tempIndex;
      strcat(msg.receiver, users[tempIndex].username);
      strcat(msg.receiver, " ");
      index++;
    }
  }
  for (i = 0; i < index; i++)
  {
    UserObj receiver = users[receiversIndeces[i]];
    receiver.inbox[receiver.countInbox] = msg;
    receiver.countInbox++;
    users[receiversIndeces[i]] = receiver;
  }

  user.sent[user.countSent] = msg;
  user.countSent++;
  users[userIndex] = user;
  printf("\t\t\t\t\tMessage sent to the group.\n\n");
}

/* This functiona allows the user to compose a message
<Precondition/assumption> TODO:
@param users is an arrayy of registered user
@param usersAdded is the number of registered users
@param userIndex index of the user( used to identify who the user is among the registered users)
@returns a string that will be copied to an array of messeges of the user
*/
void composeMessage(UserObj users[], int usersAdded, int index)
{
  char message[100];
  char receiverUsername[20];
  char subject[20];
  UserObj sender = users[index];
  printf("\t\t\t\t\tSubject: ");
  gets(subject);
  printf("\t\t\t\t\tType your message: ");
  gets(message);
  char whom[2];
  printf("\t\t\t\t\tTo whom? (G for group, S for specific): ");
  gets(whom);
  if (strcmp(whom, "S") == 0 || strcmp(whom, "s") == 0)
  {
    printf("\t\t\t\t\tReceiver's Username: ");
    gets(receiverUsername);
    int receiverIndex = getIndexUsername(users, receiverUsername, usersAdded);
    UserObj receiver = users[receiverIndex];
    MessageObj msg;
    if (receiverIndex >= 0)
    {
      strcpy(msg.messageSubject, subject);
      strcpy(msg.content, message);
      strcpy(msg.sender, sender.username);
      strcpy(msg.receiver, receiver.username);
      msg.messageType = 'S';
      msg.isRead = 0;
      sendMessage(&sender, &receiver, msg);
      printf("\t\t\t\t\tSent message to %s.\n", receiverUsername);
      users[receiverIndex] = receiver;
      users[index] = sender;
    }
    else
    {
      printf("\t\t\t\t\tInvalid username or username does not exist.\n\n");
    }
  }
  else if (strcmp(whom, "G") == 0 || strcmp(whom, "g") == 0)
  {
    MessageObj msg;
    char username[20];
    char strCount[3];
    int count = 0, i;
    strcpy(msg.receiver, "");
    strcpy(msg.messageSubject, subject);
    strcat(msg.content, sender.username);
    strcat(msg.content, ": ");
    strcat(msg.content, message);
    strcat(msg.content, "\n");
    msg.messageType = 'G';
    msg.countGroup = 0;
    printf("\t\t\t\t\tHow many users you want to send this message? : ");
    gets(strCount);
    count = atoi(strCount);
    char receivers[count][20];
    printf("\t\t\t\t\tEnter their usernames: ");
    for (i = 0; i < count; i++)
    {
      gets(username);
      strcpy(receivers[i], username);
    }
    strcpy(receivers[i], sender.username);
    count++;
    for (i = 0; i < count; i++)
    {
      strcpy(msg.group[i], receivers[i]);
    }
    msg.countGroup = count;
    sendGroupMessage(users, usersAdded, index, msg);
  }
}

int checkUserStatus(UserObj users[], int usersAdded)
{
  int i;
  for (i = 0; i < usersAdded; i++)
  {
    if (strcmp(users[i].status, "ACTIVE") != 0)
    {
      return -1;
    }
  }
  return 0;
}

/* This function shows the inbox of the user
<Precondition/assumption>
@param users is an arrayy of registered user
@param usersAdded is the number of registered users
@param index index of the user( used to identify who the user is among the registered users)
@return the inbox of the user based of the index parameter
*/

void inbox(UserObj users[], int usersAdded, int index)
{
  UserObj user = users[index];
  int i, j;
  char messageChoice[2];
  int x;
  char answer[2];
  MessageObj replyMsg;
  char message[100];
  int senderIndex;

  if (user.countInbox == 0)
  {
    printf("\t\t\t\t\tInbox is empty.\n\n");
  }
  else
  {
    printf("\t\t\t\t\tRead messages: \n");
    for (i = 0; i < user.countInbox; i++)
    {
      if (user.inbox[i].isRead && user.inbox[i].messageType == 'S')
      {
        printf("\t\t\t\t\t%d. Sender: %s\n", i + 1, user.inbox[i].sender);
      }
      else if (user.inbox[i].isRead && user.inbox[i].messageType == 'G')
      {
        printf("\t\t\t\t\t%d. Sender: ", i + 1);
        for (j = 0; j < user.inbox[i].countGroup; j++)
        {
          if (!strcmp(user.inbox[i].group[j], user.username) == 0)
          {
            printf("%s ", user.inbox[i].group[j]);
          }
        }
        printf("\n");
      }
    }
    printf("\t\t\t\t\tUnread messages: \n");
    for (i = 0; i < user.countInbox; i++)
    {
      if (user.inbox[i].isRead == 0 && user.inbox[i].messageType == 'S')
      {
        printf("\t\t\t\t\t%d. %s\n", i + 1, user.inbox[i].sender);
      }

      else if (user.inbox[i].isRead == 0 && user.inbox[i].messageType == 'G')
      {
        printf("\t\t\t\t\t%d. Sender: ", i + 1);
        for (j = 0; j < user.inbox[i].countGroup; j++)
        {
          if (!strcmp(user.inbox[i].group[j], user.username) == 0)
          {
            printf("%s ", user.inbox[i].group[j]);
          }
        }
        printf("\n");
      }
    }
    printf("\t\t\t\t\tSelect which message to open (x to go back): ");
    gets(messageChoice);
    if (strcmp(messageChoice, "x") == 0)
    {
      return;
    }
    x = atoi(messageChoice) - 1;
    if (x > user.countInbox || x < -1)
    {
      printf("\t\t\t\t\tInvalid choice.\n\n");
    }
    else
    {
      if (user.inbox[x].messageType == 'S')
      {
        printf("\t\t\t\t\tMessage: %s\n\n", user.inbox[x].content);
      }
      else if (user.inbox[x].messageType == 'G')
      {
        printf("\t\t\t\t\tMessage: \n");
        printf("\t\t\t\t\t%s\n\n", user.inbox[x].content);
      }

      user.inbox[x].isRead = 1;
      printf("\t\t\t\t\tDo you want to reply? (Y/N): ");
      gets(answer);
      system("cls");
      if (strcmp(answer, "Y") == 0)
      {
        senderIndex = getIndexUsername(users, user.inbox[x].sender, usersAdded);
        // turning the username of deleted user to DELETED USER
        if (strcmp(users[senderIndex].status, "NOT ACTIVE") == 0)
        {
          strcpy(users[senderIndex].username, "DELETED USER");
        }

        printf("\t\t\t\t\tType your message: ");
        gets(message);
        strcpy(replyMsg.messageSubject, user.inbox[x].messageSubject);
        if (user.inbox[x].messageType == 'S')
        {
          strcpy(replyMsg.content, message);
          strcpy(replyMsg.sender, user.username);
          strcpy(replyMsg.receiver, users[senderIndex].username);
          replyMsg.messageType = 'S';
          replyMsg.isRead = 0;
          sendMessage(&users[index], &users[senderIndex], replyMsg);
        }
        else if (user.inbox[x].messageType == 'G')
        {
          strcpy(replyMsg.content, user.inbox[x].content);
          replyMsg.messageType = 'G';
          replyMsg.isRead = 0;
          replyMsg.countGroup = user.inbox[x].countGroup;
          strcat(replyMsg.content, user.username);
          strcat(replyMsg.content, ": ");
          strcat(replyMsg.content, message);
          strcat(replyMsg.content, "\n");
          for (i = 0; i < replyMsg.countGroup; i++)
          {
            strcpy(replyMsg.group[i], user.inbox[x].group[i]);
          }
          sendGroupMessage(users, usersAdded, index, replyMsg);
        }

        printf("\t\t\t\t\tReplied message.\n\n");
      }
    }
  }
}

/* This function allows the users to view the messages the user sent
<Precondition/assumption>
@param users is an arrayy of registered user
@param index index of the user( used to identify who the user is among the registered users)
@return the sent messages
*/

void sent(UserObj users[], int index)
{

  UserObj user = users[index];
  int i, j;
  char messageChoice[2];
  int x;
  if (user.countSent == 0)
  {
    printf("\t\t\t\t\tSent messages is empty.\n\n");
  }
  else
  {
    printf("\t\t\t\t\tUnread: \n");
    for (i = 0; i < user.countSent; i++)
    {
      if (user.sent[i].isRead == 0 && user.sent[i].messageType == 'S')
      {
        printf("\t\t\t\t\t%d. %s\n", i + 1, user.sent[i].receiver);
      }
      else if (user.sent[i].isRead == 0 && user.sent[i].messageType == 'G')
      {
        printf("\t\t\t\t\t%d. ", i + 1);
        for (j = 0; j < user.sent[i].countGroup; j++)
        {
          if (!strcmp(user.sent[i].group[j], user.username) == 0)
          {
            printf("%s ", user.sent[i].group[j]);
          }
        }
        printf("\n");
      }
    }
    printf("\t\t\t\t\tRead messages: \n");
    for (i = 0; i < user.countSent; i++)
    {
      if (user.sent[i].isRead == 1 && user.sent[i].messageType == 'S')
      {
        printf("\t\t\t\t\t%d. %s\n", i + 1, user.sent[i].receiver);
      }
      else if (user.sent[i].isRead == 1 && user.sent[i].messageType == 'G')
      {
        printf("\t\t\t\t\t%d. ", i + 1);
        for (j = 0; j < user.sent[i].countGroup; j++)
        {
          if (!strcmp(user.sent[i].group[j], user.username) == 0)
          {
            printf("\t\t\t\t\t%s ", user.sent[i].group[j]);
          }
        }
        printf("\n");
      }
    }
    printf("\t\t\t\t\tSelect which message to open (x to go back): ");
    gets(messageChoice);
    if (strcmp(messageChoice, "x") == 0)
    {
      return;
    }
    x = atoi(messageChoice) - 1;
    if (x > user.countSent || x < -1)
    {
      printf("\t\t\t\t\tInvalid choice.\n\n");
    }
    else
    {
      printf("\t\t\t\t\tMessage: %s\n\n", user.sent[x].content);
      user.sent[x].isRead = 1;
    }

    users[index] = user;
  }
}

/* This function allows the user view the announcement as well as to reply to the announcement
<Precondition/assumption> there is an announcement
@param users is an arrayy of registered user
@param index is index of the user( used to identify who the user is among the registered users)
@param announcements is an array of announcement
@param announcementsAdded is the number of announcements existing
@return displays the array of announcement
*/

void viewAnnouncements(UserObj users[], int index, char announcements[][100], int announcementsAdded)
{

  int i;
  char select[2];
  char message[50];
  char answer[2];
  UserObj user = users[index];
  if (announcementsAdded == 0)
  {
    printf("\t\t\t\t\tAnnouncement list is empty.\n\n");
  }
  else
  {
    for (i = 0; i < announcementsAdded; i++)
    {
      printf("\t\t\t\t\t%d. Announcement: %s \n", i + 1, announcements[i]);
    }
    printf("\t\t\t\t\tDo you want reply from any announcements? (Y/N): ");
    gets(answer);
    if (strcmp(answer, "Y") == 0)
    {
      printf("\t\t\t\t\tSelect which announcement to reply: ");
      gets(select);
      int choice = atoi(select) - 1;
      if (choice > -1 && choice < announcementsAdded)
      {
        printf("\t\t\t\t\tType your reply: ");
        gets(message);
        strcat(announcements[choice], "\n");
        strcat(announcements[choice], user.username);
        strcat(announcements[choice], ": ");
        strcat(announcements[choice], message);
      }
    }
  }
}

/* This function allows the user to modify the user's information 
<Precondition/assumption>: the user is existing/ already registered
@param users is an arrayy of registered user
@param index index of the user( used to identify who the user is among the registered users)
@returns the modified personal contents
*/

void modifyPersonalContents(UserObj users[], int userIndex)
{
	
  UserObj user = users[userIndex];
  char cChoice;
  // printf("\t\t\t\t\t\t\tCURRENT PROFILE:\n");
  // printf("\t\t\t\t\tName: %s", user.name);
  // printf("\n\t\t\t\t\tDescription: %s\n\n", user.description);
  // printf("\t\t\t\t\tChoose what you want to modify..\n");
  // printf("\t\t\t\t\t[1]. Name\n");
  // printf("\t\t\t\t\t[2]. Description\n");
   printf("\t\t\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 201,205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205,205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205,187);
  printf("\t\t\t\t\t%c      C U R R E N T  P R O F I L E      %c\n", 186, 186);
  printf("\t\t\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 200,205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205,205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205,188);
  printf("\t\t\t\t\t Username: %s                           \n", user.username);
  printf("\t\t\t\t\t Name: %s                               \n", user.name);
  printf("\t\t\t\t\t Description: %s                        \n", user.description);
  printf("\t\t\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 205,205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205,205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205,205);
  printf("\n");
  printf("\t\t\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 201,205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205,205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205,187);
  printf("\t\t\t\t\t%c        Modify what? :                  %c\n", 186, 186);
  printf("\t\t\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 204,205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205,205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205,185);
  printf("\t\t\t\t\t%c1. Name                                 %c\n", 186, 186);
  printf("\t\t\t\t\t%c2. Username                             %c\n", 186, 186);
  printf("\t\t\t\t\t%c3. Description                          %c\n", 186, 186);
  printf("\t\t\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 200,205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205,205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205,188);
  printf("\t\t\t\t\tChoice: ");
  cChoice = getche();
  while(cChoice != '1' && cChoice !='2')
  {
  	printf("\t\t\t\t\tError: Invalid choice. Choose again...");
  	cChoice = getch();
  }
  
  switch(cChoice)
  {
  	case '1':
  	{
  		system("cls");
  		printf("\t\t\t\t\tEnter name: ");
  		gets(user.name);
  		
	}
	break;
	case '2':
	{
		system("cls");
		printf("\t\t\t\t\tDescription: ");
 		gets(user.description);
	}
  }
  
  printf("\t\t\t\t\tEnter your password to complete this process: ");
  char password[50];
  gets(password);
  if (strcmp(password, user.password) == 0)
  {
    users[userIndex] = user;
    printf("\t\t\t\t\tModification completed.\n\n");
  }
  else
  {
    printf("\t\t\t\t\tInvalid password. Modification failed.\n\n");
  }
}

/* This function allows the users to modify the personal connections
<Precondition/assumption>: user is existing
@param users is an arrayy of registered user
@param userIndex index of the user( used to identify who the user is among the registered users)
@param usersAdded is the number of registered users
@returns the modified personal connections
*/

void modifyPersonalConnections(UserObj users[], int userIndex, int usersAdded)
{

  UserObj user = users[userIndex];
  char choice[2];
  int i, select, numbering;
  int index, friendIndex;
  char username[20];
  char temp[20][20];
  do
  {
    // printf("\t\t\t\t\t1. Add a personal connection.\n");
    // printf("\t\t\t\t\t2. View personal connections.\n");
    // printf("\t\t\t\t\t3. Remove a personal connection.\n");
    // printf("\t\t\t\t\t4. View user connections.\n");
    // printf("\t\t\t\t\t5. Go back.\n");
    // printf("\t\t\t\t\tChoice: ");
    modifyPersonalConnectionsOptions();
    gets(choice);
    system("cls");
    if (strcmp(choice, "1") == 0)
    {
      do
      {
        printf("\t\t\t\t\t1. Search for Friends.\n");
        printf("\t\t\t\t\t2. Go back.\n");
        gets(choice);
        if (strcmp(choice, "1") == 0)
        { // Search for Friends
          printf("\t\t\t\t\tList of users: \n");
          for (i = 0; i < usersAdded; i++)
          {
            if (i != userIndex && strcmp(users[i].username, "DELETED USER")!= 0)
            {
              printf("\t\t\t\t\t%s\n", users[i].username);
            }
          }

          printf("\t\t\t\t\tType Username: ");
          fgets(username, sizeof(username), stdin);
          username[strlen(username)-1]='\0';
          select = getIndexUsername(users, username, usersAdded);
          friendIndex = getIndexFriendUsername(user.friends, user.countFriends, username);
          if (friendIndex == -1)
          {
            if (select == -1 || select == userIndex)
            {
              if (select == -1)
              {
                printf("\t\t\t\t\tUsername does not exist.\n\n");
              }
              else if (select == userIndex)
              {
                printf("\t\t\t\t\tCannot add own profile.\n\n");
              }
            }
            else
            {
              strcpy(user.friends[user.countFriends], username);
              user.countFriends += 1;
              printf("\t\t\t\t\tSucessfully added %s to your Friends List.\n\n", username);
              users[userIndex] = user;
            }
          }
          else
          {
            printf("\t\t\t\t\t%s is already in your Friends List.\n\n", username);
          }
        }

      } while (!strcmp(choice, "2") == 0);
    }

    else if (strcmp(choice, "2") == 0)
    {

      if (user.countFriends == 0)
      {
        printf("\t\t\t\t\tFriends List is empty.\n\n");
      }
      else
      {
        printf("\t\t\t\t\tFriends: \n");
        for (i = 0; i < user.countFriends; i++)
        {
          printf("\t\t\t\t\t%d. %s\n", i + 1, user.friends[i]);
        }
        printf("\t\t\t\t\tEnter username (Enter x to go back): ");
        gets(username);
        if (!strcmp(username, "x") == 0)
        {
          select = getIndexFriendUsername(user.friends, user.countFriends, username);
          if (select == -1)
          {
            printf("\t\t\t\t\tUsername not in the list.\n\n");
          }
          else
          {
            friendIndex = getIndexUsername(users, username, usersAdded);
            UserObj friendObj = users[friendIndex];
            printf("\t\t\t\t\tName: %s\n", friendObj.name);
          }
        }
      }
    }

    else if (strcmp(choice, "3") == 0)
    {
     if (user.countFriends == 0)
      {
        printf("\t\t\t\t\tFriends List is empty.\n\n");
      }
      else
      {
      	// printf("\t\t\t\t\tList of users: \n");
          printf("\t\t\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 201,205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205,205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205,187);
          printf("\t\t\t\t\t%c      L I S T  O F  U S E R S           %c\n", 186, 186);
          printf("\t\t\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 200,205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205,205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205,188);
 
     	 for (i = 0; i < user.countFriends; i++)
	      {
	        // printf("\t\t\t\t\t%s\n", user.friends[i]);
          printf("\t\t\t\t\t%d. %s                                \n",i+1, user.friends[i]);
	      }
          printf("\t\t\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 205,205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205,205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205,205);

//	  }
      
      printf("\t\t\t\t\tType Username (Enter x to go back): ");
      gets(username);
      if (!strcmp(username, "x") == 0)
      {
        select = getIndexFriendUsername(user.friends, user.countFriends, username);
        if (select == -1)
        {
          printf("\t\t\t\t\tUsername not in your Friends List.\n");
        }
        else
        {
          index = 0;
          for (i = 0; i < user.countFriends; i++)
          {
            if (i != select)
            {
              strcpy(temp[index], user.friends[i]);
              index++;
            }
          }
          copyList(user.friends, temp, user.countFriends);
          user.countFriends--;
          users[userIndex] = user;
          printf("\t\t\t\t\t%s is now deleted from your Friends List.\n\n", username);
        }
      }
 	 }
    }
    else if (strcmp(choice, "4") == 0)
    {
      numbering = 1;
      if (user.countFriends == 0)
      {
        printf("\t\t\t\t\tFriends List is empty.\n\n");
      }
      else
      {
      	//  printf("\t\t\t\t\tList of users that have you in their friends list: \n");
      printf("\t\t\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 201,205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205,205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205,187);
      printf("\t\t\t\t\t%clist of users that are friends with you %c\n", 186, 186);
      printf("\t\t\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 200,205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205,205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205,188);
 
	      for (i = 0; i < usersAdded; i++)
	      {
	        UserObj friendObj = users[i];
	        index = getIndexFriendUsername(friendObj.friends, friendObj.countFriends, user.username);
	        if (index != -1)
	        {
	          // printf("\t\t\t\t\t%d. %s\n", numbering, friendObj.username);
               printf("\t\t\t\t\t %d. %s                                \n", numbering, friendObj.username);
	          numbering += 1;
	        }
	      }
       printf("\t\t\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 205,205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205,205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205,205);
      system("\t\t\t\t\tpause");

	  }
     
    }
  } while (!strcmp(choice, "5") == 0);
}


/* This function allows the user to modify the account's password and the answer to security question
<Precondition/assumption>: user is registered and the information provided were correct
@param ptr user is the user
@returns the modifed password or security question answer
*/

void modifyAccountSecurity(UserObj *user)
{
  char select[2];
  char password[20];
  char newPassword[20];
  char confirmPassword[20];
  char newSecurityAnswer[20];
  char reEnter[20];
  
 userModifyAccountSecurityOptions();
  gets(select);

  if (strcmp(select, "1") == 0)
  {
    int validPassword = 0;
    while (!validPassword)
    {
      printf("\t\t\t\t\tEnter old password (x to exit): ");
      gets(password);

      if (strcmp(password, "x") == 0)
      {
        return;
      }
      else if (strcmp(password, user->password) == 0)
      {
        validPassword = 1;
      }
      else
      {
        printf("\t\t\t\t\tInvalid password.\n");
      }
    }

    int passwordMatch = 0;
    while (!passwordMatch)
    {
      printf("\t\t\t\t\tEnter new password: ");
      gets(newPassword);
      printf("\t\t\t\t\tRe-enter new password: ");
      gets(confirmPassword);

      if (strcmp(newPassword, confirmPassword) == 0)
      {
        passwordMatch = 1;
      }
      else
      {
        printf("\t\t\t\t\tPasswords does not match.\n");
      }
    }
    strcpy(user->password, newPassword);
    printf("\t\t\t\t\tPassword successfully updated.\n");
  }
  else if (strcmp(select, "2")==0)
  {
    printf("\n\t\t\t\t\tSecurity Question: %s", user->securityQuestion);
    int answerMatch = 0;
    while (!answerMatch)
    {
      printf("\n\t\t\t\t\tEnter new security answer: ");
      gets(newSecurityAnswer);
      printf("\t\t\t\t\tRe-enter new security answer: ");
      gets(reEnter);

      if (strcmp(newSecurityAnswer, reEnter) == 0)
      {
        answerMatch = 1;
      }
      else
      {
        printf("\t\t\t\t\tSecurity answers does not match.\n");
      }
    }
    strcpy(user->securityAnswer, newSecurityAnswer);
    printf("\t\t\t\t\tAnswer to security question successfully updated.\n");
  }
}


/* This function allows the user to browse the registered users. view their profile, add them as a friend and send them a message.
<Precondition/assumption>: username entered exists
@param users is an arrayy of registered user
@param userIndex index of the user( used to identify who the user is among the registered users)
@param usersAdded is the number of registered users
@return <description of returned result>
*/

void browseUsers(UserObj users[], int userIndex, int usersAdded)
{

  char choice[2];
  char username[20];
  UserObj user = users[userIndex];
  int i, select;
  int friendIndex;
  UserObj friendObj;
  char message[100];
  MessageObj msg;

  // printf("\t\t\t\t\tList of users: \n");
          printf("\t\t\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 201,205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205,205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205,187);
          printf("\t\t\t\t\t%c      L I S T  O F  U S E R S           %c\n", 186, 186);
          printf("\t\t\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 200,205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205,205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205,188);
 
  for (i = 0; i < usersAdded; i++)
  {
    if (i != userIndex)
    {
      // printf("\t\t\t\t\t%s\n", users[i].username);
         printf("\t\t\t\t\t %d. %s                                \n", i+1, users[i].username);

    }
  }

  printf("\t\t\t\t\tType Username: ");
  gets(username);
  select = getIndexUsername(users, username, usersAdded);

  if (select == -1 || select == userIndex)
  {
    if (select == -1)
    {
      printf("\t\t\t\t\tUsername does not exist.\n\n");
    }
    else if (select == userIndex)
    {
      printf("\t\t\t\t\tCannot add/view own profile.\n\n");
    }
  }
  else
  {
    friendObj = users[select];
    do
    {
       printf("\t\t\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 201,205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205,205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205,187);
       printf("\t\t\t\t\t%c     Modify Connection Options          %c\n", 186, 186);
       printf("\t\t\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 200,205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205,205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205,188);
       printf("\t\t\t\t\t 1. View %s profile.                    \n", friendObj.name);
       printf("\t\t\t\t\t 2. Add %s as a friend.                 \n", friendObj.name);
       printf("\t\t\t\t\t 3. Send %s private message.            \n", friendObj.name);
       printf("\t\t\t\t\t 4. Go back.                            \n");
       printf("\t\t\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 205,205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205,205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205,205);
       printf("\t\t\t\t\tChoice: ");

      gets(choice);
      system("cls");
      if (strcmp(choice, "1") == 0)
      {
        // printf("\t\t\t\t\tUsername: %s\n", friendObj.username);
        // printf("\t\t\t\t\tName: %s\n", friendObj.name);
        // printf("\t\t\t\t\tDescription: %s\n\n", friendObj.description);
          printf("\t\t\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 201,205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205,205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205,187);
          printf("\t\t\t\t\t%c          P R O F I L E                 %c\n", 186, 186);
           printf("\t\t\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 200,205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205,205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205,188);
          printf("\t\t\t\t\t Username: %s                           \n",friendObj.username);
          printf("\t\t\t\t\t Name: %s                               \n", friendObj.name);
          printf("\t\t\t\t\t Description: %s                        \n", friendObj.description);
       printf("\t\t\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 205,205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205,205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205,205);
          
      }
      else if (strcmp(choice, "2") == 0)
      {
        strcpy(user.friends[user.countFriends], username);
        user.countFriends += 1;
        printf("\t\t\t\t\tSucessfully added %s to your Friends List.\n\n", friendObj.name);
        users[userIndex] = user;
      }
      else if (strcmp(choice, "3") == 0)
      {
        printf("\t\t\t\t\tType your message: ");
        gets(message);
        strcpy(msg.content, message);
        msg.isRead = 0;
        msg.messageType = 'S';
        strcpy(msg.sender, user.username);
        strcpy(msg.receiver, friendObj.username);
        sendMessage(&user, &friendObj, msg);
        users[userIndex] = user;
        users[friendIndex] = friendObj;
        printf("\t\t\t\t\tMessage successfully sent to %s.\n\n", friendObj.name);
      }
    } while (!strcmp(choice, "4") == 0);
  }
}
