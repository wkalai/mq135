#ifndef __L9110_H
#define __L9110_H  
#include "sys.h" 
#include "stm32f10x.h"

#define MOT1 PBout(13)
#define MOT2 PBout(15)

void fan_Init(void);

#endif
