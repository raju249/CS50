#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int n;
    // takes height from user and keeps prompting for a number 
    // between 0 and 23
    do
    {
        printf("Enter a positive height: ");
        n = GetInt();
    } while(n < 0 || n > 23);
    
    // loop for printing the desired pattern of given height
    for(int i=1; i <= n; i++)
    {
        // print spaces
        for(int space = 1; space <= n - i; space++)
        {
            printf(" ");
        }
        
        // print "#"
        for(int hash = 1; hash <= (i + 1); hash++)
        {
            printf("#");
        }
        
        // prints newline
        printf("\n");
    }
    
    
    
}
