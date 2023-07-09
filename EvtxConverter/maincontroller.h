#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QObject>
#include <QWidget>
#include <QProcess>
#include <QStringList>
//#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QFile>
#include <QFileInfo>
#include <QFileDialog>
#include <QDate>
#include <QByteArray>
#include <QDirIterator>
#include <QDir>
#include <QStandardPaths>

class MainController:  public QWidget{
    Q_OBJECT

public:
    MainController(QWidget *parent = nullptr);

signals:
    void fileNameToQml(QString fileName);
    void filePathToQml(QString filePath);
    void dirPathToQml(QString dirPath);
    void dirPathSepToQml(QString sDirPath);
    void saveToPathToQml(QString saveToPath);
    void fileConvertEvtxStatus(QString curStatus);

public slots:
    void ce_SelectFile();
    void ce_SelectDir();
    void ce_SaveToPath();
    void fileConvertEvtx(QString, QString, QString, QString);
    void dirConvertEvtx(QString, QString, QString);
    void dirConvertEachEvtx(QString, QString);
    void selectDirConvertEachEvtx();
    void updateEvtxConvertStatus();
    void updateIndividualEvtxConvertStatus(QString);
    void checkDirectories();
    void evtxCmdFolderExistsResponse();

private:
    QProcess convertEvtxToXmlProcess;
    QProcess convertEvtxToJsonProcess;
    QProcess convertEvtxToFullJsonProcess;
    QProcess convertEvtxToCsvProcess;
    QProcess convertSecEvtxToXmlProcess;
    QProcess convertSecEvtxToJsonProcess;
    QProcess convertAppEvtxToXmlProcess;
    QProcess convertAppEvtxToJsonProcess;
    QProcess convertSysEvtxToXmlProcess;
    QProcess convertSysEvtxToJsonProcess;
    QProcess moveEvtxCmdFilesToDocs;
    QProcess checkEvtxeCmdPathProcess;
    QProcess moveEvtxeCmdToDocsProcess;

    QString convertEvtxFileName = "";
    QString convertEvtxFullFilePath = "";
    QString convertEvtxFilePathOnly = "";
    QString convertEvtxFileSize = "";
    QString s_StdOutConvertInfo;
    QString s_StdErrConvertInfo;
    QString docsFolder = "";

    QStringList listOfFilesToConvert;

    QByteArray b_StdOutConvertInfo;
    QByteArray b_StdErrConvertInfo;       
};

#endif // MAINCONTROLLER_H
