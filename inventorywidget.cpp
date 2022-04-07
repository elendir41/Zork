#include "inventorywidget.h"
#include <QDialog>
#include <QGridLayout>
#include <QPushButton>
#include <QMainWindow>
#include <QScreen>
#include <QGuiApplication>
#include "mainwindow.h"
#include "Character.h"


InventoryWidget::InventoryWidget()
{
    if (Instance == nullptr)
    {
        Instance = this;
        inventoryWindow = new QDialog(this, Qt::WindowStaysOnTopHint);
        inventoryWindow->setWindowTitle("Inventory");
        inventoryWindow->setGeometry(0,0,200,200);

        layout = new QGridLayout(inventoryWindow);
        inventoryWindow->setLayout(layout);
        isOpen = false;
    }


}

void InventoryWidget::ClearInventory()
{
    QLayoutItem *child;
    while ((child = layout->takeAt(0)) != 0)  {
        layout->removeWidget(child->widget());
        child->widget()->deleteLater();
        delete child;
    }
}

void InventoryWidget::RemoveItem(int index)
{
    QWidget *w = layout->itemAt(index)->widget();
    w->deleteLater();
    layout->removeWidget(w);
}

void InventoryWidget::Add(QWidget* w)
{
    layout->addWidget(w);
}

void InventoryWidget::Show()
{
    inventoryWindow->show();

}

QGridLayout* InventoryWidget::GetLayout()
{
    return layout;
}

void InventoryWidget::MoveToCenter()
{
    QScreen *screen        = QGuiApplication::primaryScreen();
    const int screenWidth  = screen->size().width();
    const int screenHeight = screen->size().height();
    inventoryWindow->move(screenWidth / 2 - inventoryWindow->width(), screenHeight / 2 - inventoryWindow->height());


}
