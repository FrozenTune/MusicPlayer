#include "songinfo.h"
#include <QObject>
#include <QMediaPlayer>

SongInfo::SongInfo()
{
    song_path=song_artist=song_title="";
    song_length_ms=0;

    connect(&loadedPlayer,SIGNAL(durationChanged(qint64)),this,SLOT(getDuration(qint64)));
}

bool SongInfo::forceGetDuration()
{
    if (loadedPlayer.PlayingState == QMediaPlayer::PausedState) return true;
    loadedPlayer.play();
    return false;
}

void SongInfo::getDuration(qint64 playDuration)
{
    setLength_ms(playDuration);
    loadedPlayer.pause();
}
