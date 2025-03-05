use Test
go
update SheepGoat
set sex = "0"
where right(IDSheepGoat,2) = "00"
go