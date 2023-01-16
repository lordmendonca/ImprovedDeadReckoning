/*
 * CIMUSensor.h
 */

#ifndef CIMUSENSOR_H_
#define CIMUSENSOR_H_

#include "common.h"

///////////////////////////////////////////////////////////
/// @brief IMUSENSOR__scanvalue
///
class CIMUSENSOR__scanvalue
{
public:
    float32_t acc[MAX_AXES]; //acceleration along linear axes - x and y
    float32_t gyro[MAX_AXES]; //angular velocity along 3 axes
    float32_t angle[MAX_AXES]; // angle out along z axis;

    CIMUSENSOR__scanvalue();    //constructor
    virtual ~CIMUSENSOR__scanvalue();  //destructor

    /**
    * \brief Operator Overloading : Overloads the assignment operator '='.
    * \param [in] value copy of value of type float 
    * \return None.
    */
    void operator = (float32_t value);
};

typedef CIMUSENSOR__scanvalue IMUSENSOR__scanvalue_t;

///////////////////////////////////////////////////////////
/// @brief IMUSENSOR__filter_mem
///
class CIMUSENSOR__filter_mem
{
public:
    float32_t mem[NO_OF_FILTER_TAPS]; // memory for n-tap filter

    CIMUSENSOR__filter_mem(); //constructor
    virtual ~CIMUSENSOR__filter_mem();  //destructor

    /**
    * \brief Operator Overloading : Overloads the assignment operator '='.
    * \param [in] value copy of value of type float 
    * \return None.
    */
    void operator = (float32_t value);
};

typedef CIMUSENSOR__filter_mem IMUSENSOR__filter_mem_t;

///////////////////////////////////////////////////////////
/// @brief IMUSENSOR__filtered
///
class CIMUSENSOR__filtered
{
public:
    float32_t               acc[MAX_AXES];        //filtered acceleration along linear axes -  x and y
    float32_t               angle;                  //filtered angle along linear axes -  x and y
    IMUSENSOR__filter_mem_t acc_filter[MAX_AXES]; //filter memory for acceleration along linear axes -  x and y
    IMUSENSOR__filter_mem_t angle_filter;           //filter memory for angle along z axis

    CIMUSENSOR__filtered(); //constructor
    virtual ~CIMUSENSOR__filtered();  //destructor

    /**
    * \brief Operator Overloading : Overloads the assignment operator '='.
    * \param [in] value copy of value of type float 
    * \return None.
    */
    void operator = (float32_t value);
};

typedef CIMUSENSOR__filtered IMUSENSOR__filtered_t;

///////////////////////////////////////////////////////////
/// @brief IMUSENSOR_position_data
///
class CIMUSENSOR_position_data
{
public:
    float32_t x;    /*!< brief x Position in [cm] */
    float32_t y;    /*!< brief y Position in [cm] */
    float32_t phi;  /*!< brief Orientation in [degree] */
    CIMUSENSOR_position_data(); //constructor
    virtual ~CIMUSENSOR_position_data();  //destructor

    /**
    * \brief Operator Overloading : Overloads the assignment operator '='.
    * \param [in] value copy of value of type float 
    * \return None.
    */
    void operator = (float32_t value);
};

typedef CIMUSENSOR_position_data IMUSENSOR_position_data_t;

///////////////////////////////////////////////////////////
/// @brief IMUSENSOR__preprocess
///
class CIMUSENSOR__preprocess
{
public:
    float32_t   acc[MAX_AXES]; //acceleration along linear axes - x and y
    float32_t   vel[MAX_AXES]; //angular velocity along linear axes - x and y
    float32_t   prevZangle; //previous angle along 3 axes

    IMUSENSOR_position_data_t pos;

    CIMUSENSOR__preprocess(); //constructor
    virtual ~CIMUSENSOR__preprocess();  //destructor

    /**
    * \brief Operator Overloading : Overloads the assignment operator '='.
    * \param [in] value copy of value of type float 
    * \return None.
    */
    void operator = (float32_t value);
};

typedef CIMUSENSOR__preprocess IMUSENSOR__preprocess_t;

typedef IMUSENSOR_position_data_t IMUSENSOR_kalman_position_data_t;

///////////////////////////////////////////////////////////
/// @brief CIMUSENSOR__kalman_mem_type1
///
class CIMUSENSOR__kalman_mem_type1
{
public:
    float32_t mem[NO_OF_KALMAN_STATE_VARIABLES * NO_OF_KALMAN_STATE_VARIABLES]; // memory to store the kalman gain and measurement error covariance matrix
    
    CIMUSENSOR__kalman_mem_type1(); //constructor
    virtual ~CIMUSENSOR__kalman_mem_type1();  //destructor
    /**
    * \brief Operator Overloading : Overloads the assignment operator '='.
    * \param [in] value copy of value of type float 
    * \return None.
    */
    void operator = (float32_t value);
};

typedef CIMUSENSOR__kalman_mem_type1 IMUSENSOR__kalman_mem_type1_t;

///////////////////////////////////////////////////////////
/// @brief CIMUSENSOR__kalman_mem_type2
///
class CIMUSENSOR__kalman_mem_type2
{
public:
    float32_t mem[NO_OF_KALMAN_STATE_VARIABLES]; // memory to store the state vector
    
    CIMUSENSOR__kalman_mem_type2(); //constructor
    virtual ~CIMUSENSOR__kalman_mem_type2(); //destructor

    /**
    * \brief Operator Overloading : Overloads the assignment operator '='.
    * \param [in] value copy of value of type float 
    * \return None.
    */
    void operator = (float32_t value);
};

typedef CIMUSENSOR__kalman_mem_type2 IMUSENSOR__kalman_mem_type2_t;

///////////////////////////////////////////////////////////
/// @brief IMUSENSOR__kalman_position
///
class CIMUSENSOR__kalman_position
{
public:
    IMUSENSOR_kalman_position_data_t    pos;            // position determined using kalman filte,  Note: maybe obselete
    IMUSENSOR__kalman_mem_type1_t       matrix_P;       // measurement error covariance matrix
    IMUSENSOR__kalman_mem_type1_t       matrix_K;       // kalman gain
    IMUSENSOR__kalman_mem_type2_t       stateVector_x;  // state vector


    CIMUSENSOR__kalman_position(); //constructor
    virtual ~CIMUSENSOR__kalman_position();  //destructor

    /**
    * \brief Operator Overloading : Overloads the assignment operator '='.
    * \param [in] value copy of value of type float 
    * \return None.
    */
    void operator = (float32_t value);

};

typedef CIMUSENSOR__kalman_position IMUSENSOR__kalman_position_t;

///////////////////////////////////////////////////////////
/// @brief SENSORPOSITION_data
///
class CSENSORPOSITION_data
{
public:
    float32_t						raster;			//!< Buffer timestamp
	IMUSENSOR__scanvalue_t          scanValue;      //!< Buffer storing the received scans
    IMUSENSOR__preprocess_t         preProcess;     //!< Buffer storing the pre-process outputs
    IMUSENSOR__filtered_t           filtered;       //!< Buffer storing the filter elements
    IMUSENSOR__kalman_position_t    kalman;         //!< Buffer storing the kalman filter estimates

    CSENSORPOSITION_data(); //constructor
    virtual ~CSENSORPOSITION_data();  //destructor

    /**
    * \brief Operator Overloading : Overloads the assignment operator '='.
    * \param [in] value copy of value of type float 
    * \return None.
    */
    CSENSORPOSITION_data& operator = (float32_t value);
    /**
    * \brief Operator Overloading : Overloads the assignment operator '='.
    * \param [in] RHS reference of RHS of type CSENSORPOSITION_data 
    * \return reference of type CSENSORPOSITION_data.
    */
    CSENSORPOSITION_data& operator = (const CSENSORPOSITION_data& RHS);
};

typedef CSENSORPOSITION_data SENSORPOSITION_data_t;

#endif
