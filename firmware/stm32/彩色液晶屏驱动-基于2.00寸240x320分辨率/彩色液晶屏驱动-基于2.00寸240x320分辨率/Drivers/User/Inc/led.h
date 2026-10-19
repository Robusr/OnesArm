#ifndef __LED_H
#define __LED_H

#include "main.h"



/*------------------------------------------ LED配置宏 ----------------------------------*/

#define LED1_PIN            			 GPIO_PIN_13        				 	// LED1 引脚      
#define LED1_PORT           			 GPIOC                 			 	// LED1 GPIO端口     
#define __HAL_RCC_LED1_CLK_ENABLE    __HAL_RCC_GPIOC_CLK_ENABLE() 	// LED1 GPIO端口时钟
 

  
/*----------------------------------------- LED控制宏 ----------------------------------*/
						
#define LED1_ON 		LED1_PORT->BRR 	=  LED1_PIN  	// LED1亮，此时IO口是低电平
#define LED1_OFF		LED1_PORT->BSRR 	=  LED1_PIN		// LED1灭，此时IO口是高电平
#define LED1_Toggle	HAL_GPIO_TogglePin(LED1_PORT,LED1_PIN);							// 翻转IO口状态
			
		
/*---------------------------------------- 函数声明 ------------------------------------*/

void LED_Init(void);

#endif //__LED_H


