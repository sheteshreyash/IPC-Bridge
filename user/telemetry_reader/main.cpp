#include <fcntl.h>
#include <unistd.h>
#include <poll.h>
#include <cstdio>
#include <cerrno>
#include <cstring>
#include <iostream>

int main()
{
    const char *dev = "/dev/telem0";

    int fd = open(dev, O_RDONLY | O_NONBLOCK);
    if (fd < 0)
    {
        std::perror("open");
        return 1;
    }

    std::cout << "Reading from " << dev << std::endl;

    struct pollfd pfd;
    pfd.fd = fd;
    pfd.events = POLLIN;
    pfd.revents = 0;

    char buf[256];

    while (true)
    {
        int pret = poll(&pfd, 1, 1000);
        if (pret < 0)
        {
            std::perror("poll");
            break;
        }

        if (pret == 0)
        {
            continue;
        }

        if (pfd.revents & POLLIN)
        {
            ssize_t n = read(fd, buf, sizeof(buf) - 1);
            if (n < 0)
            {
                if (errno == EAGAIN || errno == EWOULDBLOCK)
                {
                    continue;
                }
                std::perror("read");
                break;
            }

            if (n == 0)
            {
                continue;
            }

            buf[n] = '\0';
            std::cout << buf;
            std::cout.flush();
        }
    }

    close(fd);
    return 0;
}
