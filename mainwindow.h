#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "item.h"
#include "inventorywidget.h"
#include "wordle.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

using namespace std;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    inline static MainWindow *Instance = nullptr;

    void Print(QString message);

private slots:

    void on_NorthButton_clicked();

    void on_SouthButton_clicked();

    void on_EastButton_clicked();

    void on_WestButton_clicked();

    void on_MapButton_clicked();

    void on_TakeButton_clicked();

    void on_validateInputName_clicked();

    void on_teleportButton_clicked();

    void on_AttackButton_clicked();

    void on_InventoryItemClicked();

    void on_restartButton_clicked();

    void on_validateWordButton_clicked();

public slots:
    void on_InventoryButton_clicked();

private:
    bool isMapOpen;
    Ui::MainWindow *ui;
    InventoryWidget* inventory;
    Wordle *wordle;


    void InitializeItemsRooms();
    void InitializeEnemiesInRoom();
    void UpdateCurrentRoom();
    void ShowUI();
    void HideUI();
    void UpdateLives();
    void StartWordle();
    void EndWordle();
    void ShowVictory();
};
#endif // MAINWINDOW_H
