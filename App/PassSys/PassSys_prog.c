#include "../Library/STD_TYPES.h"
#include <util/delay.h>

#include "../HAL/KPD/KPD_interface.h"
#include "../HAL/CLCD/CLCD_interface.h"

#include "PassSys_interface.h"

void voidGetPasswordToSet(uint8 Copy_au8SetPassword[])
{
	uint8 Local_u8DigitsCounter;
	uint8 Local_u8KPDKey;

	CLCD_u8SendString("Set Password:");
	for(Local_u8DigitsCounter=0;Local_u8DigitsCounter<NUM_OF_DIGITS;Local_u8DigitsCounter++)
	{
		do
		{
			Local_u8KPDKey= KPD_u8GetPressedKey();
		}while(Local_u8KPDKey == 0xff || Local_u8KPDKey == '=');

		Copy_au8SetPassword[Local_u8DigitsCounter]=Local_u8KPDKey;

		CLCD_voidGoToXY(Local_u8DigitsCounter,1);
		CLCD_voidSendNumber(Local_u8KPDKey);
		_delay_ms(200);
		CLCD_voidGoToXY(Local_u8DigitsCounter,1);
		CLCD_voidSendData('*');
	}
	CLCD_voidClear();
	CLCD_u8SendString("PW has been set!");
	_delay_ms(1000);
}
void voidGetPasswordtoCheck(const uint8 Copy_au8SetPassword[],uint8 Copy_au8CheckPassword[])
{
	uint8 Local_u8DigitsCounter;
	uint8 Local_u8KPDKey;
	uint8 Local_u8WrongPasswordFlag=0;
	uint8 Local_u8PassowrdEntryTries = NUM_OF_TRIES;

	while(Local_u8PassowrdEntryTries > 0)
	{
		CLCD_voidClear();
		CLCD_u8SendString("Enter Password:");
		Local_u8WrongPasswordFlag = 0;
		for(Local_u8DigitsCounter=0;Local_u8DigitsCounter<NUM_OF_DIGITS;Local_u8DigitsCounter++)
		{
			do
			{
				Local_u8KPDKey= KPD_u8GetPressedKey();
			}while(Local_u8KPDKey == 0xff || Local_u8KPDKey == '=');

			Copy_au8CheckPassword[Local_u8DigitsCounter]=Local_u8KPDKey;

			CLCD_voidGoToXY(Local_u8DigitsCounter,1);
			CLCD_voidSendNumber(Local_u8KPDKey);
			_delay_ms(200);
			CLCD_voidGoToXY(Local_u8DigitsCounter,1);
			CLCD_voidSendData('*');
			if(Copy_au8CheckPassword[Local_u8DigitsCounter] != Copy_au8SetPassword[Local_u8DigitsCounter])
			{
				Local_u8WrongPasswordFlag = 1;
			}
		}
		if(Local_u8WrongPasswordFlag == 0)
		{
			break;
		}
		else
		{
			Local_u8PassowrdEntryTries--;
			if(Local_u8PassowrdEntryTries>0)
			{
				CLCD_voidClear();
				CLCD_u8SendString(" Wrong Password ");
				CLCD_voidGoToXY(2,1);
				CLCD_u8SendString("Tries Left:");
				CLCD_voidSendNumber(Local_u8PassowrdEntryTries);
				_delay_ms(2000);
			}
		}

	}

	if(Local_u8WrongPasswordFlag == 1)
	{

		CLCD_voidClear();
		CLCD_u8SendString(" NO TRIES LEFT!");
		CLCD_voidGoToXY(1,1);
		CLCD_u8SendString("SYSTEM LOCKED!");
		while(1);
	}
}
