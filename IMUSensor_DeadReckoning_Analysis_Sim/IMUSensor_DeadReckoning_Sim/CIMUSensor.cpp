/*
 * CIMUSensor.cpp
 */

#include "CIMUSensor.h"

CIMUSENSOR__scanvalue::CIMUSENSOR__scanvalue()
{
    for(uint16_t idx = 0; idx < MAX_AXES; idx++)
    {
        this->acc[idx]  =   0.0F;
    }

    for(uint16_t idx = 0; idx < MAX_AXES; idx++)
    {
        this->gyro[idx]  =   0.0F;
    }

    for(uint16_t idx = 0; idx < MAX_AXES; idx++)
    {
        this->angle[idx]  =   0.0F;
    }
}

CIMUSENSOR__scanvalue::~CIMUSENSOR__scanvalue()
{

}

void CIMUSENSOR__scanvalue::operator = (float32_t value)
{
    for(uint16_t idx = 0; idx < MAX_AXES; idx++)
    {
        this->acc[idx]  =   value;
    }

    for(uint16_t idx = 0; idx < MAX_AXES; idx++)
    {
        this->gyro[idx]  =   value;
    }

    for(uint16_t idx = 0; idx < MAX_AXES; idx++)
    {
        this->angle[idx]  =   value;
    }
}

CIMUSENSOR__filter_mem::CIMUSENSOR__filter_mem()
{
    for(uint16_t idx = 0; idx < NO_OF_FILTER_TAPS; idx++)
    {
        mem[idx] = 0.0F;
    }
}

CIMUSENSOR__filter_mem::~CIMUSENSOR__filter_mem()
{

}

void CIMUSENSOR__filter_mem::operator = (float32_t value)
{
    for(uint16_t idx = 0; idx < NO_OF_FILTER_TAPS; idx++)
    {
        mem[idx] = value;
    }
}

CIMUSENSOR__filtered::CIMUSENSOR__filtered()
{
    for(uint16_t idx = 0; idx < MAX_AXES; idx++)
    {
        this->acc[idx]          =   0.0F;
        this->acc_filter[idx]   =   0.0F;
    }

    this->angle         =   0.0F;
    this->angle_filter  =   0.0F;
}

CIMUSENSOR__filtered::~CIMUSENSOR__filtered()
{

}

void CIMUSENSOR__filtered::operator = (float32_t value)
{
    for(uint16_t idx = 0; idx < MAX_AXES; idx++)
    {
        this->acc[idx]          =   value;
        this->acc_filter[idx]   =   value;
    }

    this->angle         =   value;
    this->angle_filter  =   value;
}

CIMUSENSOR__preprocess::CIMUSENSOR__preprocess()
{
    for(uint16_t idx = 0; idx < MAX_AXES; idx++)
    {
        this->acc[idx]  =   0.0F;
        this->vel[idx]  =   0.0F;
    }

    this->prevZangle    =   0.0F;

    this->pos = 0.0F;
}

CIMUSENSOR__preprocess::~CIMUSENSOR__preprocess()
{

}

void CIMUSENSOR__preprocess::operator = (float32_t value)
{
    for(uint16_t idx = 0; idx < MAX_AXES; idx++)
    {
        this->acc[idx]  =   value;
        this->vel[idx]  =   value;
    }

    this->prevZangle    =   value;

    this->pos = value;
}

CIMUSENSOR_position_data::CIMUSENSOR_position_data()
{
    this->x     =   0.0F;
    this->y     =   0.0F;
    this->phi   =   0.0F;
}

CIMUSENSOR_position_data::~CIMUSENSOR_position_data()
{

}

void CIMUSENSOR_position_data::operator = (float32_t value)
{
    this->x     = 0.0F;
    this->y     = 0.0F;
    this->phi   = 0.0F;
}

CIMUSENSOR__kalman_mem_type1::CIMUSENSOR__kalman_mem_type1()
{
    for(uint16_t idx = 0; idx < NO_OF_KALMAN_STATE_VARIABLES * NO_OF_KALMAN_STATE_VARIABLES; idx++)
    {
        this->mem[idx] = 0.0F;
    }
}

CIMUSENSOR__kalman_mem_type1::~CIMUSENSOR__kalman_mem_type1()
{

}

void CIMUSENSOR__kalman_mem_type1::operator = (float32_t value)
{
    for(uint16_t idx = 0; idx < NO_OF_KALMAN_STATE_VARIABLES * NO_OF_KALMAN_STATE_VARIABLES; idx++)
    {
        this->mem[idx] = value;
    }
}

CIMUSENSOR__kalman_mem_type2::CIMUSENSOR__kalman_mem_type2()
{
    for(uint16_t idx = 0; idx < NO_OF_KALMAN_STATE_VARIABLES; idx++)
    {
        this->mem[idx] = 0.0F;
    }
}

CIMUSENSOR__kalman_mem_type2::~CIMUSENSOR__kalman_mem_type2()
{

}

void CIMUSENSOR__kalman_mem_type2::operator = (float32_t value)
{
    for(uint16_t idx = 0; idx < NO_OF_KALMAN_STATE_VARIABLES; idx++)
    {
        this->mem[idx] = value;
    }
}

CIMUSENSOR__kalman_position::CIMUSENSOR__kalman_position()
{
    this->pos           =   0.0F;
    this->matrix_P      =   0.0F;
    this->matrix_K      =   0.0F;
    this->stateVector_x =   0.0F;
}

CIMUSENSOR__kalman_position::~CIMUSENSOR__kalman_position()
{

}

void CIMUSENSOR__kalman_position::operator = (float32_t value)
{
    this->pos               =   value;
    this->matrix_P          =   value;
    this->matrix_K          =   value;
    this->stateVector_x     =   value;
}

CSENSORPOSITION_data::CSENSORPOSITION_data()
{
    this->raster		= 0.0F;
	this->scanValue     = 0.0F;
    this->preProcess    = 0.0F;
    this->filtered      = 0.0F;
    this->kalman        = 0.0F;
}

CSENSORPOSITION_data::~CSENSORPOSITION_data()
{

}

CSENSORPOSITION_data& CSENSORPOSITION_data::operator = (float32_t value)
{
    this->raster		= value;
	this->scanValue     = value;
    this->preProcess    = value;
    this->filtered      = value;
    this->kalman        = value;
    return *this;
}

CSENSORPOSITION_data& CSENSORPOSITION_data::operator = (const CSENSORPOSITION_data& RHS)
{
	this->raster		= RHS.raster;
	this->scanValue		= RHS.scanValue;
	this->preProcess	= RHS.preProcess;
	this->filtered		= RHS.filtered;
	this->kalman		= RHS.kalman;
	return *this;
}

