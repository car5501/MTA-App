/*
  Author: Carlos Cepeda
  Description: This program was written to perform basic operations that are executed in a regular messaging app by reading in the operations from a file. I decided to use fscanf functions and not just fgets because fscanf reads in the string and ends at a space, and the different pieces of data needed for the program run are separated by spaces.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

/*
  This struct will make up the linked lists that will be holding
  the conversation messages between me and all of the other users.
*/
typedef struct Node
{
  char contact[10];
  int timeStamp;
  char Message[255];
  struct Node *next;
} TEXT;


/*
  This fuction will not be returning anything, but it will be making changes to the variable
  "new" via passing through the File pointer and the new variable.
*/
void readText(FILE **fp, TEXT *new);
/*
  This function will not returning anything, but this is the fuction that starts the linked lists
  and adds to them according to their timestamp so they can remain stored in order from earliest to latest.
  Its parameters are the head of the designated linked list and the newText.
*/
void insertMessage(TEXT **headP, TEXT new);
/*
  This fuction will not return anything, and its parameters are the head of the corresponding linked list.
  That linked list will be used to display all the messages from the conversation.
*/
void printMessage(TEXT **headP);
/*
  This function will not return anything, and its parameters are the head of the corresponding linked list, and the
  the criteria for the message that will be deleted.
*/
void deleteMessage(TEXT **headP, TEXT del);

int main(int argc, char* argv[])
{

  FILE *fp = fopen(argv[1], "r");//File pointer that will be used to traverse the input file.
  char name[10];// Will be used when it is time to display a conversation
  char Operation[25];//This will contain the operation that will be compared in the main function. (ReceiveMessage, OpenApp,...)
  TEXT *headA = NULL, *headB = NULL, *headC = NULL;// These are the heads and the only way to access the 3 linked linked lists.
  TEXT new, del;//The information from the file for operations Receive and Delete Messages will be stored in these variables.
  int countA = 0, countB = 0, countC = 0;//These are to keep count of the messages, and act as a method for notifications.
  int open = 0;//This is a flag that will signifiy when the operation "OpenApp" was run to execute the other operations.

  fscanf((FILE*)fp, "%s", Operation);//This line will scan in the operation that will be executed by using fscanf to cut the string at the next space
  while(!feof(fp))//This cause the loop to reiterate until fp reaches the end of the file.
  {
    //Lines 77-97 will read in the message and add it to the link list according to the Person.
    //Uses string compare to see if the operation that was scanned in corresponds with the if statement
    if(strcmp(Operation, "ReceiveMessage") == 0)//Checks to see if the operation is to recieve a message
    {
      readText(&fp, &new);//The function was called to edit the TEXT struct new
      if(strcmp(new.contact, "Alice") == 0)
      {
        insertMessage(&headA, new);//If the contact of the message belongs to Alice, this function will insert the "new" struct into the linked list.
        countA++;//Updates the notification count for each person.
        printf("NotifyUser Alice\n");
      }
      else if(strcmp(new.contact, "Bob") == 0)
      {
        insertMessage(&headB, new);//If the contact of the message belongs to Bob, this function will insert the "new" struct into the linked list.
        countB++;
        printf("NotifyUser Bob\n");
      }
      else if(strcmp(new.contact, "Carol") == 0)
      {
        insertMessage(&headC, new);//If the contact of the message belongs to Carol, this function will insert the "new" struct into the linked list.
        countC++;
        printf("NotifyUser Carol\n");
      }
    }
    else if(strcmp(Operation, "OpenApp") == 0)//Checks if the operation is to open the app.
    {
      open = 1;//This is a flag used to tell if the app is open. It is used to prevent usage of the other operations if the app isnt open
      printf("OpenApp\n");
      printf("Alice %d\nBob %d\nCarol %d\n", countA, countB, countC);
    }
    else if(strcmp(Operation, "DisplayConversation") == 0 && open == 1)//Checks if the operation is to display a conversation and if the app is open
    {
      fscanf(fp, "%s", name);//This line reads in the name of the person who's conversation will be displayed
      printf("DisplayConversation %s\n", name);
      if(strcmp(name, "Alice") == 0)
      {
        printMessage(&headA);//The printMessage function will print the linked list containing the messages between me and Alice (headA)
        countA = 0;//Sets the notification counter to zero when the message is displayed for each person
      }
      else if(strcmp(name, "Bob") == 0)
      {
        printMessage(&headB);//The printMessage function will print the linked list containing the messages between me and Bob (headB)
        countB = 0;
      }
      else if(strcmp(name, "Carol") == 0)
      {
        printMessage(&headC);//The printMessage function will print the linked list containing the messages between me and Carol (headC)
        countC = 0;
      }
    }
    else if(strcmp(Operation, "SendMessage") == 0 && open == 1)//Checks if the operation is to send a message and that the app is open
    {
      readText(&fp, &new);//This line reads in the message that will be sent to the contact
      printf("SendMessage %d %s %s\n", new.timeStamp, new.contact, new.Message);
      if(strcmp(new.contact, "Alice") == 0)
      {
        strcpy(new.contact, "Me");//Changes the name of the contact to "me" since the message is coming from me
        insertMessage(&headA, new);//This function sends the TEXT struct variable new to be inserted into the linked of Alice
        printMessage(&headA);//This line will display the conversation after the message was sent to each person
      }
      else if(strcmp(new.contact, "Bob") == 0)
      {
        strcpy(new.contact, "Me");
        insertMessage(&headB, new);//This function sends the TEXT struct variable new to be inserted into the linked of Bob
        printMessage(&headB);
      }
      else if(strcmp(new.contact, "Carol") == 0)
      {
        strcpy(new.contact, "Me");
        insertMessage(&headC, new);//This function sends the TEXT struct variable new to be inserted into the linked of Carol
        printMessage(&headC);
      }
    }
    else if(strcmp(Operation, "DeleteMessage") == 0 && open == 1)//Checks if the operation is to delete a message and that the app is open
    {
      fscanf(fp, "%d", &del.timeStamp);//Lines 144-145 are meant to read the time stamp and name of the person of the message we will be removing
      fscanf(fp, "%s", del.contact);
      printf("DeleteMessage %d %s\n", del.timeStamp, del.contact);
      if(strcmp(del.contact, "Alice") == 0)
      {
        deleteMessage(&headA, del);//This function sends the TEXT struct variable "del" into itself so that the function will know what to remove from the linked list for Alice
        printMessage(&headA);//This line will display the conversation after the message is removed from the linked list
      }
      else if(strcmp(del.contact, "Bob") == 0)
      {
        deleteMessage(&headB, del);//This function sends the TEXT struct variable "del" into itself so that the function will know what to remove from the linked list for Bob
        printMessage(&headB);
      }
      else if(strcmp(del.contact, "Carol") == 0)
      {
        deleteMessage(&headC, del);//This function sends the TEXT struct variable "del" into itself so that the function will know what to remove from the linked list for Carol
        printMessage(&headC);
      }
    }
    else if(strcmp(Operation, "CloseApp") == 0)//Checks if the operation is to close the app
    {
      open = 0;//Changes the "open" flag to 0 from 1 to signify the app is closed
      printf("CloseApp\n");
    }
    fscanf((FILE*)fp, "%s", Operation);//This line is here to prevent the loop from ending before it gets to read the last operation of the file. In this case its CloseApp
  }

  if(strcmp(Operation, "CloseApp") == 0)//Since the operation CloseApp was scanned right before the loop ended, this line gives it a chance to execute the operation.
    {
      open = 0;
      printf("CloseApp\n");
    }

  fclose(fp);//This line closes the file once we are done with it.

  return 0;//Returns 0 because main function is expecting an integer
}

void readText(FILE **fp, TEXT *new)
{
  fscanf((*fp), "%d", &(new->timeStamp));//Lines 184-186 are reading in the information from the file that will be added into the TEXT struct variable "new"
  fscanf((*fp), "%s", new->contact);
  fgets(new->Message, 255, (*fp));//I used fgets instead of fscanf here becuase I wanted to read the entire message while ignoring while including the spaces

  int i = strlen(new->Message) - 1;//This is the index of the last character read in by fgets into new->Message; This is to get rid of the /n and /r characters at the end of the string
  while(isspace(new->Message[i]))//Checks to see if the character at the index is a space: '/n' or ' ' or '\r'
  {
    i--;//Decrements the index and will repeat until it reaches the last alphabetical character in the string
  }
  new->Message[i+1] = '\0';//Appends the NULL character to end of the string to get rid of the space characters
}

void insertMessage(TEXT **headP, TEXT new)
{
  TEXT *newText = (TEXT*) malloc(sizeof(TEXT));//This line allocates the memeory needed for a node into the pointer "newText"
  newText->timeStamp = new.timeStamp;//Lines 199-202 inputs the data from "new" into "newText" to be added to the linked list
  strcpy(newText->contact, new.contact);
  strcpy(newText->Message, new.Message);
  newText->next = NULL;
  TEXT *tempText;//This line declares a temporary pointer that will be used to traverse the linked list


  if(*headP == NULL)//Lines 206-209 checks to see if the linked list has been created. If not, it will set head to the new node
  {
      *headP = newText;
    (*headP)->next = NULL;
  }
  else
  {
    if(newText->timeStamp < (*headP)->timeStamp)//Checks to see if the timeStamp of newText is older than the timeStamp of the first message
    {
    newText->next = *headP;//Lines 215-216 add the new message before the head message and sets the new message as the new head
    *headP = newText;
    }

      else if(newText->timeStamp > (*headP)->timeStamp && (*headP)->next == NULL)//Checks if the timeStamp of new is newer than the head and that head is the only node
      {
        (*headP)->next = newText;//Adds the new message after the head message
      }
      else
      {
        tempText = *headP;//Sets tempText to the head to begin traversing the linked list
        while(tempText->next != NULL && tempText->next->timeStamp < newText->timeStamp)//Will traverse the linked list until tempText reaches the last node and also checks if the timeStamp of newText is newer than the tempText timeStamp
        {
            tempText = tempText->next;
        }
        newText->next = tempText->next;//Lines 230-231 add the node to wear it belongs on the list based on the order of the timeStamps
        tempText->next = newText;
      }
  }
}

void printMessage(TEXT **headP)
{
  if(*headP == NULL)//Checks if there are any messages to be displayed in the linked list
  {
    return;
  }
  else if((*headP)->next == NULL)//Prints the infomration of head if there are no other messages in the linked list
  {
    printf("%d %s %s\n", (*headP)->timeStamp, (*headP)->contact, (*headP)->Message);
  }
  else
  {
    TEXT *temp = *headP;//Sets temp to the head of the linked list to begin traversing the list
    while(temp->next != NULL)//Lines 249-252 will keep on repeating until temp reaches the last node;
    {
      printf("%d %s %s\n", temp->timeStamp, temp->contact, temp->Message);
      temp = temp->next;
    }
    printf("%d %s %s\n", temp->timeStamp, temp->contact, temp->Message);//Prints the last message of the linked list since the loop ended when it reached the last node and did not get to execute the operation
  }
}

void deleteMessage(TEXT **headP, TEXT del)
{
  TEXT *temp = *headP;//Sets temp to the head message of the linked list to traverse the list
  TEXT *tempDel;//Will be used to store the message that will be freed so that it si not lost in memeory

  if(*headP == NULL)//Checks to see if there are any messages in the linked list
  {
    return;
  }
  else if((*headP)->timeStamp == del.timeStamp)//Lines 263-266 check to see if the head message is the one to be deleted and sets the head pointer to the next one
  {
    *headP = (*headP)->next;
    free(temp);//Deallocates the memory of the old head message
  }
  else
  {
    while(temp->next != NULL)//Will keep looping until temp reaches the last node
    {
      if(temp->next->timeStamp == del.timeStamp)//Checks to see if the timeStamp of the message after the message temp is pointing to see if it is the one to be deleted
      {
        tempDel = temp->next;//Lines 274-276 stores the message with the timeStamp to be deleted, sets that message to the next one in the linked list than deallocates the message
        temp->next = temp->next->next;
        free(tempDel);
      }
      else
      {
        temp = temp->next;//Traverses the linked list
      }
    }
  }
}
