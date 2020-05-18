use Test
--use FlockBookRec
go
update SheepGoat
set IDSire = "-"
where IDSire = ""
go
update SheepGoat
set IDDam = "-"
where IDDam = ""
go
update SheepGoat
set Remark = "-"
where Remark = ""
go