#include "../../Library/STD_TYPES.h"
#include "../../Library/BIT_MATH.h"
#include "../../Library/ErrType.h"
#include <util/delay.h>

#include "../../MCAL/DIO/DIO_interface.h"
#include "DCMOTOR_cfg.h"
#include "DCMOTOR_interface.h"
#include "DCMOTOR_prv.h"


uint8 DCMOTOR_u8RotateCW(const DCMOTOR_Config_t* Copy_pstConfig)
{
	uint8 Local_ErrorState = OK;

	if(Copy_pstConfig != NULL)
	{
		DIO_u8SetPinValue(Copy_pstConfig->u8Port,Copy_pstConfig->u8Pin2,DIO_u8PIN_LOW);
		DIO_u8SetPinValue(Copy_pstConfig->u8Port,Copy_pstConfig->u8Pin1,DIO_u8PIN_HIGH);
	}
	else
	{
		Local_ErrorState = NULL_PTR_ERR;
	}

	return Local_ErrorState;
}
uint8 DCMOTOR_u8RotateCCW(const DCMOTOR_Config_t* Copy_pstConfig)
{
	uint8 Local_ErrorState = OK;

	if(Copy_pstConfig != NULL)
	{
		DIO_u8SetPinValue(Copy_pstConfig->u8Port,Copy_pstConfig->u8Pin1,DIO_u8PIN_LOW);
		DIO_u8SetPinValue(Copy_pstConfig->u8Port,Copy_pstConfig->u8Pin2,DIO_u8PIN_HIGH);
	}
	else
	{
		Local_ErrorState = NULL_PTR_ERR;
	}

	return Local_ErrorState;
}
uint8 DCMOTOR_u8Stop(const DCMOTOR_Config_t* Copy_pstConfig)
{
	uint8 Local_ErrorState = OK;
	if(Copy_pstConfig != NULL)
	{
		DIO_u8SetPinValue(Copy_pstConfig->u8Port,Copy_pstConfig->u8Pin1,DIO_u8PIN_LOW);
		DIO_u8SetPinValue(Copy_pstConfig->u8Port,Copy_pstConfig->u8Pin2,DIO_u8PIN_LOW);
	}
	else
	{
		Local_ErrorState = NULL_PTR_ERR;
	}
	return Local_ErrorState;
}
