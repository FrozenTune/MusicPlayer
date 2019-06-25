#include "musicplayer.h"
#include "ui_musicplayer.h"
#include "dbcontrol.h"
#include <song.h>

#include <QDebug>
#include <QString>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QFileDialog>
#include <QTimer>
#include <QSqlTableModel>

#define DEBUG(x) qDebug()<<__FUNCTION__<<__LINE__<<x

MusicPlayer::MusicPlayer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MusicPlayer)
{
    ui->setupUi(this);

    DBControl::instance()->connectDb();
    mediaPlaylist = new QMediaPlaylist;
    mediaPlayer.setPlaylist(mediaPlaylist);
    initUI();

    connect(ui->selectLocalMusicBtn,SIGNAL(clicked()),this,SLOT(getFile()));

    connect(&mediaPlayer,SIGNAL(durationChanged(qint64)),this,SLOT(updateDuration(qint64)));
    connect(&mediaPlayer,SIGNAL(positionChanged(qint64)),this,SLOT(updatePosition(qint64)));
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
    if (!s_file.isEmpty())
    {
        ui->filePath->setText(s_file);
        addSongToList(mySong->getSong(s_file));
        mediaPlaylist->addMedia(QUrl::fromLocalFile(s_file));
    }
}

void MusicPlayer::playFile(const QString& filePath)
{
    if (mediaPlayer.state() == QMediaPlayer::PausedState)
    {
        mediaPlayer.play();
    }
    else if (mediaPlayer.state() == QMediaPlayer::PlayingState)
    {
        mediaPlayer.pause();
    }
    else
    {
        mediaPlayer.setVolume(ui->playVolume_Silder->value());
        DEBUG(filePath);
        mediaPlayer.setMedia(QUrl::fromLocalFile(filePath));
        mediaPlayer.play();
    }
}


/******************** 进度条事件 *********************/

void MusicPlayer::updateDuration(qint64 duration)           //根据文件更新总进度
{
    ui->playProgress_Silder->setRange(0,duration);          //设置总时长
    ui->playProgress_Silder->setEnabled(duration > 0);      //若时长大于0则可用
    ui->playProgress_Silder->setPageStep(duration / 10);    //设置步长
}

void MusicPlayer::updatePosition(qint64 position)           //更新进度
{
    ui->playProgress_Silder->setValue(position);
    //QTime::QTime(int h, int m, int s = 0, int ms = 0)
    DEBUG(position);
    ui->durationLabel->setText(song::convertSongLengthToString(position));
    DEBUG(song::convertSongLengthToString(position));
}

void MusicPlayer::on_playVolume_Silder_valueChanged(int volume)
{
    mediaPlayer.setVolume(volume);
    DEBUG(ui->playVolume_Silder->value());
}

void MusicPlayer::on_playProgress_Silder_sliderReleased()
{
    mediaPlayer.setPosition(ui->playProgress_Silder->value());
    DEBUG(ui->playProgress_Silder->value());
}

/********************** UI初始化 ***********************/

void MusicPlayer::initUI()
{
    //设置Slider默认属性
    ui->playVolume_Silder->setRange(0,100);
    ui->playVolume_Silder->setPageStep(5);
    ui->playProgress_Silder->setEnabled(false);

    //设置歌单列表属性
    ui->songList_TabelWidget->setColumnCount(4);
    ui->songList_TabelWidget->setHorizontalHeaderLabels(QStringList()<<"路径"<<"艺术家"<<"标题"<<"长度");
    ui->songList_TabelWidget->setShowGrid(false);

    ui->songList_TabelWidget->setEditTriggers(QTableView::NoEditTriggers);
    ui->songList_TabelWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->songList_TabelWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
/*
    if (DBControl::instance()->db.isOpen())
    {
        QSqlTableModel *model = new QSqlTableModel;
        QString sql = "select * from songs_in_playlist_view";
        DBControl::instance()->initQueryModel(model,&DBControl::instance()->db,sql);

        model->setHeaderData(4,Qt::Horizontal,"艺术家");
        model->setHeaderData(5,Qt::Horizontal,"歌曲名");
        model->setHeaderData(6,Qt::Horizontal,"时长");
        ui->songList_TabelView->setModel(model);
        ui->songList_TabelView->setColumnHidden(0,true);
        ui->songList_TabelView->setColumnHidden(1,true);
        ui->songList_TabelView->setColumnHidden(2,true);
        ui->songList_TabelView->setColumnHidden(3,true);
        ui->songList_TabelView->resizeColumnsToContents();
    }*/
}

/********************** 歌曲显示列操作 ***********************/

void MusicPlayer::addSongToList(song *mySong)
{
    QTableWidgetItem *song_path_item=new QTableWidgetItem(mySong->getPath());
    QTableWidgetItem *song_artist_item=new QTableWidgetItem(mySong->getArtist());
    QTableWidgetItem *song_title_item=new QTableWidgetItem(mySong->getTitle());
    QTableWidgetItem *song_length_item=new QTableWidgetItem(mySong->getLength_ms());

    ui->songList_TabelWidget->insertRow(ui->songList_TabelWidget->rowCount());
    ui->songList_TabelWidget->setItem(ui->songList_TabelWidget->rowCount(),0,song_path_item);
    ui->songList_TabelWidget->setItem(ui->songList_TabelWidget->rowCount(),1,song_artist_item);
    ui->songList_TabelWidget->setItem(ui->songList_TabelWidget->rowCount(),2,song_title_item);
    ui->songList_TabelWidget->setItem(ui->songList_TabelWidget->rowCount(),3,song_length_item);
}



