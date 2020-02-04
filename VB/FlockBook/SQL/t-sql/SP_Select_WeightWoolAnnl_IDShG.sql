USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spSelect_WeightWoolAnnl_IDShG" AND 
    type = "P")
DROP PROCEDURE spSelect_WeightWoolAnnl_IDShG
GO
CREATE PROCEDURE spSelect_WeightWoolAnnl_IDShG (@IDSheepGoat char(6)) AS
    SELECT * FROM WeightWoolAnnl
	WHERE IDSheepGoat = @IDSheepGoat
GO
spSelect_WeightWoolAnnl_IDShG "¿¿0000"