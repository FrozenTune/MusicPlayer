#ifndef SONGINFO_H
#define SONGINFO_H

#include <QObject>
#include <QMediaPlayer>

class SongInfo
{
public:
    SongInfo();

    QString getPath()  { return song_path; }
    QString getTitle()  { return song_title; }
    QString getArtist() { return song_artist; }
    qint64 getLength_ms()   { return song_length_ms; }

    void setPath(QString m_path)  { this->song_path=m_path; }
    void setTitle(QString m_title)  { this->song_title=m_title; }
    void setArtist(QString m_artist) { this->song_artist=m_artist; }
    void setLength_ms(qint64 m_len_ms)   { this->song_length_ms=m_len_ms; }

    bool forceGetDuration();

signals:

private slots:

    void getDuration(qint64 playDuration);

private:
    QString song_path;
    QString song_title;
    QString song_artist;
    qint64 song_length_ms;

    QMediaPlayer loadedPlayer;
};

#endif // SONGINFO_H
