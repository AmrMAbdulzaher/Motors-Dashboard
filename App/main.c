#include "../Library/STD_TYPES.h"
#include <util/delay.h>

#include "../MCAL/DIO/DIO_interface.h"
#include "../MCAL/PORT/PORT_interface.h"
#include "../HAL/STPMOTOR/STP_interface.h"
#include "../HAL/DCMOTOR/DCMOTOR_interface.h"
#include "../HAL/KPD/KPD_interface.h"
#include "../HAL/CLCD/CLCD_interface.h"

void voidGetPasswordToSet(uint8 Copy_au8SetPassword[]);
void voidGetPasswordtoCheck(const uint8 Copy_au8SetPassword[], uint8 Copy_au8CheckPassword[]);
void voidStartMotorDashboard(const DCMOTOR_Config_t* Copy_pstDCMotor, const STP_Config_t* Copy_pstSTPMotor);
void voidDCMotorPanel(const DCMOTOR_Config_t* Copy_pstMotorConfig);
void voidSTPMotorPanel(const STP_Config_t* Copy_pstMotorConfig);

void main(void)
{
	PORT_voidInit();
	CLCD_voidInit();

	STP_Config_t STP_MOTOR={
			.u8Port= DIO_u8PORTC,
			.u8Blue= DIO_u8PIN0,
			.u8Pink= DIO_u8PIN1,
			.u8Yellow= DIO_u8PIN2,
			.u8Orange= DIO_u8PIN3,
	};

	DCMOTOR_Config_t DC_MOTOR={
			.u8Port= DIO_u8PORTC,
			.u8Pin1= DIO_u8PIN4,
			.u8Pin2= DIO_u8PIN5,
	};

	uint8 Local_au8SetPassword[4];
	uint8 Local_au8CheckPassword[4];

	while(1)
	{
		voidGetPasswordToSet(Local_au8SetPassword);
		voidGetPasswordtoCheck(Local_au8SetPassword,Local_au8CheckPassword);
		voidStartMotorDashboard(&DC_MOTOR,&STP_MOTOR);
	}
}

void voidGetPasswordToSet(uint8 Copy_au8SetPassword[])
{
	uint8 Local_u8DigitsCounter;
	uint8 Local_u8KPDKey;

	CLCD_u8SendString("Set Password:");
	for(Local_u8DigitsCounter=0;Local_u8DigitsCounter<4;Local_u8DigitsCounter++)
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
	uint8 Local_u8PassowrdEntryTries=3;

	while(Local_u8PassowrdEntryTries > 0)
	{
		CLCD_voidClear();
		CLCD_u8SendString("Enter Password:");
		Local_u8WrongPasswordFlag = 0;
		for(Local_u8DigitsCounter=0;Local_u8DigitsCounter<4;Local_u8DigitsCounter++)
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
