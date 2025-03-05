use FlockBook
alter table oblasts
add constraint FK_countries_oblasts 
foreign key (country_id)
references countries (country_id)
go
