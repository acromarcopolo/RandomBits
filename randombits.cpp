#include <iostream>
#include <vector>
#include <string>

#define LOG 0

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
  (byte & 0x80 ? '1' : '0'), \
  (byte & 0x40 ? '1' : '0'), \
  (byte & 0x20 ? '1' : '0'), \
  (byte & 0x10 ? '1' : '0'), \
  (byte & 0x08 ? '1' : '0'), \
  (byte & 0x04 ? '1' : '0'), \
  (byte & 0x02 ? '1' : '0'), \
  (byte & 0x01 ? '1' : '0')

using namespace std;

/* UNUSED: Alternative way to print binary, using recursion
void print_0b( unsigned int number )
{
    if( number >> 1 ){
        print_0b( number >> 1 );
    }
    putc( (number & 1) ? '1' : '0', stdout );
}*/

// Print a short int (2 bytes) in its binary form, with all 0s and a space between the 2 bytes 
// TODO: make this cleaner with vprintf
void print_ushort2bin( unsigned short twobytes )
{
    printf( BYTE_TO_BINARY_PATTERN " " BYTE_TO_BINARY_PATTERN ,
            BYTE_TO_BINARY(twobytes>>8), // first byte
            BYTE_TO_BINARY(twobytes) );  // second byte
}


int main()
{

    /*
        Button "Generieren"
    */

    // Get an integer from the user
    unsigned short my_int; // number will be restricted to small positive range
    printf("Enter a number from 2 to 10: ");
    scanf("%hu",&my_int);
    // TODO: chek number is in the 2..10 range

    // Generate 'my_int' random numbers & store in a vector
    std::srand( std::time(nullptr) ); // use current time as seed for random generator
    vector<unsigned short> vec_of_rand1; // vector that will store random numbers
    vector<unsigned short> vec_of_rand2; // vector that will store random numbers
    unsigned short my_rand; // 16 bit is enough for a 0..10000 random number
    for( int ii = 0; ii < my_int; ii++ )
    {
        my_rand = std::rand() % 10000; // quick and dirty random number in the 0..10000 range
        vec_of_rand1.push_back( my_rand ); // populate vector
        std::srand( my_rand ); // use current time as seed for random generator
        my_rand = std::rand() % 10000; // quick and dirty random number in the 0..10000 range
        vec_of_rand2.push_back( my_rand ); // populate vector
    }

    // Sort random number vectors in ascending order
    std::sort( vec_of_rand1.begin(), vec_of_rand1.end() );
    std::sort( vec_of_rand2.begin(), vec_of_rand2.end() );

    // Print out resulting sorted vectors
    printf("I generated 2 arrays of %d random numbers, and sorted them for you:\nArray 1:", my_int );
    for( vector<unsigned short>::iterator ptr = vec_of_rand1.begin(); ptr < vec_of_rand1.end(); ptr++ )
    {
        cout << "\t" << *ptr ;
    }
    cout << endl << "Array 2:";
    for( vector<unsigned short>::iterator ptr = vec_of_rand2.begin(); ptr < vec_of_rand2.end(); ptr++ )
    {
        cout << "\t" << *ptr;
    }
    cout << endl;


    /*
        Button "Berechnen"
    */

    vector<unsigned short> vec_of_results; // vector that will store computation result
    
    unsigned short new_even, new_odd; // intermediate computation values
    unsigned short new_even_f, new_odd_f, new_val; // intermediate computation values
    for( int idx = 0; idx < my_int; idx++ )
    {
        printf("\nArray1: value at position %d is %d =\t", idx, vec_of_rand1[idx] );
        print_ushort2bin(vec_of_rand1[idx]);
        printf("\nArray2: value at position %d is %d =\t", idx, vec_of_rand2[idx] );
        print_ushort2bin(vec_of_rand2[idx]);


        unsigned short op1 = vec_of_rand1[idx]; // operand 1
        unsigned short op2 = vec_of_rand2[idx]; // operand 2

        // Apply AND to operand 1 and operand 2
        new_even = op1 & op2; 
        //printf("\n\tafter AND:\t" );
        //print_ushort2bin(new_even);
        // Hex A is Bin 1010 so we're masking all odd-index bits by 1, "even" bits pass through
        new_even_f = 0xAAAA | new_even; 
        //printf("\nafter ODD mask:\t");
        //print_ushort2bin(new_even_f);
        
        // Apply OR to operand 1 and operand 2
        new_odd = op1 | op2;
        //printf("\n\tafter OR:\t" );
        //print_ushort2bin(new_odd);
        // Hex 5 is Bin 0101 so we're masking all even-index bits by 1, "odd" bits pass through
        new_odd_f = 0x5555 | new_odd; 
        //printf("\nafter EVEN mask:\t");
        //print_ushort2bin(new_odd_f);

        // Apply AND, so 1s of the above masks let correponding bits them pass through.
        // This way the new value is made of the even-indexed bits of operand 1 and 
        // odd-indexed bits of operand 2
        new_val = new_even_f & new_odd_f; 
        printf("\nBIN:\t\t"); print_ushort2bin(new_val);
        printf("\nDEC:\t\t%d", new_val);

        vec_of_results.push_back( new_val );
    }
    cout << endl;

    /*
        Present results
    */


}