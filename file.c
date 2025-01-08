#include <stdio.h>
#include<stdlib.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook) {
  FILE *f1ptr;
  f1ptr = fopen("contacts.csv","w");
  puts("opened file");
  for(int i=0;i<addressBook->contactCount;i++)
  {
    printf("%s,%s,%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    fprintf(f1ptr,"%s,%s,%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    puts("saved 1 contact");
  }
  fclose(f1ptr);
  puts("file closed");
  exit(0);
}

void loadContactsFromFile(AddressBook *addressBook) {
        
    FILE *fptr; 
    fptr = fopen("contacts.csv","r");
    
    ///  checking if the file is empty or not 

    fseek(fptr,0,SEEK_END);
    if(!ftell(fptr))
    {
        return ;
    }
    fseek(fptr,0,SEEK_SET);
    /////////////////////////////////////////

    while(!feof(fptr))
    {
        int i = addressBook->contactCount;
        fscanf(fptr,"%[^,],%[^,],%[^\n]\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
        addressBook->contactCount++;
    }
    fclose(fptr);
}
