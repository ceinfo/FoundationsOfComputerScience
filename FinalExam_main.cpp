//
//  main.cpp
//  CS5403_FinalExam
//  Catherine Eng - ce2086@nyu.edu
//  N-Queen Algorithm


#include <iostream>
using namespace std;

typedef enum {FALSE, TRUE} BOOLEAN;
#define MAX 25 /* Largest board size */

/* GLOBALS */
int a[MAX], /* vector holding solution */
size = 0, /* board size selected by user */
type = 0, /* display type */
numb = 0; /* total number of solutions */

void find_sol( int, int );

int main( ) {
    printf("\nN-Queen Example\n");
    do { /* Obtain board size */
        printf("\n\n\nEnter the size of the board 1-%1d ", MAX);
        scanf("%d", &size );
    } while ( size < 0 || size > MAX );
    do { /* Obtain output format */
        printf("Enter the output display type 1 = diagrammatic | 2 = numeric ");
        
        scanf("%d", &type );
    } while ( type < 0 || type > 2 );
    printf("\n\nFor a board of size %d solutions are: \n",size);
    find_sol( 0 , 0 ); /* Initial call */
    if ( ! numb ) printf("\n\nZERO !");
    printf("\n\n\n");
}


/*
 Function no_conflict: Passed row and column position. Returns
 TRUE if no conflict with previous
 locations else returns FALSE
 */
BOOLEAN
no_conflict( int row, int col ){
    register int i;
    int d; /* Temporary diagonal offset value.*/
    BOOLEAN ok = TRUE; /* Assume no conflict at the start.*/
    /*
     Step backward and check for conflicts with
     previous selections.
     */
    for ( i = col-1; i >= 0 && ok ; --i ) {
        d = col - i;
        if ( a[i] == row || /* Check for conflict in: same row,*/
            a[i]-d == row || /* same major diagonal, */
            a[i]+d == row /* same minor diagonal. */
            ) ok = FALSE;
    }
    return( ok );
}
/*
 Function print
 it : Displays output in user selected format.
 */
void
print_it( ){
    register int r, c;
    static char line[]="+---+---+---+---+---+---+---+---+";
    line[size*4+1] = '\0'; /* cut string to size */
    printf("\n%03d : ", ++numb );
    switch ( type ) {
        case 1:
            printf("\n\n%s\n", line );
            for ( r = 0; r < size ; ++r ) {
                for ( c = 0; c < size ; ++c ) {
                  //  printf("| %c ", a[r] == c ? 'Q' : (r+c) % 2 ? '#':' ');
                    printf("| %c ", a[c] == r ? 'Q' : (r+c) % 2 ? '#':' ');
                   // printf("ack[%d,%d]=%d\n", r, c, a[c]);
                    //cout << "[" << r << "," << c << "=" << a[c] << "\n";
                }
                printf("|\n%s\n", line );
            }
            
            /**
             for ( r = 0; r < size ; ++r ) {
             for ( c = 0; c < size ; ++c ) {
             //  printf("| %c ", a[r] == c ? 'Q' : (r+c) % 2 ? '#':' ');
             printf("| %c ", a[c] == r ? 'Q' : (r+c) % 2 ? '#':' ');
             }
             printf("|\n%s\n", line );
             }
             **/
            break;
        case 2 :
        default :
            for ( c = 0; c < size ; ++c )
                printf("%3d", a[c]+1 );
    }
}

/*
 A non-recursive find
 sol( ) function. A few more lines of
 code but less system intensive.
 */
void
find_sol( int row, int col ){
    
    do {
        printf ("\nBeginning new element[%d, %d] for \n", row, col);

        if (no_conflict(row,col)){ /*Check for conflicts, if none*/
            printf("\t No conflict, set row a[%d]=%d \n", col, row);
            
            a[col] = row; /*save the location in vector.*/
            
            printf("\t TestIf [col=size-1],  col=%d, size-1=%d\n", col, size-1);
            
            if ( col==size-1 ) { /*If full solution display. */
                printf("\t\t Matching col and size-1!!!\n");
                print_it( );
            } else { /*Otherwise reset the row and */
                printf("\t\t Non-Matching,  will reset row=0 and inc col!!!\n");
                row = 0;
                ++col; /*check the next column. */
                continue;
            }
        }
        printf("\t\t AAAfter conflict check and there is a conflict\n");
        
        // Only here when conflict found
        
        // if more rows are available to process
        if ( row < size-1 ) { 
            printf("\t\t\t  Row<size-1, row=%d, size=%d\n", row, size-1);
            ++row; /*try next row, same column. */
        } else { /*Otherwise backtrack until a */
            
            printf("\t\t\t  BackTop of while, col=%d, a[col-1]+1=%d, size=%d\n", col, a[col-1]+1, size-1);

            while (col && a[col-1]+1 > size-1) {
                --col; /*column is found with a row */
            }
            row = a[--col]+1; /*value that can be increment-*/
            printf("\t\t\t =>Final a[%d, %d]=%d \n", row, col, a[col]);

        } /*end to the next row. */
    } while ( row < size ); /*Loop until beyond last row */
}