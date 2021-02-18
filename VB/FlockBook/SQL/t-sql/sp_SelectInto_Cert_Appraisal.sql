USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE 
	name = "spSelectInto_Cert_Appraisal" AND type = "P")
DROP PROCEDURE spSelectInto_Cert_Appraisal
GO
CREATE PROCEDURE spSelectInto_Cert_Appraisal @IDSheepGoat char(6)
AS
--SET DATEFORMAT dmy
-- Drop the previous table.
IF EXISTS (SELECT name FROM sysobjects WHERE name = "Cert_Appraisal" AND type = "U")
DROP TABLE Cert_Appraisal
-- Create a new one.
SELECT * --IDSheepGoat, Age, Leng, Diam 
	INTO Cert_Appraisal
FROM Appraisal	
WHERE IDSheepGoat = @IDSheepGoat --(SELECT IDSheepGoat FROM Cert_SheepGoat)
/*CREATE NONCLUSTERED INDEX IX_Cert_Appraisal ON 
	Cert_Appraisal (Diam) ON [PRIMARY]
CREATE NONCLUSTERED INDEX IX_Cert_Appraisal_1 ON 
	Cert_Appraisal (Age) ON [PRIMARY]
CREATE NONCLUSTERED INDEX IX_Cert_Appraisal_2 ON 
	Cert_Appraisal (IDColour) ON [PRIMARY]
CREATE NONCLUSTERED INDEX IX_Cert_Appraisal_3 ON 
	Cert_Appraisal (IDFluffColour) ON [PRIMARY]*/
GO
spSelectInto_Cert_Appraisal "¿¿0000"
GO
SELECT * FROM Cert_Appraisal
GO