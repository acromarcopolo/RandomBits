#include <iostream>
#include <vector>
#include <string>

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

#define FILTER_ODD2(byte)  \
  (byte & 0x80 ? '1' : '0'), \
  (byte & 0x40 ? '1' : '1'), \
  (byte & 0x20 ? '1' : '0'), \
  (byte & 0x10 ? '1' : '1'), \
  (byte & 0x08 ? '1' : '0'), \
  (byte & 0x04 ? '1' : '1'), \
  (byte & 0x02 ? '1' : '0'), \
  (byte & 0x01 ? '1' : '1') 

#define FILTER_EVEN2(byte)  \
  (byte & 0x80 ? '1' : '1'), \
  (byte & 0x40 ? '1' : '0'), \
  (byte & 0x20 ? '1' : '1'), \
  (byte & 0x10 ? '1' : '0'), \
  (byte & 0x08 ? '1' : '1'), \
  (byte & 0x04 ? '1' : '0'), \
  (byte & 0x02 ? '1' : '1'), \
  (byte & 0x01 ? '1' : '0') 


#define NIBBLE_TO_BINARY_PATTERN "%c%c%c%c"
#define FILTER_EVEN(nibble)  \
  1, \
  (nibble & 0x4 ? '1' : '0'), \
  1, \
  (nibble & 0x1 ? '1' : '0') 

#define FILTER_ODD(nibble)  \
  (nibble & 0x8 ? '1' : '0'), \
  1, \
  (nibble & 0x2 ? '1' : '0'), \
  1


using namespace std;


void print_0b( unsigned int number )
{
    if( number >> 1 ){ 
        print_0b( number >> 1 );
    }
    putc( (number & 1) ? '1' : '0', stdout );
}

void extract_even_bits( unsigned int number )
{
    if( number >> 1 ){ 
        print_0b( number >> 1 );
    }
    putc( (number & 1) ? '1' : '0', stdout );
}


int main()
{
  /*  vector<string> msg {"Hello", "C++", "World", "from", "VS Code", "and the C++ extension!"};
    for (const string& word : msg){
       cout << word << " ";
    }
    cout << endl;*/


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
        my_rand = std::rand() % 10000; // quick and dirty random number in the 0..10000 range
        vec_of_rand2.push_back( my_rand ); // populate vector
    }

    // Sort random number vectors in ascending order
    std::sort( vec_of_rand1.begin(), vec_of_rand1.end() );
    std::sort( vec_of_rand2.begin(), vec_of_rand2.end() );

    // Print out resulting sorted vector
    printf("I randomly generated %d numbers, and sorted them for you:\nArray1:", my_int );
    for( vector<unsigned short>::iterator ptr = vec_of_rand1.begin(); ptr < vec_of_rand1.end(); ptr++ )
    {
        cout << "\t" << *ptr ;
    }
    cout << endl << "Array2:";
    for( vector<unsigned short>::iterator ptr = vec_of_rand2.begin(); ptr < vec_of_rand2.end(); ptr++ )
    {
        cout << "\t" << *ptr;
    }
    cout << endl;



    /*
        Button "Berechnen"
    */

    vector<unsigned short> vec_of_results; // vector that will store computation result

    int val = 0;
    printf("Which position would you like to see in both arrrays?");
    while( val >= 0 ) 
    {
        scanf("%d",&val);
        if( val >=0 )
        {
            printf("Array1: value at position %d is %d =\t", val, vec_of_rand1[val] );
            printf("0b " BYTE_TO_BINARY_PATTERN " " BYTE_TO_BINARY_PATTERN " \n",
                BYTE_TO_BINARY(vec_of_rand1[val]>>8), BYTE_TO_BINARY(vec_of_rand1[val]));
            printf("Array2: value at position %d is %d =\t", val, vec_of_rand2[val] );
            printf("0b " BYTE_TO_BINARY_PATTERN " " BYTE_TO_BINARY_PATTERN " \n",
                BYTE_TO_BINARY(vec_of_rand2[val]>>8), BYTE_TO_BINARY(vec_of_rand2[val]));

            /*printf("\nSame same, using print_0b():");
            printf("\nArray1: value at position %d is %d =  ", val, vec_of_rand1[val] );
            print_0b( vec_of_rand1[val] );
            printf("\nArray2: value at position %d is %d =  ", val, vec_of_rand2[val] );
            print_0b( vec_of_rand2[val] );
            printf("\n");*/

        unsigned short op1 = vec_of_rand1[val];
        unsigned short op2 = vec_of_rand2[val];
        unsigned short new_even, new_odd;
        unsigned short new_even_f, new_odd_f;
        
        // Create new short int for operands 1 and 2 
        // FILTER_EVEN: let even-index bits pass through, and set odd-index-bits to 1
            // Apply AND to operand 1 and operand 2
            new_even = op1 & op2; 
//            new_even2 = FILTER_EVEN2(op1>>8) & FILTER_EVEN2(op2>>8); // second byte
            printf("\nEVEN:\t" );
            printf("\nbyte 1: " BYTE_TO_BINARY_PATTERN " & " BYTE_TO_BINARY_PATTERN " = ",
                FILTER_EVEN2(op2), FILTER_EVEN2(op1) );
            printf(" " BYTE_TO_BINARY_PATTERN, FILTER_EVEN2(new_even) );
            printf("\nbyte 2: " BYTE_TO_BINARY_PATTERN " & " BYTE_TO_BINARY_PATTERN " = ",
                FILTER_EVEN2(op2>>8), FILTER_EVEN2(op1>>8) );
            printf(" " BYTE_TO_BINARY_PATTERN, FILTER_EVEN2(new_even>>8) );

            printf("\nunfiltered:\t " BYTE_TO_BINARY_PATTERN " " BYTE_TO_BINARY_PATTERN " \n",
                BYTE_TO_BINARY(new_even>>8), BYTE_TO_BINARY(new_even) );
            new_even_f = 0xAAAA | new_even;
            printf("\nfiltered:\t " BYTE_TO_BINARY_PATTERN " " BYTE_TO_BINARY_PATTERN " \n",
                BYTE_TO_BINARY(new_even_f>>8), BYTE_TO_BINARY(new_even_f) );


        // FILTER_ODD: Let odd-index bits pass through, and set even-index-bits to 1
            // Apply OR to operand 1 and operand 2
            new_odd = op1 | op2;
            printf("\nODD:\t" );
            printf("\nbyte 1: " BYTE_TO_BINARY_PATTERN " | " BYTE_TO_BINARY_PATTERN " = ",
                FILTER_ODD2(op2), FILTER_ODD2(op1) );
            printf(" " BYTE_TO_BINARY_PATTERN, FILTER_ODD2(new_odd) );
            printf("\nbyte 2: " BYTE_TO_BINARY_PATTERN " | " BYTE_TO_BINARY_PATTERN " = ",
                FILTER_ODD2(op2>>8), FILTER_ODD2(op1>>8) );
            printf(" " BYTE_TO_BINARY_PATTERN, FILTER_ODD2(new_odd>>8) );    

            printf("\nunfiltered:\t " BYTE_TO_BINARY_PATTERN " " BYTE_TO_BINARY_PATTERN " \n",
                BYTE_TO_BINARY(new_odd>>8), BYTE_TO_BINARY(new_odd) );
            new_odd_f = 0x5555 | new_odd;
            printf("\nfiltered:\t " BYTE_TO_BINARY_PATTERN " " BYTE_TO_BINARY_PATTERN " \n",
                BYTE_TO_BINARY(new_odd_f>>8), BYTE_TO_BINARY(new_odd_f) );


            unsigned short new_val;
            new_val = new_even_f & new_odd_f;   
            printf("\n New val: " BYTE_TO_BINARY_PATTERN " " BYTE_TO_BINARY_PATTERN " \n",
                BYTE_TO_BINARY(new_val>>8), BYTE_TO_BINARY(new_val) );
        } else {
            printf("\nbye\nbye\n");
            break;
        }
    }
/*
    vector<unsigned short> new_vec; // vector that will store random numbers
    for( int ii=0; ii<my_int; ii++ )
    {
        unsigned short op1 = vec_of_rand1[ii];
        unsigned short op2 = vec_of_rand2[ii];
        unsigned short new_even1, new_even2, new_odd;
        
        if( ii%2 ) // even index
        {
            new_even1 = FILTER_EVEN(op1) & FILTER_EVEN(op2);
            new_even2 = FILTER_EVEN(op1>>8) & FILTER_EVEN(op2>>8);
            printf("\nEVEN: value at position %d is %d =\t", val, vec_of_rand2[val] );
            printf("0b " BYTE_TO_BINARY_PATTERN " " BYTE_TO_BINARY_PATTERN " \n",
                BYTE_TO_BINARY(new_even2), BYTE_TO_BINARY(new_even1));
           
        } else { // odd index

        }
        //new_val = vec_of_rand1[val] >> 1  &  vec_of_rand2[val] >> 1
        //new_val = new_even & new_odd;
    }*/

}