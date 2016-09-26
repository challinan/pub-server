#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "pmd-datagen.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
	printf("MainWindow startup\n");
    ui->setupUi(this);
    ui->myLabel->setText("PMD Data Simulator");

	// Start the listener	
	PmdDatagen *ds = new PmdDatagen(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    exit(0);
}

void MainWindow::connectionStatusMainWindow(bool status)
{
    QDateTime dateTime = QDateTime::currentDateTime();
    QString dateTimeString = dateTime.toString("hh:mmap");
	QByteArray dateStrArray = dateTimeString.toUtf8();
	char *pstr = dateStrArray.data();
	printf("MainWindow::connectionStatusMainWindow() %s\n", (status == false) ? "disconnected" : "connected");
	printf("MainWindow::connectionStatusMainWindow(): %s\n", pstr); 
}

