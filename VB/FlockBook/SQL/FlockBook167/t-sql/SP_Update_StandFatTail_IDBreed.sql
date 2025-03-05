USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spUpdate_StandFatTail_IDBreed" AND type = 
    "P")
    DROP PROCEDURE spUpdate_StandFatTail_IDBreed
GO
CREATE PROCEDURE spUpdate_StandFatTail_IDBreed (@IDBreed char(2), @MaleMax char(1), 
    @MaleMin char(1), @MaleElite char(1), @MaleClass1 char(1), @FemaleMax char(1), 
    @FemaleMin char(1), @FemaleElite char(1), @FemaleClass1 char(1)) AS
    UPDATE StandFatTail
	SET MaleMax = @MaleMax, MaleMin = @MaleMin, MaleElite = @MaleElite, MaleClass1 = 
	    @MaleClass1, FemaleMax = @FemaleMax, FemaleMin = @FemaleMin, FemaleElite = 
	    @FemaleElite, FemaleClass1 = @FemaleClass1
	WHERE IDBreed = @IDBreed
GO
SELECT * FROM StandFatTail 
GO
spUpdate_StandFatTail_IDBreed "99", "4", "4", "4", "4", "4", "4", "4", "4"
GO
SELECT * FROM StandFatTail 
GO