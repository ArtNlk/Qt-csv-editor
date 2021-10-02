#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QMessageBox>
#include <QCommandLineParser>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCommandLineParser parser;

    QCommandLineOption localeOption("locale");
    parser.addOption(localeOption);
    parser.process(a);

    QLocale locale;
    if(parser.value("locale") == "ru")
    {
        locale = QLocale::Russian;
    }else if(parser.value("locale") == "en")
    {
        locale = QLocale::English;
    }else
    {
        locale = QLocale::system();
    }

    const char* dirs[] = {
        "../translations",
        "/translations",
        0
    };

    QTranslator translator;
    bool translatorLoaded = false;
    for(const char* dir : dirs)
    {
        translatorLoaded = translator.load(locale,"Qt-csv-editor","_",dir);
        if(translatorLoaded) break;
    }
    if(!translatorLoaded){
        QMessageBox::warning(nullptr,
                             "Переводчик",
                             QString("Ошибка загрузки переводчика для %1").arg(QLocale::system().name()));
    }
    else
    {
        a.installTranslator(&translator);
    }
    MainWindow w;
    w.show();
    return a.exec();
}
