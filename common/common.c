#include "common.h"

bool send_file(FILE* fp, int socket_fd)
{
    // Buffer that the file will be read into
    char buffer[SIZE] = { 0 };

    // Read the file `fp` `SIZE` bytes at a time into `buffer`
    while (fgets(buffer, SIZE, fp) != NULL) {
        if (send(socket_fd, buffer, sizeof(buffer), 0) < 0) {
            return false;
        }

        // Zero out the buffer after each block has been read
        bzero(buffer, SIZE);
    }

    return true;
}

bool save_file(int socket_fd)
{
    FILE* fp;
    char file_id[SIZE];
    char buffer[SIZE];
    int seconds, minutes, hours, day, month, year;

    // File name will be in the following format: 2022-10-3-11-32-32.txt
    get_time(&seconds, &minutes, &hours, &day, &month, &year);
    snprintf(file_id, SIZE, "%d-%d-%d-%d-%d-%d%s", year, month, day, hours, minutes, seconds, EXTENSION);

    // Validate the file specified
    if ((fp = fopen(file_id, "w")) == NULL) {
        return false;
    }

    // Read into `buffer` + write `buffer` into `fp` `SIZE` bytes at a time
    while (true) {
        if (recv(socket_fd, buffer, SIZE, 0) < 0) {
            return false;
        }

        // Write data into the file
        fprintf(fp, "%s", buffer);
        bzero(buffer, SIZE);
    }

    return true;
}

void get_time(int* seconds, int* minutes, int* hours, int* day, int* month, int* year)
{
    time_t now;
    tm* local_time = localtime(&now);

    *seconds = local_time->tm_sec;
    *minutes = local_time->tm_min;
    *hours = local_time->tm_hour;
    *day = local_time->tm_mday;
    *month = local_time->tm_mon + 1;     // tm_mon represents months from 0 to 11
    *year = local_time->tm_year + 1900;  // tm_year is the number of years since 1900
}

bool validate_file_extension(char* file_name, int file_name_len, char* extension, int extension_len)
{
    /**
     * Start at the end and check each character backwards for a match
     * 
     * If all match, return true
     * If we find one that doesn't, return false
     * 
     */
    for (int i = file_name_len-1; i > file_name_len-extension_len; i--) {
        if (file_name[i] != extension[i]) {
            return false;
        }
    }

    return true;
}