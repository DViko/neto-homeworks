-- genres
insert into genres (title) values
    ('rock'),
    ('pop'),
    ('electronic')

-- singers
insert into singers (singer_name) values
    ('Radiohead'),
    ('Taylor Swift'),
    ('Draft Punk'),
    ('Coldplay')

-- references between singers and genres
insert into singers_genres (singer_id, genre_id) values
	(1, 1),			-- Radihead > Rock
	(2, 2),			-- Taylor Swift > Pop
	(3, 3),			-- Draft Punk > Electronic
	(4, 1), (4, 2) 	-- Coldplay > Rock, Pop

-- albums
insert into albums (title, release_year) values
	('OK Computer', 1997),
	('1989', 2014),
	('Random Access Memories', 2013),
	('Music of the Spheres', 2021)

-- references between singers and albums
insert into singers_albums (singer_id, album_id) values
    (1, 1),             -- Radiohead > OK Computer
    (2, 2),             -- Taylor Swift > 1989
    (3, 3),             -- Draft Punk > Random Access Memories
    (4, 4), (4, 1)      -- Coldplay > Music of the Spheres, OK Computer (cover)

-- tracks
insert into tracks (title, duration, album_id) values
    ('Paranoid Android', 366, 1), ('Karma Police', 261, 1), ('The Scientist', 256, 1),
    ('Shake It Off', 219, 2), ('Blank Space', 231, 2),
    ('Get Lucky', 368, 3), ('Instant Crush', 337, 3),
    ('My Universe', 255, 4), ('Higher Power', 203, 4)

-- compilations
insert into compilations (title, release_year) values
    ('Rock Classics', 2018),
    ('Pop Hits', 2019),
    ('Electronic Essentials', 2020),
    ('Best of 2021', 2021)

-- references between compilations and tracks
insert into compilations_tracks (compilation_id, track_id) values
    (1, 1), (1, 2), (1, 3),      -- Rock Classics > Paranoid Android, Karma Police, The Scientist
    (2, 3), (2, 4),              -- Pop Hits > Shake It Off, Blank Space
    (3, 5), (3, 6),              -- Electronic Essentials > Get Lucky, Instant Crush
    (4, 7), (4, 8)               -- Best of 2021 > My Universe, Higher Power

