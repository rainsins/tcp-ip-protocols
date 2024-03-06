#pragma once
#include <iostream>
#include "../lib/xnet/pcap_device.h"
#include "../head/xnet_tiny.hpp"

#define XNET_MAC_ADDR_SIZE       8

typedef enum _xnet_err_t{
    XNET_ERR_OK = 0,
    XNET_ERR_IO = -1,
}xnet_err_t;

//以太网帧头部定义
#pragma pack(1)
class _xether_hdr_t{
    uint8_t dest[XNET_MAC_ADDR_SIZE];   //目的MAC地址
    uint8_t src[XNET_MAC_ADDR_SIZE];    //源MAC地址
    uint16_t protocol;                  //上一层的协议
};
#pragma pack()

xnet_err_t xnet_driver_open(uint8_t* mac_addr);
xnet_err_t xnet_driver_send(_xnet_packet_t * packet);
xnet_err_t xnet_driver_read(_xnet_packet_t** packet);

static pcap_t* pcap;
const char* ip_str="192.168.74.1";
const uint8_t my_mac_addr[]={0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88};

xnet_err_t xnet_driver_open(uint8_t* mac_addr){
    memcpy(mac_addr,my_mac_addr,sizeof(my_mac_addr));
    pcap = pcap_device_open(ip_str,my_mac_addr, 1);
    if(pcap == (pcap_t*)0){
        exit(-1);
    }
    return XNET_ERR_OK;
}

xnet_err_t xnet_driver_send(_xnet_packet_t * packet){
    return (xnet_err_t)pcap_device_send(pcap,packet->r_data(),packet->r_size());
}

xnet_err_t xnet_driver_read(_xnet_packet_t** packet){
    uint16_t size;
    _xnet_packet_t* tmp = *packet;
    _xnet_packet_t* r_packet = tmp->xnet_alloc_for_read(XNET_CFG_PACKET_MAX_SIZE);
    size = pcap_device_read(pcap,r_packet->r_data(),XNET_CFG_PACKET_MAX_SIZE);
    if(size){
        r_packet->set_size(size);
        *packet = r_packet;
        return XNET_ERR_OK;
    }
    return XNET_ERR_IO;
}