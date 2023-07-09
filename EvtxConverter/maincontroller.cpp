#include "maincontroller.h"

MainController::MainController(QWidget *parent) : QWidget(parent){
    checkDirectories();
}

//Get file path for EVTX file
void MainController::ce_SelectFile(){
    convertEvtxFileName = QFileDialog::getOpenFileName(Q_NULLPTR, tr("Select File"), "");
    QFileInfo fileInfo(convertEvtxFileName);
    convertEvtxFullFilePath  = fileInfo.filePath().trimmed();

    emit filePathToQml(convertEvtxFullFilePath);
    emit dirPathToQml("");
}

//Get directory path for EVTX files
void MainController::ce_SelectDir(){
    QString dir = QFileDialog::getExistingDirectory(Q_NULLPTR, tr("Select Directory"), "/home", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    emit dirPathToQml(dir);
    emit filePathToQml("");
}

//Get path where converted files will be stored
void MainController::ce_SaveToPath(){
    QString dir = QFileDialog::getExistingDirectory(Q_NULLPTR, tr("Select Directory"), "/home", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    emit saveToPathToQml(dir);
}

//Convert an EVTX file to JSON, XML, or CSV
void MainController::fileConvertEvtx(QString convertType, QString fPah, QString savePath, QString iFileName ){
    if(convertType == "JSON"){
        emit fileConvertEvtxStatus("EVTX to JSON conversion process starting " + QDateTime::currentDateTime().toString("MM/dd/yyyy h:mm:ss ap"));
        emit fileConvertEvtxStatus("Please Wait....");

        QStringList args;
        args << "Set-Location -Path " + docsFolder + "/EvtxConverter/EvtxeCmd/;"
             << "./EvtxECmd.exe -f " + fPah.trimmed() +  " --json " +  savePath.trimmed() + " --jsonf " + iFileName.trimmed() + ".json";
        connect(&convertEvtxToJsonProcess, (void(QProcess::*)(int))&QProcess::finished, [=]{updateEvtxConvertStatus();});
        convertEvtxToJsonProcess.start("powershell", args);
    }
    else if(convertType == "Full JSON"){
        emit fileConvertEvtxStatus("EVTX to FUll JSON conversion process starting " + QDateTime::currentDateTime().toString("MM/dd/yyyy h:mm:ss ap"));
        emit fileConvertEvtxStatus("Please Wait....");

        QStringList args;
        args << "Set-Location -Path " + docsFolder + "/EvtxConverter/EvtxeCmd/;"
             << "./EvtxECmd.exe -f " + fPah.trimmed() +  " --fj --json " +  savePath.trimmed() + " --jsonf " + iFileName.trimmed() + ".json";
        connect(&convertEvtxToJsonProcess, (void(QProcess::*)(int))&QProcess::finished, [=]{updateEvtxConvertStatus();});
        convertEvtxToJsonProcess.start("powershell", args);
    }
    else if(convertType == "XML"){
        emit fileConvertEvtxStatus("EVTX to XML conversion process starting " + QDateTime::currentDateTime().toString("MM/dd/yyyy h:mm:ss ap"));
        emit fileConvertEvtxStatus("Please Wait....");

        QStringList args;
        args << "Set-Location -Path " + docsFolder + "/EvtxConverter/EvtxeCmd/;"
             << "./EvtxECmd.exe -f " + fPah.trimmed() +  " --xml " +  savePath.trimmed() + " --xmlf " + iFileName.trimmed() + ".xml";
        connect(&convertEvtxToXmlProcess, (void(QProcess::*)(int))&QProcess::finished, [=]{updateEvtxConvertStatus();});
        convertEvtxToXmlProcess.start("powershell", args);
    }
    else if(convertType == "CSV"){
        emit fileConvertEvtxStatus("EVTX to CSV conversion process starting " + QDateTime::currentDateTime().toString("MM/dd/yyyy h:mm:ss ap"));
        emit fileConvertEvtxStatus("Please Wait....");

        QStringList args;
        args << "Set-Location -Path " + docsFolder + "/EvtxConverter/EvtxeCmd/;"
             << "./EvtxECmd.exe -f " + fPah.trimmed() +  " --csv " +  savePath.trimmed() + " --csvf " + iFileName.trimmed() + ".csv";

        connect(&convertEvtxToCsvProcess, (void(QProcess::*)(int))&QProcess::finished, [=]{updateEvtxConvertStatus();});
        convertEvtxToCsvProcess.start("powershell", args);
    }
    else{
        //error
    }
}

//Convert a directory of evtx files to a single json, xml, or csv
void MainController::dirConvertEvtx(QString convertType, QString fPah, QString savePath){
    if(convertType == "JSON"){
        emit fileConvertEvtxStatus("EVTX to JSON conversion process starting " + QDateTime::currentDateTime().toString("MM/dd/yyyy h:mm:ss ap"));
        QStringList args;
        //Set a permanent location for deployment
        args << "Set-Location -Path " + docsFolder + "/EvtxConverter/EvtxeCmd/;"
             << "./EvtxECmd.exe -d " + fPah.trimmed() +  " --json " +  savePath.trimmed();
        connect(&convertEvtxToJsonProcess, (void(QProcess::*)(int))&QProcess::finished, [=]{updateEvtxConvertStatus();});
        convertEvtxToJsonProcess.start("powershell", args);
    }
    else if(convertType == "Full JSON"){
        emit fileConvertEvtxStatus("EVTX to FUll JSON conversion process starting " + QDateTime::currentDateTime().toString("MM/dd/yyyy h:mm:ss ap"));
        emit fileConvertEvtxStatus("Please Wait....");
        QStringList args;
        //Set a permanent location for deployment
        args << "Set-Location -Path " + docsFolder + "/EvtxConverter/EvtxeCmd/;"
             << "./EvtxECmd.exe -d " + fPah.trimmed() +  " --fj --json " +  savePath.trimmed() + " --jsonf ";
        connect(&convertEvtxToFullJsonProcess, (void(QProcess::*)(int))&QProcess::finished, [=]{updateEvtxConvertStatus();});
        convertEvtxToFullJsonProcess.start("powershell", args);
    }
    else if(convertType == "XML"){
        emit fileConvertEvtxStatus("EVTX to XML conversion process starting " + QDateTime::currentDateTime().toString("MM/dd/yyyy h:mm:ss ap"));
        emit fileConvertEvtxStatus("Please Wait....");

        QStringList args;
        args << "Set-Location -Path " + docsFolder + "/EvtxConverter/EvtxeCmd/;"
             << "./EvtxECmd.exe -d " + fPah.trimmed() +  " --xml " + savePath.trimmed();
        connect(&convertEvtxToXmlProcess, (void(QProcess::*)(int))&QProcess::finished, [=]{updateEvtxConvertStatus();});
        convertEvtxToXmlProcess.start("powershell", args);
    }
    else if(convertType == "CSV"){
        emit fileConvertEvtxStatus("EVTX to CSV conversion process starting " + QDateTime::currentDateTime().toString("MM/dd/yyyy h:mm:ss ap"));
        emit fileConvertEvtxStatus("Please Wait....");

        QStringList args;
        args << "Set-Location -Path " + docsFolder + "/EvtxConverter/EvtxeCmd/;"
             << "./EvtxECmd.exe -d " + fPah.trimmed() +  " --csv " +  savePath.trimmed();
        connect(&convertEvtxToCsvProcess, (void(QProcess::*)(int))&QProcess::finished, [=]{updateEvtxConvertStatus();});
        convertEvtxToCsvProcess.start("powershell", args);
    }
    else{
        //error
    }
}

//Convert a directory of Evtx files to individual JSON, XML, or CSV files
void MainController::dirConvertEachEvtx(QString convertType, QString savePath){
    emit fileConvertEvtxStatus("EVTX file conversion process starting " + QDateTime::currentDateTime().toString("MM/dd/yyyy h:mm:ss ap"));
    emit fileConvertEvtxStatus("Please Wait....");
    emit fileNameToQml("");
    emit filePathToQml("");
    emit dirPathToQml("");
    emit saveToPathToQml("");
    emit dirPathSepToQml("");

    foreach(const QString &evtxFile, listOfFilesToConvert){
        QFileInfo fileInfo(evtxFile);
        QString curFileName = fileInfo.fileName().trimmed();
        QString curFullFileName = fileInfo.fileName().trimmed();
        curFileName.replace(".evtx","");

        if(convertType == "JSON"){            
            QProcess *convertEachEvtxFileProcess = new QProcess();
            QStringList args;
            args << "Set-Location -Path " + docsFolder + "/EvtxConverter/EvtxeCmd/;"
                 << "./EvtxECmd.exe -f " + evtxFile.trimmed() +  " --json " +  savePath.trimmed() + " --jsonf " + curFileName + ".json";
            connect(convertEachEvtxFileProcess, (void(QProcess::*)(int))&QProcess::finished, [=]{updateIndividualEvtxConvertStatus(curFullFileName);});
            convertEachEvtxFileProcess->start("powershell", args);
        }
        else if(convertType == "Full JSON"){
            QProcess *convertEachEvtxFileProcess2 = new QProcess();
            QStringList args;
            args << "Set-Location -Path " + docsFolder + "/EvtxConverter/EvtxeCmd/;"
                 << "./EvtxECmd.exe -f " + evtxFile.trimmed() +  " --fj --json " +  savePath.trimmed() + " --jsonf " + curFileName + ".json";
            connect(convertEachEvtxFileProcess2, (void(QProcess::*)(int))&QProcess::finished, [=]{updateIndividualEvtxConvertStatus(curFullFileName);});
            convertEachEvtxFileProcess2->start("powershell", args);
        }
        else if(convertType == "XML"){
            QProcess *convertEachEvtxFileProcess3 = new QProcess();
            QStringList args;
            args << "Set-Location -Path " + docsFolder + "/EvtxConverter/EvtxeCmd/;"
                 << "./EvtxECmd.exe -f " + evtxFile.trimmed() +  " --xml " +  savePath.trimmed() + " --xmlf " + curFileName + ".xml";
            connect(convertEachEvtxFileProcess3, (void(QProcess::*)(int))&QProcess::finished, [=]{updateIndividualEvtxConvertStatus(curFullFileName);});
            convertEachEvtxFileProcess3->start("powershell", args);
        }
        else if(convertType == "CSV"){
            QProcess *convertEachEvtxFileProcess3 = new QProcess();
            QStringList args;
            args << "Set-Location -Path " + docsFolder + "/EvtxConverter/EvtxeCmd/;"
                 << "./EvtxECmd.exe -f " + evtxFile.trimmed() +  " --csv " +  savePath.trimmed() + " --csvf " + curFileName + ".csv";
            connect(convertEachEvtxFileProcess3, (void(QProcess::*)(int))&QProcess::finished, [=]{updateIndividualEvtxConvertStatus(curFullFileName);});
            convertEachEvtxFileProcess3->start("powershell", args);
        }
    }
}

//Select a directory and store the path of each file to be converted to individual JSON, XML, or CSV files
void MainController::selectDirConvertEachEvtx(){
    listOfFilesToConvert.clear();
    QString path = QFileDialog::getExistingDirectory(Q_NULLPTR, tr("Select Directory"), "/home", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    emit dirPathSepToQml(path);
    QDir dir(path);
    dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    dir.setSorting(QDir::Size | QDir::Reversed);

    QFileInfoList list = dir.entryInfoList();
    for (int i = 0; i < list.size(); ++i) {
        QFileInfo fileInfo = list.at(i);
        listOfFilesToConvert << fileInfo.absoluteFilePath();
    }
}

//Update the UI when comversion is complete
void MainController::updateEvtxConvertStatus(){
    emit fileConvertEvtxStatus("Conversion completed @ " +  QDateTime::currentDateTime().toString("MM/dd/yyyy h:mm:ss ap"));
    emit fileNameToQml("");
    emit filePathToQml("");
    emit dirPathToQml("");
    emit saveToPathToQml("");
    emit dirPathSepToQml("");
}

//Update the UI when comversion is complete for each file
void MainController::updateIndividualEvtxConvertStatus(QString fileName){
    emit fileConvertEvtxStatus("Conversion for: " + fileName +  " completed @ " +  QDateTime::currentDateTime().toString("MM/dd/yyyy h:mm:ss ap"));
}

//Get the Documents path. Check to see if directories exist. Create directories if needed.
void MainController::checkDirectories(){

    //Get the Documents path and create the main EvtxConverter directory
    docsFolder = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    QDir docsDir(docsFolder + "/EvtxConverter");

    if(!docsDir.exists()){
        QDir().mkdir(docsFolder + "/EvtxConverter/");
    }

    //Check if the EvtxeCmd folder exists in the Documents\EvtxConverter folder
    QStringList args;
    args << "Test-Path -Path " + docsFolder + "/EvtxConverter/EvtxeCmd;";
    checkEvtxeCmdPathProcess.connect(&checkEvtxeCmdPathProcess, &QProcess::readyReadStandardOutput, this, &MainController::evtxCmdFolderExistsResponse);
    checkEvtxeCmdPathProcess.start("powershell", args);    
}

//Copy EvtxeCmd files to docs folder if not already there
void MainController::evtxCmdFolderExistsResponse(){
    QByteArray ba  = checkEvtxeCmdPathProcess.readAllStandardOutput().trimmed();
    QString response = QString(ba);

    if(response == "true"){
        return;
    }
    else{
        QString targetDir = "C:/EvtxConverter/EvtxeCmd/";
        QStringList args;
        args << "Copy-Item -Path "  + targetDir +  " -Destination " + docsFolder + "/EvtxConverter/EvtxeCmd/ -Recurse";
        moveEvtxeCmdToDocsProcess.start("powershell", args);
    }                    
}
