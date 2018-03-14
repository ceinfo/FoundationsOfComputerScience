//  main.cpp
//  CS5403-Hw4
//  Catherine Eng - ce2086@nyu.edu
//  Includes linked list as array and double linked list

#include <iostream>

using namespace std;

struct NODE {
    int val;
    NODE *prev;
    NODE *next;
};

void arrayLinkedList();
void printElementsInSet(int arr[], int pos[], int prev[], int size, string elemText);
void linkedSetupMembers();
void linkedPrintMembers(NODE *ptr);
void linkedInsertMembers(NODE* &ptr, int val);
void linkedDeleteMembers(NODE* &ptr, NODE* &head);


int main(int argc, const char * argv[])
{
    //Hw#4,  Problem 6a - eliminate members from array simulated as double linked list
    arrayLinkedList();
    
    //Hw#4,  Problem 6b - eliminate members from double linked list
    linkedSetupMembers();
    
    return 0;
}


void arrayLinkedList() {
    int MAXSIZE = 9;
    int arr[9] = {1,2,3,4,5,6,7,8,9};
    int pos[9] = {0,1,2,3,4,5,6,7,8};
    int prevpos[9] = {8,0,1,2,3,4,5,6,7};
    
    int removeElem = 5;
    int removeElemCounter = 0;
    int elementsLeft = MAXSIZE;
    int i = 0;
    
    cout << "\n\nShow array elimination:";
    cout << "\nElements are printed as New Index:[CurrentPosition, PrevPosition]=Value";
    printElementsInSet(arr, pos, prevpos, MAXSIZE, "\nStarting Index:");

    while (elementsLeft > 0) {
        if (pos[i] != -1) {
            removeElemCounter++;
        }
        
        //remove element from pos array + reset the indices in pos
        if (removeElemCounter == removeElem) {
            pos[i] = -1;
            prevpos[i] = -1;
            int startInd = 0;
            for (int j=0; j < MAXSIZE; j++) {
                if (pos[j] != -1) {
                    pos[j] = startInd++;
                    prevpos[j] = (pos[j] == 0) ? elementsLeft-2 : pos[j] - 1;
                }
            }

            elementsLeft--;
            removeElemCounter = 0;
            cout << "\nRemoved pos[" << i << "]=" << arr[i] << ", ";
            printElementsInSet(arr, pos, prevpos, MAXSIZE, "New Index:");
        }
        //reset when max reached or increment counter
        i = (i == MAXSIZE-1) ? 0 : i+1;
    }
}



/***************************************************************
 * printElementsInSet - print elements in a set, allows prepend
 *   text before print
 ***************************************************************/
void printElementsInSet(int arr[], int pos[], int prev[], int size, string elemText) {
    std::cout << elemText;
    for (int i=0; i<size; i++) {
        std::cout << "[" << pos[i] << "," << prev[i] << "]=" << arr[i] << " ";
    }
}


/***************************************************************
 * linkedSetupMembers - master function to setup members
 *   calls insert and delete on the double linked list
 ***************************************************************/
void linkedSetupMembers() {

    int MAXSIZE = 9;
    int arr[9] = {1,2,3,4,5,6,7,8,9};
    NODE *head = NULL;
    
    cout << "\n\nShows double linked list elimination:";
    for (int i=0; i<MAXSIZE; i++) {
        linkedInsertMembers(head, arr[i]);
        linkedPrintMembers(head);
    }

    int i = 1;
    NODE *itr = head;
    linkedPrintMembers(head);
    while (head != NULL) {
        if (i % 5 == 0) {
            //remove member from the set
            linkedDeleteMembers(itr, head);
            linkedPrintMembers(head);
        } else {
            itr = itr->next;
        }
        i++;
    }
}


/***************************************************************
 * linkedPrintMembers - prints the elements in the set
 ***************************************************************/
void linkedPrintMembers(NODE *ptr) {
    int i = 0;
    NODE *itr = ptr;
    while (itr != ptr || (i == 0 && itr!= NULL)) {
        //cout << "\n{"  << itr->prev << "}-{" << itr->val << "}-[" << itr << "]-{l_" << itr->next << "}|";
        cout << itr->val << "|";
        itr = itr->next;
        i++;
    }
    if (ptr == NULL) {
        cout << "No elements exist";
    }
}

/***************************************************************
 * linkedInsertMembers - inserts into the double linked list
 ***************************************************************/
void linkedInsertMembers(NODE* &ptr, int val) {
    NODE *elem = new NODE();
    elem->val = val;

    cout << "\nAdding element: " << elem->val << " =>";
    if (ptr == NULL) {
        ptr = elem;
        ptr->prev = ptr;
        ptr->next = ptr;
    } else {
        NODE *itr = ptr;
        //move to the end of the list and insert
        while (itr->next != ptr) {
            itr = itr->next;
            //cout << "\nLandingNode=" << itr << ", next=" << itr->next << ", head=" << ptr << "\n";
        }

        elem->prev = itr;
        elem->next = itr->next;
        itr->next = elem;
        ptr->prev = elem;
        //cout << "\nFinal Nodes ==> LandingNode=" << itr << ", next=" << itr->next << ", head=" << ptr << "\n";
    }
}

/***************************************************************
 * linkedDeleteMembers - deletes from the double linked list
 ***************************************************************/
void linkedDeleteMembers(NODE* &ptr, NODE* &head) {
    NODE *temp = NULL;
    //cout << "  \n\n\n\t Removing val=" << ptr->val << ", add=" << ptr << ", head=" << head;
    cout << "\nRemoving element: " << ptr->val << " =>";
    
    //head case
    if (ptr == head && ptr != NULL) {
        temp = head;
        head->next->prev = head->prev;
        head->prev->next = head->next;
        delete temp;
        temp = NULL;
        
        if (head == head->next) {  //one element in list
            head = NULL;
        } else  { //more than one element 
            head = head->next;
            ptr = head;
        }
    } else {
        //in the body of the list
        //cout << "\n\t\t Orig ptr=" << ptr << ", next=" << ptr->next << ", prev=" << ptr->prev << "";
        temp = ptr;
        ptr->prev->next = ptr->next;
        ptr->next->prev = ptr->prev;
        ptr = ptr->next;
        if (temp != NULL) {
            delete temp;
            temp = NULL;
        }
        //cout << "\n\t\t New ptr=" << ptr << ", next=" << ptr->next << ", prev=" << ptr->prev << "";
    }
}

