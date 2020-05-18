USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE NAME = "spSelect_Farms_GridFarmer" AND type = "P")
    DROP PROCEDURE spSelect_Farms_GridFarmer
GO
CREATE PROCEDURE spSelect_Farms_GridFarmer (@Nam varchar(100)) AS
    SELECT Farms.IDFarm AS [������ �� �����]
	FROM Persons 
	    INNER JOIN Farms ON 
		Persons.IDPers = Farms.IDPersFarmer
	WHERE Persons.Nam = @Nam
	ORDER BY Persons.Nam
GO
spSelect_Farms_GridFarmer "������ ���������� ��������" -- "���������� �������� ������������"
GO

