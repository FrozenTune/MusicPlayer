create table local_playlist(
music_id INTEGER PRIMARY KEY AUTOINCREMENT,
music_url varchar(50) default(''),
music_artist nvarchar(100) default(''),
music_songname nvarchar(100) default(''),
music_length integer default(0),
is_playable bit default(0),
music_addlist_time datetime default(datetime(CURRENT_TIMESTAMP,'localtime')));