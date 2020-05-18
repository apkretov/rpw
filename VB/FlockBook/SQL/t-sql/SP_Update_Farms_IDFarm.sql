USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spUpdate_Farms_IDFarm" AND type = "P")
    DROP PROCEDURE spUpdate_Farms_IDFarm
GO
CREATE PROCEDURE spUpdate_Farms_IDFarm (@IDFarmOrig char(2), @IDFarm char(2), @IDTownVill int, 
    @IDPersFarmer int, @IDPersCont int, @Remark varchar(150)) AS
    UPDATE Farms
	SET IDFarm = @IDFarm, IDTownVill = @IDTownVill, IDPersFarmer = @IDPersFarmer, 
	    IDPersCont = @IDPersCont, Remark = @Remark
	WHERE IDFarm = @IDFarmOrig
GO
SELECT * FROM Farms 
GO
spUpdate_Farms_IDFarm "ZZ", "YY", 1, 14, 2, "99999999999 999999999"
GO
SELECT * FROM Farms 
GO