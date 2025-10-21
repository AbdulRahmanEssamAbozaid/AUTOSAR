 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.c
 *
 * Description: Source file for TM4C123GH6PM Microcontroller - Port Driver.
 *              This file contains the implementation of functions to configure
 *              and control GPIO pins, including setting pin direction, mode,
 *              and initial values.
 *
 * Author: AbdulRahman Essam Abozaid
 ******************************************************************************/

#include "Port.h"
#include "tm4c123gh6pm_registers.h"

#if (PORT_DEV_ERROR_DETECT == STD_ON)

#include "Det.h"
/* AUTOSAR Version checking between Det and PORT Modules */
#if ((DET_AR_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 || (DET_AR_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 || (DET_AR_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Det.h does not match the expected version"
#endif

/* Software Version checking between Det.h and PORT.h files */
#if ((DET_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
 ||  (DET_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
 ||  (DET_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
#error "The SW version of PORT.h does not match the expected version"
#endif

#endif
/* Global variables */
volatile uint32 * PortGpio_Ptr = NULL_PTR;               /* Pointer to the required Port Registers base address */

STATIC const Port_Config * PortChannels = NULL_PTR;      /* Pointer to the configuration structure for Port pins */

STATIC uint8 Port_Status = PORT_NOT_INITIALIZED;         /* Status of the Port module */

STATIC boolean error = FALSE;                            /* Error flag */

STATIC uint8 i =0;                                        /* Loop counter */
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
void PORT_Init(const Port_ConfigType * ConfigPtr)
{
#if (PORT_DEV_ERROR_DETECT == STD_ON)
	/* check if the input configuration pointer is not a NULL_PTR */
	if (NULL_PTR == ConfigPtr)
	{
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID,
		     PORT_E_PARAM_CONFIG);
	}
	else
#endif
	{
		/*
		 * Set the module state to initialized and point to the Port configuration structure using a global pointer.
		 * This global pointer is used by other functions to read the Port configuration structures.
		 */
		Port_Status       = PORT_INITIALIZED;
		PortChannels = ConfigPtr->Pins; /* address of the first Channels structure --> Channels[0] */
    }

    if (error == FALSE)
    {
        for(i =0; i<= PORT_CONFIGURED_PINS; i++)
        {
            /* Identify the port base address */
            switch(PortChannels[i].port_num)
            {
                case  0: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
    	    	         break;
             	case  1: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
    	    	         break;
    	        case  2: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
    	    	         break;
    	        case  3: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
    	    	         break;
                case  4: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
    	    	         break;
                case  5: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
    	    	         break;
                default:
        #if (PORT_DEV_ERROR_DETECT == STD_ON)
                        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID, PORT_E_PARAM_INVALID_MODE);
        #endif            
                }
        /* Unlock special pins if necessary */
        if( ((PortChannels[i].port_num == 3) && (PortChannels[i].pin_num == 7)) 
            || ((PortChannels[i].port_num == 5) && (PortChannels[i].pin_num == 0)) ) /* PD7 or PF0 */
        {
            *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_LOCK_REG_OFFSET) = 0x4C4F434B;                     /* Unlock the GPIOCR register */   
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_COMMIT_REG_OFFSET) , PortChannels[i].pin_num);  /* Set the corresponding bit in GPIOCR register to allow changes on this pin */
        }
        else if( (PortChannels[i].port_num == 2) && (PortChannels[i].pin_num <= 3) ) /* PC0 to PC3 */
        {
            continue;
            /* Do Nothing ...  this is the JTAG pins */
        }
        else
        {
            /* Do Nothing ... No need to unlock the commit register for this pin */
        }
        /* Set pin direction and mode */
        PORT_SetDirection(PortChannels[i].pin_num , PortChannels[i].direction);
        Port_SetPinMode(PortChannels[i].pin_num , PortChannels[i].pin_mode);
    }
    }
}
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
void PORT_SetDirection(Port_Pin pin_num , Port_PinDirection dirction)
{
#if (PORT_DEV_ERROR_DETECT == STD_ON)
	/* check if the input configuration pointer is not a NULL_PTR */
	if (PORT_NOT_INITIALIZED == Port_Status)
	{
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, 
                        PORT_SET_PIN_DIRECTION_SID,
		                PORT_E_UNINIT);
        error = TRUE;
	}
	else
    {
        /* No Action Required */   
    }
    if (PORT_CONFIGURED_PINS <=  pin_num)
	{

		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
				PORT_SET_PIN_DIRECTION_SID, 
                PORT_E_PARAM_PINS);
		error = TRUE;
	}
	else
	{
		/* No Action Required */
	}
    if (  PortChannels[i].direction == INVALID)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
				PORT_SET_PIN_DIRECTION_SID, 
                PORT_E_DIRECTION_UNCHANGEABLE);
		error = TRUE;
    }
    else
	{
		/* No Action Required */
	}
#endif


    if( PortChannels[i].direction == OUTPUT)
    {
	    SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) ,  pin_num);               /* Set the corresponding bit in the GPIODIR register to configure it as output pin */
        
        if( PortChannels[i].initial_value == STD_HIGH)
        {
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET) ,  pin_num);          /* Set the corresponding bit in the GPIODATA register to provide initial value 1 */
        }
        else
        {
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET) ,  pin_num);        /* Clear the corresponding bit in the GPIODATA register to provide initial value 0 */
        }
    }
    else if( PortChannels[i].direction == INPUT)
    {
        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) ,  pin_num);             /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */
        
        if( PortChannels[i].resistor == PULL_UP)
        {
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET) ,  pin_num);       /* Set the corresponding bit in the GPIOPUR register to enable the internal pull up pin */
        }
        else if(  PortChannels[i].resistor == PULL_DOWN)
        {
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET) ,  pin_num);     /* Set the corresponding bit in the GPIOPDR register to enable the internal pull down pin */
        }
        else
        {
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET) ,  pin_num);     /* Clear the corresponding bit in the GPIOPUR register to disable the internal pull up pin */
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET) ,  pin_num);   /* Clear the corresponding bit in the GPIOPDR register to disable the internal pull down pin */
        }
    }
    else
    {
        /* Do Nothing */
    }
}



/************************************************************************************
* Service Name: Port_SetPinMode
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): port_num - Port number (0 to 5)
*                  pin_num - Pin number (0 to 7)
*                  pin_mode - Pin mode (GPIO_MODE, ADC_MODE, UART_MODE, etc.)
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to set the pin mode (GPIO, ADC, UART, CAN, SPI, I2C, PWM, USB, QEI).
************************************************************************************/
void Port_SetPinMode( Port_Pin pin_num, Port_PinMode pin_mode)
{
#if (PORT_DEV_ERROR_DETECT == STD_ON)
	/* check if the input configuration pointer is not a NULL_PTR */
	if (PORT_NOT_INITIALIZED == Port_Status)
	{
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, 
                        PORT_SET_PIN_MODE_SID,
		                PORT_E_UNINIT);
        error = TRUE;
	}
	else
    {
        /* No Action Required */   
    }

    if (PORT_CONFIGURED_PINS <= pin_num)
	{

		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
				PORT_SET_PIN_MODE_SID, PORT_E_PARAM_PINS);
		error = TRUE;
	}
	else
	{
		/* No Action Required */
	}
    if (pin_mode == INVALID_MODE )
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
				PORT_SET_PIN_MODE_SID, PORT_E_MODE_UNCHANGEABLE);
		error = TRUE;
    }
    else
	{
		/* No Action Required */
	}
#endif
    if(error == FALSE)
    {
        switch( pin_mode)
        {
            case GPIO_MODE:
                /* Setup the pin mode as GPIO */
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) ,  pin_num);      /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) ,  pin_num);             /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) ,  pin_num);         /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */      
                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << ( pin_num * 4)); /* Clear the PMCx bits */    
                break; 
            case ADC_MODE:
                /* Enable alternative function and configure for ADC mode */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) ,  pin_num);             /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET),  pin_num); /* Enable analog mode */
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) ,  pin_num);         /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */      
                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << ( pin_num * 4)); /* Clear the PMCx bits */         
                break;
            /*UART Pins in Tiva_C ==> PA0 - PA1
            * PB0 - PB1 - PC4 - PC5 - PC6 - PC7
            * PD4 - PD5 - PD6 - PD7
            * PE0 -  PE1 - PE4 - PE5*/
            case UART_MODE:  
                if(((  PortChannels->port_num == 0) && (( pin_num == 0) || ( pin_num == 1))) ||
                    ((  PortChannels->port_num == 1) && (( pin_num == 0) || ( pin_num == 1))) ||
                    ((  PortChannels->port_num == 2) && (( pin_num == 4) || ( pin_num == 5) || ( pin_num == 6) || ( pin_num == 7))) ||
                    ((  PortChannels->port_num == 3) && (( pin_num == 4) || ( pin_num == 5) || ( pin_num == 6) || ( pin_num == 7))) ||
                    ((  PortChannels->port_num == 4) && (( pin_num == 0) || ( pin_num == 1) || ( pin_num == 4) || ( pin_num == 5))))
                {
                    /* Enable alternate function */
                    SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET),  pin_num);
                    /* Set PMCx bits to UART function */
                    *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000E << ( pin_num * 4));
                    /* Enable Digital functionality */
                    SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET),  pin_num);
                }
                else if(((  PortChannels->port_num  == 2) && (( pin_num == 4) || ( pin_num == 5))))
                {
#ifdef U1
                    *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000D << (pin_num * 4));
#else 
                    *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000E << ( pin_num * 4));
#endif
                }
                else 
                {
                    /*No Action Required*/
                }
                break;        
            case CAN_MODE:  // CAN Pins in Tiva C ==> PA0 - PA1 - PB4 - PB5 - PE4 - PE5 - PF0 - PF3
                if(((PortChannels[i].port_num == 0) && ( pin_num == 0) || ( pin_num == 1))
                || ((PortChannels[i].port_num == 1) && ( pin_num == 4) || ( pin_num == 5))
                || ((PortChannels[i].port_num == 4) && ( pin_num == 4) || ( pin_num == 5)))
                {
                    SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET),  pin_num);
                    *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x00000007 << ( pin_num * 4));
                }
                else if ((PortChannels->port_num == 5) && ( pin_num == 0) || ( pin_num == 3))
                {
                    SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET),  pin_num);
                    *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000C << ( pin_num * 4));
                }
                else 
                {
                    /*No Action Required*/
                }
                break;
           /*SPI Pins in Tiva_C ==> PA2 - PA3 - PA4 - PA5
            * PB4 - PB5 - PB6 - PB7 - PD0 - PD1 - PD2 - PD3
            * PF0 - PF1 - PF2 - PF3 */                
            case SPI_MODE:  
                if((((PortChannels->port_num == 0) && ( pin_num == 2) || (( pin_num == 3) || ( pin_num == 4) || ( pin_num == 5))))
                || (((PortChannels->port_num == 1) && (( pin_num == 4) || ( pin_num == 5) || ( pin_num == 6) || ( pin_num == 7)))) 
                || ((PortChannels->port_num == 5) && (( pin_num == 0) || ( pin_num == 1) || ( pin_num == 2) || ( pin_num == 3))))
                {
                    SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET),  pin_num);
                    *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000D << ( pin_num * 4));
                }
                else if (((PortChannels->port_num == 3) && (( pin_num == 0) || ( pin_num == 1) || ( pin_num == 2) || ( pin_num == 3))))
                {
#ifdef  SSI3
                    SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET), pin_num);
                    *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000E << (pin_num * 4));
#else
                    SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET),  pin_num);
                    *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000D << ( pin_num * 4));
#endif
                }
                else
                {
                    /*No Action Required*/
                }
                break;
            case WATCHDOG_MODE:
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET),  pin_num);
                /* Configure the pin for Watchdog mode (PMCx = 0) */
                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << ( pin_num * 4));
               break;
            case PWM_MODE:   /*PWM Pins in Tiva_C ==> PB4 - PB5 - PB6 - PB7  - PC4 - PC5 - PD0 - PD1*/
                if((((PortChannels->port_num == 1) && ( pin_num == 4) || (( pin_num == 5) || ( pin_num == 6) || ( pin_num == 7))))
                || (((PortChannels->port_num == 2) && (( pin_num == 4) || ( pin_num == 5))))
                || ((PortChannels->port_num == 3) && (( pin_num == 0) || ( pin_num == 1))))
                {
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET),  pin_num);
                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000B << ( pin_num * 4));                        
                }
                else
                {
                    /*No Action Required*/
                }
                break;
            case I2C_MODE:
                if((((PortChannels->port_num == 0) &&  (( pin_num == 6) || ( pin_num == 7))))
                || (((PortChannels->port_num == 1) && ((  pin_num == 2) || ( pin_num == 3))))
                || ((PortChannels->port_num == 3) && ((   pin_num == 0) || ( pin_num == 1)))
                || ((PortChannels->port_num == 4) && ((   pin_num == 4) || ( pin_num == 5))))
                {
                    /* Enable alternative function and configure for I2C mode (PMCx = 3) */
                    SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET),  pin_num);
                    *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000C << ( pin_num * 4));
                }
                else 
                {
                    /* No Action Required */
                }
                break;
            case USB_MODE:
                /* Enable alternative function and configure for USB mode (PMCx = 8) */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET),  pin_num);
                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x00000007 << ( pin_num * 4));
                break;
            case QEI_MODE:
                /* Enable alternative function and configure for QEI mode (PMCx = 6) */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET),  pin_num);
                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x00000009 << ( pin_num * 4));
                break;
            default:
                /* Report an error for an invalid mode */
#if(PORT_DEV_ERROR_DETECT == STD_ON)
                Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID, PORT_E_PARAM_INVALID_MODE);
#endif
                return;
    }           

}

    /* Enable digital functionality for non-ADC modes */
    if ( pin_mode != ADC_MODE)
    {
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET),  pin_num); /* Enable digital functionality */
    }
    else
    {
        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET),  pin_num); /* Disable digital functionality for ADC mode */
    }
}
// WatchDog , GPIO , ADC , UART , SSI , I2C , CAN , USB , PWM , QEI 
