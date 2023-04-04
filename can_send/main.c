#include <linux/can.h>
#include <linux/can/raw.h>
#include <net/if.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

int main() {
  int s;
  int nbytes;
  struct sockaddr_can addr;
  struct can_frame frame;
  struct ifreq ifr;

  const char *ifname = "can0";

  if ((s = socket(PF_CAN, SOCK_RAW, CAN_RAW)) == -1) {
    perror("Error while opening socket");
    return -1;
  }

  strcpy(ifr.ifr_name, ifname);
  ioctl(s, SIOCGIFINDEX, &ifr);

  addr.can_family = AF_CAN;
  addr.can_ifindex = ifr.ifr_ifindex;

  printf("%s at index %d\n", ifname, ifr.ifr_ifindex);

  if (bind(s, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
    perror("Error in socket bind");
    return -2;
  }

  frame.can_id = 0x123;
  // As can_dlc is deprecated, use len instead.
  frame.len = 2;
  frame.data[0] = 0x11;
  frame.data[1] = 0x22;

  while (1) {
    nbytes = write(s, &frame, sizeof(struct can_frame));
    printf("Wrote %d bytes\n", nbytes);
    sleep(1);
  }
}
