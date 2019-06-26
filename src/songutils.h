#ifndef SONG_H
#define SONG_H
#include <QUrl>
#include <songinfo.h>
#include <QMediaPlayer>

class SongUtils //歌曲操作整合类
{
public:
    SongUtils();

    static bool getSongInfo(const QString& song_path,SongInfo *songinfo);   //获取歌曲信息

    static QString convertSongLengthToString(qint64 song_int64Length);  //将qint64的长度转换为hh:mm:ss的QString输出

};

#endif // SONG_H
