/*
 * config.h
 *
 *  Automatically created by Flexible OpenSource firmware - Configuration tool
 *  Author: stancecoke
 *  Author: casainho
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#define EBIKE_THROTTLE_TYPE EBIKE_THROTTLE_TYPE_TORQUE_SENSOR
#define EBIKE_THROTTLE_TYPE_THROTTLE_PAS_CURRENT_SPEED
#define EBIKE_THROTTLE_TYPE_THROTTLE_PAS_ASSIST_LEVEL_PAS_ONLY
#define PAS_NUMBER_MAGNETS 12
#define PAS_MAX_CADENCE_RPM 80
#define PAS_DIRECTION PAS_DIRECTION_RIGHT
#define ASSIST_LEVEL_0 0.0
#define ASSIST_LEVEL_1 0.2
#define ASSIST_LEVEL_2 0.4
#define ASSIST_LEVEL_3 0.6
#define ASSIST_LEVEL_4 0.8
#define ASSIST_LEVEL_5 1.0
#define BATTERY_LI_ION_CELLS_NUMBER 7
#define MOTOR_ROTOR_OFFSET_ANGLE 202
#define FOC_READ_ID_CURRENT_ANGLE_ADJUST 137
#define MOTOR_ROTOR_ERPS_START_INTERPOLATION_60_DEGREES 40
#define ADC_MOTOR_CURRENT_MAX 60
#define ADC_MOTOR_REGEN_CURRENT_MAX 30
#define PWM_DUTY_CYCLE_RAMP_UP_INVERSE_STEP 25
#define PWM_DUTY_CYCLE_RAMP_DOWN_INVERSE_STEP 25

#endif /* CONFIG_H_ */
