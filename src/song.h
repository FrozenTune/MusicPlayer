#ifndef SONG_H
#define SONG_H
#include <QUrl>
#include <QMediaPlayer>

class song
{
public:
    song();
    void getSongInfo(song* r_song,const QString& song_path);   //获取歌曲信息
    song* getSong(const QString& song_path);

    QString getPath()  { return song_path; }
    QString getTitle()  { return song_title; }
    QString getArtist() { return song_artist; }
    qint64 getLength_ms()   { return song_length_ms; }

    QString static convertSongLengthToString(qint64 song_int64Length);

private:
    QString song_path;
    QString song_title;
    QString song_artist;
    qint64 song_length_ms;

    QMediaPlayer loaded_mediaPlayer;
};

#endif // SONG_H
