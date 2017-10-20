-- TO BE REMOVED
USE Test
GO
CREATE PROCEDURE spInsertFarms (@IDFarm char(6), @IDTownVill char(6))
AS
INSERT INTO Farms
(IDFarm, IDTownVill, IDPersFarmer, IDPersCont, Remark)
VALUES (@IDFarm, @IDTownVill, "¿—¿Õ01", "¿—¿Õ02", "-")
GO