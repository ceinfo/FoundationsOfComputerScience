//
//  main.cpp
//  CS5403-Hw3
//  Catherine Eng - ce2086@nyu.edu
//  Includes Vigenere Tableau as single array, Bubble Sort, Reversal Numbers

#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <string>

using namespace std;

void writeVigenereTables();
void bubbleSortForSet(int arr[], int size);
void printElementsInSet(int arr[], int size, string elemText);
void findTwoReversedNumbers();
int readAndAllocateElement(int a, int* &modAPtr);
int compareReverse(int a, int b, int* modAPtr, int* modBPtr, int modACount, int modBCount);
void removeMemoryUsed(int* &ptr);

int main(int argc, const char * argv[])
{
    std::string outputSep = "\n--------------------------------------------------------------------------\n";
        
    //Hw3, Problem9: write Vigenere Tables as single array
    writeVigenereTables();
    std::cout << outputSep;
    
    
    //Hw3, Problem10: BubbleSort for set of numbers
    int arr[][11] = {
        {3,3,1,2,2,3},
        {9,7,2,1,6,9,8,4,5},
        {1,0},
        {1},
        {49,17,2002,-1,86,9000,8,0,50},
    };
    bubbleSortForSet(arr[0],6);
    bubbleSortForSet(arr[1],9);
    bubbleSortForSet(arr[2],2);
    bubbleSortForSet(arr[3],1);
    bubbleSortForSet(arr[4],9);
    std::cout << outputSep;

    
    //Hw3,  Problem11: accept 2#'s and see if they are reverse of each other
    string input;
    do {
        cout << "\n===================================================";
        cout << "\n\nInstructions:  start reverse search, type any key+Enter to begin or type \"exit\"+Enter at this prompt end:  ";
        cin >> input;
        if (input.compare("exit") != 0) {
            findTwoReversedNumbers();
        }
    } while (input.compare("exit") != 0);
    
    return 0;
}


/***************************************************************
 * writeVigenereTables() - write cipher by row/column
 ***************************************************************/
void writeVigenereTables() {
    int MAX_SIZE= 26;
    char cipher[26*26] = {'\0'};
    int beginVal = (int)'a';
    int innerInd = 0;
    
    // Vigenere Tableau beginning with the first index
    // Ex:  a...z
    //      b...a
    // Start at pos[prev+1] ... if you reach the end then start value from a --> end of size
    std::cout << "\n\nVigenere Tableau as single array [0] .. [MAX_SIZE^2 -1], fill index 0 first";
    for (int i=0; i < MAX_SIZE; i++) {
        int beginChar = beginVal + i;
        std::cout << "\n";
        
        for (int x=0; x < MAX_SIZE; x++) {
            innerInd = (i*MAX_SIZE) + x;
            cipher[innerInd] = (char)beginChar++;
            //std::cout << "[" << innerInd << "]=" << cipher[innerInd] << "|";
            std::cout << cipher[innerInd] << "|";
            if (beginChar > (char)'z') {
                beginChar = 'a';
            }
        }
    }
    
    // Vigenere Tableau with single array [MAX_SIZE^2 - -1] ... 0,  fill last element first
    std::cout << "\n\nVigenere Tableau as single array [MAX_SIZE^2 -1] .. 0, fill last elem first";
    for (int i=MAX_SIZE; i > 0; i--) {
        int beginChar = beginVal + (MAX_SIZE -i);
        std::cout << "\n";
        for (int x=0; x < MAX_SIZE; x++) {
            innerInd = (i*MAX_SIZE) -x -1;
            cipher[innerInd] = (char)beginChar++;
            //std::cout << "[" << x << "," << i << ", " << innerInd <<"]=" << cipher[innerInd] << "|";
            std::cout << cipher[innerInd] << "|";
            if (beginChar > (char)'z') {
                beginChar = 'a';
            }
        }
    }
}

/***************************************************************
 * bubbleSortForSet - for a set of #s loop through a choose the
 *   highest for the entire index for this position and place 
 *   into current index if found
 ***************************************************************/
void bubbleSortForSet(int arr[], int size) {
    printElementsInSet(arr, size, "\nElements Before Sort:  ");
    for (int i=0; i<size; i++) {
        for (int j=i+1; j<size; j++) {
            if (arr[i] > arr[j]) {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
    printElementsInSet(arr, size, "Elements After Sort:   ");
}

/***************************************************************
 * printElementsInSet - print elements in a set, allows prepend
 *   text before print
 ***************************************************************/
void printElementsInSet(int arr[], int size, string elemText) {
    std::cout << "\n" << elemText;
    for (int i=0; i<size; i++) {
        std::cout << arr[i] << "|";
    }
}

/***************************************************************
 * findTwoReversedNumbers - input for 2 #s, comparsion in 2 
 *    separate arrays
 ***************************************************************/
void findTwoReversedNumbers() {
    int a=0, b=0;
    int modACount=0, modBCount=0;
    int *modAPtr=NULL, *modBPtr = NULL;
    int reverseStatus = -1;
    
    cout << "Enter first number:";
    cin >> a;
    cout << "Enter second number:";
    cin >> b;
    
    if (a > 0 and b > 0) {
        //separate the numbers into 2 sets
        modACount = readAndAllocateElement(a,modAPtr);
        modBCount = readAndAllocateElement(b,modBPtr);
        //0 when memory cannot be created
        if (modACount == 0 or modBCount == 0) {
            return;
        }
        //compare the digits in each set
        reverseStatus = compareReverse(a, b, modAPtr, modBPtr, modACount, modBCount);
        cout << "Reverse Equality is " << ((reverseStatus == 0) ? "true" : "false");
    } else {
        cout << "You must enter numeric values, exiting.";
        return;
    }
    // free the memory used
    removeMemoryUsed(modAPtr);
    removeMemoryUsed(modBPtr);
}

/***************************************************************
 * readAndAllocateElement - accept a and 
 *   accepts a, create an array 
 ***************************************************************/
int readAndAllocateElement(int a, int* &modAPtr) {
    int modA=0, modAIter=0;
    
    modA = a;
    while (modA > 0) {
        //cout << modA % 10 << "-";
        modA = modA /10;
        modAIter++;
    }
    if ((modAPtr = (int*) malloc(sizeof(int) * (modAIter))) == NULL) {
        cout << "Cannot malloc new memory, returning\n";
        return 0;
    }
    modA = a;
    
    // assign these values into dynamic array
    for (int i=0; i< modAIter; i++) {
        *(modAPtr+modAIter -1-i) = modA % 10;
        modA = modA/10;
    }
    
    // print values to verify
    /**
    cout << "Iter=" << modAIter << "\n";
    for (int i = 0; i < modAIter; i++) {
        cout <<  modAPtr[i] << "|";
    }
     **/
    return modAIter;
}

/***************************************************************
 * removeMemoryUsed -  check if memory exists, remove it
 ***************************************************************/
void removeMemoryUsed(int* &ptr) {
    if (ptr != NULL) {
        free (ptr);
    }
    return;
}


/***************************************************************
 * compareReverse -  check if setA is the reverse of setB
 *     return -1 if reverse is not true, 0 alternatively
 ***************************************************************/
int compareReverse(int a, int b, int *modAPtr, int *modBPtr, int modACount, int modBCount) {
    if (modACount != modBCount) {
        //cout << "The # of digits do not match, not equal.";
        return -1;
    } else {
        int i = 0;
        int newBCount = 0;
        while (i < modACount) {
            newBCount = modBCount -i -1;
            if (modAPtr[i] != modBPtr[newBCount]) {
                //cout << "Numbers entered " << modAPtr[i] << "," << modAPtr[newBCount] << " are not equal.";
                return -1;
            }
            i++;
        }
        //cout << "The numbers " << a << "," << b << " are equal.";
    }
    return 0;
}


