// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

typedef uint8_t BYTE;
typedef int16_t TWOBYTES;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    BYTE h_buffer[HEADER_SIZE]; //Create a Header buffer
    TWOBYTES s_buffer; //Create a samples buffer

    //Copy the header of input in h_buffer
    fread(&h_buffer, sizeof(BYTE), HEADER_SIZE, input);

    //Write h_buffer in output
    fwrite(&h_buffer, sizeof(BYTE), HEADER_SIZE, output);

    //Read each sample
    while (fread(&s_buffer, sizeof(TWOBYTES), 1, input) == 1)
    {
        s_buffer = s_buffer * factor; //Multiply each sample by the factor
        fwrite(&s_buffer, sizeof(TWOBYTES), 1, output); //Write the new value of samples in output
    }

    // Close files
    fclose(input);
    fclose(output);
}
