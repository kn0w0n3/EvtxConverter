#include "maincontroller.h"

MainController::MainController(QWidget *parent) : QWidget(parent){
    checkDirectories();
}

//Get file name and path for evtx file
void MainController::ce_SelectFile(){
    convertEvtxFileName = QFileDialog::getOpenFileName(Q_NULLPTR, tr("Select File"), "");
    QFileInfo fileInfo(convertEvtxFileName);
    convertEvtxFileName = fileInfo.fileName().trimmed();

    convertEvtxFullFilePath  = fileInfo.filePath().trimmed();

    //convertEvtxFilePathOnly = fileInfo.filePath().trimmed();
    //convertEvtxFilePathOnly.replace(convertEvtxFileName, "");
    convertEvtxFileSize = QString::number(fileInfo.size());

    emit filePathToQml(convertEvtxFullFilePath);
    emit dirPathToQml("");
}

//Get directory path for evtx files
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

//Convert an extx file to json, xml, or csv
void MainController::fileConvertEvtx(QString convertType, QString fPah, QString savePath, QString iFileName ){
    if(convertType == "JSON"){
        emit fileConvertEvtxStatus("EVTX to JSON conversion process starting " + QDateTime::currentDateTime().toString("MM/dd/yyyy h:mm:ss ap"));
        emit fileConvertEvtxStatus("Please Wait....");
        QStringList args;
        //Set a permanent location for deployment
        args << "Set-Location -Path C:/Users/Voldem0rt/Documents/Qt_Projects/EvtxConverter/EvtxeCmd/;"
             << "./EvtxECmd.exe -f " + fPah.trimmed() +  " --json " +  savePath.trimmed() + " --jsonf " + iFileName.trimmed() + ".json";

        convertEvtxToJsonProcess.connect(&convertEvtxToJsonProcess, &QProcess::readyReadStandardOutput, this, &MainController::processConvertStdOutInfo);
        convertEvtxToJsonProcess.connect(&convertEvtxToJsonProcess, &QProcess::readyReadStandardError, this, &MainController::processConvertErrorInfo);
        connect(&convertEvtxToJsonProcess, (void(QProcess::*)(int))&QProcess::finished, [=]{updateEvtxConvertStatus();});
        convertEvtxToJsonProcess.start("powershell", args);
    }
    else if(convertType == "Full JSON"){
        emit fileConvertEvtxStatus("EVTX to FUll JSON conversion process starting " + QDateTime::currentDateTime().toString("MM/dd/yyyy h:mm:ss ap"));
        emit fileConvertEvtxStatus("Please Wait....");
        QStringList args;
        //Set a permanent location for deployment
        args << "Set-Location -Path C:/Users/Voldem0rt/Documents/Qt_Projects/EvtxConverter/EvtxeCmd/;"
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
        args << "Set-Location -Path C:/Users/Voldem0rt/Documents/Qt_Projects/EvtxConverter/EvtxeCmd/;"
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
        args << "Set-Location -Path C:/Users/Voldem0rt/Documents/Qt_Projects/EvtxConverter/EvtxeCmd/;"
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

//Convert a directory of evtx files to json, xml, or csv
void MainController::dirConvertEvtx(QString convertType, QString fPah, QString savePath){
    if(convertType == "JSON"){
        emit fileConvertEvtxStatus("EVTX to JSON conversion process starting " + QDateTime::currentDateTime().toString("MM/dd/yyyy h:mm:ss ap"));
        emit fileConvertEvtxStatus("Please Wait....");
        QStringList args;
        //Set a permanent location for deployment
        args << "Set-Location -Path C:/Users/Voldem0rt/Documents/Qt_Projects/EvtxConverter/EvtxeCmd/;"
             << "./EvtxECmd.exe -d " + fPah.trimmed() +  " --json " +  savePath.trimmed();

        convertEvtxToJsonProcess.connect(&convertEvtxToJsonProcess, &QProcess::readyReadStandardOutput, this, &MainController::processConvertStdOutInfo);
        convertEvtxToJsonProcess.connect(&convertEvtxToJsonProcess, &QProcess::readyReadStandardError, this, &MainController::processConvertErrorInfo);
        connect(&convertEvtxToJsonProcess, (void(QProcess::*)(int))&QProcess::finished, [=]{updateEvtxConvertStatus();});
        convertEvtxToJsonProcess.start("powershell", args);
    }
    else if(convertType == "Full JSON"){
        emit fileConvertEvtxStatus("EVTX to FUll JSON conversion process starting " + QDateTime::currentDateTime().toString("MM/dd/yyyy h:mm:ss ap"));
        emit fileConvertEvtxStatus("Please Wait....");
        QStringList args;
        //Set a permanent location for deployment
        args << "Set-Location -Path C:/Users/Voldem0rt/Documents/Qt_Projects/EvtxConverter/EvtxeCmd/;"
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
        args << "Set-Location -Path C:/Users/Voldem0rt/Documents/Qt_Projects/EvtxConverter/EvtxeCmd/;"
             << "./EvtxECmd.exe -d " + fPah.trimmed() +  " --xml " +  savePath.trimmed();

        //convertSecEvtxToXmlProcess.connect(&convertSecEvtxToXmlProcess, &QProcess::readyReadStandardOutput, this, &MainController::processStdOutSecLogInfo);
        //convertSecEvtxToXmlProcess.connect(&convertSecEvtxToXmlProcess, &QProcess::readyReadStandardError, this, &MainController::processErrorSecLogInfo);
        connect(&convertEvtxToXmlProcess, (void(QProcess::*)(int))&QProcess::finished, [=]{updateEvtxConvertStatus();});
        convertEvtxToXmlProcess.start("powershell", args);

    }
    else if(convertType == "CSV"){
        emit fileConvertEvtxStatus("EVTX to CSV conversion process starting " + QDateTime::currentDateTime().toString("MM/dd/yyyy h:mm:ss ap"));
        emit fileConvertEvtxStatus("Please Wait....");

        QStringList args;
        args << "Set-Location -Path C:/Users/Voldem0rt/Documents/Qt_Projects/EvtxConverter/EvtxeCmd/;"
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

void MainController::dirConvertEachEvtx(QString convertType, QString savePath){
    emit fileConvertEvtxStatus("EVTX file conversion process starting " + QDateTime::currentDateTime().toString("MM/dd/yyyy h:mm:ss ap"));
    emit fileConvertEvtxStatus("Please Wait....");
    foreach(const QString &evtxFile, listOfFilesToConvert){
        QFileInfo fileInfo(evtxFile);
        QString curFileName = fileInfo.fileName().trimmed();

        //TODO: Remove extension from file name
        if(convertType == "JSON"){
            QProcess *convertEachEvtxFileProcess = new QProcess();
            QStringList args;
            args << "Set-Location -Path C:/Users/Voldem0rt/Documents/Qt_Projects/EvtxConverter/EvtxeCmd/;"
                 << "./EvtxECmd.exe -f " + evtxFile.trimmed() +  " --json " +  savePath.trimmed() + " --jsonf " + curFileName + ".json";
            connect(convertEachEvtxFileProcess, (void(QProcess::*)(int))&QProcess::finished, [=]{updateEvtxConvertStatus();});
            convertEachEvtxFileProcess->start("powershell", args);
        }
    }
}

void MainController::selectDirConvertEachEvtx(){
    QString path = QFileDialog::getExistingDirectory(Q_NULLPTR, tr("Select Directory"), "/home", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    emit dirPathSepToQml(path);
    QDir dir(path);
    dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    dir.setSorting(QDir::Size | QDir::Reversed);

    QFileInfoList list = dir.entryInfoList();

    for (int i = 0; i < list.size(); ++i) {
        QFileInfo fileInfo = list.at(i);

        listOfFilesToConvert << fileInfo.absoluteFilePath();
        //Get the file size
        //qDebug() << "The file Size is: " + QString::number(fileInfo.size());

        //Get the file name only
        //qDebug() << "The file name is: " + fileInfo.fileName();

        //Absolute file path includes the file name in the file path
        //qDebug() << "The path including the filename is: " + fileInfo.absoluteFilePath();

        //Absolute path returns the path of the file only
        //qDebug() << "Th file path only is: " + fileInfo.absolutePath();
    }
    qDebug() << "List of files loaded";
}

void MainController::updateEvtxConvertStatus(){
    emit fileConvertEvtxStatus("Conversion completed @ " +  QDateTime::currentDateTime().toString("MM/dd/yyyy h:mm:ss ap"));
    emit fileNameToQml("");
    emit filePathToQml("");
    emit dirPathToQml("");
    emit saveToPathToQml("");
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

void MainController::checkDirectories(){
    qDebug() << "In check directories function......";
    qDebug() << "The username is: " << getenv("USERNAME"); //for windows

    QDir mainDir("C:/Program Files/Lumberjack");

    QDir evtxDir("C:/Program Files/Lumberjack/evtx");
    QDir evtxSysDir("C:/Program Files/Lumberjack/evtx/system");
    QDir evtxAppDir("C:/Program Files/Lumberjack/evtx/application");
    QDir evtxSecDir("C:/Program Files/Lumberjack/evtx/security");

    //Get the myDocuments path. This will be different on each system
    const QString docsFolder = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    qDebug() << "The mydocs path is: " +docsFolder;

    QDir docsDir(docsFolder + "/Lumberjack");
    QDir docsJsonDir(docsFolder + "/Lumberjack/json");
    QDir docsXmlDir(docsFolder + "/Lumberjack/xml");
    QDir docsCsvDir(docsFolder + "/Lumberjack/csv");

    QDir docsJsonSysDir(docsFolder + "/Lumberjack/json/system");
    QDir docsJsonAppDir(docsFolder + "/Lumberjack/json/application");
    QDir docsJsonSecDir(docsFolder + "/Lumberjack/json/security");

    QDir docsXmlSysDir(docsFolder + "/Lumberjack/xml/system");
    QDir docsXmlAppDir(docsFolder + "/Lumberjack/xml/application");
    QDir docsXmlSecDir(docsFolder + "/Lumberjack/xml/security");

    QDir docsCsvSysDir(docsFolder + "/Lumberjack/csv/system");
    QDir docsCsvAppDir(docsFolder + "/Lumberjack/csv/application");
    QDir dcsCsvSecDir(docsFolder + "/Lumberjack/csv/security");

    if (!mainDir.exists()){
        QDir().mkdir("C:/Program Files/Lumberjack");
        //qDebug() << "Error Dir does not exist or can't be reached. There is a space in the path name: Program Files";
        qDebug() << "Trying to create dir C:/Program Files/Lumberjack ";
    }
    else{
        qDebug() << "Dir Exists";
    }

    if(!evtxDir.exists()){
        QDir().mkdir("C:/Program Files/Lumberjack/evtx");
        //qDebug() << "Error Dir does not exist or can't be reached. There is a space in the path name: Program Files";
        qDebug() << "Trying to create dir C:/Program Files/Lumberjack/evtx ";
    }
    if(!evtxSysDir.exists()){
        QDir().mkdir("C:/Program Files/Lumberjack/evtx/system");
    }
    if(!evtxAppDir.exists()){
        QDir().mkdir("C:/Program Files/Lumberjack/evtx/application");
    }
    if(!evtxSecDir.exists()){
        QDir().mkdir("C:/Program Files/Lumberjack/evtx/security");
    }
    if(!docsDir.exists()){
        QDir().mkdir(docsFolder + "/Lumberjack");
        //qDebug() << "Error Dir does not exist or can't be reached. There is a space in the path name: Program Files";
        //qDebug() << "Trying to create dir docsFolder + /Lumberjack";
    }
    if(!docsJsonDir.exists()){
        QDir().mkdir(docsFolder + "/Lumberjack/json");
    }
    if(!docsXmlDir.exists()){
        QDir().mkdir(docsFolder + "/Lumberjack/xml");
    }
    if(!docsCsvDir.exists()){
        QDir().mkdir(docsFolder + "/Lumberjack/csv");
    }
}
