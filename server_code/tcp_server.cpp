#include <iostream>
#include <thread>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

using namespace std;

// This function handles communication with a single client
void handle_client(int client_fd, sockaddr_in c_addr) {
    char buffer[1024];

    // Read message from client
    ssize_t bytes_read = read(client_fd, buffer, 1024);

    if (bytes_read > 0) {
        // Output the received message and client's IP address
        cout << "Received from client " << inet_ntoa(c_addr.sin_addr) << ": " << buffer << endl;

        // Send a response to the client
        string reply = "Done!\n";
        write(client_fd, reply.c_str(), reply.size());
    } else if (bytes_read == 0) {
        // Connection closed by client
        cout << "Client disconnected" << endl;
    } else {
        // Error occurred during read
        cout << "Read error" << endl;
    }

    // Close client socket
    close(client_fd);
}

int main() {
    const int PORT = 8080;

    // Create a TCP socket (IPv4)
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd < 0) {
        cout << "Socket creation failed" << endl;
        return -1;
    }

    // Set up server address structure
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;          // IPv4
    addr.sin_addr.s_addr = INADDR_ANY;  // Listen on all interfaces
    addr.sin_port = htons(PORT);        // Convert port to network byte order

    // Bind socket to the IP and port
    if (bind(socket_fd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        cout << "Bind failed" << endl;
        return -1;
    }

    // Start listening for incoming connections
    int backlog = 5; // Max queue of 5 pending connections
    if (listen(socket_fd, backlog) < 0) {
        cout << "Listen failed" << endl;
        return -1;
    }

    cout << "Server listening on port " << PORT << endl;

    // Main loop to accept and handle incoming client connections
    while (true) {
        struct sockaddr_in c_addr;
        socklen_t c_len = sizeof(c_addr);

        // Accept a new client connection
        int client_fd = accept(socket_fd, (struct sockaddr*)&c_addr, &c_len);
        if (client_fd < 0) {
            cout << "Accept failed" << endl;
            return -1;
        }

        // Show connected client's IP address
        cout << "Client connected: " << inet_ntoa(c_addr.sin_addr) << endl;

        // Optional: greet client immediately after connection
        string reply = "Hello\n";
        write(client_fd, reply.c_str(), reply.size());

        // Start a detached thread to handle this client
        thread(handle_client, client_fd, c_addr).detach();
    }

    // Close the server socket (never reached in this loop)
    close(socket_fd);
    return 0;
}

