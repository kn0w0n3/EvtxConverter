#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QObject>
#include <QWidget>
#include <QProcess>
#include <QStringList>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QFile>
#include <QFileInfo>
#include <QFileDialog>
#include <QDate>
#include <QByteArray>

class MainController:  public QWidget{
    Q_OBJECT

public:
    MainController(QWidget *parent = nullptr);

signals:
    //File info
    void fileNameToQml(QString fileName);
    void filePathToQml(QString filePath);
    void dirPathToQml(QString dirPath);
    void saveToPathToQml(QString saveToPath);
    void fileConvertEvtxStatus(QString curStatus);

public slots:
    void ce_SelectFile();
    void ce_SelectDir();
    void ce_SaveToPath();
    void fileConvertEvtx(QString, QString, QString, QString);
    void dirConvertEvtx(QString, QString, QString);
    void updateEvtxConvertStatus();
    void processConvertStdOutInfo();
    void processConvertErrorInfo();

    //void convertEvtxToXml();
    //void convertEvtxToJson();
    //void convertEvtxToCSV();


private:
    QProcess convertEvtxToXmlProcess;
    QProcess convertEvtxToJsonProcess;
    QProcess convertEvtxToFullJsonProcess;
    QProcess convertEvtxToCsvProcess;

    QString convertEvtxFileName = "";
    QString convertEvtxFullFilePath = "";
    QString convertEvtxFilePathOnly = "";
    QString convertEvtxFileSize = "";

    QProcess convertSecEvtxToXmlProcess;
    QProcess convertSecEvtxToJsonProcess;
    QProcess convertAppEvtxToXmlProcess;
    QProcess convertAppEvtxToJsonProcess;
    QProcess convertSysEvtxToXmlProcess;
    QProcess convertSysEvtxToJsonProcess;

    QString s_StdOutConvertInfo;
    QString s_StdErrConvertInfo;

    QByteArray b_StdOutConvertInfo;
    QByteArray b_StdErrConvertInfo;
};

#endif // MAINCONTROLLER_H
