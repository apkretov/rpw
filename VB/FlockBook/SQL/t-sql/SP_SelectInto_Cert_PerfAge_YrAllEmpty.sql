USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spSelectInto_Cert_PerfAge_YrAllEmpty" AND 
    type = "P")
    DROP PROCEDURE spSelectInto_Cert_PerfAge_YrAllEmpty
GO
CREATE PROCEDURE spSelectInto_Cert_PerfAge_YrAllEmpty AS -- Below: -- Drop the previous table.
    IF EXISTS (SELECT * FROM sysobjects WHERE name = "Cert_PerfAge_YrAll" AND type  = "U") 
	DROP TABLE Cert_PerfAge_YrAll 
    SELECT Cert_WeightWoolAnnlAge.IDSheepGoat, Cert_WeightWoolAnnlAge.Age, -- Create an empty
	Cert_WeightWoolAnnl.DateAnnl, Cert_WeightWoolAnnl.WtAnnl, 	       --  table.
	Cert_WeightWoolAnnl.DateShearAnnl, Cert_WeightWoolAnnl.GreaseAnnl
	INTO Cert_PerfAge_YrAll
	FROM Cert_WeightWoolAnnlAge LEFT OUTER JOIN Cert_WeightWoolAnnl ON 
	    Cert_WeightWoolAnnlAge.Age = Cert_WeightWoolAnnl.Age
GO
spSelectInto_Cert_PerfAge_YrAllEmpty
GO
SELECT * FROM Cert_PerfAge_YrAll
GO