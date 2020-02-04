USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE 
	name = "spSelectInto_Cert_SheepGoatSire" AND type = "P")
DROP PROCEDURE spSelectInto_Cert_SheepGoatSire
GO
CREATE PROCEDURE spSelectInto_Cert_SheepGoatSire
AS
--SET DATEFORMAT dmy
-- Drop the previous table.
IF EXISTS (SELECT name FROM sysobjects WHERE name = "Cert_SheepGoatSire" AND type = "U")
DROP TABLE Cert_SheepGoatSire
-- Create a new one.
SELECT IDSheepGoat AS IDSire, BreedCross, IDSire AS IDSiresSire, IDDam AS IDSiresDam 
	INTO Cert_SheepGoatSire 
FROM SheepGoat	
WHERE IDSheepGoat = (SELECT IDSire FROM Cert_SheepGoat WHERE IDSire <> "-")
go

spSelectInto_Cert_SheepGoatSire
go
SELECT * FROM Cert_SheepGoatSire
go