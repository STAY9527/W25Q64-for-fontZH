#include "fun.h"

uint8_t B1;
uint8_t B1_last=1;
uint8_t B2;
uint8_t B2_last=1;

uint8_t readstart[4]={0x03,0x00,0x00,0x00};
uint8_t  read[]={0xff,0xff,0xff,0xff,0xff};
// char massage[20];
void butten(void){
    B1=HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_12);
    B2=HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_13);
    if(B1==0&&B1_last==1){
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
        HAL_SPI_Transmit(&hspi1, (uint8_t*)readstart, 4, 1000);
        HAL_SPI_Receive(&hspi1, (uint8_t*)read, 5, 1000);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
        if(read[0]==0x02){//&&read[1]==0x03&&read[2]==0x05
            OLED_Clear();
            // sprintf(massage,"%d",read);
            OLED_PrintASCIIString(0,0,"OK",&afont16x8,OLED_COLOR_NORMAL);
            OLED_Show();
        }
        else{
            OLED_Clear();
            OLED_PrintASCIIString(0,0,"ERROR",&afont16x8,OLED_COLOR_NORMAL);
            OLED_Show();

        }
        
    }

    B1_last=B1;
    B2_last=B2;
}