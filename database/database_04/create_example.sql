create table genres (
	id serial primary key,
	title varchar(100) not null unique
)

create table singers (
	id serial primary key,
	singer_name varchar(150) not null
)

create table singers_genres (
	singer_id int not null,
	genre_id int not null,
	primary  key(singer_id, genre_id),
	foreign key(singer_id) references singers(id) on delete cascade,
	foreign key(genre_id) references genres(id) on delete cascade
)

create table albums (
	id serial primary key,
	title varchar(150) not null,
	release_year int
)

create table singers_albums (
	singer_id int not null,
	album_id int not null,
	primary key(singer_id, album_id),
	foreign key(singer_id) references singers(id) on delete cascade,
	foreign key(album_id) references albums(id) on delete cascade
)

create table tracks (
	id serial primary key,
	title varchar(150) not null,
	duration int not null,
	album_id int not null,
	foreign key (album_id) references albums(id) on delete cascade
)

create table compilations (
	id serial primary key,
	title varchar(150) not null,
	release_year int
)

create table compilations_tracks (
	compilation_id int not null,
	track_id int not null,
	primary key(compilation_id, track_id),
	foreign key(compilation_id) references compilations(id) on delete cascade,
	foreign key(track_id) references tracks(id) on delete cascade
)

