#include "Turn_On_Off_Delay.h"

#include <stddef.h>


/*============================================================================*/
/* Elements access */
/*============================================================================*/
#define My_Var_Attr ((Turn_On_Off_Delay_Var*)(Me->super.var_attr))
#define Me_Is_Output_On (Me->super.var_attr->Is_Output_On)
#define Me_Is_Input_On (My_Var_Attr->Is_Input_On)
#define Me_My_Timer (Me->super.My_Timer)
#define Me_Delay_Is_Up (Me->super.Delay_Is_Up)
#define Me_On_Delay_Duration (Me->super.Delay_Duration)
#define Me_Off_Delay_Duration (Me->Off_Delay_Duration)


/*============================================================================*/
/* Public methods */
/*============================================================================*/
static void Turn_On_Off_Delay__Set( const Turn_On_Off_Delay* Me )
{
    if( false==Me_Is_Input_On )
    {
        Triggered_Timer__Start(
            Me_My_Timer,
            Me_On_Delay_Duration );
        Me_Is_Input_On = true;
    }
    else
    { /* Input is true */
        if( true==Me_Is_Output_On )
        { /* input is already ON and output also */
            /* Cancel reset (eventually) */
            Triggered_Timer__Stop( Me_My_Timer );
        }
        else
        { /* input is already ON but output not yet */
            /* No effect */
        }
    }
}
/*----------------------------------------------------------------------------*/
static void Turn_On_Off_Delay__Reset( const Turn_On_Off_Delay* Me )
{
    if( true==Me_Is_Input_On )
    {
        Triggered_Timer__Start(
            Me_My_Timer,
            Me_Off_Delay_Duration );
        Me_Is_Input_On = false;
    }
    else
    { /* Input is false */
        if( false==Me_Is_Output_On )
        { /* input is already OFF and output also */ 
            /* Cancel set (eventually) */
            Triggered_Timer__Stop( Me_My_Timer );
        }
        else
        { /* input is already OFF and output not yet */ 
            /* No effect */
        }
    }
}


/*============================================================================*/
/* Received events */
/*============================================================================*/
static void Turn_On_Off_Delay__Timer_Is_Up( const Turn_On_Off_Delay* Me )
{
    Me_Is_Output_On = Me_Is_Input_On;
    if( Me_Delay_Is_Up != NULL )
    {
        Me_Delay_Is_Up();
    }
}


/*============================================================================*/
/* Virtual operations realization */
/*============================================================================*/
Delay_Virtual_Operations Turn_On_Off_Delay_Operations = {
    /* set */
    ( void (*) (const Delay*) )Turn_On_Off_Delay__Set,
    /* reset */
    ( void (*) (const Delay*) )Turn_On_Off_Delay__Reset,
    /* time_is_up */
    ( void (*) (const Delay*) )Turn_On_Off_Delay__Timer_Is_Up
};