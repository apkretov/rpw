USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spUpdate_StandGrease_IDBreed" AND type = 
    "P")
    DROP PROCEDURE spUpdate_StandGrease_IDBreed
GO
CREATE PROCEDURE spUpdate_StandGrease_IDBreed (@IDBreed char(2), @MaleMax real, @MaleMin real, 
    @MaleElite real, @MaleClass1 real, @FemaleMax real, @FemaleMin real, @FemaleElite real, 
    @FemaleClass1 real) AS
    UPDATE StandGrease
	SET MaleMax = @MaleMax / 10, MaleMin = @MaleMin / 10, MaleElite = @MaleElite / 10, 
	    MaleClass1 = @MaleClass1 / 10, FemaleMax = @FemaleMax / 10, FemaleMin = 
	    @FemaleMin / 10, FemaleElite = @FemaleElite / 10, FemaleClass1 = @FemaleClass1 / 10
	WHERE IDBreed = @IDBreed
GO
SELECT * FROM StandGrease 
GO
spUpdate_StandGrease_IDBreed "ZZ", 999, 999, 999, 999, 999, 999, 999, 999
GO
SELECT * FROM StandGrease 
GO