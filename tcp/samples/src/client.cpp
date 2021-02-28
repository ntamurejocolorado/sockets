#include <stdio.h>
#include<arpa/inet.h>
#include <sys/socket.h>
#include <iostream>
#include <string.h>
#include <string>


int main()
{
    struct sockaddr_in direccionServer;
    direccionServer.sin_family = AF_INET;
    direccionServer.sin_addr.s_addr = inet_addr("127.0.0.1");
    direccionServer.sin_port = htons(8080);

    int cliente = socket(AF_INET,SOCK_STREAM,0);

    if (connect(cliente,(sockaddr*) &direccionServer,sizeof(direccionServer))!= 0)
    {
        std::cerr << "No se puede conectar al servidor" << std::endl;
        return 1;
    }
    std::cout << "Connected to the server!" << std::endl;
   

    char buffer[4096] = {0};
    //Clear the buffer
    
    while(true)
    {
        memset(buffer, 0, 4096);
        int bytesRecibidos = recv(cliente, buffer,4096,0);
        if (bytesRecibidos <= 0)
        {
            std::cerr << "Se ha desconectado" << std::endl;
            return 1;
        }
        //buffer[bytesRecibidos] ='\0';
        //printf("Me llegaron %d bytes con %s", bytesRecibidos, buffer);
        std::cout <<"Received del servidor: "<< std::string(buffer,0,bytesRecibidos) <<std::endl;
        //send(cliente,"Bienvenido a mi cliente.\n",26,0);
        //Contestamos al servidor
        while(true)
        {
            //string myString = "Hello World";

            //send(myString.c_str(), myString.length());

            char mensaje[1000];
            scanf("%s", mensaje);

            send(cliente,mensaje,strlen(mensaje),0);
        }   
        //send(cliente,mensaje,strlen(mensaje),0);
    }
    return 0;
}