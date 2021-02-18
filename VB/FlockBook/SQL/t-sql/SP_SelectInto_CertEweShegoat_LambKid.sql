USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE 
	name = "spSelectInto_CertEweShegoat_LambKid" AND type = "P")
DROP PROCEDURE spSelectInto_CertEweShegoat_LambKid
GO
CREATE PROCEDURE spSelectInto_CertEweShegoat_LambKid @IDDam char(6)
AS
--SET DATEFORMAT dmy
-- Drop the previous table.
IF EXISTS (SELECT * FROM sysobjects WHERE id = object_id(N'CertEweShegoat_LambKid') 
	AND OBJECTPROPERTY(id, N'IsUserTable') = 1)
DROP TABLE CertEweShegoat_LambKid
-- Create a new one.
SELECT IDDam, Cycle, CycleLambKid, DateLambKid	INTO CertEweShegoat_LambKid 
FROM LambKid
WHERE IDDam = @IDDam --(SELECT IDSheepGoat FROM Cert_SheepGoat)
/*CREATE NONCLUSTERED INDEX IX_CertEweShegoat_LambKid ON 
	CertEweShegoat_LambKid (CycleLambKid) ON [PRIMARY]
CREATE NONCLUSTERED INDEX IX_CertEweShegoat_LambKid_1 ON 
	CertEweShegoat_LambKid(IDDam) ON [PRIMARY]
CREATE NONCLUSTERED INDEX IX_CertEweShegoat_LambKid_2 ON 
	CertEweShegoat_LambKid (Cycle) ON [PRIMARY]*/
GO
spSelectInto_CertEweShegoat_LambKid "¿¿0002"
GO
SELECT * FROM CertEweShegoat_LambKid
GO