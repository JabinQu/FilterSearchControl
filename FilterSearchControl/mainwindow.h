#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "FilterSearchControl.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void loadData();

private slots:
    void on_pushButtonChoose_clicked();

private:
    Ui::MainWindow *ui;
    FilterSearchControl *m_searchPromptControl;
};

#endif // MAINWINDOW_H
