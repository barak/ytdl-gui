#include "readconfig.h"
#include "mainactions.h"
#include <string>
#include <iostream>
#include <fstream>
#include <QPushButton>
#include <QMessageBox>
#include <QProgressBar>
#include <QShortcut>
#include <cstdlib>
#include <unistd.h>
#include <QThread>
#include <QFile>
#include <QDebug>

std::string whitespace = " ";
std::string quote = "'";

mainActions::mainActions(QObject *parent) : QObject(parent)	{
        ytdl* window = ytdl::getWinInstance();
        Ui::ytdl* ui = ytdl::getUiInstance();

        connect(ui->buttonDownload, &QPushButton::released, window, &ytdl::downloadAction);

        //connect enter to downloadAction
        QShortcut* returnAction = new QShortcut(QKeySequence("Return"), window);
        connect(returnAction, &QShortcut::activated, ui->buttonDownload, &QPushButton::click);

        //connect defaults checkbox to blurring out of options
        connect(ui->defaultsCheck, &QCheckBox::stateChanged, window, &ytdl::changeVisibility);


        // resume user settings
        if (QFile(window->file_qstr).exists()) {
            readConfig* user_settings = new readConfig(window->file_str);
            user_settings->get_values();

            //apply checkbox settings
            bool_to_checkbox(user_settings->values[0], ui->defaultsCheck);
            bool_to_checkbox(user_settings->values[1], ui->playlistCheck);

            //apply dir setting
            std::string stored_value = user_settings->values[2];
            if (!stored_value.empty() && stored_value != "Location:") {
                ui->lineBrowse->setText(QString::fromStdString(stored_value));
            }

            try {
                //apply tab setting
                ui->Tabs->setCurrentIndex(stoi(user_settings->values[3]));

                //apply audio settings
                num_to_button(ui->MQualityGroup, stoi(user_settings->values[4]), 4);
                num_to_button(ui->MFormatGroup, stoi(user_settings->values[5]), 5);

                //apply video settings
                num_to_button(ui->VResGroup, stoi(user_settings->values[6]), 5);
                num_to_button(ui->VFormatGroup, stoi(user_settings->values[7]), 4);
            }

             catch (const std::invalid_argument &e) {
                qDebug() << "Invalid argument in config file:";
                qDebug() << e.what() << "invalid argument";
            }
             catch (const std::out_of_range &e) {
                qDebug() << "Invalid argument in config file:";
                qDebug() << e.what()  << "out of range";
            }
             catch (const std::exception &e) {
                qDebug() << "Invalid argument in config file:";
                qDebug() << e.what() << "undefined error";
            }

        }


}

void mainActions::bool_to_checkbox(std::string input, QCheckBox* box) {
    if (input == "yes") {
        box->setCheckState(Qt::Checked);
    }
    else if (input == "no") {
        box->setCheckState(Qt::Unchecked);
    }
    else {
        qDebug() << "Invalid argument in config file";
    }
}

void mainActions::num_to_button(QButtonGroup* group, int sel, int total) {
    if ( -1 < sel && sel < total) {
        group->button(sel)->setChecked(true);
    }
    else {
        qDebug() << "Invalid argument in config file";
    }
}


std::string QString_to_str(QString input) {
        std::string output = input.toUtf8().constData();
        return output;
}


//Begin ytdl namespace

void ytdl::run_ytdl(std::string input) {
    //initialize youtube-dl thread
    downloadThread = new QThread;
    download_instance = new mainCommand(input);
    download_instance->moveToThread(downloadThread);

    //start thread
    connect(downloadThread, &QThread::started, this, &ytdl::messageDownload);
    connect(downloadThread, &QThread::started, this, &ytdl::setStatusClose);
    connect(downloadThread, &QThread::started, download_instance, &mainCommand::download);
    connect(download_instance, &mainCommand::returnFinished, this, [=](){setStatusClose();});
    connect(download_instance, &mainCommand::returnFinished, this, [=](int num){printResult(num);});

    //delete thread
    connect(download_instance, &mainCommand::finished, downloadThread, &QThread::quit);
    connect(this, &ytdl::userAccepted, download_instance, &QObject::deleteLater);
    connect(downloadThread, &QThread::finished, downloadThread, &QObject::deleteLater);


    //execute
    downloadThread->start();

}

void ytdl::messageDownload() {
    downloading = new downloadStatus;
    Ui::downloadStatus* download_ui = downloading->getUiInstance();

    progressThread = new QThread;
    downloadProgress* status = new downloadProgress(download_ui);
    status->moveToThread(progressThread);

    //ProgressThread connections
    //start
    connect(progressThread, &QThread::started, status, &downloadProgress::updateStatus);

    //end
    connect(status, &downloadProgress::finished, progressThread, &QThread::quit);
    connect(progressThread, &QThread::finished, status, &QObject::deleteLater);
    connect(progressThread, &QThread::finished, progressThread, &QObject::deleteLater);
    connect(this, &ytdl::closeDownloading, this, &ytdl::deleteDownloading);

    //confirmation close window
    cancel = new cancelDownload;
    QThread* cancelThread = new QThread;

    //start
    connect(downloading, &downloadStatus::openCancelWindow, cancelThread, [=](){cancelThread->start();});
    connect(downloading, &downloadStatus::openCancelWindow, cancel, &cancelDownload::show);
    connect(cancel, &cancelDownload::accepted, this, &ytdl::killDownloadProcess);

    //end
    connect(this, &ytdl::closeDownloading, cancelThread, &QThread::quit);
    connect(cancelThread, &QThread::finished, cancel, &QObject::deleteLater);
    connect(cancelThread, &QThread::finished, cancelThread, &QObject::deleteLater);

    //exec
    progressThread->start();
    downloading->exec();
}

void ytdl::killDownloadProcess() {
    no_feedback = true;
    downloading->closeDownloadWindow();

    //kill command
    download_instance->command->kill();
}


void ytdl::setStatusClose() {
    if (downloading->download_lock == false) {
        downloading->download_lock = true;
    }
    else {
        downloading->download_lock = false;
    }
}

void ytdl::deleteDownloading() {
    downloading->close();
}

void ytdl::changeVisibility(int state) {
    if (state == 2) {
        ui->Music->setEnabled(false);
        ui->Video->setEnabled(false);
    }
    else {
        ui->Music->setEnabled(true);
        ui->Video->setEnabled(true);
    }
}

void ytdl::printResult(int result_num) {
        bool is_active = downloading->isActiveWindow();
        emit closeDownloading();

        if (result_num == 0) {
                QMessageBox success;
                success.setWindowIcon(QIcon::fromTheme("youtubedl-gui"));
                success.setIcon(QMessageBox::Information);
                success.setText("Download Succeeded");

                if (!no_feedback && is_active) {
                    success.exec();
                }

                emit userAccepted();
                no_feedback = false;
        }
        else {
                QMessageBox fail;
                fail.setWindowIcon(QIcon::fromTheme("youtubedl-gui"));
                fail.setIcon(QMessageBox::Critical);
                fail.setText("Failed! Recheck input for errors.");

                if (no_feedback == false) {
                    fail.exec();
                }

                emit userAccepted();
                no_feedback = false;
        }
}

void ytdl::downloadAction() {
    std::string ytdl_prog = "youtube-dl 2> /tmp/ytdl_stderr --no-warnings --all-subs";
    std::string url_str = quote + QString_to_str(ui->lineURL->text()) + quote;
    std::string directory_str = quote + QString_to_str(ui->lineBrowse->text()) + "/%(title)s.%(ext)s" + quote;
    std::string parse_output = R"(stdbuf -o0 grep -oP '^\[download\].*?\K([0-9]+)')";
    std::string thumbnail;

    //Youtube playlist support
    std::string playlist;
    if (ui->playlistCheck->isChecked()) {
        playlist = "";
    }
    else {
        playlist = "--no-playlist ";
    }

    //Defaults override
    if (ui->defaultsCheck->isChecked()) {

        //Audio selected
        if (ui->Tabs->currentIndex() == 0) {
            std::string command = ytdl_prog + " -x " + url_str + " -o " + directory_str \
                    + " --ignore-config " + playlist + "--newline | " \
                    + parse_output;

            this->run_ytdl(command);
        }

        //Video selected
        else {
            std::string command = ytdl_prog + whitespace + url_str + " -o " + directory_str \
                    + " --ignore-config " + playlist + "--newline | " \
                    + parse_output;

            this->run_ytdl(command);
        }

    }

    //Standard options
    else {
        //Audio selected
        if (ui->Tabs->currentIndex() == 0) {
            std::string audio_format;
            switch(ui->MFormatGroup->checkedId()) {
                    case 0:
                            audio_format = "aac";
                            break;
                    case 1:
                            audio_format = "vorbis";
                            break;
                    case 2:
                            audio_format = "mp3";
                            thumbnail = "--embed-thumbnail ";
                            break;
                    case 3:
                            audio_format = "opus";
                            break;
                    case 4:
                            audio_format = "wav";
                            break;
            }

            std::string audio_quality;
            switch(ui->MQualityGroup->checkedId()) {
                    case 0:
                            audio_quality = "0";
                            break;
                    case 1:
                            audio_quality = "2";
                            break;
                    case 2:
                            audio_quality = "5";
                            break;
                    case 3:
                            audio_quality = "8";
            }


            std::string command = ytdl_prog + " -x " + url_str + " -o " + directory_str \
                    + " --audio-format " + audio_format \
                    + " --audio-quality " + audio_quality \
                    + " --ignore-config " + playlist + thumbnail + "--newline | " \
                    + parse_output;

            this->run_ytdl(command);
        }

        //Video selected
        else {
            std::string audio_format = "bestaudio";
            std::string video_format;
            switch(ui->VFormatGroup->checkedId()) {
                    case 0:
                            video_format = "3gp";
                            break;
                    case 1:
                            video_format = "flv";
                            break;
                    case 2:
                            video_format = "mp4";
                            audio_format = "m4a";
                            break;
                    case 3:
                            video_format = "webm";
                            break;
            }

            std::string video_res;
            switch(ui->VResGroup->checkedId()) {
                    case 0:
                            video_res = "2160";
                            break;
                    case 1:
                            video_res = "1440";
                            break;
                    case 2:
                            video_res = "1080";
                            break;
                    case 3:
                            video_res = "720";
                            break;
                    case 4:
                            video_res = "480";
                            break;
            }

            std::string format_options = quote + video_format + "[height=" + video_res \
                    + "]+" + audio_format + "/bestvideo[height<=" + video_res + "]+bestaudio" + quote;

            std::string command = ytdl_prog + whitespace + url_str + " -o " + directory_str \
                    + " -f " + format_options \
                    + " --ignore-config " + playlist + "--newline | " \
                    + parse_output;

            this->run_ytdl(command);
        }
    }

}
