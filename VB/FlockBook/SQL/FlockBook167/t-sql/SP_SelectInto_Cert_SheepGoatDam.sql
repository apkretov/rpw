USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE 
	name = "spSelectInto_Cert_SheepGoatDam" AND type = "P")
DROP PROCEDURE spSelectInto_Cert_SheepGoatDam
GO
CREATE PROCEDURE spSelectInto_Cert_SheepGoatDam
AS
--SET DATEFORMAT dmy
-- Drop the previous table.
IF EXISTS (SELECT name FROM sysobjects WHERE name = "Cert_SheepGoatDam" AND type = "U")
DROP TABLE Cert_SheepGoatDam
-- Create a new one.
SELECT IDSheepGoat AS IDDam, BreedCross, IDSire AS IDDamsSire, IDDam AS IDDamsDam 
	INTO Cert_SheepGoatDam 
FROM SheepGoat	
WHERE IDSheepGoat = (SELECT IDDam FROM Cert_SheepGoat WHERE IDDam <> "-")
go

spSelectInto_Cert_SheepGoatDam
go
SELECT * FROM Cert_SheepGoatDam
go