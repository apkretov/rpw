use FlockBook
create table townvill
(country_id 	char(2), 
oblast_id 	char(2),
rayon_id	char(2),
townvill_id	char(2),
townvill	varchar(20) not null,
primary key (country_id, oblast_id, rayon_id, townvill_id))
go