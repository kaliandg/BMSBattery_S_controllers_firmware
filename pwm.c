/*
 * EGG OpenSource EBike firmware
 *
 * Copyright (C) Casainho, 2015, 2106, 2017.
 *
 * Released under the GPL License, Version 3
 */

#include <stdint.h>
#include <stdio.h>
#include "stm8s_tim1.h"
#include "gpio.h"
#include "pwm.h"
#include "motor.h"

void pwm_init_bipolar_4q (void)
{
  TIM1_CtrlPWMOutputs(DISABLE);

  TIM1_TimeBaseInit(0, // TIM1_Prescaler = 0
		    TIM1_COUNTERMODE_CENTERALIGNED1,
		    (512 - 1), // clock = 16MHz; counter period = 1024; PWM freq = 16MHz / 1024 = 15.625kHz;
		    //(BUT PWM center aligned mode needs twice the frequency)
		    1); // will fire the TIM1_IT_UPDATE at every PWM period cycle


//#define DISABLE_PWM_CHANNELS_1_3

  TIM1_OC1Init(TIM1_OCMODE_PWM1,
#ifdef DISABLE_PWM_CHANNELS_1_3
	       TIM1_OUTPUTSTATE_DISABLE,
	       TIM1_OUTPUTNSTATE_DISABLE,
#else
	       TIM1_OUTPUTSTATE_ENABLE,
	       TIM1_OUTPUTNSTATE_ENABLE,
#endif
	       255, // initial duty_cycle value
	       TIM1_OCPOLARITY_HIGH,
	       TIM1_OCNPOLARITY_LOW,
	       TIM1_OCIDLESTATE_RESET,
	       TIM1_OCNIDLESTATE_SET);

  TIM1_OC2Init(TIM1_OCMODE_PWM1,
	       TIM1_OUTPUTSTATE_ENABLE,
	       TIM1_OUTPUTNSTATE_ENABLE,
	       255, // initial duty_cycle value
	       TIM1_OCPOLARITY_HIGH,
	       TIM1_OCNPOLARITY_LOW,
	       TIM1_OCIDLESTATE_SET,
	       TIM1_OCIDLESTATE_SET);

  TIM1_OC3Init(TIM1_OCMODE_PWM1,
#ifdef DISABLE_PWM_CHANNELS_1_3
	       TIM1_OUTPUTSTATE_DISABLE,
	       TIM1_OUTPUTNSTATE_DISABLE,
#else
	       TIM1_OUTPUTSTATE_ENABLE,
	       TIM1_OUTPUTNSTATE_ENABLE,
#endif
	       255, // initial duty_cycle value
	       TIM1_OCPOLARITY_HIGH,
	       TIM1_OCNPOLARITY_LOW,
	       TIM1_OCIDLESTATE_RESET,
	       TIM1_OCNIDLESTATE_SET);

  // break, dead time and lock configuration
  TIM1_BDTRConfig(TIM1_OSSISTATE_ENABLE,
		  TIM1_LOCKLEVEL_OFF,
		  // hardware nees a dead time of 1us
		  16, // DTG = 0; dead time in 62.5 ns steps; 1us/62.5ns = 16
		  TIM1_BREAK_DISABLE,
		  TIM1_BREAKPOLARITY_LOW,
		  TIM1_AUTOMATICOUTPUT_DISABLE);

  TIM1_ITConfig(TIM1_IT_UPDATE, ENABLE);
  TIM1_Cmd(ENABLE); // TIM1 counter enable
}

void pwm_init_6_steps (void)
{
  TIM1_CtrlPWMOutputs(DISABLE);

  TIM1_TimeBaseInit(0, // TIM1_Prescaler = 0
		     TIM1_COUNTERMODE_UP,
		     (1024 - 1), // clock = 16MHz; counter period = 1024; PWM freq = 16MHz / 1024 = 15.625kHz
		     0); // TIM1_RepetitionCounter = 0

  TIM1_OC1Init(TIM1_OCMODE_PWM1,
	       TIM1_OUTPUTSTATE_ENABLE,
	       TIM1_OUTPUTNSTATE_DISABLE,
	       0, // initial duty_cycle value
	       TIM1_OCPOLARITY_HIGH,
	       TIM1_OCNPOLARITY_LOW,
	       TIM1_OCIDLESTATE_RESET,
	       TIM1_OCNIDLESTATE_SET);

  TIM1_OC2Init(TIM1_OCMODE_PWM1,
	       TIM1_OUTPUTSTATE_ENABLE,
	       TIM1_OUTPUTNSTATE_DISABLE,
	       0, // initial duty_cycle value
	       TIM1_OCPOLARITY_HIGH,
	       TIM1_OCNPOLARITY_LOW,
	       TIM1_OCIDLESTATE_RESET,
	       TIM1_OCNIDLESTATE_SET);

  TIM1_OC3Init(TIM1_OCMODE_PWM1,
	       TIM1_OUTPUTSTATE_ENABLE,
	       TIM1_OUTPUTNSTATE_DISABLE,
	       0, // initial duty_cycle value
	       TIM1_OCPOLARITY_HIGH,
	       TIM1_OCNPOLARITY_LOW,
	       TIM1_OCIDLESTATE_RESET,
	       TIM1_OCNIDLESTATE_SET);

  // break, dead time and lock configuration
  TIM1_BDTRConfig(TIM1_OSSISTATE_ENABLE,
		  TIM1_LOCKLEVEL_OFF,
		  // hardware nees a dead time of 1us
		  16, // DTG = 0; dead time in 62.5 ns steps; 1us/62.5ns = 16
		  TIM1_BREAK_DISABLE,
		  TIM1_BREAKPOLARITY_LOW,
		  TIM1_AUTOMATICOUTPUT_DISABLE);

  // put the phases to a valid state
  pwm_phase_a_disable ();
  pwm_phase_b_disable ();
  pwm_phase_c_disable ();

  TIM1_ITConfig(TIM1_IT_UPDATE, ENABLE);
  TIM1_Cmd(ENABLE); // TIM1 counter enable
}

void pwm_phase_a_disable (void)
{
  TIM1_OC3Init(TIM1_OCMODE_PWM1,
	       TIM1_OUTPUTNSTATE_DISABLE,
  	       TIM1_OUTPUTNSTATE_DISABLE,
	       0,
  	       TIM1_OCPOLARITY_HIGH,
  	       TIM1_OCNPOLARITY_LOW,
  	       TIM1_OCIDLESTATE_RESET,
  	       TIM1_OCNIDLESTATE_SET);

  // disable pin
  GPIO_Init(PMW_PHASE_A_HIGH__PORT,
	    PMW_PHASE_A_HIGH__PIN,
	    GPIO_MODE_OUT_PP_LOW_FAST);

  // disable pin
  GPIO_Init(PMW_PHASE_A_LOW__PORT,
	    PMW_PHASE_A_LOW__PIN,
	    GPIO_MODE_OUT_PP_HIGH_FAST);
}

void pwm_phase_a_enable_pwm (void)
{
  TIM1_OC3Init(TIM1_OCMODE_PWM1,
	       TIM1_OUTPUTSTATE_ENABLE,
	       TIM1_OUTPUTNSTATE_DISABLE,
	       ui8_duty_cycle,
	       TIM1_OCPOLARITY_HIGH,
	       TIM1_OCNPOLARITY_LOW,
	       TIM1_OCIDLESTATE_RESET,
	       TIM1_OCNIDLESTATE_SET);

  // disable pin
  GPIO_Init(PMW_PHASE_A_LOW__PORT,
	    PMW_PHASE_A_LOW__PIN,
	    GPIO_MODE_OUT_PP_HIGH_FAST);
}

void pwm_phase_a_enable_low (void)
{
  TIM1_OC3Init(TIM1_OCMODE_PWM1,
	       TIM1_OUTPUTNSTATE_DISABLE,
  	       TIM1_OUTPUTNSTATE_DISABLE,
	       0,
	       TIM1_OCPOLARITY_HIGH,
	       TIM1_OCNPOLARITY_LOW,
	       TIM1_OCIDLESTATE_RESET,
	       TIM1_OCNIDLESTATE_SET);

  // disable pin
  GPIO_Init(PMW_PHASE_A_HIGH__PORT,
	    PMW_PHASE_A_HIGH__PIN,
	    GPIO_MODE_OUT_PP_LOW_FAST);

  // enable pin
  GPIO_Init(PMW_PHASE_A_LOW__PORT,
	    PMW_PHASE_A_LOW__PIN,
	    GPIO_MODE_OUT_PP_LOW_FAST);
}

void pwm_phase_b_disable (void)
{
  TIM1_OC2Init(TIM1_OCMODE_PWM1,
	       TIM1_OUTPUTNSTATE_DISABLE,
  	       TIM1_OUTPUTNSTATE_DISABLE,
	       0,
  	       TIM1_OCPOLARITY_HIGH,
  	       TIM1_OCNPOLARITY_LOW,
  	       TIM1_OCIDLESTATE_RESET,
  	       TIM1_OCNIDLESTATE_SET);

  // disable pin
  GPIO_Init(PMW_PHASE_B_HIGH__PORT,
	    PMW_PHASE_B_HIGH__PIN,
	    GPIO_MODE_OUT_PP_LOW_FAST);

  // disable pin
  GPIO_Init(PMW_PHASE_B_LOW__PORT,
	    PMW_PHASE_B_LOW__PIN,
	    GPIO_MODE_OUT_PP_HIGH_FAST);
}

void pwm_phase_b_enable_pwm (void)
{
  TIM1_OC2Init(TIM1_OCMODE_PWM1,
	       TIM1_OUTPUTSTATE_ENABLE,
	       TIM1_OUTPUTNSTATE_DISABLE,
	       ui8_duty_cycle,
	       TIM1_OCPOLARITY_HIGH,
	       TIM1_OCNPOLARITY_LOW,
	       TIM1_OCIDLESTATE_RESET,
	       TIM1_OCNIDLESTATE_SET);

  // disable pin
  GPIO_Init(PMW_PHASE_B_LOW__PORT,
	    PMW_PHASE_B_LOW__PIN,
	    GPIO_MODE_OUT_PP_HIGH_FAST);
}

void pwm_phase_b_enable_low (void)
{
  TIM1_OC2Init(TIM1_OCMODE_PWM1,
	       TIM1_OUTPUTNSTATE_DISABLE,
  	       TIM1_OUTPUTNSTATE_DISABLE,
	       0,
	       TIM1_OCPOLARITY_HIGH,
	       TIM1_OCNPOLARITY_LOW,
	       TIM1_OCIDLESTATE_RESET,
	       TIM1_OCNIDLESTATE_SET);

  // disable pin
  GPIO_Init(PMW_PHASE_B_HIGH__PORT,
	    PMW_PHASE_B_HIGH__PIN,
	    GPIO_MODE_OUT_PP_LOW_FAST);

  // enable pin
  GPIO_Init(PMW_PHASE_B_LOW__PORT,
	    PMW_PHASE_B_LOW__PIN,
	    GPIO_MODE_OUT_PP_LOW_FAST);
}

void pwm_phase_c_disable (void)
{
  TIM1_OC1Init(TIM1_OCMODE_PWM1,
	       TIM1_OUTPUTNSTATE_DISABLE,
  	       TIM1_OUTPUTNSTATE_DISABLE,
	       0,
  	       TIM1_OCPOLARITY_HIGH,
  	       TIM1_OCNPOLARITY_LOW,
  	       TIM1_OCIDLESTATE_RESET,
  	       TIM1_OCNIDLESTATE_SET);

  // disable pin
  GPIO_Init(PMW_PHASE_C_HIGH__PORT,
	    PMW_PHASE_C_HIGH__PIN,
	    GPIO_MODE_OUT_PP_LOW_FAST);

  // disable pin
  GPIO_Init(PMW_PHASE_C_LOW__PORT,
	    PMW_PHASE_C_LOW__PIN,
	    GPIO_MODE_OUT_PP_HIGH_FAST);
}

void pwm_phase_c_enable_pwm (void)
{
  TIM1_OC1Init(TIM1_OCMODE_PWM1,
	       TIM1_OUTPUTSTATE_ENABLE,
	       TIM1_OUTPUTNSTATE_DISABLE,
	       ui8_duty_cycle,
	       TIM1_OCPOLARITY_HIGH,
	       TIM1_OCNPOLARITY_LOW,
	       TIM1_OCIDLESTATE_RESET,
	       TIM1_OCNIDLESTATE_SET);

  // disable pin
  GPIO_Init(PMW_PHASE_C_LOW__PORT,
	    PMW_PHASE_C_LOW__PIN,
	    GPIO_MODE_OUT_PP_HIGH_FAST);
}

void pwm_phase_c_enable_low (void)
{
  TIM1_OC1Init(TIM1_OCMODE_PWM1,
	       TIM1_OUTPUTNSTATE_DISABLE,
  	       TIM1_OUTPUTNSTATE_DISABLE,
	       0,
	       TIM1_OCPOLARITY_HIGH,
	       TIM1_OCNPOLARITY_LOW,
	       TIM1_OCIDLESTATE_RESET,
	       TIM1_OCNIDLESTATE_SET);

  // disable pin
  GPIO_Init(PMW_PHASE_C_HIGH__PORT,
	    PMW_PHASE_C_HIGH__PIN,
	    GPIO_MODE_OUT_PP_LOW_FAST);

  // enable pin
  GPIO_Init(PMW_PHASE_C_LOW__PORT,
	    PMW_PHASE_C_LOW__PIN,
	    GPIO_MODE_OUT_PP_LOW_FAST);
}

