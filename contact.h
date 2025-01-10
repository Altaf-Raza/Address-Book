#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100

typedef struct {
    char name[50];
    char phone[20];
    char email[50];
} Contact;

typedef struct {
    Contact contacts[100];
    int contactCount;
} AddressBook;

void createContact(AddressBook *addressBook);
void searchContact(AddressBook *addressBook);
void editContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
void listContacts(AddressBook *addressBook);
void initialize(AddressBook *addressBook);
void saveContactsToFile(AddressBook *addressBook);

int isValidPhoneNumber(const char* temp_phone);
int isDuplicatePhone(AddressBook* addressBook, char* temp_phone);
int isValidEmail(const char* temp_mail);
int isDuplicateEmail(AddressBook* addressBook,const char* temp_mail);
void addContact(AddressBook *addressBook, const char *name, const char *phone, const char *email);
void searchAndPrint(AddressBook* addressBook,const char* query,int choice);
void searchAndDelete(AddressBook* addressBook,const char* query,int choice);
void loadContactsFromFile(AddressBook*addressBook);

#endif
