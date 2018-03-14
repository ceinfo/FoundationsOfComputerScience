//
//  main.cpp
//  CS5403-Hw2
//  Catherine Eng - ce2086@nyu.edu
//  Includes Johnson's algorithm,  Dutch National Flag Problem,  Magic Squares

#include <iostream>

typedef struct {
    char dir;
    int num;
    
} unit;

void dutchNationFlagAlgorithm();
void dutchNationalFlagSort(int arr[], int size, int red, int white, int blue);
void johnsonAlgorithm();
void printJohnson(unit unitarr[], int size);
int findNextMobile(int sizearr, unit unitarr[]);
void swapElements(unit unitarr[], int src, int dest);

std::string outputSep = "\n-----------------------------------------------------------------------------\n";


int main(int argc, const char * argv[])
{    
    //Hw2, #8:  Johnson's Algorithm
    johnsonAlgorithm();
        
    //Hw2, #9:  Dutch National Flag Problem
    dutchNationFlagAlgorithm();

    return 0;
}


/*********************************************************************
 * dutchNationalFlagAlgorithm() - calls dutchNationalFlagSort with
 *     multiple input values
 **********************************************************************/
void dutchNationFlagAlgorithm() {
    int arr[][11] = {
        {3,3,1,2,2,3},
        {3,3,2,1,1,1},
        {2,3,3,1,2,1,1,2,1},
        {1,1,1,1,1,1},
        {1,1},
        {1,2},
        {1,3},
        {2,1},
        {2,2},
        {3,2},
        {6,6,1},
    };
    dutchNationalFlagSort(arr[2], 9, 1, 2, 3);
    dutchNationalFlagSort(arr[2], 9, 1, 3, 2);
    dutchNationalFlagSort(arr[2], 9, 2, 1, 3);
    dutchNationalFlagSort(arr[2], 9, 2, 3, 1);
    dutchNationalFlagSort(arr[2], 9, 3, 1, 2);
    dutchNationalFlagSort(arr[2], 9, 3, 2, 1);
    dutchNationalFlagSort(arr[0], 6, 1, 2, 3);
    dutchNationalFlagSort(arr[1], 6, 1, 2, 3);
    dutchNationalFlagSort(arr[1], 6, 2, 1, 3);
    dutchNationalFlagSort(arr[3], 2, 2, 1, 3);
    dutchNationalFlagSort(arr[4], 2, 1, 2, 3);
    dutchNationalFlagSort(arr[5], 2, 1, 2, 3);
    dutchNationalFlagSort(arr[6], 2, 1, 2, 3);
    dutchNationalFlagSort(arr[7], 2, 1, 2, 3);
    dutchNationalFlagSort(arr[8], 2, 1, 2, 3);
    dutchNationalFlagSort(arr[9], 2, 1, 2, 3);
    dutchNationalFlagSort(arr[10], 3, 1, 2, 3);
    std::cout << outputSep;

}

/*********************************************************************
 * dutchNationalFlagSort() - receive an array, sort order as red -> white -> blue
 *  - the best way to do this is update based on the number of each red, white, blue
 *  - tracking by index is much harder, don't do it (more complex as you shift red)
 **********************************************************************/
void dutchNationalFlagSort(int arr[], int size, int red, int white, int blue) {
    
    std::cout << "\n\nStarting dutchNationalFlagSort(), r=" << red << ", w=" << white << ", b=" << blue << "\nElements =====> ";
    for (int i=0; i<size; i++) {
        std::cout <<  arr[i] << "|";
    }
    
    int numRed=0, numWhite=0, numBlue=0;
    for (int n=0; n<size; n++) {
        //std::cout << "\nFound " << arr[n] << " ...\n";
        if (arr[n] == red) { //update for red
            numRed++;
            if (arr[numRed-1] == white) {
                arr[numRed-1] = red;
                if (arr[numRed+numWhite-1] == blue) {
                    arr[numRed+numWhite+numBlue-1] = blue;
                }
                arr[numRed+numWhite-1] = white;
            } else if (arr[numRed-1] == blue) {
                arr[numRed-1] = red;
                arr[numRed+numWhite+numBlue-1] = blue; // don't really add the numWhite or could be arr[n]
            }
        } else if (arr[n] == white) { //update for white
            numWhite++;
            if (arr[numRed+numWhite-1] == blue) {
                arr[numRed+numWhite-1] = white;
                arr[numRed+numWhite+numBlue-1] = blue;
            } else {
                arr[n] = white;
            }
        } else if (arr[n] == blue) { //update for blue
            numBlue++;
        } else {
            std::cout << "Invalid Number Found: " << arr[n] << ", returning";
            return;
        }
    }
        
    std::cout << "\nEndElements ==> ";
    for (int i=0; i<size; i++) {
        std::cout <<  arr[i] << "|";
    }
}



/**********************************************************************
 * johnsonAlgorithm - calls functions to run the johnson algorithm, 
 *     setup tests for output
 **********************************************************************/
void johnsonAlgorithm() {
    unit unitarr[10];
    int sizearr = 10;
    int lastMaxMobile = 0;
    int beginVal = 0;
        
    /******************
     *  run test 3x:
     * 1- 0..2
     * 2- 1..3
     * 3 -1..4
     ******************/
    for (int i=0; i<3; i++) {
        if (i == 0) {
            sizearr = 3;
            beginVal = 1;
        } else if (i == 1) {
            sizearr = 3;
            beginVal = 1;
        } else if (i == 2) {
            sizearr = 4;
            beginVal = 1;
        }
        // reset the array
        for (int i=0; i<sizearr; i++) {
            unitarr[i].num = beginVal++;
            unitarr[i].dir = '<';
        }
        
        //print and call the johnson fn
        std::cout << "Beginning Johnson Algorithm:\n";
        printJohnson(unitarr, sizearr);
        while (findNextMobile(sizearr, unitarr) > 0) {
            lastMaxMobile++;
        }
        std::cout << "\n";
    }
    std::cout << outputSep;

}



/**********************************************************************
 * printJohnson - prints the current number and values in the array
 **********************************************************************/
void printJohnson(unit unitarr[], int sizearr)  {
    std::cout << "\t";
    for (int i=0; i<sizearr; i++) {
        std::cout << unitarr[i].dir << unitarr[i].num << " ";
    }
    std::cout << "\n";
}


/**********************************************************************
 * findNextMobile - finds and updates the next mobile number and direction
 **********************************************************************/
int findNextMobile(int sizearr, unit unitarr[]) {
    int foundMobileInd = 0;
    int maxNumberInd = -1;
    int findMaxCounter = 0;
    int maxFoundCounter = 0;
    bool maxFound = false;

    while (!maxFound) {
        foundMobileInd = 0;
        //check for the max integer and direction.
        //if it is not mobile then check for the next possible mobile # if not found         
        if (maxFoundCounter > 0) {
            while(unitarr[foundMobileInd].num == unitarr[maxNumberInd].num) {
                foundMobileInd++;
                //std::cout << " chging the maxfound " << unitarr[foundMobileInd].num << "\n";
            }
        }
        
        for (int i=maxFoundCounter; i< sizearr; i++) {
            //get the highest number
            //std::cout << "\n     prep if foundNum=" << unitarr[foundMobileInd].num  << ", iNum=" << unitarr[i].num << ", max=" << unitarr[maxNumberInd].num << "| maxCounter=" << maxFoundCounter << ", 1st=" <<  unitarr[foundMobileInd].num  << ", 2nd=" << unitarr[i].num << ", 3rdMax=" << unitarr[maxNumberInd].num;
            
            
            if ((unitarr[foundMobileInd].num <unitarr[i].num && maxFoundCounter==0)
                    || (maxFoundCounter > 0 && unitarr[foundMobileInd].num <unitarr[i].num && unitarr[foundMobileInd].num < unitarr[maxNumberInd].num)) {
                foundMobileInd = i;
                findMaxCounter++;
                maxNumberInd = i;
                //std::cout << "\n           new foundMobileInd=" << unitarr[foundMobileInd].num << "\n";
            }
        }
        
        int curInd = foundMobileInd;
        //direction to the right
        while (unitarr[foundMobileInd].dir == '>' && curInd < sizearr-1) {
            curInd++;
            if (unitarr[curInd].num < unitarr[foundMobileInd].num) {
                swapElements(unitarr, foundMobileInd, curInd);
                foundMobileInd = curInd;
                printJohnson(unitarr, sizearr);
                maxFound = true;
            }
        }
        //direction to the left
        while (unitarr[foundMobileInd].dir == '<' && curInd >= 0) {
            curInd--;
            if (unitarr[curInd].num < unitarr[foundMobileInd].num) {
                swapElements(unitarr, foundMobileInd, curInd);
                foundMobileInd = curInd;
                printJohnson(unitarr, sizearr);
                maxFound = true;
            }
        }
        
        //swap dir of any other element with element.val > foundMobile.val
        if (maxFound) {
            for (int i=0; i<sizearr; i++) {
                if (unitarr[i].num > unitarr[foundMobileInd].num) {
                    if (unitarr[i].dir == '<') {
                        unitarr[i].dir = '>';
                    } else {
                        unitarr[i].dir = '<';
                    }
                    //std::cout << "\n Max # found" << unitarr[foundMobileInd].num;
                }
            }
        } 
        //std::cout << "\nMaxNumber===" << unitarr[foundMobileInd].num << ", Counter=" << maxFoundCounter;
        maxFoundCounter++;
    
    }
    return findMaxCounter;
}


/**********************************************************************
 * swapElements in array from a->b,  b->
 **********************************************************************/
void swapElements(unit unitarr[], int a, int b) {
    unit temp = unitarr[b];
    unitarr[b] = unitarr[a];
    unitarr[a] = temp;
}
