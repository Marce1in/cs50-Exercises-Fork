#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <cs50.h>

typedef uint8_t BYTE; //8-bit unsigned integer (1 byte)

int main(int argc, char *argv[])
{
    //Check if there's only one commandline argument
    if (argc != 2)
    {
        printf("Usage: recover [something]\n");
        return 1;
    }
    //Open the file
    FILE *open_input = fopen(argv[1], "r");

    //Check if the file is valid
    if (open_input == NULL)
    {
        fclose(open_input);
        printf("Invalid file\n");
        return 1;
    }

    const int BLOCK_SIZE = 512; //The size of each chunk "fread" gonna read
    BYTE buffer[BLOCK_SIZE]; //Store the variables that "fread" is reading


    int i = 0; //counter how many JPEG exists in the card
    bool in_a_jpg = false; //check if the loop is in a JPEG
    FILE *blank_file = NULL; //blank file used to create new ones
    while (fread(&buffer, sizeof(BYTE), BLOCK_SIZE, open_input) == BLOCK_SIZE) //Read all the file by 512 chunks
    {
        char file_name[8]; //Create memory space for the name
        sprintf(file_name, "%03i.jpg", i); //Create a new name for each new JPEG file

        if  (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0) //Search for the JPEG header files
        {
            if (i == 0) //if this is the first JPEG
            {
                blank_file = fopen(file_name, "w"); //Create a new file using the name created
                fwrite(&buffer, sizeof(BYTE), BLOCK_SIZE, blank_file); //Write in this file
                i++;
            }
            else //if is not the first JPEG
            {
                fclose(blank_file); //Close the old JPEG
                blank_file = fopen(file_name, "w"); //Create a new file using the name created
                fwrite(&buffer, sizeof(BYTE), BLOCK_SIZE, blank_file); //Write in this file
                i++;
            }
            in_a_jpg = true; //Register that the loop is in a JPEG
        }
        else if (in_a_jpg) //if the loop is in a JPEG and the next 512 chunk do not have the JPEG header files
        {
            fwrite(&buffer, sizeof(BYTE), BLOCK_SIZE, blank_file); //Keep Writing in the file
        }
    }

    //Close the files
    fclose(blank_file);
    fclose(open_input);
}