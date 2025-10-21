/******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port_PBcfg.c
 *
 * Description: Post-Build Configuration Source File for the Port Driver.
 *              This file contains the configuration structure for the Port module,
 *              which is used to initialize the GPIO pins of the TM4C123GH6PM microcontroller.
 *
 * Author: AbdulRahman Essam Abozaid 
 ******************************************************************************/


#define PORT_PBCFG_SW_MAJOR_VERSION           (1U)    /* Major version of the module */ 
#define PORT_PBCFG_SW_MINOR_VERSION           (0U)    /* Minor version of the module */
#define PORT_PBCFG_SW_PATCH_VERSION           (0U)    /* Patch version of the module */

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_PBCFG_AR_RELEASE_MAJOR_VERSION   (4U)    /* AUTOSAR major version */
#define PORT_PBCFG_AR_RELEASE_MINOR_VERSION   (0U)    /* AUTOSAR minor version */
#define PORT_PBCFG_AR_RELEASE_PATCH_VERSION   (3U)    /* AUTOSAR patch version */

#include "Port.h"
#include "Port_Cfg.h"

/* AUTOSAR Version checking between Port_PBcfg.c and Port.h files */
#if ((PORT_PBCFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (PORT_PBCFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (PORT_PBCFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of PBcfg.c does not match the expected version"
#endif

/* Software Version checking between Port_PBcfg.c and Port.h files */
#if ((PORT_PBCFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
 ||  (PORT_PBCFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
 ||  (PORT_PBCFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
  #error "The SW version of PBcfg.c does not match the expected version"
#endif

/* 
 * PB (Post-Build) structure used with Port_Init API.
 * This structure contains the configuration for all GPIO pins.
 * Each pin is configured with the following parameters:
 *   - port_num: Port number (0 to 5)
 *   - pin_num: Pin number (0 to 7)
 *   - direction: Pin direction (INPUT or OUTPUT)
 *   - resistor: Internal resistor configuration (OFF, PULL_UP, or PULL_DOWN)
 *   - initial_value: Initial value for output pins (STD_HIGH or STD_LOW)
 *   - pin_mode: Pin mode (e.g., GPIO_MODE, ADC_MODE, etc.)
 */
const Port_ConfigType Port_PinConfig = {
                                        /* Port A Configuration */
                                        0,0,OUTPUT,OFF,STD_HIGH,GPIO_MODE,
                                        0,1,INPUT,PULL_UP,STD_HIGH,GPIO_MODE,
                                        0,2,INPUT,PULL_UP,STD_HIGH,GPIO_MODE,
                                        0,3,INPUT,PULL_UP,STD_HIGH,GPIO_MODE,
                                        0,4,INPUT,PULL_UP,STD_HIGH,GPIO_MODE,
                                        0,5,INPUT,PULL_UP,STD_HIGH,GPIO_MODE,
                                        0,6,INPUT,PULL_UP,STD_HIGH,GPIO_MODE,
                                        0,7,INPUT,PULL_UP,STD_HIGH,GPIO_MODE,
                                        /* Port B Configuration */
                                        1,0,OUTPUT,OFF,STD_HIGH,GPIO_MODE,
                                        1,1,INPUT,PULL_UP,STD_HIGH,GPIO_MODE,
                                        1,2,INPUT,PULL_UP,STD_HIGH,GPIO_MODE,
                                        1,3,INPUT,PULL_UP,STD_HIGH,GPIO_MODE,
                                        1,4,INPUT,PULL_UP,STD_HIGH,GPIO_MODE,
                                        1,5,INPUT,PULL_UP,STD_HIGH,GPIO_MODE,
                                        1,6,INPUT,PULL_UP,STD_HIGH,GPIO_MODE,
                                        1,7,INPUT,PULL_UP,STD_HIGH,GPIO_MODE,
                                        /* Port C Configuration */
                                        2,0,OUTPUT,OFF,STD_HIGH,GPIO_MODE,
                                        2,1,INPUT,PULL_UP,STD_HIGH,GPIO_MODE,
                                        2,2,INPUT,PULL_UP,STD_HIGH,GPIO_MODE,
                                        2,3,INPUT,PULL_UP,STD_HIGH,GPIO_MODE,
                                        2,4,INPUT,PULL_UP,STD_HIGH,GPIO_MODE,
                                        2,5,INPUT,PULL_UP,STD_HIGH,GPIO_MODE,
                                        2,6,INPUT,PULL_UP,STD_HIGH,GPIO_MODE,
                                        2,7,INPUT,PULL_UP,STD_HIGH,GPIO_MODE,
                                        /* Port D Configuration */
                                        3,0,OUTPUT,OFF,STD_HIGH,GPIO_MODE,
                                        3,1,INPUT,PULL_UP,STD_HIGH,GPIO_MODE,
                                        3,2,INPUT,PULL_UP,STD_HIGH,GPIO_MODE,
                                        3,3,INPUT,PULL_UP,STD_HIGH,GPIO_MODE,
                                        3,4,INPUT,PULL_UP,STD_HIGH,GPIO_MODE,
                                        3,5,INPUT,PULL_UP,STD_HIGH,GPIO_MODE,
                                        3,6,INPUT,PULL_UP,STD_HIGH,GPIO_MODE,
                                        3,7,INPUT,PULL_UP,STD_HIGH,GPIO_MODE,
                                        /* Port E Configuration */
                                        4,0,OUTPUT,OFF,STD_HIGH,GPIO_MODE,
                                        4,1,INPUT,PULL_UP,STD_HIGH,GPIO_MODE,
                                        4,2,INPUT,PULL_UP,STD_HIGH,GPIO_MODE,
                                        4,3,INPUT,PULL_UP,STD_HIGH,GPIO_MODE,
                                        4,4,INPUT,PULL_UP,STD_HIGH,GPIO_MODE,
                                        4,5,INPUT,PULL_UP,STD_HIGH,GPIO_MODE,
                                        /* Port F Configuration */
                                        5,0,OUTPUT,OFF,STD_HIGH,GPIO_MODE,
                                        5,1,OUTPUT,OFF,STD_LOW,GPIO_MODE,
                                        5,2,INPUT,OFF,STD_LOW,GPIO_MODE,
                                        5,3,INPUT,OFF,STD_LOW,GPIO_MODE,
                                        5,4,INPUT,PULL_UP,STD_HIGH,GPIO_MODE                                    
};

