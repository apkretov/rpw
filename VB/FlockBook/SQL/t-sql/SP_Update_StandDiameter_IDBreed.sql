USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spUpdate_StandDiameter_IDBreed" AND type = 
    "P")
    DROP PROCEDURE spUpdate_StandDiameter_IDBreed
GO
CREATE PROCEDURE spUpdate_StandDiameter_IDBreed (@IDBreed char(2), @MaleMax char(2), 
    @MaleMin char(2), @MaleElite char(2), @MaleClass1 char(2), @FemaleMax char(2), 
    @FemaleMin char(2), @FemaleElite char(2), @FemaleClass1 char(2)) AS
    UPDATE StandDiameter
	SET MaleMax = @MaleMax, MaleMin = @MaleMin, MaleElite = @MaleElite, MaleClass1 = 
	    @MaleClass1, FemaleMax = @FemaleMax, FemaleMin = @FemaleMin, FemaleElite = 
	    @FemaleElite, FemaleClass1 = @FemaleClass1
	WHERE IDBreed = @IDBreed
GO
SELECT * FROM StandDiameter 
GO
spUpdate_StandDiameter_IDBreed "99", "58", "58", "58", "58", "58", "58", "58", "58"
GO
SELECT * FROM StandDiameter 
GO