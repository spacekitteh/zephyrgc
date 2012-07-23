/*
 * File: Main.cpp
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

#include "Main.h"
#include "Main_private.h"

/*
 * This function updates continuous states using the ODE4 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si , RT_MODEL *const
  rtM, BlockIO *rtB, D_Work *rtDWork)
{
  time_T t = rtsiGetT(si);
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE4_IntgData *id = (ODE4_IntgData *)rtsiGetSolverData(si);
  real_T *y = id->y;
  real_T *f0 = id->f[0];
  real_T *f1 = id->f[1];
  real_T *f2 = id->f[2];
  real_T *f3 = id->f[3];
  real_T temp;
  int_T i;
  int_T nXc = 3;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  Main_derivatives(rtM, rtB);

  /* f1 = f(t + (h/2), y + (h/2)*f0) */
  temp = 0.5 * h;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (temp*f0[i]);
  }

  rtsiSetT(si, t + temp);
  rtsiSetdX(si, f1);
  Main_output(rtM, rtB, rtDWork);
  Main_derivatives(rtM, rtB);

  /* f2 = f(t + (h/2), y + (h/2)*f1) */
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (temp*f1[i]);
  }

  rtsiSetdX(si, f2);
  Main_output(rtM, rtB, rtDWork);
  Main_derivatives(rtM, rtB);

  /* f3 = f(t + h, y + h*f2) */
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (h*f2[i]);
  }

  rtsiSetT(si, tnew);
  rtsiSetdX(si, f3);
  Main_output(rtM, rtB, rtDWork);
  Main_derivatives(rtM, rtB);

  /* tnew = t + h
     ynew = y + (h/6)*(f0 + 2*f1 + 2*f2 + 2*f3) */
  temp = h / 6.0;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + temp*(f0[i] + 2.0*f1[i] + 2.0*f2[i] + f3[i]);
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

real_T rt_urand_Upu32_Yd_f_pw_snf(uint32_T *u)
{
  uint32_T lo;
  uint32_T hi;

  /* Uniform random number generator (random number between 0 and 1)

     #define IA      16807                      magic multiplier = 7^5
     #define IM      2147483647                 modulus = 2^31-1
     #define IQ      127773                     IM div IA
     #define IR      2836                       IM modulo IA
     #define S       4.656612875245797e-10      reciprocal of 2^31-1
     test = IA * (seed % IQ) - IR * (seed/IQ)
     seed = test < 0 ? (test + IM) : test
     return (seed*S)
   */
  lo = *u % 127773U * 16807U;
  hi = *u / 127773U * 2836U;
  if (lo < hi) {
    *u = 2147483647U - (hi - lo);
  } else {
    *u = lo - hi;
  }

  return (real_T)*u * 4.6566128752457969E-10;
}

real_T rt_nrand_Upu32_Yd_f_pw_snf(uint32_T *u)
{
  real_T sr;
  real_T si;

  /* Normal (Gaussian) random number generator */
  do {
    sr = 2.0 * rt_urand_Upu32_Yd_f_pw_snf(u) - 1.0;
    si = 2.0 * rt_urand_Upu32_Yd_f_pw_snf(u) - 1.0;
    si = sr * sr + si * si;
  } while (si > 1.0);

  return sqrt(-2.0 * log(si) / si) * sr;
}

/* Model output function */
void Main_output(RT_MODEL *const rtM, BlockIO *rtB, D_Work *rtDWork)
{
  if (rtmIsMajorTimeStep(rtM)) {
    /* set solver stop time */
    rtsiSetSolverStopTime(&rtM->solverInfo,((rtM->Timing.clockTick0+1)*
      rtM->Timing.stepSize0));
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(rtM)) {
    rtM->Timing.t[0] = rtsiGetT(&rtM->solverInfo);
  }

  if (rtmIsMajorTimeStep(rtM)) {
    /* Gain: '<S1>/Output' incorporates:
     *  RandomNumber: '<S1>/White Noise'
     */
    rtB->Output[0] = rtDWork->NextOutput;
    rtB->Output[1] = rtDWork->NextOutput;
    rtB->Output[2] = rtDWork->NextOutput;
  }
}

/* Model update function */
void Main_update(RT_MODEL *const rtM, BlockIO *rtB, D_Work *rtDWork)
{
  if (rtmIsMajorTimeStep(rtM)) {
    /* Update for RandomNumber: '<S1>/White Noise' */
    rtDWork->NextOutput = rt_nrand_Upu32_Yd_f_pw_snf(&rtDWork->RandSeed);
  }

  if (rtmIsMajorTimeStep(rtM)) {
    rt_ertODEUpdateContinuousStates(&rtM->solverInfo, rtM, rtB, rtDWork);
  }

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   */
  ++rtM->Timing.clockTick0;
  rtM->Timing.t[0] = rtsiGetSolverStopTime(&rtM->solverInfo);

  {
    /* Update absolute timer for sample time: [0.1s, 0.0s] */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The resolution of this integer timer is 0.1, which is the step size
     * of the task. Size of "clockTick1" ensures timer will not overflow during the
     * application lifespan selected.
     */
    rtM->Timing.clockTick1++;
  }
}

/* Derivatives for root system: '<Root>' */
void Main_derivatives(RT_MODEL *const rtM, BlockIO *rtB)
{
  StateDerivatives *_rtXdot;
  _rtXdot = ((StateDerivatives *) rtM->ModelData.derivs);

  /* Derivatives for Integrator: '<Root>/Integrator' */
  _rtXdot->Integrator_CSTATE[0] = rtB->Output[0];
  _rtXdot->Integrator_CSTATE[1] = rtB->Output[1];
  _rtXdot->Integrator_CSTATE[2] = rtB->Output[2];
}

/* Model initialize function */
void Main_initialize(RT_MODEL *const rtM, BlockIO *rtB, D_Work *rtDWork,
                     ContinuousStates *rtX)
{
  /* Registration code */

  /* initialize real-time model */
  (void) memset((void *)rtM, 0,
                sizeof(RT_MODEL));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&rtM->solverInfo, &rtM->Timing.simTimeStep);
    rtsiSetTPtr(&rtM->solverInfo, &rtmGetTPtr(rtM));
    rtsiSetStepSizePtr(&rtM->solverInfo, &rtM->Timing.stepSize0);
    rtsiSetdXPtr(&rtM->solverInfo, &rtM->ModelData.derivs);
    rtsiSetContStatesPtr(&rtM->solverInfo, &rtM->ModelData.contStates);
    rtsiSetNumContStatesPtr(&rtM->solverInfo, &rtM->Sizes.numContStates);
    rtsiSetErrorStatusPtr(&rtM->solverInfo, ((const char_T **)
      (&rtmGetErrorStatus(rtM))));
    rtsiSetRTModelPtr(&rtM->solverInfo, rtM);
  }

  rtsiSetSimTimeStep(&rtM->solverInfo, MAJOR_TIME_STEP);
  rtM->ModelData.intgData.y = rtM->ModelData.odeY;
  rtM->ModelData.intgData.f[0] = rtM->ModelData.odeF[0];
  rtM->ModelData.intgData.f[1] = rtM->ModelData.odeF[1];
  rtM->ModelData.intgData.f[2] = rtM->ModelData.odeF[2];
  rtM->ModelData.intgData.f[3] = rtM->ModelData.odeF[3];
  rtM->ModelData.contStates = ((real_T *) rtX);
  rtsiSetSolverData(&rtM->solverInfo, (void *)&rtM->ModelData.intgData);
  rtsiSetSolverName(&rtM->solverInfo,"ode4");
  rtmSetTPtr(rtM, &rtM->Timing.tArray[0]);
  rtM->Timing.stepSize0 = 0.1;

  /* block I/O */
  (void) memset(((void *) rtB), 0,
                sizeof(BlockIO));

  /* states (continuous) */
  {
    (void) memset((void *)rtX, 0,
                  sizeof(ContinuousStates));
  }

  /* states (dwork) */
  (void) memset((void *)rtDWork, 0,
                sizeof(D_Work));

  /* Start for RandomNumber: '<S1>/White Noise' */
  rtDWork->RandSeed = 1529675776U;
  rtDWork->NextOutput = rt_nrand_Upu32_Yd_f_pw_snf(&rtDWork->RandSeed);

  /* InitializeConditions for Integrator: '<Root>/Integrator' */
  rtX->Integrator_CSTATE[0] = 0.0;
  rtX->Integrator_CSTATE[1] = 0.0;
  rtX->Integrator_CSTATE[2] = 0.0;
}

/* Model terminate function */
void Main_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
