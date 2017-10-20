USE FlockBook
go

IF EXISTS (SELECT name FROM sysobjects WHERE 
	name = "spSelectInto_Cert_SheepGoat" AND type = "P")
DROP PROCEDURE spSelectInto_Cert_SheepGoat
GO

CREATE PROCEDURE spSelectInto_Cert_SheepGoat (@IDSheepGoat char(6))
AS
--SET DATEFORMAT dmy
-- Drop the previous table.
IF EXISTS (SELECT name FROM sysobjects WHERE name = "Cert_SheepGoat" AND type = "U")
DROP TABLE Cert_SheepGoat
-- Create a new one.
SELECT IDFarm, IDSheepGoat, IDSex, BreedCross, DateBirth, IDFarmBirth, TypeBirth, IDSire, IDDam
	INTO Cert_SheepGoat 
FROM SheepGoat	
WHERE IDSheepGoat = @IDSheepGoat
GO

spSelectInto_Cert_SheepGoat "¿¿0000"
GO
SELECT * FROM Cert_SheepGoat
GO