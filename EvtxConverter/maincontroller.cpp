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

        //convertEvtxToJsonProcess.connect(&convertEvtxToJsonProcess, &QProcess::readyReadStandardOutput, this, &MainController::processConvertStdOutInfo);
        //convertEvtxToJsonProcess.connect(&convertEvtxToJsonProcess, &QProcess::readyReadStandardError, this, &MainController::processConvertErrorInfo);
        connect(&convertEvtxToJsonProcess, (void(QProcess::*)(int))&QProcess::finished, [=]{updateEvtxConvertStatus();});
        convertEvtxToJsonProcess.start("powershell", args);
    }
    else if(convertType == "Full JSON"){
        emit fileConvertEvtxStatus("EVTX to FUll JSON conversion process starting " + QDateTime::currentDateTime().toString("MM/dd/yyyy h:mm:ss ap"));
        emit fileConvertEvtxStatus("Please Wait....");

        QStringList args;
        args << "Set-Location -Path " + docsFolder + "/EvtxConverter/EvtxeCmd/;"
             << "./EvtxECmd.exe -f " + fPah.trimmed() +  " --fj --json " +  savePath.trimmed() + " --jsonf " + iFileName.trimmed() + ".json";

        //convertEvtxToFullJsonProcess.connect(&convertEvtxToFullJsonProcess, &QProcess::readyReadStandardOutput, this, &MainController::processConvertStdOutInfo);
        //convertEvtxToFullJsonProcess.connect(&convertEvtxToFullJsonProcess, &QProcess::readyReadStandardError, this, &MainController::processConvertErrorInfo);
        connect(&convertEvtxToJsonProcess, (void(QProcess::*)(int))&QProcess::finished, [=]{updateEvtxConvertStatus();});
        convertEvtxToJsonProcess.start("powershell", args);
    }
    else if(convertType == "XML"){
        emit fileConvertEvtxStatus("EVTX to XML conversion process starting " + QDateTime::currentDateTime().toString("MM/dd/yyyy h:mm:ss ap"));
        emit fileConvertEvtxStatus("Please Wait....");

        QStringList args;
        args << "Set-Location -Path " + docsFolder + "/EvtxConverter/EvtxeCmd/;"
             << "./EvtxECmd.exe -f " + fPah.trimmed() +  " --xml " +  savePath.trimmed() + " --xmlf " + iFileName.trimmed() + ".xml";

        //convertSecEvtxToXmlProcess.connect(&convertSecEvtxToXmlProcess, &QProcess::readyReadStandardOutput, this, &MainController::processStdOutSecLogInfo);
        //convertSecEvtxToXmlProcess.connect(&convertSecEvtxToXmlProcess, &QProcess::readyReadStandardError, this, &MainController::processErrorSecLogInfo);
        connect(&convertEvtxToXmlProcess, (void(QProcess::*)(int))&QProcess::finished, [=]{updateEvtxConvertStatus();});
        convertEvtxToXmlProcess.start("powershell", args);
    }
    else if(convertType == "CSV"){
        emit fileConvertEvtxStatus("EVTX to CSV conversion process starting " + QDateTime::currentDateTime().toString("MM/dd/yyyy h:mm:ss ap"));
        emit fileConvertEvtxStatus("Please Wait....");

        QStringList args;
        args << "Set-Location -Path " + docsFolder + "/EvtxConverter/EvtxeCmd/;"
             << "./EvtxECmd.exe -f " + fPah.trimmed() +  " --csv " +  savePath.trimmed() + " --csvf " + iFileName.trimmed() + ".csv";

        //convertSecEvtxToXmlProcess.connect(&convertSecEvtxToXmlProcess, &QProcess::readyReadStandardOutput, this, &MainController::processStdOutSecLogInfo);
        //convertSecEvtxToXmlProcess.connect(&convertSecEvtxToXmlProcess, &QProcess::readyReadStandardError, this, &MainController::processErrorSecLogInfo);
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
        emit fileConvertEvtxStatus("Please Wait....");
        qDebug() << "SAVE PATH IS: " + savePath;
        QStringList args;
        //Set a permanent location for deployment
        args << "Set-Location -Path " + docsFolder + "/EvtxConverter/EvtxeCmd/;"
             << "./EvtxECmd.exe -d " + fPah.trimmed() +  " --json " +  savePath.trimmed();

        //convertEvtxToJsonProcess.connect(&convertEvtxToJsonProcess, &QProcess::readyReadStandardOutput, this, &MainController::processConvertStdOutInfo);
        //convertEvtxToJsonProcess.connect(&convertEvtxToJsonProcess, &QProcess::readyReadStandardError, this, &MainController::processConvertErrorInfo);
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

        //convertEvtxToFullJsonProcess.connect(&convertEvtxToFullJsonProcess, &QProcess::readyReadStandardOutput, this, &MainController::processConvertStdOutInfo);
        //convertEvtxToFullJsonProcess.connect(&convertEvtxToFullJsonProcess, &QProcess::readyReadStandardError, this, &MainController::processConvertErrorInfo);
        connect(&convertEvtxToFullJsonProcess, (void(QProcess::*)(int))&QProcess::finished, [=]{updateEvtxConvertStatus();});
        convertEvtxToFullJsonProcess.start("powershell", args);
    }
    else if(convertType == "XML"){
        emit fileConvertEvtxStatus("EVTX to XML conversion process starting " + QDateTime::currentDateTime().toString("MM/dd/yyyy h:mm:ss ap"));
        emit fileConvertEvtxStatus("Please Wait....");

        QStringList args;
        args << "Set-Location -Path " + docsFolder + "/EvtxConverter/EvtxeCmd/;"
             << "./EvtxECmd.exe -d " + fPah.trimmed() +  " --xml " + savePath.trimmed();

        //convertSecEvtxToXmlProcess.connect(&convertSecEvtxToXmlProcess, &QProcess::readyReadStandardOutput, this, &MainController::processStdOutSecLogInfo);
        //convertSecEvtxToXmlProcess.connect(&convertSecEvtxToXmlProcess, &QProcess::readyReadStandardError, this, &MainController::processErrorSecLogInfo);
        connect(&convertEvtxToXmlProcess, (void(QProcess::*)(int))&QProcess::finished, [=]{updateEvtxConvertStatus();});
        convertEvtxToXmlProcess.start("powershell", args);
    }
    else if(convertType == "CSV"){
        emit fileConvertEvtxStatus("EVTX to CSV conversion process starting " + QDateTime::currentDateTime().toString("MM/dd/yyyy h:mm:ss ap"));
        emit fileConvertEvtxStatus("Please Wait....");

        QStringList args;
        args << "Set-Location -Path " + docsFolder + "/EvtxConverter/EvtxeCmd/;"
             << "./EvtxECmd.exe -d " + fPah.trimmed() +  " --csv " +  savePath.trimmed();

        //convertSecEvtxToXmlProcess.connect(&convertSecEvtxToXmlProcess, &QProcess::readyReadStandardOutput, this, &MainController::processStdOutSecLogInfo);
        //convertSecEvtxToXmlProcess.connect(&convertSecEvtxToXmlProcess, &QProcess::readyReadStandardError, this, &MainController::processErrorSecLogInfo);
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

    foreach(const QString &evtxFile, listOfFilesToConvert){
        QFileInfo fileInfo(evtxFile);
        QString curFileName = fileInfo.fileName().trimmed();
        curFileName.replace(".evtx","");

        if(convertType == "JSON"){            
            QProcess *convertEachEvtxFileProcess = new QProcess();
            QStringList args;
            args << "Set-Location -Path " + docsFolder + "/EvtxConverter/EvtxeCmd/;"
                 << "./EvtxECmd.exe -f " + evtxFile.trimmed() +  " --json " +  savePath.trimmed() + " --jsonf " + curFileName + ".json";
            connect(convertEachEvtxFileProcess, (void(QProcess::*)(int))&QProcess::finished, [=]{updateEvtxConvertStatus();});
            convertEachEvtxFileProcess->start("powershell", args);
        }
        else if(convertType == "Full JSON"){
            QProcess *convertEachEvtxFileProcess2 = new QProcess();
            QStringList args;
            args << "Set-Location -Path " + docsFolder + "/EvtxConverter/EvtxeCmd/;"
                 << "./EvtxECmd.exe -f " + evtxFile.trimmed() +  " --fj --json " +  savePath.trimmed() + " --jsonf " + curFileName + ".json";
            connect(convertEachEvtxFileProcess2, (void(QProcess::*)(int))&QProcess::finished, [=]{updateEvtxConvertStatus();});
            convertEachEvtxFileProcess2->start("powershell", args);
        }
        else if(convertType == "XML"){
            QProcess *convertEachEvtxFileProcess3 = new QProcess();
            QStringList args;
            args << "Set-Location -Path " + docsFolder + "/EvtxConverter/EvtxeCmd/;"
                 << "./EvtxECmd.exe -f " + evtxFile.trimmed() +  " --xml " +  savePath.trimmed() + " --xmlf " + curFileName + ".xml";
            connect(convertEachEvtxFileProcess3, (void(QProcess::*)(int))&QProcess::finished, [=]{updateEvtxConvertStatus();});
            convertEachEvtxFileProcess3->start("powershell", args);
        }
        else if(convertType == "CSV"){
            QProcess *convertEachEvtxFileProcess3 = new QProcess();
            QStringList args;
            args << "Set-Location -Path " + docsFolder + "/EvtxConverter/EvtxeCmd/;"
                 << "./EvtxECmd.exe -f " + evtxFile.trimmed() +  " --csv " +  savePath.trimmed() + " --csvf " + curFileName + ".csv";
            connect(convertEachEvtxFileProcess3, (void(QProcess::*)(int))&QProcess::finished, [=]{updateEvtxConvertStatus();});
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

void MainController::updateEvtxConvertStatus(){
    emit fileConvertEvtxStatus("Conversion completed @ " +  QDateTime::currentDateTime().toString("MM/dd/yyyy h:mm:ss ap"));
    emit fileNameToQml("");
    emit filePathToQml("");
    emit dirPathToQml("");
    emit saveToPathToQml("");
    emit dirPathSepToQml("");
}

void MainController::processConvertStdOutInfo(){
    b_StdOutConvertInfo += convertEvtxToJsonProcess.readAllStandardOutput().trimmed();
    s_StdOutConvertInfo = QString(b_StdOutConvertInfo);
    //qDebug() << "Std out convert evtx Info: " + s_StdOutConvertInfo;
}

void MainController::processConvertErrorInfo(){
    b_StdErrConvertInfo += convertEvtxToJsonProcess.readAllStandardError().trimmed();
    s_StdErrConvertInfo = QString(b_StdErrConvertInfo);
    //qDebug() << "Error Convert Info: " + s_StdErrConvertInfo;
}

//Get the Documents path. Check to see if directories exist. Create directories if needed.
void MainController::checkDirectories(){

    //Get the Documents path and create the main EvtxConverter directory
    docsFolder = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    QDir docsDir(docsFolder + "/EvtxConverter");

    //Main JSON, XML, and CSV directories
    QDir docsJsonDir(docsFolder + "/EvtxConverter/json");
    QDir docsXmlDir(docsFolder + "/EvtxConverter/xml");
    QDir docsCsvDir(docsFolder + "/EvtxConverter/csv");

    //JSON subdirectories for System, Application, and Security files
    QDir docsJsonSysDir(docsFolder + "/EvtxConverter/json/system");
    QDir docsJsonAppDir(docsFolder + "/EvtxConverter/json/application");
    QDir docsJsonSecDir(docsFolder + "/EvtxConverter/json/security");

    //XML subdirectories for System, Application, and Security files
    QDir docsXmlSysDir(docsFolder + "/EvtxConverter/xml/system");
    QDir docsXmlAppDir(docsFolder + "/EvtxConverter/xml/application");
    QDir docsXmlSecDir(docsFolder + "/EvtxConverter/xml/security");

    //CSV subdirectories for System, Application, and Security files
    QDir docsCsvSysDir(docsFolder + "/EvtxConverter/csv/system");
    QDir docsCsvAppDir(docsFolder + "/EvtxConverter/csv/application");
    QDir docsCsvSecDir(docsFolder + "/EvtxConverter/csv/security");

    if(!docsDir.exists()){
        QDir().mkdir(docsFolder + "/EvtxConverter/");
    }
    if(!docsJsonDir.exists()){
        QDir().mkdir(docsFolder + "/EvtxConverter/json");
    }
    if(!docsXmlDir.exists()){
        QDir().mkdir(docsFolder + "/EvtxConverter/xml");
    }
    if(!docsCsvDir.exists()){
        QDir().mkdir(docsFolder + "/EvtxConverter/csv");
    }
    if(!docsJsonSysDir.exists()){
        QDir().mkdir(docsFolder + "/EvtxConverter/json/system");
    }
    if(!docsJsonAppDir.exists()){
        QDir().mkdir(docsFolder + "/EvtxConverter/json/application");
    }
    if(!docsJsonSecDir.exists()){
        QDir().mkdir(docsFolder + "/EvtxConverter/json/security");
    }
    if(!docsXmlSysDir.exists()){
        QDir().mkdir(docsFolder + "/EvtxConverter/xml/system");
    }
    if(!docsXmlAppDir.exists()){
        QDir().mkdir(docsFolder + "/EvtxConverter/xml/application");
    }
    if(!docsXmlSecDir.exists()){
        QDir().mkdir(docsFolder + "/EvtxConverter/xml/security");
    }
    if(!docsCsvSysDir.exists()){
        QDir().mkdir(docsFolder + "/EvtxConverter/csv/system");
    }
    if(!docsCsvAppDir.exists()){
        QDir().mkdir(docsFolder + "/EvtxConverter/csv/appliation");
    }
    if(!docsCsvSecDir.exists()){
        QDir().mkdir(docsFolder + "/EvtxConverter/csv/security");
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
        qDebug() << "The folder does not exist Need to create it with powershell......";
        //TODO: Copy the contents of evtxcmd to docs location
        QString targetDir = "C:/EvtxConverter/EvtxeCmd/";
        //QString qtargetDor2 = "C:/EvtxConverter/EvtxeCmd/Maps/";
        qDebug() << "Target Dir is: " + targetDir;
        QStringList args;
        args << "Copy-Item -Path "  + targetDir +  " -Destination " + docsFolder + "/EvtxConverter/EvtxeCmd/ -Recurse";
        //moveEvtxeCmdToDocsProcess.connect(&moveEvtxeCmdToDocsProcess, &QProcess::readyReadStandardOutput, this, &MainController::evtxCmdFolderExistsResponse);
        //connect(&checkEvtxeCmdPathProcess,(void(QProcess::*)(int))&QProcess::finished, [=]{updateEvtxConvertStatus();});
        moveEvtxeCmdToDocsProcess.start("powershell", args);
    }                    
}
