#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include <QWidget>
#include <QMediaPlayer>

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

private:
    Ui::MusicPlayer *ui;    //ui所有控件的调用
    QMediaPlayer mediaPlayer;
};

#endif // MUSICPLAYER_H
