use FlockBook
alter table townvill
add constraint FK_rayons_townvill
foreign key (country_id, oblast_id, rayon_id)
references rayons (country_id, oblast_id, rayon_id)
go
