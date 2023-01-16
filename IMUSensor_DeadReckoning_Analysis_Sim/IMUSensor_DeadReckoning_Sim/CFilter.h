/*
 * CFilter.h
 */

#ifndef CFILTER_H_
#define CFILTER_H_

#include "common.h"

class CFilter
{
public:
	CFilter();
	virtual ~CFilter();
	/**
	 * \brief N-Tap Moving Averager : Low-Pass FIR Filter Type 1.
	 * \param float32_t*	data_out		: pointer to latest filtered output data.
	 * \param float32_t		data_in			: latest input data.
	 * \param float32_t*	data_mem		: pointer to previous input data.
	 * \param float32_t		noOfTaps		: number of filter taps.
	 * \param float32_t*	data_out_delay	: previous filtered output data.
	 * \details The output data is the most recent averaged data.
	 * \details [output data] = ([input data at i] + [input data at i-1] + ... + [input data at i-(N-1)]) / N, where N is the number of filter taps.
	 */
	void maf_ntap(float* data_out, float data_in, float* data_mem, unsigned int noOfTaps);

	/**
	 * \brief N-Tap Moving Averager : Low-Pass FIR Filter Type 2.
	 * \param float32_t*	data_out		: pointer to latest filtered output data.
	 * \param float32_t*	data_out_delay	: pointer to previous filtered output data.
	 * \param float32_t		data_in			: latest input data.
	 * \param float32_t*	data_mem		: pointer to previous input data.
	 * \param float32_t		noOfTaps		: number of filter taps.
	 * \details The output data is the most recent averaged data.
	 * \details [output data] = [previous output data] + ([input data at i] - [input data at i-(N-1)]) / N, where N is the number of filter taps.
	 */
	void maf_ntap(float* data_out, float* data_out_prev, float data_in, float* data_mem, unsigned int noOfTaps);

	/**
	 * \brief Exponential Averager : Low-Pass IIR Filter.
	 * \param float32_t*	data_out		: pointer to latest filtered output data.
	 * \param float32_t		data_in			: latest input data.
	 * \param float32_t*	data_out_delay	: pointer to previous filtered output data.
	 * \details [output data] = [exponentially averaging co-effecient] * [input data] + [1 -  (exponentially averaging co-effecient)] * [delayed output data]
	 * \details The output data is the most recent averaged data.
	 */
	void exp_avg_filter(float* data_out, float data_in, float* data_out_delay);
};

#endif /* CFILTER_H_ */
