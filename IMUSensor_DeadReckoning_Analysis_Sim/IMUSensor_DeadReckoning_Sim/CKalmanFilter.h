/*
 * CKalmanFilter.h
 */

#ifndef CKALMANFILTER_H_
#define CKALMANFILTER_H_

#include <iostream>
#include "common.h"
#include "CMatrix.h"

/**
 * Please refer https://code.fbi.h-da.de/StudentCar/teamprojects/080_deadreckoning/-/blob/main/40_Implementation/70_Reports/report_sensor_fusion_using_the_Kalman_filter_for_improved_deadreckoning.pdf
 * for details.
 */
class CKalmanFilter
{
public:
	/**
	 * state variable vector, x
	 */
	CMatrix x;
	/**
	 * state covariance matrix, P
	 */
	CMatrix P;
	/**
	 * measurement variable vector, z
	 */
	CMatrix z;
	/**
	 * measurement covariance matrix, R
	 */
	CMatrix R;
	/**
	 * Kalman gain, K
	 */
	CMatrix K;
	/**
	 * state transition matrix, A
	 */
	CMatrix A;
	/**
	 * state to measurement matrix, H
	 */
	CMatrix H;
	/**
	 * process covariance matrix, Q
	 */
	CMatrix Q;
	/**
	 * system state prediction, xP
	 */
	CMatrix xP;
	/**
	 * system state error covariance prediction, PP
	 */
	CMatrix PP;
	/**
	 * unit matrix, U
	 */
	CMatrix U;
	/**
	 * @brief Parameterized Constructor
	 * @param noOfStateVariablesInStateVector Number of state variables that define a state vector
	 * @details Used to initialise the dimensions of the underlying Kalman filter parameters.
	 */
	CKalmanFilter(uint16_t noOfStateVariablesInStateVector);
	/**
	 * @brief Destructor 
	 */
	virtual ~CKalmanFilter();

	/** 
 	* @brief				: Predict system state and system error covariance matrix
 	* @details Please refer https://code.fbi.h-da.de/StudentCar/teamprojects/080_deadreckoning/-/blob/main/40_Implementation/70_Reports/report_sensor_fusion_using_the_Kalman_filter_for_improved_deadreckoning.pdf
 	* for details.
 	*/ 
	RC_t kalman_filter_predict();
	/** 
 	* @brief				: Calculate the Kalman gain, K, and then update system state and system error covariance matrix
 	* @details Please refer https://code.fbi.h-da.de/StudentCar/teamprojects/080_deadreckoning/-/blob/main/40_Implementation/70_Reports/report_sensor_fusion_using_the_Kalman_filter_for_improved_deadreckoning.pdf
 	* for details.
 	*/ 
	RC_t kalman_filter_update(const CMatrix& H);
};

typedef CKalmanFilter KalmanFilter_t;

#endif /* CKALMANFILTER_H_ */
