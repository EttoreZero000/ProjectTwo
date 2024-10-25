#include <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};
    std::string mensaje;

    // Crear el socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::cerr << "Error al crear el socket" << std::endl;
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8080);

    // Convertir la dirección IP
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        std::cerr << "Dirección inválida o no soportada" << std::endl;
        return -1;
    }

    // Conectar al servidor
    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cerr << "Conexión fallida" << std::endl;
        return -1;
    }

    std::cout << "Conectado al servidor Node.js" << std::endl;

    // Ciclo para enviar y recibir mensajes
    while (true) {
        // Leer mensaje del usuario
        std::cout << "Escribe un mensaje para el otro cliente: ";
        std::getline(std::cin, mensaje);

        // Enviar mensaje al servidor
        send(sock, mensaje.c_str(), mensaje.length(), 0);

        // Recibir respuesta del servidor (mensaje del otro cliente)
        int valread = read(sock, buffer, 1024);
        if (valread > 0) {
            buffer[valread] = '\0';  // Agregar terminador de cadena
            std::cout << "Mensaje del otro cliente: " << buffer << std::endl;
        }
    }

    // Cerrar el socket
    close(sock);
    return 0;
}
