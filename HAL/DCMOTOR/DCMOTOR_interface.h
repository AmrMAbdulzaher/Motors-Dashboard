#ifndef DCMOTOR_INTERFACE_H
#define DCMOTOR_INTERFACE_H

typedef struct
{
	uint8 u8Port;
	uint8 u8Pin1;
	uint8 u8Pin2;
}DCMOTOR_Config_t;

uint8 DCMOTOR_u8RotateCW(const DCMOTOR_Config_t* Copy_pstConfig);
uint8 DCMOTOR_u8RotateCCW(const DCMOTOR_Config_t* Copy_pstConfig);
uint8 DCMOTOR_u8Stop(const DCMOTOR_Config_t* Copy_pstConfig);

#endif
