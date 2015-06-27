#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    
    if (argc != 2)
    {
        // handles case where arguments are lower
        printf("Yoou screwed up!!!");
        return 1;
    }
    else
    {
        string text = GetString();
        int k = atoi(argv[1]);
        
        // encryptig the text
        
        for (int i = 0, n = strlen(text); i < n; i++)
        {
            if (isalpha(text[i]))
            {
                if (islower(text[i]))
                {
                    // handles lower case
                    int lower = (((text[i] - 97 + k) % 26) + 97);
                    printf("%c", lower);
                }
                if (isupper(text[i]))
                {
                    // handles upper case
                    int upper = (((text[i] - 65 + k) % 26) + 65);
                    printf("%c", upper);
                }
            }
            else
            {
                // handles input other than alphabets
                printf("%c", text[i]);
            }
        }
        printf("\n");
    }
    return 0;
}
