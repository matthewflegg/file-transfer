#include "common/common.h"

int main(void)
{
    int server_fd, client_fd;
    sockaddr_in server_addr, client_addr;
    socklen_t addr_size;

    // Create client socket and validate
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("[-] Error creating socket");
        return -1;
    }

    printf("[+] Created socket with FD %d.\n", server_fd);
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    inet_aton(HOST, &server_addr.sin_addr);

    // Bind socket to address and validate
    if (bind(server_fd, (sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("[-] Error binding socket");
        return -2;
    }
    
    printf("[+] Bound socket to address %s port %d.\n", HOST, PORT);

    // Attempt to listen and validate
    if (listen(server_fd, 10) < 0) {
        perror("[-] Error instructing socket to listen");
        return -3;
    }

    printf("[+] Listening for connections...\n");
    addr_size = sizeof(client_addr);

    while (true) {

        // Attempt connection to client and validate
        if ((client_fd = accept(server_fd, (sockaddr*)&client_addr, &addr_size)) < 0) {
            perror("[-] Error accepting connection");
            return -4;
        } 

        printf("[+] Connected to client with socket FD %d.\n", client_fd);

        if (!save_file(client_fd)) {
            printf("[-] Failed to save the file.\n");
            return -5;
        }

        printf("[+] File saved successfully.\n");
        close(client_fd);
        printf("[+] Connection closed with client.\n");
    }

    return 0;    
}