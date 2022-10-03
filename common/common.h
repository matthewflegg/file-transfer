#ifndef __COMMON_H__
#define __COMMON_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <time.h>
#include <unistd.h>

// A standard size in bytes for buffers used throughout the program
#define SIZE 1024

/**
 * The port that the server socket is bound to
 * 
 * Port forwarding must be enabled on the router on the server's network to use
 * the program on a client machine outside of it.
 * 
 */
#define PORT 8080

// The IPv4 address that identifies the server
#define HOST "127.0.0.1"

// The file extension used for file transfer
#define EXTENSION ".txt"

// Redefinition of struct sockaddr, removing the `struct` keyword for more concise types
typedef struct sockaddr sockaddr;

// Redefinition of struct sockaddr_in, removing the `struct` keyword for more concise types
typedef struct sockaddr_in sockaddr_in;

// Redefinition of struct tm, removing the `struct` keyword for more concise types
typedef struct tm tm;

/**
 * @brief  Sends `fp` to socket connected to `socket_fd`
 * @param  fp: A pointer to the file to send
 * @param  socket_fd: The socket file descriptor of the sender
 * @retval `true` on success, `false` on failure
 * 
 */
bool send_file(FILE* fp, int socket_fd);

/**
 * @brief  Recieves a file from `socket_fd` and saves it
 * @param  socket_fd: The socket file descriptor of the recipient
 * @retval `true` on success, `false` on failure
 * 
 */
bool save_file(int socket_fd);

/**
 * @brief  Gets the current time in SMHDMY format
 * @note   
 * @param  seconds: Out parameter, the current second past the minute
 * @param  minutes: Out parameter, the current minute past the hour 
 * @param  hours: Out parameter, the current hour of the day
 * @param  day: Out parameter, the current day of the month
 * @param  month: Out parameter, the current month of the year
 * @param  year: Out parameter, the current year
 *
 */
void get_time(int* seconds, int* minutes, int* hours, int* day, int* month, int* year);

/**
 * @brief  Checks if a filename ends with a specified extension
 * @note   
 * @param  file_name:     The name of the file to validate
 * @param  file_name_len: The length of the file name
 * @param  extension:     The file extension to validate
 * @param  extension_len: The length of the file extension
 * @retval 
 */
bool validate_file_extension(char* file_name, int file_name_len, char* extension, int extension_len);

#ifdef __cplusplus
}
#endif

#endif  // __COMMON_H__