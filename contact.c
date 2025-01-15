#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

//////////////////////////*                    PRINT FUNCTIONS                       *//////////////////////////////////////////////


void print_contact(int index,AddressBook *addressBook)
{
    printf("\nName : %s",addressBook->contacts[index].name);
    printf("\t\t\tPhone Number : %s",addressBook->contacts[index].phone);
    printf("\t\t\tEmail : %s\n",addressBook->contacts[index].email);

}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////*                     SORT FUNCTIONS                        */////////////////////////////////////////////

void sortname(AddressBook *addressBook)
{
    for(int i=0;i<addressBook->contactCount-1;i++)
    {
        for(int j=0;j<addressBook->contactCount-i-1;j++)
        {
            if(strcmp(addressBook->contacts[j].name,addressBook->contacts[j+1].name)>0)
            {
                Contact temp = addressBook->contacts[j];
                addressBook->contacts[j] = addressBook->contacts[j+1];
                addressBook->contacts[j+1] = temp;
            }
        }
    }
}

void sortphone(AddressBook *addressBook)
{
    for(int i=0;i<addressBook->contactCount-1;i++)
    {
        for(int j=0;j<addressBook->contactCount-i-1;j++)
        {
            if(strcmp(addressBook->contacts[j].phone,addressBook->contacts[j+1].phone)>0)
            {
                Contact temp = addressBook->contacts[j];
                addressBook->contacts[j] = addressBook->contacts[j+1];
                addressBook->contacts[j+1] = temp;
            }
        }
    }
}

void sortmail(AddressBook *addressBook)
{
    for(int i=0;i<addressBook->contactCount-1;i++)
    {
        for(int j=0;j<addressBook->contactCount-i-1;j++)
        {
            if(strcmp(addressBook->contacts[j].email,addressBook->contacts[j+1].email)>0)
            {
                Contact temp = addressBook->contacts[j];
                addressBook->contacts[j] = addressBook->contacts[j+1];
                addressBook->contacts[j+1] = temp;
            }
        }
    }

}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void listContacts(AddressBook *addressBook, int sortCriteria) 
{
    // Sort contacts based on the chosen criteria
    printf("\nThere are %d contacts\n",addressBook->contactCount);
    switch(sortCriteria)
    {
        case 1: sortname(addressBook);
                for(int i =0;i<addressBook->contactCount;i++)
                {
                    print_contact(i,addressBook);
                }
                break;
        case 2: sortphone(addressBook);
                for(int i =0;i<addressBook->contactCount;i++)
                {
                    print_contact(i,addressBook);
                }
                break;
        case 3: sortmail(addressBook);
                for(int i =0;i<addressBook->contactCount;i++)
                {
                    print_contact(i,addressBook);
                }
                break;
        default:
                printf("\nenter a valid choice\n");
                break;
        
    }
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    //populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);

    //loadContactsFromFile(addressBook);
}


void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}




//////////////////////////*                    VALIDATE   FUNCTIONS                  */////////////////////////////////////////////

int unique_number(char *number,AddressBook *addressBook)
{
    int count = addressBook->contactCount;
    for(int i=0;i<count;i++)
    {
        if(strcmp(number,addressBook->contacts[i].phone)==0)
            return 1;
    }
    return 0;
}

int validate_number(char *number)
{
    int len = 0; 
   while(*number)
   {
        if(!isdigit(*number))
        {
            return 1; 
        }
        len ++ ;
        number++;
   }
return len==10?0:1;

}

int validate_name(char *name)
{
    while(*name)
    {
        if(*name!=' ')
        {
            if(!(isalpha(*name)))
            {
                return 1;
            }
        }
        name++;
    }
    return 0;
}

int unique_mail(char *mail,AddressBook *addressBook)
{
    int count = addressBook->contactCount; 
        for(int i = 0;i<count;i++)
        {
            if(strcmp(addressBook->contacts[i].email,mail)==0)
                return 1;   
        }
        return 0;
}

int validate_mail(char *mail)
{
    bool flag  = true;
    char av_mail[5][20] = {"@gmail.com","@hotmail.com","@yahoo.com","@outlook.com","@zoho.com"};
    for(int i=0;i<5;i++)
    {
        if(strstr(mail,av_mail[i]))
        {
            flag = false;
        }
    }
    return flag? 1:0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void createContact(AddressBook *addressBook)
{
	/* Define the logic to create a Contacts */
    char name[30];
    printf("Enter name : ");
    scanf(" %[^\n]",name);
    while(validate_name(name))
    {
        printf("\nValidation Failed. Enter a valid name\n");
        printf("\nEnter name : ");
        scanf(" %[^\n]",name);
    }


    char number[11];
    printf("\nEnter Phone Number : ");
    scanf(" %[^\n]",number);
    while(validate_number(number))
    {
        printf("\nValidation Failed. Enter a valid Number\n");
        printf("\nEnter Phone Number : ");
        scanf(" %[^\n]",number);

    }

    while(unique_number(number,addressBook))
    {   
        printf("\nNumber already exists input another number\n");
        printf("\nEnter Phone Number : ");
        scanf(" %[^\n]",number);
    }

    char mail[50];
    printf("\nEnter the Mail id : ");
    scanf(" %[^\n]",mail);
    while(validate_mail(mail))
    {
        printf("\nValidation Failed. Enter valid email\n");
        printf("\nEnter the Mail id : ");
        scanf(" %[^\n]",mail);
    }
    while(unique_mail(mail,addressBook))
    {
        printf("\nEmail already exists. Please Enter another email\n");
        scanf(" %[^\n]",mail);

    }
    int index = addressBook->contactCount;
    strcpy(addressBook->contacts[index].name,name);
    strcpy(addressBook->contacts[index].phone,number);
    strcpy(addressBook->contacts[index].email,mail);
    addressBook->contactCount++ ;


}

int search_name(char *str,AddressBook *addressBook)
{
    int count = addressBook->contactCount;
    for(int i=0;i<count;i++)
    {
        if(strcmp(str,addressBook->contacts[i].name)==0)
        {
            return i;
        }
    }
    printf("\nName not Found.  Enter an existing name\n");
    return -1;
}
int search_number(char *str,AddressBook *addressBook)
{
    int count = addressBook->contactCount;
    for(int i=0;i<count;i++)
    {
        if(strcmp(str,addressBook->contacts[i].phone)==0)
        {
            return i;
        }
    }
    printf("\nNumber not Found.  Enter an existing Number\n");
    return -1;
}
int search_mail(char *str,AddressBook *addressBook)
{
    int count = addressBook->contactCount;
    for(int i=0;i<count;i++)
    {
        if(strcmp(str,addressBook->contacts[i].email)==0)
        {
            return i;
        }
    }
    printf("\nMail not Found.  Enter an existing Mail\n");
    return -1;
}

int searchContact(AddressBook *addressBook)
{
    /* Define the logic for search */
    printf("Search by : \n");
    label1 :
    printf("1.Name\n2.Phone Number\n3.Email id\nEnter your choice : ");
    int choice;
    while(getchar()!='\n');
    scanf("%d",&choice);
    char str[50];
    int index;
    switch(choice)
    {
        case 1 :
                do
                { 
                    printf("\n Enter Name : ");
                    scanf(" %[^\n]",str);   
                    index = search_name(str,addressBook);
                }
                while(index==-1);
                break;
        case 2 : 
                do
                {
                    printf("\nEnter Phone NUmber : ");
                    scanf(" %[^\n]",str);   
                    index = search_number(str,addressBook);
                }
                while (index==-1);
                break;
        case 3 :
                do
                {
                    printf("\nEnter Email id : ");
                    scanf(" %[^\n]",str);   
                    index = search_mail(str,addressBook);
                }
                while (index==-1);
                break;
        default:
                printf("\nEnter a valid choice\n");
                goto label1;
                
    }
    print_contact(index,addressBook);
    return index ; 
    
}

void editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */
    printf("\nFor editing ");
    int index  = searchContact(addressBook);
    printf("\nSelect option for Edit : ");
    printf("1.Name\n2.Phone Number\n3.Email id\nEnter your choice : ");
    int choice;
    char str[50];
    do
    {
        scanf("%d",&choice);
        switch(choice)
        {
            case 1 :
                    printf("\nEnter the new name : ");
                    scanf(" %[^\n]",str);
                    while(validate_name(str))
                    {
                        printf("\nEnter Valid name : \n");
                        scanf(" %[^\n]",str);
                    }
                    strcpy(addressBook->contacts[index].name,str);
                    break;

            case 2 :
                    printf("\nEnter the new phone number : ");
                    scanf(" %[^\n]",str);
                    while(validate_number(str))
                    {
                        printf("\nEnter Valid number : \n");
                        scanf(" %[^\n]",str);
                    }
                    while(unique_number(str,addressBook))
                    {
                        printf("\nEmail already exists. Please Enter another email\n");
                        scanf(" %[^\n]",str);

                    }
                    strcpy(addressBook->contacts[index].phone,str);
                    break;
            case 3 :
                    printf("\nEnter the new email id : ");
                    scanf(" %[^\n]",str);
                    while(validate_mail(str))
                    {
                        printf("\nEnter Valid email id : \n");
                        scanf(" %[^\n]",str);
                    }
                    while(unique_mail(str,addressBook))
                    {
                        printf("\n Mail already exists. Please Enter another email\n");
                        scanf(" %[^\n]",str);

                    }
                    strcpy(addressBook->contacts[index].email,str);
                    break;
            default:
                    printf("\nEnter valid choice\n");
        }
    } while (choice<1 && choice>3);
    printf("\nAfter editing The contact is ");
    print_contact(index,addressBook);
    

}

void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */
    printf("For deleting ");
    int index = searchContact(addressBook);
    char ch; 
    printf("\n  ARE YOU SURE YOU WANT TO DELETE THE CONTACT ? IF YES PRESS 'Y' ");
    scanf(" %c",&ch);
    if(tolower(ch)!='y')return;
    for(int i=index;i<addressBook->contactCount-1;i++)
    {
        addressBook->contacts[i]=addressBook->contacts[i+1];
    }
    addressBook->contactCount--;
    printf("\ndeleted the contact \n");
   
}
