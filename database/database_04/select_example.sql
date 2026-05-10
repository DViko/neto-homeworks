-- task 2

-- longest track
select title, duration
from tracks
where duration = (select max(duration) from tracks)

-- titles of tracks that are at least 3.5 minutes long (210 seconds)
select title, duration
from tracks 
where duration >= 210

-- titles of compilations published between 2018 and 2020 
select title, release_year 
from compilations 
where release_year between 2018 and 2020

-- singer whose names consist of one word
select singer_name 
from singers 
where singer_name not like '% %'

-- tracks containing "my"
select title 
from tracks
where lower(title) like '%my%'


-- task 3

-- number of singers in each genre
select g.title as genres, count(sg.singer_id) as singers_count
from genres g
left join singers_genres sg on g.id = sg.genre_id
group by g.id, g.title

-- number of tracks included in albums released in 2019–2020
select count(t.id) as tracks_count
from tracks t
join albums a on t.album_id = a.id
where a.release_year between 2019 and 2020

-- average track length for each album
select a.title as album, avg(t.duration) as avg_duration_sec
from albums a
left join tracks t on a.id = t.album_id
group by a.id, a.title

-- all singers who didn't release albums in 2020
select s.singer_name
from singers s
where s.id not in (
    select sa.singer_id
    from singers_albums sa
    join albums a on sa.album_id = a.id
    where a.release_year = 2020
)

-- titles of compilations that feature a specific singer (Radiohead)
select distinct c.title
from compilations c
join compilations_tracks ct on c.id = ct.compilation_id
join tracks t on ct.track_id = t.id
join albums a on t.album_id = a.id
join singers_albums sa on a.id = sa.album_id
where sa.singer_id = 1


-- task 4

-- albums that feature artists from more than one genre
select distinct a.title
from albums a
join singers_albums sa on a.id = sa.album_id
join singers_genres sg on sa.singer_id = sg.singer_id
group by a.id, a.title, sa.singer_id
having count(distinct sg.genre_id) > 1

-- tracks not included in any compilation
select t.title
from tracks t
left join compilations_tracks ct on t.id = ct.track_id
where ct.compilation_id is null

-- singers of the shortest track
select s.singer_name, t.title, t.duration
from tracks t
join albums a on t.album_id = a.id
join singers_albums sa on a.id = sa.album_id
join singers s on sa.singer_id = s.id
where t.duration = (select min(duration) from tracks)

-- titles of albums containing the least number of tracks
with track_counts as (
    select album_id, count(*) as track_count
    from tracks
    group by album_id
)
select a.title, tc.track_count
from albums a
join track_counts tc on a.id = tc.album_id
where tc.track_count = (select min(track_count) from track_counts)
