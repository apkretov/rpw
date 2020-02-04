USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE NAME = "spSelect_PersonsFarms_Grid" AND type = "P")
    DROP PROCEDURE spSelect_PersonsFarms_Grid
GO
CREATE PROCEDURE spSelect_PersonsFarms_Grid (@TownVill varchar(50)) AS
    SELECT TownVill.TownVill AS [��������� �����], Farms.IDFarm AS �����, Persons.Nam AS 
	�������, Persons1.Nam AS [���������� ����]
	FROM TownVill 
	    INNER JOIN Farms ON 
    		TownVill.IDTownVill = Farms.IDTownVill 
	    INNER JOIN Persons ON 
    		Farms.IDPersFarmer = Persons.IDPers 
	    LEFT OUTER JOIN Persons Persons1 ON 
    		Farms.IDPersCont = Persons1.IDPers
	WHERE TownVill.TownVill = @TownVill
	ORDER BY Farms.IDFarm
GO
spSelect_PersonsFarms_Grid "����01"
GO
