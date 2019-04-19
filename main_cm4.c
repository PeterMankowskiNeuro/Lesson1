/*************************************/
// My 1st GitHUB Project
/*************************************/

#include "project.h"
#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>
#include <limits.h>
#include "semphr.h"
#include "timers.h"

#define HEAP_SIZE_1 8*1024
#define COUNTER_BLOCK_TIME 0

/* Local task declaration */
void TaskLedGreen   ( void * pvParameters );
void TaskLedRed     ( void * pvParameters );
void MyTask3        ( void * pvParameters );
void ErrorTaskHandle( void);

TaskHandle_t    xHandle0;
TaskHandle_t    xHandle1;
TaskHandle_t    xHandle2;

/* Global Variables */
/********************/
uint32_t pinStateHigh = 0UL;
uint32_t pinStateLow  = 1UL;

int main(void)
{   
     /*************************************************************
    *          Enable global interrupts                         */
    __enable_irq();                                             
    /************************************************************/
    
    /************************************************************/
    BaseType_t      xReturned0;
    BaseType_t      xReturned1;
    BaseType_t      xReturned2;

    UART_1_Start();    
    
    xReturned0 = xTaskCreate(TaskLedGreen,  /* Function that implements the task. */
                "TaskLedGreen",             /* Text name for the task. */
                100,                        /* Stack size in words, not bytes. */
                ( void * ) 1,               /* Parameter passed into the task. */
                1,                          /* Priority at which the task is created. */
                &xHandle0);                 /* Optional: Used to pass out the created task's handle. */
        
    xReturned1 = xTaskCreate(TaskLedRed,     /* Function that implements the task. */
                "TaskLedRed",                /* Text name for the task. */
                200,                         /* Stack size in words, not bytes. */
                ( void * ) 2,                /* Parameter passed into the task. */
                1,                           /* Priority at which the task is created. */
                &xHandle1);                  /* Optional: Used to pass out the created task's handle. */
        
    xReturned2 = xTaskCreate(MyTask3,        /* Function that implements the task. */
                "Task3",                     /* Text name for the task. */
                200,                         /* Stack size in words, not bytes. */
                ( void * ) 3,                /* Parameter passed into the task. */
                2,                           /* Priority at which the task is created. */
                &xHandle2);                  /* Optional: Used to pass out the created task's handle. */
    
    /**************************************/
    if(
            pdPASS == xReturned0
         && pdPASS == xReturned1
         && pdPASS == xReturned2)
    {
        printf("All three xTasks created succesfully\r\n");   
    }
    
 if( uxTaskPriorityGet( xHandle0 ) != 1 ||
     uxTaskPriorityGet( xHandle1 ) != 1 ||
     uxTaskPriorityGet( xHandle2 ) != 2)
     {
         ErrorTaskHandle();
     }
    
    vTaskStartScheduler();
    
    for(;;)
    {
         //
    }
} 

/* Task GREEN LED */
void TaskLedGreen (void * pvParameters)
{
    /* The parameter value is expected to be 1 as 1 is passed in the
    pvParameters value in the call to xTaskCreate() below. */
    configASSERT( ( ( uint32_t ) pvParameters ) == 1 );
    for(;;)
    {
        /* Send a notification to prvTask2(), bringing it out of the Blocked
        state. */
        xTaskNotifyGive( xHandle1 );
        
        printf("GREEN LED \r\n");
        /*Cy_GPIO_Write(GREEN_PORT, GREEN_NUM,pinStateLow);
        vTaskDelay(400);
        Cy_GPIO_Write(GREEN_PORT, GREEN_NUM,pinStateHigh);
        vTaskDelay(400);
        */
        /* Block to wait for RED LED Task() to notify this task. */
        ulTaskNotifyTake ( pdTRUE, 1000 );
    }
}

/* Task RED LED */
void TaskLedRed (void * pvParameters)
{
    /* The parameter value is expected to be 1 as 1 is passed in the
    pvParameters value in the call to xTaskCreate() below. */
    configASSERT( ( ( uint32_t ) pvParameters ) == 2 );
    
    for(;;)
    {
        ulTaskNotifyTake ( pdTRUE, 1000 );
        
        printf("RED LED \r\n");
        /*Cy_GPIO_Write(RED_PORT, RED_NUM,pinStateHigh);
        vTaskDelay(399);
        Cy_GPIO_Write(RED_PORT, RED_NUM,pinStateLow);
        vTaskDelay(399);
        */
        //xTaskNotifyGive ( xHandle0 );
    }
}

/* Task3 */
void MyTask3 (void * pvParameters)
{    
    /* The parameter value is expected to be 1 as 1 is passed in the
    pvParameters value in the call to xTaskCreate() below. */
    configASSERT( ( ( uint32_t ) pvParameters ) == 3 );
    for(;;)
    {
        printf("MyTask3 \r\n");
        
        xTaskNotifyGive ( xHandle0 );
        
        /*Turn them both OFF */
        Cy_GPIO_Write(GREEN_PORT, GREEN_NUM, pinStateLow);
        Cy_GPIO_Write(RED_PORT, RED_NUM, pinStateLow);
        vTaskDelay(299);  
        
    }
}

void ErrorTaskHandle ()
{
    printf ("The task has changed its priority\r\n");   
}

/* [] END OF FILE */
