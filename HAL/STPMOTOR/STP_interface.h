#ifndef STP_INTERFACE_H
#define STP_INTERFACE_H

typedef enum
{
	CW=0,
	CCW=1
}STP_Direction;

typedef struct
{
	uint8 u8Port;
	uint8 u8Blue;
	uint8 u8Pink;
	uint8 u8Yellow;
	uint8 u8Orange;
}STP_Config_t;

uint8 STP_u8Rotate(const STP_Config_t* Copy_pstConfig,uint8 Copy_u8Direction,uint16 Copy_u16Angle);

#endif
