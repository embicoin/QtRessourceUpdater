#include "Window.hpp"
#include "ui_Window.h"

#include <QDebug>
#include <iostream>
#include <exception>
#include <QSvgWidget>
#include <QFileDialog>
#include <QMessageBox>

using namespace std;

Window::Window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Window)
{
    ui->setupUi(this);

    // Initialize window
    this->setWindowTitle("QRessourceUpdater");

    // Initialize icon
    QGridLayout* icon_layout = new QGridLayout(ui->icon);
    icon_layout->setMargin(0);
    icon_layout->setSpacing(0);
    icon_layout->addWidget(new QSvgWidget(":/icon/icon"));
    ui->icon->setLayout(icon_layout);

    // Initialize line
    ui->rscDirLine->setText("rsc");
    ui->rscFileLine->setText("ressources.qrc");

}

Window::~Window()
{
    delete ui;
}

void Window::on_rscFileSearchButton_clicked()
{
    // Get the file path
    QString file = QFileDialog::getOpenFileName();

    // Update ui
    ui->rscFileLine->setText(file);
}

void Window::on_rscDirSearchButton_clicked()
{
    // Get the directory path
    QString directory = QFileDialog::getExistingDirectory(this);

    // Update ui
    ui->rscDirLine->setText(directory);
}

void Window::on_exitButton_clicked()
{
    QApplication::exit();
}

void Window::on_updateButton_clicked()
{
    try
    {
        update();
    }
    catch(std::runtime_error& e)
    {
        QMessageBox msgBox;
        msgBox.setText(e.what());
        msgBox.exec();
    }
}

QString Window::tagName(QString name)
{
    return name.split('.').at(0);
}



void Window::update()
{
    if(ui->rscDirLine->text().compare("")==0)
    {
        throw std::runtime_error("Vous devez indiquer un dossier");
    }

    QDir rsc_dir(ui->rscDirLine->text());
    if(!rsc_dir.exists())
    {
        throw std::runtime_error("Le dossier n'existe pas");
    }

    QFile rsc_file(ui->rscFileLine->text());
    if(!rsc_file.exists())
    {
        throw std::runtime_error("Le fichier de ressource n'existe pas");
    }

    if(!rsc_file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        throw std::runtime_error("Le fichier n'a pas pu etre ouvert");
    }

    QTextStream out(&rsc_file);

    out << "<RCC>\n";

    // List every sub directory to get prefixe
    QFileInfoList subdirs = rsc_dir.entryInfoList( QDir::Dirs | QDir::NoDotAndDotDot |QDir::NoSymLinks );
    foreach (QFileInfo subdir, subdirs)
    {
        QString prefixe = subdir.fileName();

        out << "    <qresource prefix=\"/" << prefixe << "\">\n";

        QStringList rscs = QDir(subdir.absoluteFilePath()).entryList(QDir::Files);
        foreach (QString rsc, rscs)
        {
            QString path =  rsc_dir.dirName() + QDir::separator() +
                            prefixe + QDir::separator() + rsc;
            out << "        <file alias=\"" << tagName(rsc) << "\">" << path << "</file>\n";

        }

        out << "    </qresource>\n";
    }

    out << "</RCC>\n";


    out.flush();

    rsc_file.close();

}
