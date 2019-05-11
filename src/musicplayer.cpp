#include "musicplayer.h"
#include "ui_musicplayer.h"
#include "dbcontrol.h"

#include <QDebug>
#include <QString>
#include <QMediaPlayer>
#include <QFileDialog>

#define DEBUG(x) qDebug()<<__FUNCTION__<<__LINE__<<x

//class denoiser;

MusicPlayer::MusicPlayer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MusicPlayer)
{
    ui->setupUi(this);

    DBControl::instance()->connectDb();

    connect(ui->selectLocalMusicBtn,SIGNAL(clicked()),this,SLOT(getFile()));
    //connect(ui->playButton,SIGNAL(clicked()),this,SLOT(on_playButton_clicked()));
}

MusicPlayer::~MusicPlayer()
{
    delete ui;
}

void MusicPlayer::on_playButton_clicked()
{
    playFile(ui->filePath->text());
}

void MusicPlayer::getFile()
{
    QString s_file = QFileDialog::getOpenFileName(this,"Select Music File",
                                                  ui->filePath->text().isEmpty()?"/":ui->filePath->text(),
                                                  "mp3 Files(*.mp3);;All Files(*.*)");
    if (!s_file.isEmpty()) ui->filePath->setText(s_file);
}

void MusicPlayer::playFile(const QString& filePath)
{
    if (mediaPlayer.state() != QMediaPlayer::PlayingState)
    {
        bool ok;
        int volume=ui->volumeEdit->text().toInt(&ok);
        if (!ok) volume = 20;

        mediaPlayer.setVolume(volume);
        DEBUG(filePath);
        mediaPlayer.setMedia(QUrl::fromLocalFile(filePath));
        mediaPlayer.play();
    }
    else mediaPlayer.pause();
}
