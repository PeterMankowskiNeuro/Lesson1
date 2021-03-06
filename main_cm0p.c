/*******************************************************************************
* My 1st GitHUB Project
* Adding Header notes
* Final edit goes here
*
* File Name: main_cm0p.c
*
* Version: 1.20
*
* Description:
*   This is source code for the PSoC 6 MCU with BLE Find Me code example.
*
* Note:
*
* Owners:
*   peter@novelaneuro.com

********************************************************************************
* Copyright 2019, Novela Neuro.  All rights reserved.
*
*******************************************************************************/

#include "project.h"
#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>

int main(void)
{   
    __enable_irq(); /* Enable global interrupts. */
    
    
    Cy_SysEnableCM4(CY_CORTEX_M4_APPL_ADDR);
   
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    
    for(;;)
    {
        //       
    }
}

/* [] END OF FILE */
