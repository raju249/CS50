#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    float change;
    double changeInDollars;
    int coins = 0;
    do
    {
        // gets th change owed by user in dollars
        printf("Enter the change you owe: ");
        change = GetFloat();
        
    } while (change <= 0);
    
    // converting the dollars in cents
    changeInDollars = round(change * 100);
    
    // counting the number of coins
    while(changeInDollars >= 25)
    {
        // counts number of quarters
        coins++;
        changeInDollars -= 25;
    }
    while(changeInDollars >= 10 )
    {
        // counts number of dimes
        coins++;
        changeInDollars -= 10;
    }
    while(changeInDollars >= 5)
    {
        // counts number of nickels
        coins++;
        changeInDollars -= 5;
    }
    while(changeInDollars >= 1)
    {
        // counts number of pennies
        coins++;
        changeInDollars -= 1;
    }
    
    // printing total coins
    printf("%d\n",coins);   
}
