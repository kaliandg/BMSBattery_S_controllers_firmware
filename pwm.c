/*
 * EGG OpenSource EBike firmware
 *
 * Copyright (C) Casainho, 2015, 2106, 2017.
 *
 * Released under the GPL License, Version 3
 */

#include <stdint.h>
#include <stdio.h>
#include "stm8s_gpio.h"
#include "stm8s_tim1.h"
#include "motor.h"
#include "gpio.h"
#include "motor.h"
#include "pwm.h"

#if (SVM_TABLE == SVM)
uint8_t ui16_svm_table [SVM_TABLE_LEN] =
{
    127	,
    133	,
    138	,
    144	,
    149	,
    154	,
    160	,
    165	,
    170	,
    176	,
    181	,
    186	,
    191	,
    197	,
    202	,
    207	,
    212	,
    217	,
    222	,
    227	,
    231	,
    236	,
    239	,
    240	,
    242	,
    243	,
    244	,
    245	,
    247	,
    248	,
    249	,
    250	,
    250	,
    251	,
    252	,
    253	,
    253	,
    254	,
    254	,
    254	,
    255	,
    255	,
    255	,
    255	,
    255	,
    255	,
    254	,
    254	,
    254	,
    253	,
    253	,
    252	,
    251	,
    251	,
    250	,
    249	,
    248	,
    247	,
    246	,
    245	,
    243	,
    242	,
    241	,
    239	,
    238	,
    239	,
    241	,
    242	,
    243	,
    245	,
    246	,
    247	,
    248	,
    249	,
    250	,
    251	,
    251	,
    252	,
    253	,
    253	,
    254	,
    254	,
    254	,
    255	,
    255	,
    255	,
    255	,
    255	,
    255	,
    254	,
    254	,
    254	,
    253	,
    253	,
    252	,
    251	,
    250	,
    250	,
    249	,
    248	,
    247	,
    245	,
    244	,
    243	,
    242	,
    240	,
    239	,
    236	,
    231	,
    227	,
    222	,
    217	,
    212	,
    207	,
    202	,
    197	,
    191	,
    186	,
    181	,
    176	,
    170	,
    165	,
    160	,
    154	,
    149	,
    144	,
    138	,
    133	,
    127	,
    122	,
    116	,
    111	,
    106	,
    100	,
    95	,
    89	,
    84	,
    79	,
    74	,
    68	,
    63	,
    58	,
    53	,
    48	,
    43	,
    38	,
    33	,
    28	,
    23	,
    18	,
    16	,
    14	,
    13	,
    12	,
    10	,
    9	,
    8	,
    7	,
    6	,
    5	,
    4	,
    3	,
    3	,
    2	,
    1	,
    1	,
    1	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    1	,
    1	,
    2	,
    2	,
    3	,
    4	,
    5	,
    6	,
    6	,
    8	,
    9	,
    10	,
    11	,
    12	,
    14	,
    15	,
    17	,
    15	,
    14	,
    12	,
    11	,
    10	,
    9	,
    8	,
    6	,
    6	,
    5	,
    4	,
    3	,
    2	,
    2	,
    1	,
    1	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    1	,
    1	,
    1	,
    2	,
    3	,
    3	,
    4	,
    5	,
    6	,
    7	,
    8	,
    9	,
    10	,
    12	,
    13	,
    14	,
    16	,
    18	,
    23	,
    28	,
    33	,
    38	,
    43	,
    48	,
    53	,
    58	,
    63	,
    68	,
    74	,
    79	,
    84	,
    89	,
    95	,
    100	,
    106	,
    111	,
    116	,
    122
};
#elif (SVM_TABLE == SINE_SVM_ORIGINAL)
uint16_t ui16_svm_table [SVM_TABLE_LEN] =
{
    0	,
    17	,
    34	,
    51	,
    69	,
    86	,
    103	,
    120	,
    136	,
    153	,
    170	,
    186	,
    203	,
    219	,
    235	,
    252	,
    267	,
    283	,
    299	,
    314	,
    330	,
    345	,
    359	,
    374	,
    388	,
    402	,
    416	,
    430	,
    443	,
    457	,
    469	,
    482	,
    494	,
    506	,
    518	,
    529	,
    540	,
    551	,
    561	,
    571	,
    581	,
    591	,
    600	,
    608	,
    616	,
    624	,
    632	,
    639	,
    646	,
    652	,
    658	,
    664	,
    669	,
    674	,
    678	,
    682	,
    686	,
    689	,
    691	,
    694	,
    696	,
    697	,
    698	,
    699	,
    699	,
    699	,
    698	,
    697	,
    696	,
    694	,
    691	,
    689	,
    686	,
    682	,
    678	,
    674	,
    669	,
    664	,
    658	,
    652	,
    646	,
    639	,
    632	,
    624	,
    616	,
    620	,
    628	,
    635	,
    642	,
    649	,
    655	,
    661	,
    666	,
    671	,
    676	,
    680	,
    684	,
    687	,
    690	,
    693	,
    695	,
    696	,
    698	,
    699	,
    699	,
    699	,
    699	,
    698	,
    696	,
    695	,
    693	,
    690	,
    687	,
    684	,
    680	,
    676	,
    671	,
    667	,
    661	,
    655	,
    649	,
    643	,
    636	,
    628	,
    621	,
    613	,
    604	,
    595	,
    586	,
    577	,
    567	,
    557	,
    546	,
    535	,
    524	,
    513	,
    501	,
    489	,
    476	,
    463	,
    450	,
    437	,
    424	,
    410	,
    396	,
    382	,
    367	,
    352	,
    338	,
    322	,
    307	,
    292	,
    276	,
    260	,
    244	,
    228	,
    212	,
    195	,
    179	,
    162	,
    145	,
    129	,
    112	,
    95	,
    78	,
    61	,
    43	,
    26	,
    9	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0
};
#elif (SVM_TABLE == SINE)
uint8_t ui16_svm_table [SVM_TABLE_LEN] =
{
    5	,
    12	,
    18	,
    24	,
    30	,
    37	,
    43	,
    49	,
    55	,
    61	,
    67	,
    73	,
    79	,
    85	,
    91	,
    97	,
    103	,
    108	,
    114	,
    120	,
    125	,
    131	,
    136	,
    141	,
    146	,
    151	,
    156	,
    161	,
    166	,
    171	,
    176	,
    180	,
    184	,
    189	,
    193	,
    197	,
    201	,
    205	,
    208	,
    212	,
    215	,
    219	,
    222	,
    225	,
    228	,
    231	,
    233	,
    236	,
    238	,
    240	,
    243	,
    244	,
    246	,
    248	,
    249	,
    251	,
    252	,
    253	,
    254	,
    255	,
    255	,
    256	,
    256	,
    256	,
    256	,
    256	,
    255	,
    255	,
    254	,
    253	,
    253	,
    251	,
    250	,
    249	,
    247	,
    246	,
    244	,
    242	,
    240	,
    237	,
    235	,
    232	,
    230	,
    227	,
    224	,
    221	,
    217	,
    214	,
    211	,
    207	,
    203	,
    199	,
    195	,
    191	,
    187	,
    183	,
    178	,
    174	,
    169	,
    164	,
    159	,
    154	,
    149	,
    144	,
    139	,
    134	,
    128	,
    123	,
    117	,
    112	,
    106	,
    100	,
    94	,
    89	,
    83	,
    77	,
    71	,
    65	,
    59	,
    53	,
    46	,
    40	,
    34	,
    28	,
    22	,
    15	,
    9	,
    3	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0	,
    0
};
#endif

uint8_t ui8_duty_cycle = 0;
uint8_t ui8_duty_cycle_target = 0;
uint16_t ui16_value_a;
uint16_t ui16_value_b;
uint16_t ui16_value_c;
uint32_t ui32_value;

void pwm_set_duty_cycle (uint8_t value)
{
  ui8_duty_cycle_target = value;
}

void pwm_init (void)
{
// TIM1 Peripheral Configuration
  TIM1_DeInit();

#if (SVM_TABLE == SVM)
  TIM1_TimeBaseInit(0, // TIM1_Prescaler = 0
		    TIM1_COUNTERMODE_CENTERALIGNED1,
		    (512 - 1), // clock = 16MHz; counter period = 1024; PWM freq = 16MHz / 1024 = 15.625kHz;
		    //(BUT PWM center aligned mode needs twice the frequency)
		    1); // will fire the TIM1_IT_UPDATE at every PWM period cycle
#elif (SVM_TABLE == SINE) || (SVM_TABLE == SINE_SVM_ORIGINAL)
  TIM1_TimeBaseInit(0, // TIM1_Prescaler = 0
		    TIM1_COUNTERMODE_UP,
		    (700 - 1), // clock = 16MHz; counter period = 1024; PWM freq = 16MHz / 700 = 22.857kHz;
		    0); // will fire the TIM1_IT_UPDATE at every PWM period
#endif


//#define DISABLE_PWM_CHANNELS_1_3

  TIM1_OC1Init(TIM1_OCMODE_PWM1,
#ifdef DISABLE_PWM_CHANNELS_1_3
	       TIM1_OUTPUTSTATE_DISABLE,
	       TIM1_OUTPUTNSTATE_DISABLE,
#else
	       TIM1_OUTPUTSTATE_ENABLE,
	       TIM1_OUTPUTNSTATE_ENABLE,
#endif
	       0, // initial duty_cycle value
	       TIM1_OCPOLARITY_HIGH,
	       TIM1_OCNPOLARITY_LOW,
	       TIM1_OCIDLESTATE_RESET,
	       TIM1_OCNIDLESTATE_SET);

  TIM1_OC2Init(TIM1_OCMODE_PWM1,
	       TIM1_OUTPUTSTATE_ENABLE,
	       TIM1_OUTPUTNSTATE_ENABLE,
	       0, // initial duty_cycle value
	       TIM1_OCPOLARITY_HIGH,
	       TIM1_OCNPOLARITY_LOW,
	       TIM1_OCIDLESTATE_RESET,
	       TIM1_OCNIDLESTATE_SET);

  TIM1_OC3Init(TIM1_OCMODE_PWM1,
#ifdef DISABLE_PWM_CHANNELS_1_3
	       TIM1_OUTPUTSTATE_DISABLE,
	       TIM1_OUTPUTNSTATE_DISABLE,
#else
	       TIM1_OUTPUTSTATE_ENABLE,
	       TIM1_OUTPUTNSTATE_ENABLE,
#endif
	       0, // initial duty_cycle value
	       TIM1_OCPOLARITY_HIGH,
	       TIM1_OCNPOLARITY_LOW,
	       TIM1_OCIDLESTATE_RESET,
	       TIM1_OCNIDLESTATE_SET);

  TIM1_OC1PreloadConfig (ENABLE);
  TIM1_OC2PreloadConfig (ENABLE);
  TIM1_OC3PreloadConfig (ENABLE);

  // break, dead time and lock configuration
  TIM1_BDTRConfig(TIM1_OSSISTATE_ENABLE,
		  TIM1_LOCKLEVEL_OFF,
		  // hardware nees a dead time of 1us
		  16, // DTG = 0; dead time in 62.5 ns steps; 1us/62.5ns = 16
		  TIM1_BREAK_DISABLE,
		  TIM1_BREAKPOLARITY_LOW,
		  TIM1_AUTOMATICOUTPUT_ENABLE);

  TIM1_ITConfig(TIM1_IT_UPDATE, ENABLE);

  TIM1_Cmd(ENABLE); // TIM1 counter enable
  TIM1_CtrlPWMOutputs(ENABLE); // main Output Enable
}

void pwm_duty_cycle_controller (void)
{
  // limit PWM increase/decrease rate --- comment from stancecoke: this part does just nothing? ui8_counter is never increased?!
  static uint8_t ui8_counter;

  if (ui8_motor_total_current_flag == 0)
  {
    if (ui8_counter++ > PWM_DUTY_CYCLE_CONTROLLER_COUNTER)
    {
      ui8_counter = 0;

      // increment or decrement duty_cycle
      if (ui8_duty_cycle_target > ui8_duty_cycle) { ui8_duty_cycle++; }
      else if (ui8_duty_cycle_target < ui8_duty_cycle) { ui8_duty_cycle--; }
    }
  }
  else
  {
    ui8_motor_total_current_flag = 0;
//    debug_pin_set ();
//    if (ui8_duty_cycle > 20)
    if (ui8_duty_cycle > 0)
    {
      ui8_duty_cycle--;
//      ui8_duty_cycle -= 20;
    }
  }

//#define DO_DUTY_CYCLE_RAMP 1
#if DO_DUTY_CYCLE_RAMP == 1
  pwm_apply_duty_cycle (ui8_duty_cycle);
#else
  pwm_apply_duty_cycle (ui8_duty_cycle_target);
#endif
}

void pwm_apply_duty_cycle (uint8_t ui8_duty_cycle_value)
{
#if (SVM_TABLE == SVM)
  static uint8_t ui8__duty_cycle;
  static uint8_t ui8_temp;

  ui8__duty_cycle = ui8_duty_cycle_value;

  // scale and apply _duty_cycle
  ui8_temp = ui16_svm_table[ui8_motor_rotor_position];
  if (ui8_temp > MIDDLE_PWM_VALUE_DUTY_CYCLE_MAX)
  {
    ui16_value = ((uint16_t) (ui8_temp - MIDDLE_PWM_VALUE_DUTY_CYCLE_MAX)) * ui8__duty_cycle;
    ui8_temp = (uint8_t) (ui16_value >> 8);
    ui8_value_a = MIDDLE_PWM_VALUE_DUTY_CYCLE_MAX + ui8_temp;
  }
  else
  {
    ui16_value = ((uint16_t) (MIDDLE_PWM_VALUE_DUTY_CYCLE_MAX - ui8_temp)) * ui8__duty_cycle;
    ui8_temp = (uint8_t) (ui16_value >> 8);
    ui8_value_a = MIDDLE_PWM_VALUE_DUTY_CYCLE_MAX - ui8_temp;
  }

  // add 120 degrees and limit
  ui8_temp = ui16_svm_table[(uint8_t) (ui8_motor_rotor_position + 85 /* 120º */)];
  if (ui8_temp > MIDDLE_PWM_VALUE_DUTY_CYCLE_MAX)
  {
    ui16_value = ((uint16_t) (ui8_temp - MIDDLE_PWM_VALUE_DUTY_CYCLE_MAX)) * ui8__duty_cycle;
    ui8_temp = (uint8_t) (ui16_value >> 8);
    ui8_value_b = MIDDLE_PWM_VALUE_DUTY_CYCLE_MAX + ui8_temp;
  }
  else
  {
    ui16_value = ((uint16_t) (MIDDLE_PWM_VALUE_DUTY_CYCLE_MAX - ui8_temp)) * ui8__duty_cycle;
    ui8_temp = (uint8_t) (ui16_value >> 8);
    ui8_value_b = MIDDLE_PWM_VALUE_DUTY_CYCLE_MAX - ui8_temp;
  }

  // subtract 120 degrees and limit
  ui8_temp = ui16_svm_table[(uint8_t) (ui8_motor_rotor_position + 171 /* 240º */)];
  if (ui8_temp > MIDDLE_PWM_VALUE_DUTY_CYCLE_MAX)
  {
    ui16_value = ((uint16_t) (ui8_temp - MIDDLE_PWM_VALUE_DUTY_CYCLE_MAX)) * ui8__duty_cycle;
    ui8_temp = (uint8_t) (ui16_value >> 8);
    ui8_value_c = MIDDLE_PWM_VALUE_DUTY_CYCLE_MAX + ui8_temp;
  }
  else
  {
    ui16_value = ((uint16_t) (MIDDLE_PWM_VALUE_DUTY_CYCLE_MAX - ui8_temp)) * ui8__duty_cycle;
    ui8_temp = (uint8_t) (ui16_value >> 8);
    ui8_value_c = MIDDLE_PWM_VALUE_DUTY_CYCLE_MAX - ui8_temp;
  }

  // set final duty_cycle value
  TIM1_SetCompare1((uint16_t) (ui8_value_a << 1));
  TIM1_SetCompare2((uint16_t) (ui8_value_c << 1));
  TIM1_SetCompare3((uint16_t) (ui8_value_b << 1));
#elif (SVM_TABLE == SINE) || (SVM_TABLE == SINE_SVM_ORIGINAL)
  // scale and apply _duty_cycle
  ui16_value_a = ui16_svm_table[ui8_motor_rotor_position];
  ui32_value = ui16_value_a * (uint32_t) (ui8_duty_cycle_value);
  ui16_value_a = ui32_value >> 8;

  // add 120 degrees and limit
  ui16_value_b = ui16_svm_table[(uint8_t) (ui8_motor_rotor_position + 85 /* 120º */)];
  ui32_value = ui16_value_b * (uint32_t) (ui8_duty_cycle_value);
  ui16_value_b = ui32_value >> 8;

  // subtract 120 degrees and limit
  ui16_value_c = ui16_svm_table[(uint8_t) (ui8_motor_rotor_position + 171 /* 240º */)];
  ui32_value = ui16_value_c * (uint32_t) (ui8_duty_cycle_value);
  ui16_value_c = ui32_value >> 8;

  // set final duty_cycle value
  TIM1_SetCompare1(ui16_value_a);
  TIM1_SetCompare2(ui16_value_c);
  TIM1_SetCompare3(ui16_value_b);
#endif
}

