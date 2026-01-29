#include "ytdl.h"
#include "mainactions.h"

#include <QApplication>

#include <QCoreApplication>
#include <QTranslator>


//#define tr QCoreApplication::tr
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QLocale locale = QLocale::system();
    qDebug() << "Current locale:" << locale.name();
    QTranslator translator;
    QString localePath = QString(YTDL_GUI_DATA_DIR)+"locales/ytdl-gui_fr.qm" ;

    qDebug() << "Loading locale: "<< localePath;
    if (locale.name() == "fr_BE" or locale.name() == "fr_FR" or locale.name() == "fr_CA" or locale.name() == "fr") {
        if (!translator.load(localePath)) {
            qWarning() << "Failed to load translation file from installation path, will try from some other path.";
            if (!translator.load("/usr/share/ytdl-gui/locales/ytdl-gui_fr.qm")) {
                if (!translator.load("/usr/local/share/ytdl-gui/locales/ytdl-gui_fr.qm")) {
                    if (!translator.load("locales/ytdl-gui_fr.qm")) {
                        qWarning() << "Failed to load translation file.";
                    }
                }
            }
        }
    }
    a.installTranslator(&translator);
    ytdl w;
    mainActions q;
    QCoreApplication::setApplicationName(QString(QCoreApplication::tr("Youtube Downloader")));
    w.setWindowTitle( QCoreApplication::applicationName() );
    w.setWindowIcon(QIcon::fromTheme("youtubedl-gui"));
    w.show();
    return a.exec();
}
