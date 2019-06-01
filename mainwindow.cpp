#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_triggered()
{
    currentFile.clear();
    ui->textEdit->setText(QString());
    setWindowTitle("Untitled");
}



void MainWindow::on_actionOpen_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, "Open the file", "~/");
    QFile file(filename);

    // Update current file name
    currentFile = filename;

    // Check if file is not read only
    if(!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot open file : " + file.errorString());
        return;
    }

    // Set window title as file name
    setWindowTitle(currentFile);

    // Setup file reading mechanism
    QTextStream in(&file);
    QString text = in.readAll();

    // Display text of file
    ui->textEdit->setText(text);

    // Close the file
    file.close();
}

void MainWindow::on_actionSave_triggered()
{
    QFile file(currentFile);
    // Check if we have write permission
    if(!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot save file : " + file.errorString());
        return;
    }

    // Setup file saving mechanism
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
}

void MainWindow::on_actionSave_as_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this, "Save as", "~/");
    QFile file(filename);

    // Check if we have write permission
    if(!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot save file : " + file.errorString());
        return;
    }

    // Set window title as file name
    currentFile = filename;
    setWindowTitle(currentFile);

    // Setup file saving mechanism
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;


    // Close file
    file.close();

}

void MainWindow::on_actionPrint_triggered()
{
    QPrinter printer;
    printer.setPrinterName("Printer name");
    QPrintDialog pDialog(&printer, this);
    if(pDialog.exec() == QDialog::Rejected) {
        QMessageBox::warning(this, "Warning", "Cannot print file");
        return;
    }
    ui->textEdit->print(&printer);
}

void MainWindow::on_actionQuit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}


