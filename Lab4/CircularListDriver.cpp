#include "CircularList.h"
#include "CD.h"
#include "ListArray.h"
#include "ListArrayIterator.h"
using namespace CSC2110;

#include <iostream>
using namespace std;

void addCDs(ListArray<CD>* list, CircularList<CD>* cl)
{
   ListArrayIterator<CD>* iter = list->iterator();

   while(iter->hasNext())
   {
      CD* cd = iter->next();
      cl->add(cd);
   }

   delete iter;
}

void deleteCDs(ListArray<CD>* list)
{
   ListArrayIterator<CD>* iter = list->iterator();

   while(iter->hasNext())
   {
      CD* cd = iter->next();
      delete cd;
   }

   delete iter;
}

int main()
{
   ListArray<CD>* cds = CD::readCDs("cds.txt");

   CircularList<CD>* circ_list = new CircularList<CD>();
   addCDs(cds, circ_list);
   //cl->remove(5);

cout << circ_list->size() << endl;
   CircularListIterator<CD>* iter = circ_list->iterator();
   while(iter->hasNext())
   {
      CD* cd = iter->next();
      cd->displayCD();
   }
   delete iter;

   deleteCDs(cds);
   delete cds;
   delete circ_list;

   return 0;
}
