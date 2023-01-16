
import os
from ProcessMethods import *

def main():
    try:
        DeleteExistingCSVFilesInSimResults()
        DeleteExistingCSVFilesInTestDataCSV_WITSensor()
        DeleteExistingListOfFiles()
        ConvertWITSensorDataTXTFileFormatToCSVFileFormat()
        MoveWITSensorDataCSVFileFormat()
        MoveListOfFilesAndDeleteOutputFolder()
        CopyWITSensorDataCSVFileFormat()
        os.system(r"IMUSensor_DeadReckoning_Sim\main.exe")
        MoveRunSimulationAnalysisResult()
        DeleteWITSensorDataCSVFileFormat()
        DeleteListOfFiles()
        print("**********************************************************************************************************")
        print("*                                Simulation Successful                                                   *")
        print("**********************************************************************************************************")
    except OSError as e:
        print("**********************************************************************************************************")
        print("*                                Simulation Unsuccessful!!!                                              *")
        print("**********************************************************************************************************")
        print ("Error: %s - %s." % (e.filename, e.strerror))

if __name__ == "__main__":
    main()