#include "socketcan.h"

int socketcan_socket_open(socketcan_socket *socketcan_socket,
                                   socketcan_bus bus, socketcan_filter *filters,
                                   size_t filter_count) {
  int s = socket(PF_CAN, SOCK_RAW, CAN_RAW);
  if (s < 0) {
    return 1;
  }
  struct ifreq ifr;
  if (bus == SOCKETCAN_BUS_CAN0) {
    strcpy(ifr.ifr_name, "can0");
  } else if (bus == SOCKETCAN_BUS_CAN1) {
    strcpy(ifr.ifr_name, "can1");
  } else {
    return 1;
  }
  ioctl(s, SIOCGIFINDEX, &ifr);

  struct sockaddr_can addr;
  memset(&addr, 0, sizeof(addr));
  addr.can_family = AF_CAN;
  addr.can_ifindex = ifr.ifr_ifindex;
  if (bind(s, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
    return 1;
  }
  socketcan_socket->linux_socket = s;

  if (filters != NULL || filter_count == 0) {
    int erno =
        setsockopt(socketcan_socket->linux_socket, SOL_CAN_RAW, CAN_RAW_FILTER,
                   filters, sizeof(socketcan_filter) * filter_count);
    if (erno) {
      return 1;
    }
  }

  return 0;
}


int socketcan_send_frame(socketcan_socket *socketcan_socket,
                                socketcan_frame *frame) {
  if (write(socketcan_socket->linux_socket, frame, sizeof(socketcan_frame)) !=
      sizeof(socketcan_frame)) {
    return 1;
  }
  return 0;
}
int socketcan_recv_frame(socketcan_socket *socketcan_socket,
                         socketcan_frame *frame) {
  int nbytes =
      read(socketcan_socket->linux_socket, &frame, sizeof(socketcan_frame));
  if (nbytes < 0) {
    return 1;
  }
  return 0;
}

int socketcan_close(socketcan_socket *socketcan_socket) {
  if (close(socketcan_socket->linux_socket) < 0) {
    return 1;
  }
  return 0;
}

