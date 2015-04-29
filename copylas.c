#include <errno.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void usage(void) {
    fprintf(stderr, "Usage:\n"
            "\tcopylas src dest\n"
            "\n"
            "Copies an ASPRS LAS file from src to dest.\n");
}

int main(int argc, char **argv) {
    if (argc < 3) {
        usage();
        exit(EXIT_FAILURE);
    }
    char *dest = argv[2];
    char *src = argv[1];

    int srcfd = open(src, O_RDONLY);
    if (!srcfd) { perror(src); return EXIT_FAILURE; }
    int destfd = open(dest, O_CREAT | O_WRONLY);
    if (!destfd) { perror(dest); return EXIT_FAILURE; }

    char buffer[BUFSIZ];

    ssize_t nread;
    ssize_t written;
    while (true) {
        errno = 0;
        nread = read(srcfd, buffer, BUFSIZ);
        if (nread < 0) switch (errno) {
                case EAGAIN: case EINTR: default:
                    continue;
                case EBADF: case EFAULT: case EINVAL: case EIO: case EISDIR:
                    perror("copylas");
                    exit(EXIT_FAILURE);
        } else if (nread == 0) break; // eof
        errno = 0;
        written = write(destfd, buffer, nread);
        if (written <= 0) {
            perror(dest); // Let's just be lazy, OK?
            exit(EXIT_FAILURE);
        }
    }

    errno = 0;
    close(srcfd);
    close(destfd);
    return EXIT_SUCCESS;
}
