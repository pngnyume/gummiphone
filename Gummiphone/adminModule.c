

//#include "display.c"
#include "userModule.c"

/* This function encrypts the password by adding 3 to the ascii code of the character
<Precondition/assumption>: the user is registered
@param phrase is a string that holds the user's password
@return 
*/
void encrypt(char phrase[])
{
  int i;
  int length = strlen(phrase);
  char encrypted[20];
  int x;

  for (i = 0; i < length; i++)
  {
    x = (int)phrase[i] + 3;
    encrypted[i] = (char)(x);
  }
  encrypted[i] = '\0';
  printf("%s", encrypted);
}

/* This function allows the admin to vie the registered users and their inoformation
<Precondition/assumption>: admin information provided are correct
@param users - array of registered users
@param userAdded - total number of users
@returns the list of the registered users and their information
*/
void adminViewUsers(UserObj users[], int usersAdded)
{
  int i, j;
  // char encrypted[strlen(user.password)-1];
  printf("\t\t\t\t\t\tList of Users: \n");
  // for (i = 0; i < usersAdded; i++)
  // {
  //   UserObj user = users[i];
  //   printf("\t\t\t\t\t%d. Username: %s\n", i + 1, user.username);
  //   printf("\t\t\t\t\t   Name: %s\n", user.name);
  //   printf("\t\t\t\t\t   Password: ");
  //   encrypt(user.password);
  //   printf("\n");
  //   printf("\t\t\t\t\t   Status: %s\n", user.status);
  //   printf("\t\t\t\t\t   Reset Password: %s\n", user.lockunlock);
  //   printf("\t\t\t\t\t   Description: %s\n", user.description);
  //   printf("\t\t\t\t\t   Friends: \n");
  //   for (j = 0; j < user.countFriends; j++)
  //   {
  //     printf("\t\t\t\t\t   \t%d. %s\n", j + 1, user.friends[j]);
  //   }
  // }
   for (i = 0; i < usersAdded; i++)
  {
    UserObj user = users[i];
  printf("\t\t\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 201,205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205,205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205,187);
  printf("\t\t\t\t\t%c [%d]            P R O F I L E           %c\n",186, i+1, 186);
  printf("\t\t\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 204,205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205,205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205,185);
  printf("\t\t\t\t\t Username: %s                           \n",user.username);
  printf("\t\t\t\t\t Name: %s                               \n", user.name);
  printf("\t\t\t\t\t Password: ");
  encrypt(user.password);
  printf("\n");
  printf("\t\t\t\t\t Status: %s                             \n", user.status);
  printf("\t\t\t\t\t Reset Password: %s                     \n", user.lockunlock);
  printf("\t\t\t\t\t Description: %s                        \n", user.description);
  printf("\t\t\t\t\t Friends:                               \n");
    for (j = 0; j < user.countFriends; j++)
    {
      // printf("\t\t\t\t\t   \t%d. %s\n", j + 1, user.friends[j]);
        printf("\t\t\t\t\t \t%d. %s                               \n", j + 1, user.friends[j]);
    }
  printf("\t\t\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 200,205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205,205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205,188);
  }
}

/* This function allows the admin to modify the users
<Precondition/assumption>: admin information provided are correct
@param users - array of registered users
@param userAdded - total number of users
@returns modified version of user's information
*/
void adminModifyUsers(UserObj users[], int usersAdded)
{

  char choice[2], newName[20], newDescription[100], newUsername[20];
  char temp[20][20];
  int select, index, i, friendSelect, friendIndex, trackIndex;
  adminViewUsers(users, usersAdded);
  printf("\t\t\t\t\tChoice: ");
  gets(choice);
  index = atoi(choice) - 1;
  if (index > -1 && index < usersAdded)
  {
    UserObj user = users[index];
    printf("\t\t\t\t\tAccessed %s's Account: \n\n", users[index].username);
    do
    {
      adminModifyUsersOptions();
      gets(choice);
      system("cls");
      select = atoi(choice);

      if (select == 1)
      {
        printf("\t\t\t\t\tCurrent name: %s", user.name);
        printf("\n\t\t\t\t\tNew Name: ");
        gets(newName);
        strcpy(user.name, newName);
        printf("\t\t\t\t\tName successfully modified.\n");
        system("pause");
      }
      else if (select == 2)
      {
        printf("\t\t\t\t\tCurrent name: %s", user.username);
        printf("\n\t\t\t\t\tNew Username: ");
        gets(newUsername);
        strcpy(user.username, newUsername);
        printf("\t\t\t\t\tUsername successfully modified.\n");
        system("pause");
      }
      else if (select == 3)
      {
        printf("\t\t\t\t\tCurrent Description: %s", user.description);
        printf("\n\t\t\t\t\tNew Description: ");
        gets(newDescription);
        strcpy(user.description, newDescription);
        printf("\t\t\t\t\tDescription successfully modified.\n");
        system("pause");
      }
      else if (select == 4)
      {
        adminModifyUsersFriendsOptions();
        gets(choice);
        friendSelect = atoi(choice);
        if (friendSelect == 1)
        {
          printf("\t\t\t\t\tEnter username: ");
          gets(newUsername);
          friendIndex = getIndexUsername(users, newUsername, usersAdded);
          if (friendIndex == -1)
          {
            printf("\t\t\t\t\t%s does not exist yet as User.\n", newUsername);
          }
          else
          {
            strcpy(user.friends[user.countFriends], newUsername);
            user.countFriends += 1;
            printf("\t\t\t\t\t%s is successfully added as a Friend.\n", newUsername);
          }
        }
        else if (friendSelect == 2)
        {
          printf("\t\t\t\t\tEnter username: ");
          gets(newUsername);
          friendIndex = getIndexFriendUsername(user.friends, user.countFriends, newUsername);
          if (friendIndex == -1)
          {
            printf("\t\t\t\t\t%s does not exist in your Friends List.\n", newUsername);
          }
          else
          {
            trackIndex = 0;
            for (i = 0; i < user.countFriends; i++)
            {
              if (!strcmp(user.friends[i], newUsername) == 0)
              {
                strcpy(temp[trackIndex], user.friends[i]);
                trackIndex += 1;
              }
            }
            user.countFriends -= 1;
            copyList(user.friends, temp, user.countFriends);
          }
        }
        system("pause");
      }
      else if (select == 5)
      {
        users[index] = user;
      }

    } while (!strcmp(choice, "5") == 0);
  }
  else
  {
    printf("\t\t\t\t\tInvalid choice.\n");
  }
}

/* This function allows the admin to refresh the user's password
<Precondition/assumption>: admin information provided are correct
@param users - array of registered users
@param userAdded - total number of users
@returns modified version of user's password and unlocks the user's account
*/
void adminRefreshUsers(UserObj users[], int usersAdded)
{
    int i, nLocked = 0, n = 1;
    UserObj lockedUser[usersAdded];
    char cChoice;

    for (i = 0; i < usersAdded; i++)
    {
        if (strcmp(users[i].lockunlock, "LOCKED") == 0)
        {
            lockedUser[nLocked] = users[i];
            nLocked++;
        }
    }

    printf("\t\t\t\t\t Users Requesting for Password Refresh:\n");
    for (i = 0; i < nLocked; i++)
    {
        printf("\t\t\t\t\t%d. %s\n", n, lockedUser[i].username);
        n++;
    }

    printf("\t\t\t\t\tDo you want to REFRESH their Passwords?\n\t\t\t\t\t[Y]es or [N]o:");
    cChoice = getche();

    if (cChoice == 'Y' || cChoice == 'y')
    {
        for (i = 0; i < usersAdded; i++)
        {
            if (strcmp(users[i].lockunlock, "LOCKED") == 0)
            {
                strcpy(users[i].lockunlock, "UNLOCKED");
                strcpy(users[i].password, "password");
            }
        }
    }
}
/* This function allows the admin to delete users
<Precondition/assumption>: admin information provided are correct
@param users - array of registered users
@param userAdded - total number of users
@returns modified version of user's username and status
*/
void adminDeleteUsers(UserObj users[], int usersAdded)
{
  int i;
  int count = 1;
  int index;
  char username[20];
  for (i = 0; i < usersAdded; i++)
  {
    if (strcmp(users[i].status, "ACTIVE") == 0)
    {
      printf("\t\t\t\t\t%d. %s\n", count, users[i].username);
      count += 1;
    }
  }
  printf("\t\t\t\t\tEnter username: ");
  gets(username);
  index = getIndexUsername(users, username, usersAdded);
  if (index != -1)
  {
  	strcpy(users[index].username,  "DELETED USER");
  	strcpy(users[index].description,  "NOT AVAILABLE");
    strcpy(users[index].status, "NOT ACTIVE");
    printf("\t\t\t\t\t%s's account is now deleted.\n", username);
  }
  else
  {
    printf("\t\t\t\t\t%s does not exist in the Accounts.\n", username);
  }
}

void adminPrintQuestion()
{
	FILE *pFile;
	char strQuestion[MAX_QNA];
	int i=1;
	
	pFile = fopen("qnaQuestions.txt","rt");
	if (pFile !=NULL)
	{
		// printf("\t\t\t\t\tSECURITY QUESTIONS:\n\n");
  printf("\t\t\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 201,205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205,205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205,187);
  printf("\t\t\t\t\t%c   S E C U R I T Y  Q U E S T I O N S   %c\n", 186, 186);
  printf("\t\t\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 204,205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205,205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205,185);
 
	while(fgets(strQuestion, sizeof(strQuestion),pFile))
	{
		printf("\t\t\t\t\t%d. %s \n",i,strQuestion);
		i++;
	}
  printf("\t\t\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 200,205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205,205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205,188);
	fclose(pFile);
	} else
	{
		printf("\t\t\t\t\tError! Could not Open file\n");
		exit(-1);
	}
	
}

/* This function allows the admin to add a security question to the file
<Precondition/assumption>: admin information provided are correct
@returns the file with the added question
*/
void adminSecurityQuestions()
{
	FILE  *inputFile;
	char strQuestion[MAX_QNA];
	char choice;
	
	adminPrintQuestion();
	
//	do
//	{
		printf("\t\t\t\t\tDo you want to add a security Question?\n\t\t\t\t\t[Y]es or [N]o: ");
		scanf("%c", &choice);	
		fflush(stdin);
//	} while (choice != 'Y' && choice != 'y'&&choice != 'N' && choice != 'n' );

	if (choice == 'Y')
	{
		printf("\n\t\t\t\t\tEnter the question you want to add:");
		fgets(strQuestion, sizeof(strQuestion), stdin);
		strQuestion[strlen(strQuestion)-1]='\0';
		
		inputFile = fopen("qnaQuestions.txt", "a+");
		if (inputFile != NULL)
		{
			fprintf(inputFile,"\n%s",strQuestion);
			fclose(inputFile);
			printf("\n\t\t\t\t\tYour question is successfully added!");	
//			system("\t\t\t\t\tpause");
//			system("cls");
			printf("\n\t\t\t\t\t\t SECURITY QUESTIONS:\n");
			adminPrintQuestion();
		} else{
			printf("\t\t\t\t\tError! Could not Open file\n");
		}
	} 
}

/* This function allows the admin to view messages from inbox
<Precondition/assumption>: admin information provided are correct
@param users - array of registered users
@param userAdded - total number of users
@param a  TODO:
@returns modified version of user's information
*/
void viewMessagesFromInboxSent(UserObj users[], int usersAdded, int s)
{

 int i, j, k;
 int indexSender, indexReceiver;
 UserObj user;
 for (i = 0; i < usersAdded; i++)
 {
   if (s == 1)
   {
     user = users[i];
     printf("\t\t\t\t\tINBOX:\n");
     printf("\t\t\t\t\t%d. %s's Messages: \n", i + 1, user.username);
     for (j = 0; j < user.countInbox; j++)
     {

       indexSender = getIndexUsername(users, user.inbox[j].sender, usersAdded);
       if (strcmp(users[indexSender].status, "ACTIVE") == 0)
       {
         printf("\t\t\t\t\t\t%d. Sender: %s\n", j + 1, user.inbox[j].sender);
       }
       else if (strcmp(users[indexSender].status, "NOT ACTIVE") == 0)
       {
         printf("\t\t\t\t\t\t Sender: DELETED USER\n");
       }
       else
       {
         printf("\t\t\t\t\t\t Sender: Group Message\n");
       }

       if (user.inbox[j].messageType == 'S')
       {
         indexReceiver = getIndexUsername(users, user.inbox[j].receiver, usersAdded);
         if (strcmp(users[indexReceiver].status, "ACTIVE") == 0)
         {
           printf("\t\t\t\t\t\t   Receiver: %s\n", user.inbox[j].receiver);
         }
         else if (strcmp(users[indexReceiver].status, "NOT ACTIVE") == 0)
         {
           printf("\t\t\t\t\t\t   Receiver: %s\n", user.inbox[j].receiver);
         }
       }
       else if (user.inbox[j].messageType == 'G')
       {
         printf("\t\t\t\t\t\t   Receivers: \n");
         for (k = 0; k < user.inbox[j].countGroup; k++)
         {
           printf("\t\t\t\t\t\t\t%s\n", user.inbox[j].group[k]);
         }
         printf("\n");
       }
       printf("\t\t\t\t\t\t   Message subject: %s\n", user.inbox[j].messageSubject);
       printf("\t\t\t\t\t\t   Message content: %s\n", user.inbox[j].content);
     }
   }
   else
   {
     user = users[i];
     printf("\t\t\t\t\tSENT:\n");
     printf("\t\t\t\t\t%d. %s's Messages: \n", i + 1, user.username);
     for (j = 0; j < user.countSent; j++)
     {

       indexSender = getIndexUsername(users, user.sent[j].sender, usersAdded);
       if (strcmp(users[indexSender].status, "ACTIVE") == 0)
       {
         printf("\t\t\t\t\t\t%d. Sender: %s\n", j + 1, user.sent[j].sender);
       }
       else if (strcmp(users[indexSender].status, "NOT ACTIVE") == 0)
       {
         printf("\t\t\t\t\t\t%d. Sender: DELETED USER\n", j + 1);
       }
       else
       {
         printf("\t\t\t\t\t\tSender: Group Message\n");
       }

       if (user.inbox[j].messageType == 'S')
       {
         indexReceiver = getIndexUsername(users, user.sent[j].receiver, usersAdded);
         if (strcmp(users[indexReceiver].status, "ACTIVE") == 0)
         {
           printf("\t\t\t\t\t\t   Receiver: %s\n", user.sent[j].receiver);
         }
         else if (strcmp(users[indexReceiver].status, "NOT ACTIVE") == 0)
         {
           printf("\t\t\t\t\t\t   Receiver: DELETED USER\n");
         }
       }
       else if (user.inbox[j].messageType == 'G')
       {
         printf("\t\t\t\t\t\t   Receivers: \n");
         for (k = 0; k < user.sent[j].countGroup; k++)
         {
           printf("\t\t\t\t\t\t\t%s\n", user.sent[j].group[k]);
         }
         printf("\n");
       }
       printf("\t\t\t\t\t\t   Message subject: %s\n", user.sent[j].messageSubject);
       printf("\t\t\t\t\t\t   Message content: %s\n", user.sent[j].content);
     }
   }
 }
}


/* This function allows the admin to vie messages
<Precondition/assumption>: admin information provided are correct
@param users - array of registered users
@param userAdded - total number of users
@param sender is the sneder's username
@returns the list of messages of the users for the admin to view
*/
void adminViewMessages(UserObj users[], int usersAdded, char sender[20], char receiver[20])
{
  int i, j, k;
  int indexReceiver;
  int indexSender;
  UserObj user;
  if (strlen(sender) == 0 && strlen(receiver) == 0)
  {
    viewMessagesFromInboxSent(users, usersAdded, 1);
    viewMessagesFromInboxSent(users, usersAdded, 0);
  }
  else if (strlen(receiver) == 0)
  {
    for (i = 0; i < usersAdded; i++)
    {
      user = users[i];
      printf("\t\t\t\t\t%d. %s's Messages: \n", i + 1, user.username);
      for (j = 0; j < user.countInbox; j++)
      {
        if (strcmp(user.inbox[j].sender, sender) == 0)
        {
          indexSender = getIndexUsername(users, user.inbox[j].sender, usersAdded);
          if (strcmp(users[indexSender].status, "ACTIVE") == 0)
          {
            printf("\t\t\t\t\t\t%d. Sender: %s\n", j + 1, user.inbox[j].sender);
          }
          else if (strcmp(users[indexSender].status, "NOT ACTIVE") == 0)
          {
            printf("\t\t\t\t\t\t. Sender: DELETED USER\n");
          }
          else
          {
            printf("\t\t\t\t\tGroup Message.\n");
          }

          if (user.inbox[j].messageType == 'S')
          {
            indexReceiver = getIndexUsername(users, user.inbox[j].receiver, usersAdded);
            if (strcmp(users[indexReceiver].status, "ACTIVE") == 0)
            {
              printf("\t\t\t\t\tReceiver: %s\n", user.inbox[j].receiver);
            }
            else if (strcmp(users[indexReceiver].status, "NOT ACTIVE") == 0)
            {
              printf("\t\t\t\t\tReceiver: DELETED USER\n");
            }
            else
            {

              printf("\t\t\t\t\tReceiver: DELETED USER\n");
            }
          }
          else if (user.inbox[j].messageType == 'G')
          {
            printf("\t\t\t\t\tReceivers: \n");
            for (k = 0; k < user.inbox[j].countGroup; k++)
            {
              printf("\t\t\t\t\t%s\n", user.inbox[j].group[k]);
            }
            printf("\n");
          }
          printf("\t\t\t\t\t\t   Message subject: %s\n", user.inbox[j].messageSubject);
          printf("\t\t\t\t\t\t   Message content: %s\n", user.inbox[j].content);
        }
      }
    }
  }
  else if (strlen(sender) == 0)
  {
    for (i = 0; i < usersAdded; i++)
    {
      user = users[i];
      printf("\t\t\t\t\t%d. %s's Messages: \n", i + 1, user.username);
      for (j = 0; j < user.countInbox; j++)
      {
        if (strcmp(user.inbox[j].receiver, receiver) == 0)
        {
          indexSender = getIndexUsername(users, user.inbox[j].sender, usersAdded);
          if (strcmp(users[indexSender].status, "ACTIVE") == 0)
          {
            printf("\t\t\t\t\t\t%d. Sender: %s\n", j + 1, user.inbox[j].sender);
          }
          else
          {
            printf("\t\t\t\t\t\t. Sender: DELETED USER\n");
          }

          if (user.inbox[j].messageType == 'S')
          {
            indexReceiver = getIndexUsername(users, user.inbox[j].receiver, usersAdded);
            if (strcmp(users[indexReceiver].status, "ACTIVE") == 0)
            {
              printf("\t\t\t\t\tReceiver: %s\n", user.inbox[j].receiver);
            }
            else
            {

              printf("\t\t\t\t\tReceiver: DELETED USER\n");
            }
          }
          else if (user.inbox[j].messageType == 'G')
          {
            printf("\t\t\t\t\tReceivers: \n");
            for (k = 0; k < user.inbox[j].countGroup; k++)
            {
              printf("\t\t\t\t\t%s\n", user.inbox[j].group[k]);
            }
            printf("\n");
          }
          printf("\t\t\t\t\tMessage subject: %s\n", user.inbox[j].messageSubject);
          printf("\t\t\t\t\tMessage content: %s\n", user.inbox[j].content);
        }
      }
    }
  }
}

/* This function allows the admin to filter the messages
<Precondition/assumption>: admin information provided are correct
@param users - array of registered users
@param userAdded - total number of users
@returns the filtered messages either sent or received based on the username provided.
*/
void adminViewFilterMessages(UserObj users[], int usersAdded)
{

  char username[20];
  char choice[2];
//  int i;
//  int index;
  do
  {
    adminViewMessages(users, usersAdded, "", "");
    adminFilterMessagesOptions();
    gets(choice);
    if (strcmp(choice, "1") == 0)
    {
      printf("\t\t\t\t\tEnter username: ");
      gets(username);
      adminViewMessages(users, usersAdded, username, "");
      system("pause");
    }
    else if (strcmp(choice, "2") == 0)
    {
      printf("\t\t\t\t\tEnter username: ");
      gets(username);
      adminViewMessages(users, usersAdded, "", username);
      system("pause");
    }

  } while (!strcmp(choice, "3") == 0);
}

/* This function allows the admin to view the usernames
<Precondition/assumption>: admin information provided are correct
@param users - array of registered users
@param userAdded - total number of users
@returns the list of username
*/
void adminViewUsernames(UserObj users[], int usersAdded)
{
  int i;
  for (i = 0; i < usersAdded; i++)
  {
    printf("\t\t\t\t\t%d. %s\n", i + 1, users[i].username);
  }
}

/* This function copies an array of string to a destination array
<Precondition/assumption>: 
@param destination is the destination array
@param source is the array to copy
@returns a copied array of string to the destination file
*/
void adminCopyMessages(MessageObj destination[], MessageObj source[], int count)
{
  int i;
  for (i = 0; i < count; i++)
  {
    destination[i] = source[i];
  }
}

/* This function compare strings
<Precondition/assumption> the two strings are provided
@param msg1 is a string to be compared to
param msg2 is a string to be compared to
@returns 1 is the strings are alike and 0 if not
*/
int compareTwoMessage(MessageObj msg1, MessageObj msg2)
{
  if (strcmp(msg1.content, msg2.content) == 0)
  {
    if (strcmp(msg1.messageSubject, msg2.messageSubject) == 0)
    {
      if (strcmp(msg1.receiver, msg2.receiver) == 0)
      {
        if (strcmp(msg1.sender, msg2.sender) == 0)
        {
          return 1;
        }
      }
    }
  }
  return 0;
}

/* This function allows the admin to delete messgaes
<Precondition/assumption>: admin information provided are correct
@param users - array of registered users
@param userAdded - total number of users
@returns modified version messages
*/
void adminDeleteMessages(UserObj users[], int usersAdded)
{

  char choice[2];
  char s[2];
  char username[20];
  int index, select;
  MessageObj temp[20];
  int i, j, k;
  int track;

  do
  {
    printf("\t\t\t\t\t1. Delete Message From Inbox.\n");
    printf("\t\t\t\t\t2. Delete Message From Sent.\n");
    printf("\t\t\t\t\t3. Exit\n");

    printf("\t\t\t\t\tChoice: ");
    gets(choice);
    if (strcmp(choice, "1") == 0 || strcmp(choice, "2") == 0)
    {
      adminViewUsernames(users, usersAdded);
      printf("\t\t\t\t\tEnter username of the user's account: ");
      gets(username);
      index = getIndexUsername(users, username, usersAdded);
      if (index == -1)
      {
        printf("\t\t\t\t\tUsername does not exist.");
      }
      else
      {
        if (strcmp(choice, "1") == 0)
        {
          for (i = 0; i < users[index].countInbox; i++)
          {
            printf("\t\t\t\t\t%d. %s\n", i + 1, users[index].inbox[i].receiver);
          }
          printf("\t\t\t\t\tSelect number to delete: ");
          gets(s);
          select = atoi(s) - 1;
          if (select < 0 || select > users[index].countInbox)
          {
            printf("\t\t\t\t\tSelected number out of range.\n");
          }
          else
          {
            track = 0;
            for (j = 0; i < users[index].countInbox; i++)
            {
              if (j != select)
              {
                temp[track] = users[index].inbox[j];
                track++;
              }
            }
            adminCopyMessages(users[index].inbox, temp, users[index].countInbox);
            users[index].countInbox--;
            printf("\t\t\t\t\tMessage deleted.\n");
          }
        }
        else
        {
          MessageObj msgToDelete;
          for (i = 0; i < users[index].countSent; i++)
          {
            printf("\t\t\t\t\t%d. %s\n", i + 1, users[index].sent[i].receiver);
          }
          printf("\t\t\t\t\tSelect number to delete: ");
          gets(s);
          select = atoi(s) - 1;
          if (select < 0 || select > users[index].countSent)
          {
            printf("\t\t\t\t\tSelected number out of range.\n");
          }
          else
          {
            msgToDelete = users[index].sent[select];
            track = 0;
            for (j = 0; i < users[index].countSent; i++)
            {
              if (j != select)
              {
                temp[track] = users[index].sent[j];
                track++;
              }
            }
            users[index].countSent--;
            adminCopyMessages(users[index].sent, temp, users[index].countSent);

            for (j = 0; j < usersAdded; j++)
            {
              MessageObj temp[20];
              track = 0;
              for (k = 0; k < users[j].countInbox; k++)
              {
                if (compareTwoMessage(users[j].inbox[k], msgToDelete) == 0)
                {
                  temp[track] = users[j].inbox[k];
                  track++;
                }
                else
                {
                  users[j].countInbox--;
                }
              }
              adminCopyMessages(users[j].inbox, temp, users[j].countInbox);
            }
            printf("\t\t\t\t\tMessage deleted.\n");
          }
        }
      }
    }
  } while (!strcmp(choice, "3") == 0);
}

/* This function allows the admin to mmodify their password
<Precondition/assumption>: admin informtion provided are valid
@param ptr admin is the admiin's information
@returns an updated version of admin's password
*/
void adminChangePassword(UserObj *admin)
{

  char password[20];
  char newPassword[20];
  char confirmPassword[20];

  while (1)
  {

    printf("\t\t\t\t\tEnter old password (x to exit): ");
    gets(password);

    if (strcmp(password, "x") == 0)
    {
      return;
    }
    else if (strcmp(password, admin->password) == 0)
    {
      break;
    }
    else
    {
      printf("\t\t\t\t\tInvalid password.\n");
    }
  }

  while (1)
  {
    printf("\t\t\t\t\tEnter new password: ");
    gets(newPassword);
    printf("\t\t\t\t\tRe-enter new password: ");
    gets(confirmPassword);

    if (strcmp(newPassword, confirmPassword) == 0)
    {
      break;
    }
    else
    {
      printf("\t\t\t\t\tPasswords does not match.\n");
    }
  }

  strcpy(admin->password, newPassword);
  printf("\t\t\t\t\tPassword successfully updated.\n");
}

/* This function creates a new announcement
<Precondition/assumption>: admin is logged in
@param snnouncements is an array of announcements
@param ptr added is the number of added announcement
@returns a modified version of viewAnnouncement
*/
void addAnnouncement(char announcements[][100], int *added)
{
  printf("\t\t\t\t\tEnter your new Announcement: ");
  gets(announcements[*added]);
  *added = *added + 1;
  printf("\t\t\t\t\tAnnouncement added.\n");
}

