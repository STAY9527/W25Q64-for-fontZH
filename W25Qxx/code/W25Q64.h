
#ifndef __W25Q64__H__
#define __W25Q64__H__

#include "main.h"
#include "spi.h"
#include "stdio.h"
#include "string.h"

#define ManufactDeviceID_CMD	0x90
#define READ_STATU_REGISTER_1   0x05
#define READ_STATU_REGISTER_2   0x35
#define READ_DATA_CMD	        0x03
#define WRITE_ENABLE_CMD	    0x06
#define WRITE_DISABLE_CMD	    0x04
#define SECTOR_ERASE_CMD	    0x20
#define CHIP_ERASE_CMD	        0xc7
#define PAGE_PROGRAM_CMD        0x02
// #define CHIP_ERASE_CMD	        0xc




static HAL_StatusTypeDef SPI_Transmit(uint8_t* send_buf, uint16_t size);//向 SPI Flash 发送数据的函数
static HAL_StatusTypeDef SPI_Receive(uint8_t* recv_buf, uint16_t size);//从 SPI Flash 接收数据的函数
static HAL_StatusTypeDef SPI_TransmitReceive(uint8_t* send_buf, uint8_t* recv_buf, uint16_t size);//发送数据的同时读取数据的函数


uint16_t W25QXX_ReadID(void);//读取Flash内部的ID
static uint8_t W25QXX_ReadSR(uint8_t reg);//读取W25QXX的状态寄存器，W25Q64一共有2个状态寄存器
int W25QXX_Read(uint8_t* buffer, uint32_t start_addr, uint16_t nbytes);//
void W25QXX_Write_Enable(void);
void W25QXX_Write_Disable(void);
void W25QXX_Erase_Sector(uint32_t sector_addr);
void W25QXX_Page_Program(uint8_t* dat, uint32_t WriteAddr, uint16_t nbytes);
void W25QXX_Erase_chip(void);


#endif /* __MAIN_H */