USE FlockBook
GO
IF EXISTS (SELECT NAME FROM sysobjects WHERE NAME = "spUpdate_Cert" AND type = "P")
DROP PROCEDURE spUpdate_Cert
GO
CREATE PROCEDURE spUpdate_Cert (@IDSheepGoat char(6)) AS
    UPDATE Cert_SheepGoatSire -- Delete hyphens from the pedigree tables: Cert_SheepGoatSire,
	SET IDSiresSire = "" WHERE IDSiresSire = "-" -- Cert_SheepGoatSire, Cert_SheepGoatDam,
    UPDATE Cert_SheepGoatSire			     -- Cert_SheepGoatDam.
	SET IDSiresDam = "" WHERE IDSiresDam = "-" 
    UPDATE Cert_SheepGoatDam 
	SET IDDamsSire = "" WHERE IDDamsSire = "-" 				
    UPDATE Cert_SheepGoatDam
	SET IDDamsDam = "" WHERE IDDamsDam = "-" 
    UPDATE Cert_WeightWoolAnnlAge -- Insert the sheep/goat's ID into the Cert_WeightWoolAnnlAge 
	SET IDSheepGoat = @IDSheepGoat 				      -- table next to the ages.
GO
spUpdate_Cert "¿¿0000"
GO
SELECT * FROM Cert_WeightWoolAnnlAge
GO