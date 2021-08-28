/*
 * File: Controller_data.c
 *
 * Code generated for Simulink model 'Controller'.
 *
 * Model version                  : 3.4
 * Simulink Coder version         : 9.4 (R2020b) 29-Jul-2020
 * C/C++ source code generated on : Wed Aug 25 10:24:31 2021
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "Controller.h"
#include "Controller_private.h"

/* Model block global parameters (default storage) */
CoreConfiguration rtP_Configuration =
{
  {
    false,
    0.6
  },

  {
    1.2
  }
} ;                                    /* Variable: Configuration
                                        * Referenced by: '<Root>/MatGain1'
                                        */

real_T rtP_X3_DD[27] =
{
  1.0, 4.0, 7.0, 2.0, 5.0, 8.0, 3.0, 6.0, 9.0, 1.0, 4.0, 7.0, 2.0, 5.0, 8.0, 3.0,
  6.0, 9.0, 1.0, 4.0, 7.0, 2.0, 5.0, 8.0, 3.0, 6.0, 9.0
} ;                                    /* Variable: X3_DD
                                        * Referenced by: '<Root>/Constant1'
                                        */

real_T rtP_X4_DD[64] =
{
  1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0,
  15.0, 16.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0,
  13.0, 14.0, 15.0, 16.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0,
  11.0, 12.0, 13.0, 14.0, 15.0, 16.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0,
  9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0
} ;                                    /* Variable: X4_DD
                                        * Referenced by: '<Root>/Constant2'
                                        */

/* Block parameters (default storage) */
Parameters_Controller_T Controller_P =
{
  /* Variable: mMatrix
   * Referenced by: '<Root>/MatGain'
   */
  {
    1.0, 3.0, 6.0, 2.0, 4.0, 7.0, 3.0, 5.0, 8.0
  },

  /* Expression: eye(3)
   * Referenced by: '<Root>/Constant'
   */
  {
    1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0
  },

  /* Expression: Config3_MW(2).Gain
   * Referenced by: '<Root>/ConfigMW2'
   */
  1.5,

  /* Expression: Config3_MW(1).Gain
   * Referenced by: '<Root>/ConfigMW1'
   */
  1.5,

  /* Expression: 0
   * Referenced by: '<Root>/AlgLoop'
   */
  0.0,

  /* Expression: 2
   * Referenced by: '<Root>/SuperDuperGainBlock'
   */
  2.0,

  /* Computed Parameter: DiscreteTimeIntegrator_gainval
   * Referenced by: '<Root>/Discrete-Time Integrator'
   */
  0.01,

  /* Expression: 0
   * Referenced by: '<Root>/Discrete-Time Integrator'
   */
  0.0
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
