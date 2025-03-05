use FlockBook
create table oblasts
(country_id 	char(2), 
oblast_id 	char(2),
oblast		varchar(20) not null,
primary key 	(country_id, oblast_id))
go
