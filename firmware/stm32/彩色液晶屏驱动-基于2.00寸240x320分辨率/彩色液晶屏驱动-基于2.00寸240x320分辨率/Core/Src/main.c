/***
	*************************************************************************************************
	*	@file  	main.c
	*	@version V1.0
	*  @date    2023-3-15
	*	@author  反客科技
	*	@brief   SPI驱动屏幕
   ************************************************************************************************
   *  @description
	*
	*	实验平台：反客STM32F407ZGT6核心板 （型号：FK407M2-ZGT6）+ 2.00寸液晶模块（型号：SPI200M1-240*320）
	*	淘宝地址：https://shop212360197.taobao.com
	*	QQ交流群：536665479
	*
>>>>> 功能说明：
	*
	*	SPI驱动LCD进行简单的演示
	*
	************************************************************************************************
***/

#include "main.h"
#include "led.h"
#include "usart.h"
#include "lcd_spi_200.h"



// LCD测试函数，函数定义在底部
void 	LCD_Test_Clear(void);			// 清屏测试
void 	LCD_Test_Text(void);			   // 文本测试
void 	LCD_Test_Variable (void);	   // 变量显示，包括整数和小数
void 	LCD_Test_Color(void);			// 矩形填充测试
void 	LCD_Test_Grahic(void);		   // 2D图形绘制
void 	LCD_Test_Image(void);			// 图片显示
void  LCD_Test_Direction(void);	   // 更换显示方向

/********************************************** 函数声明 *******************************************/

void SystemClock_Config(void);		// 时钟初始化


int main(void)
{
	HAL_Init();					// 初始化HAL库
	SystemClock_Config();	// 配置系统时钟
	LED_Init();					// 初始化LED引脚
	USART1_Init();				// USART1初始化	

	SPI_LCD_Init();			// SPI LCD屏幕初始化
	
	while (1)
	{
		LCD_Test_Clear(); 		// 清屏测试
		LCD_Test_Text();			// 文本测试
		LCD_Test_Variable();		// 变量显示，包括整数和小数
		LCD_Test_Color();			// 颜色测试
		LCD_Test_Grahic();		// 2D图形绘制	
		LCD_Test_Image();			// 图片显示
		LCD_Test_Direction();	// 更换显示方向	
	}
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}



/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}


/*************************************************************************************************
*	函 数 名:	LCD_Test_Clear
*
*	函数功能:	清屏测试
*************************************************************************************************/
void LCD_Test_Clear(void)
{
	uint8_t	i = 0;			// 计数变量
			
	LCD_SetTextFont(&CH_Font24);			// 设置2424中文字体,ASCII字体对应为2412
	LCD_SetColor(LCD_BLACK);				// 设置画笔颜色

	for(i=0;i<8;i++)
	{
		switch (i)		// 切换背景色
		{
			case 0: LCD_SetBackColor(LIGHT_RED); 		break;	
			case 1: LCD_SetBackColor(LIGHT_GREEN); 	break;				
			case 2: LCD_SetBackColor(LIGHT_BLUE); 		break;
			case 3: LCD_SetBackColor(LIGHT_YELLOW); 	break;
			case 4: LCD_SetBackColor(LIGHT_CYAN);		break;
			case 5: LCD_SetBackColor(LIGHT_GREY); 		break;
			case 6: LCD_SetBackColor(LIGHT_MAGENTA); 	break;
			case 7: LCD_SetBackColor(LCD_WHITE); 		break;			
			default:	break;			
		}
		LCD_Clear();		// 清屏
		LCD_DisplayText(13, 70,"STM32 刷屏测试");
		LCD_DisplayText(13,106,"屏幕分辨率:240*320");
		LCD_DisplayText(13,142,"控制器:ST7789");	
		HAL_Delay(1000);	// 延时
	}
}

/*************************************************************************************************
*	函 数 名:	LCD_Test_Text
*
*	函数功能:	文本显示测试
*
*	说    明:	显示文本，包括各种字体大小的中文和ASCII字符 
*************************************************************************************************/
void LCD_Test_Text(void)
{
	LCD_SetBackColor(LCD_BLACK); 			//	设置背景色
	LCD_Clear(); 								// 清屏
	
	LCD_SetColor(LCD_WHITE);
	LCD_SetAsciiFont(&ASCII_Font32); LCD_DisplayString(0, 0,"!#$'()*+,-.0123"); 						    		
	LCD_SetAsciiFont(&ASCII_Font24); LCD_DisplayString(0,32,"!#$'()*+,-.012345678"); 				   
	LCD_SetAsciiFont(&ASCII_Font20); LCD_DisplayString(0,56,"!#$'()*+,-.0123456789:;<");      	
	LCD_SetAsciiFont(&ASCII_Font16); LCD_DisplayString(0,76,"!#$'()*+,-.0123456789:;<=>?@AB"); 	
	LCD_SetAsciiFont(&ASCII_Font12); LCD_DisplayString(0,92,"!#$'()*+,-.0123456789:;<=>?@ABCDEFGHIJKL"); 	
																																		
	LCD_SetColor(LCD_CYAN);                                                                             
	LCD_SetAsciiFont(&ASCII_Font12); LCD_DisplayString(0,104,"!#&'()*+,-.0123456789:;<=>?@ABCDEFGHIJKL"); 	
	LCD_SetAsciiFont(&ASCII_Font16); LCD_DisplayString(0,116,"!#&'()*+,-.0123456789:;<=>?@AB"); 	
	LCD_SetAsciiFont(&ASCII_Font20); LCD_DisplayString(0,132,"!#&'()*+,-.0123456789:;<");		  	
	LCD_SetAsciiFont(&ASCII_Font24); LCD_DisplayString(0,152,"!#&'()*+,-.012345678"); 				  	
	LCD_SetAsciiFont(&ASCII_Font32); LCD_DisplayString(0,176,"!#&'()*+,-.0123"); 							  		

	LCD_SetTextFont(&CH_Font24);			// 设置2424中文字体,ASCII字体对应为2412
	LCD_SetColor(LCD_YELLOW);				// 设置画笔，黄色
	LCD_DisplayText(0, 216,"ASCII字符集");

	HAL_Delay(2000);	// 延时等待
	LCD_Clear(); 								// 清屏

	LCD_SetTextFont(&CH_Font12);			// 设置1212中文字体,ASCII字体对应为1206
	LCD_SetColor(0X8AC6D1);					// 设置画笔
	LCD_DisplayText(14, 10,"1212:反客科技");	
	
	LCD_SetTextFont(&CH_Font16);			// 设置1616中文字体,ASCII字体对应为1608
	LCD_SetColor(0XC5E1A5);					// 设置画笔
	LCD_DisplayText(14, 30,"1616:反客科技");		
	
	LCD_SetTextFont(&CH_Font20);			// 设置2020中文字体,ASCII字体对应为2010
	LCD_SetColor(0XFFB549);					// 设置画笔
	LCD_DisplayText(14, 60,"2020:反客科技");		

	LCD_SetTextFont(&CH_Font24);			// 设置2424中文字体,ASCII字体对应为2412
	LCD_SetColor(0XFF585D);					// 设置画笔
	LCD_DisplayText(14, 90,"2424:反客科技");		

	LCD_SetTextFont(&CH_Font32);			// 设置3232中文字体,ASCII字体对应为3216
	LCD_SetColor(0xFFB6B9);					// 设置画笔
	LCD_DisplayText(14, 130,"3232:反客科技");		

	LCD_SetTextFont(&CH_Font24);			// 设置2424中文字体,ASCII字体对应为2412
	LCD_SetColor(LCD_WHITE);
 	LCD_DisplayText(14, 180,"中文显示");	  

	HAL_Delay(2000);	// 延时等待
}
/************************************************************************************************
*	函 数 名:	LCD_Test_Variable
*
*	函数功能:	变量显示，包括整数和小数
*************************************************************************************************/
void LCD_Test_Variable (void)
{
	uint16_t i;					// 计数变量
	int32_t	a = 0;			// 定义整数变量，用于测试
	int32_t	b = 0;			// 定义整数变量，用于测试
	int32_t	c = 0;			// 定义整数变量，用于测试

	double p = 3.1415926;	// 定义浮点数变量，用于测试
	double f = -1234.1234;	// 定义浮点数变量，用于测试
	
	LCD_SetBackColor(LCD_BLACK); 			//	设置背景色
	LCD_Clear(); 								// 清屏
	
   LCD_SetTextFont(&CH_Font24);     
	LCD_SetColor(LIGHT_CYAN);					// 设置画笔，蓝绿色		
	LCD_DisplayText(0,10,"正数:");				
	LCD_DisplayText(0,40,"负数:");					
				
	LCD_SetColor(LIGHT_YELLOW);				// 设置画笔，亮黄色		
	LCD_DisplayText(0, 80,"填充空格:");	
	LCD_DisplayText(0,110,"填充0:");	
	
	LCD_SetColor(LIGHT_RED);					// 设置画笔	，亮红色		
	LCD_DisplayText(0, 150,"正小数:");	
	LCD_DisplayText(0, 180,"负小数:");		
	
	for(i=0;i<100;i++)
   {
		LCD_SetColor(LIGHT_CYAN);								// 设置画笔	，蓝绿色	
		LCD_ShowNumMode(Fill_Space);							// 多余位填充空格
		LCD_DisplayNumber( 80,10, b+i*10, 4) ;				// 显示变量			
		LCD_DisplayNumber( 80,40, c-i*10, 4) ;				// 显示变量			
		
		LCD_SetColor(LIGHT_YELLOW);								// 设置画笔，亮黄色	

		LCD_ShowNumMode(Fill_Space);								// 多余位填充 空格
		LCD_DisplayNumber( 130, 80, a+i*150, 8) ;				// 显示变量		

		LCD_ShowNumMode(Fill_Zero);								// 多余位填充0      
		LCD_DisplayNumber( 130,110, b+i*150, 8) ;				// 显示变量			
		
		LCD_SetColor(LIGHT_RED);									// 设置画笔，亮红色			
		LCD_ShowNumMode(Fill_Space);								// 多余位填充空格		
		LCD_DisplayDecimals( 100, 150, p+i*0.1,  6,3);		// 显示小数	
		LCD_DisplayDecimals( 100, 180, f+i*0.01, 11,4);		// 显示小数		
		
		HAL_Delay(15);				
   }
	HAL_Delay(2500);		
}
/*************************************************************************************************
*	函 数 名:	LCD_Test_Color
*
*	函数功能:	颜色测
*************************************************************************************************/
void LCD_Test_Color(void)
{
	uint16_t i;					// 计数变量
	uint16_t y;
// 颜色测试>>>>>	
	LCD_SetBackColor(LCD_BLACK); //设置背景色
	LCD_Clear(); //清屏，刷背景色
	
	LCD_SetTextFont(&CH_Font20);			// 设置字体
	LCD_SetColor(LCD_WHITE);				// 设置画笔颜色
	LCD_DisplayText(0,0,"RGB三基色:");

	//使用画线函数绘制三基色色条
	for(i=0;i<240;i++)
	{
		LCD_SetColor( LCD_RED-(i<<16) );
      LCD_DrawLine_V(0+i,  20,10);
	}
	for(i=0;i<240;i++)
	{
		LCD_SetColor( LCD_GREEN-(i<<8) );
      LCD_DrawLine_V(0+i,  35,10);
	}
	for(i=0;i<240;i++)
	{
		LCD_SetColor( LCD_BLUE-i );
      LCD_DrawLine_V(0+i,  50,10);
	}	

   y = 70;
   LCD_SetColor(LIGHT_CYAN);    LCD_FillRect(150,y+5     ,90,10);  LCD_DisplayString(0,y     ,"LIGHT_CYAN");	   
	LCD_SetColor(LIGHT_MAGENTA); LCD_FillRect(150,y+20*1+5,90,10);  LCD_DisplayString(0,y+20*1,"LIGHT_MAGENTA");	
	LCD_SetColor(LIGHT_YELLOW);  LCD_FillRect(150,y+20*2+5,90,10);  LCD_DisplayString(0,y+20*2,"LIGHT_YELLOW");	
	LCD_SetColor(LIGHT_GREY);    LCD_FillRect(150,y+20*3+5,90,10);  LCD_DisplayString(0,y+20*3,"LIGHT_GREY");  	
	LCD_SetColor(LIGHT_RED);     LCD_FillRect(150,y+20*4+5,90,10);  LCD_DisplayString(0,y+20*4,"LIGHT_RED");  	
	LCD_SetColor(LIGHT_BLUE);    LCD_FillRect(150,y+20*5+5,90,10);  LCD_DisplayString(0,y+20*5,"LIGHT_BLUE");  	

   LCD_SetColor(DARK_CYAN);     LCD_FillRect(150,y+20*6+5,90,10);  LCD_DisplayString(0,y+20*6,"DARK_CYAN");		
	LCD_SetColor(DARK_MAGENTA);  LCD_FillRect(150,y+20*7+5,90,10);  LCD_DisplayString(0,y+20*7,"DARK_MAGENTA");	
	LCD_SetColor(DARK_YELLOW);   LCD_FillRect(150,y+20*8+5,90,10);  LCD_DisplayString(0,y+20*8,"DARK_YELLOW");	
	LCD_SetColor(DARK_GREY);     LCD_FillRect(150,y+20*9+5,90,10);	 LCD_DisplayString(0,y+20*9,"DARK_GREY");	
	LCD_SetColor(DARK_RED);   	  LCD_FillRect(150,y+20*10+5,90,10); LCD_DisplayString(0,y+20*10,"DARK_RED");	
	LCD_SetColor(DARK_GREEN);    LCD_FillRect(150,y+20*11+5,90,10); LCD_DisplayString(0,y+20*11,"DARK_GREEN");	

	HAL_Delay(2000);
}

/*************************************************************************************************
*	函 数 名:	LCD_Test_Grahic
*
*	函数功能:	2D图形绘制
*************************************************************************************************/
void LCD_Test_Grahic(void)
{
	LCD_SetBackColor(LCD_BLACK); //设置背景色
	LCD_Clear(); //清屏，刷背景色	

	LCD_SetColor(LCD_WHITE);	
	LCD_DrawRect(0,0,240,320); 			//绘制矩形

	LCD_SetColor(LCD_RED);    LCD_FillCircle(140,50,30);		//填充圆形
	LCD_SetColor(LCD_GREEN);  LCD_FillCircle(170,50,30); 	
	LCD_SetColor(LCD_BLUE);   LCD_FillCircle(200,50,30);  	
	
	LCD_SetColor(LCD_YELLOW);
	LCD_DrawLine(26,26,113,64);				//画直线
	LCD_DrawLine(35,22,106,81);				//画直线
	LCD_DrawLine(45,20, 93,100);				//画直线
	LCD_DrawLine(52,16, 69,108);				//画直线
	LCD_DrawLine(62,16, 44,108);				//画直线
	
	LCD_SetColor(LIGHT_CYAN);
	LCD_DrawCircle(120,170,30);			//绘制圆形
	LCD_DrawCircle(120,170,20);   

	LCD_SetColor(LIGHT_RED);	
	LCD_DrawEllipse(120,170,90,40); 	//绘制椭圆 
	LCD_DrawEllipse(120,170,70,40); 	//绘制椭圆    
	LCD_SetColor(LIGHT_MAGENTA);	
	LCD_DrawEllipse(120,170,100,50); 	//绘制椭圆
	LCD_DrawEllipse(120,170,110,60);  
	
	LCD_SetColor(DARK_RED);  	LCD_FillRect( 50, 250, 50, 50);			//填充矩形
	LCD_SetColor(DARK_BLUE); 	LCD_FillRect(100, 250, 50, 50);			//填充矩形	
	LCD_SetColor(LIGHT_GREEN); LCD_FillRect(150, 250, 50, 50);			//填充矩形	
	
	HAL_Delay(2000);		
}
/*************************************************************************************************
*	函 数 名:	LCD_Test_Image
*
*	函数功能:	图片显示测试
*************************************************************************************************/
void LCD_Test_Image(void)
{
	LCD_SetBackColor(LCD_BLACK); 			//	设置背景色
	LCD_Clear(); 								// 清屏
	
	LCD_SetColor( 0xffF6E58D);
	LCD_DrawImage( 19, 55, 83, 83, Image_Android_83x83) ;	   // 显示图片

	LCD_SetColor( 0xffDFF9FB);
	LCD_DrawImage( 141, 55, 83, 83, Image_Message_83x83) ;	// 显示图片
	
	LCD_SetColor( 0xff9DD3A8);
	LCD_DrawImage( 19, 175, 83, 83, Image_Toys_83x83) ;		// 显示图片
	
	LCD_SetColor( 0xffFF8753);
	LCD_DrawImage( 141, 175, 83, 83, Image_Video_83x83) ;		// 显示图片

	HAL_Delay(2000);	
}
/*************************************************************************************************
*	函 数 名:	LCD_Test_Direction
*
*	函数功能:	更换显示方向
*************************************************************************************************/
void  LCD_Test_Direction(void)
{
	int i;
	for( i=0;i<4;i++ )
	{  
      LCD_SetBackColor(LCD_BLACK); 			//	设置背景色
      LCD_Clear(); 								// 清屏
      LCD_SetTextFont(&CH_Font24);  
	   LCD_SetColor( 0xffDFF9FB);         
		switch (i)		// 切换背景色
		{
			case 0:  
            LCD_SetDirection(Direction_V);		   
            LCD_DisplayText(20,20,"Direction_V"); 
         break;	

			case 1:  
            LCD_SetDirection(Direction_H); 	
            LCD_DisplayText(20,20,"Direction_H"); 
         break;	

			case 2:  
            LCD_SetDirection(Direction_V_Flip); 
            LCD_DisplayText(20,20,"Direction_V_Flip"); 
         break;
			case 3: 
            LCD_SetDirection(Direction_H_Flip); 	
            LCD_DisplayText(20,20,"Direction_H_Flip"); 
         break;
	
			default:	break;			
		}
      LCD_SetColor( 0xffF6E58D);
      LCD_DrawImage( 19, 80, 83, 83, Image_Android_83x83) ;	   // 显示图片
      LCD_SetTextFont(&CH_Font32);
      LCD_SetColor( 0xff9DD3A8);  
      LCD_DisplayText(130,90,"反客");
      LCD_DisplayText(130,130,"科技");
      LCD_SetDirection(Direction_V);	
      HAL_Delay(1000);	// 延时
	}
}





