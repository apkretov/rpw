USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spSelect_WeightWoolAnnl_IDSheepGoatAge" AND
    type = "P")
    DROP PROCEDURE spSelect_WeightWoolAnnl_IDSheepGoatAge
GO
CREATE PROCEDURE spSelect_WeightWoolAnnl_IDSheepGoatAge (@IDSheepGoat char(6), @Age tinyint) AS
    DECLARE @DateZero smalldatetime
    SET @DateZero = "1.1.1900"
    --SET DATEFORMAT dmy
    SELECT IDSheepGoat, Age, ISNULL(DateAnnl, @DateZero) AS DateAnnl, 
	ISNULL(WtAnnl, 0) AS WtAnnl, ISNULL(DateShearAnnl, @DateZero) AS DateShearAnnl, 
	ISNULL(GreaseAnnl, 0) AS GreaseAnnl
	FROM WeightWoolAnnl
	WHERE IDSheepGoat = @IDSheepGoat AND 
	    Age = @Age
GO
spSelect_WeightWoolAnnl_IDSheepGoatAge "юб0000", 4
GO