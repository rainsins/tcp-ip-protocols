#pragma once
//数据包结构定义
//定义包缓冲区
#include <stdint.h>

#define XNET_CFG_PACKET_MAX_SIZE 1516           //缓冲区最大尺寸
#define min(a,b)  ((a)>(b)? (b) : (a))          //获取两个数的最小值


class _xnet_packet_t{
protected:
    uint16_t _size;                              //数据包尺寸
    uint8_t* _data;                              //数据起始地址
    uint8_t payload[XNET_CFG_PACKET_MAX_SIZE];  //缓冲区
    static _xnet_packet_t tx_packet,rx_packet;  //发送包和接收包
public:
    uint16_t r_size(){
        return _size;
    }
    uint8_t* r_data(){
        return _data;
    }
    void set_size(uint16_t v){
        _size = v;
    }
    _xnet_packet_t* xnet_alloc_for_send(uint16_t data_size){
        tx_packet._data = tx_packet.payload + XNET_CFG_PACKET_MAX_SIZE - data_size;
        tx_packet._size = data_size;
        return &tx_packet;
    };
    _xnet_packet_t* xnet_alloc_for_read(uint16_t data_size){
        rx_packet._data = rx_packet.payload;
        rx_packet._size = data_size;
        return &rx_packet;
    };
    static void add_header(_xnet_packet_t* packet, uint16_t header_size);
    static void remove_header(_xnet_packet_t* packet, uint16_t header_size);
    static void truncate_header(_xnet_packet_t* packet, uint16_t _size);
};

void _xnet_packet_t::add_header(_xnet_packet_t* packet, uint16_t header_size){
    packet->_data -= header_size;
    packet->_size += header_size;
}

void _xnet_packet_t::remove_header(_xnet_packet_t* packet, uint16_t header_size){
    packet->_data += header_size;
    packet->_size -= header_size;
}

void _xnet_packet_t::truncate_header(_xnet_packet_t* packet, uint16_t _size){
    packet->_size = min(packet->_size, _size);
} 


void _xnet_init(void){

};
void _xnet_poll(void){
    
};

