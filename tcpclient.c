#include "common/common.h"

int main(int argc, char** argv)
{
    // Validate command line args
    if (argc != 2) {
        printf("[-] Incorrect arguments. Should be `tcpclient <file>`.");
        return -1;
    }

    int client_fd;
    sockaddr_in server_addr;
    FILE* fp;
    char* file_name = argv[1];

    if (!validate_file_extension(file_name, strlen(file_name), EXTENSION, strlen(EXTENSION))) {
        printf("[-] Invalid file extension. Must be of type %s.\n", EXTENSION);
        return -2;
    }

    // Validate the file specified
    if ((fp = fopen(file_name, "r")) == NULL) {
        perror("[-] Error reading specified file");
        return -3;
    }

    // Create client socket and validate
    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("[-] Error creating socket");
        return -4;
    }

    printf("[+] Created socket with FD %d.\n", client_fd);

    // Attempt connection to server and validate
    if (connect(client_fd, (sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("[-] Error connecting to client");
        return -5;
    }

    printf("[+] Connected to server with address %d.\n", HOST);

    // Send the file to server and validate
    if (!send_file(fp, client_fd)) {
        perror("[-] Could not send file to server");
        return -6;
    }

    printf("[+] Successfully sent file to server.\n");
    close(client_fd);
    printf("[+] Disconnected from server.\n");
    return 0;
}