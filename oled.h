#ifndef _OLED_H_
#define _OLED_H_

#include "stm32f10x.h"
#include "iic.h"
#include "font.h"

#define OLED_CMD  0	//Ð´ÃüÁî
#define OLED_DATA 1	//Ð´Êý¾Ý
#define OLED_MODE 0

#define SIZE 16          //16---------8
#define XLevelL		0x02
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF 
#define X_WIDTH 	128
#define Y_WIDTH 	64	   
void OLED_Set_Pos(unsigned char x, unsigned char y) ;
void OLED_Display_On(void);
void OLED_Display_Off(void);
void OLED_Send_Command(u8 com);
void Oled_Write_Data(u8 data);
void Oled_Init(void);
void OLED_Clear(void);
void Oled_Address(u8 row,u8 col);
void Oled_Display_Char(u8 page,u8 col,char ch);

void Oled_Display_String(u8 page,u8 col,char *str);

void Oled_Display_Pic(u8 high,u8 wight,u8 page,u8 col,u8 *str);
void Oled_Display_Num(u8 page,u8 col,float f);

#endif
