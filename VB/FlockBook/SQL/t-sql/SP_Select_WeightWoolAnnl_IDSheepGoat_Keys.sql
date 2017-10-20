USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects 
    WHERE name = "spSelect_WeightWoolAnnl_IDSheepGoat_Keys" AND type = "P")
    DROP PROCEDURE spSelect_WeightWoolAnnl_IDSheepGoat_Keys
GO
CREATE PROCEDURE spSelect_WeightWoolAnnl_IDSheepGoat_Keys (@IDSheepGoat char(6)) AS
    SELECT IDSheepGoat, Age FROM WeightWoolAnnl
	WHERE IDSheepGoat = @IDSheepGoat
GO
spSelect_WeightWoolAnnl_IDSheepGoat_Keys "¿¿0000"
GO