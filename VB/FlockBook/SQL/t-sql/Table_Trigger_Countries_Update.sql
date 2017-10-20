use FlockBook
go
if exists (select name from sysobjects
where name = "UpdateCountry" and type = "tr")
drop trigger UpdateCountry 
go
CREATE TRIGGER UpdateCountry ON Countries
FOR UPDATE
AS
declare @OrigValue char(2), @NewValue char(2)
select @OrigValue = IDCountry from deleted
select @NewValue = IDCountry from inserted
update Oblasts set IDCountry = @NewValue
where Oblasts.IDCountry = @OrigValue
go

-- Test the trigger
--update Countries set IDCountry = "03" where IDCountry = "02"
--update Countries set IDCountry = "02" where IDCountry = "03"
--go