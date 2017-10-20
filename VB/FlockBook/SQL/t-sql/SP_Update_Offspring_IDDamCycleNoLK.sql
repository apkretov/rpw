USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spUpdate_Offspring_IDDamCycleNoLK" AND 
    type = "P")
    DROP PROCEDURE spUpdate_Offspring_IDDamCycleNoLK
GO
CREATE PROCEDURE spUpdate_Offspring_IDDamCycleNoLK (@IDDam char(6), @Cycle tinyint, 
    @NoLambKidOrigin tinyint, @NoLambKid tinyint, @IDLambKid char(6), @IDSex char(1), 
    @WtBirth real, @IDLiv char(1)) AS
    IF @WtBirth = 0 -- Convert zero to NULL.
	SET @WtBirth = NULL
    UPDATE Offspring
	SET IDDam = @IDDam, Cycle = @Cycle, NoLambKid = @NoLambKid, IDLambKid = @IDLambKid, 
	    IDSex = @IDSex, WtBirth = @WtBirth/10, IDLiv = @IDLiv
	WHERE IDDam = @IDDam and Cycle = @Cycle and NoLambKid = @NoLambKidOrigin
GO
SELECT * FROM Offspring WHERE IDDam = "юб0001"
GO
spUpdate_Offspring_IDDamCycleNoLK "юб0001", 1, 2, 2, "юб0011", "1", 55, "0"
GO
SELECT * FROM Offspring WHERE IDDam = "юб0001"
GO