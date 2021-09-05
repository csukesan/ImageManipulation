#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct header{
    char TypeString[4];
    char numberOfBands;
    int numberOfRows;
    int numberOfColumns;
    char numberOfBits;
}header_t;

int main(int argc, char *argv[])
{

    header_t header14;
    FILE *input;
    input = fopen(argv[1], "rb");
    FILE *output;
    output = fopen(argv[2], "wb");
    char *p;

    int CropC = strtol(argv[3],&p,10);
    int CropR = strtol(argv[4],&p,10);
    int CropWidth = strtol(argv[5],&p,10);
    int CropHeight = strtol(argv[6],&p,10);
    memset(&header14,0,sizeof(header14));

    fread(&header14.TypeString, sizeof(header14.TypeString),1,input);
    fread(&header14.numberOfBands,sizeof(header14.numberOfBands),1,input);
    fread(&header14.numberOfRows, sizeof(header14.numberOfRows) ,1, input);
    fread(&header14.numberOfColumns,sizeof(header14.numberOfColumns), 1, input);
    fread(&header14.numberOfBits,sizeof(header14.numberOfBits),1,input);

    fwrite(header14.TypeString, sizeof(header14.TypeString),1,output);
    fwrite(&header14.numberOfBands,sizeof(header14.numberOfBands),1,output);
    fwrite(&CropHeight, sizeof(CropHeight), 1 , output);
    fwrite(&CropWidth, sizeof(CropWidth),1, output);
    fwrite(&header14.numberOfBits, sizeof(header14.numberOfBits),1, output);


    unsigned char **Data = (unsigned char **) malloc(sizeof(char*)*header14.numberOfRows);
    for(int i = 0;i<header14.numberOfRows;i++)
    {
        Data[i]=(char *)malloc(sizeof(char)*header14.numberOfColumns*header14.numberOfBands);
    }

    for(int i=0;i<header14.numberOfRows;i++)
    {
        for(int j = 0; j<header14.numberOfColumns*header14.numberOfBands; j++)
        {
            fread(&Data[i][j],sizeof(char),1,input);
        }
    }
char zero = 0;
    for (int i = 0; i < CropHeight; i++)
	{
		for (int j = 0; j < CropWidth * 3; j++)
		{
			if (CropC*3 +j >= header14.numberOfColumns * 3 || CropR+i >= header14.numberOfRows) //if outside of the image put 0
			{
				fwrite(&zero, 1, 1, output);
			}
			else
				fwrite(&Data[CropR + i][j + CropC * 3], 1, 1, output);
		}

	}



    fclose(input);
    fclose(output);


return 0;
}
