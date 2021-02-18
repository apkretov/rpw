use FlockBook
create table rayons
(country_id 	char(2), 
oblast_id 	char(2),
rayon_id	char(2),
rayon		varchar(20) not null,
primary key (country_id, oblast_id, rayon_id))
go


