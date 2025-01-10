#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "populate.h"
#include<ctype.h>

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    loadContactsFromFile(addressBook);
    if(addressBook->contactCount==0)
    {
      populateAddressBook(addressBook);
    }
}

void loadContactsFromFile(AddressBook*addressBook)
{
    char name[50],mobile[20],email[20];
    FILE*file=fopen("contact.csv","r");
    if(file==NULL)
    {
        printf("File doesn't esxist\n");
        return ;

    }
    
    while((fscanf(file,"%49[^,],%19[^,],%49[^\n]\n",name,mobile,email)==3))
    {
        strcpy(addressBook->contacts[addressBook ->contactCount].name,name);
        strcpy(addressBook->contacts[addressBook-> contactCount].phone,mobile);
        strcpy(addressBook->contacts[addressBook->contactCount].email,email);
        
        addressBook->contactCount ++; 
    }
    fclose(file);
}

void saveContactsToFile(AddressBook *addressBook)
{
 FILE* file=fopen("contact.csv" ,"w");
    int i;
    if(file==NULL)
    {
        printf("File does not exist");
        return;
    }
    
   // fprintf(file,"#%d\n",addressBook->contactCount);
    for(i=0;i< addressBook->contactCount;i++)
    {
         fprintf(file,"%s,%s,%s\n",addressBook ->contacts[i].name,addressBook ->contacts[i].phone,addressBook ->contacts[i].email);
     
    }
    fclose(file);
    printf("Saved successfully to file\n");
}

void listContacts(AddressBook *addressBook) 
{
    for(int i=0;i<addressBook->contactCount;i++)
    {
        printf("%s %s %s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
}
void createContact(AddressBook *addressBook)
{
    char temp_name[50], temp_phone[12], temp_mail[50];;
    printf("Enter the name:\n");
    scanf(" %[^\n]",temp_name);
    int flag=0;
    while(flag==0)
    {
        printf("Enter the phone number:\n");
        scanf(" %[0-9]",temp_phone);
        if (!isValidPhoneNumber(temp_phone) || isDuplicatePhone(addressBook, temp_phone))
        {
            flag=0;
            printf("Re-");
        }
        else
        {
            flag=1;
        }
    }
    
    flag=0;
    while(flag==0)
    {
        printf("Enter the Email id:\n");
        scanf(" %[^\n]",temp_mail);
        if (!isValidEmail(temp_mail) || isDuplicateEmail(addressBook, temp_mail))
         {
            flag=0;
            printf("Re-");
        }
        else
        {
            flag=1;
        }
    }
   
    addContact(addressBook,temp_name,temp_phone,temp_mail);   
}

void searchContact(AddressBook *addressBook) 
{
    int choice;
    char query[50];
    do
    {
        printf("1. Search by Name\n2. Search by Phone\n3. Search by Email\n4. Exit\nEnter your choice: ");
        scanf("%d", &choice);
        if(choice>4 || choice<1)printf("Invalid choice, please Try Again\n");
    }while(choice<1 || choice>4);
    if(choice==4) return;
    printf("Enter the search query: ");
    scanf(" %[^\n]", query);

    searchAndPrint(addressBook, query, choice);

}

void editContact(AddressBook *addressBook)
{
    char query[50];
    int choice;

    printf("Enter the name, phone number, or email of the contact to edit: ");
    scanf(" %[^\n]", query);

    int index = -1;
    for (int i = 0; i < addressBook->contactCount; i++) {
        if (strcmp(query, addressBook->contacts[i].name) == 0 ||
            strcmp(query, addressBook->contacts[i].phone) == 0 ||
            strcmp(query, addressBook->contacts[i].email) == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("No matching contact found.\n");
        return;
    }

    // Display current contact details
    printf("Editing Contact: %s %s %s\n", 
           addressBook->contacts[index].name, 
           addressBook->contacts[index].phone, 
           addressBook->contacts[index].email);

    // Choose field to edit
    do{
    printf("1. Edit Name\n2. Edit Phone\n3. Edit Email\n4. Cancel\nEnter your choice: ");
    scanf("%d", &choice);
    if(choice<1 || choice>4)printf("Invalid choice, Try Again!\n");
    }while(choice<1 || choice>4);
       
    char newValue[50];
    switch (choice) {
        case 1: // Edit Name
            printf("Enter the new name: ");
            scanf(" %[^\n]", newValue);
            strcpy(addressBook->contacts[index].name, newValue);
            printf("Name updated successfully.\n");
            break;
        case 2: // Edit Phone
            int flag=0;
            while(flag==0)
            {
                printf("Enter the new phone number: ");
                scanf(" %[^\n]", newValue);
                if (!isValidPhoneNumber(newValue) || isDuplicatePhone(addressBook, newValue))
                {
                    flag=0;
                    printf("Re-");
                }
                else
                {
                    flag=1;
                }  
            }
            strcpy(addressBook->contacts[index].phone, newValue);
            printf("Phone number updated successfully.\n");
            break;
        case 3: // Edit Email
            flag=0;
            while(flag==0)
            {
              printf("Enter the new email: ");
              scanf(" %[^\n]", newValue);
              if (!isValidEmail(newValue) || isDuplicateEmail(addressBook, newValue))
                {
                    flag=0;
                    printf("Re-");
                }
                else
                {
                    flag=1;
                }  
            }
            strcpy(addressBook->contacts[index].email, newValue);
            printf("Email updated successfully.\n");
            break;
        case 4: // Cancel
            printf("Edit operation canceled.\n");
            return;
        default:
            printf("Invalid choice.\n");
            return;
    }
    
}

void deleteContact(AddressBook *addressBook)
{
	int choice;
    char query[50];
    do{
       printf("1. Delete by Name\n2. Delete by Phone\n3. Delete by Email\n4. Exit\nEnter your choice: ");
       scanf("%d", &choice);
       if(choice>4 || choice<1)printf("Invalid choice, please Try Again\n");
    }while(choice<1 || choice>4);

    if(choice==4) return;
    printf("Enter the search query: ");
    scanf(" %[^\n]", query);

    searchAndDelete(addressBook, query, choice);
}       
int isValidPhoneNumber(const char* temp_phone)
{
    if((strlen(temp_phone)!=10))
    {
        printf("Phone number should be 10 digit\n");
        return 0;
    }
    return 1;
}
int isDuplicatePhone(AddressBook* addressBook, char* temp_phone)
{
    for(int i=0;i<addressBook->contactCount;i++)
    {
        if(strcmp(temp_phone,addressBook->contacts[i].phone)==0)
        {
            printf("This number already exist\n");
            return 1;
        }
    }
    return 0;
}
int isValidEmail(const char* temp_mail)
{
    int atcount=0, dotcount=0, atposition=0, dotposition=0;
    for(int i=0;temp_mail[i]!=0;i++)
    {
        if(temp_mail[i]=='@')
        {
            atcount++;
            atposition=i;
        }
        else if(temp_mail[i]=='.')
        {
            dotcount++;
            dotposition=i;
        }
       else if(!(isalnum(temp_mail[i])) && temp_mail[i]!='-' && temp_mail[i] != '_')
       {
        printf("Invalid email: Contains invalid characters.\n");
        return 0;
       }
    }

    if (atcount != 1 || dotcount < 1 || (dotposition < atposition + 1) || temp_mail[0] == '@' || temp_mail[0] == '.' || temp_mail[strlen(temp_mail) - 1] == '@' || temp_mail[strlen(temp_mail) - 1] == '.') 
    {
        printf("Invalid email format.\n");
        return 0;
    }

    if(!strstr(temp_mail,"@gmail.com"))
    {
        printf("Email must end with '@gmail.com'.\n");
        return 0;
    }
    return 1;  
}
int isDuplicateEmail(AddressBook* addressBook,const char* temp_mail)
{
    for (int i = 0; i < addressBook->contactCount ; i++) 
    {
        if(strcmp(temp_mail, addressBook->contacts[i].email)==0)
        {
            printf("This Email Already Exist\n");
            return 1;
        }
    }
    return 0;  
}
void addContact(AddressBook *addressBook, const char *name, const char *phone, const char *email)
{
    strcpy(addressBook->contacts[addressBook->contactCount].name,name);
    strcpy(addressBook->contacts[addressBook->contactCount].phone,phone);
    strcpy(addressBook->contacts[addressBook->contactCount].email,email);
    addressBook->contactCount++;
    printf("Contact added successfully!\n");
}
void searchAndPrint(AddressBook* addressBook,const char* query,int choice)
{
    int found=0;
    for(int i=0;i< addressBook->contactCount;i++)
    {
        if((choice==1 && strcmp(query,addressBook->contacts[i].name)==0) ||
           (choice==2 && strcmp(query,addressBook->contacts[i].phone)==0)||
           (choice==3 && strcmp(query,addressBook->contacts[i].email)==0))
           {
             printf("%s %s %s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
             found=1;
           }
    }
    if(!found)
    {
        printf("Contact not found.\n");
    }
}
void searchAndDelete(AddressBook* addressBook,const char* query,int choice)
{
    for(int i=0;i< addressBook->contactCount;i++)
    {
        if((choice==1 && strcmp(query,addressBook->contacts[i].name)==0) ||
           (choice==2 && strcmp(query,addressBook->contacts[i].phone)==0)||
           (choice==3 && strcmp(query,addressBook->contacts[i].email)==0))
        {
            for(int j=i;j<addressBook->contactCount;j++)
            {
                addressBook->contacts[j]=addressBook->contacts[j+1];   
            }
            addressBook->contactCount--;
            printf("Contact deleted successfully.\n");
            return;
        }
    }      
    printf("Contact not found.\n");   
}
