USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE NAME = "spSelect_TransFarm_Grid" AND type = "P")
    DROP PROCEDURE spSelect_TransFarm_Grid
GO
CREATE PROCEDURE spSelect_TransFarm_Grid (@IDFarm char(2)) AS
    SELECT IDSheepGoat AS [��������� �� �����], DateTrans AS [���� �����������]
	FROM TransFarm
	WHERE (IDFarm = @IDFarm)
GO
spSelect_TransFarm_Grid "��"
GO
