#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>

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
    void closeEvent(QCloseEvent *);

private slots:
    void on_inputFileButton_clicked();

    void on_outputFileButton_clicked();

    void on_runButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
