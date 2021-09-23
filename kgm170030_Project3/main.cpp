/*
    Kate Malinis
    kgm170030
 
    Project 3
    CS 1337.505
 */

#include "declarations.h"
using namespace std;

int main()
{
    // Open the file at the beginning of the program
    ofstream textFile;
    textFile.open("output.txt");
    
    // This function gets the desired integer from the user
    getInteger(textFile);

    return 0;
}

// This function gets the integer from the user, supplying various test cases
void getInteger(std::ofstream& outputFile)
{
    unsigned short oddInteger;
    
    // Do/while function ensures that the program will run AT LEAST once.
    // The while loop at the end gives user the option of running it again for further calculations.
    do
    {
        cout << "Enter an odd integer: ";
        cin >> oddInteger;
        
        // If the user enters 0, the program will terminate
        if (oddInteger == 0)
        {
            cout << "Since you entered 0, the program will end now. " << endl;
            cout << "Any valid numbers entered prior to entering 0 will produce magic squares in the text file now." << endl;
            
            // Close the file after user enters 0
            outputFile.close();
        }
        
        else
        {
            while (oddInteger % 2 == 0 || oddInteger > 999)
            {
                cout << "You entered something that is not valid for magic squares." << endl;
                cout << "Enter an odd integer: ";
                cin >> oddInteger;
            }
        }
        
        // Call the function to proceed processing the square once all input verifications passed
        createAndPrintSquare(oddInteger, outputFile);
        
    } while (oddInteger != 0);      // Continue looping the do/while until user enters 0
}

// This function creates the magic square, given the order from the user
void createAndPrintSquare(unsigned short orderN, std::ofstream& outputFile)
{
    // Dynamically allocate a new magic square using the user-input integer
    unsigned short ** magicSquare = new unsigned short *[orderN];       // row declaration
    for (unsigned short index = 0; index < orderN; ++index)             // column declaration
    {
        magicSquare[index] = new unsigned short[orderN];
    }
    
    // Initialize the position for 1
    int row = 0;
    int column = orderN / 2;
    
    // Place the values in the magic square
    
    /*
     Algorithm: (De la Loubere's algorithm)
     1. Place a in the middle of the top row
     2. All numbers are then placed one column to the right, and one row up from the previous numbers
     3. Whenever the next number placement is above the top row, stay in that column and place the number in the bottom row
     4. Whenever the next number placement is outside the rightmost column, stay in that row and place the number in the leftmost column
     5. When encountering a filled-in space, place the number directly below the previous number
     6. When the next number position is outside both a row and a column, place the number directly beneath the previous number
     */
    
    for (int index = 1; index <= orderN * orderN; ++index)  // This loop controls the wrapping around of number placements
    {
        magicSquare[row][column] = index;
        
        row--;      // Decrement the row (one row up)
        column++;   // Increment the column (one column to the right)
        
        // The position will wrap around based on the following conditions..
        if (index % orderN == 0)        // If there are no more spaces to fill in the numbers,
        {
            row += 2;       // Increment the row by 2
            --column;       // Decrement the column by 1
        }
        
        else
        {
            if (column == orderN)   // If the column placement is outside the rightmost column,
            {
                column -= orderN;   // keep the row the same, just place the number in the leftmost column
            }
            
            else if (row < 0)       // If row is not in bounds,
            {
                row += orderN;      // set row to be the bottom row
            }
        }
    }
    
    // Output the information about the magic square
    outputFile << "Magic square with order: " << orderN << endl;
    outputFile << "Magic sum: " << getMagicSum(orderN) << endl;
    outputFile << "\n";     // add a newline so the following squares do not look cluttered together
    
    // Output the magic square
    for (int rowIndex = 0; rowIndex < orderN; rowIndex++)
    {
        for (int columnIndex = 0; columnIndex < orderN; columnIndex++)
        {
            outputFile << setw(3) << magicSquare[rowIndex][columnIndex] << " ";
        }
        outputFile << "\n";
        outputFile << "\n";
    }
    
    // Delete the allocated array to prevent memory leak afterwards
    for (int index2 = 0; index2 < orderN; index2++)
    {
        delete [] magicSquare[index2];
    }
    delete [] magicSquare;
}

// This function calculates the magic sum, given the order
int getMagicSum(unsigned short order)
{
    return order * (( order * order ) + 1 ) / 2;
}
