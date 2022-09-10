#include "configfile.h"
#include<QDebug>
#include<QDir>

configFile::configFile()
{

}

bool configFile::fileName(QString qstrFileName)
{
    if(qstrFileName.isEmpty())
    {
        m_qStrFileName="databaseInfo.cnf";
    }
    else
    {
        m_qStrFileName=qstrFileName;
    }//如果没有特殊指定，则默认为databaseInfo.cnf
    qDebug()<<m_qStrFileName;
    QDir dir;
    if(!dir.exists(m_qStrFileName))
    {
        qDebug()<<"未找到"<<m_qStrFileName;
        return false;
    }
    else
    {
        m_pSetting=new QSettings(m_qStrFileName,QSettings::IniFormat);
        return true;
    }
}

configFile::~configFile()
{
    delete m_pSetting;
    m_pSetting=0;
}

void configFile::set(QString qStrNodeName, QString qStrKeyName,QVariant qVarValue)
{
    m_pSetting->setValue(QString("/%1/%2").arg(qStrNodeName).arg(qStrKeyName),qVarValue);
}

QVariant configFile::get(QString qStrNodeName,QString qStrKeyName)
{
   QVariant qvar=m_pSetting->value(QString("/%1/%2").arg(qStrNodeName).arg(qStrKeyName));
   return qvar;
}
