#include <stdio.h>
#include<stdlib.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook) {
  FILE *f1ptr;
  f1ptr = fopen("contacts.csv","w");
  puts("opened file");
  for(int i=0;i<addressBook->contactCount;i++)
  {
    fprintf(f1ptr,"%s,%s,%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
  }
  fclose(f1ptr);
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
