create table genre (
	id serial primary key,
	title varchar(100) not null unique
)

create table signer (
	id serial primary key,
	signer_name varchar(150) not null
)

create table signer_genre (
	signer_id int not null,
	genre_id int not null,
	primary  key(signer_id, genre_id),
	foreign key(signer_id) references signer(id) on delete cascade,
	foreign key(genre_id) references genre(id) on delete cascade
)

create table album (
	id serial primary key,
	title varchar(150) not null,
	release_year int
)

create table signer_album (
	signer_id int not null,
	album_id int not null,
	primary key(signer_id, album_id),
	foreign key(signer_id) references signer(id) on delete cascade,
	foreign key(album_id) references album(id) on delete cascade
)

create table track (
	id serial primary key,
	album_id int not null,
	title varchar(150) not null,
	duration int not null,
	foreign key (album_id) references album(id) on delete cascade
)

create table compilation (
	id serial primary key,
	title varchar(150) not null,
	release_year int
)

create table compilation_track (
	compilation_id int not null,
	track_id int not null,
	primary key(compilation_id, track_id),
	foreign key(compilation_id) references compilation(id) on delete cascade,
	foreign key(track_id) references track(id) on delete cascade
)

-- Genre
insert into genre (title) values
	('trance'), ('club')

-- Signer
insert into signer (signer_name) values
	('Denis Kenzo'), ('Sveta B.')

-- Linking between signer and genres
insert into signer_genre (signer_id, genre_id) values
	(1, 1), (1, 2),
	(2, 1)

-- Album
insert into album (title, release_year) values
	('Sweet Lie', 2018),
	('Reasons Cry', 2019),
	('That Same ID', 2022)

-- Album (joint)
insert into signer_album (signer_id, album_id) values
	(1, 1),
	(1, 2), (2, 2),
	(1, 3), (2, 3)

-- Album tracks
insert into track (album_id, title, duration) values
	(1, 'Sweet Lie', 243),
	(2, 'Reasons Cry', 190),
	(2, 'Reasons Cry (Extended mix)', 231),
	(3, 'That Same ID', 287)

-- Compilation
insert into compilation (title, release_year) values
	('Trancemission vol 19', 2019),
	('Best of Sveta B.', 2020)

-- Linking collection to the tracks
insert into compilation_track (compilation_id, track_id) values
	(1, 1), (1, 3),
	(2, 1), (2, 3), (2, 4)

-- Test

-- Signer > genre
SELECT s.signer_name AS signer, STRING_AGG(g.title, ', ') AS genres
FROM signer s
JOIN signer_genre sg ON s.id = sg.signer_id
JOIN genre g ON sg.genre_id = g.id
GROUP BY s.id, s.signer_name

-- Signer > album
SELECT s.signer_name AS signer, STRING_AGG(a.title, ', ') AS albums
FROM signer s
JOIN signer_album sa ON s.id = sa.signer_id
JOIN album a ON sa.album_id = a.id
GROUP BY s.id, s.signer_name

-- Track > album
SELECT t.title AS track, a.title AS album, a.release_year
FROM track t
JOIN album a ON t.album_id = a.id
ORDER BY a.release_year, t.id

-- Track > compilation
SELECT c.title AS compilation, t.title AS track
FROM compilation c
JOIN compilation_track ct ON c.id = ct.compilation_id
JOIN track t ON ct.track_id = t.id
ORDER BY c.id, t.id

-- Count of tracks in each album
SELECT a.title AS album, COUNT(t.id) AS track_count
FROM album a
LEFT JOIN track t ON a.id = t.album_id
GROUP BY a.id, a.title
ORDER BY a.release_year