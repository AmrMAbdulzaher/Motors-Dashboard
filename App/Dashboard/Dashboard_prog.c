#include "../Library/STD_TYPES.h"
#include <util/delay.h>

#include "../MCAL/DIO/DIO_interface.h"
#include "../MCAL/PORT/PORT_interface.h"
#include "../HAL/STPMOTOR/STP_interface.h"
#include "../HAL/DCMOTOR/DCMOTOR_interface.h"
#include "../HAL/KPD/KPD_interface.h"
#include "../HAL/CLCD/CLCD_interface.h"

#include "Dashboard_interface.h"

void voidStartMotorDashboard(const DCMOTOR_Config_t* Copy_pstDCMotor, const STP_Config_t* Copy_pstSTPMotor)
{
	uint8 Local_u8KPDKey;
	while(1)
	{
		CLCD_voidClear();
		CLCD_u8SendString("1- DC MOTOR");
		CLCD_voidGoToXY(0,1);
		CLCD_u8SendString("2- STP Motor");

		do
		{
			Local_u8KPDKey = KPD_u8GetPressedKey();
		}while(Local_u8KPDKey != 1 && Local_u8KPDKey != 2);

		if(Local_u8KPDKey == 1)
		{
			voidDCMotorPanel(Copy_pstDCMotor);
		}
		else if (Local_u8KPDKey == 2)
		{
			voidSTPMotorPanel(Copy_pstSTPMotor);
		}
	}
}
void voidDCMotorPanel(const DCMOTOR_Config_t* Copy_pstMotorConfig)
{
	uint8 Local_u8KPDKey;

	CLCD_voidClear();
	CLCD_u8SendString("1- CW for 5sec");
	CLCD_voidGoToXY(0,1);
	CLCD_u8SendString("2- CCW for 5sec");

	do
	{
		Local_u8KPDKey = KPD_u8GetPressedKey();
	}while(Local_u8KPDKey != 1 && Local_u8KPDKey != 2);

	CLCD_voidClear();

	if(Local_u8KPDKey == 1)
	{
		CLCD_u8SendString("  Rotating CW");
		DCMOTOR_u8RotateCW(Copy_pstMotorConfig);
		_delay_ms(5000);
		DCMOTOR_u8Stop(Copy_pstMotorConfig);
	}
	else if(Local_u8KPDKey == 2)
	{
		CLCD_u8SendString("  Rotating CCW");
		DCMOTOR_u8RotateCCW(Copy_pstMotorConfig);
		_delay_ms(5000);
		DCMOTOR_u8Stop(Copy_pstMotorConfig);
	}

}
void voidSTPMotorPanel(const STP_Config_t* Copy_pstMotorConfig)
{
	uint8 Local_u8KPDKey;
	uint16 Local_u16Degree;
	uint8 Local_u8DigitsCounter;

	while(1)
	{
		Local_u16Degree=0;
		Local_u8DigitsCounter=0;

		CLCD_voidClear();
		CLCD_u8SendString("Enter degree:");
		CLCD_voidGoToXY(0,1);

		do
		{
			do
			{
				Local_u8KPDKey= KPD_u8GetPressedKey();
			}while(Local_u8KPDKey == 0xff);

			if(Local_u8KPDKey == '=' || Local_u8DigitsCounter == 3)
			{
				continue;
			}

			Local_u16Degree = (uint16)((Local_u16Degree*10U) + (uint16)Local_u8KPDKey);

			CLCD_voidGoToXY(Local_u8DigitsCounter,1);
			Local_u8DigitsCounter++;
			CLCD_voidSendNumber(Local_u8KPDKey);

		}while(Local_u8KPDKey != '=');

		CLCD_voidClear();

		if(Local_u16Degree >= 0 && Local_u16Degree <= 360)
		{
			CLCD_u8SendString("1- CW");
			CLCD_voidGoToXY(0,1);
			CLCD_u8SendString("2- CCW");

			do
			{
				Local_u8KPDKey = KPD_u8GetPressedKey();
			}while(Local_u8KPDKey != 1 && Local_u8KPDKey != 2);

			CLCD_voidClear();

			if(Local_u8KPDKey == 1)
			{
				CLCD_u8SendString("  Rotating  CW");
				CLCD_voidGoToXY(3,1);
				CLCD_voidSendNumber(Local_u16Degree);
				CLCD_voidGoToXY(7,1);
				CLCD_u8SendString("degree");
				STP_u8Rotate(Copy_pstMotorConfig,CW,Local_u16Degree);
			}
			else if(Local_u8KPDKey == 2)
			{
				CLCD_u8SendString("  Rotating CCW");
				CLCD_voidGoToXY(3,1);
				CLCD_voidSendNumber(Local_u16Degree);
				CLCD_voidGoToXY(7,1);
				CLCD_u8SendString("degree");
				STP_u8Rotate(Copy_pstMotorConfig,CCW,Local_u16Degree);
			}

			_delay_ms(2000);

			break;
		}
		else
		{

			CLCD_u8SendString(" Invalid Degree");
			CLCD_voidGoToXY(1,1);
			CLCD_u8SendString("range 0 to 360");

			_delay_ms(2000);
		}
	}
}
