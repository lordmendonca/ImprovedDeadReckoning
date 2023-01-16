/*
 * CFaulhaber.h
 */

#ifndef CFAULHABER_H_
#define CFAULHABER_H_

#include "common.h"

///////////////////////////////////////////////////////////
/// @brief FHDecoder_position_data
///
class CFHDecoder_position_data
{
public:
    float32_t x;    /*!< brief x Position in [cm] */
    float32_t y;    /*!< brief y Position in [cm] */
    float32_t phi;  /*!< brief Orientation in [degree] */
    CFHDecoder_position_data(); //constructor
    virtual ~CFHDecoder_position_data();  //destructor

    /**
    * \brief Operator Overloading : Overloads the assignment operator '='.
    * \param [in] value copy of value of type float 
    * \return None.
    */
    void operator = (float32_t value);
};

typedef CFHDecoder_position_data FHDecoder_position_data_t;

///////////////////////////////////////////////////////////
/// @brief FHDecoderPosition_data
///
class CFHDecoderPosition_data
{
public:
    float32_t						raster;			//!< Buffer timestamp
	FHDecoder_position_data_t       pos;            //!< Buffer FH decoder dead reckoned position  

    CFHDecoderPosition_data(); //constructor
    virtual ~CFHDecoderPosition_data();  //destructor

    /**
    * \brief Operator Overloading : Overloads the assignment operator '='.
    * \param [in] value copy of value of type float 
    * \return None.
    */
    CFHDecoderPosition_data& operator = (float32_t value);
    /**
    * \brief Operator Overloading : Overloads the assignment operator '='.
    * \param [in] RHS reference of RHS of type CFHDecoderPosition_data 
    * \return reference of type CFHDecoderPosition_data.
    */
    CFHDecoderPosition_data& operator = (const CFHDecoderPosition_data& RHS);
};

typedef CFHDecoderPosition_data FHDecoderPosition_data_t;

#endif
