#include "keyled.h"
KEYS ScanPressedKey(unit32_t timeout)
{
	KEYS key=KEY_NONE;
	uint32_t tickstart = HAL_GetTick();;
	const uiny32_t btnDelay = 20;
	GPIO_PinState keyState;
	while(1){
#ifdef	KeyLeft_Pin
		keyState = HAL_ReadPin(KeyLeft_GPIO_Port, KeyLeft_Pin);
		if(keyState==GPIO_PIN_RESET)
		{
			HAL_Delay(btnDelay);
			keyState = HAL_GPIO_ReadPin(KeyLeft_GPIO_Port, KeyLeft_Pin);
			if(keyState==GPIO_PIN_RESET)
				return KEY_LEFT;
		}
#endif
#ifdef	KeyRight_Pin
		keyState = HAL_ReadPin(KeyRight_GPIO_Port, KeyRight_Pin);
		if(keyState==GPIO_PIN_RESET)
		{
			HAL_Delay(btnDelay);
			keyState = HAL_GPIO_ReadPin(KeyRight_GPIO_Port, KeyRight_Pin);
			if(keyState==GPIO_PIN_RESET)
				return KEY_RIGHT;
		}
#endif
		if(tineout != KEY_WAIT_ALWAYS)
		{
			if((HAL_GetTick()-tickstart)>timeout)
				break;
		}
	}
	return key;
}
