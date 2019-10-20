#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <Windows.h>
#include <vector>
#include <string>
#include <time.h>
#include <iterator>
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
    vector<wstring> get_all_files_names_within_folder(wstring folder);
    vector<wstring> m_allFiles;
    void CreatSqlTable();
    bool OpenDataBase();
private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
