USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects 
    WHERE name = "spSelectInto_Cert_WeightWoolAnnl" AND type = "P")
    DROP PROCEDURE spSelectInto_Cert_WeightWoolAnnl
GO
CREATE PROCEDURE spSelectInto_Cert_WeightWoolAnnl @IDSheepGoat char(6) AS
--    SET DATEFORMAT dmy
    IF EXISTS (SELECT name FROM sysobjects WHERE name = "Cert_WeightWoolAnnl" AND type = "U")
	DROP TABLE Cert_WeightWoolAnnl
    SELECT * -- Create a new one.
	INTO Cert_WeightWoolAnnl
	FROM WeightWoolAnnl	
	WHERE IDSheepGoat = @IDSheepGoat
    /*CREATE NONCLUSTERED INDEX IX_Cert_WeightWoolAnnl ON 
	Cert_WeightWoolAnnl (IDSheepGoat) ON [PRIMARY]
    CREATE NONCLUSTERED INDEX IX_Cert_WeightWoolAnnl_1 ON 
	Cert_WeightWoolAnnl (Age) ON [PRIMARY]*/
GO
spSelectInto_Cert_WeightWoolAnnl "¿¿0000"
GO
SELECT * FROM Cert_WeightWoolAnnl
GO