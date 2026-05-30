#include <fcntl.h>
#include <unistd.h>
#include <poll.h>
#include <cstdio>
#include <cerrno>
#include <cstring>
#include <iostream>

#include "../../shared/telem0_protocol.h"

static void print_packet(const telem0_packet_t &pkt)
{
    std::printf(
        "MAGIC=%08X,SEQ=%u,TS_US=%u,AX=%d,AY=%d,AZ=%d,GX=%d,GY=%d,GZ=%d\n",
        pkt.magic,
        pkt.seq,
        pkt.ts_us,
        pkt.ax,
        pkt.ay,
        pkt.az,
        pkt.gx,
        pkt.gy,
        pkt.gz);
}

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

    while (true)
    {
        int pret = poll(&pfd, 1, 1000);
        if (pret < 0)
        {
            std::perror("poll");
            break;
        }

        if (pret == 0)
            continue;

        if (pfd.revents & POLLIN)
        {
            telem0_packet_t pkt;
            ssize_t n = read(fd, &pkt, sizeof(pkt));

            if (n < 0)
            {
                if (errno == EAGAIN || errno == EWOULDBLOCK)
                    continue;

                std::perror("read");
                break;
            }

            if (n == (ssize_t)sizeof(pkt) && pkt.magic == TELEM0_PACKET_MAGIC)
            {
                print_packet(pkt);
            }
            else if (n > 0)
            {
                char buf[256];
                size_t copy_n = (n < (ssize_t)(sizeof(buf) - 1)) ? (size_t)n : sizeof(buf) - 1;
                memcpy(buf, &pkt, copy_n);
                buf[copy_n] = '\0';
                std::cout << buf;
                std::cout.flush();
            }
        }
    }

    close(fd);
    return 0;
}
