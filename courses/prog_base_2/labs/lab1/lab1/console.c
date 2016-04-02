#include "console.h"
#include "errormodule.h"
#include <windows.h>

struct tagConsole_Private
{
    HANDLE hConsole_Output;
    HANDLE hConsole_Input;
    int width;
    int height;
};

int Console_initialize (Console* c, int width, int height)
{
    int status = 0;

    Console_Private* cp = malloc (sizeof (Console_Private));

    if (cp == NULL)
    {
        status = 1;
        ErrorModule_setLastError(status);
        return status;
    }

    c->cp = cp;

    c->cp->hConsole_Output = GetStdHandle(STD_OUTPUT_HANDLE);
    c->cp->hConsole_Input = GetStdHandle (STD_INPUT_HANDLE);
    c->cp->width = width;
    c->cp->height = height;

    char cmd[32];
    sprintf(cmd, "mode con: lines=%d cols=%d", height, width);
    system(cmd);

    ErrorModule_setLastError(status);
    return status;
}
int Console_deinitialize (Console* c)
{
    int status = 0;

    CloseHandle (c->cp->hConsole_Output);
    CloseHandle(c->cp->hConsole_Input);

    ErrorModule_setLastError(status);
    return status;
}

int Console_showCinema (Console* c)
{
    int status = 0;

    const int n = 256;
    char szFileName[n];
    strcpy (szFileName, "cinema.bmp");

    HBITMAP hBmp;
    BITMAP bmp;

    hBmp = (HBITMAP)LoadImage (NULL, szFileName, IMAGE_BITMAP, NULL, NULL, LR_LOADFROMFILE);

    if (hBmp == NULL)
    {
        status = 2;
        ErrorModule_setLastError(status);
        return status;
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

            SetConsoleTextAttribute(c->cp->hConsole_Output, attr);
            SetConsoleCursorPosition(c->cp->hConsole_Output, pos);

            printf (" ");
    	}
	}

    ErrorModule_setLastError(status);
    return 0;
}

int Console_getSize (Console* c, COORD* cd)
{
    int status = 0;

    COORD coord;

    coord.X = c->cp->width;
    coord.Y = c->cp->height;

    memcpy(cd, &coord, sizeof (COORD));

    ErrorModule_setLastError(status);
    return status;
}

int Console_setPosition (Console* c, int x, int y)
{
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(c->cp->hConsole_Output, pos);

    return 0;
}
int Console_printSymbol (Console* c, char ch, int attr)
{
    SetConsoleTextAttribute(c->cp->hConsole_Output, attr);
    printf (" ");

    return 0;
}

int Console_showCinemaHall (Console* c, CinemaHall* ch)
{
    const int marginTop = 20;
    const int marginLeft = 10;
    const int marginRight = 10;

    const int secondMarginLeft = 1;
    const int secondMarginRight = 1;
    int status = 0;
    int dl = 0;
    int dr = 0;
    for (int i = 0; i < CinemaHall_getQuantity (ch); i++)
    {
        if (i != 0 && i % (c->cp->width - marginLeft - marginRight - dl - dr) == 0)
            dl+=secondMarginLeft, dr+=secondMarginRight;

        int y = marginTop + (i / (c->cp->width - marginLeft - marginRight - dl - dr));

        int x = marginLeft +
                i % (c->cp->width - marginLeft - marginRight - dl - dr);

        Console_setPosition (c, x, y);

        int attr = 0;

        switch ( CinemaHall_getSeatState(ch, i) )
        {
        case SEAT_AVAILABLE:
            attr = BACKGROUND_GRAY;
            break;
        case SEAT_BOUGHT:
            attr = BACKGROUND_RED;
            break;
        case SEAT_BOOKED:
            attr = BACKGROUND_YELLOW;
            break;
        }
        Console_printSymbol (c, ' ', attr);
    }

    ErrorModule_setLastError(status);
    return status;
}

char* Console_errorCode_toString (int code)
{
    const char* errorStrings [] =
    {
        "All success",
        "Error allocating memory"
        "Error no cinema picture"
    };
    const int errorSize = sizeof (errorStrings) / sizeof (char*);

    return errorStrings [code % errorSize];
}
