//
//  main.cpp
//  CS5403_Week12_13
//  Catherine Eng - ce2086@nyu.edu
//  Divide and conquer algorithm


#include <iostream>
using namespace std;

int Max(int a, int b);
int MaxSum(int L, int U, int elemIndex);
void PrintArrayElements(int elemIndex, int maxElem);


int X[][10] = {
    {31, -41, 59, 26, -53, 58, 97, -93, -23, 84},
    {10,20,-2},
    {10,20,-2,40}
};



int main(int argc, const char * argv[])
{
    PrintArrayElements(0,10);
    cout << "\nMax sum is: " << MaxSum(0,9,0);
    
    PrintArrayElements(1,3);
    cout << "\nMax sum is: " << MaxSum(0,2,1);
    
    PrintArrayElements(2,4);
    cout << "\nMax sum is: " << MaxSum(0,3,2);

    return 0;
}


/*******************************************************************
 * MaxSum - takes the starting and size of the array to process
 * returns the max sum available in array
 *******************************************************************/
int MaxSum(int L, int U, int elemIndex) {
    int Sum=0, M=0;
    int MaxToLeft=0, MaxToRight=0, MaxCrossing=0;
    int MaxInA=0,  MaxInB=0;
    
    // if zero elements
    if (L > U)  {
        return 0;
    }
    // if one element only
    if (L == U) {
        return max(0, X[elemIndex][L]);
    }
    
    // find M, on left used to countdown to M->0.  On right, it is a countup to M+1->Len-1
    M = (L + U)/2;

    // find max to the left
    for (int I=M; I >= L; I--) {
        Sum = Sum + X[elemIndex][I];
        MaxToLeft = Max(MaxToLeft, Sum);
    }
    // find max to the right
    Sum = 0; MaxToRight = 0;
    for (int I=M+1; I <= U; I++) {
        Sum = Sum + X[elemIndex][I];
        MaxToRight = max(MaxToRight, Sum);
    }
    MaxCrossing = MaxToLeft + MaxToRight;
    // recursive calls to calculate the largest sum
    MaxInA = MaxSum(L,M, elemIndex);
    MaxInB = MaxSum(M+1, U, elemIndex);
    
    /***************************************
    cout << "\n\nMaxInARange[" << L << " - " << M << "]=" << MaxInA;
    cout << "\n\tMaxInBRange[" << M+1 << " - " << U << "]=" << MaxInB;
    cout << "\n\tMaxCrossing[" << MaxToLeft << " - " << MaxToRight << "]=" << MaxCrossing;
    ****************************************/
    
    //final return values for the maximum sum
    int ret1 = Max(MaxInA, MaxInB);
    return Max(MaxCrossing, ret1);
}


/*******************************************************************
 * Max - accepts two numbers and returns the largest
 * if a >= b then returns a, else b
 *******************************************************************/
int Max(int a, int b) {
    if (a >= b) {
        return a;
    } else {
        return b;
    }
}

/*******************************************************************
 * PrintArrayElements - references array by index passed in to
 * print elements for readability
 *******************************************************************/
void PrintArrayElements(int elemIndex, int maxElem) {
    cout << "\n==========================================================";
    cout << "\nArray values tested: {";
    for (int i=0; i<maxElem; i++) {
        cout <<  X[elemIndex][i];
        if (i < maxElem-1) {
            cout << ",";
        }
    }
    cout << "}";
}

