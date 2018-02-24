#include "tray.h"

Tray::Tray(QWidget *parent) : QWidget(parent)
{
    // Setup the tray icon
    trayIcon = new QSystemTrayIcon(QIcon(":/resources/tray.png"));
    trayIcon->setToolTip(QString("Visual Translator"));
    trayIcon->show();

    // Setup all forms
    settingsForm = new SettingsForm(parent);
    translationResultForm = new TranslationResultForm(parent);
    translationResultForm->setWindowFlag(Qt::Popup);

    // Create a menu
    menu = new QMenu(this);
    langFromMenu = new QMenu("Translate from", menu);
    langToMenu = new QMenu("Translate to", menu);

    menu->addMenu(langFromMenu);
    menu->addMenu(langToMenu);
    menu->addSeparator();
    menu->addAction("Settings...", settingsForm, SLOT(showForm()));

    menu->addSeparator();
    menu->addAction("Exit", qApp, SLOT(quit()));

    // Fill a menu with all available languages
    foreach (Lang language, Language::languages) {
        addLanguageToMenu("from", language.name);
        addLanguageToMenu("to", language.name);
    }

    trayIcon->setContextMenu(menu);

    connect(trayIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(showMenu()));
}

void Tray::showMessage(const QString &message)
{
    translationResultForm->ui->textEdit->setText(message);

    // search for the correct position for the translationResultForm
    int screenWidth = QApplication::desktop()->screenGeometry().width();
    int screenHeight = QApplication::desktop()->screenGeometry().height();
    QRect trayIconGeometry = trayIcon->geometry();
    QPoint formPosition = QPoint(trayIconGeometry.x(), trayIconGeometry.y());

    // TODO check with non-default dock position (left, right, top)
    if (formPosition.x() + translationResultForm->width() > screenWidth - 100) {
        formPosition.setX(screenWidth - translationResultForm->width());
    }

    if (formPosition.y() + translationResultForm->height() > screenHeight - 100) {
        formPosition.setY(screenHeight - translationResultForm->height() - trayIconGeometry.height());
    }

    translationResultForm->move(formPosition);
    translationResultForm->show();
}

void Tray::chooseFromLang()
{
    QAction *action = qobject_cast<QAction*>(sender());
    App::theApp()->settings()->setValue("/Settings/Languages/from", action->data().toString());
}

void Tray::chooseToLang()
{
    QAction *action = qobject_cast<QAction*>(sender());
    App::theApp()->settings()->setValue("/Settings/Languages/to", action->data().toString());
}

void Tray::addLanguageToMenu(QString type, QString name)
{
    QString settingsLangFrom = App::theApp()->settings()->value("/Settings/Languages/from", "English").toString();
    QString settingsLangTo = App::theApp()->settings()->value("/Settings/Languages/to", "English").toString();

    QAction *item = new QAction(name);
    item->setCheckable(true);
    item->setData(QVariant(name));
    item->setIcon(QIcon(Language::getIconPath(name)));

    if (type == "from") {
        bool isInserted = false;

        // search for the separator and if exist - add menu item before it
        foreach (QAction* a, langFromMenu->actions())
        {
            if (a->isSeparator()) {
                langFromMenu->insertAction(a, item);
                isInserted = true;
            }
        }

        // if there was no separator - just add a new menu item
        if (!isInserted) langFromMenu->addAction(item);

        if (name == settingsLangFrom) item->setChecked(true);
        QObject::connect(item, SIGNAL(triggered()), this, SLOT(chooseFromLang()));
    }

    if (type == "to") {
        langToMenu->addAction(item);
        if (name == settingsLangTo) item->setChecked(true);
        QObject::connect(item, SIGNAL(triggered()), this, SLOT(chooseToLang()));
    }
}

void Tray::removeLanguageFromMenu(QString name)
{
    foreach (QAction* a, langFromMenu->actions())
    {
        if (a->data().toString() == name) {
            langFromMenu->removeAction(a);
            break;
        }
    }
}

void Tray::showMenu()
{
    trayIcon->contextMenu()->exec(QCursor::pos());
}

void Tray::languageAdded(QString name)
{
    addLanguageToMenu("from", name);
}

void Tray::languageRemoved(QString name)
{
    removeLanguageFromMenu(name);
}
