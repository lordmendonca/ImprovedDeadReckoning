import glob
import os
import shutil

def DeleteExistingCSVFilesInSimResults() -> None :
    try:
        path = os.path.abspath(r"SimulationResults")

        # retrieve file list
        filelist=glob.glob(path + "/*.csv")
        for file in filelist:
            print("Deleting ", str(file))
            # remove file with full paths as shutil.move()
            os.remove(str(file))
            print("DONE.")

    except OSError as e:
        print ("Error: %s - %s." % (e.filename, e.strerror))

def DeleteExistingCSVFilesInTestDataCSV_WITSensor() -> None :
    try:
        path = os.path.abspath(r"TestDataCSV_WITSensor")

        # retrieve file list
        filelist=glob.glob(path + "/*.csv")
        for file in filelist:
            print("Deleting ", str(file))
            # remove file with full paths as shutil.move()
            os.remove(str(file))
            print("DONE.")

    except OSError as e:
        print ("Error: %s - %s." % (e.filename, e.strerror))

def DeleteExistingListOfFiles() -> None:
    try:
        path = os.path.abspath(r"TestDataCSV_WITSensor\listOfFiles.txt")
        print("Deleting ", str(path))
        os.remove(path)
        print("DONE.")
    except OSError as e:
        print ("Error: %s - %s." % (e.filename, e.strerror))

# Conversion of WIT sensor logged data in .txt format into .csv format.
# This code is only applicable to the data logged using the software provided by the vendor of WIT Sensor.
# The csv format uses comma seperation format.

def ConvertWITSensorDataTXTFileFormatToCSVFileFormat() -> None :
    try:
        path = os.path.abspath(r"TestDataTXT_WITSensor")
        outputPathName = path + "\output"
        if not os.path.exists(outputPathName):
            os.mkdir(outputPathName)
        fileName = "listOfFiles.txt"
    
        fileReadHandle  =   open(outputPathName + "/" + fileName,"w")
        filelist = os.listdir(str(path))
        for file in filelist:
            if "output" != str(file):
                fileNameTrim        = str(file).partition(".txt")
                fileNameOnly        = str(fileNameTrim[0])
                fileReadHandle.write(fileNameOnly + "\n")       
        fileReadHandle.close()
    
        fileWriteHandle = open(outputPathName + "/" + fileName,"r")
        while True:
            csvFileName = fileWriteHandle.readline().rstrip("\n")
            txtFileName = csvFileName
            if csvFileName == '':
                break
            else:
                txtFileHandler = open(path + "/" + txtFileName + ".txt", "r")
                csvFileHandler = open(outputPathName + "/" + csvFileName + ".csv", "w")
                content = txtFileHandler.read()
                editContent = content.replace('	 ',',')
                editContent = content.replace('	',',')
                editContent = content.replace('	',',')
                csvFileHandler.write(editContent)
                print(csvFileName + ".csv generated successfully.")
                csvFileHandler.close()
                txtFileHandler.close()
    
        fileWriteHandle.close()
        print('Conversion successful.')
    
    except OSError as e:
        print('Conversion Unsuccessful!!!')
        print ("Error: %s - %s." % (e.filename, e.strerror))

def MoveWITSensorDataCSVFileFormat() -> None :
    try:
        srcpath = os.path.abspath(r"TestDataTXT_WITSensor\output")
        dstpath = os.path.abspath(r"TestDataCSV_WITSensor")
    
        # retrieve file list
        filelist=glob.glob(srcpath + "/*.csv")
        for file in filelist:
            print("Moving ", str(srcpath), " to ", str(dstpath))
            # move file with full paths as shutil.move()
            shutil.move(file,dstpath)
            print("DONE.")
    
    except OSError as e:
        print ("Error: %s - %s." % (e.filename, e.strerror))

def MoveListOfFilesAndDeleteOutputFolder() -> None:
    try:
        srcpath = os.path.abspath(r"TestDataTXT_WITSensor\output\listOfFiles.txt")
        dstpath = os.path.abspath(r"TestDataCSV_WITSensor")
        cpypath = os.path.abspath(r"")
        print("Moving ", str(srcpath), " to ", str(dstpath))
        shutil.move(srcpath, dstpath)
        print("Copying ", str(dstpath), " to ", str(cpypath))
        shutil.copy(dstpath + "\listOfFiles.txt", cpypath)
        print("DONE.")
        
    except OSError as e:
        print ("Error: %s - %s." % (e.filename, e.strerror))


    ## Try to remove tree; if failed show an error using try...except on screen
    folderpath = os.path.abspath(r"TestDataTXT_WITSensor\output")
    try:
        print("Deleting ", str(folderpath))
        shutil.rmtree(folderpath)
        print("DONE.")
    except OSError as e:
        print ("Error: %s - %s." % (e.filename, e.strerror))

def CopyWITSensorDataCSVFileFormat() -> None :
    try:    
        srcpath = os.path.abspath(r"TestDataCSV_WITSensor")
        dstpath = os.path.abspath(r"")
    
        # retrieve file list
        filelist=glob.glob(srcpath + "/*.csv")
        for file in filelist:
            print("Copying ", str(srcpath), " to ", str(dstpath))
            # move file with full paths as shutil.move()
            shutil.copy(file,dstpath)
            print("DONE.")
    
    except OSError as e:
        print ("Error: %s - %s." % (e.filename, e.strerror))

def MoveRunSimulationAnalysisResult() -> None:
    try:
        srcpath = os.path.abspath(r"")
        dstpath = os.path.abspath(r"SimulationResults")
    
        # retrieve file list
        filelist=glob.glob(srcpath + "/*_sim.csv")
        for file in filelist:
            print("Moving ", str(srcpath), " to ", str(dstpath))
            # move file with full paths as shutil.move()
            shutil.move(file,dstpath)
            print("DONE.")
            
    except OSError as e:
        print ("Error: %s - %s." % (e.filename, e.strerror))

def DeleteWITSensorDataCSVFileFormat() -> None :
    try:
        path = os.path.abspath(r"")
    
        # retrieve file list
        filelist=glob.glob(path + "/*.csv")
        for file in filelist:
            print("Deleting ", str(file))
            # remove file with full paths as shutil.move()
            os.remove(str(file))
            print("DONE.")
    
    except OSError as e:
        print ("Error: %s - %s." % (e.filename, e.strerror))

def DeleteListOfFiles() -> None:
    try:
        path = os.path.abspath(r"listOfFiles.txt")
        print("Deleting ", str(path))
        os.remove(path)
        print("DONE.")
    except OSError as e:
        print ("Error: %s - %s." % (e.filename, e.strerror))