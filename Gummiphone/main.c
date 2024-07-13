#include "AdminModule.c"
#include <windows.h>
#include <MMsystem.h>

int main(void)
{

  UserObj users[20];
  UserObj admin;
  char announcements[20][100];
  int announcementsAdded = 0;
  int usersAdded = 0;
  char choice[2];
  int index;


	
  FILE *fptr;
  fptr = fopen("UsersAdded.txt", "r");
  fscanf(fptr, "%d", &usersAdded);
  fclose(fptr);

  FILE *ptr;
  ptr = fopen("Data.bin", "rb");
  if (ptr != NULL)
  {
    fread(&users, sizeof(users), 1, ptr);
  }

  fclose(ptr);

  FILE *aptr;
  aptr = fopen("Admin.bin", "r");
  fread(&admin, sizeof(admin), 1, aptr);
  fclose(aptr);

  FILE *an;
  an = fopen("Announcements.txt", "r");
  if (an != NULL)
  {
    fread(&announcements, sizeof(announcements), 1, an);
  }

  FILE *aa;
  aa = fopen("AnnouncementAdded.txt", "r");
  if (aa != NULL)
  {
    fscanf(aa, "%d", &announcementsAdded);
  }

		PlaySound(TEXT("C:\\Users\\eliza\\Downloads\\mp\\bgMusic.wav"),NULL,SND_FILENAME|SND_ASYNC);
  do
  {
    mainPageDisplay();

    printf("\t\t\t\t\tChoice: ");
    gets(choice);
    system("cls");
    char username[20];
    char password[20];
    if (strcmp(choice, "1") == 0)
    {
      printf("\n\n\n\n\n");
      printf("\t\t\t\t\tEnter username: ");
      gets(username);
      printf("\t\t\t\t\tEnter password: ");
      gets(password);

      if (strcmp(username, admin.username) == 0 && strcmp(password, admin.password) == 0)
      { // admin module
        system("cls");
        char adminChoice[2];
        do
        {
          printf("\n\n\n\n\n");
          printf("\t\t\t\t\tWelcome Admin\n");
          adminOptions();
          printf("\t\t\t\t\tChoice. ");
          gets(adminChoice);
          system("cls");
          if (strcmp(adminChoice, "1") == 0)
          { // user module in admin module
            char moduleChoice[2];
            do
            {
              printf("\n\n\n\n\n");
              adminUsersModuleOptions();
              printf("\t\t\t\t\tChoice. ");
              gets(moduleChoice);
              system("cls");
              printf("\n\n\n\n\n");
              if (strcmp(moduleChoice, "1") == 0)
              { // view users
                adminViewUsers(users, usersAdded);
                system("\t\t\t\t\tpause");
              }
              else if (strcmp(moduleChoice, "2") == 0)
              { // modify users1
                adminModifyUsers(users, usersAdded);
                system("\t\t\t\t\tpause");
              }
              else if (strcmp(moduleChoice, "3") == 0)
              {
              	//refresh
              	adminRefreshUsers(users, usersAdded);
              	system("\t\t\t\t\tpause");
			  }
              else if (strcmp(moduleChoice, "4") == 0)
              { // delete users
                adminDeleteUsers(users, usersAdded);
                system("\t\t\t\t\tpause");
              }
              else if (strcmp(moduleChoice, "5") == 0)
              {// security questions
              	adminSecurityQuestions();
              	system("\t\t\t\t\tpause");
			  }
              system("cls");

            } while (!strcmp(moduleChoice, "6") == 0);
          }
          else if (strcmp(adminChoice, "2") == 0)
          { // message module in admin module
            char messageChoice[2];
            do
            {
              printf("\n\n\n\n\n");
              adminMessagesModuleOptions();
              printf("\t\t\t\t\tChoice: ");
              gets(messageChoice);
              system("cls");
              printf("\n\n\n\n\n");
              if (strcmp(messageChoice, "1") == 0)
              {
                adminViewFilterMessages(users, usersAdded); // view all and filter messages
                system("\t\t\t\t\tpause");
              }
              else if (strcmp(messageChoice, "2") == 0)
              { // delete messages
                adminDeleteMessages(users, usersAdded);
                system("\t\t\t\t\tpause");
              }

              system("cls");
            } while (!strcmp(messageChoice, "3") == 0);
          }
          else if (strcmp(adminChoice, "3") == 0)
          { // password module in admin module
            printf("\n\n\n\n\n");
            adminChangePassword(&admin);
            system("\t\t\t\t\tpause");
          }
          else if (strcmp(adminChoice, "4") == 0)
          { // log out
            printf("\n\n\n\n\n");
            addAnnouncement(announcements, &announcementsAdded);
            system("\t\t\t\t\tpause");
          }
          system("cls");
        } while (!strcmp(adminChoice, "5") == 0);
      }
      else
      { // users module

        index = login(users, username, password, usersAdded);
        UserObj user = users[index];
//        UserObj receiver;
        char userChoice[2];
        if (index >= 0)
        {
          system("cls");
          do
          {
            printf("\n\n\n\n\n");
            printf("\t\t\t\t\tWelcome %s\n", user.name);
            displayUserModuleOptions();
            printf("\t\t\t\t\tChoice: ");
            gets(userChoice);
            system("cls");
            printf("\n\n\n\n\n");
            if (strcmp(userChoice, "1") == 0)
            { // compose message

              composeMessage(users, usersAdded, index);
              system("\t\t\t\t\tpause");
            }
            else if (strcmp(userChoice, "2") == 0)
            { // inbox

              inbox(users, usersAdded, index);
              system("\t\t\t\t\tpause");
            }
            else if (strcmp(userChoice, "3") == 0)
            { // sent

              sent(users, index);
              system("\t\t\t\t\tpause");
            }
            else if (strcmp(userChoice, "4") == 0)
            { // view announcements

              viewAnnouncements(users, index, announcements, announcementsAdded);
              system("\t\t\t\t\tpause");
            }
            else if (strcmp(userChoice, "5") == 0)
            { // modify personal contents

              modifyPersonalContents(users, index);
              system("\t\t\t\t\tpause");
            }
            else if (strcmp(userChoice, "6") == 0)
            { // modify security profile
            	modifyAccountSecurity(&user);
              system("\t\t\t\t\tpause");
            }
            else if (strcmp(userChoice, "7") == 0)
            { // modify personal connections

              modifyPersonalConnections(users, index, usersAdded);
              system("\t\t\t\t\tpause");
            }
            else if (strcmp(userChoice, "8") == 0)
            { // browse users

              browseUsers(users, index, usersAdded);
              system("\t\t\t\t\tpause");
            }
            else if (strcmp(userChoice, "9") == 0)
            { // log out
            }
            system("cls");
          } while (strcmp(userChoice, "9"));
        }

        else
        {
          printf("\t\t\t\t\tInvalid details or Account does not exist.\n");
          system("\t\t\t\t\tpause");
        }
      }
    }
    else if (strcmp(choice, "2") == 0)
    { // create new user
      printf("\n\n\n\n\n");
      CreateAccount(users, &usersAdded);
      system("\t\t\t\t\tpause");
    }
    else if (strcmp(choice, "3") == 0)
    { // forgot password
      printf("\n\n\n\n\n");
      ForgotPassword(users, usersAdded);
      system("\t\t\t\t\tpause");
    }
    else if (strcmp(choice, "4") == 0)
    {
      ptr = fopen("Data.bin", "wb");
      fwrite(&users, sizeof(users), 1, ptr);
      fclose(ptr);

      fptr = fopen("UsersAdded.txt", "w");
      fprintf(fptr, "%d", usersAdded);
      fclose(fptr);

      aptr = fopen("Admin.bin", "w");
      fwrite(&admin, sizeof(admin), 1, aptr);
      fclose(aptr);

      an = fopen("Announcements.txt", "w");
      fwrite(&announcements, sizeof(announcements), 1, an);

      aa = fopen("AnnouncementAdded.txt", "w");
      fprintf(aa, "%d", announcementsAdded);
    }
    system("cls");
  } while (!strcmp(choice, "4") == 0);
  
  return 0;
}
