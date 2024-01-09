#ifndef APP_PASS_SYS_INTERFACE_H_
#define APP_PASS_SYS_INTERFACE_H_

#define NUM_OF_DIGITS		4U
#define NUM_OF_TRIES		3U

void voidGetPasswordToSet(uint8 Copy_au8SetPassword[]);
void voidGetPasswordtoCheck(const uint8 Copy_au8SetPassword[], uint8 Copy_au8CheckPassword[]);

#endif /* APP_PASS_SYS_INTERFACE_H_ */
