/* Edytor tekstu
 * widget plainText
 * przyciski zmiany stylu czcionki (textEdit->setFontItalic(true/false))
 * slider z labelem i możlowością ustawienie wielkości czcionki
 * zapisywanie tekstu do plików i wczytywanie z pliku txt
 * analiza tekstu (ile słów, liter, średnio liter na słowo, słów jednoliterowych)
 * dodatkowo:listy dynamiczne
 */
#include <cmath>
#include <QFontDialog>
#include <QTextCharFormat>
#include <QFont>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "analizator.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);

    setWindowTitle("Bez tytułu - Notatnik");
    QString komunikat = "Wyrazy: 0, litery: 0, średnio liter na słowo: 0, słów jednoliterowych: 0.";
    MainWindow::statusBar()->showMessage(komunikat);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNowy_triggered()
{
    sciezka_pliku.clear();
    ui->textEdit->setText(QString());
}

void MainWindow::on_actionOtw_rz_triggered()
{
    QString nazwa_pliku = QFileDialog::getOpenFileName(this, "Otwórz plik", "/", "Pliki tekstowe (*.txt)");

    QFile plik(nazwa_pliku);
    sciezka_pliku = nazwa_pliku;
    QString nazwa_pliku_skrot = plik.fileName().section("/",-1,-1);
    if(!plik.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(this,"Uwaga!","Nie można otworzyć pliku: " + plik.errorString());
        return;
    }
    setWindowTitle(nazwa_pliku_skrot + " - Notatnik");
    QTextStream wejscie(&plik);
    QString text = wejscie.readAll();
    ui->textEdit->setText(text);
    plik.close();
}

void MainWindow::on_actionZapisz_triggered()
{
        QString nazwa_pliku;

        if (sciezka_pliku.isEmpty()) {
            nazwa_pliku = QFileDialog::getSaveFileName(this, "Zapisz plik", "/", "Pliki tekstowe (*.txt)");
            sciezka_pliku = nazwa_pliku;
        } else {
            nazwa_pliku = sciezka_pliku;
        }
        QFile plik(nazwa_pliku);
        if (!plik.open(QIODevice::WriteOnly | QFile::Text)) {
            QMessageBox::warning(this, "Uwaga!", "Nie można zapisać pliku: " + plik.errorString());
            return;
        }
        QString nazwa_pliku_skrot = plik.fileName().section("/",-1,-1);
        setWindowTitle(nazwa_pliku_skrot + " - Notatnik");
        QTextStream wyjscie(&plik);
        QString text = ui->textEdit->toPlainText();
        wyjscie << text;
        plik.close();
}

void MainWindow::on_actionZapisz_jako_triggered()
{



    QString nazwa_pliku = QFileDialog::getSaveFileName(this, "Zapisz plik jako", "/", "Pliki tekstowe (*.txt)");
    sciezka_pliku = nazwa_pliku;


    QFile plik(nazwa_pliku);
    if (!plik.open(QIODevice::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Uwaga!", "Nie można zapisać pliku: " + plik.errorString());
        return;
    }

    QString nazwa_pliku_skrot = plik.fileName().section("/",-1,-1);
    setWindowTitle(nazwa_pliku_skrot + " - Notatnik");
    QTextStream wyjscie(&plik);
    QString text = ui->textEdit->toPlainText();
    wyjscie << text;
    plik.close();
}

void MainWindow::on_actionCofnij_triggered()
{
    ui->textEdit->undo();
}

void MainWindow::on_actionWytnij_triggered()
{
    ui->textEdit->cut();
}

void MainWindow::on_actionKopiuj_triggered()
{
    ui->textEdit->copy();
}

void MainWindow::on_actionWklej_triggered()
{
    ui->textEdit->paste();
}

void MainWindow::on_actionPogrubiony_triggered()
{
     int bold = ui->textEdit->fontWeight();
     if (bold!=75) ui->textEdit->setFontWeight(QFont::Bold);
     else ui->textEdit->setFontWeight(QFont::Normal);

}

void MainWindow::on_actionKursywa_triggered()
{
    bool italic = ui->textEdit->fontItalic();
    if (!italic) ui->textEdit->setFontItalic(true);
    else ui->textEdit->setFontItalic(false);
}

void MainWindow::on_actionPodkre_lenie_triggered()
{
    bool underline = ui->textEdit->fontUnderline();
    if (!underline) ui->textEdit->setFontUnderline(true);
    else ui->textEdit->setFontUnderline(false);
}

void MainWindow::on_actionCzcionka_triggered()
{
    bool ok = 0;
    QFont font = QFontDialog::getFont(&ok, this);
    if (ok)
    {

        ui->textEdit->setFont(font);
    }


}

void MainWindow::on_actionNotatnik_informacje_triggered()
{
    QMessageBox::information(this,"Informacje o Notatniku","Notatnik wersja v1.0. Wykonany przez Pawła Górskiego.");
}

void MainWindow::on_actionPowt_rz_triggered()
{
    ui->textEdit->redo();
}

void MainWindow::on_actionZamknij_triggered()
{
    this->close();
}

void MainWindow::on_textEdit_textChanged()
{
    analizator tekst;
    tekst.str = ui->textEdit->toPlainText();
    QStringList lista = tekst.zrobListe(tekst.str);
    int slowa = lista.size();
    int litery = tekst.ileLiter();
    int litery_na_slowo;

    if (slowa!=0) litery_na_slowo = round((double)litery/(double)slowa);
    else litery_na_slowo = 0;

    int slow_jedno = tekst.ileSlowJednoliter(lista);
    QString komunikat = "Wyrazy: " + QString::number(slowa) + ", litery: " + QString::number(litery) +
            ", średnio liter na słowo: " + QString::number(litery_na_slowo) + ", słów jednoliterowych: " +
            QString::number(slow_jedno) + ".";
    MainWindow::statusBar()->showMessage(komunikat);

}
