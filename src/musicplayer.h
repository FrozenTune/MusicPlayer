#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include <QWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QTimer>
#include <QSqlTableModel>
#include <song.h>

namespace Ui {
class MusicPlayer;
}

class MusicPlayer : public QWidget
{
    Q_OBJECT

public:
    explicit MusicPlayer(QWidget *parent = nullptr);
    ~MusicPlayer();

signals:

public slots:
    void getFile();
    void playFile(const QString& filePath);

    void addSongToList(song *mySong);

private slots:
    void on_playButton_clicked();

    void updateDuration(qint64 duration);
    void updatePosition(qint64 position);

    void on_playVolume_Silder_valueChanged(int volume);
    void on_playProgress_Silder_sliderReleased();

private:
    void initUI();

    Ui::MusicPlayer *ui;    //ui所有控件的调用
    QMediaPlayer mediaPlayer;
    QMediaPlaylist *mediaPlaylist;

    song *mySong;   //存放处理歌曲信息用
};

#endif // MUSICPLAYER_H
