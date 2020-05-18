USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE NAME = "spSelect_BrsShG_WtWoolAll" AND type = "P")
    DROP PROCEDURE spSelect_BrsShG_WtWoolAll
GO
CREATE PROCEDURE spSelect_BrsShG_WtWoolAll (@IDFarm char(2), @DateDispMin int, @DateDispMax int) 
    AS
    SELECT SheepGoat.IDFarm, WeightWoolAnnl.IDSheepGoat, WeightWoolAnnl.Age, 
	WeightWoolAnnl.DateAnnl, WeightWoolAnnl.WtAnnl, WeightWoolAnnl.DateShearAnnl, 
	WeightWoolAnnl.GreaseAnnl 
	FROM WeightWoolAnnl 
	    INNER JOIN SheepGoat ON 
    		WeightWoolAnnl.IDSheepGoat = SheepGoat.IDSheepGoat
	WHERE (SheepGoat.IDFarm = @IDFarm) AND
	    (SheepGoat.DateDisp >= @DateDispMin) AND 
	    (SheepGoat.DateDisp <= @DateDispMax)
GO						
spSelect_BrsShG_WtWoolAll "юб", 0, 65500 -- All. 
GO
-- The disposition parameters: 
    -- 0, 0 	- Kept;
    -- 1, 65500 - Disposed.