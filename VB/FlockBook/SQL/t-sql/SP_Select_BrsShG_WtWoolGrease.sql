USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE NAME = "spSelect_BrsShG_WtWoolGrease" 
    AND type = "P")
    DROP PROCEDURE spSelect_BrsShG_WtWoolGrease
GO
CREATE PROCEDURE spSelect_BrsShG_WtWoolGrease (@IDFarm char(2), @DateDispMin int, 
    @DateDispMax int) AS
    SELECT SheepGoat.IDFarm, WeightWoolAnnl.IDSheepGoat, WeightWoolAnnl.Age, 
	WeightWoolAnnl.DateAnnl, WeightWoolAnnl.WtAnnl, WeightWoolAnnl.DateShearAnnl, 
	WeightWoolAnnl.GreaseAnnl
	FROM WeightWoolAnnl 
	    INNER JOIN SheepGoat ON 
    		WeightWoolAnnl.IDSheepGoat = SheepGoat.IDSheepGoat
	WHERE (SheepGoat.IDFarm = @IDFarm) AND
	    (SheepGoat.DateDisp >= @DateDispMin) AND 
	    (SheepGoat.DateDisp <= @DateDispMax) AND
	    (WeightWoolAnnl.DateAnnl IS NULL/*= @DateNull*/) AND
	    (WeightWoolAnnl.DateShearAnnl IS NOT NULL/*> @DateNull*/)
GO						
spSelect_BrsShG_WtWoolGrease "юб", 0, 65500 -- All. 
GO
-- The disposition parameters: 
    -- 0, 0 	- Kept;
    -- 1, 65500 - Disposed.