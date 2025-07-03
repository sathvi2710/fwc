#include <stdio.h>
#include <stdint.h>
struct IPv6Header {
    int version : 4;
    int traffic_class : 8;
    int flow_label : 20;
    int payload_length:16;
    int next_header:8;
    int hop_limit:8;

    // Source and Destination Addresses (128 bits each)
   uint8_t source_address[16];
    uint8_t destination_address[16];
};
int main()
{
        printf("size of struct Ipv6 : %zu bytes\n",sizeof(struct IPv6Header));
        }