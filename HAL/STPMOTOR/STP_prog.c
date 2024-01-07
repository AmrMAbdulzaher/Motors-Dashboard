#include "../../Library/STD_TYPES.h"
#include "../../Library/BIT_MATH.h"

#include "../../Library/ErrType.h"
#include <util/delay.h>

#include "../../MCAL/DIO/DIO_interface.h"
#include "STP_cfg.h"
#include "STP_interface.h"
#include "STP_prv.h"


uint8 STP_u8Rotate(const STP_Config_t* Copy_pstConfig,uint8 Copy_u8Direction,uint16 Copy_u16Angle)
{
	uint8 Local_u8ErrorState = OK;
	uint16 Local_u16Steps= (uint16)(((uint32)Copy_u16Angle*2048UL)/360UL);
	uint16 Local_u8LoopIterator;

	if(Copy_pstConfig != NULL)
	{
		for(Local_u8LoopIterator=0;Local_u8LoopIterator<Local_u16Steps;Local_u8LoopIterator++)
		{
			if(Copy_u8Direction == CW)
			{
				if(Local_u8LoopIterator%4 == 0)
				{
					DIO_u8SetPinValue(Copy_pstConfig->u8Port,Copy_pstConfig->u8Blue,DIO_u8PIN_LOW);
					DIO_u8SetPinValue(Copy_pstConfig->u8Port,Copy_pstConfig->u8Pink,DIO_u8PIN_HIGH);
					DIO_u8SetPinValue(Copy_pstConfig->u8Port,Copy_pstConfig->u8Yellow,DIO_u8PIN_HIGH);
					DIO_u8SetPinValue(Copy_pstConfig->u8Port,Copy_pstConfig->u8Orange,DIO_u8PIN_HIGH);
					_delay_ms(2);
				}
				else if(Local_u8LoopIterator%4 == 1)
				{
					DIO_u8SetPinValue(Copy_pstConfig->u8Port,Copy_pstConfig->u8Blue,DIO_u8PIN_HIGH);
					DIO_u8SetPinValue(Copy_pstConfig->u8Port,Copy_pstConfig->u8Pink,DIO_u8PIN_LOW);
					DIO_u8SetPinValue(Copy_pstConfig->u8Port,Copy_pstConfig->u8Yellow,DIO_u8PIN_HIGH);
					DIO_u8SetPinValue(Copy_pstConfig->u8Port,Copy_pstConfig->u8Orange,DIO_u8PIN_HIGH);
					_delay_ms(2);
				}
				else if(Local_u8LoopIterator%4 == 2)
				{
					DIO_u8SetPinValue(Copy_pstConfig->u8Port,Copy_pstConfig->u8Blue,DIO_u8PIN_HIGH);
					DIO_u8SetPinValue(Copy_pstConfig->u8Port,Copy_pstConfig->u8Pink,DIO_u8PIN_HIGH);
					DIO_u8SetPinValue(Copy_pstConfig->u8Port,Copy_pstConfig->u8Yellow,DIO_u8PIN_LOW);
					DIO_u8SetPinValue(Copy_pstConfig->u8Port,Copy_pstConfig->u8Orange,DIO_u8PIN_HIGH);
					_delay_ms(2);
				}
				else if(Local_u8LoopIterator%4 == 3)
				{
					DIO_u8SetPinValue(Copy_pstConfig->u8Port,Copy_pstConfig->u8Blue,DIO_u8PIN_HIGH);
					DIO_u8SetPinValue(Copy_pstConfig->u8Port,Copy_pstConfig->u8Pink,DIO_u8PIN_HIGH);
					DIO_u8SetPinValue(Copy_pstConfig->u8Port,Copy_pstConfig->u8Yellow,DIO_u8PIN_HIGH);
					DIO_u8SetPinValue(Copy_pstConfig->u8Port,Copy_pstConfig->u8Orange,DIO_u8PIN_LOW);
					_delay_ms(2);
				}
			}
			else if(Copy_u8Direction == CCW)
			{
				if(Local_u8LoopIterator%4 == 0)
				{
					DIO_u8SetPinValue(Copy_pstConfig->u8Port,Copy_pstConfig->u8Blue,DIO_u8PIN_HIGH);
					DIO_u8SetPinValue(Copy_pstConfig->u8Port,Copy_pstConfig->u8Pink,DIO_u8PIN_HIGH);
					DIO_u8SetPinValue(Copy_pstConfig->u8Port,Copy_pstConfig->u8Yellow,DIO_u8PIN_HIGH);
					DIO_u8SetPinValue(Copy_pstConfig->u8Port,Copy_pstConfig->u8Orange,DIO_u8PIN_LOW);
					_delay_ms(2);
				}
				else if(Local_u8LoopIterator%4 == 1)
				{
					DIO_u8SetPinValue(Copy_pstConfig->u8Port,Copy_pstConfig->u8Blue,DIO_u8PIN_HIGH);
					DIO_u8SetPinValue(Copy_pstConfig->u8Port,Copy_pstConfig->u8Pink,DIO_u8PIN_HIGH);
					DIO_u8SetPinValue(Copy_pstConfig->u8Port,Copy_pstConfig->u8Yellow,DIO_u8PIN_LOW);
					DIO_u8SetPinValue(Copy_pstConfig->u8Port,Copy_pstConfig->u8Orange,DIO_u8PIN_HIGH);
					_delay_ms(2);
				}
				else if(Local_u8LoopIterator%4 == 2)
				{
					DIO_u8SetPinValue(Copy_pstConfig->u8Port,Copy_pstConfig->u8Blue,DIO_u8PIN_HIGH);
					DIO_u8SetPinValue(Copy_pstConfig->u8Port,Copy_pstConfig->u8Pink,DIO_u8PIN_LOW);
					DIO_u8SetPinValue(Copy_pstConfig->u8Port,Copy_pstConfig->u8Yellow,DIO_u8PIN_HIGH);
					DIO_u8SetPinValue(Copy_pstConfig->u8Port,Copy_pstConfig->u8Orange,DIO_u8PIN_HIGH);
					_delay_ms(2);
				}
				else if(Local_u8LoopIterator%4 == 3)
				{
					DIO_u8SetPinValue(Copy_pstConfig->u8Port,Copy_pstConfig->u8Blue,DIO_u8PIN_LOW);
					DIO_u8SetPinValue(Copy_pstConfig->u8Port,Copy_pstConfig->u8Pink,DIO_u8PIN_HIGH);
					DIO_u8SetPinValue(Copy_pstConfig->u8Port,Copy_pstConfig->u8Yellow,DIO_u8PIN_HIGH);
					DIO_u8SetPinValue(Copy_pstConfig->u8Port,Copy_pstConfig->u8Orange,DIO_u8PIN_HIGH);
					_delay_ms(2);
				}
			}
		}
	}
	else
	{
		Local_u8ErrorState = NULL_PTR_ERR;
	}

	return Local_u8ErrorState;
}
