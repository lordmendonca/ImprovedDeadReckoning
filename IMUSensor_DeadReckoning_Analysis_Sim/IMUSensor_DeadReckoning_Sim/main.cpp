#include "common.h"
#include "CIMUSensor.h"
#include "CSensorPosition.h"
#include "CKalmanFilter.h"
#include "CSensorFusion.h"

int main()
{
    std::cout << "**********************************************************************************" << std::endl;
    std::cout << "*                        start imusensor_deadreckoning_sim                       *" << std::endl;
    std::cout << "**********************************************************************************" << std::endl;

    std::string                 fileName;
    std::vector<std::string>    fileList;
    SensorPosition_t			sensorPosition;

    sensorPosition.readTXTFile("listOfFiles",fileList);

    std::vector<std::string>::iterator fileListItr;
    for(fileListItr = fileList.begin(); fileListItr != fileList.end(); fileListItr++)
    {
    	std::cout << *fileListItr << std::endl;
    	fileName		= *fileListItr;
    	sensorPosition	= 0.0F;
    	sensorPosition.readCSVFile(fileName);
    }
    std::cout << std::endl;

    std::cout << "**********************************************************************************" << std::endl;
    std::cout << "*                        end imusensor_deadreckoning_sim                         *" << std::endl;
    std::cout << "**********************************************************************************" << std::endl;

    return 0;
}
