#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include <QWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QTimer>
#include <QSqlTableModel>
#include <songutils.h>

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

    void addSongToList(SongInfo *songInfo);

private slots:
    void on_playButton_clicked();

    void updateDuration(qint64 duration);
    void updatePosition(qint64 position);

    void on_playVolume_Silder_valueChanged(int volume);
    void on_playProgress_Silder_sliderReleased();

    void on_selectLocalMusicBtn_clicked();

    void on_selectLocalMusicBtn_clicked(bool checked);

private:
    void initUI();

    Ui::MusicPlayer *ui;    //ui所有控件的调用
    QMediaPlayer mediaPlayer;
    QMediaPlaylist *mediaPlaylist;

    SongInfo songInfo;   //存放处理歌曲信息用
};

#endif // MUSICPLAYER_H
