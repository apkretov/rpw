USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE NAME = "spSelect_BrsShG_WtLmK7Mon" AND type = "P")
    DROP PROCEDURE spSelect_BrsShG_WtLmK7Mon
GO
CREATE PROCEDURE spSelect_BrsShG_WtLmK7Mon (@IDFarm char(2), @DateDispMin int, @DateDispMax int) 
    AS
--    SET DATEFORMAT dmy
    SELECT SheepGoat.IDFarm, SheepGoat.IDSheepGoat AS IDLambKid, WeightWean.DateWean, 
	WeightWean.WtWean, Weight7Mon.Date7Mon, Weight7Mon.Wt7Mon
	FROM SheepGoat 
	    LEFT OUTER JOIN WeightWean ON 
    		SheepGoat.IDSheepGoat = WeightWean.IDLambKid 
	    LEFT OUTER JOIN Weight7Mon ON 
    		SheepGoat.IDSheepGoat = Weight7Mon.IDLambKid
	WHERE (WeightWean.IDLambKid IS NULL) AND 
	    (Weight7Mon.IDLambKid IS NOT NULL) AND
	    (SheepGoat.IDFarm = @IDFarm) AND 
	    (SheepGoat.DateDisp >= @DateDispMin) AND 
	    (SheepGoat.DateDisp <= @DateDispMax)
GO						
spSelect_BrsShG_WtLmK7Mon "ÀÀ", 0, 65500 -- All. 
GO
-- The disposition parameters: 
    -- 0, 0 	- Kept;
    -- 1, 65500 - Disposed.