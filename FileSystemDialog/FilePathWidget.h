#ifndef FILEPATHWIDGET_H
#define FILEPATHWIDGET_H

#include <QWidget>
#include <QPushButton>

class PathButton : public QPushButton
{
    Q_OBJECT

public:
    explicit PathButton(QWidget *parent = 0) : QPushButton(parent)
    {

    }

    void setPath(const QString &path)
    {
        m_path = path;
    }
    QString path()
    {
        return m_path;
    }

private:
    QString m_path;
};

namespace Ui {
class FilePathWidget;
}

class FilePathWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FilePathWidget(QWidget *parent = 0);
    ~FilePathWidget();

    void setRootPath(const QString &path);
    void cdPath(const QString &path);

protected:
    void paintEvent(QPaintEvent *) override;

signals:
    void sig_cdPath(const QString &path);

private slots:
    void onPathButtonClicked();

private:
    Ui::FilePathWidget *ui;

    QList<PathButton *> m_listPathButton;
};

#endif // FILEPATHWIDGET_H
