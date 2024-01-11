
#include "socketcan.h"

#include <stdio.h>
int main() {
  socketcan_socket socket;
  int erno;
  erno = socketcan_socket_open(&socket, SOCKETCAN_BUS_CAN0, NULL, 0);
  if (erno) {
    printf("Failed to open socket\n");
  }

  socketcan_frame frame = {};
  frame.can_id = 0x555;
  frame.can_dlc = 5;
  sprintf(frame.data, "Hello");
  erno = socketcan_send_frame(&socket, &frame);
  if (erno) {
    printf("failed to write to socket\n");
  }
  
  printf("receiving...\n");
  erno = socketcan_recv_frame(&socket, &frame);
  if (erno) {
    printf("failed to recv frame\n");
  }

  erno = socketcan_close(&socket);
  if (erno) {
    printf("failed to close socket");
  }

  printf("Hello, World\n");
}
