#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionNowy_triggered();

    void on_actionOtw_rz_triggered();

    void on_actionZapisz_triggered();

    void on_actionZapisz_jako_triggered();

    void on_actionCofnij_triggered();

    void on_actionWytnij_triggered();

    void on_actionKopiuj_triggered();

    void on_actionWklej_triggered();

    void on_actionPogrubiony_triggered();

    void on_actionKursywa_triggered();

    void on_actionPodkre_lenie_triggered();

    void on_actionCzcionka_triggered();

    void on_actionNotatnik_informacje_triggered();

    void on_actionPowt_rz_triggered();

    void on_actionZamknij_triggered();

    void on_textEdit_textChanged();

private:
    Ui::MainWindow *ui;
    QString sciezka_pliku;
};

#endif // MAINWINDOW_H
