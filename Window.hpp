#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <QMainWindow>

namespace Ui {
class Window;
}

class Window : public QMainWindow
{
    Q_OBJECT

public:
    explicit Window(QWidget *parent = 0);
    ~Window();

private slots:
    void on_rscFileSearchButton_clicked();

    void on_rscDirSearchButton_clicked();

    void on_exitButton_clicked();

    void on_updateButton_clicked();

private:
    Ui::Window *ui;


    QString tagName(QString name);

    void update();

};

#endif // WINDOW_HPP
