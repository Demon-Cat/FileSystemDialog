#include "FileSystemDialog.h"
#include "ui_FileSystemDialog.h"
#include <QtDebug>
#include <QPainter>
#include <QMouseEvent>
#include "MyFileSystemModel.h"

FileSystemDialog::FileSystemDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FileSystemDialog)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    m_fileModel = new MyFileSystemModel(this);

    ui->tableView->setModel(m_fileModel);
    ui->tableView->sortByColumn(0, Qt::AscendingOrder);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    ui->label_title->installEventFilter(this);

    connect(ui->widget_path, &FilePathWidget::windowTitleChanged, this, &FileSystemDialog::onWindowTitleChanged);
    connect(ui->widget_path, &FilePathWidget::sig_cdPath, this, &FileSystemDialog::onCdPath);
}

FileSystemDialog::~FileSystemDialog()
{
    delete ui;
}

void FileSystemDialog::setPath(const QString &path)
{
    m_fileModel->setRootPath(path);
    ui->tableView->setRootIndex(m_fileModel->index(path));

    ui->widget_path->cdPath(path);
}

bool FileSystemDialog::eventFilter(QObject *obj, QEvent *e)
{
    if (obj == ui->label_title)
    {
        switch (e->type())
        {
        case QEvent::MouseButtonPress:
        {
            m_pressed = true;
            QMouseEvent *event = static_cast<QMouseEvent *>(e);
            m_pressDistance = mapToGlobal(event->pos()) - pos();
            break;
        }
        case QEvent::MouseButtonRelease:
        {
            m_pressed = false;
            break;
        }
        case QEvent::MouseMove:
        {
            QMouseEvent *event = static_cast<QMouseEvent *>(e);
            move(mapToGlobal(event->pos()) - m_pressDistance);
            break;
        }
        default:
            break;
        }
    }
    return QDialog::eventFilter(obj, e);
}

void FileSystemDialog::resizeEvent(QResizeEvent *event)
{
    int width = ui->tableView->width();
    ui->tableView->setColumnWidth(0, width - 350);
    ui->tableView->setColumnWidth(1, 100);
    ui->tableView->setColumnWidth(2, 100);
    QDialog::resizeEvent(event);
}

void FileSystemDialog::paintEvent(QPaintEvent *)
{
    int shadowWidth = 10;
    qreal alphaStep = 100.0 / shadowWidth;
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(Qt::NoBrush);
    QColor color(0, 0, 0, 50);
    for (int i = 0; i < shadowWidth; i++)
    {
        QRect rect(shadowWidth - i, shadowWidth - i, this->width() - (shadowWidth - i) * 2, this->height() - (shadowWidth - i) * 2);
        //int alpha = 150 - qSqrt(i) * 50;
        color.setAlpha(100 - i * alphaStep);
        painter.setPen(color);
        painter.drawRoundedRect(rect, i, i);
    }
}

void FileSystemDialog::onWindowTitleChanged(const QString &title)
{
    ui->label_title->setText(title);
}

void FileSystemDialog::onCdPath(const QString &path)
{
    setPath(path);
}

void FileSystemDialog::on_tableView_doubleClicked(const QModelIndex &index)
{
    if (m_fileModel->isDir(index))
    {
        QString strPath = m_fileModel->filePath(index);
        setPath(strPath);
    }
}

void FileSystemDialog::on_pushButton_close_clicked()
{
    close();
}
