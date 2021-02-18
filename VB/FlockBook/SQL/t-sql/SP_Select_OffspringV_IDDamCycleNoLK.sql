USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spSelect_OffspringV_IDDamCycleNoLK" AND 
    type = "P")
    DROP PROCEDURE spSelect_OffspringV_IDDamCycleNoLK
GO
CREATE PROCEDURE spSelect_OffspringV_IDDamCycleNoLK (@IDDam char(6), @Cycle tinyint, 
    @NoLambKid tinyint) AS
    SELECT IDDam, Cycle, NoLambKid, IDLambKid, IDSex, Sex, ISNULL(WtBirth, 0) AS WtBirth, IDLiv,
	Liv 
	FROM OffspringV
	WHERE IDDam = @IDDam AND 
	    Cycle = @Cycle AND 
	    NoLambKid = @NoLambKid
GO
spSelect_OffspringV_IDDamCycleNoLK "юб0001", 1, 3
GO