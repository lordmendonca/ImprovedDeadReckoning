/*
 * CSensorFusion.h
 */

#ifndef CIMUSENSORFUSION_H_
#define CIMUSENSORFUSION_H_

#include <iostream>
#include "common.h"
#include "CKalmanFilter.h"
#include "CIMUSensor.h"
#include "CFaulhaber.h"

/**
 * Please refer https://code.fbi.h-da.de/StudentCar/teamprojects/080_deadreckoning/-/blob/main/40_Implementation/70_Reports/report_sensor_fusion_using_the_Kalman_filter_for_improved_deadreckoning.pdf
 * for details.
 */
class CSensorFusion
{
public:

typedef enum
{
	IMUSENSOR,	// Uses IMU sensor for both predict and update steps
	FAULHABER	// Uses IMU sensor for predict step and Faulhaber decoder for update step
}sensor_t;
	/**
	 * A member of type pointer to Kalman filter. 
	 */
	KalmanFilter_t* m_kalmanPtr;
	/**
	 * state to measurement matrix for IMU sensor
	 */
	CMatrix H_IMU;
	/**
	 * state to measurement matrix for Faulhaber decoder sensor
	 */
	CMatrix H_FH;
	/**
	 * default Constructor 
	 */
	CSensorFusion();
	/**
	 * Destructor 
	 */
	virtual ~CSensorFusion();

	/**
	 * @brief Calibration of Kalman filter parameters 
	 */
	RC_t sensorfusion_calibration();
	/**
	 * @brief Kalman filter prediction step at sensor fusion
	 * @details Please refer https://code.fbi.h-da.de/StudentCar/teamprojects/080_deadreckoning/-/blob/main/40_Implementation/70_Reports/report_sensor_fusion_using_the_Kalman_filter_for_improved_deadreckoning.pdf
 	 * for details. 
	 */
	RC_t sensorfusion_kalman_predict(SENSORPOSITION_data_t& senspos);
	/**
	 * @brief Kalman filter update step at sensor fusion
	 * 
	 * @details Please refer https://code.fbi.h-da.de/StudentCar/teamprojects/080_deadreckoning/-/blob/main/40_Implementation/70_Reports/report_sensor_fusion_using_the_Kalman_filter_for_improved_deadreckoning.pdf
 	 * for details. 
	 */
	RC_t sensorfusion_kalman_update(SENSORPOSITION_data_t& senspos);
	/**
	 * @brief Kalman filter update step at sensor fusion
	 * 
	 * @details Please refer https://code.fbi.h-da.de/StudentCar/teamprojects/080_deadreckoning/-/blob/main/40_Implementation/70_Reports/report_sensor_fusion_using_the_Kalman_filter_for_improved_deadreckoning.pdf
 	 * for details. 
	 */
	RC_t sensorfusion_kalman_update(SENSORPOSITION_data_t& senspos, FHDecoderPosition_data_t& fhdecoderpos);
};

#endif /* CIMUSENSORFUSION_H_ */
