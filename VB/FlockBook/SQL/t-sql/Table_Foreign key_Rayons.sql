use FlockBook
alter table rayons
add constraint FK_oblasts_rayons
foreign key (country_id, oblast_id)
references oblasts (country_id, oblast_id)
go
