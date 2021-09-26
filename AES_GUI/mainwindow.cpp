#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QInputDialog>
#include <QString>
#include <QFileDialog>
#include <QByteArray>
#include <QDebug>
#include <QMessageBox>

#include <bits/stdc++.h>
#include "AES.h"

QString file_input = "";
QString file_output = "";


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionExit_triggered()
{
    exit(0);
}

void MainWindow::on_Input_button_clicked()
{
    file_input = QFileDialog::getOpenFileName(0,"Choose file","Select path");
    ui->InLine->setText(file_input);
}

void MainWindow::on_OutBrowse_clicked()
{
    file_output = QFileDialog::getSaveFileName(0,"Choose file","Select path");
    ui->OutLine->setText(file_output);
}

void MainWindow::on_Decrypt_Button_clicked()
{
    qDebug()<<"Decrypt";
    QByteArray keyba = QByteArray::fromHex( ui->KeyLine->toPlainText().toLatin1());
    QString inputfile = ui->InLine->text();
    QString outfile = ui->OutLine->text();
    int sz = (ui->SizeCombo->currentIndex());
    AES_MODE aesz;
    if(sz == 0)
    {
        aesz = AES128;
    }
    else if(sz == 1)
    {
        aesz = AES192;
    }
    else
    {
        aesz = AES256;
    }
    std::string fileName = inputfile.toLatin1().constData();
    std::string outName = outfile.toLatin1().constData();

    std::vector<unsigned char> key;
    key.resize(keyba.size());
    for(int i = 0 ; i < keyba.size();i++)
    {
        key[i] = keyba[i];
    }
    std::ifstream stream(fileName, std::ios::in | std::ios::binary);
    std::vector<unsigned char> plain((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());
    std::vector<unsigned char> decrypt;
    decrypt.resize(plain.size());
    AES_TYPE mode =  NOPADDING;
    if(ui->RFCcheckBox->isChecked())
    {
        qDebug()<<"Checked";
        mode = RFC5652;
    }
    /**************************Decrypt Data *******************************/
    AES_Decrypt(key,plain,decrypt,aesz,mode);
    /********************* Write to file ****************************/
    std::ofstream fout(outName, std::ios::out | std::ios::binary);
    fout.write((char*)&decrypt[0], decrypt.size());
    fout.close();
    QMessageBox::information(0, "Done", "Decryption Done");
}

void MainWindow::on_Encrypt_Button_clicked()
{

    qDebug()<<"Encrypt";
    QByteArray keyba = QByteArray::fromHex( ui->KeyLine->toPlainText().toLatin1());
    QString inputfile = ui->InLine->text();
    QString outfile = ui->OutLine->text();
    int sz = (ui->SizeCombo->currentIndex());
    AES_MODE aesz;
    if(sz == 0)
    {
        aesz = AES128;
    }
    else if(sz == 1)
    {
        aesz = AES192;
    }
    else
    {
        aesz = AES256;
    }
    std::string fileName = inputfile.toLatin1().constData();
    std::string outName = outfile.toLatin1().constData();

    std::vector<unsigned char> key;
    key.resize(keyba.size());
    for(int i = 0 ; i < keyba.size();i++)
    {
        key[i] = keyba[i];
    }
    std::ifstream stream(fileName, std::ios::in | std::ios::binary);
    std::vector<unsigned char> plain((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());
    std::vector<unsigned char> encrypt;
    encrypt.resize(plain.size());
    AES_TYPE mode =  NOPADDING;
    if(ui->RFCcheckBox->isChecked())
    {
        qDebug()<<"Checked";
        mode = RFC5652;
    }
    /************************* Encrypt Data *******************************/
    AES_Encrypt(key,plain,encrypt,aesz,mode);
    /********************* Write to file ****************************/
    std::ofstream fout(outName, std::ios::out | std::ios::binary);
    fout.write((char*)&encrypt[0], encrypt.size());
    fout.close();
    QMessageBox::information(0, "Done", "Encryption Done");
}
