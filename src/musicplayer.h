#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include <QWidget>
#include <QMediaPlayer>
#include <QTimer>

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

private slots:
    void on_playButton_clicked();

    void updateDuration(qint64 duration);
    void updatePosition(qint64 position);

    void on_playVolume_Silder_valueChanged(int volume);
    void on_playProgress_Slider_sliderReleased();

private:
    void initUI();
    Ui::MusicPlayer *ui;    //ui所有控件的调用
    QMediaPlayer mediaPlayer;
    QTimer *timer;
};

#endif // MUSICPLAYER_H
