/*
 * File: Main.h
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

#ifndef RTW_HEADER_Main_h_
#define RTW_HEADER_Main_h_
#ifndef Main_COMMON_INCLUDES_
# define Main_COMMON_INCLUDES_
#include <math.h>
#include <string.h>
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                                 /* Main_COMMON_INCLUDES_ */

#include "Main_types.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetStopRequested
# define rtmGetStopRequested(rtm)      ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
# define rtmSetStopRequested(rtm, val) ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
# define rtmGetStopRequestedPtr(rtm)   (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
# define rtmGetT(rtm)                  (rtmGetTPtr((rtm))[0])
#endif

/* Block signals (auto storage) */
typedef struct {
  real_T Output[3];                    /* '<S1>/Output' */
} BlockIO;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  real_T NextOutput;                   /* '<S1>/White Noise' */
  uint32_T RandSeed;                   /* '<S1>/White Noise' */
} D_Work;

/* Continuous states (auto storage) */
typedef struct {
  real_T Integrator_CSTATE[3];         /* '<Root>/Integrator' */
} ContinuousStates;

/* State derivatives (auto storage) */
typedef struct {
  real_T Integrator_CSTATE[3];         /* '<Root>/Integrator' */
} StateDerivatives;

/* State disabled  */
typedef struct {
  boolean_T Integrator_CSTATE[3];      /* '<Root>/Integrator' */
} StateDisabled;

#ifndef ODE4_INTG
#define ODE4_INTG

/* ODE4 Integration Data */
typedef struct {
  real_T *y;                           /* output */
  real_T *f[4];                        /* derivatives */
} ODE4_IntgData;

#endif

/* Real-time Model Data Structure */
struct RT_MODEL {
  const char_T * volatile errorStatus;
  RTWSolverInfo solverInfo;

  /*
   * ModelData:
   * The following substructure contains information regarding
   * the data used in the model.
   */
  struct {
    real_T *contStates;
    real_T *derivs;
    boolean_T *contStateDisabled;
    boolean_T zCCacheNeedsReset;
    boolean_T derivCacheNeedsReset;
    boolean_T blkStateChange;
    real_T odeY[3];
    real_T odeF[4][3];
    ODE4_IntgData intgData;
  } ModelData;

  /*
   * Sizes:
   * The following substructure contains sizes information
   * for many of the model attributes such as inputs, outputs,
   * dwork, sample times, etc.
   */
  struct {
    int_T numContStates;
    int_T numSampTimes;
  } Sizes;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    uint32_T clockTick0;
    time_T stepSize0;
    uint32_T clockTick1;
    SimTimeStep simTimeStep;
    boolean_T stopRequestedFlag;
    time_T *t;
    time_T tArray[2];
  } Timing;
};

#ifdef __cplusplus

extern "C" {

#endif

  /* Model entry point functions */
  extern void Main_initialize(RT_MODEL *const rtM, BlockIO *rtB, D_Work *rtDWork,
    ContinuousStates *rtX);
  extern void Main_output(RT_MODEL *const rtM, BlockIO *rtB, D_Work *rtDWork);
  extern void Main_update(RT_MODEL *const rtM, BlockIO *rtB, D_Work *rtDWork);
  extern void Main_terminate(void);

#ifdef __cplusplus

}
#endif

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'Main'
 * '<S1>'   : 'Main/Band-Limited White Noise'
 * '<S2>'   : 'Main/Gaussian Filter'
 * '<S3>'   : 'Main/Target Preferences'
 */
#endif                                 /* RTW_HEADER_Main_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
