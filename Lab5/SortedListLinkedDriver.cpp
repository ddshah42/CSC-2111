#include "SortedListLinked.h"
#include "CD.h"
using CSC2110::CD;
#include "ListArray.h"
using CSC2110::ListArray;
#include "ListArrayIterator.h"
using CSC2110::ListArrayIterator;
#include <iostream>
using namespace std;

void addCDs(ListArray<CD>* list, SortedListLinked<CD>* lb)
{
   ListArrayIterator<CD>* iter = list->iterator();

   //DO THIS
   //iterate over and add the cds to the list box (use lb->addItem)
	while(iter->hasNext())
	{
		CD* cd = iter->next();
		lb->add(cd);
	}
   delete iter;
}

void deleteCDs(ListArray<CD>* list)
{
   ListArrayIterator<CD>* iter = list->iterator();

   //DO THIS  
   //iterate over and delete the cds
	while(iter->hasNext())
	{
		CD* cd = iter->next();
		delete cd;
	}

   delete iter;
}

int main(int argc, char* argv[])
{
   ListArray<CD>* cds = CD::readCDs("cds.txt");
   //DO THIS
   //create and test the sorted linked list 
   SortedListLinked<CD>* list = new SortedListLinked<CD>(&CD::compare_items);
   addCDs(cds, list);
   ListLinkedIterator<CD>* iter = list->iterator();
   while(iter->hasNext())
   {
	   iter->next()->displayCD();
   }
   
   cout << "Post-Removal \n\n\n" << endl;
   //Just going to remove these CDs from cds, which are "Waiting for the end to come" and "Omnivium"
   list->remove(cds->get(1));
   list->remove(cds->get(3));
   iter = list->iterator();
   while(iter->hasNext())
   {
	   iter->next()->displayCD();
   }
   
   //Literally just to keep the prompt open, shouldn't really reflect any part of our grade.
   //Can just close prompt once done reading, but also could have made like a readString that waited for input before closing
   deleteCDs(cds);
   bool dontStop = 1;
   while(dontStop){
	   dontStop = 1;
   }
   
   return 0;
}
