USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spInsert_StandDiameter" AND type = "P")
    DROP PROCEDURE spInsert_StandDiameter
GO
CREATE PROCEDURE spInsert_StandDiameter (@IDBreed char(2), @MaleMax char(2), @MaleMin char(2),
    @MaleElite char(2), @MaleClass1 char(2), @FemaleMax char(2), @FemaleMin char(2), 
    @FemaleElite char(2), @FemaleClass1 char(2)) AS
    INSERT INTO StandDiameter (IDBreed, MaleMax, MaleMin, MaleElite, MaleClass1, FemaleMax, 
	FemaleMin, FemaleElite, FemaleClass1)
	VALUES (@IDBreed, @MaleMax, @MaleMin, @MaleElite, @MaleClass1, @FemaleMax, @FemaleMin, 
	    @FemaleElite, @FemaleClass1)
GO
SELECT * FROM StandDiameter
GO
spInsert_StandDiameter "99", "56", "56", "56", "56", "56", "56", "56", "56"
GO
SELECT * FROM StandDiameter
GO