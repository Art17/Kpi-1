#include <winsock2.h>
#include <windows.h>

#pragma comment(lib, "ws2_32.lib")

#define NO_FLAGS_SET 0
#define PORT 80
#define MAXBUFLEN 20480 // How much is printed out to the screen

char* myRequest (SOCKET recvSocket, const char request [], char buffer [], int maxLen)
{
    send(recvSocket, request, strlen(request), 0);

    // Receieve
    int numrcv = recv(recvSocket, buffer, maxLen, NO_FLAGS_SET);
    int status = 0;
    if (numrcv == SOCKET_ERROR)
    {
        printf("ERROR: recvfrom unsuccessful\r\n");
        status = closesocket(recvSocket);
        if(status == SOCKET_ERROR)
            printf("ERROR: closesocket unsuccessful\r\n");
        status = WSACleanup();
        if (status == SOCKET_ERROR)
            printf("ERROR: WSACleanup unsuccessful\r\n");
        system("pause");
        return(1);
    }

    return buffer;
}

char* getNString (char source [], char dest[], int num)
{
    int i = 0;
    int c = 0;

    while (c < num && i < strlen (source))
    {
        if (source[i++] == '\n')
            c++;
    }
    strcpy (dest, source + i);

    return dest;
}

int isVowel(int ch)
{
    int c = toupper(ch);

    return (c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U');
}

int task (char str [])
{
    int ans = 0;
    char* buf = strtok(str, " .,!?\n");
    while (buf)
    {
        if (!isVowel(buf[0]))
            ans++;
       buf = strtok(NULL, " .,!?\n");
    }
    return ans;
}

int main(void) {
    WSADATA Data;
    SOCKADDR_IN recvSockAddr;
    SOCKET recvSocket;
    int status;
    struct hostent * remoteHost;
    char * ip;
    const char * host_name = "pb-homework.appspot.com";
    char buffer[MAXBUFLEN];
    memset(buffer,0,MAXBUFLEN);
    // Initialize Windows Socket DLL
    status = WSAStartup(MAKEWORD(2, 2), &Data);
    if(status != 0)
    {
        printf("ERROR: WSAStartup unsuccessful\r\n");
        return 0;
    }
    // Get IP address from host name
    remoteHost = gethostbyname(host_name);
    ip = inet_ntoa(*(struct in_addr *)*remoteHost->h_addr_list);
    printf("IP address is: %s.\n", ip);
    memset(&recvSockAddr, 0, sizeof(recvSockAddr)); // zero the sockaddr_in structure
    recvSockAddr.sin_port=htons(PORT); // specify the port portion of the address
    recvSockAddr.sin_family=AF_INET; // specify the address family as Internet
    recvSockAddr.sin_addr.s_addr= inet_addr(ip); // specify ip address
    // Create socket
    recvSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(recvSocket == INVALID_SOCKET)
    {
        printf("ERROR: socket unsuccessful\r\n");
        WSACleanup();
        system("pause");
        return 0;
    }
    // Connect
    if(connect(recvSocket,(SOCKADDR*)&recvSockAddr,sizeof(SOCKADDR_IN)) == SOCKET_ERROR)
    {
        printf("ERROR: socket could not connect\r\n");
        closesocket(recvSocket);
        WSACleanup();
        return 0;
    }

    char request[200];
    sprintf(request, "GET /var/14 HTTP/1.1\r\nHost:%s\r\n\r\n", host_name);
    myRequest (recvSocket, request, buffer, MAXBUFLEN);

    puts (buffer);

    char word[36];
    char* secret = strstr(buffer, "secret=");
    sscanf (secret + strlen("secret="), "%s", word);

    printf ("secret word: %s\n", word);

    sprintf(request, "GET /var/14?secret=%s HTTP/1.1\r\nHost:%s\r\n\r\n", word, host_name);

    myRequest (recvSocket, request, buffer, MAXBUFLEN);

    char data[200];
    getNString (buffer, data, 6);

    printf ("Sentence: %s\n", data);

    int ans = task (data);
    char result[20];
    sprintf (result, "result=%d", ans);

    printf ("result = %d\n", ans);

    sprintf(request, "POST %s/var/14 HTTP/1.1\r\n"
            "Content-length: %d\r\n\r\n"
            "%s", host_name, strlen(result), result);
    myRequest (recvSocket, request, buffer, MAXBUFLEN);

    printf ("Server answer: \n");
    puts (buffer);

    system("pause");
    return 0;
}
