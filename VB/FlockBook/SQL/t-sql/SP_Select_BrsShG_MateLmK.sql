USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE NAME = "spSelect_BrsShG_MateLmK" AND type = "P")
    DROP PROCEDURE spSelect_BrsShG_MateLmK
GO
CREATE PROCEDURE spSelect_BrsShG_MateLmK (@IDFarm char(2), @DateDispMin int, @DateDispMax int) 
    AS
--    SET DATEFORMAT dmy
    SELECT SheepGoat.IDFarm, Mate.IDDam, Mate.Cycle, Mate.IDSire, Mate.DateMatFrom, 
	LambKid.DateLambKid
	FROM Mate 
	    INNER JOIN SheepGoat ON 
		Mate.IDDam = SheepGoat.IDSheepGoat 
     	    LEFT OUTER JOIN LambKid ON 
		Mate.IDDam = LambKid.IDDam AND Mate.Cycle = LambKid.Cycle
	WHERE (SheepGoat.IDFarm = @IDFarm) AND 
	    (SheepGoat.DateDisp >= @DateDispMin) AND 
	    (SheepGoat.DateDisp <= @DateDispMax) AND
	    (LambKid.IDDam IS NOT NULL)
GO
spSelect_BrsShG_MateLmK "ÀÀ", 0, 65500
GO
