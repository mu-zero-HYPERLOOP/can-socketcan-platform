#ifndef CAN_SOCKETCAN_PLATFORM_SOCKET_H
#define CAN_SOCKETCAN_PLATFORM_SOCKET_H

#include <inttypes.h>
#include <linux/can.h>
#include <linux/can/raw.h>
#include <net/if.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <unistd.h>

typedef enum {
  SOCKETCAN_BUS_CAN0,
  SOCKETCAN_BUS_CAN1,
} socketcan_bus;

typedef enum : uint32_t {
  SOCKETCAN_FRAME_ERR_BIT = 1u << 29,
  SOCKETCAN_FRAME_RTR_BIT = 1u << 30,
  SOCKETCAN_FRAME_IDE_BIT = 1u << 31,
} socketcan_frame_bits;

typedef struct can_frame socketcan_frame;

typedef struct can_filter socketcan_filter;

typedef struct {
  int linux_socket;
} socketcan_socket;

int socketcan_socket_open(socketcan_socket *socketcan_socket,
                                   socketcan_bus bus, socketcan_filter *filters,
                                   size_t filter_count);

int socketcan_send_frame(socketcan_socket *socketcan_socket,
                                socketcan_frame *frame);

int socketcan_recv_frame(socketcan_socket *socketcan_socket,
                         socketcan_frame *frame);

int socketcan_close(socketcan_socket *socketcan_socket);

#endif
