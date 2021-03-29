#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_searchPromptControl = new FilterSearchControl(this);
    ui->horizontalLayout->addWidget(m_searchPromptControl);

    loadData();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadData()
{
    QStringList infoList;
    infoList << "123" << "a123" << "aa12" << "abc13" << "bc2";

    m_searchPromptControl->loadData(infoList);
}

void MainWindow::on_pushButtonChoose_clicked()
{
    ui->label->setText(m_searchPromptControl->getString());
}
