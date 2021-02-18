USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE NAME = "spSelect_BrsShG_LmK" AND type = "P")
    DROP PROCEDURE spSelect_BrsShG_LmK
GO
CREATE PROCEDURE spSelect_BrsShG_LmK (@IDFarm char(2), @AbortNo char(1), @AbortYes char(1), 
    @DateDispMin int, @DateDispMax int, @IDSexOffspMl char(1), @IDSexOffspFm char(1), 
    @IDLivAliv char(1), @IDLivDead char(1)) AS
    DECLARE @IDSexDead char(1)
    DECLARE @IDLiv0 char(1)
    DECLARE @IDLiv1 char(1)
    DECLARE @IDLiv2 char(1)
    DECLARE @IDLivDead1 char(1)
    DECLARE @IDLivDead2 char(1)
--    SET DATEFORMAT dmy
    SET @IDSexDead = "-" -- Initialise the dead offspring's sex constant.
    SET @IDLiv0 = "0" -- Initialise the livability constants.
    SET @IDLiv1 = "1" 
    SET @IDLiv2 = "2"
    IF @IDLivDead = @IDLiv0 -- Define the dead variables.
	BEGIN -- Nullify the dead codes.
	SET @IDLivDead1 = @IDLiv0
	SET @IDLivDead2 = @IDLiv0
	END
    ELSE -- Distinguish 2 different dead codes.
	BEGIN
	SET @IDLivDead1 = @IDLiv1
	SET @IDLivDead2 = @IDLiv2
	END
    SELECT SheepGoat.IDFarm, LambKid.IDDam, LambKid.Cycle, LambKid.DateLambKid, AbortYN.AbortYN, 
	Offspring.IDLambKid, SexOffspring.Sex, Offspring.WtBirth, Liveability.Liv
	FROM SheepGoat 
	    INNER JOIN LambKid ON 
    		SheepGoat.IDSheepGoat = LambKid.IDDam 
	    INNER JOIN AbortYN ON 
		LambKid.Abort = AbortYN.Abort 
	    LEFT OUTER JOIN SexOffspring 
	    INNER JOIN Offspring ON 
    		SexOffspring.IDSex = Offspring.IDSex 
	    INNER JOIN Liveability ON 
    		Offspring.IDLiv = Liveability.IDLiv ON 
    		LambKid.IDDam = Offspring.IDDam AND LambKid.Cycle = Offspring.Cycle
	WHERE ( (SheepGoat.IDFarm = @IDFarm) AND 
	    ((LambKid.Abort = @AbortNo) OR (LambKid.Abort = @AbortYes)) AND 
	    (SheepGoat.DateDisp >= @DateDispMin) AND 
	    (SheepGoat.DateDisp <= @DateDispMax) AND
	    ((ISNULL(Offspring.IDSex, @IDSexOffspMl) = @IDSexOffspMl) OR -- Replace the NULL's
	    (ISNULL(Offspring.IDSex, @IDSexOffspFm) = @IDSexOffspFm) OR  -- with the compared
	    (ISNULL(Offspring.IDSex, @IDSexDead) = @IDSexDead)) AND      -- values not to exclude
	    ((ISNULL(Offspring.IDLiv, @IDLivAliv) = @IDLivAliv) OR   	 -- such records 
	    (ISNULL(Offspring.IDLiv, @IDLivDead1) = @IDLivDead1) OR	 -- altogether.
	    (ISNULL(Offspring.IDLiv, @IDLivDead2) = @IDLivDead2)) )   
GO						
spSelect_BrsShG_LmK "ÀÀ", "0", "1", 0, 65500, "0", "1", "0", "1" -- All. 
GO
-- The disposition parameters: 
    -- 0, 0 	- Kept;
    -- 1, 65500 - Disposed.