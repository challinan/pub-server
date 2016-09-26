#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "pmd-datagen.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
	// Ui::MainWindow *getMainWindow();

private slots:
    void on_pushButton_clicked();
	void connectionStatusMainWindow(bool status);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
