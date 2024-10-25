const net = require('net');

let clients = []; // Array para almacenar los dos clientes

// Crear el servidor
const server = net.createServer((socket) => {
    console.log('Nuevo cliente conectado');
    
    // Añadir el nuevo cliente al array de clientes
    clients.push(socket);

    // Si tenemos dos clientes, permitir la comunicación entre ellos
    if (clients.length === 2) {
        console.log('Ambos clientes están conectados. Listos para comunicarse.');

        // Configurar comunicación del cliente 1 al cliente 2
        clients[0].on('data', (data) => {
            console.log('Cliente 1 dice:', data.toString());
            clients[1].write(`Mensaje de Cliente 1: ${data.toString()}`);
        });

        // Configurar comunicación del cliente 2 al cliente 1
        clients[1].on('data', (data) => {
            console.log('Cliente 2 dice:', data.toString());
            clients[0].write(`Mensaje de Cliente 2: ${data.toString()}`);
        });

        // Manejar la desconexión de los clientes
        clients[0].on('end', () => {
            console.log('Cliente 1 desconectado');
            clients[1].write('Cliente 1 se ha desconectado');
            clients = [];
        });

        clients[1].on('end', () => {
            console.log('Cliente 2 desconectado');
            clients[0].write('Cliente 2 se ha desconectado');
            clients = [];
        });
    }

    // Manejar la desconexión de un cliente si aún no hay dos conectados
    socket.on('end', () => {
        console.log('Un cliente se ha desconectado');
        clients = clients.filter((client) => client !== socket);
    });
});

// Escuchar en el puerto 8080
server.listen(8080, '0.0.0.0', () => {
    console.log('Servidor escuchando en el puerto 8080');
});
