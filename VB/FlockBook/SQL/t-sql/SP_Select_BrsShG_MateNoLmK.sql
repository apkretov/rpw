USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE NAME = "spSelect_BrsShG_MateNoLmK" AND type = "P")
    DROP PROCEDURE spSelect_BrsShG_MateNoLmK
GO
CREATE PROCEDURE spSelect_BrsShG_MateNoLmK (@IDFarm char(2), @DateDispMin int, @DateDispMax int) 
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
	    (LambKid.IDDam IS NULL)
GO
spSelect_BrsShG_MateNoLmK "ÀÀ", 0, 65500
GO
