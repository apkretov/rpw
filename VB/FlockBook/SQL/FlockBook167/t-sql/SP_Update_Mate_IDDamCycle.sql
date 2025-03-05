USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spUpdate_Mate_IDDamCycle" AND type = "P")
    DROP PROCEDURE spUpdate_Mate_IDDamCycle
GO
CREATE PROCEDURE spUpdate_Mate_IDDamCycle (@IDDam char(6), @Cycle tinyint, @CycleLambKid tinyint,
    @DateMatFrom varchar(8), @IDSire char(6)) AS
    SET DATEFORMAT dmy
    UPDATE Mate
	SET IDDam = @IDDam, Cycle = @Cycle, CycleLambKid = @CycleLambKid, DateMatFrom = 
	    CAST(@DateMatFrom AS smalldatetime), IDSire = @IDSire
	WHERE IDDam = @IDDam AND 
	    Cycle = @Cycle
GO
SELECT * FROM Mate 
    WHERE IDDam = "응0001"
GO
spUpdate_Mate_IDDamCycle "응0001", 5, 5, "02.02.02", "응0000"
GO
SELECT * FROM Mate 
    WHERE IDDam = "응0001"
GO