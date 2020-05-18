USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spInsert_Farms" AND type = "P")
    DROP PROCEDURE spInsert_Farms
GO
CREATE PROCEDURE spInsert_Farms (@IDFarm char(2), @IDTownVill int, @IDPersFarmer int, 
    @IDPersCont int, @Remark varchar(150)) AS
    INSERT INTO Farms (IDFarm, IDTownVill, IDPersFarmer, IDPersCont, Remark)
	VALUES (@IDFarm, @IDTownVill, @IDPersFarmer, @IDPersCont, @Remark)
GO
SELECT * FROM Farms
GO
spInsert_Farms "ZZ", 1, 14, 2, "DKJDJAJD DHD DJF DIUFHD "
GO
SELECT * FROM Farms
GO