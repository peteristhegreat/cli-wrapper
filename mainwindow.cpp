#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QProcess>
#include <QSettings>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QSettings s;
    this->restoreGeometry(s.value("geometry").toByteArray());
    this->restoreState(s.value("state").toByteArray());

    ui->inputFileLabel->setText(s.value("input_file").toString());
    ui->outputFileLabel->setText(s.value("output_file").toString());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *)
{
    QSettings s;
    s.setValue("geometry", this->saveGeometry());
    s.setValue("state", this->saveState());
    s.setValue("input_file", ui->inputFileLabel->text());
    s.setValue("output_file", ui->outputFileLabel->text());
}

void MainWindow::on_inputFileButton_clicked()
{
    QString inputFile = QFileDialog::getOpenFileName();
    if(inputFile != QString())
        ui->inputFileLabel->setText(inputFile);
}

void MainWindow::on_outputFileButton_clicked()
{
    QString saveFile = QFileDialog::getSaveFileName();
    if(saveFile != QString())
        ui->outputFileLabel->setText(saveFile);
}

void MainWindow::on_runButton_clicked()
{
    // TODO: show progress bar, maybe as a widget in the progress bar
    // TODO: show an hour glass for the cursor
    // TODO: add slots for catching and displaying the output in real time

    ui->statusBar->showMessage("Starting process...");

    QString inputFile = ui->inputFileLabel->text();
    QString outputFile = ui->outputFileLabel->text();

    qDebug() << "pwd" << QDir::currentPath();


    QString program = "hello_world.exe";
    QStringList arguments;
    arguments << "-i" << inputFile
              << "-o" << outputFile;

    QProcess *myProcess = new QProcess(this);
    myProcess->start(program, arguments);

    bool started = myProcess->waitForStarted();
    qDebug() << "started?" << started;
    qDebug() << "Error string" << myProcess->errorString();

    myProcess->waitForFinished();

    QString stdOut = myProcess->readAllStandardOutput();

    qDebug() << stdOut;

    // TODO: parse the output and put it in the tableWidget.


    ui->statusBar->showMessage("...process finished.");
}
