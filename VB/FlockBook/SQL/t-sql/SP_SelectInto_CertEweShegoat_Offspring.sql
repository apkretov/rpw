use FlockBook
go

IF EXISTS (SELECT name FROM sysobjects WHERE 
	name = "spSelectInto_CertEweShegoat_Offspring" AND type = "P")
DROP PROCEDURE spSelectInto_CertEweShegoat_Offspring
GO

CREATE PROCEDURE spSelectInto_CertEweShegoat_Offspring @IDDam char(6)
AS
--SET DATEFORMAT dmy
-- Drop the previous table.
IF exists (SELECT * FROM sysobjects WHERE id = object_id(N'CertEweShegoat_Offspring') 
	and OBJECTPROPERTY(id, N'IsUserTable') = 1)
DROP TABLE CertEweShegoat_Offspring
-- Create a new one.
SELECT * INTO CertEweShegoat_Offspring 
FROM Offspring
WHERE IDDam = @IDDam --(SELECT IDSheepGoat FROM Cert_SheepGoat)
/*CREATE NONCLUSTERED INDEX IX_CertEweShegoat_Offspring ON 
	CertEweShegoat_Offspring (IDDam) ON [PRIMARY]
CREATE NONCLUSTERED INDEX IX_CertEweShegoat_Offspring_1 ON 
	CertEweShegoat_Offspring (IDLiv) ON [PRIMARY]
CREATE NONCLUSTERED INDEX IX_CertEweShegoat_Offspring_2 ON 
	CertEweShegoat_Offspring (IDSex) ON [PRIMARY]
CREATE NONCLUSTERED INDEX IX_CertEweShegoat_Offspring_3 ON 
	CertEweShegoat_Offspring (IDLambKid) ON [PRIMARY]*/
GO

spSelectInto_CertEweShegoat_Offspring "¿¿0002"
go
select * from CertEweShegoat_Offspring
go