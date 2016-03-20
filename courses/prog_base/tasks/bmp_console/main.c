// libgdi32.a needed

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

#pragma comment( lib, "libgdi32.lib" )

int main(int argc, char* argv[])
{
    const int n = 256;
    char szFileName[n];
    if (argc > 1)
        strcpy (szFileName, argv[1]);
    else
        strcpy (szFileName, "def.bmp");

    HBITMAP hBmp;
    BITMAP bmp;

    hBmp = (HBITMAP)LoadImage (NULL, szFileName, IMAGE_BITMAP, NULL, NULL, LR_LOADFROMFILE);

    if (hBmp == NULL)
    {
        printf ("Error: No File");
        getch();
        return 0;
    }

    GetObject (hBmp, sizeof (BITMAP), &bmp);

    int BitCount = bmp.bmPlanes*bmp.bmBitsPixel;
    int colorSize = 0;

    switch (BitCount)
    {
           case 1:
           case 4:
           case 8:
           case 32:
                colorSize = sizeof (RGBQUAD)* (1 << BitCount);
                break;
           case 16:
           case 24:
                colorSize = NULL;
                break;
           }

    int dataSize = bmp.bmWidthBytes*bmp.bmHeight;

    void* pvBits = malloc (dataSize);

    BITMAPINFO* pBmi = (BITMAPINFO*)malloc(sizeof (BITMAPINFOHEADER) + colorSize);

    pBmi->bmiHeader.biSize = sizeof (BITMAPINFOHEADER);
    pBmi->bmiHeader.biWidth = bmp.bmWidth;
    pBmi->bmiHeader.biHeight = -bmp.bmHeight;
    pBmi->bmiHeader.biPlanes = 1;
    pBmi->bmiHeader.biBitCount = BitCount;
    pBmi->bmiHeader.biCompression = BI_RGB;
    pBmi->bmiHeader.biSizeImage = dataSize;
    pBmi->bmiHeader.biXPelsPerMeter = pBmi->bmiHeader.biYPelsPerMeter = 0;
    pBmi->bmiHeader.biClrImportant = 0;

    HDC hDC = GetDC (0);
    GetDIBits (hDC, hBmp, 0, bmp.bmHeight, pvBits, pBmi, DIB_RGB_COLORS);
    ReleaseDC (0, hDC);

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    for (int y = 0; y < bmp.bmHeight; y++)
    {
    	for (int x = 0; x < bmp.bmWidth; x++)
    	{
    		BYTE* pixel = (BYTE*)(pvBits + 4*y*bmp.bmWidth + x*4);

            pos.X = x;
            pos.Y = y;

            //pixel[0] - BLUE pixel[1] - GREEN pixel[2] - RED pixel[3] - alpha

            int attr = 0;

            if (pixel[0] > 100)
                attr |= BACKGROUND_BLUE;
            if (pixel[1] > 100)
                attr |= BACKGROUND_GREEN;
            if (pixel[2] > 100)
                attr |= BACKGROUND_RED;

            SetConsoleTextAttribute(hConsole, attr);
            SetConsoleCursorPosition(hConsole, pos);

            printf (" ");
    	}
	}

	getch();
    return 0;
}
