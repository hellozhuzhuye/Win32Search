#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QDebug>
#include <qdebug.h>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDateTime>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //OpenDataBase();
    //CreatSqlTable();
    m_allFiles=MainWindow::get_all_files_names_within_folder(L"D:\\");

}


bool MainWindow::OpenDataBase()
{
    QSqlDatabase database;
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("MyDataBase.db");
    if (!database.open())
    {
        qDebug() << "Error: Failed to connect database." << database.lastError();
    }
    else
    {
        qDebug() << "Succeed to connect database." ;
    }
    return database.open();
}


void MainWindow::CreatSqlTable()
{


    //创建表格
    QSqlQuery sql_query;
    if(!sql_query.exec("create table allfilesdata(  \
                       fileid INTEGER primary key AUTOINCREMENT,    \
                       filename text,  \
                       filepath  text NOT NULL, \
                       filesize INTEGER, \
                       fileattributes INTEGER NOT NULL, \
                       creat_dwlowtime INTEGER NOT NULL,    \
                       creat_dwhightime INTEGER NOT NULL,   \
                       lastaccess_dwlowtime INTEGER NOT NULL,   \
                       lastaccess_dwhightime INTEGER NOT NULL,  \
                       lastwrite_dwlowtime INTEGER NOT NULL,    \
                       lastwrite_dwhightime INTEGER NOT NULL,   \
                       UNIQUE(filename,filepath) ON CONFLICT REPLACE)"))
    {
        qDebug() << "Error: Fail to create table."<< sql_query.lastError();
    }
    else
    {
        qDebug() << "Table created!";
    }


}

vector<wstring> MainWindow::get_all_files_names_within_folder(wstring folder)
{
    vector<wstring> names;
    names.reserve(10000);
    WIN32_FIND_DATA fd;
    auto searchName = folder + L"*";
    HANDLE hFind = ::FindFirstFile(searchName.c_str(), &fd);

    if (hFind != INVALID_HANDLE_VALUE) {
        do {
            if ('.' == fd.cFileName[0])
            {
                continue;
            }


            // 判断是否是目录还是文件
            if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            {
                // 目录, 则继续往下递归遍历文件

//                wstring sqlinsert = L"\"INSERT INTO allfilesdata VALUES(\'";
//                sqlinsert += fd.cFileName;
//                sqlinsert += L"\',\'";
//                sqlinsert += folder;
//                sqlinsert += L"\',";

//                sqlinsert += L"NULL,";
//                wchar_t filedata[65];

//                _itow_s(fd.dwFileAttributes, filedata, 10);
//                sqlinsert += filedata;
//                sqlinsert += L",";


//                _itow_s(fd.ftCreationTime.dwLowDateTime, filedata, 10);
//                sqlinsert += filedata;
//                sqlinsert += L",";

//                _itow_s(fd.ftCreationTime.dwHighDateTime, filedata, 10);
//                sqlinsert += filedata;
//                sqlinsert += L",";

//                _itow_s(fd.ftLastAccessTime.dwLowDateTime, filedata, 10);
//                sqlinsert += filedata;
//                sqlinsert += L",";

//                _itow_s(fd.ftLastAccessTime.dwHighDateTime, filedata, 10);
//                sqlinsert += filedata;
//                sqlinsert += L",";

//                _itow_s(fd.ftLastWriteTime.dwLowDateTime, filedata, 10);
//                sqlinsert += filedata;
//                sqlinsert += L",";

//                _itow_s(fd.ftLastWriteTime.dwHighDateTime, filedata, 10);
//                sqlinsert += filedata;
//                sqlinsert += L")\"";

//                qDebug() << "sqlinsert::  "<<sqlinsert << endl;

                names.push_back(folder + fd.cFileName);
                auto str = folder + fd.cFileName+L"\\";


//                QSqlQuery sql_query;

//                sql_query.prepare("INSERT INTO allfilesdata(filename,filepath,filesize,fileattributes,creat_dwlowtime,creat_dwhightime,lastaccess_dwlowtime,lastaccess_dwhightime,lastwrite_dwlowtime,lastwrite_dwhightime) VALUES(:filename,:filepath,:filesize,:fileattributes,:creat_dwlowtime,:creat_dwhightime,:lastaccess_dwlowtime,:lastaccess_dwhightime,:lastwrite_dwlowtime,:lastwrite_dwhightime)");
//                sql_query.bindValue(":filename",QString::fromStdWString(fd.cFileName));
//                sql_query.bindValue(":filepath",QString::fromStdWString(folder));
//                sql_query.bindValue(":filesize","NULL");
//                sql_query.bindValue(":fileattributes",(int)fd.dwFileAttributes);
//                sql_query.bindValue(":creat_dwlowtime",(int)fd.ftCreationTime.dwLowDateTime);
//                sql_query.bindValue(":creat_dwhightime",(int)fd.ftCreationTime.dwHighDateTime);
//                sql_query.bindValue(":lastaccess_dwlowtime",(int)fd.ftLastAccessTime.dwLowDateTime);
//                sql_query.bindValue(":lastaccess_dwhightime",(int)fd.ftLastAccessTime.dwHighDateTime);
//                sql_query.bindValue(":lastwrite_dwlowtime",(int)fd.ftLastWriteTime.dwLowDateTime);
//                sql_query.bindValue(":lastwrite_dwhightime",(int)fd.ftLastWriteTime.dwHighDateTime);

//                if(!sql_query.exec())
//        {
//                qDebug() << sql_query.lastError();
//        }
//                else
//        {
//                qDebug() << "inserted dir successfully!";
//        }

//                QString qstrinsert = QString::fromStdWString(sqlinsert);
//                qDebug() << qstrinsert << endl;
//                if(!sql_query.exec(qstrinsert))
//                {
//                    //qDebug() << sql_query.lastError();
//                }
//                else
//                {
//                    //qDebug() << "inserted successfully!";
//                }



                auto nextfindstr = folder + fd.cFileName+L"\\";
                auto namelist=get_all_files_names_within_folder(nextfindstr);
                names.insert(names.end(), namelist.begin(), namelist.end());



            }
            else
            {
                // 文件
//                QSqlQuery sql_query;
//                sql_query.prepare("INSERT INTO allfilesdata(filename,filepath,filesize,fileattributes,creat_dwlowtime,creat_dwhightime,lastaccess_dwlowtime,lastaccess_dwhightime,lastwrite_dwlowtime,lastwrite_dwhightime) VALUES(:filename,:filepath,:filesize,:fileattributes,:creat_dwlowtime,:creat_dwhightime,:lastaccess_dwlowtime,:lastaccess_dwhightime,:lastwrite_dwlowtime,:lastwrite_dwhightime)");
//                sql_query.bindValue(":filename",QString::fromStdWString(fd.cFileName));
//                sql_query.bindValue(":filepath",QString::fromStdWString(folder));
//                sql_query.bindValue(":filesize",(int)(fd.nFileSizeHigh*(MAXDWORD + 1) + fd.nFileSizeLow));
//                sql_query.bindValue(":fileattributes",(int)fd.dwFileAttributes);
//                sql_query.bindValue(":creat_dwlowtime",(int)fd.ftCreationTime.dwLowDateTime);
//                sql_query.bindValue(":creat_dwhightime",(int)fd.ftCreationTime.dwHighDateTime);
//                sql_query.bindValue(":lastaccess_dwlowtime",(int)fd.ftLastAccessTime.dwLowDateTime);
//                sql_query.bindValue(":lastaccess_dwhightime",(int)fd.ftLastAccessTime.dwHighDateTime);
//                sql_query.bindValue(":lastwrite_dwlowtime",(int)fd.ftLastWriteTime.dwLowDateTime);
//                sql_query.bindValue(":lastwrite_dwhightime",(int)fd.ftLastWriteTime.dwHighDateTime);

//                if(!sql_query.exec())
//        {
//                qDebug() << sql_query.lastError();
//        }
//                else
//        {
//                qDebug() << "inserted file successfully!";
//        }

                names.push_back(folder + fd.cFileName);

//                wstring sqlinsert = L"INSERT INTO allfilesdata VALUES(";
//                sqlinsert += fd.cFileName;
//                sqlinsert += L",";
//                sqlinsert += folder;
//                sqlinsert += L",";

//                wchar_t fsize[65];



//                DWORD filesizebyte = (fd.nFileSizeHigh*(MAXDWORD + 1) + fd.nFileSizeLow);
//                _itow_s(filesizebyte, fsize, 10);
//                sqlinsert += fsize;
//                sqlinsert += L",";

//                _itow_s(fd.dwFileAttributes, fsize, 10);
//                sqlinsert += fsize;
//                sqlinsert += L",";


//                _itow_s(fd.ftCreationTime.dwLowDateTime, fsize, 10);
//                sqlinsert += fsize;
//                sqlinsert += L",";

//                _itow_s(fd.ftCreationTime.dwHighDateTime, fsize, 10);
//                sqlinsert += fsize;
//                sqlinsert += L",";

//                _itow_s(fd.ftLastAccessTime.dwLowDateTime, fsize, 10);
//                sqlinsert += fsize;
//                sqlinsert += L",";

//                _itow_s(fd.ftLastAccessTime.dwHighDateTime, fsize, 10);
//                sqlinsert += fsize;
//                sqlinsert += L",";

//                _itow_s(fd.ftLastWriteTime.dwLowDateTime, fsize, 10);
//                sqlinsert += fsize;
//                sqlinsert += L",";

//                _itow_s(fd.ftLastWriteTime.dwHighDateTime, fsize, 10);
//                sqlinsert += fsize;
//                sqlinsert += L")";

                //qDebug() << sqlinsert << endl;
            }


        } while (::FindNextFile(hFind, &fd));
        ::FindClose(hFind);
    }
    return names;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    int iRow = ui->tableWidget->rowCount();
    for(int i = 0;i < iRow;i++)
    {
       ui->tableWidget->removeRow(0);
    }
    int iRow2 = ui->tableWidget->rowCount();

    QString linetext=ui->lineEdit->text();

//    QSqlQuery sql_query;
//    QString searchstr="select * from allfilesdata where filename LIKE :linetext";
//    sql_query.prepare(searchstr);
//    sql_query.bindValue(":linetext",QString("%%1%").arg(linetext));


//    if(!sql_query.exec())
//    {
//            qDebug()<<"push:::"<<sql_query.lastError();
//    }
//    else
//    {
//            while(sql_query.next())
//        {
//            QString filename= sql_query.value(1).toString();
//            QString filepath = sql_query.value(2).toString();
//            QString filesize = sql_query.value(3).toString();

//            qDebug()<<filename<<"::::::::"<<QString::compare(filesize,"NULL")<<"size:"<<filesize;
//            if((QString::compare(filesize,"null"))==0)
//            {
//                filesize=" ";
//                qDebug()<<"find null";
//            }


//            ui->tableWidget->insertRow(iRow2);
//            ui->tableWidget->setItem(iRow2,0,new QTableWidgetItem(filename));
//            ui->tableWidget->setItem(iRow2,1,new QTableWidgetItem(filepath));
//            ui->tableWidget->setItem(iRow2,2,new QTableWidgetItem(filesize));

//            //qDebug()<<QString("filename:%1    filepath:%2    filesize:%3").arg(filename).arg(filepath).arg(filesize);
//        }
//    }




    std::vector<wstring> searchFiles;
    searchFiles.reserve(10000);
    wstring searchStr=linetext.toStdWString();

    int allFilesSize = (int)m_allFiles.size();

    for (int i = 0; i < allFilesSize; i++)
    {
        if (m_allFiles[i].find(searchStr) != wstring::npos)
        {
            searchFiles.push_back(m_allFiles[i]);
        }
    }

    for (int i=0;i<searchFiles.size();i++)
    {

        ui->tableWidget->insertRow(iRow2);
        QString searchfile = QString::fromStdWString(searchFiles[i]);

        ui->tableWidget->setItem(iRow2,0,new QTableWidgetItem(searchfile));


    }
}
