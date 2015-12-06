#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#pragma pack(push,2)
typedef struct tagFileHeader {
	unsigned short	    type;
	unsigned long	    size;
	unsigned short	    r1;
	unsigned short	    r2;
	unsigned long	    offBits;
} FileHeader;
#pragma pack(pop)

typedef struct tagInfoHeader{
	unsigned long	    size;
	long	            width;
	long	            height;
	unsigned short	    planes;
	unsigned short	    bitCount;
	unsigned long	    compression;
	unsigned long	    imageSize;
	long	            XPelsPerMeter;
	long	            YPelsPerMeter;
	unsigned long	    clrUsed;
	unsigned long	    clrImportant;
} InfoHeader;


int main(int argc, char* argv[])
{
    const int n = 256;
    char fileName[n];
    if (argc > 1)
        strcpy (fileName, argv[1]);
    else
        strcpy (fileName, "def.bmp");

    FILE* pIn = fopen (fileName, "r");

    FileHeader fileHeader;
    InfoHeader infoHeader;

    fread (&fileHeader, sizeof (FileHeader), 1, pIn);
    fread (&infoHeader, sizeof (InfoHeader), 1, pIn);

    int width = infoHeader.width;
    int height = infoHeader.height;

    int imageSize = (fileHeader.size - fileHeader.offBits);

    void* pBits = malloc (imageSize);

    fread (pBits, sizeof(byte), imageSize, pIn);

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;

    for (int y = height - 1; y >= 0; y--)
    {
        for (int x = 0; x < width; x++)
        {
            byte* p = (byte*)(pBits + 3*y*height + 3*x);

            pos.X = x;
            pos.Y = height - y - 1;

            int attr = 0;

            if (p[0] > 100)
                attr |= BACKGROUND_BLUE;
            if (p[1] > 100)
                attr |= BACKGROUND_GREEN;
            if (p[2] > 100)
                attr |= BACKGROUND_RED;

            SetConsoleTextAttribute(hConsole, attr);
            SetConsoleCursorPosition(hConsole, pos);

            printf (" ");
        }
    }

    free (pBits);
    fclose (pIn);

    getch ();

    return 0;
}
