#include "song.h"
#include <QFileInfo>
#include <QTime>
#define DEBUG(x) qDebug()<<__FUNCTION__<<__LINE__<<x

song::song()
{
}

song* song::getSong(const QString& song_path)
{
    if (QFileInfo(song_path).isFile())
    {
        this->getSongInfo(this,song_path);
    }
    return this;
}

QString song::convertSongLengthToString(qint64 song_int64Length)
{
    QTime convertedTime(song_int64Length / 60000 / 60000,
                   song_int64Length / 60000,
                   qRound((song_int64Length % 60000) / 1000.0));
    return convertedTime.toString();
}

void song::getSongInfo(song *r_song,const QString& song_path)
{
    loaded_mediaPlayer.setMedia(QUrl::fromLocalFile(song_path));

    r_song->song_path=song_path;
    r_song->song_length_ms=loaded_mediaPlayer.duration();
    r_song->song_title=QFileInfo(song_path).baseName();
    DEBUG(r_song->song_length_ms);
    DEBUG(r_song->song_title);
}
