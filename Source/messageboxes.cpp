#include "messageboxes.h"

MessageBoxes::MessageBoxes()
{

}

void MessageBoxes::showDeleteMsBox()
{
    QMessageBox deleteMsBox;
    deleteMsBox.setWindowTitle("Delete File");
    //    deleteMsBox.setIcon(QMessageBox::Question);
    deleteMsBox.setText("Are you sure you want to delete this date?");
    deleteMsBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    deleteMsBox.setDefaultButton(QMessageBox::No);
    deleteMsBox.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    deleteMsBox.setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint); //hide message box icon
    deleteMsBox.setMinimumSize(300, 200); //need this to fix a warning
    deleteMsBox.setStyleSheet("QLabel{min-width: 300px;}");
    int ret = deleteMsBox.exec();

    switch (ret) {
    case QMessageBox::Yes:
        emit deletionConfirmed();
        break;
    case QMessageBox::No:
        deleteMsBox.close();
        break;
    default:
        break;
    }
}
