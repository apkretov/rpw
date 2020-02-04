USE FlockBookRec
GO

IF EXISTS (SELECT name FROM sysobjects WHERE 
	NAME = "spDropTable_CertEweShegoat" AND type = "P")
DROP PROCEDURE spDropTable_CertEweShegoat
GO

CREATE PROCEDURE spDropTable_CertEweShegoat
AS
-- Drop the Cert_SheepGoat table.
IF exists (SELECT * FROM sysobjects WHERE id = object_id(N'Cert_SheepGoat') 
	and OBJECTPROPERTY(id, N'IsUserTable') = 1)
DROP TABLE Cert_SheepGoat

-- Drop the Cert_SheepGoatDam table.
IF exists (SELECT * FROM sysobjects WHERE id = object_id(N'Cert_SheepGoatDam') 
	and OBJECTPROPERTY(id, N'IsUserTable') = 1)
DROP TABLE Cert_SheepGoatDam

-- Drop the Cert_SheepGoatSire table.
IF exists (SELECT * FROM sysobjects WHERE id = object_id(N'Cert_SheepGoatSire') 
	and OBJECTPROPERTY(id, N'IsUserTable') = 1)
DROP TABLE Cert_SheepGoatSire

-- Drop the Cert_WeightWoolAnnl table.
IF exists (SELECT * FROM sysobjects WHERE id = object_id(N'Cert_WeightWoolAnnl') 
	and OBJECTPROPERTY(id, N'IsUserTable') = 1)
DROP TABLE Cert_WeightWoolAnnl

---- Drop the Cert_WeightWoolAnnlAge table.
--IF exists (SELECT * FROM sysobjects WHERE id = object_id(N'Cert_WeightWoolAnnlAge') 
--	and OBJECTPROPERTY(id, N'IsUserTable') = 1)
--DROP TABLE Cert_WeightWoolAnnlAge

-- Drop the CertEweShegoat_LambKid table.
IF exists (SELECT * FROM sysobjects WHERE id = object_id(N'CertEweShegoat_LambKid') 
	and OBJECTPROPERTY(id, N'IsUserTable') = 1)
DROP TABLE CertEweShegoat_LambKid

-- Drop the CertEweShegoat_Offspring table.
IF exists (SELECT * FROM sysobjects WHERE id = object_id(N'CertEweShegoat_Offspring') 
	and OBJECTPROPERTY(id, N'IsUserTable') = 1)
DROP TABLE CertEweShegoat_Offspring

GO

spDropTable_CertEweShegoat
GO