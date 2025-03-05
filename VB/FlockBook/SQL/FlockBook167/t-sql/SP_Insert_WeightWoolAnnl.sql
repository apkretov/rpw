USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spInsert_WeightWoolAnnl" AND type = "P")
    DROP PROCEDURE spInsert_WeightWoolAnnl
GO
CREATE PROCEDURE spInsert_WeightWoolAnnl (@IDSheepGoat char(6), @Age tinyint, 
    @DateAnnl smalldatetime/*varchar(8)*/, @WtAnnl real, 
    @DateShearAnnl smalldatetime/*varchar(8)*/, @GreaseAnnl real) AS
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
    INSERT INTO WeightWoolAnnl (IDSheepGoat, Age, DateAnnl, WtAnnl, DateShearAnnl, GreaseAnnl)
	VALUES (@IDSheepGoat, @Age, /*CAST(*/@DateAnnl /*AS smalldatetime)*/, @WtAnnl / 10, 
	    /*CAST(*/@DateShearAnnl /*AS smalldatetime)*/, @GreaseAnnl / 10)
GO
SELECT * FROM WeightWoolAnnl WHERE IDSheepGoat = "юб0000"
GO
spInsert_WeightWoolAnnl "юб0000", 4, "12.31.02", 600, "1.1.1900", 0 -- "12.31.02", NULL, "12.31.02", 159
GO
SELECT * FROM WeightWoolAnnl WHERE IDSheepGoat = "юб0000"
GO