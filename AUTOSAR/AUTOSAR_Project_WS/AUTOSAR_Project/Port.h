/******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.h
 *
 * Description: Header file for TM4C123GH6PM Microcontroller - Port Driver.
 *              This file contains definitions, data types, and function prototypes
 *              for configuring and controlling GPIO pins.
 *
 * Author: AbdulRahman Essam Abozaid 
 ******************************************************************************/

#ifndef PORT_H
#define PORT_H

#include "Std_Types.h"
/*Type definition for Port_PinType used by the PORT APIs */
typedef uint8 Port_Pin;                                 /* Represents the pin number (0 to 7) within a port */
/* Id for the company in the AUTOSAR */
#define PORT_VENDOR_ID    (1000U)                       /* Example: Vendor ID for the module */
/* PORT Module Id */
#define PORT_MODULE_ID    (120U)                        /* Module ID for the Port driver */
/* PORT Instance Id */
#define PORT_INSTANCE_ID  (0U)                          /* Instance ID for the Port driver */

/*
 * Module Version 1.0.0
 */
#define PORT_SW_MAJOR_VERSION           (1U)            /* Major version of the module */
#define PORT_SW_MINOR_VERSION           (0U)            /* Minor version of the module */
#define PORT_SW_PATCH_VERSION           (0U)            /* Patch version of the module */

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_AR_RELEASE_MAJOR_VERSION   (4U)            /* AUTOSAR major version */
#define PORT_AR_RELEASE_MINOR_VERSION   (0U)            /* AUTOSAR minor version */
#define PORT_AR_RELEASE_PATCH_VERSION   (3U)            /* AUTOSAR patch version */

#include "Common_Macros.h"
#include "Std_Types.h"

/* AUTOSAR checking between Std Types and PORT Modules */
#if ((STD_TYPES_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Std_Types.h does not match the expected version"
#endif

/* PORT Pre-Compile Configuration Header file */
#include "Port_Cfg.h"

/* AUTOSAR Version checking between PORT_Cfg.h and PORT.h files */
#if ((PORT_CFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of PORT_Cfg.h does not match the expected version"
#endif

/* Software Version checking between PORT_Cfg.h and PORT.h files */
#if ((PORT_CFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
 ||  (PORT_CFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
 ||  (PORT_CFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
  #error "The SW version of PORT_Cfg.h does not match the expected version"
#endif

/*
 * Macros for PORT Statu
 */
#define PORT_INITIALIZED                (1U)                     /* Module is initialized */
#define PORT_NOT_INITIALIZED            (0U)                     /* Module is not initialized */

/* Service ID for Port_SetPinDirection*/
#define PORT_SET_PIN_DIRECTION_SID          (uint8)0x01          /* Service ID for setting pin direction */
/* Service ID for Port_Init */
#define PORT_INIT_SID                       (uint8)0x00          /* Service ID for initializing the Port module */
/* Service ID for Port_SetPinMode */
#define PORT_SET_PIN_MODE_SID               (uint8)0x04           /* Service ID for setting pin mode */   

/*******************************************************************************
 *                      DET Error Codes                                        *
 *******************************************************************************/
/* DET code to report Invalid Mode */
#define PORT_E_PARAM_PINS                (uint8)0x0A                 /* Invalid pin number */

/*DET code to report Port Pin not configured as changeable*/
#define PORT_E_DIRECTION_UNCHANGEABLE    (uint8)0x0B                 /* Pin direction cannot be changed */

/*DET code to report API Port_SetPinMode service called when mode is unchangeable.*/
#define PORT_E_PARAM_INVALID_MODE        (uint8)0x0D                 /* Invalid pin mode */

/* PORT_Init API service called with NULL pointer parameter */
#define PORT_E_PARAM_CONFIG              (uint8)0x0C                 /* Invalid configuration pointer */

/*DET code to report API Port_SetPinMode service called when mode is unchangeable.*/
#define PORT_E_MODE_UNCHANGEABLE         (uint8)0x0E                 /* Pin mode cannot be changed */

/*DET code to report API service called without module initialization*/
#define PORT_E_UNINIT                    (uint8)0x0F                  /* Module not initialized */

/*DET code to report APIs called with a Null Pointer*/  
#define PORT_E_PARAM_POINTER             (uint8)0x10                  /* Null pointer passed to an API */

/*******************************************************************************
 *                              Module Definitions                             *
 *******************************************************************************/

/* GPIO Registers base addresses */
#define GPIO_PORTA_BASE_ADDRESS           0x40004000                    /* Base address for GPIO Port A */
#define GPIO_PORTB_BASE_ADDRESS           0x40005000                    /* Base address for GPIO Port B */
#define GPIO_PORTC_BASE_ADDRESS           0x40006000                    /* Base address for GPIO Port C */
#define GPIO_PORTD_BASE_ADDRESS           0x40007000                    /* Base address for GPIO Port D */
#define GPIO_PORTE_BASE_ADDRESS           0x40024000                    /* Base address for GPIO Port E */
#define GPIO_PORTF_BASE_ADDRESS           0x40025000                    /* Base address for GPIO Port F */

/* GPIO Registers offset addresses */
#define PORT_DATA_REG_OFFSET              0x3FC
#define PORT_DIR_REG_OFFSET               0x400
#define PORT_ALT_FUNC_REG_OFFSET          0x420
#define PORT_PULL_UP_REG_OFFSET           0x510
#define PORT_PULL_DOWN_REG_OFFSET         0x514
#define PORT_DIGITAL_ENABLE_REG_OFFSET    0x51C
#define PORT_LOCK_REG_OFFSET              0x520
#define PORT_COMMIT_REG_OFFSET            0x524
#define PORT_ANALOG_MODE_SEL_REG_OFFSET   0x528
#define PORT_CTL_REG_OFFSET               0x52C

/* UART Registers based Addresses */
#define UART0                            0x4000C000
#define UART1                            0x4000D000
#define UART2                            0x4000E000
#define UART3                            0x4000F000
#define UART4                            0x40010000
#define UART5                            0x40011000
#define UART6                            0x40012000
#define UART7                            0x40013000

/* UART Registers offset addresses */
#define UART_RSR_REG                     0x004          
#define UART_ECR_REG                     0x004          
#define UART_FR_REG                      0x018             
#define UART_ILPR_REG                    0x020         
#define UART_IBRD_REG                    0x028      
#define UART_FBRD_REG                    0x02C      
#define UART_LCRH_REG                    0x030      
#define UART_CTL_REG                     0x034      
#define UART_IFLS_REG                    0x038      
#define UART_IM_REG                      0x03C      
#define UART_RIS_REG                     0x03C      
#define UART_MIS_REG                     0x040      
#define UART_ICR_REG                     0x044      
#define UART_DMACTL_REG                  0x048      
#define UART_9BITADDR_REG                0x0A4      
#define UART_9BITAMASK_REG               0x0A8     
#define UART_PP_REG                      0xFC0      
#define UART_CC_REG                      0xFC8      


/*******************************************************************************
 *                              Module Data Types                              *
 *******************************************************************************/

/* Description: Enum to hold PIN direction */
typedef enum
{
    INPUT,OUTPUT,INVALID
}Port_PinDirection;

/* Description: Enum to hold internal resistor type for PIN */
typedef enum
{
    OFF,PULL_UP,PULL_DOWN
}Port_InternalResistor;

/* Description: Enum to hold pin mode */
typedef enum
{
    GPIO_MODE,          /* GPIO mode */
    ADC_MODE,           /* Analog-to-Digital Converter mode */
    UART_MODE,          /* UART mode */
    CAN_MODE,           /* CAN mode */
    SPI_MODE,           /* SPI mode */
    I2C_MODE,           /* I2C mode */
    PWM_MODE,           /* PWM mode */
    USB_MODE,           /* USB mode */
    QEI_MODE,           /* Quadrature Encoder Interface mode */
    WATCHDOG_MODE,      /* Watchdog mode */
    INVALID_MODE        /* Invalid mode */
} Port_PinMode;

/* Description: Structure to configure each individual PIN:
 *	1. the PORT Which the pin belongs to. 0, 1, 2, 3, 4 or 5
 *	2. the number of the pin in the PORT.
 *      3. the direction of pin --> INPUT or OUTPUT
 *      4. the internal resistor --> Disable, Pull up or Pull down
 * 5. the Initial value --> STD_HIGH , STD_LOW
 * 6. the Pin Mode  --> Pin mode (e.g., GPIO, ADC, etc.) 
 */
typedef struct 
{
    uint8 port_num;                     /* Port number (0 to 5) */
    uint8 pin_num;                      /* Pin number (0 to 7) */
    Port_PinDirection direction;        /* Pin direction (INPUT or OUTPUT) */
    Port_InternalResistor resistor;     /* Internal resistor configuration */
    uint8 initial_value;                /* Initial value for output pins */
    Port_PinMode pin_mode;              /* Pin mode (e.g., GPIO, ADC, etc.) */
}Port_Config;

/* Data Structure required for initializing the Dio Driver */
typedef struct
{
	Port_Config Pins[PORT_CONFIGURED_PINS];          /* Array of pin configurations */
} Port_ConfigType;

/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/
/************************************************************************************
* Service Name: PORT_Init
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): ConfigPtr - Pointer to the configuration structure for Port pins
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Initializes the Port module based on the provided configuration.
*              This function sets the direction, mode, and initial value of each pin.
************************************************************************************/
 void PORT_Init(const Port_ConfigType * ConfigPtr);
/************************************************************************************
* Service Name: Port_SetPinMode
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): port_num - Port number (0 to 5)
*                  pin_num - Pin number (0 to 7)
*                  pin_mode - Pin mode (GPIO_MODE or ALT_FUNC_MODE)
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to set the pin mode (GPIO or Alternate Function).
************************************************************************************/
void Port_SetPinMode( Port_Pin pin_num , Port_PinMode pin_mode);
/************************************************************************************
* Service Name: PORT_SetDirection
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): pin_num - Pin number (0 to 7)
*                  direction - Pin direction (OUTPUT, INPUT)
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Sets the direction of a specific pin (INPUT or OUTPUT).
************************************************************************************/
void PORT_SetDirection(Port_Pin pin_num , Port_PinDirection dirction);

#endif /* PORT_H */
