/*
 * CFilter.cpp
 */

#include "CFilter.h"

CFilter::CFilter()
{
	// TODO Auto-generated constructor stub

}

CFilter::~CFilter()
{
	// TODO Auto-generated destructor stub
}

void CFilter::maf_ntap(float* data_out, float data_in, float* data_mem, unsigned int noOfTaps)
{
	float data_sum = 0.0F;

	for(unsigned int i = 0; i < noOfTaps-1; i++)
	{
		data_mem[i] = data_mem[i+1];
	}

	data_mem[noOfTaps-1] = data_in;

	for(unsigned int i = 0; i < noOfTaps; i++)
	{
		data_sum += data_mem[i];
	}

	*data_out = data_sum / noOfTaps;
}

void CFilter::maf_ntap(float* data_out, float* data_out_prev, float data_in, float* data_mem, unsigned int noOfTaps)
{

	*data_out = *data_out_prev + ((data_in - data_mem[0])/noOfTaps);

	for(unsigned int i = 0; i < noOfTaps-1; i++)
	{
		data_mem[i] = data_mem[i+1];
	}

	data_mem[noOfTaps-1] = data_in;
}

void CFilter::exp_avg_filter(float* data_out, float data_in, float* data_out_delay)
{
	*data_out = ALPHA_COEFF * (data_in) + (1.0F - ALPHA_COEFF) * (*data_out_delay);
	*data_out_delay = *data_out;
}

