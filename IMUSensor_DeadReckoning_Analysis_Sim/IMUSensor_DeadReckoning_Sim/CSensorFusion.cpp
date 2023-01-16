/*
 * CKalmanFilter.cpp
 */

#include "common.h"
#include "CSensorFusion.h"

CSensorFusion::CSensorFusion()
{
    m_kalmanPtr = new KalmanFilter_t(NO_OF_KALMAN_STATE_VARIABLES);

    CMatrix H(NO_OF_KALMAN_STATE_VARIABLES, NO_OF_KALMAN_STATE_VARIABLES);

    H_IMU = H;
    H_FH  = H;

    sensorfusion_calibration();
}

CSensorFusion::~CSensorFusion()
{
    delete m_kalmanPtr;
}

RC_t CSensorFusion::sensorfusion_calibration()
{
    /* 
     * Please refer https://code.fbi.h-da.de/StudentCar/teamprojects/080_deadreckoning/-/blob/main/40_Implementation/70_Reports/report_sensor_fusion_using_the_Kalman_filter_for_improved_deadreckoning.pdf
 	 * for details.
     *            _                                        _
     *           |  1   0   0   0   0   0   0   0   0   0   |
     *  H_IMU  = |  0   1   0   0   0   0   0   0   0   0   |
     *           |  0   0   1   0   0   0   0   0   0   0   |
     *           |  0   0   0   0   0   0   0   0   0   0   |
     *           |  0   0   0   0   0   0   0   0   0   0   |
     *           |  0   0   0   0   0   0   0   0   0   0   |
     *           |  0   0   0   0   0   0   0   0   0   0   |
     *           |  0   0   0   0   0   0   0   0   0   0   |
     *           |  0   0   0   0   0   0   0   0   0   0   |
     *           |  0   0   0   0   0   0   0   0   0   0   |
     *           -                                         -
     *
     */
    this->H_IMU.setBuffer(NO_OF_KALMAN_STATE_VARIABLES-NO_OF_KALMAN_STATE_VARIABLES, NO_OF_KALMAN_STATE_VARIABLES-NO_OF_KALMAN_STATE_VARIABLES, (float)1.0F);
    this->H_IMU.setBuffer(NO_OF_KALMAN_STATE_VARIABLES-(NO_OF_KALMAN_STATE_VARIABLES-1), NO_OF_KALMAN_STATE_VARIABLES-(NO_OF_KALMAN_STATE_VARIABLES-1), (float)1.0F);
    this->H_IMU.setBuffer(NO_OF_KALMAN_STATE_VARIABLES-(NO_OF_KALMAN_STATE_VARIABLES-2), NO_OF_KALMAN_STATE_VARIABLES-(NO_OF_KALMAN_STATE_VARIABLES-2), (float)1.0F);
    /* 
     *
     * Please refer https://code.fbi.h-da.de/StudentCar/teamprojects/080_deadreckoning/-/blob/main/40_Implementation/70_Reports/report_sensor_fusion_using_the_Kalman_filter_for_improved_deadreckoning.pdf
 	 * for details.
     *             _                                       _
     *           |  0   0   0   0   0   0   0   0   0   0   |
     *  H_FH   = |  0   0   0   0   0   0   0   0   0   0   |
     *           |  0   0   0   0   0   0   0   0   0   0   |
     *           |  0   0   0   0   0   0   0   0   0   0   |
     *           |  0   0   0   0   0   0   0   0   0   0   |
     *           |  0   0   0   0   0   0   0   0   0   0   |
     *           |  0   0   0   0   0   0   0   0   0   0   |
     *           |  0   0   0   0   0   0   0   1   0   0   |
     *           |  0   0   0   0   0   0   0   0   1   0   |
     *           |  0   0   0   0   0   0   0   0   0   1   |
     *           -                                         -
     *
     */
    this->H_FH.setBuffer(NO_OF_KALMAN_STATE_VARIABLES-3, NO_OF_KALMAN_STATE_VARIABLES-3, (float)1.0F);
    this->H_FH.setBuffer(NO_OF_KALMAN_STATE_VARIABLES-2, NO_OF_KALMAN_STATE_VARIABLES-2, (float)1.0F);
    this->H_FH.setBuffer(NO_OF_KALMAN_STATE_VARIABLES-1, NO_OF_KALMAN_STATE_VARIABLES-1, (float)1.0F);

    /***************************************************************************************/
    /*
     * This segment of code is for simulation purpose only.
     * Actual calibration needs to be achieved for the below matrices.
     * Please refer https://code.fbi.h-da.de/StudentCar/teamprojects/080_deadreckoning/-/blob/main/40_Implementation/70_Reports/report_sensor_fusion_using_the_Kalman_filter_for_improved_deadreckoning.pdf
 	 * for details.
     */
    for(uint16_t rowIdx = 0; rowIdx < NO_OF_KALMAN_STATE_VARIABLES; rowIdx++)
    {
        for(uint16_t colIdx = 0; colIdx < NO_OF_KALMAN_STATE_VARIABLES; colIdx++)
        {
            m_kalmanPtr->R.setBuffer(rowIdx, colIdx, (float)(rowIdx+colIdx)/50);
            m_kalmanPtr->Q.setBuffer(rowIdx, colIdx, (float)(colIdx-rowIdx)/50);
            m_kalmanPtr->P.setBuffer(rowIdx, colIdx, (float)((rowIdx+colIdx) * (colIdx-rowIdx))/50);
            m_kalmanPtr->A.setBuffer(rowIdx, colIdx, (float)(rowIdx+colIdx));
        }
    }
    
    return RC_SUCCESS;
}

RC_t CSensorFusion::sensorfusion_kalman_predict(SENSORPOSITION_data_t& senspos)
{
    /* 
     * Please refer https://code.fbi.h-da.de/StudentCar/teamprojects/080_deadreckoning/-/blob/main/40_Implementation/70_Reports/report_sensor_fusion_using_the_Kalman_filter_for_improved_deadreckoning.pdf
 	 * for details.
     *            _        _
     *           |  axm     |
     *  x(k-1) = |  aym     |
     *           |  anglezm |
     *           |  ax      |
     *           |  ay      |
     *           |  vx      |
     *           |  vy      |
     *           |   x      |
     *           |   y      |
     *           |  phi     |
     *            -        -
     *
     */
    this->m_kalmanPtr->x.setBuffer(0, 0, senspos.scanValue.acc[X_AXIS]);
    this->m_kalmanPtr->x.setBuffer(1, 0, senspos.scanValue.acc[Y_AXIS]);
    this->m_kalmanPtr->x.setBuffer(2, 0, senspos.scanValue.angle[PHI_AXIS]);
    this->m_kalmanPtr->x.setBuffer(3, 0, senspos.preProcess.acc[X_AXIS]);
    this->m_kalmanPtr->x.setBuffer(4, 0, senspos.preProcess.acc[Y_AXIS]);
    this->m_kalmanPtr->x.setBuffer(5, 0, senspos.preProcess.vel[X_AXIS]);
    this->m_kalmanPtr->x.setBuffer(6, 0, senspos.preProcess.vel[Y_AXIS]);
    this->m_kalmanPtr->x.setBuffer(7, 0, senspos.preProcess.pos.x);
    this->m_kalmanPtr->x.setBuffer(8, 0, senspos.preProcess.pos.y);
    this->m_kalmanPtr->x.setBuffer(9, 0, senspos.preProcess.pos.phi);

    this->m_kalmanPtr->kalman_filter_predict();
    return RC_SUCCESS;
}

RC_t CSensorFusion::sensorfusion_kalman_update(SENSORPOSITION_data_t& senspos)
{
    /* 
     * Please refer https://code.fbi.h-da.de/StudentCar/teamprojects/080_deadreckoning/-/blob/main/40_Implementation/70_Reports/report_sensor_fusion_using_the_Kalman_filter_for_improved_deadreckoning.pdf
 	 * for details.
     *            _        _
     *           |  axm     |
     *  z(k) =   |  aym     |
     *           |  anglezm |
     *           |  0       |
     *           |  0       |
     *           |  0       |
     *           |  0       |
     *           |  0       |
     *           |  0       |
     *           |  0       |....................IMU
     *            -        -
     *
     */
    this->m_kalmanPtr->z.setBuffer(0, 0, senspos.scanValue.acc[X_AXIS]);
    this->m_kalmanPtr->z.setBuffer(1, 0, senspos.scanValue.acc[Y_AXIS]);
    this->m_kalmanPtr->z.setBuffer(2, 0, senspos.scanValue.angle[PHI_AXIS]);
    this->m_kalmanPtr->z.setBuffer(3, 0, (float) 0.0F);
    this->m_kalmanPtr->z.setBuffer(4, 0, (float) 0.0F);
    this->m_kalmanPtr->z.setBuffer(5, 0, (float) 0.0F);
    this->m_kalmanPtr->z.setBuffer(6, 0, (float) 0.0F);
    this->m_kalmanPtr->z.setBuffer(7, 0, (float) 0.0F);
    this->m_kalmanPtr->z.setBuffer(8, 0, (float) 0.0F);
    this->m_kalmanPtr->z.setBuffer(9, 0, (float) 0.0F);

    this->m_kalmanPtr->kalman_filter_update(this->H_IMU);

    /* Optimal position and orientation determined. */
    /* Further, memorising the values for next iteration of Kalman filter algorithm.*/
    senspos.preProcess.pos.x    = this->m_kalmanPtr->x.getBuffer(NO_OF_KALMAN_STATE_VARIABLES-3, 0);
    senspos.preProcess.pos.y    = this->m_kalmanPtr->x.getBuffer(NO_OF_KALMAN_STATE_VARIABLES-2, 0);
    senspos.preProcess.pos.phi  = this->m_kalmanPtr->x.getBuffer(NO_OF_KALMAN_STATE_VARIABLES-1, 0);

    

    return RC_SUCCESS;
}

RC_t CSensorFusion::sensorfusion_kalman_update(SENSORPOSITION_data_t& senspos, FHDecoderPosition_data_t& fhdecoderpos)
{
    /* 
     *            _        _
     *           |  0       |
     *  z(k) =   |  0       |
     *           |  0       |
     *           |  0       |
     *           |  0       |
     *           |  0       |
     *           |  0       |
     *           |  x       |
     *           |  y       |
     *           |  phi     |....................Faulhaber decoder
     *            -        -
     *
     */
    this->m_kalmanPtr->z.setBuffer(0, 0, (float) 0.0F);
    this->m_kalmanPtr->z.setBuffer(1, 0, (float) 0.0F);
    this->m_kalmanPtr->z.setBuffer(2, 0, (float) 0.0F);
    this->m_kalmanPtr->z.setBuffer(3, 0, (float) 0.0F);
    this->m_kalmanPtr->z.setBuffer(4, 0, (float) 0.0F);
    this->m_kalmanPtr->z.setBuffer(5, 0, (float) 0.0F);
    this->m_kalmanPtr->z.setBuffer(6, 0, (float) 0.0F);
    this->m_kalmanPtr->z.setBuffer(7, 0, fhdecoderpos.pos.x);
    this->m_kalmanPtr->z.setBuffer(8, 0, fhdecoderpos.pos.y);
    this->m_kalmanPtr->z.setBuffer(9, 0, fhdecoderpos.pos.phi);

    this->m_kalmanPtr->kalman_filter_update(this->H_IMU);

    /* Optimal position and orientation determined. */
    /* Further, memorising the values for next iteration of Kalman filter algorithm.*/
    senspos.preProcess.pos.x    = this->m_kalmanPtr->x.getBuffer(NO_OF_KALMAN_STATE_VARIABLES-3, 0);
    senspos.preProcess.pos.y    = this->m_kalmanPtr->x.getBuffer(NO_OF_KALMAN_STATE_VARIABLES-2, 0);
    senspos.preProcess.pos.phi  = this->m_kalmanPtr->x.getBuffer(NO_OF_KALMAN_STATE_VARIABLES-1, 0);

    return RC_SUCCESS;
}
