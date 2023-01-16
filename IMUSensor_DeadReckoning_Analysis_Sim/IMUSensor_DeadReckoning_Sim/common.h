
/*
 * Filename :   common.h
 */

#ifndef _H_DEFINE_COMMON
#define _H_DEFINE_COMMON

// Standard (system) header files
#include <iostream>
#include <cstdlib>

// Add more standard header files as required
#include "math.h"
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

typedef enum
{
    X_AXIS,
    Y_AXIS,
    Z_AXIS,
    MAX_AXES
} IMUSENSOR_axes_t;

typedef enum
{
    RC_SUCCESS,
    RC_BUFFEROVERFLOW,
    RC_BUFFERUNDERFLOW,
    RC_DIVIDEBYZERO,
    RC_ERRORBADPARAM,
	RC_ERRORREADTXTFILE,
	RC_ERRORREADCSVFILE,
	RC_ERRORREADSENSORRAWDATA,
	RC_ERRORCREATECSVIMUSENSORDEADRECKONING,
	RC_ERRORUPDATESENSORFILTER,
	RC_ERRORCALCSENSORPOSITION,
    RC_ERRORPREDICTKALMANPOSITION,
	RC_ERRORUPDATEKALMANPOSITION,
	RC_ERRORPRINTIMUSENSORDEADRECKONING,
	RC_ERRORWRITEIMUSENSORDEADRECKONING,
    RC_ERROR
} RC_t;

#define PHI_AXIS                    Z_AXIS

#define M_PI						3.14159265358979323846

/**
 * Sensor Rx interrupt arrives nearly every 5ms.
 */
#define CYCLETIME                   0.005F
#define CYCLETIMESQ                 0.000025F
/**
 * acceleration (physical) = acceleration (internal) * ACCEL_COMPENSATION
 *                           _          _
 *                          |   16 * g   |
 *  ACCEL_COMPENSATION =    | ---------- |..................................[unit : cm/s2]
 *                          |    32768   |
 *                           -          -
 * where, g is acceleration of gravity , 980.665 cm/s2
 */
#define ACCEL_COMPENSATION          0.47884033203125F
/**
 * angular velocity (physical) =  angular velocity (internal) * GYRO_COMPENSATION
 *                           _         _
 *                          |   2000    |
 *  GYRO_COMPENSATION  =    | --------- |..................................[unit : deg/s]
 *                          |   32768   |
 *                           -         -
 */
#define GYRO_COMPENSATION           0.06103515625F
/**
 * angle (physical) =  angle (internal) * ANGLE_COMPENSATION
 *                           _         _
 *                          |    180    |
 *  ANGLE_COMPENSATION =    | --------- |..................................[unit : deg]
 *                          |   32768   |
 *                           -         -
 */
#define ANGLE_COMPENSATION          0.0054931640625F

/* Number of state parameters for Kalman Filter. */
#define NO_OF_KALMAN_STATE_VARIABLES    10U

/* Is the motion of the car only linear? then 1U else 0U. */
#define LINEAR_MODE                 1U

/* Enabling filter with 1U, else 0U. */
#define FILTERMODE                  1U

/* Number of filter taps */
#define NO_OF_FILTER_TAPS           32U
/* alpha co-effecient of Exponential Averager Filter */
#define ALPHA_COEFF 0.1F

/* Enabling Kalman Filter estimation algorithm with 1U, else 0U. */
#define KALMANFILTERMODE            0U

/* Macros for fixed point comparisons. */
#define _absfxp_u8(X)               ((uint8_t)  ( ((X) < (uint8_t)  0U) ? -(X) : (X) ))
#define _absfxp_s8(X)               ((int8_t)   ( ((X) < (int8_t)   0U) ? -(X) : (X) ))
#define _absfxp_u16(X)              ((uint16_t) ( ((X) < (uint16_t) 0U) ? -(X) : (X) ))
#define _absfxp_s16(X)              ((int16_t)  ( ((X) < (int16_t)  0U) ? -(X) : (X) ))
#define _absfxp_u32(X)              ((uint32_t) ( ((X) < (uint32_t) 0U) ? -(X) : (X) ))
#define _absfxp_s32(X)              ((int32_t)  ( ((X) < (int32_t)  0U) ? -(X) : (X) ))


#define float32_t float_t

#endif
