/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "dictionary.h"

/** 
 * Implementing a trie datastructure
 */
 typedef struct trie
 {
    bool isAword;
    struct trie* children[27];
 }
 trie;
 
 trie* firstnode;
 
 // function to freenode
void freenode(trie* firstnode)
{
    for(int i = 0; i < 27; i++)
    {
        if (firstnode -> children[i] != NULL)
        {
            freenode(firstnode -> children[i]);
        }
    }
    free(firstnode);
    return;
}
 // total number of words counter
 int numberOfWords = 0;


/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    // TODO
    // letter as int
    int aAsInt = (int)'a';
    int zAsInt = (int)'z';
    
    // set current node to first node
    trie* currentnode = firstnode;
    
    // looping through each letter in word
    int i = 0;
    while(word[i] != '\0')
    {
        char ch = word[i];
        
        
        // find is ch is apostrophe
        if (word[i] == '\'')
        {
            ch = zAsInt + 1;
        }
        // converting letter between 0 and 25
        int childIndex = tolower(ch) - aAsInt;
        
        if (currentnode -> children[childIndex] != NULL)
        {
            currentnode = currentnode -> children[childIndex];
            i++;
        }
        else
        {
            return false;
        }
        
    }
    
    
        if (currentnode -> isAword == true)
        {
            
            return true;
        }
        else
        {
            return false;
        }
    
     
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // TODO
    
     // integer mapping for a and z
   int aAsInt = (int)'a';
   int zAsInt = (int)'z';
   
   // opening the dictionary file
   FILE* fp = fopen(dictionary,"r");
   
   // sanity check for null returned reference
   if (fp == NULL)
   {
    return false;
   }
   // mallocking memory for first node
   firstnode = (trie*) malloc(sizeof(trie));
   
   // integer for current position in children array
   int character = 0;
   
   // cursor node
   trie* currentnode = NULL;
   
   // looping through dictionary until end of file is encountered
   while(EOF != (character = fgetc(fp)))
   {
   		// setting current node to first node
   		currentnode = firstnode;
   		
   		// iterating through character and adding each 
   		// letter to children until "\n"
   		for(; character != '\n'; character = fgetc(fp))
   		{
   			// if apostrophe then store in 
   			if (character == '\'')
   			{
   				character = zAsInt + 1;
   			}
   			
   			// if the character is not in trie...create one
   			if (currentnode -> children[character - aAsInt] == NULL)
   			{
   				// malloc a new node
   				currentnode -> children[character - aAsInt] = (trie*)malloc(sizeof(trie));
   				currentnode = currentnode -> children[character - aAsInt];
   			}
   			// got to address in children
   			else
   			{
   				currentnode = currentnode -> children[character - aAsInt];
   			}
   			
   		}
   		currentnode -> isAword = true;
   		numberOfWords++;
   }
   
   // close the dictionary file
   fclose(fp);
   return true;
    
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // TODO
    return numberOfWords;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    // TODO
    trie* currentnode = firstnode;
    freenode(currentnode);
    return true;
    
}
