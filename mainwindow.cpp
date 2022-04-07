#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include "ZorkUL.h"
#include "Character.h"
#include <QDialog>
#include "inventorywidget.h"
#include "wordle.h"

using namespace std;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    isMapOpen(false),
    ui(new Ui::MainWindow)

{
    ui->setupUi(this);
    HideUI();
    setWindowTitle("Zork");


    if (Instance == nullptr)
    {
        Instance = this;
        inventory = new InventoryWidget();

    }
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::Print(QString message)
{
    ui->MainText->append(message + "\n");

}



void MainWindow::on_NorthButton_clicked()
{
    QString description = ZorkUL::Instance->go("north");
    Print(description);
    UpdateCurrentRoom();
}


void MainWindow::on_SouthButton_clicked()
{
    QString description = ZorkUL::Instance->go("south");
    Print(description);
    UpdateCurrentRoom();
}


void MainWindow::on_EastButton_clicked()
{
    QString description = ZorkUL::Instance->go("east");
    Print(description);
    UpdateCurrentRoom();
}


void MainWindow::on_WestButton_clicked()
{
    QString description = ZorkUL::Instance->go("west");
    Print(description);
    UpdateCurrentRoom();
}

void MainWindow::UpdateCurrentRoom()
{
    Room *currentRoom = ZorkUL::Instance->GetCurrentRoom();
    QString roomName = "Current room: " + currentRoom->shortDescription() ;
    ui->RoomLabel->setText(roomName );

    Print(currentRoom->longDescription());
    InitializeItemsRooms();
    InitializeEnemiesInRoom();
    if (currentRoom->shortDescription() == "F")
    {
       StartWordle();
    }
    else
    {
        EndWordle();
    }
}


void MainWindow::StartWordle()
{
    wordle = new Wordle(Character::Instance->GetLives());
    ui->inputWordle->show();
    ui->validateWordButton->show();
}

void MainWindow::EndWordle()
{
    ui->inputWordle->hide();
    ui->validateWordButton->hide();
    /*if (wordle != nullptr)
    {
        delete wordle;
    }*/
}

void MainWindow::InitializeEnemiesInRoom()
{
    ui->EnemiesInRoom->clear();
    Room *currentRoom = ZorkUL::Instance->GetCurrentRoom();
    for (size_t i = 0; i < currentRoom->enemiesInRoom.size(); i++ )
    {
        currentRoom->enemiesInRoom[i]->PrintInfo();
        ui->EnemiesInRoom->addItem(currentRoom->enemiesInRoom[i]->getShortDescription());
    }
}
void MainWindow::InitializeItemsRooms()
{
    ui->ItemsRoom->clear();

    Room* currentRoom = ZorkUL::Instance->GetCurrentRoom();
    for (size_t i = 0; i < currentRoom->itemsInRoom.size(); i++)
    {
        ui->ItemsRoom->addItem(currentRoom->itemsInRoom[i]->GetName());
    }
}

void MainWindow::on_MapButton_clicked()
{
    if (isMapOpen)
    {
        ui->MapLabel->hide();
    }
    else
    {
        ui->MapLabel->show();
    }
    isMapOpen = !isMapOpen;
}


void MainWindow::on_TakeButton_clicked()
{
    int index = ui->ItemsRoom->currentIndex();
    if (index == -1)
    {
        return;
    }
    if (ui->EnemiesInRoom->count() > 0)
    {
        Print("Some enemies prevent you from taking the items");
        return;
    }

    if (Character::Instance->GetNbItems() == MAX_ITEMS)
    {
        Print("You have reached the maximum number of items in your inventory");
        return;
    }


    Item* itemPickUp = ZorkUL::Instance->GetCurrentRoom()->removeItemFromRoom(index);

    InitializeItemsRooms();
    if (itemPickUp->GetType() == ObjectType::weapon)
    {
        Character::Instance->ChangeWeapon((Weapon*)itemPickUp);
        ui->CurrentWeaponLabel->setText("Weapon : " + ((Weapon *)itemPickUp)->GetLongDescription());
        Print("Your weapon is now " + ((Weapon*)itemPickUp)->GetLongDescription());
    }
    else
    {
        Print("You picked up " + itemPickUp->GetName());
        if (itemPickUp->GetName() == "Map")
        {
            if (Character::Instance->IsAlreadyInInventory(itemPickUp))
            {
                Print("You already have a map");
            }
            else
            {
                ui->MapButton->show();
                 Character::Instance->addItem(itemPickUp);
            }
        }
       else
        {
             Character::Instance->addItem(itemPickUp);
        }
    }
}



void MainWindow::on_validateInputName_clicked()
{
    QString name = ui->inputName->toPlainText();
    Character::Instance = new Character(name);
    ui->inputName->hide();
    ui->validateInputName->hide();
    ui->nameLabel->setText("Name: " + name);
    ShowUI();
    UpdateCurrentRoom();
}


void MainWindow::ShowUI()
{
    ui->EastButton->show();
    ui->NorthButton->show();
    ui->SouthButton->show();
    ui->WestButton->show();
    //ui->MapButton->show();
    ui->ItemsRoom->show();
    ui->TakeButton->show();
    ui->teleportButton->show();
    ui->EnemiesInRoom->show();
    ui->AttackButton->show();
    ui->InventoryButton->show();
    ui->ItemsInRoomLabel->show();
    ui->EnemiesInRoomLabel->show();
    ui->LivesLabel->show();
    ui->CurrentWeaponLabel->show();
    ui->RoomLabel->show();
}

void MainWindow::HideUI()
{
    ui->EastButton->hide();
    ui->NorthButton->hide();
    ui->SouthButton->hide();
    ui->WestButton->hide();
    ui->MapButton->hide();
    ui->ItemsRoom->hide();
    ui->TakeButton->hide();
    ui->MapLabel->hide();
    ui->teleportButton->hide();
    ui->EnemiesInRoom->hide();
    ui->AttackButton->hide();
    ui->InventoryButton->hide();
    ui->ItemsInRoomLabel->hide();
    ui->EnemiesInRoomLabel->hide();
    ui->LivesLabel->hide();
    ui->CurrentWeaponLabel->hide();
    ui->RoomLabel->hide();
    ui->restartButton->hide();
    ui->inputWordle->hide();
    ui->validateWordButton->hide();
}

void MainWindow::on_teleportButton_clicked()
{
    if (ZorkUL::Instance->GetCurrentRoom()->enemiesInRoom.size() > 0)
    {
        Print("Some enemies prevent you from teleporting");
        return;
    }
    ZorkUL::Instance->Teleport();
    Print("You were teleported in room "+  ZorkUL::Instance->GetCurrentRoom()->shortDescription());
    UpdateCurrentRoom();
}


void MainWindow::on_AttackButton_clicked()
{
    int index = ui->EnemiesInRoom->currentIndex();
    if (index == -1)
    {
        return;
    }
    Enemy* enemy = ZorkUL::Instance->GetCurrentRoom()->enemiesInRoom[index];
    Character::Instance->Attack(enemy, index);

    InitializeEnemiesInRoom();
    ZorkUL::Instance->EnemiesAttack();
    UpdateLives();
}


void MainWindow::on_InventoryButton_clicked()
{
    vector<Item *> items = Character::Instance->inventory;



//    QDialog* inventoryWindow = new QDialog(this, Qt::Widget);
//    inventoryWindow->setWindowTitle("Inventory");
//    inventoryWindow->setGeometry(0,0 ,200, 200);
//    inventoryWindow->setLayout(new QGridLayout());

    inventory->ClearInventory();
    inventory->MoveToCenter();
    if (items.size() == 0)
    {
        //inventoryWindow->layout()->addWidget(new QLabel("Your inventory is empy", inventoryWindow));
        inventory->Add(new QLabel("Your inventory is empy",inventory));
    }
    else
    {
        for (size_t i = 0; i < items.size(); i++)
        {
            //QPushButton *button = new QPushButton(items[i]->GetName(), inventoryWindow);
            QPushButton *button = new QPushButton(items[i]->GetName(), inventory);
            //inventoryWindow->layout()->addWidget(button);
            QObject::connect(button, SIGNAL(clicked()), SLOT(on_InventoryItemClicked()));
            inventory->Add(button);

        }
    }

    inventory->Show();
    //inventoryWindow->show();
}

void MainWindow::on_InventoryItemClicked()
{
    QObject *button = sender();
    int inventoryIndex = inventory->GetLayout() ->indexOf((QWidget*) button);
    Item *item = Character::Instance->GetItem(inventoryIndex);
    item->UseItem(inventoryIndex);
    UpdateLives();

}

void MainWindow::UpdateLives()
{
    ui->LivesLabel->setText("Lives: " + ((QString::number(Character::Instance->GetLives()))));
    if (Character::Instance->GetLives() <= 0)
    {
        HideUI();
        Print("You are dead");
        Print("Restart ?");
        ui->restartButton->show();
    }
}

void MainWindow::on_restartButton_clicked()
{
    QString playerName = Character::Instance->shortDescription();
    delete Character::Instance;
    Character::Instance = new Character(playerName);
    ZorkUL::Instance->play();
    ShowUI();
    ui->LivesLabel->setText("Lives: " + QString::number(Character::Instance->GetLives()));
    ui->CurrentWeaponLabel->setText("Weapon" + Character::Instance->GetCurrentWeapon()->GetLongDescription());
    UpdateCurrentRoom();
    ui->restartButton->hide();
    ui->MapButton->hide();
    ui->MapLabel->hide();
    ui->MainText->clear();
    ZorkUL::Instance->printWelcome();
}


void MainWindow::on_validateWordButton_clicked()
{
    QString inputWord = ui->inputWordle->toPlainText();
    ui->inputWordle->clear();
    int result = wordle->CompareWords(inputWord);
    if (result == 1)
    {
        Character::Instance->ReceiveDamage(1);
        UpdateLives();
    }
    else if (result == 2)
    {
        ShowVictory();
    }
}

void MainWindow::ShowVictory()
{
    Print("You finish the game !!!");
    Print("Do you want to restart ?");
    ui->restartButton->show();
}
