/*
 * CSensorPosition.h
 */

#ifndef CSENSORPOSITION_H_
#define CSENSORPOSITION_H_

#include "common.h"
#include "CIMUSensor.h"

class CSensorPosition
{
	SENSORPOSITION_data_t m_senspos;
public:
	CSensorPosition();
	virtual ~CSensorPosition();
	CSensorPosition& operator = (float32_t value);
	void set_senspos(const SENSORPOSITION_data_t& senspos);
	const SENSORPOSITION_data_t& get_senspos() const;
	RC_t readTXTFile(std::string fileName, std::vector<std::string>& ListOfFiles);
	RC_t readCSVFile(std::string fileName);
	RC_t readSensorRawData(std::istream& in, std::string fileName);
	RC_t createCSVIMUSensorDeadReckoning(std::ofstream& fileWrite, std::string& fileName);
	RC_t updateRaster(float32_t raster);
	RC_t updateAccScanValue(float32_t ax, float32_t ay, float32_t az);
	RC_t updateGyroScanValue(float32_t gx, float32_t gy, float32_t gz);
	RC_t updateAngleScanValue(float32_t wx, float32_t wy, float32_t wz);
	RC_t updateSensorFilter();
	RC_t calcSensorPosition();
	RC_t updateKalmanPosition();
	RC_t printIMUSensorDeadReckoning() const;
	RC_t writeIMUSensorDeadReckoning(std::ofstream& fileWrite, const std::string fileName);
};

typedef CSensorPosition SensorPosition_t;

#endif /* CSENSORPOSITION_H_ */
