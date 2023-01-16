/*
 * CSensorPosition.cpp
 */

#include "CSensorPosition.h"
#include "CFilter.h"
#include "CSensorFusion.h"

CSensorPosition::CSensorPosition()
{
	this->m_senspos = 0.0F;
}

CSensorPosition::~CSensorPosition()
{

}

CSensorPosition& CSensorPosition::operator = (float32_t value)
{
    this->m_senspos = 0.0F;
    return *this;
}

void CSensorPosition::set_senspos(const SENSORPOSITION_data_t& senspos)
{
	m_senspos = senspos;
}

const SENSORPOSITION_data_t& CSensorPosition::get_senspos() const
{
	return m_senspos;
}

RC_t CSensorPosition::readTXTFile(std::string fileName, std::vector<std::string>& ListOfFiles)
{
	std::ifstream fileRead;

    std::cout << std::endl;
	fileName.append(".txt");

	try
	{
		/* Open the file for reading. */
		fileRead.open(fileName, std::ios::in);
		if(fileRead.is_open())
		{
            std::string dataFromFile;
            while(std::getline(fileRead, dataFromFile))
            {
            	//std::cout << dataFromFile << std::endl;
            	ListOfFiles.push_back(dataFromFile);
            }
			std::cout << "File " << fileName << " was successfully read." << std::endl;
		}
		else
			std::cout << "File '" << fileName << "' is not available in your directory." << std::endl;
		fileRead.close(); /* Close the file. */
	}
	catch(std::exception& e)
	{
		std::cout << "File to be imported has corrupted entry/entries." << std::endl;
		fileRead.close(); /* Close the file. */
        return RC_ERRORREADTXTFILE;
	}
    return RC_SUCCESS;
}

RC_t CSensorPosition::readCSVFile(std::string fileName)
{
	SensorPosition_t senspos;
	std::ifstream fileRead;

    std::cout << std::endl;
	std::string currFileName = fileName;
	try
	{
		/* Open the file for reading. */
		fileRead.open(currFileName + ".csv", std::ios::in);
		if(fileRead.is_open())
		{
			readSensorRawData(fileRead, currFileName);
			std::cout << "**********************************************************************************************" << std::endl;
			std::cout << "* File '" << fileName << "' was successfully updated with dead reckoning simulation results. *" << std::endl;
			std::cout << "* Check folder /SimulationResults.														   *" << std::endl;
			std::cout << "**********************************************************************************************" << std::endl;
		}
		else
			std::cout << "File '" << fileName << "' is not available in your directory." << std::endl;
		fileRead.close(); /* Close the file. */
	}
	catch(std::exception& e)
	{
		std::cout << "File to be imported has corrupted entry/entries." << std::endl;
		fileRead.close(); /* Close the file. */
        return RC_ERRORREADCSVFILE;
	}
    return RC_SUCCESS;
}

RC_t CSensorPosition::readSensorRawData(std::istream& in, std::string fileName)
{
	try
	{
			std::string dataFromFile;
			std::vector<std::string> dataUnderProcess;
			std::ofstream fileWrite;
			float raster = 0.0F;

			/* Clearing the first and second lines of data from the file as they are not required for output file. */
			getline(in, dataFromFile);
			dataFromFile.clear();		/* Clearing the first line of data i.e. Timestamp. */
			getline(in, dataFromFile);
			dataFromFile.clear();		/* Clearing the second line of data i.e. column labels. */

			this->createCSVIMUSensorDeadReckoning(fileWrite, fileName);

			while(in.peek() != EOF)
			{

				this->updateRaster(raster);
				raster += 0.005;

				getline(in, dataFromFile);
				std::stringstream strCoursesStream(dataFromFile);

				while(getline(strCoursesStream, dataFromFile, ','))
				{
					dataUnderProcess.push_back(dataFromFile);
				}

				this->updateAccScanValue((float32_t)(std::stof(dataUnderProcess[2])	* 980),
											(float32_t)(std::stof(dataUnderProcess[3])	* 980),
											(float32_t)(std::stof(dataUnderProcess[4])	* 980)
											);
				this->updateGyroScanValue((float32_t)(std::stof(dataUnderProcess[5])),
											(float32_t)(std::stof(dataUnderProcess[6])),
											(float32_t)(std::stof(dataUnderProcess[7]))
											);
				this->updateAngleScanValue((float32_t)(std::stof(dataUnderProcess[8])),
											(float32_t)(std::stof(dataUnderProcess[9])),
											(float32_t)(std::stof(dataUnderProcess[10]))
											);

				dataUnderProcess.clear();
				
				this->updateSensorFilter();
				this->calcSensorPosition();
				this->printIMUSensorDeadReckoning();
				this->writeIMUSensorDeadReckoning(fileWrite, fileName);
			}
	}
	catch(std::exception& e)
	{
			std::cout << "Corrupted data entry found to be exported to a file." << std::endl;
			return RC_ERRORREADSENSORRAWDATA;
	}

	return RC_SUCCESS;
}

RC_t CSensorPosition::createCSVIMUSensorDeadReckoning(std::ofstream& fileWrite, std::string& fileName)
{
	/* Writing the filtered data */
	std::string fileNameWrite = fileName;
#if FILTERMODE == 0U
	fileNameWrite.append("_no_filter");
#endif
#if FILTERMODE == 1U
	std::string taps = std::to_string(NO_OF_FILTER_TAPS);
	fileNameWrite += "_" + taps + "-Tap";
	fileNameWrite.append("_filtered");
#endif
#if KALMANFILTERMODE == 0U
	fileNameWrite.append("_no_kalmanfilter");
#endif
#if KALMANFILTERMODE == 1U
	fileNameWrite.append("_with_kalmanfilter");
#endif
	fileNameWrite.append("_sim.csv");
	try
	{
		/* Open the file for writing while deleting the content previously present. */
		fileWrite.open(fileNameWrite, std::ios::out | std::ios::trunc);
		if(fileWrite.is_open())
		{
			fileName.clear();
			fileName = fileNameWrite;
			std::ostream& outFile  = fileWrite;
			std::string fileColumnLabel;
			fileColumnLabel = "time,ax(cm/s^2),ay(cm/s^2),az(cm/s^2),";
#if FILTERMODE == 1U
			fileColumnLabel += "fax(cm/s^2),fay(cm/s^2),faz(cm/s^2),";
#endif
			fileColumnLabel += "gx(deg/s),gy(deg/s),gz(deg/s),";
			fileColumnLabel += "wx((deg),wy(deg),wz(deg),";
#if FILTERMODE == 1U
			fileColumnLabel += "fwz(deg),";
#endif
			fileColumnLabel += "prevZAngle(deg),";
			fileColumnLabel += "Ax(cm/s^2),Ay(cm/s^2),Vx(cm/s),Vy(cm/s),";
			fileColumnLabel += "x(cm),y(cm),phi(deg)";
#if KALMANFILTERMODE == 1U
			fileColumnLabel += ",kx(cm),ky(cm),kphi(deg)";
#endif
			outFile << fileColumnLabel << std::endl;
		}
		else
			std::cout << "File '" << fileNameWrite << "' is already opened. Close the existing instances for the file update." << std::endl;
	}
	catch(std::exception& e)
	{
		std::cout << "Corrupted data entry found to be exported to a file." << std::endl;
		fileWrite.close(); /* Close the file. */
		return RC_ERRORCREATECSVIMUSENSORDEADRECKONING;
	}
	std::cout << "File " << fileNameWrite << " was successfully written." << std::endl;
	fileWrite.close(); /* Close the file. */
	std::cout << std::endl;
	return RC_SUCCESS;
}

RC_t CSensorPosition::updateRaster(float32_t raster)
{
	this->m_senspos.raster = raster;
	return RC_SUCCESS;
}

RC_t CSensorPosition::updateAccScanValue(float32_t ax, float32_t ay, float32_t az)
{
	this->m_senspos.scanValue.acc[X_AXIS] = ax;
	this->m_senspos.scanValue.acc[Y_AXIS] = ay;
	this->m_senspos.scanValue.acc[Z_AXIS] = az;
	return RC_SUCCESS;
}
RC_t CSensorPosition::updateGyroScanValue(float32_t gx, float32_t gy, float32_t gz)
{
	this->m_senspos.scanValue.gyro[X_AXIS] = gx;
	this->m_senspos.scanValue.gyro[Y_AXIS] = gy;
	this->m_senspos.scanValue.gyro[Z_AXIS] = gz;
	return RC_SUCCESS;
}

RC_t CSensorPosition::updateAngleScanValue(float32_t wx, float32_t wy, float32_t wz)
{
	this->m_senspos.scanValue.angle[X_AXIS] = wx;
	this->m_senspos.scanValue.angle[Y_AXIS] = wy;
	this->m_senspos.scanValue.angle[Z_AXIS] = wz;
	return RC_SUCCESS;
}

RC_t CSensorPosition::updateSensorFilter()
{
	try
	{
		CFilter filter;
		//Handling prevZangle during only initial code execution. After this prevZangle will always be updated from the current z-angle
        if ((float32_t) 0.0F == this->m_senspos.preProcess.prevZangle)
        {

            this->m_senspos.filtered.angle			=	this->m_senspos.scanValue.angle[Z_AXIS];

            // The angle determined from the initial position of the IMU Sensor is taken as reference angle.
            // This reference angle is then used to set the initial angle as 0 degrees from the initial position of the IMU Sensor for all the further calculations.
            this->m_senspos.preProcess.prevZangle	=	(float32_t) this->m_senspos.filtered.angle;

			for(uint16_t iter = 0; iter < MAX_AXES; iter++)
			{
				this->m_senspos.filtered.acc[iter] = this->m_senspos.scanValue.acc[iter];
			}

#if FILTERMODE == 1U
            for(uint16_t filt_idx = 0; filt_idx < NO_OF_FILTER_TAPS; filt_idx++)
            {
                this->m_senspos.filtered.angle_filter.mem[filt_idx] = (float32_t) this->m_senspos.filtered.angle;
            }

			for(uint16_t iter = 0; iter < MAX_AXES; iter++)
			{
				for(uint16_t filt_idx = 0; filt_idx < NO_OF_FILTER_TAPS; filt_idx++)
				{
					this->m_senspos.filtered.acc_filter[iter].mem[filt_idx] = this->m_senspos.scanValue.acc[iter];
				}
			}
#endif
        }
		else
		{
			for(uint16_t iter = 0; iter < MAX_AXES; iter++)
			{
#if FILTERMODE == 0U
				this->m_senspos.filtered.acc[iter] = this->m_senspos.scanValue.acc[iter];
#endif
#if FILTERMODE == 1U
				filter.maf_ntap(&this->m_senspos.filtered.acc[iter],
            					this->m_senspos.scanValue.acc[iter],
								this->m_senspos.filtered.acc_filter[iter].mem,
								(uint16_t) NO_OF_FILTER_TAPS
								);
#endif			
			}

#if FILTERMODE == 0U
			this->m_senspos.filtered.angle = this->m_senspos.scanValue.angle[Z_AXIS];
#endif

#if FILTERMODE == 1U
			filter.maf_ntap(&this->m_senspos.filtered.angle,
							this->m_senspos.scanValue.angle[Z_AXIS],
							this->m_senspos.filtered.angle_filter.mem,
							(uint16_t) NO_OF_FILTER_TAPS
							);
#endif
		}
	}
	catch(std::exception& e)
	{
			std::cout << "Calculation Error in updateSensorFilter()" << std::endl;
			return RC_ERRORUPDATESENSORFILTER;
	}

	return RC_SUCCESS;
}

RC_t CSensorPosition::calcSensorPosition()
{
	try
	{
#if LINEAR_MODE == 1U
    // Calculate Phi
    this->m_senspos.preProcess.pos.phi += (this->m_senspos.filtered.angle - this->m_senspos.preProcess.prevZangle);

    this->m_senspos.preProcess.prevZangle = (float32_t) this->m_senspos.filtered.angle;

    // Calculate new position
	// Gyroscope values are used to determine the movement
    if (this->m_senspos.scanValue.gyro[X_AXIS]		!= (float32_t) 0.0F
		|| this->m_senspos.scanValue.gyro[Y_AXIS]	!= (float32_t) 0.0F
		|| this->m_senspos.scanValue.gyro[Z_AXIS]	!= (float32_t) 0.0F)
    {
        double thetaInRad = 0.0F;

        thetaInRad = this->m_senspos.preProcess.pos.phi * M_PI / 180; //convert to radians

        // Apply Phi correction to acceleration components ax and ay
        this->m_senspos.preProcess.acc[X_AXIS]
                = this->m_senspos.filtered.acc[X_AXIS] * ((float32_t) cos(thetaInRad)) - this->m_senspos.filtered.acc[Y_AXIS] * ((float32_t) sin(thetaInRad));
        this->m_senspos.preProcess.acc[Y_AXIS]
                = this->m_senspos.filtered.acc[X_AXIS] * ((float32_t) sin(thetaInRad)) + this->m_senspos.filtered.acc[Y_AXIS] * ((float32_t) cos(thetaInRad));

		// Calculate position
        //the formula, {pos = (initial velocity * time) + (0.5 * acceleration * time * time)} is calculated in 2 steps
        // 1. pos (position) = initial velocity * time
        this->m_senspos.preProcess.pos.x += this->m_senspos.preProcess.vel[X_AXIS] * (float32_t) CYCLETIME;
        this->m_senspos.preProcess.pos.y += this->m_senspos.preProcess.vel[Y_AXIS] * (float32_t) CYCLETIME;
		// update velocity = acceleration * time
        this->m_senspos.preProcess.vel[X_AXIS] += this->m_senspos.preProcess.acc[X_AXIS] * (float32_t) CYCLETIME;
        this->m_senspos.preProcess.vel[Y_AXIS] += this->m_senspos.preProcess.acc[Y_AXIS] * (float32_t) CYCLETIME;
		// 2. update pos (position) += 0.5 * acceleration * time * time
        this->m_senspos.preProcess.pos.x += (float32_t) 0.5F * this->m_senspos.preProcess.acc[X_AXIS]  * (float32_t) CYCLETIMESQ;
        this->m_senspos.preProcess.pos.y += (float32_t) 0.5F * this->m_senspos.preProcess.acc[Y_AXIS]  * (float32_t) CYCLETIMESQ;

        updateKalmanPosition();
    }
    else
    {
        this->m_senspos.preProcess.vel[X_AXIS]  =   (float32_t) 0.0F;
        this->m_senspos.preProcess.vel[Y_AXIS]  =   (float32_t) 0.0F;
        this->m_senspos.preProcess.acc[X_AXIS]  =   (float32_t) 0.0F;
        this->m_senspos.preProcess.acc[Y_AXIS]  =   (float32_t) 0.0F;
    }
#endif
	}
	catch(std::exception& e)
	{
			std::cout << "Calculation Error in calcSensorPosition()" << std::endl;
			return RC_ERRORCALCSENSORPOSITION;
	}

	return RC_SUCCESS;
}

RC_t CSensorPosition::updateKalmanPosition()
{
	try
	{
#if KALMANFILTERMODE == 1U
       CSensorFusion sensFusion;

	   sensFusion.sensorfusion_kalman_predict(this->m_senspos);
	   sensFusion.sensorfusion_kalman_update(this->m_senspos);

#endif
	}
	catch(std::exception& e)
	{
			std::cout << "Calculation Error in updateKalmanPosition()" << std::endl;
			return RC_ERRORUPDATEKALMANPOSITION;
	}

	return RC_SUCCESS;
}

RC_t CSensorPosition::printIMUSensorDeadReckoning() const
{
	try
	{
		std::cout << "time : " 						<< this->m_senspos.raster 						<< std::endl;
		std::cout << "ax(g) : " 					<< this->m_senspos.scanValue.acc[X_AXIS] 		<< std::endl;
		std::cout << "ay(g) : " 					<< this->m_senspos.scanValue.acc[Y_AXIS] 		<< std::endl;
		std::cout << "az(g) : " 					<< this->m_senspos.scanValue.acc[Z_AXIS] 		<< std::endl;
#if FILTERMODE == 1U
		std::cout << "filtered ax(g) : " 			<< this->m_senspos.filtered.acc[X_AXIS]		<< std::endl;
		std::cout << "filtered ay(g) : " 			<< this->m_senspos.filtered.acc[Y_AXIS] 		<< std::endl;
		std::cout << "filtered az(g) : " 			<< this->m_senspos.filtered.acc[Z_AXIS] 		<< std::endl;
#endif
		std::cout << "wx(deg/s) : " 				<< this->m_senspos.scanValue.gyro[X_AXIS] 		<< std::endl;
		std::cout << "wy(deg/s) : " 				<< this->m_senspos.scanValue.gyro[Y_AXIS] 		<< std::endl;
		std::cout << "wz(deg/s) : " 				<< this->m_senspos.scanValue.gyro[Z_AXIS] 		<< std::endl;
		std::cout << "AngleX(deg) : " 				<< this->m_senspos.scanValue.angle[X_AXIS] 	<< std::endl;
		std::cout << "AngleY(deg) : " 				<< this->m_senspos.scanValue.angle[Y_AXIS] 	<< std::endl;
		std::cout << "AngleZ(deg) : " 				<< this->m_senspos.scanValue.angle[Z_AXIS] 	<< std::endl;
#if FILTERMODE == 1U
		std::cout << "filtered wz(deg/s) : " 		<< this->m_senspos.filtered.angle 				<< std::endl;
#endif
		std::cout << "prevZAngle(deg)" 				<< this->m_senspos.preProcess.prevZangle 		<< std::endl;
		std::cout << "Ax : " 						<< this->m_senspos.preProcess.acc[X_AXIS] 		<< std::endl;
		std::cout << "Ay : " 						<< this->m_senspos.preProcess.acc[Y_AXIS] 		<< std::endl;
		std::cout << "Vx : " 						<< this->m_senspos.preProcess.vel[X_AXIS]		<< std::endl;
		std::cout << "Vy : " 						<< this->m_senspos.preProcess.vel[Y_AXIS] 		<< std::endl;
		std::cout << "Position x : " 				<< this->m_senspos.preProcess.pos.x 			<< std::endl;
		std::cout << "Position y : " 				<< this->m_senspos.preProcess.pos.y 			<< std::endl;
		std::cout << "Position phi : " 				<< this->m_senspos.preProcess.pos.phi 			<< std::endl;
#if KALMANFILTERMODE == 1U
		std::cout << "Kalman Position x : " 		<< this->m_senspos.kalman.pos.x 				<< std::endl;
		std::cout << "Kalman Position y : " 		<< this->m_senspos.kalman.pos.y 				<< std::endl;
		std::cout << "Kalman Position phi : " 		<< this->m_senspos.kalman.pos.phi 				<< std::endl;
#endif
	}
	catch(std::exception& e)
	{
		std::cout << "Corrupted data found and hence could not print." << std::endl;
		return RC_ERRORPRINTIMUSENSORDEADRECKONING;
	}
	return RC_SUCCESS;
}

RC_t CSensorPosition::writeIMUSensorDeadReckoning(std::ofstream& fileWrite, const std::string fileName)
{
	/* Writing the filtered data */
	std::string fileNameWrite = fileName;
	try
	{
		/* Open the file for writing while deleting the content previously present. */
		fileWrite.open(fileNameWrite, std::ios::out | std::ios::app);
		if(fileWrite.is_open())
		{
			std::ostream& outFile  = fileWrite;

			outFile << this->m_senspos.raster 						<< ",";
			outFile << this->m_senspos.scanValue.acc[X_AXIS] 		<< ",";
			outFile << this->m_senspos.scanValue.acc[Y_AXIS] 		<< ",";
			outFile << this->m_senspos.scanValue.acc[Z_AXIS] 		<< ",";
#if FILTERMODE == 1U
			outFile << this->m_senspos.filtered.acc[X_AXIS]			<< ",";
			outFile << this->m_senspos.filtered.acc[Y_AXIS]			<< ",";
			outFile << this->m_senspos.filtered.acc[Z_AXIS]			<< ",";
#endif
			outFile << this->m_senspos.scanValue.gyro[X_AXIS] 		<< ",";
			outFile << this->m_senspos.scanValue.gyro[Y_AXIS] 		<< ",";
			outFile << this->m_senspos.scanValue.gyro[Z_AXIS] 		<< ",";
			outFile << this->m_senspos.scanValue.angle[X_AXIS]		<< ",";
			outFile << this->m_senspos.scanValue.angle[Y_AXIS]		<< ",";
			outFile << this->m_senspos.scanValue.angle[Z_AXIS]		<< ",";
#if FILTERMODE == 1U
			outFile << this->m_senspos.filtered.angle 				<< ",";
#endif
			outFile << this->m_senspos.preProcess.prevZangle 		<< ",";
			outFile << this->m_senspos.preProcess.acc[X_AXIS] 		<< ",";
			outFile << this->m_senspos.preProcess.acc[Y_AXIS] 		<< ",";
			outFile << this->m_senspos.preProcess.vel[X_AXIS]		<< ",";
			outFile << this->m_senspos.preProcess.vel[Y_AXIS] 		<< ",";
			outFile << this->m_senspos.preProcess.pos.x				<< ",";
			outFile << this->m_senspos.preProcess.pos.y				<< ",";
			outFile << this->m_senspos.preProcess.pos.phi 			;
#if KALMANFILTERMODE == 1U
			outFile << ",";
			outFile << this->m_senspos.kalman.pos.x					<< ",";
			outFile << this->m_senspos.kalman.pos.y					<< ",";
			outFile << this->m_senspos.kalman.pos.phi				;
#endif
			outFile << std::endl;

		}
		else
					std::cout << "File '" << fileNameWrite << "' is already opened. Close the existing instances for the file update." << std::endl;
	}
	catch(std::exception& e)
	{
		std::cout << "Corrupted data entry found to be exported to a file." << std::endl;
		fileWrite.close(); /* Close the file. */
		return RC_ERRORWRITEIMUSENSORDEADRECKONING;
	}
	std::cout << "File " << fileNameWrite << " was successfully written." << std::endl;
	fileWrite.close(); /* Close the file. */
	std::cout << std::endl;
	return RC_SUCCESS;
}

