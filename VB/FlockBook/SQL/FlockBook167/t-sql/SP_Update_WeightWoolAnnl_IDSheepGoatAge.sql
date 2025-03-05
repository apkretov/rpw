USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spUpdate_WeightWoolAnnl_IDSheepGoatAge" AND
    type = "P")
    DROP PROCEDURE spUpdate_WeightWoolAnnl_IDSheepGoatAge
GO
CREATE PROCEDURE spUpdate_WeightWoolAnnl_IDSheepGoatAge (@IDSheepGoat char(6), @Age tinyint, 
    @DateAnnl smalldatetime, @WtAnnl real, @DateShearAnnl smalldatetime, @GreaseAnnl real) AS
    --SET DATEFORMAT dmy
    IF @WtAnnl = 0 -- Convert zeros to NULLs.
	BEGIN
	SET @DateAnnl = NULL
	SET @WtAnnl = NULL
	END
    IF @GreaseAnnl = 0 -- Convert zeros to NULLs.
	BEGIN
	SET @DateShearAnnl = NULL
	SET @GreaseAnnl = NULL
	END
    UPDATE WeightWoolAnnl
	SET Age = @Age, DateAnnl = @DateAnnl, WtAnnl = @WtAnnl / 10, DateShearAnnl = 
	    @DateShearAnnl, GreaseAnnl = @GreaseAnnl / 10
	WHERE IDSheepGoat = @IDSheepGoat and Age = @Age
GO
SELECT * FROM WeightWoolAnnl WHERE IDSheepGoat = "юб0000"
GO
spUpdate_WeightWoolAnnl_IDSheepGoatAge "юб0000", 4, "1.1.1900", 0, "12.31.02", 105 --  1, "12.31.99", 1301, "12.31.99", 160 -- "12.31.1999", 1301, "12.31.1999", 160 -- "31.12.99", 1301, "31.12.99", 160 
GO
SELECT * FROM WeightWoolAnnl WHERE IDSheepGoat = "юб0000"
GO