#ifndef FILESYSTEMDIALOG_H
#define FILESYSTEMDIALOG_H

#include <QDialog>

class MyFileSystemModel;

namespace Ui {
class FileSystemDialog;
}

class FileSystemDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FileSystemDialog(QWidget *parent = 0);
    ~FileSystemDialog();

    void setPath(const QString &path);

protected:
    bool eventFilter(QObject *obj, QEvent *e) override;
    void resizeEvent(QResizeEvent *event) override;
    void paintEvent(QPaintEvent *) override;

private slots:
    void onWindowTitleChanged(const QString &title);
    void onCdPath(const QString &path);
    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_pushButton_close_clicked();

private:
    Ui::FileSystemDialog *ui;

    MyFileSystemModel *m_fileModel;

    bool m_pressed = false;
    QPoint m_pressDistance;
};

#endif // FILESYSTEMDIALOG_H
