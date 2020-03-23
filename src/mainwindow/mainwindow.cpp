#include <QMessageBox>
#include <QDebug>

#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow) {
    setWindowIcon(QIcon(":/icons/morseparser.ico"));

    ui->setupUi(this);

    // set icon and toolTip on swap button
    ui->buttonSwap->setIcon(QIcon(":/icons/swap.ico"));
    ui->buttonSwap->setToolTip("Swap languages");

    // connect all signals to slots
    connect(ui->actionAbout_developer, SIGNAL(triggered()), this, SLOT(actions()));
    connect(ui->actionAbout_program, SIGNAL(triggered()), this, SLOT(actions()));
    connect(ui->actionRefresh, SIGNAL(triggered()), this, SLOT(actions()));
    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(actions()));
    connect(ui->actionShow_Morse_table, SIGNAL(triggered()), this, SLOT(actions()));

    connect(ui->buttonSwap, SIGNAL(clicked()), this, SLOT(swap()));

    connect(ui->buttonTranslate, SIGNAL(clicked()), this, SLOT(parse()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::actions() {
    auto *action = (QAction *) sender();

    if (action == ui->actionAbout_program) {
        QMessageBox::information(this, "MorseParser",
                                 "Simple Morse parser\n"
                                 "May have a lot of bugs and mistakes\n"
                                 "Used technologies:\n"
                                 "C++, Qt, CMake");
    } else if (action == ui->actionAbout_developer) {
        QMessageBox::information(this, "MorseParser",
                                 "Find me in the Web!\n"
                                 "Telegram: @vlad_is_real\n"
                                 "GMail: vladislav.kolyadenko@gmail.com\n"
                                 "Instagram: @ncks_gwc");
    } else if (action == ui->actionShow_Morse_table) {
        QMessageBox msgBox;

        msgBox.setWindowTitle("MorseParser");
        msgBox.setIconPixmap(QPixmap(":images/morsetable.jpg"));
        msgBox.show();
        msgBox.exec();
    } else if (action == ui->actionRefresh) {
        // clear text
        ui->textEditLeft->clear();
        ui->textEditRight->clear();
    } else if (action == ui->actionExit)
        QApplication::quit();
    else {
        qDebug() << "Invalid action!\n";

        QApplication::exit(EXIT_FAILURE);
    }
}

void MainWindow::swap() {
    // swap labels (had to do it manually because QString swap didn't work)
    QString temp = ui->labelLeft->text();
    ui->labelLeft->setText(ui->labelRight->text());
    ui->labelRight->setText(temp);

    // swap texts
    temp = ui->textEditRight->toPlainText();
    ui->textEditRight->setText(ui->textEditLeft->toPlainText());
    ui->textEditLeft->setText(temp);

    // swap placeholder texts depending on translated language
    if (ui->labelLeft->text() == "Morse") {
        ui->textEditLeft->setPlaceholderText("Enter Morse signal here");
        ui->textEditRight->setPlaceholderText("Translation to English");
    } else {
        ui->textEditLeft->setPlaceholderText("Enter text here");
        ui->textEditRight->setPlaceholderText("Translation to Morse");
    }
}

void MainWindow::parse() {
    QString temp;

    if (ui->labelLeft->text() == "English") {
        // parse every character in Morse signal and push it in temp string
                foreach(auto val, ui->textEditLeft->toPlainText())
                temp.push_back(
                        english_morse.value(val.toUpper()) + ' ');

        // push the result in the right text edit
        ui->textEditRight->setText(temp);
    } else { // need to be fixed
        QString tmpChar;

        // add space to the end to get the last symbol
        ui->textEditLeft->setText(ui->textEditLeft->toPlainText() + ' ');

        // push all symbols in the tmpChar until space
        // then parse it in English and push it in the temp string
                foreach(const auto &val, ui->textEditLeft->toPlainText()) {
                if (val != ' ')
                    tmpChar.push_back(val);
                else {
                    temp.push_back(english_morse.key(tmpChar));
                    tmpChar.clear();
                }
            }

        // push the result in the right text edit
        ui->textEditRight->setText(temp);
    }
}