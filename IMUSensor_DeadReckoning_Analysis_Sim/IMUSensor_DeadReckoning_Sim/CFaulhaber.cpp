/*
 * CFaulhaber.cpp
 */

#include "CFaulhaber.h"

CFHDecoder_position_data::CFHDecoder_position_data()
{
    this->x     =   0.0F;
    this->y     =   0.0F;
    this->phi   =   0.0F;
}

CFHDecoder_position_data::~CFHDecoder_position_data()
{

}

void CFHDecoder_position_data::operator = (float32_t value)
{
    this->x     = 0.0F;
    this->y     = 0.0F;
    this->phi   = 0.0F;
}

CFHDecoderPosition_data::CFHDecoderPosition_data()
{
    this->raster		= 0.0F;
	this->pos           = 0.0F;
}

CFHDecoderPosition_data::~CFHDecoderPosition_data()
{

}

CFHDecoderPosition_data& CFHDecoderPosition_data::operator = (float32_t value)
{
    this->raster		= value;
    this->pos           = value;
    return *this;
}

CFHDecoderPosition_data& CFHDecoderPosition_data::operator = (const CFHDecoderPosition_data& RHS)
{
	this->raster		= RHS.raster;
	this->pos           = RHS.pos;
	return *this;
}

