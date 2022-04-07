#ifndef INVENTORYWIDGET_H
#define INVENTORYWIDGET_H

#include <QObject>
#include <QGridLayout>
#include <QWidget>
#include <QDialog>

class InventoryWidget :  public QDialog
{
    Q_OBJECT
private:
    QGridLayout *layout;

public:
    inline static InventoryWidget *Instance = nullptr;
    bool isOpen;
    QDialog *inventoryWindow;

    InventoryWidget();

    void ClearInventory();
    void RemoveItem(int index);
    void Add(QWidget* w);
    void Show();
    void MoveToCenter();
    QGridLayout* GetLayout();
};

#endif // INVENTORYWIDGET_H
