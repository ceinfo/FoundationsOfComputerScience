//  main.cpp
//  CS5403-Hw 5 and 6
//  Catherine Eng - ce2086@nyu.edu
//  Includes magic squares with 4 outgoing links,  sort 4 digits 

#include <iostream>
#include <string>
#include <sstream>
#include <math.h>

using namespace std;

//used for sorting list
struct NODE {
    int val;
    NODE* prev;
    NODE* next;
};

//used for magic squares list
struct SQNODE {
    int val;
    int indIndex;
    string index;
    SQNODE* left;
    SQNODE* right;
    SQNODE* top;
    SQNODE* bottom;
};

bool magicSqSequence();
bool SqInsertNodes(SQNODE* &head, int size);
void SqPrintNodes(SQNODE* &head, int size, string descrip);
void SqClearNodes(SQNODE* &head, int size);
void SqNumberUpdate(SQNODE* &head, int size);

bool sortingNumbers();
void insertNode(NODE* &head, int val);
void deleteNodes(NODE *head);
void printNodes(NODE* head);
void printReverseNodes(NODE* head);
int sortNodesDescAsc(NODE* head);


int main(int argc, const char * argv[])
{    
    //Hw5-6, question 7 - magic squares
    while (magicSqSequence()) {
        ; //keep running sequence until exit
    };
    
    //Hw5-6, question 8 - double linked list that
    //orders digits by desc and asc and subtract till repeat
    while (sortingNumbers()) {
        ; // keep running sequance until exit
    }

    return 0;
}

/***************************************************************
 * magicSqSequence - main fn to run the magic square sequence
 *  calls fns that create the list, populates and prints the list
 ***************************************************************/
bool magicSqSequence() {
    string inval = "";
    int val = 0;
    SQNODE* head = NULL;
    
    //accept user input
    cout << "\n\n==============================================================";
    cout << "\nPlease number for grid size or 'exit' to end program: ";
    cin >> inval;
    if (inval.find("exit") == 0) {
        return false;
    }
    val = atoi(inval.c_str());
    //validate user input
    if (val % 2 == 0 || val ==0) {
        cout << "You must enter an odd number for sq size, returning";
        return true;
    }
    //fns to create magic sq
    if (!SqInsertNodes(head, val)) {
        return true;
    }
    SqPrintNodes(head, val, "Step 1 - After new node creation with sample values");
    SqClearNodes(head, val);
    SqPrintNodes(head, val, "Step 2 - After nodes are cleared");
    SqNumberUpdate(head, val);
    SqPrintNodes(head, val, "Step 3 - After nodes are updated with values");
    return true;
}


/***************************************************************
 * SqInsertNodes - creating the new nodes for the magic squares
 *   links up proper direction, populates 1->size-1 value initially
 ***************************************************************/
bool SqInsertNodes(SQNODE* &head, int size) {
    SQNODE *itr = NULL;
    bool isTop = false;
    int top=-1, left=-1, right=-1, bottom=-1;
    stringstream ss;
    
    head = new SQNODE[size*size];
    if (head == NULL) {
        cout << "ERROR: cannot create memory for magic sq, returning";
        return false;
    }
    //begin adding values and directional links to each node
    itr = head;
    for (int i=0; i<size*size; i++) {
        itr->val = i+1;
        isTop = (i < size) ? true: false;
        top = (isTop) ? (size*size - size+i) : i-size;
        right = (i%size==size-1) ? i-size+1 : i+1;
        left = (i%size==0) ? i+size-1 : i-1;
        bottom = (i+size >= size*size) ? i%size : i+size;
        
        itr->top = head + top;
        itr->right = head + right;
        itr->left = head + left;
        itr->bottom = head + bottom;
        itr->val = i+1;
        //cout << "\nAssigned the following for " << itr->val << "{" << top << "," << right << "," << bottom << "," << left << "}, addr=" << itr;
        // ss << "\n New:" << itr->val << "{" << top <<  "/" << itr->top << "," << right << "," << bottom << "," << left << "}, addr=" << itr;
        ss << "\n New:" << itr->val << "{" << top << "," << right << "," << bottom << "," << left << "}, addr=" << itr;
        
        //cout << ss.str();
        itr->index = ss.str();
        itr->indIndex = i;
        ss.str("");
        ss.clear();
        itr=head+i+1;
    }
    return true;
}


/***************************************************************
 * SqPrintNodes2 - ignore, used for testing only
 ***************************************************************/
void SqPrintNodes2(SQNODE* &head, int size) {
    SQNODE* itr = head;
    int count = 0;
    cout << "\n  Printing elems:\n";
    while (count == 0 || itr != head) {
        // add newline for every row
        if (count % size == 0) {
            cout << "\n";
        }
        // print element
        cout << itr->val << "{" << itr->top->indIndex << "," <<
            itr->right->indIndex << "}, add=" << itr << " | \n";
        
        //cout << itr->val << "{" << itr->top->val << ","  << itr->right->val << ","
        //<< itr->bottom->val << "," << itr->left->val << "}";
        count++;
        itr = itr+count;
    }
}


/***************************************************************
 * SqPrintNodes - prints the magic square list
 ***************************************************************/
void SqPrintNodes(SQNODE* &head, int size, string descrip) {
    SQNODE* itr = head;
    int count = 0;
    cout << "\n" << descrip << ". Printing list data==>";
    while (count < size*size) {
        count++;
        /**
        cout << "\nPrint=" << itr->val << "{" << (itr->top)->indIndex << ","
            << (itr->right)->indIndex
            << "," << itr->bottom->indIndex
            << "," << itr->left->indIndex << "}";
         **/
        if (count % size-1 == 0) {
            cout << "\n\t";
        }
        cout << itr->val << "|";
        itr = head + count;
    }
}

/***************************************************************
 * SqClearNodes - resets all node values to -1
 ***************************************************************/
void SqClearNodes(SQNODE* &head, int size) {
    SQNODE* itr = head;
    for (int i=0; i<size*size; i++) {
        itr->val = -1;
        itr = head+i+1;
    }
}

/***************************************************************
 * SqNumberUpdate - updates each nodes numerical value with 
 *  magic square rules
 ***************************************************************/
void SqNumberUpdate(SQNODE* &head, int size) {
    SQNODE * itr = NULL;
    int midInd = floor(size/2);
    for (int i=0; i<size*size; i++) {
        //begin first elem at top/middle
        if (i == 0) {
            itr = head + midInd;
            itr->val = i+1;
        } else {
            //fill for sqs that are not populated
            if (itr->val == -1) {
                itr->val = i+1;
            } else {
            // handle cases when sqs are populated
                itr = itr->left->bottom->bottom;
                itr->val = i+1;
            }
        }
        itr = (itr->top)->right;
    }
}

/***************************************************************
 * sortingNumbers - main call for the sortingNumber problem
 *  accepts input, verifies, calls fns that insert values,
 *  prints elements, prints reverse elements and calculates
 *  the desc-asc values.  Stops when the desc-asc value repeated 2x
 ***************************************************************/
bool sortingNumbers() {
    string inval;
    int val = 0, modval = 0, prevSortedNumber = 0;
    NODE* head = NULL;
    bool stop = false;
    
    cout << "\n\n==============================================================";
    cout << "\nPlease enter a 4 digit number or 'exit' to end program: ";
    cin >> inval;
    if (inval.find("exit") == 0) {
        return false;
    }
    val = atoi(inval.c_str());
    if (val >= 9999 || val < 1000) {
        cout << "You have entered an invalid #, returning";
        return true;
    }

    while (!stop) {
        modval = val;
        prevSortedNumber = modval;
        int curmod = 0;
        while (modval > 0) {
            curmod = modval % 10;   //prints the current mod
            modval = modval / 10;   //prints the remaining values
            insertNode(head, curmod);
        }
        printNodes(head);
        printReverseNodes(head);
        val = sortNodesDescAsc(head);
        deleteNodes(head);
        head = NULL;
        if (prevSortedNumber == val) {
            cout << ".  Repeating sums, stopping here."; 
            stop = true;
        }
    }
    return true;
}

/***************************************************************
 * insertNode - creates a double linked list in desc order 
 ***************************************************************/
void insertNode(NODE* &head, int val) {
    int count = 0;
    NODE *itr = head;
    NODE *prev = NULL;
    NODE *elem = new NODE();
    elem->val = val;
    
    //cout << "\nInserting new elem:" << elem->val << ", addr=" << elem;
    if (head == NULL) {
        head = elem;
        head->next = head;
        head->prev = head;
    } else {
        // sort by descending order
        while (itr->val > val && (count == 0 || itr != head)) {
            prev = itr;
            itr = itr->next;   
            count++;
        }
        // insert elements at beginning or later in the link
        if (prev == NULL) {
            elem->prev = head->prev;
            elem->next = head;
            head->prev = elem;
            head = elem;
            head->prev->next = elem;
        } else { 
            elem->prev = prev;
            elem->next = prev->next;
            prev->next->prev = elem;
            prev->next = elem;
            
            if (elem->next == head) {
                head->prev = elem;
            }
        }
    }
}

/***************************************************************
 * printNodes - prints the elements in the set
 ***************************************************************/
void printNodes(NODE* head) {
    int count = 0;
    NODE *itr = head;
    cout << "\nPrintNodes: ";
    while ((count==0  && itr != NULL) || itr != head) {
        cout << itr->val << "|";
        count++;
        itr = itr->next;
    }
}

/***************************************************************
 * printReverseNodes - prints the elements in the set using 
 *   NODE->prev
 ***************************************************************/
void printReverseNodes(NODE* head) {
    int count = 0;
    NODE *itr = head->prev;
    cout << "\nPrintReverseNodes: ";
    while (count==0 || itr != head->prev) {
        cout << itr->val << "|";
        count++;
        itr = itr->prev;
    }
}

/***************************************************************
 * sortNodesDescAsc - loops through and calculates the actual 
 *  digits from the list and calculates desc-asc values
 ***************************************************************/
int sortNodesDescAsc(NODE* head) {
    //loop through the list and keep a running count for descending # and ascending #
    int count = 0, asc=0, desc=0, ascMod=1000, descMod=1000;
    NODE* itr = head;
    NODE* bitr = head->prev;
    
    while (count==0 || itr != head) {
        desc += itr->val * descMod;
        descMod /= 10;
        //cout << " descElem=" << desc;
        count++;
        itr = itr->next;
        
        asc += bitr->val * ascMod;
        ascMod /= 10;
        bitr = bitr->prev;
        //cout << "\n ascElem=" << asc;
    }
    cout << "\n==>Final: " << desc << " - " << asc << " = " << (desc-asc);
    return (desc-asc);
}

/***************************************************************
 * deleteNodes - deletes the entire list
 ***************************************************************/
void deleteNodes(NODE *head) {
    int count = 0;
    NODE *itr = head;
    NODE *prev = head;
    
    while (count==0 || itr != head) {
        prev = itr;
        count++;
        itr = itr->next;

        // deleting elements 
        if (prev != NULL) {
            delete prev;
            prev = NULL;
        }
    }
    head = NULL;
}