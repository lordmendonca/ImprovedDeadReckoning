/*
 * CKalmanFilter.cpp
 */

#include "common.h"
#include "CKalmanFilter.h"
#include "CIMUSensor.h"

CKalmanFilter::CKalmanFilter(uint16_t noOfStateVariablesInStateVector)
{
    CMatrix columnVector((uint16_t)noOfStateVariablesInStateVector, (uint16_t)1);
    CMatrix squareMatrix((uint16_t)noOfStateVariablesInStateVector, (uint16_t)noOfStateVariablesInStateVector);

    x = columnVector;

    P = squareMatrix;

    z = columnVector;

    R = squareMatrix;

    K = squareMatrix;

    A = squareMatrix;

    H = squareMatrix;

    Q = squareMatrix;

    xP = columnVector;

    PP = squareMatrix;

    U = squareMatrix;
    for(uint16_t rowIdx = 0; rowIdx < noOfStateVariablesInStateVector; rowIdx++)
    {
        for(uint16_t colIdx = 0; colIdx < noOfStateVariablesInStateVector; colIdx++)
        {
            U.setBuffer(rowIdx, colIdx, (float) 1.0F);
        }
    }    
}

CKalmanFilter::~CKalmanFilter()
{

}

RC_t CKalmanFilter::kalman_filter_predict()
{
    try
    {
    /* Predict the system  state estimate, xP
     * 
     * xP = A * x(k-1)
     * 
     */
    
        this->xP = this->A * this->x;

    /* Predict the system  state error covariance, PP
     * 
     * PP = [A * P(k-1) * transpose(A)] + Q
     * 
     */
        this->PP = (this->A * this->P * this->A.matrixTranspose()) + this->Q;
        
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return RC_ERRORPREDICTKALMANPOSITION;
    }
    
    return RC_SUCCESS;
}

RC_t CKalmanFilter::kalman_filter_update(const CMatrix& H)
{
	try
    {
    /* Update Kalman Gain
     *       _                             _
     *      |         PP * transpose(H)     |
     *  K = | ----------------------------- |
     *      |  (H * PP * transpose(H)) + R  |
     *       -                             -
     *
     */
        CMatrix HTranspose;
        HTranspose = this->H.matrixTranspose();

        CMatrix denom;
        denom = (this->H * this->PP * HTranspose) + R;

        if(denom.isInvertible())
        {
            this->K = this->PP * HTranspose * denom;
        }
        else
        {
            /* Error thrown when denominator is singular. */
            std::cout << "Denominator of Kalman gain calculation is singular" << std::endl;
            throw;
        }

    /* Update the system state, xk
     *
     *  xk = xP + K(zk - H * xP)
     *
     */
        this->x = this->xP + this->K * (this->z - (this->H * this->xP));

    
    /* Update the system state error covariance, P
     *
     *  Pk = PP[1 - (K * H)]
     *
     */
        this->P = this->PP * (this->U - (this->K * this->H));
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return RC_ERRORUPDATEKALMANPOSITION;
    }
    
    return RC_SUCCESS;
}
