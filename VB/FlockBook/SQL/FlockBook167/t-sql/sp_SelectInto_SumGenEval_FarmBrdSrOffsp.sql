USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spSelectInto_SumGenEval_FarmBrdSrOffsp" AND
    type = "P")
    DROP PROCEDURE spSelectInto_SumGenEval_FarmBrdSrOffsp
GO
CREATE PROCEDURE spSelectInto_SumGenEval_FarmBrdSrOffsp (@IDFarm char(2), @DateEnd smalldatetime)
    AS
    DECLARE @DateMinAge smalldatetime
    DECLARE @AgeMatMinSire smallint
    DECLARE @PregnLengMin smallint
    SELECT @AgeMatMinSire = AgeMatMinSire FROM ContrlParam
    SELECT @PregnLengMin = PregnLengMin FROM ContrlParam
    SET @DateMinAge = @DateEnd - @AgeMatMinSire - @PregnLengMin
    IF EXISTS (SELECT name FROM sysobjects WHERE name = "SumGenEval_FarmBrdSrOffsp" 
	AND type = "U")
	DROP TABLE SumGenEval_FarmBrdSrOffsp
    SELECT SheepGoat.IDFarm, SheepGoat.BreedCross, Mate.IDSire, Offspring.IDLambKid
	INTO SumGenEval_FarmBrdSrOffsp 
	FROM Mate 
	    INNER JOIN LambKid ON 
		Mate.IDDam = LambKid.IDDam AND Mate.Cycle = LambKid.Cycle 
    	    INNER JOIN Offspring ON 
		LambKid.IDDam = Offspring.IDDam AND LambKid.Cycle = Offspring.Cycle 
    	    INNER JOIN SheepGoat ON 
		Mate.IDSire = SheepGoat.IDSheepGoat
	WHERE (SheepGoat.IDFarm = @IDFarm) AND 
    	    (SheepGoat.DateBirth <= @DateMinAge) AND
    	    ((SheepGoat.IDDispReas = "-") OR
    	    ((SheepGoat.IDDispReas <> "-" AND SheepGoat.DateDisp > @DateEnd))) AND 
    	    (Offspring.IDLambKid <> "-")
    /*CREATE NONCLUSTERED INDEX IX_SumGenEval_FarmBrdSrOffsp ON -- Create the IDLambKid index.
    	SumGenEval_FarmBrdSrOffsp (IDLambKid) ON [PRIMARY]*/
GO
spSelectInto_SumGenEval_FarmBrdSrOffsp "¿¿", "01.23.03" -- "23.01.03" -- "12/31/02" -- "12.05.93" 
GO
SELECT * FROM SumGenEval_FarmBrdSrOffsp
GO
