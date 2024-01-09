#ifndef APP_DASHBOARD_INTERFACE_H_
#define APP_DASHBOARD_INTERFACE_H_

void voidStartMotorDashboard(const DCMOTOR_Config_t* Copy_pstDCMotor, const STP_Config_t* Copy_pstSTPMotor);
void voidDCMotorPanel(const DCMOTOR_Config_t* Copy_pstMotorConfig);
void voidSTPMotorPanel(const STP_Config_t* Copy_pstMotorConfig);

#endif /* APP_DASHBOARD_INTERFACE_H_ */
