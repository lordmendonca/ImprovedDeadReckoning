# ImprovedDeadReckoning
Team project SS2022

## List of Entities
1. Simulation Tool for improved dead reckoning using WIT IMU sensor using the Kalman filter.
2. Report - Sensor fusion of an Inertial Motion Unit sensor and a Faulhaber decoder using the Kalman filter for improved dead reckoning.

## 1. Simulation Tool for improved dead reckoning using WIT IMU sensor using the Kalman filter

### Description
Run 'RunSimulation.py'.
Tool Used : Visual Studio Code - Python extension for Visual Studio Code by Microsoft.
Converts WIT sensor logged data in .txt format into .csv format.
Simulates the software written for "Improvement Dead-reckoning" based on the data of WIT Sensor.
This code is only applicable for the data logged using the software provided by the vendor of WIT Sensor. 
The csv format uses comma seperation format.
Place all the .txt files in the 'TestDataTXT_WITSensor' subfolder.
All the converted files will be generated in 'TestDataCSV_WITSensor' sub-folder.
Simulation results will be generated in 'SimulationResults' sub-folder.
When any changes in 'IMUSensor_DeadReckoning_Sim' are made, a standalone build to generate new .exe is a must.
Tool Used : Visual Studio Code - C/C++ extension pack for Visual Studio Code by Microsoft.

## 2. Report - Sensor fusion of an Inertial Motion Unit sensor and a Faulhaber decoder using the Kalman filter for improved dead reckoning.

### Description
Sensor fusion using the Kalman filter for improved deadreckoning
