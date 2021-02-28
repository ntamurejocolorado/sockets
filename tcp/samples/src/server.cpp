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
    direccionServer.sin_addr.s_addr = INADDR_ANY;
    direccionServer.sin_port = htons(8080);

    int servidor = socket(AF_INET,SOCK_STREAM,0);

    //------
    // Estas dos lineas lo que hacen es que el sistema operativo pueda utlizar las direcciones de seguido
    // es decir, que no falle en el bind() cuando cerramos una conexión de forma abrupta mientras entamos provando
    // y a continuación arrancamos, podria dar error, ya que se queda inutilizado durante 2 min
    // con estas dos lineas lo solucionamos.
    int activado = 1;
    setsockopt(servidor,SOL_SOCKET,SO_REUSEADDR,&activado,sizeof(activado));
    //-----------------------

    if (bind(servidor,(sockaddr*) &direccionServer, sizeof(direccionServer))!= 0)
    {
        std::cerr << "Fallo en el bind" << std::endl;
        return -1;
    }
    std::cout << "Estoy escuchando" << std::endl;
    listen(servidor,SOMAXCONN);

    //-----------------------
    // Aceptamos clientes
    struct  sockaddr_in direccionClient;
    unsigned int sizeDireccionClient;
    int client = accept(servidor, (sockaddr*) &direccionClient, &sizeDireccionClient);
    send(client,"Bienvenido a mi servidor.\n",26,0);
    std::cout << "Recibi una conexion en " << client <<  std::endl;

    //Contestamos al cliente 
    
    //send(client, "Hola cliente\n", 13,0);

    //---------------------------------------------------
    // Recibimos datos.

    char buffer[4096] = {0};
    //Clear the buffer
    
    while(true)
    {
        
        int bytesRecibidos = recv(client, buffer,4096,0);
        if (bytesRecibidos <= 0)
        {
            std::cerr << "Se ha desconectado" << std::endl;
            return 1;
        }
        //buffer[bytesRecibidos] ='\0';
        //printf("Me llegaron %d bytes con %s", bytesRecibidos, buffer);
        std::cout <<"Received del cliente: "<< std::string(buffer,0,bytesRecibidos) <<std::endl;

        //Contestamos al cliente
        //send(client, "Hola cliente\n", 13,0);
        send(client,buffer,bytesRecibidos+1,0); //para enviar un echo al cliente
        memset(buffer, 0, 4096);
    }
    
    return 0;
}