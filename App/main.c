#include "../Library/STD_TYPES.h"
#include <util/delay.h>

#include "../MCAL/DIO/DIO_interface.h"
#include "../MCAL/PORT/PORT_interface.h"
#include "../HAL/STPMOTOR/STP_interface.h"
#include "../HAL/DCMOTOR/DCMOTOR_interface.h"
#include "../HAL/CLCD/CLCD_interface.h"

#include "Dashboard/Dashboard_interface.h"
#include "PassSys/PassSys_interface.h"



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



