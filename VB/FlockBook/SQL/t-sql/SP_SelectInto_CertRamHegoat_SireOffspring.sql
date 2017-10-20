USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects 
    WHERE name = "spSelectInto_CertRamHegoat_SireOffspring" AND type = "P")
    DROP PROCEDURE spSelectInto_CertRamHegoat_SireOffspring
GO
CREATE PROCEDURE spSelectInto_CertRamHegoat_SireOffspring @IDSire char(6) AS
    --SET DATEFORMAT dmy
    IF EXISTS (SELECT * FROM sysobjects WHERE name = "CertRamHegoat_SireOffspring" AND 
	type = "U") -- Drop the previous table.
	DROP TABLE CertRamHegoat_SireOffspring
    SELECT Mate.IDSire, Mate.DateMatFrom, Offspring.IDLambKid, Offspring.WtBirth, 
	WeightWean.WtWean, Weight7Mon.Wt7Mon -- Create a new one.
	INTO CertRamHegoat_SireOffspring 
	FROM Mate 
	    LEFT OUTER JOIN LambKid ON 
		Mate.IDDam = LambKid.IDDam AND 
    		Mate.Cycle = LambKid.Cycle 
	    LEFT OUTER JOIN Offspring 
	    LEFT OUTER JOIN Weight7Mon ON 
    		Offspring.IDLambKid = Weight7Mon.IDLambKid 
	    LEFT OUTER JOIN WeightWean ON 
    		Offspring.IDLambKid = WeightWean.IDLambKid ON 
    		LambKid.IDDam = Offspring.IDDam AND 
    		LambKid.Cycle = Offspring.Cycle
	WHERE (Mate.IDSire = @IDSire)
    /*CREATE NONCLUSTERED INDEX IX_CertRamHegoat_SireOffspring ON 
	CertRamHegoat_SireOffspring (IDSire) ON [PRIMARY]
    CREATE NONCLUSTERED INDEX IX_CertRamHegoat_SireOffspring_1 ON 
	CertRamHegoat_SireOffspring (DateMatFrom) ON [PRIMARY]
    CREATE NONCLUSTERED INDEX IX_CertRamHegoat_SireOffspring_2 ON 
	CertRamHegoat_SireOffspring (IDLambKid) ON [PRIMARY]*/
GO
spSelectInto_CertRamHegoat_SireOffspring "¿¿0000"
GO
SELECT * FROM CertRamHegoat_SireOffspring
GO