/*
 * File: ert_main.cpp
 *
 * Code generated for Simulink model 'Main'.
 *
 * Model version                  : 1.4
 * Simulink Coder version         : 8.2 (R2012a) 29-Dec-2011
 * TLC version                    : 8.2 (Dec 29 2011)
 * C/C++ source code generated on : Mon Jul 09 13:23:50 2012
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARMCortex
 * Code generation objective: Execution efficiency
 * Validation result: Not run
 */

#include <stdio.h>                     /* This ert_main.c example uses printf/fflush */
#include "Main.h"                      /* Model's header file */
#include "rtwtypes.h"                  /* MathWorks types */

static RT_MODEL rtM_;
static RT_MODEL *const rtM = &rtM_;    /* Real-time model */
static BlockIO rtB;                    /* Observable signals */
static D_Work rtDWork;                 /* Observable states */
static ContinuousStates rtX;           /* Observable continuous states */

/*
 * Associating rt_OneStep with a real-time clock or interrupt service routine
 * is what makes the generated code "real-time".  The function rt_OneStep is
 * always associated with the base rate of the model.  Subrates are managed
 * by the base rate from inside the generated code.  Enabling/disabling
 * interrupts and floating point context switches are target specific.  This
 * example code indicates where these should take place relative to executing
 * the generated code step function.  Overrun behavior should be tailored to
 * your application needs.  This example simply sets an error status in the
 * real-time model and returns from rt_OneStep.
 */
void rt_OneStep(RT_MODEL *const rtM);
void rt_OneStep(RT_MODEL *const rtM)
{
  static boolean_T OverrunFlag = FALSE;

  /* Disable interrupts here */

  /* Check for overrun */
  if (OverrunFlag) {
    rtmSetErrorStatus(rtM, "Overrun");
    return;
  }

  OverrunFlag = TRUE;

  /* Save FPU context here (if necessary) */
  /* Re-enable timer or interrupt here */
  /* Set model inputs here */

  /* Step the model for base rate */
  Main_output(rtM, &rtB, &rtDWork);

  /* Get model outputs here */
  Main_update(rtM, &rtB, &rtDWork);

  /* Indicate task complete */
  OverrunFlag = FALSE;

  /* Disable interrupts here */
  /* Restore FPU context here (if necessary) */
  /* Enable interrupts here */
}

/*
 * The example "main" function illustrates what is required by your
 * application code to initialize, execute, and terminate the generated code.
 * Attaching rt_OneStep to a real-time clock is target specific.  This example
 * illustates how you do this relative to initializing the model.
 */
int_T main(int_T argc, const char_T *argv[]);
int_T main(int_T argc, const char_T *argv[])
{
  /* Initialize model */
  Main_initialize(rtM, &rtB, &rtDWork, &rtX);

  /* Simulating the model step behavior (in non real-time) to
   *  simulate model behavior at stop time.
   */
  while ((rtmGetErrorStatus(rtM) == (NULL)) && !rtmGetStopRequested(rtM)) {
    rt_OneStep(rtM);
  }

  /* Disable rt_OneStep() here */

  /* Terminate model */
  Main_terminate();
  return 0;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
