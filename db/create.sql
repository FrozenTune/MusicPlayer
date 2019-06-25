create table IF NOT EXISTS local_playlist(
id INTEGER PRIMARY KEY AUTOINCREMENT,
list_name varchar(50) default(''),
list_description nvarchar(100) default(''),
is_deleted bit default(0),
gmt_create datetime default(datetime(CURRENT_TIMESTAMP,'localtime')),
gmt_modified datetime default(datetime(CURRENT_TIMESTAMP,'localtime')));

CREATE TABLE IF NOT EXISTS music_library(
id INTEGER PRIMARY KEY AUTOINCREMENT,
music_path varchar(150) default(''),
is_fromNet bit default(0),
is_playable bit default(1),
music_artist varchar(100) default(''),
music_title varchar(100) default(''),
music_length int default(0),
gmt_create datetime default(datetime(CURRENT_TIMESTAMP,'localtime')),
gmt_modified datetime default(datetime(CURRENT_TIMESTAMP,'localtime')));

create table IF NOT EXISTS music_playlist(
id INTEGER PRIMARY KEY AUTOINCREMENT,
playlist_id INTEGER,
music_id INTEGER);

CREATE VIEW IF NOT EXISTS songs_in_playlist_view AS
select a.id as songs_id,b.id as list_id,b.music_path,b.is_fromNet,b.music_artist,b.music_title,b.music_length from
local_playlist as a,music_library as b,music_playlist as c
where a.id=c.id and b.id=c.id
and a.is_deleted=0 and b.is_playable=1;