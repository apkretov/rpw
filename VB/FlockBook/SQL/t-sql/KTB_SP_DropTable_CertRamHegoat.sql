USE FlockBookRec
GO

IF EXISTS (SELECT name FROM sysobjects WHERE 
	NAME = "spDropTable_CertRamHegoat" AND type = "P")
DROP PROCEDURE spDropTable_CertRamHegoat
GO

CREATE PROCEDURE spDropTable_CertRamHegoat
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

-- Drop the CertRamHegoat_FarmSireOffspring table.
IF exists (SELECT * FROM sysobjects WHERE id = object_id(N'CertRamHegoat_FarmSireOffspring') 
	and OBJECTPROPERTY(id, N'IsUserTable') = 1)
DROP TABLE CertRamHegoat_FarmSireOffspring

-- Drop the CertRamHegoat_SireOffspring table.
IF exists (SELECT * FROM sysobjects WHERE id = object_id(N'CertRamHegoat_SireOffspring') 
	and OBJECTPROPERTY(id, N'IsUserTable') = 1)
DROP TABLE CertRamHegoat_SireOffspring

-- Drop the CertRamHegoat_Mate table.
IF exists (SELECT * FROM sysobjects WHERE id = object_id(N'CertRamHegoat_Mate') 
	and OBJECTPROPERTY(id, N'IsUserTable') = 1)
DROP TABLE CertRamHegoat_Mate

GO

spDropTable_CertRamHegoat
GO