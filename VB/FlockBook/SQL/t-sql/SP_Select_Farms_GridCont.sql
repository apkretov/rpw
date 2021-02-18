USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE NAME = "spSelect_Farms_GridCont" AND type = "P")
    DROP PROCEDURE spSelect_Farms_GridCont
GO
CREATE PROCEDURE spSelect_Farms_GridCont (@Nam varchar(100)) AS
    SELECT Farms.IDFarm AS [Контактное лицо на ферме]
	FROM Persons 
	    INNER JOIN Farms Farms ON 
		Persons.IDPers = Farms.IDPersCont
	WHERE Persons.Nam = @Nam
	ORDER BY Persons.Nam
GO
spSelect_Farms_GridCont "Асанов Куванычбек Асанович" -- "Асанакунов Кенешбек Асанакунович"
GO

