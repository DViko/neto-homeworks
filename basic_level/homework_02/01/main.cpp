#include <iostream>

enum DataBase : short 
{
    January = 1, February, March, April,
    May, June, July, August,
    September, October, November, December
};

enum ResponseStatus : short
{
    OK = 200, BadRequest = 400, NotFound = 404, Error = 500
};

struct Response
{
    const char* body;
    ResponseStatus status;
};

Response DataBaseQuery(DataBase request);
void SendResponse(Response response);

int main()
{
    short request {0};

    do
    {
        std::cout << "Enter month number: ";
        std::cin >> request;

        if (!std::cin)
        {
            std::cin.clear();
            std::cin.ignore(1000, '\n');

            SendResponse({ "Bad request: Invalid input format!", BadRequest });
            continue;
        }

        if (request == 0)
        {
            SendResponse({ "Goodbye. Terminating connection due to administrator command...", OK });
            break;
        }

        if (request < 1 || request > 12)
        {
            SendResponse({ "Not found: Invalid request!", NotFound });
            continue;
        }

        SendResponse(DataBaseQuery(static_cast<DataBase>(request)));
    } while (true);
}


Response DataBaseQuery(DataBase request)
{
    switch (request)
    {
        case January:   return Response {"January", OK};
        case February:  return Response {"February", OK};
        case March:     return Response {"March", OK};
        case April:     return Response {"April", OK};
        case May:       return Response {"May", OK};
        case June:      return Response {"June", OK};
        case July:      return Response {"July", OK};
        case August:    return Response {"August", OK};
        case September: return Response {"September", OK};
        case October:   return Response {"October", OK};
        case November:  return Response {"November", OK};
        case December:  return Response {"December", OK};
        default:        return Response {"Error: Unknown error occurred!", Error};
    }
}

void SendResponse(Response response)
{
    switch (response.status)
    {
        case OK:
            std::cout << "[" << response.status << "] " << response.body << std::endl;
            break;
        case BadRequest:
            std::cerr << "[" << response.status << "] " << response.body << std::endl;
            break;
        case NotFound:
            std::cerr << "[" << response.status << "] " << response.body << std::endl;
            break;
        case Error:
            std::cerr << "[" << response.status << "] " << response.body << std::endl;
            break;
    }
}