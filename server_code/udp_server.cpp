#include <iostream>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

using namespace std;

int main() {
    const int PORT = 8080;

    // Create a UDP socket (AF_INET for IPv4, SOCK_DGRAM for UDP)
    int socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (socket_fd < 0) {
        cout << "Socket creation failed" << endl;
        return -1;
    }

    // Server address structure
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;         // IPv4
    server_addr.sin_addr.s_addr = INADDR_ANY; // Listen on all interfaces
    server_addr.sin_port = htons(PORT);       // Port number

    // Bind the socket to the IP and port
    if (bind(socket_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        cout << "Bind failed" << endl;
        return -1;
    }

    cout << "UDP server listening on port " << PORT << endl;

    while (true) {
        char buffer[1024];
        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);

        // Receive message from any client
        ssize_t bytes_received = recvfrom(socket_fd, buffer, 1024, 0, (struct sockaddr*)&client_addr, &client_len);
        if (bytes_received < 0) {
            cout << "recvfrom failed" << endl;
            continue;
        }

        // Print client IP and message
        cout << "Received from " << inet_ntoa(client_addr.sin_addr) << ":" << client_addr.sin_port << " data: " << buffer << endl;

        // Send reply to the client
        string reply = "Done!\n";
        sendto(socket_fd, reply.c_str(), reply.size(), 0,(struct sockaddr*)&client_addr, client_len);
    }

    close(socket_fd);
    return 0;
}

