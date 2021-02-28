#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>


int main()
{
    // Create a socket
    int listening = socket(AF_INET,SOCK_STREAM,0);
    if (listening == -1)
    {
        std::cerr << "Can't create a socket!" << std::endl;
        return -1;
    }
    // Bind the socket to IP and Port
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(54000);
    inet_pton(AF_INET, "0.0.0.0",&hint.sin_addr);

   if ( bind(listening, (sockaddr*) &hint, sizeof(hint)) == -1)
    {
        std::cerr <<"Can't bind to IP/port" << std::endl;
        return -2;
    }
    // Mark the socket for listening in 
    if (listen(listening, SOMAXCONN) == -1)
    {
        std::cerr << "Cant't listen" << std::endl;
        return -3;
    }
    std::cerr << "Listening 1" << std::endl;
    // Accept a call
    sockaddr_in client;
    socklen_t clientSize = sizeof(client);
    char host[NI_MAXHOST];
    char svc[NI_MAXSERV];
    std::cerr << "Listening 2" << std::endl;
    
    int clientSocket = accept(listening,(sockaddr*)&client, &clientSize);
    send(clientSocket,"Bienvenido a mi servidor.\n",26,0);
    if (clientSocket == -1)
    {
        std::cerr<< "Problem with the client connecting!" << std::endl;
        return -4;
    }
    std::cerr << "Listening 3" << std::endl;
    // Close the listening socket
    close(listening);

    memset(host, 0, NI_MAXHOST);
    memset(svc, 0, NI_MAXSERV);

    int result = getnameinfo((sockaddr*)&client,
                                sizeof(client),
                                host,
                                NI_MAXHOST,
                                svc,
                                NI_MAXSERV,
                                0);

    if(result)
    {
        std::cout << host << " connected on " << svc << std::endl; 
    }
    else
    {
        inet_ntop(AF_INET, &client.sin_addr,host,NI_MAXHOST);
        std::cout << host << "connected on " << ntohs(client.sin_port) << std::endl;
    }
    
    // While receiving display message, echo message
    char buf[4096];
    while (true)
    {
        //Clear the buffer
        memset(buf, 0, 4096);
        // Wait for a message
        int bytesRecv = recv(clientSocket, buf, 4096, 0);
        if (bytesRecv == -1)
        {
            std::cout << "There was a connection issue " << std::endl;
            break;
        }
        if (bytesRecv == 0)
        {
            std::cout << "The client disconnected" <<std::endl;
            break;
        }
        // Display message
        std::cout <<"Received: "<< std::string(buf,0,bytesRecv) <<std::endl;

        // Resend message
        send(clientSocket,buf, bytesRecv + 1, 0); 
        
        
    }
    // Close socket
    close(clientSocket);
    std::cout << "Hello World Sockets!" << std::endl;
    return 0;
}