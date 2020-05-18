USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE 
	name = "spSelectInto_CertRamHegoat_Mate" AND type = "P")
DROP PROCEDURE spSelectInto_CertRamHegoat_Mate
GO
CREATE PROCEDURE spSelectInto_CertRamHegoat_Mate @IDSire char(6)
AS
--SET DATEFORMAT dmy
-- Drop the previous table.
IF EXISTS (SELECT name FROM sysobjects WHERE name = "CertRamHegoat_Mate" AND type = "U")
DROP TABLE CertRamHegoat_Mate
-- Create a new one.
SELECT IDSire, YEAR(DateMatFrom) AS YearMat, COUNT(IDDam) AS CountIDDam
INTO CertRamHegoat_Mate 
FROM Mate
GROUP BY IDSire, YEAR(DateMatFrom)
HAVING (IDSire = @IDSire) --(IDSire = (SELECT IDSheepGoat FROM Cert_SheepGoat))
/*CREATE NONCLUSTERED INDEX IX_CertRamHegoat_Mate ON 
	CertRamHegoat_Mate (IDSire) ON [PRIMARY]
CREATE NONCLUSTERED INDEX IX_CertRamHegoat_Mate_1 ON 
	CertRamHegoat_Mate (YearMat) ON [PRIMARY]*/
GO
spSelectInto_CertRamHegoat_Mate "¿¿0000"
GO
SELECT * FROM CertRamHegoat_Mate
GO