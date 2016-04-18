#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include <stdio.h>
#include <time.h>

#include "menu.h"

#define ID_EDIT_LOW 0
#define ID_EDIT_NAME 0
#define ID_EDIT_SURNAME 1
#define ID_EDIT_BIRTHDATE 2
#define ID_EDIT_YEAR 3
#define ID_EDIT_MAGIC 4
#define ID_EDIT_COMPANY 5
#define ID_EDIT_COUNTRY 6
#define ID_EDIT_HIGH 7

#define QEDIT ID_EDIT_HIGH-ID_EDIT_LOW

#define ID_STATIC_LOW 50
#define ID_STATIC_NAME 50
#define ID_STATIC_SURNAME 51
#define ID_STATIC_BIRTHDATE 52
#define ID_STATIC_YEAR 53
#define ID_STATIC_MAGIC 54
#define ID_STATIC_COMPANY 55
#define ID_STATIC_COUNTRY 56
#define ID_STATIC_HIGH 57

#define QSTATIC ID_STATIC_HIGH-ID_STATIC_LOW


/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */

int WINAPI WinMain (HINSTANCE hThisInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpszArgument,
                     int nCmdShow)
{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    srand (time (NULL));

    TCHAR szClassName[ ] = _T("MyWindow");

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_WINDOWFRAME;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    HMENU hMainMenu = LoadMenu (hThisInstance, szClassName);

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           _T("windows"),       /* Title Text */
           WS_OVERLAPPEDWINDOW, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           640,                 /* The programs width */
           480,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           hMainMenu,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );

    for (int i = 0; i < QEDIT; i++)
        CreateWindowEx (
                        WS_EX_OVERLAPPEDWINDOW,
                        _T("Edit"),
                        NULL,
                        WS_CHILD | WS_VISIBLE | ES_NOHIDESEL,
                        0,0,0,0,
                        hwnd, (HMENU)(ID_EDIT_LOW+i), hThisInstance, NULL
                        );
    const TCHAR* labels [QSTATIC] = {_T("name: "),
                              _T("surname: "),
                              _T("birthdate: "),
                              _T("year: "),
                              _T("magic: "),
                              _T("name: "),
                              _T("country: ")
                            };
    for (int i = 0; i < QSTATIC; i++)
        CreateWindowEx (
                        0,
                        _T("Static"),
                        labels[i],
                        WS_CHILD | WS_VISIBLE | SS_LEFT,
                        0,0,0,0,
                        hwnd, (HMENU)(ID_STATIC_LOW+i), hThisInstance, NULL
                        );




    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}

void reset (HWND hwnd)
{
    HWND hEdits[QEDIT];
    const TCHAR* def[] = {_T("Aaron"),
                           _T("Smith"),
                           _T("1971-01-01"),
                           _T("2000"),
                           _T("2.00"),
                            _T("Microsoft"),
                           _T("England")};
    for (int i = 0; i < QEDIT; i++)
        SetWindowText (GetDlgItem (hwnd, ID_EDIT_LOW+i), def[i]);

}


/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{

    switch (message)                  /* handle the messages */
    {
        case WM_CREATE:
        break;
        case WM_SHOWWINDOW:
            reset (hwnd);
            break;
        case WM_SIZE:
            {
                HWND hEdits[QEDIT];
                HWND hLabels[QSTATIC];
                for (int i = 0; i < QEDIT; i++)
                    hEdits[i] = GetDlgItem (hwnd, ID_EDIT_LOW+i);
                for (int i = 0; i < QSTATIC; i++)
                    hLabels[i] = GetDlgItem (hwnd, ID_STATIC_LOW+i);

                int cxClient = LOWORD (lParam);
                int cyClient = HIWORD (lParam);


                int marginY = 10;
                int marginX = 15;
                int marginCenterLeft = 100;
                int editHeight = 20;
                int editWidth = 150;
                int staticWidth = 80;
                int staticHeight = 20;
                int cxStart = cxClient/2 - (editWidth+staticWidth+marginX)/2;
                int cyStart = cyClient/2 - (QEDIT+1)*(editHeight + marginY)/2;
                int tab = 35;

                int tabs[] = {0, 0, 0, 0, 0, tab, tab};

                for (int i = 0; i < QEDIT; i++)
                {
                     MoveWindow (
                     hLabels[i],
                     tabs[i] + cxStart, cyStart + i*staticHeight + i*marginY,
                     staticWidth, staticHeight,
                     TRUE
                     );
                     MoveWindow (
                     hEdits[i],
                     tabs[i] + cxStart + staticWidth + marginX, cyStart + i*staticHeight + i*marginY,
                     editWidth, editHeight,
                     TRUE
                     );
                }

                RECT clientRect;
                clientRect.left = 0;
                clientRect.top = 0;
                clientRect.bottom = cyClient;
                clientRect.right = cxClient;

                InvalidateRect (hwnd, &clientRect, TRUE);
            }
            break;
        case WM_COMMAND:
             switch (LOWORD (wParam))
             {
                    case IDM_EXIT:
                         SendMessage (hwnd, WM_CLOSE, NULL, NULL);
                         break;
                    case IDM_RESET:
                            reset (hwnd);
                            break;
                    case IDM_RANDOM:
                        {

                        int q = 5;
                        const TCHAR* names [] =
                            {
                                _T("Aaron"),
                                _T("Austin"),
                                _T("Blake"),
                                _T("Carl"),
                                _T("Charles"),
                            };
                        const TCHAR* snames [] =
                            {
                                _T("Smith"),
                                _T("Williams"),
                                _T("Miller"),
                                _T("Anderson"),
                                _T("Thomas"),
                            };
                        const TCHAR* companyNames [] =
                        {
                            _T("Microsoft"),
                            _T("NBNL"),
                            _T("DataArt"),
                            _T("LimBit"),
                            _T("Ahnenerbe")
                        };
                        const TCHAR* countries [] =
                        {
                            _T("England"),
                            _T("USA"),
                            _T("Russia"),
                            _T("Ukraine"),
                            _T("Moldova")
                        };

                        HWND hEdits[QEDIT];
                        for (int i = 0; i < QEDIT; i++)
                            hEdits[i] = GetDlgItem (hwnd, ID_EDIT_LOW+i);
                        SetWindowText(hEdits[0], names[rand () % q]);
                        SetWindowText(hEdits[1], snames[rand () % q]);

                        TCHAR buffer[20];

                        _stprintf (buffer, _T("%d-%02d-%02d"), rand () % 20 + 1971, rand()%12, rand()% 30);
                        SetWindowText(hEdits[2], buffer);

                        _stprintf (buffer, _T("%d"), rand () % 20 + 1971);
                        SetWindowText(hEdits[3], buffer);

                        _stprintf (buffer, _T("%.2f"), (double)(rand () % 20) / (double)(rand() % 50 + 1));
                        SetWindowText(hEdits[4], buffer);

                        SetWindowText(hEdits[5], companyNames[rand () % q]);
                        SetWindowText(hEdits[6], countries[rand () % q]);
                        }
                        break;
             }
             break;
        case WM_DESTROY:

            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            break;
        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}
