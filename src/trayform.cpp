#include "trayform.h"
#include "ui_trayform.h"

TrayForm::TrayForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TrayForm)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::Popup);

    // Setup the tray icon
    trayIcon = new QSystemTrayIcon(QIcon(":/resources/tray.png"));
    trayIcon->setToolTip(QString("Visual Translator"));
    trayIcon->show();
    connect(trayIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(showMenu()));
}

TrayForm::~TrayForm()
{
    delete ui;
}

void TrayForm::showMenu()
{
    // search for the correct position
    int screenWidth = QApplication::desktop()->screenGeometry().width();
    int screenHeight = QApplication::desktop()->screenGeometry().height();
    QRect trayIconGeometry = trayIcon->geometry();
    QPoint formPosition = QPoint(trayIconGeometry.x(), trayIconGeometry.y());

    // TODO check with non-default dock position (left, right, top)

    if (formPosition.x() + this->width() > screenWidth) {
        formPosition.setX(screenWidth - this->width());
    }

    if (formPosition.y() + this->height() > screenHeight) {
        formPosition.setY(screenHeight - this->height() - trayIconGeometry.height());
    }

    this->move(formPosition);
    this->show();
}
