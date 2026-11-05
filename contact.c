#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define CONTACT_FILE "contacts.dat"
#define MAX_CONTACTS 200

/* ============================================================
   DATA STRUCTURE
   ============================================================ */

typedef struct
{
    int id;
    char name[50];
    char phone[20];
    char email[60];
    char address[100];
} Contact;


/* ============================================================
   GLOBAL DATA
   ============================================================ */

Contact contacts[MAX_CONTACTS];
int contactCount = 0;


/* ============================================================
   FILE HANDLING
   ============================================================ */

void loadContacts()
{
    FILE *fp = fopen(CONTACT_FILE, "rb");

    if (fp == NULL)
    {
        contactCount = 0;
        return;
    }

    fread(&contactCount, sizeof(int), 1, fp);
    fread(contacts, sizeof(Contact), contactCount, fp);

    fclose(fp);
}


void saveContacts()
{
    FILE *fp = fopen(CONTACT_FILE, "wb");

    if (fp == NULL)
    {
        printf("Error saving contact file!\n");
        return;
    }

    fwrite(&contactCount, sizeof(int), 1, fp);
    fwrite(contacts, sizeof(Contact), contactCount, fp);

    fclose(fp);
}


/* ============================================================
   UTILITY FUNCTIONS
   ============================================================ */

int nextContactId()
{
    int i;
    int max = 0;

    for (i = 0; i < contactCount; i++)
    {
        if (contacts[i].id > max)
        {
            max = contacts[i].id;
        }
    }

    return max + 1;
}


int findContactIndex(int id)
{
    int i;

    for (i = 0; i < contactCount; i++)
    {
        if (contacts[i].id == id)
        {
            return i;
        }
    }

    return -1;
}

/* Helper function: Case-insensitive prefix match */
int startsWith(const char *str, const char *prefix)
{
    size_t len_prefix = strlen(prefix);
    size_t len_str = strlen(str);

    if (len_prefix > len_str)
        return 0;

    for (size_t i = 0; i < len_prefix; i++)
    {
        if (tolower((unsigned char)str[i]) != tolower((unsigned char)prefix[i]))
            return 0;
    }
    return 1;
}


/* ============================================================
   MODULE 1: ADD CONTACT
   ============================================================ */

void addContact()
{
    Contact c;

    if (contactCount >= MAX_CONTACTS)
    {
        printf("\nContact list is full!\n");
        return;
    }

    c.id = nextContactId();

    printf("\n========== ADD CONTACT ==========\n");

    printf("Enter name: ");
    scanf(" %[^\n]", c.name);

    printf("Enter phone number: ");
    scanf(" %[^\n]", c.phone);

    printf("Enter email: ");
    scanf(" %[^\n]", c.email);

    printf("Enter address: ");
    scanf(" %[^\n]", c.address);

    contacts[contactCount] = c;
    contactCount++;

    saveContacts();

    printf("\nContact added successfully!\n");
    printf("Contact ID: %d\n", c.id);
}


/* ============================================================
   MODULE 6: SORT CONTACTS (Declared before displayContacts)
   ============================================================ */

void sortContacts()
{
    int i, j;
    Contact temp;

    if (contactCount == 0)
    {
        return;
    }

    for (i = 0; i < contactCount - 1; i++)
    {
        for (j = i + 1; j < contactCount; j++)
        {
            if (strcmp(contacts[i].name, contacts[j].name) > 0)
            {
                temp = contacts[i];
                contacts[i] = contacts[j];
                contacts[j] = temp;
            }
        }
    }

    saveContacts();
}


/* ============================================================
   MODULE 2: DISPLAY CONTACTS
   ============================================================ */

void displayContacts()
{
    int i;

    if (contactCount == 0)
    {
        printf("\n================ CONTACT LIST ================\n");
        printf("No contacts available.\n");
        return;
    }

    /* Automatically sort contacts alphabetically before displaying */
    sortContacts();

    printf("\n================ CONTACT LIST ================\n");
    printf("%-5s %-20s %-15s %-25s %-30s\n",
           "ID", "Name", "Phone", "Email", "Address");

    printf("------------------------------------------------------------------------------------------\n");

    for (i = 0; i < contactCount; i++)
    {
        printf("%-5d %-20s %-15s %-25s %-30s\n",
               contacts[i].id,
               contacts[i].name,
               contacts[i].phone,
               contacts[i].email,
               contacts[i].address);
    }

    printf("==========================================================================================\n");
}


/* ============================================================
   MODULE 3: SEARCH CONTACT
   ============================================================ */

void searchContact()
{
    int choice;
    int id;
    int i;
    char name[50];
    int found = 0;

    printf("\n========== SEARCH CONTACT ==========\n");
    printf("1. Search by ID\n");
    printf("2. Search by Name Prefix\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    if (choice == 1)
    {
        printf("Enter Contact ID: ");
        scanf("%d", &id);

        i = findContactIndex(id);

        if (i == -1)
        {
            printf("\nContact not found.\n");
            return;
        }

        printf("\nContact Found!\n");
        printf("ID      : %d\n", contacts[i].id);
        printf("Name    : %s\n", contacts[i].name);
        printf("Phone   : %s\n", contacts[i].phone);
        printf("Email   : %s\n", contacts[i].email);
        printf("Address : %s\n", contacts[i].address);
    }
    else if (choice == 2)
    {
        printf("Enter starting letters to search: ");
        scanf(" %[^\n]", name);

        for (i = 0; i < contactCount; i++)
        {
            /* Uses prefix matching instead of substring search */
            if (startsWith(contacts[i].name, name))
            {
                printf("\nContact Found!\n");
                printf("ID      : %d\n", contacts[i].id);
                printf("Name    : %s\n", contacts[i].name);
                printf("Phone   : %s\n", contacts[i].phone);
                printf("Email   : %s\n", contacts[i].email);
                printf("Address : %s\n", contacts[i].address);

                found = 1;
            }
        }

        if (!found)
        {
            printf("\nNo contact found starting with '%s'.\n", name);
        }
    }
    else
    {
        printf("Invalid choice.\n");
    }
}


/* ============================================================
   MODULE 4: MODIFY CONTACT
   ============================================================ */

void modifyContact()
{
    int id;
    int index;
    int choice;

    printf("\n========== MODIFY CONTACT ==========\n");

    printf("Enter Contact ID: ");
    scanf("%d", &id);

    index = findContactIndex(id);

    if (index == -1)
    {
        printf("Contact not found.\n");
        return;
    }

    printf("\nCurrent Contact Details:\n");
    printf("Name    : %s\n", contacts[index].name);
    printf("Phone   : %s\n", contacts[index].phone);
    printf("Email   : %s\n", contacts[index].email);
    printf("Address : %s\n", contacts[index].address);

    printf("\nWhat would you like to modify?\n");
    printf("1. Name\n");
    printf("2. Phone\n");
    printf("3. Email\n");
    printf("4. Address\n");
    printf("5. All Details\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
        case 1:
            printf("Enter new name: ");
            scanf(" %[^\n]", contacts[index].name);
            break;

        case 2:
            printf("Enter new phone number: ");
            scanf(" %[^\n]", contacts[index].phone);
            break;

        case 3:
            printf("Enter new email: ");
            scanf(" %[^\n]", contacts[index].email);
            break;

        case 4:
            printf("Enter new address: ");
            scanf(" %[^\n]", contacts[index].address);
            break;

        case 5:
            printf("Enter new name: ");
            scanf(" %[^\n]", contacts[index].name);

            printf("Enter new phone number: ");
            scanf(" %[^\n]", contacts[index].phone);

            printf("Enter new email: ");
            scanf(" %[^\n]", contacts[index].email);

            printf("Enter new address: ");
            scanf(" %[^\n]", contacts[index].address);
            break;

        default:
            printf("Invalid choice.\n");
            return;
    }

    saveContacts();

    printf("\nContact updated successfully!\n");
}


/* ============================================================
   MODULE 5: DELETE CONTACT
   ============================================================ */

void deleteContact()
{
    int id;
    int index;
    int i;

    printf("\n========== DELETE CONTACT ==========\n");

    printf("Enter Contact ID: ");
    scanf("%d", &id);

    index = findContactIndex(id);

    if (index == -1)
    {
        printf("Contact not found.\n");
        return;
    }

    printf("\nContact: %s\n", contacts[index].name);

    for (i = index; i < contactCount - 1; i++)
    {
        contacts[i] = contacts[i + 1];
    }

    contactCount--;

    saveContacts();

    printf("Contact deleted successfully!\n");
}


/* ============================================================
   MODULE 7: COUNT CONTACTS
   ============================================================ */

void countContacts()
{
    printf("\n========== CONTACT SUMMARY ==========\n");
    printf("Total number of contacts: %d\n", contactCount);
}


/* ============================================================
   MAIN MENU
   ============================================================ */

void printMainMenu()
{
    printf("\n=============================================\n");
    printf("        CONTACT MANAGEMENT SYSTEM\n");
    printf("=============================================\n");
    printf(" 1. Add Contact\n");
    printf(" 2. Display Contacts\n");
    printf(" 3. Search Contact\n");
    printf(" 4. Modify Contact\n");
    printf(" 5. Delete Contact\n");
    printf(" 6. Sort Contacts\n");
    printf(" 7. Count Contacts\n");
    printf(" 8. Save Contacts\n");
    printf(" 0. Exit\n");
    printf("=============================================\n");
    printf("Enter your choice: ");
}


/* ============================================================
   MAIN FUNCTION
   ============================================================ */

int main()
{
    int choice;

    loadContacts();

    printf("\n*************************************************\n");
    printf("*        WELCOME TO CONTACT MANAGEMENT SYSTEM    *\n");
    printf("*************************************************\n");

    do
    {
        printMainMenu();
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                addContact();
                break;

            case 2:
                displayContacts();
                break;

            case 3:
                searchContact();
                break;

            case 4:
                modifyContact();
                break;

            case 5:
                deleteContact();
                break;

            case 6:
                sortContacts();
                printf("\nContacts sorted alphabetically by name.\n");
                break;

            case 7:
                countContacts();
                break;

            case 8:
                saveContacts();
                printf("Contacts saved successfully.\n");
                break;

            case 0:
                saveContacts();
                printf("\nExiting... All contacts have been saved.\n");
                break;

            default:
                printf("\nInvalid choice. Please try again.\n");
        }

    } while (choice != 0);

    printf("\nThank you for using Contact Management System!\n");

    return 0;
}