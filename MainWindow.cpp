#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "FileSystemDialog/FileSystemDialog.h"
#include <QtDebug>
#include <QStack>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    FileSystemDialog dialog(this);
    dialog.setPath("F:/");
    dialog.exec();
}
