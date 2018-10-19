#include "FilePathWidget.h"
#include "ui_FilePathWidget.h"
#include <QtDebug>
#include <QDir>
#include <QPainter>
#include <QLinearGradient>

FilePathWidget::FilePathWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FilePathWidget)
{
    ui->setupUi(this);
}

FilePathWidget::~FilePathWidget()
{
    delete ui;
}

void FilePathWidget::setRootPath(const QString &path)
{
    for (int i = 0; i < m_listPathButton.size(); ++i)
    {
        PathButton *button = m_listPathButton.at(i);
        ui->horizontalLayout->removeWidget(button);
        button->deleteLater();
    }

    QString strDirName = QDir(path).dirName();
    if (strDirName.isEmpty())
    {
        strDirName = path;
    }

    PathButton *button = new PathButton(this);
    button->setText(strDirName);
    ui->horizontalLayout->addWidget(button);
}

void FilePathWidget::cdPath(const QString &path)
{
    QString strDirName = QDir(path).dirName();
    if (strDirName.isEmpty())
    {
        strDirName = path;
    }
    setWindowTitle(strDirName);

    //
    int index = -1;
    for (int i = 0; i < m_listPathButton.size(); ++i)
    {
        if (m_listPathButton.at(i)->path() == path)
        {
            index = i;
            break;
        }
    }
    if (index > -1)
    {
        int delCount = m_listPathButton.size() - index - 1;
        while (delCount > 0)
        {
            PathButton *button = m_listPathButton.takeLast();
            ui->horizontalLayout->removeWidget(button);
            button->deleteLater();
            delCount--;
        }
    }
    else
    {
        PathButton *button = new PathButton(this);
        connect(button, &PathButton::clicked, this, &FilePathWidget::onPathButtonClicked);
        button->setText(strDirName);
        button->setPath(path);
        button->setFocus();
        m_listPathButton.append(button);
        ui->horizontalLayout->addWidget(button);
    }
    //
    if (m_listPathButton.size() == 1)
    {
        m_listPathButton.first()->setStyleSheet("border-radius: 5px");
    }
    else
    {
        for (int i = 0; i < m_listPathButton.size(); ++i)
        {
            PathButton *button = m_listPathButton.at(i);
            button->setStyleSheet("border-radius: 0px");
            if (button == m_listPathButton.first())
            {
                button->setStyleSheet("border-top-left-radius: 5px;\
                                      border-bottom-left-radius: 5px;");
            }
            else if (button == m_listPathButton.last())
            {
                button->setStyleSheet("border-top-right-radius: 5px;\
                                      border-bottom-right-radius: 5px;");
            }
        }
    }
}

void FilePathWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setPen(QColor("#42413C"));

    QLinearGradient liner(QPoint(width() / 2, 0), QPoint(width() / 2, height()));
    liner.setColorAt(0, QColor("#3B3A36"));
    liner.setColorAt(1, QColor("#55534B"));

    painter.setBrush(liner);
    painter.drawRect(rect());
}

void FilePathWidget::onPathButtonClicked()
{
    PathButton *button = (PathButton *)sender();
    QString strPath = button->path();
    emit sig_cdPath(strPath);
}
