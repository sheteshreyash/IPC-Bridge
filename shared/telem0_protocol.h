#ifndef TELEM0_PROTOCOL_H
#define TELEM0_PROTOCOL_H

/* Conditional Include for Shared Kernel/Userspace ABI */
#ifdef __KERNEL__
    #include <linux/types.h>
#else
    #include <stdint.h>
#endif
#define TELEM0_PACKET_MAGIC 0x54454C4DUL
#define TELEM0_PACKET_SIZE 36U

typedef struct __attribute__((packed))
{
    uint32_t magic;
    uint32_t seq;
    uint32_t ts_us;

    int32_t ax;
    int32_t ay;
    int32_t az;

    int32_t gx;
    int32_t gy;
    int32_t gz;
} telem0_packet_t;

#endif /* TELEM0_PROTOCOL_H */
