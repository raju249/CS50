/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */

// includes
#include <stdio.h>
#include <stdint.h>

// defining a byte for 512 byte chunks
typedef uint8_t BYTE;

int main(void)
{
    // TODO
    // opening a file to read images
    FILE* rawdata = fopen("card.raw","r");
    
    // sanity check for any error in opening file
    if (rawdata == NULL)
    {
        printf("Cannot open card.raw\n");
        return 1;
    }
    
    // output file
    FILE* output = NULL;
    
    // counter for jpgs
    int jpgs = 0;
    
    BYTE buffer[512] = {0};
   
    // loop until end is encountered
    while(!feof(rawdata))
    {
        // jpgname placeholder
        char jpgname[8];
        
        // reading data for card into buffer
        int i = fread(buffer,sizeof(buffer),1,rawdata);
        
        if (i == 0)
        {
            break;
        }
        // checking the first four bytes of buffer
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] == 0xe0 || buffer[3] == 0xe1))
        {
            // closing the output file if open initially
            if (output != NULL)
            {
                fclose(output);
            }
            
            // name for jpg file
            sprintf(jpgname,"%03d.jpg",jpgs);
            
            // open new file
            output = fopen(jpgname,"w");
            
            // increment jpgs counter
            jpgs++;
            
            // write to file
            fwrite(buffer,sizeof(buffer),1,output);
        }
        else
        {
            if (jpgs > 0)
            {
                // continue till one file finishes
                fwrite(buffer,sizeof(buffer),1,output);
            }
        }
        
        
    }   
    //close last jpeg, if open
    if (jpgs > 0)
    {
        fclose(output);
    }
    
    //close card file
    fclose(rawdata);

    return 0;
    
}
