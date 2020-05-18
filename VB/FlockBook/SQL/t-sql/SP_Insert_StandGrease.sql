USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spInsert_StandGrease" AND type = "P")
    DROP PROCEDURE spInsert_StandGrease
GO
CREATE PROCEDURE spInsert_StandGrease (@IDBreed char(2), @MaleMax real, @MaleMin real,
    @MaleElite real, @MaleClass1 real, @FemaleMax real, @FemaleMin real, @FemaleElite real,
    @FemaleClass1 real) AS
    INSERT INTO StandGrease (IDBreed, MaleMax, MaleMin, MaleElite, MaleClass1, FemaleMax, 
	FemaleMin, FemaleElite, FemaleClass1)
	VALUES (@IDBreed, @MaleMax / 10, @MaleMin / 10, @MaleElite / 10, @MaleClass1 / 10, 
	    @FemaleMax / 10, @FemaleMin / 10, @FemaleElite / 10, @FemaleClass1 / 10)
GO
SELECT * FROM StandGrease
GO
spInsert_StandGrease "99", 999, 999, 999, 999, 999, 999, 999, 999
GO
SELECT * FROM StandGrease
GO