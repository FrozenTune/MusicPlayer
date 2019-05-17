#include "musicplayer.h"
#include "ui_musicplayer.h"
#include "dbcontrol.h"

#include <QDebug>
#include <QString>
#include <QMediaPlayer>
#include <QFileDialog>
#include <QTimer>

#define DEBUG(x) qDebug()<<__FUNCTION__<<__LINE__<<x

//class denoiser;

MusicPlayer::MusicPlayer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MusicPlayer)
{
    ui->setupUi(this);

    initUI();
    DBControl::instance()->connectDb();

    //timer = new QTimer(this);
    //timer->start(1000); //设定周期为1000ms,每1000ms触发一次timeout()事件

    connect(ui->selectLocalMusicBtn,SIGNAL(clicked()),this,SLOT(getFile()));

    connect(&mediaPlayer,SIGNAL(durationChanged(qint64)),this,SLOT(updateDuration(qint64)));
    connect(&mediaPlayer,SIGNAL(positionChanged(qint64)),this,SLOT(updatePosition(qint64)));

    connect(ui->playVolume_Slider,SIGNAL(valueChanged(int)),this,SLOT(on_playVolume_Silder_valueChanged(int)));
    connect(ui->playProgress_Slider,SIGNAL(sliderReleased()),this,SLOT(on_playProgress_Slider_sliderReleased()));
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
        mediaPlayer.setVolume(ui->playVolume_Slider->value());
        DEBUG(filePath);
        mediaPlayer.setMedia(QUrl::fromLocalFile(filePath));
        mediaPlayer.play();
    }
    else mediaPlayer.pause();
}


/******************** 进度条事件 *********************/

void MusicPlayer::updateDuration(qint64 duration)           //根据文件更新总进度
{
    ui->playProgress_Slider->setRange(0,duration);          //设置总时长
    ui->playProgress_Slider->setEnabled(duration > 0);      //若时长大于0则可用
    ui->playProgress_Slider->setPageStep(duration / 10);    //设置步长
}

void MusicPlayer::updatePosition(qint64 position)           //更新进度
{
    ui->playProgress_Slider->setValue(position);
    //QTime::QTime(int h, int m, int s = 0, int ms = 0)
    QTime duration(position / 60000 / 60000,
                   position / 60000,
                   qRound((position % 60000) / 1000.0));
    DEBUG(duration.toString());
    ui->durationLabel->setText(duration.toString());
}

void MusicPlayer::on_playVolume_Silder_valueChanged(int volume)
{
    mediaPlayer.setVolume(volume);
    DEBUG(ui->playVolume_Slider->value());
}

void MusicPlayer::on_playProgress_Slider_sliderReleased()
{
    mediaPlayer.setPosition(ui->playProgress_Slider->value());
    DEBUG(ui->playProgress_Slider->value());
}

/********************** UI初始化 ***********************/

void MusicPlayer::initUI()
{
    ui->playVolume_Slider->setRange(0,100);
    ui->playVolume_Slider->setPageStep(5);
    ui->playProgress_Slider->setEnabled(false);
}

