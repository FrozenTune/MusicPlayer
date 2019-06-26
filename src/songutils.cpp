#include "songutils.h"
#include "songinfo.h"
#include <QFileInfo>
#include <QTime>

#define DEBUG(x) qDebug()<<__FUNCTION__<<__LINE__<<x

SongUtils::SongUtils()
{
}

QString SongUtils::convertSongLengthToString(qint64 song_int64Length)
{
    QTime convertedTime(song_int64Length / 60000 / 60000,
                   song_int64Length / 60000,
                   qRound((song_int64Length % 60000) / 1000.0));
    return convertedTime.toString();
}

bool SongUtils::getSongInfo(const QString& song_path,SongInfo *songinfo)
{
    QMediaPlayer loaded_mediaPlayer;
    if (QFileInfo(song_path).isFile())
    {
        loaded_mediaPlayer.setMedia(QUrl::fromLocalFile(song_path));
        //读不出duration

        songinfo->setPath(song_path);
        songinfo->setLength_ms(loaded_mediaPlayer.duration());
        songinfo->setTitle(QFileInfo(song_path).baseName());
        DEBUG(songinfo->getLength_ms());
        DEBUG(songinfo->getTitle());
        return true;
    }
    else return false;
}
