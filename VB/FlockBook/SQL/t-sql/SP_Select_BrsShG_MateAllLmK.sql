USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE NAME = "spSelect_BrsShG_MateAllLmK" AND type = "P")
    DROP PROCEDURE spSelect_BrsShG_MateAllLmK
GO
CREATE PROCEDURE spSelect_BrsShG_MateAllLmK (@IDFarm char(2), @DateDispMin int, @DateDispMax int) AS
--    SET DATEFORMAT dmy
    SELECT SheepGoat.IDFarm, Mate.IDDam, Mate.Cycle, Mate.IDSire, Mate.DateMatFrom, 
	LambKid.DateLambKid
	FROM Mate 
	    INNER JOIN SheepGoat ON 
		Mate.IDDam = SheepGoat.IDSheepGoat 
     	    LEFT OUTER JOIN LambKid ON 
		Mate.IDDam = LambKid.IDDam AND Mate.Cycle = LambKid.Cycle
	WHERE ((SheepGoat.IDFarm = @IDFarm) AND 
	    (SheepGoat.DateDisp >= @DateDispMin) AND 
	    (SheepGoat.DateDisp <= @DateDispMax))
GO
spSelect_BrsShG_MateAllLmK "ÀÀ", 0, 65500 -- All.
--spSelect_BrsShG_MateAllLmK "ÀÀ", 0, 0 -- Kept.
--spSelect_BrsShG_MateAllLmK "ÀÀ", 1, 65500 -- Disposed.
GO
