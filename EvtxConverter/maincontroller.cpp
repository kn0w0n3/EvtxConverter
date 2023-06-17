#include "maincontroller.h"

MainController::MainController(QWidget *parent) : QWidget(parent){

}

//Get file name and path for evtx file
void MainController::ce_SelectFile(){
    convertEvtxFileName = QFileDialog::getOpenFileName(Q_NULLPTR, tr("Select File"), "");
    QFileInfo fileInfo(convertEvtxFileName);
    convertEvtxFileName = fileInfo.fileName().trimmed();

    //emit dbFileNameToQml(convertEvtxFileName);
    convertEvtxFullFilePath  = fileInfo.filePath().trimmed();

    convertEvtxFilePathOnly = fileInfo.filePath().trimmed();
    convertEvtxFilePathOnly.replace(convertEvtxFileName, "");
    convertEvtxFileSize = QString::number(fileInfo.size());
    //testPath = dbFullFileP\ath;
    //testPath.replace(" ","\\");

    //qDebug() << "The selected file path is " << convertEvtxFullFilePath;
    emit filePathToQml(convertEvtxFullFilePath);
    emit dirPathToQml("");
}

//Get directory path for evtx files
void MainController::ce_SelectDir(){
    QString dir = QFileDialog::getExistingDirectory(Q_NULLPTR, tr("Select Directory"), "/home", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    //qDebug() << "The Dir is: " + dir;
    emit dirPathToQml(dir);
    emit filePathToQml("");
}

//Get path where converted files will be stored
void MainController::ce_SaveToPath(){
    QString dir = QFileDialog::getExistingDirectory(Q_NULLPTR, tr("Select Directory"), "/home", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    //qDebug() << "The Save to path is: " + dir;
    emit saveToPathToQml(dir);
}

//Convert an extx file to json, xml, or csv
void MainController::fileConvertEvtx(QString convertType, QString fPah, QString savePath, QString iFileName ){

    if(convertType == "JSON"){
        //qDebug() << "IN CONVERT EVTX TO JSON........";
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
        //qDebug() << "IN CONVERT EVTX TO  Full JSON........";
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
        //qDebug() << "IN CONVERT EVTX TO XML........";
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
        //qDebug() << "IN CONVERT EVTX TO CSV........";
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
        //qDebug() << "IN CONVERT EVTX TO JSON........";
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
        //qDebug() << "IN CONVERT EVTX TO  Full JSON........";
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
        //qDebug() << "IN CONVERT EVTX TO XML........";
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
        //qDebug() << "IN CONVERT EVTX TO CSV........";
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
