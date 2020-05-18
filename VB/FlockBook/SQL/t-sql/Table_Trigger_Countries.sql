use FlockBook
go
--update countries set Country="ÊÐ"
--go

CREATE TRIGGER DeleteCountriesOblasts ON Countries
FOR DELETE 
AS

-- Delete the relationship between Countries and Oblasts
ALTER TABLE dbo.Oblasts
	DROP CONSTRAINT FK_Oblasts_Countries
GO

-- Delete the related records from Oblasts
delete Oblasts from  Oblasts, deleted
where Oblasts.IDCountry=deleted.IDCountry
go

-- Restore the relationship between Countries and Oblasts
ALTER TABLE dbo.Oblasts ADD CONSTRAINT
	FK_Oblasts_Countries FOREIGN KEY
	(
	IDCountry
	) REFERENCES dbo.Countries
	(
	IDCountry
	)
GO
-- Test the trigger
--delete Countries where IDCountry="02"
--go





