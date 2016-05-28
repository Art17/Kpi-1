#include "web.h"

struct web_s
{
    socket_t* serverSocket;

    data_manager_t directors;
};

const char* answerFormat =
        "HTTP/1.1 %d %s\r\n"
        "Content-Type: text\r\n"
        "Content-Length: %d\r\n\r\n"
        "%s";

void serverReply (web_t self, socket_t*, http_request_t);
void serverHomepage (socket_t*);
void serverAboutAuthor (socket_t*);
void serverDirectorsMenu (web_t, socket_t*);
void serverCreateNewDirector (socket_t*);
void serverApiDirectors (web_t self, socket_t*, int id);
void serverMessagePage (socket_t*, int, const char*, const char*);
void serverDirectorInfo (socket_t*, director_t, int);
void serverOptions (socket_t*);
void serverCreateNewItem (web_t, socket_t*, http_request_t);

int deleteItem (web_t, int);

void serverCreateNewItem (web_t self, socket_t* clientSocket, http_request_t httpRequest)
{
    director_t director = director_new ();

    char name [28];
    char surname [28];
    char birthdate [28];
    char budget[28];
    char years[28];

    int argsNum = http_request_getArgsNum(httpRequest);

    for (int i = 0; i < argsNum; i++)
    {
        char key[MAX_KEY];
        http_request_getKey(httpRequest, i, key);
        char value [MAX_VALUE];
        http_request_getValue(httpRequest, key, value);

        if ( strcmp (key, "name") == 0 )
            strcpy (name, value);
        else if ( strcmp (key, "surname") == 0 )
            strcpy (surname, value);
        else if ( strcmp (key, "birthdate") == 0 )
            strcpy (birthdate, value);
        else if ( strcmp (key, "budget") == 0 )
            strcpy (budget, value);
        else if ( strcmp (key, "years") == 0 )
            strcpy (years, value);
    }

    if ( isAlpha (name) && isAlpha(surname) && isDate(birthdate) && isNonNegatReal(budget) && isNonNegatInteger(years)
        && strlen (name) != 0 && strlen (surname) != 0 && strlen (birthdate) != 0 && strlen (budget) != 0 && strlen (years) != 0 )
    {
        director_setValue(director, "name", name);
        director_setValue(director, "surname", surname);
        director_setValue(director, "birthdate", birthdate);
        double d = strtod (budget, NULL);
        int y = atoi (years);
        director_setValue(director, "budget", &d);
        director_setValue(director, "years", &y);

        data_manager_add(self->directors, director);

        serverMessagePage (clientSocket, 200, "OK", "Director added successfully");
    }
    else
        serverMessagePage (clientSocket, 400, "INVALID DATA", "Invalid data passed");
}

void serverReply (web_t self, socket_t* clientSocket, http_request_t httpRequest)
{
    char method[MAX_METHOD];
    char uri [MAX_URI];

    http_request_getMethod(httpRequest, method);
    http_request_getUri (httpRequest, uri);

    if ( strcmp (method, "GET") == 0 )
    {
        const char* directorInfoUri = "/directors/";
        const char* apiDirectorsUri = "/api/directors/";

        if ( strcmp ( uri, "/" ) == 0 )
            serverHomepage (clientSocket);
        else if ( strcmp ( uri, "/about/author" ) == 0 )
            serverAboutAuthor (clientSocket);
        else if ( strcmp ( uri, "/directors" ) == 0 )
            serverDirectorsMenu (self, clientSocket);
        else if ( strcmp ( uri, "/new-director" ) == 0 )
            serverCreateNewDirector (clientSocket);
        else if ( strncmp ( uri, directorInfoUri, strlen (directorInfoUri) ) == 0 )
        {
            int id;
            sscanf (uri + strlen (directorInfoUri), "%d", &id);

            int q = data_manager_getSize(self->directors);

            if (id < q)
            {
                char infoBuffer [256];
                director_t dir = data_manager_get(self->directors, id);
                director_getInfo(dir, infoBuffer);
                serverDirectorInfo (clientSocket, dir, id);
            }
            else
                serverMessagePage (clientSocket, 404, "NOT FOUND", "Invalid id");
        }
        else if ( strcmp ( uri, "/api/directors" ) == 0 )
        {
            serverApiDirectors (self, clientSocket, -1);
        }
        else if ( strncmp ( uri, apiDirectorsUri, strlen (apiDirectorsUri) ) == 0 )
        {
            int id = 0;
            sscanf (uri + strlen (apiDirectorsUri), "%d", &id);
            int q = data_manager_getSize(self->directors);
            if (id < q)
                serverApiDirectors (self, clientSocket, id);
            else
                serverMessagePage (clientSocket, 404, "NOT FOUND", "Invalid id");
        }
        else
            serverMessagePage (clientSocket, 404, "NOT FOUND", "Page doesnt exist, sorry:(");
    }
    else if ( strcmp (method, "POST") == 0)
    {
        if ( strcmp ( uri, "/directors" ) == 0 || strcmp ( uri, "/api/directors" ) == 0)
        {
            serverCreateNewItem (self, clientSocket, httpRequest);
        }
        else
            serverMessagePage (clientSocket, 404, "NOT FOUND", "Page doesnt exist, sorry:(");
    }
    else if ( strcmp (method, "OPTIONS") == 0 )
    {
        serverOptions (clientSocket);
    }
    else if ( strcmp (method, "DELETE") == 0 )
    {
        const char* directorUri = "/directors/";
        const char* directorApiUri = "/api/directors/";
        if ( strncmp (uri, directorUri, strlen (directorUri)) == 0 )
        {
            int id;
            sscanf (uri + strlen (directorUri), "%d", &id);
            int res = deleteItem(self, id);
            if (!res)
                serverMessagePage(clientSocket, 200, "OK", "Director deleted successfully");
            else
                serverMessagePage(clientSocket, 400, "INVALID ID", "Wrong id");

        }
        else if ( strncmp (uri, directorApiUri, strlen (directorApiUri)) == 0 )
        {
            int id;
            sscanf (uri + strlen (directorApiUri), "%d", &id);
            int res = deleteItem(self, id);
            if (!res)
                serverMessagePage(clientSocket, 200, "OK", "Director deleted successfully");
            else
                serverMessagePage(clientSocket, 400, "INVALID ID", "Wrong id");
        }
        else
            serverMessagePage(clientSocket, 502, "Bad", "Bad Gateway");
    }
}

int deleteItem(web_t self, int id)
{
    int q = data_manager_getSize(self->directors);
    if (id < q)
    {
        data_manager_delete (self->directors, id);

        return 0;
    }
    return 1;
}

void serverApiDirectors (web_t self, socket_t* clientSocket, int id)
{
    char pageBuffer [1024];
    data_manager_getAsString (self->directors, pageBuffer, id);

    char szAnswerBuffer [1024];

    sprintf (szAnswerBuffer, answerFormat, 200, "OK", strlen (pageBuffer), pageBuffer);

    socket_write (clientSocket, szAnswerBuffer, strlen (szAnswerBuffer));
    socket_close(clientSocket);
}

void serverOptions (socket_t* clientSocket)
{
    char strbuf [256];
    sprintf(strbuf,
            "HTTP/1.1 200 OK\n"
            "Access-Control-Allow-Origin: *\n"
            "Access-Control-Allow-Methods: DELETE\n"
            "\n");
    socket_write (clientSocket, strbuf, strlen (strbuf));
    socket_close(clientSocket);
}

void serverDirectorInfo (socket_t* clientSocket, director_t director, int index)
{
    const char* pageFrame =
    "<body>"
    "<font size=\"5\">%s</font><br><br>"
    "<font size=\"5\"><a href=\"#\" onclick=\"doDelete()\">Delete director</a></font>"
    "<script>"
        "function doDelete() {"
            "var xhttp = new XMLHttpRequest();"
            "xhttp.open(\"DELETE\", \"http://localhost:5000/directors/%d\", true);"
            "xhttp.send();"
        "}"
    "</script>"
    "</body>";


    char infoBuffer [256];
    director_getInfo(director, infoBuffer);

    char pageBuffer [1024];
    sprintf (pageBuffer, pageFrame, infoBuffer, index);

    char szAnswerBuffer [1024];

    sprintf (szAnswerBuffer, answerFormat, 200, "OK", strlen (pageBuffer), pageBuffer);

    socket_write (clientSocket, szAnswerBuffer, strlen (szAnswerBuffer));
    socket_close(clientSocket);
}

void serverHomepage (socket_t* clientSocket)
{
    const char* message = "<h2>Welcome to directors club!!!</h2>"
                          "<font size=\"5\"><a href=\"/directors\">1. Go to directors</a></font>"
                          "<br>"
                          "<br>"
                          "<font size=\"5\"><a href=\"about/author\">2. About author</a></a>";

    char szAnswerBuffer [1024];

    sprintf (szAnswerBuffer, answerFormat, 200, "OK", strlen (message), message);

    socket_write (clientSocket, szAnswerBuffer, strlen (szAnswerBuffer));
    socket_close(clientSocket);
}

void serverAboutAuthor (socket_t* clientSocket)
{
    const char* message = "<font size=\"5\">This server was created by Saprykin Artem on c</font>";

    char szAnswerBuffer [1024];

    sprintf (szAnswerBuffer, answerFormat, 200, "OK", strlen (message), message);

    socket_write (clientSocket, szAnswerBuffer, strlen (szAnswerBuffer));
    socket_close(clientSocket);

}
void serverDirectorsMenu (web_t self, socket_t* clientSocket)
{
    char menuBuffer [10000];

    strcpy (menuBuffer,
            "<font size=\"7\">Directors main menu</font><br>"
            "<br>"
            "<font size=\"5\">"
            );
    char name[28];
    char surname[32];
    int size = data_manager_getSize(self->directors);

    for (int i = 0; i < size; i++)
    {
        director_t dir = data_manager_get (self->directors, i);
        director_getValue(dir, "name", name);
        director_getValue(dir, "surname", surname);

        char directorRef [512];
        sprintf (directorRef,  "<a href=\"directors/%d\">%d. %s %s</a><br>", i, i+1, name, surname);
        strcat (menuBuffer, directorRef);
    }

    strcat (menuBuffer, "</font>");
    strcat (menuBuffer,
                        "<br>"
                        "<br>"
                        "<font size=\"4\"><a href=\"new-director\">create new director</a></font>");

    char szAnswerBuffer [10000];

    sprintf (szAnswerBuffer, answerFormat, 200, "OK", strlen (menuBuffer), menuBuffer);

    socket_write (clientSocket, szAnswerBuffer, strlen (szAnswerBuffer));
    socket_close(clientSocket);
}

void serverCreateNewDirector (socket_t* clientSocket)
{
    const char* message = "<form action=\"/directors\" method=\"POST\">"
                          "<fieldset>"
                          "<legend>Director information:</legend>"
                          "Name:<br>"
                          "<input type=\"text\" name=\"name\" value=\"\"><br>"
                          "Surname:<br>"
                          "<input type=\"text\" name=\"surname\" value=\"\"><br>"
                          "Birthdate:<br>"
                          "<input type=\"text\" name=\"birthdate\" value=\"\"><br>"
                          "Budget:<br>"
                          "<input type=\"text\" name=\"budget\" value=\"\"><br>"
                          "Years:<br>"
                          "<input type=\"text\" name=\"years\" value=\"\"><br><br>"

                          "<input type=\"submit\" value=\"Submit\">"
                          "</fieldset>"
                          "</form>";

    char szAnswerBuffer [1024];

    sprintf (szAnswerBuffer, answerFormat, 200, "OK", strlen (message), message);

    socket_write (clientSocket, szAnswerBuffer, strlen (szAnswerBuffer));
    socket_close(clientSocket);
}

void serverMessagePage (socket_t* clientSocket, int code, const char* reason, const char* text)
{
    const char* temp = "<font size=\"5\">%s</font>";
    char message [2056];
    sprintf (message, temp, text);

    char szAnswerBuffer [1024];

    sprintf (szAnswerBuffer, answerFormat, code, reason, strlen (message), message);

    socket_write (clientSocket, szAnswerBuffer, strlen (szAnswerBuffer));
    socket_close(clientSocket);
}


web_t web_new ()
{
    web_t self = malloc ( sizeof (struct web_s) );
    memset (self, 0, sizeof (struct web_s));

    self->directors = data_manager_new ();
    data_manager_load (self->directors);

    return self;
}

void web_createServer (web_t self, int port)
{
    self->serverSocket = socket_new();
    socket_bind(self->serverSocket, port);
}

void web_listen (web_t self)
{
    socket_listen (self->serverSocket);

    char szRequest [10000];
    const char* msg = "Hello world";
    while (1)
    {
        socket_t* clientSocket = socket_accept(self->serverSocket);
        socket_read(clientSocket, szRequest, sizeof (szRequest));

        http_request_t httpRequest = http_request_new ();
        http_request_parse (httpRequest, szRequest);

        serverReply (self, clientSocket, httpRequest);

        http_request_free (httpRequest);
    }
}

void web_saveData (web_t self)
{
    data_manager_save(self->directors);
}

void web_free (web_t self)
{
    data_manager_free (self->directors);

    socket_close(self->serverSocket);
    free (self);
}
