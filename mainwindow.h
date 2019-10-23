#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <Windows.h>
#include <vector>
#include <string>
#include <time.h>
#include <iterator>
#include <QSqlDatabase>
using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void get_all_files_names_within_folder(wstring folder);
    //vector<wstring> m_allFiles;
    void CreatSqlTable();
    QSqlDatabase OpenDataBase();
    const char* headerSql="INSERT INTO allfilesdata VALUES(";
private slots:
    void on_pushButton_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
