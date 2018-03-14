//
//  main.cpp
//  CS5403-Hw1
//  Catherine Eng - ce2086@nyu.edu
//  Includes Vigenere Tableau,  Palindromes,  Sorting, Perfect Medians

#include <iostream>
#include <math.h>

void writeVigenereTables();
bool isPalindrome(int num);
void sortThreeValues(int arr[], int size, int red, int white, int blue);
void findPerfectMedians();

int main(int argc, const char * argv[])
{
    std::string outputSep = "\n-----------------------------------------------------------------------------\n";

    
    //Hw1,Problem3: write Vigenere Tables by rows and columns
    writeVigenereTables();
    std::cout << outputSep;
    
    
    //Hw1,Problem4: checking for palindrome answers
    std::cout << "\n\nTest output for isPalindrome() below";
    int testNums[22] = { 5035, 10301, 100, 2350, 213123, 1, 0, 10, 3003003, 9380009, 99, 98, 101, 232, 230, 22093, 55255, 5555555, 88288, 81, 85, 8888};
    for (int i=0; i < 22; i++) {
        std::cout << "\nTest Palindrome <" << testNums[i] << "> is: " << (isPalindrome(testNums[i])? "true" : "false");
    }
    std::cout << outputSep;
    
    
    //Hw1,Problem5:  Three numbers, sort by: red -> white -> blue 
    int arr[][11] = {
        {3,3,1,2,2,3},
        {3,3,2,1,1,1},
        {2,3,3,1,3,2,1,1,3,2,1},
        {1,1,1,1,1,1},
        {1,1},
        {1,2},
        {1,3},
        {2,1},
        {2,2},
        {2,3},
        {6,6,1},
    };
    sortThreeValues(arr[2], 11, 1, 2, 3);
    sortThreeValues(arr[2], 11, 1, 3, 2);
    sortThreeValues(arr[2], 11, 2, 1, 3);
    sortThreeValues(arr[2], 11, 2, 3, 1);
    sortThreeValues(arr[2], 11, 3, 1, 2);
    sortThreeValues(arr[2], 11, 3, 2, 1);
    sortThreeValues(arr[0], 6, 1, 2, 3);
    sortThreeValues(arr[1], 6, 1, 2, 3);
    sortThreeValues(arr[1], 6, 2, 1, 3);
    sortThreeValues(arr[3], 2, 2, 1, 3);
    sortThreeValues(arr[4], 2, 1, 2, 3);
    sortThreeValues(arr[5], 2, 1, 2, 3);
    sortThreeValues(arr[6], 2, 1, 2, 3);
    sortThreeValues(arr[7], 2, 1, 2, 3);
    sortThreeValues(arr[8], 2, 1, 2, 3);
    sortThreeValues(arr[9], 2, 1, 2, 3);
    sortThreeValues(arr[10], 3, 1, 2, 3);
    std::cout << outputSep;
    
    
    //Hw1,Problem6:  findPerfectMedians()
    findPerfectMedians();

    return 0;
}


/***************************************************************
 * writeVigenereTables() - write cipher by row/column
 ***************************************************************/
void writeVigenereTables() {
    int MAX_SIZE = 26;
    char cipher[26][26] = {'\0'};
    int beginVal = (int)'a';
    int totalCounter = 0;
    
    // Vigenere Tableau by rows
    // Ex:  a...z
    //      b...a
    // Start at pos[prev+1] ... if you reach the end then start value from a --> end of size
    std::cout << "\n\nVigenere Tableau by rows";
    for (int i=0; i < MAX_SIZE; i++) {
        int beginChar = beginVal + i;
        std::cout << "\n";
        
        for (int x=0; x < MAX_SIZE; x++) {
            cipher[i][x] = (char)beginChar++;
            //std::cout << "[" << i << "," << x << "]=" << cipher[i][x] << "|";
            std::cout << cipher[i][x] << "|";
            if (beginChar > (char)'z') {
                beginChar = 'a';
            }
        }
    }
    
    // Vigenere Tableau by by columns
    // fill index [0,x], then [1,x], ...
    std::cout << "\n\nVigenere Tableau by columns";
    for (int i=0; i < MAX_SIZE; i++) {
        int beginChar = beginVal + i;
        std::cout << "\n";
        
        for (int x=0; x < MAX_SIZE; x++) {
            cipher[x][i] = (char)beginChar++;
            //std::cout << "[" << x << "," << i << "]=" << cipher[x][i] << "|";
            std::cout << cipher[x][i] << "|";
            if (beginChar > (char)'z') {
                beginChar = 'a';
            }
        }
    }
}


/***************************************************************
 * isPalindrome(int number) - checks if number is palindrome
 ***************************************************************/
bool isPalindrome(int num) {
    int maxMult = 1;
    int calc = num/maxMult;
    int digitCount = 0;
    
    //if single digit then is a palindrome
    if (num  < 10)
        return true;
    
    //try to get # of iterations (initially divide number for front single digit and use digitCount to see how many x loops through digits)
    while (calc > 0) {
        //std::cout << " maxMult=" << maxMult << ", calc=" << (calc) << "\n";
        maxMult *= 10;
        calc = num/maxMult;
        digitCount++;
    }
    //std::cout << "MaxMult=" << maxMult << " ==> " << "\n digitCount=" << digitCount << "\n";
    
    //set variables for first/last digit comparisons
    int runNum = num;
    int runMult = maxMult/10;
    int calcNum = 0;
    int innerMult = 10;
    int innerRunNum = num;
    int innerCalcNum = 0;
    
    for (int i=0; i<(int)digitCount/2; i++) {
        calcNum = (int)(runNum/runMult);
        runNum = runNum - calcNum * runMult;
        runMult /= 10;
        //std::cout << "\t\tWriting first #'s ==> " << calcNum << "\n";
        
        innerCalcNum = innerRunNum % innerMult;
        innerRunNum = (innerRunNum - innerCalcNum) / innerMult;
        //std::cout << "\t\tWriting 2nd #'s ==> " << innerCalcNum << "\n";
        
        if (calcNum != innerCalcNum) {
            return false;
        }
    }
    return (true);
}



/*********************************************************************
 * sortThreeValues() - receive an array, sort order as red -> white -> blue
 *  - the best way to do this is update based on the number of each red, white, blue
 *  - tracking by index is much harder, don't do it (more complex as you shift red)
 **********************************************************************/
void sortThreeValues(int arr[], int size, int red, int white, int blue) {

    std::cout << "\n\nStarting sortThreeValues(), r=" << red << ", w=" << white << ", b=" << blue << "\nElements =====> ";
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
        
        /*************
        std::cout << "   \n\tModFinElement=";
        for (int i=0; i<size; i++) {
            if (i == n)
                std::cout << "{" << arr[i] << "}" << "|";
            else
                std::cout << arr[i] << "|";
        }
        *************/
    }
    
    std::cout << "\nEndElements ==> ";
    for (int i=0; i<size; i++) {
        std::cout <<  arr[i] << "|";
    }
}



/*********************************************************************
 * findPerfectMedians() - find Perfect Medians
 *   - to find a perfect median,  then [PreSum = 1...(n-1)] ==> N ==> [(n+1...) = PostSum]
 *   - if AfterSum < PreSum then we can keep checking the (n+1) sum
 *   - if == then we've found perfect median
 **********************************************************************/
void findPerfectMedians() {    
    int startNum = 1;
    int preSum = 0, postSum = 0, median = 0, outterN = 0;
    int arr[20] = {0};
    int arrCounter=0;
    bool exitLoop = false;
    
    //finds the perfect medians from 1 to 2M
    while (startNum != 500000*2*2) {
        median = 0;
        preSum = 0;
        outterN = 0;
        exitLoop = false;
        
        //std::cout << "Starting count " << startNum << "\n";
        //1...n-1,  N, n+1... ==> postSum < preSum then continue adding to postSum
        int i = startNum;
        preSum = (i)*(i-1)/2;
        
        /**
        //oldCode where sum up to preSum
        outterN = startNum+1;
        while (postSum < preSum) {
            postSum += outterN++;
        }
        **/
            
        int SumM = preSum*2 + i;
        outterN = startNum+1;
        int runningMSum = outterN*(outterN+1)/2;
        while (runningMSum < SumM) {
            outterN++;
            runningMSum += outterN;
        }
        if (runningMSum == SumM) {
            median = i;
            arr[arrCounter++] = i;
        }
        //std::cout << "    Inner[" << i << "] preSum=" << preSum << ", postSum=" << postSum << "\n";
        if (median != 0) {
            std::cout << "Perfect Median found!  Sequence 1..[" << median << "].." << outterN << ", sum=" << preSum << "\n";
            //std::cout <<  median << "\n";

        }
        startNum++;
    }
    
    //Calculating question #6(a) if perfect medians will produce perfect medians?  From values of 1 --> 2M, found
    std::cout << "\nStarting new counter for perfect median in perfect median:\n"; 
    int sizeNumbers = arrCounter;
    int subIndex = 0;
    while (subIndex < sizeNumbers) {
        // sum arr to current index
        // sum postarray till # in post < preSum
        // if match then good index found
        int preSum = 0;
        int postSum = 0;        
        int i = 0;
        int j = i;
        while (j < subIndex) {
            preSum += arr[j++];
            //std::cout << "\t\tCalculating pre=" << preSum << "\n";
        }
        j = subIndex+1;
        while (postSum < preSum) {
            postSum += arr[j++];
            //std::cout << "\t\tCalculating post=" << postSum << "\n";
        }
            
        if (postSum == preSum) {
            median = i;
            //std::cout << "\t\tFound perfect median=" << i << "\n";
        }
        std::cout << "Calculating perfect median [" << arr[subIndex] << "] preSum=" << preSum << ", postSum=" << postSum << ", medianFound=" << ((median != 0) ? "true" : "false") << "\n";
        subIndex++;
    }
    
}


