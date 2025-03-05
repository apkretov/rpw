USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spInsert_StandFatTail" AND type = "P")
    DROP PROCEDURE spInsert_StandFatTail
GO
CREATE PROCEDURE spInsert_StandFatTail (@IDBreed char(2), @MaleMax char(1), @MaleMin char(1),
    @MaleElite char(1), @MaleClass1 char(1), @FemaleMax char(1), @FemaleMin char(1), 
    @FemaleElite char(1), @FemaleClass1 char(1)) AS
    INSERT INTO StandFatTail (IDBreed, MaleMax, MaleMin, MaleElite, MaleClass1, FemaleMax, 
	FemaleMin, FemaleElite, FemaleClass1)
	VALUES (@IDBreed, @MaleMax, @MaleMin, @MaleElite, @MaleClass1, @FemaleMax, @FemaleMin, 
	    @FemaleElite, @FemaleClass1)
GO
SELECT * FROM StandFatTail
GO
spInsert_StandFatTail "99", "5", "5", "5", "5", "5", "5", "5", "5"
GO
SELECT * FROM StandFatTail
GO