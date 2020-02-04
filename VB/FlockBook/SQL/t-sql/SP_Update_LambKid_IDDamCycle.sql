USE FlockBook
GO

IF EXISTS (SELECT name FROM sysobjects WHERE 
	name = "spUpdate_LambKid_IDDamCycle" AND type = "P")
DROP PROCEDURE spUpdate_LambKid_IDDamCycle
GO

CREATE PROCEDURE spUpdate_LambKid_IDDamCycle (@IDDam char(6), @Cycle tinyint, 
	@CycleLambKid tinyint, @DateLambKid smalldatetime/*varchar(8)*/, 
	@TypeBirth tinyint/*char(1)*/, @Abort char(1))
AS
--SET DATEFORMAT dmy
UPDATE LambKid
SET IDDam = @IDDam, Cycle = @Cycle, CycleLambKid = @CycleLambKid, DateLambKid = 
	/*CAST(*/@DateLambKid /*AS smalldatetime)*/, TypeBirth = @TypeBirth, Abort = @Abort
WHERE IDDam = @IDDam and Cycle = @Cycle
GO

spUpdate_LambKid_IDDamCycle "юб0001", 2, 1, "01.06.99", 3, 0
GO