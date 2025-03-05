USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE NAME = "spSelect_Persons_Grid" AND type = "P")
    DROP PROCEDURE spSelect_Persons_Grid
GO
CREATE PROCEDURE spSelect_Persons_Grid (@TownVill varchar(50)) AS
    SELECT /*TownVill.TownVill AS [Населённый пункт],*/ Persons.Nam AS Участник/*Участники*/
	FROM TownVill 
	    INNER JOIN Persons ON 
    		TownVill.IDTownVill = Persons.IDTownVill
	WHERE TownVill.TownVill = @TownVill
	ORDER BY Persons.Nam
GO
spSelect_Persons_Grid "БАТК01"
GO
