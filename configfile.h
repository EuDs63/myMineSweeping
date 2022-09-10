#ifndef CONFIGFILE_H
#define CONFIGFILE_H

#include<QVariant>
#include<QSettings>

class configFile
{
public:
    configFile();
    virtual ~configFile(void);
    bool fileName(QString qstrFileName);
    void set(QString,QString,QVariant);
    QVariant get(QString,QString);

private:
    QString m_qStrFileName;
    QSettings *m_pSetting;

};

#endif // CONFIGFILE_H
