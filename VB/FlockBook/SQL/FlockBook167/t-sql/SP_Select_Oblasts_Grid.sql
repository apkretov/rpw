USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE NAME = "spSelect_Oblasts_Grid" AND type = "P")
    DROP PROCEDURE spSelect_Oblasts_Grid
GO
CREATE PROCEDURE spSelect_Oblasts_Grid (@Country varchar(50)) AS
    SELECT /*Countries.Country AS Страна,*/ Oblasts.Oblast AS Область/*Области*//*, Oblasts.Remark AS Заметки*/
	FROM Countries 
	    INNER JOIN Oblasts ON 
    		Countries.IDCountry = Oblasts.IDCountry
	WHERE Countries.Country = @Country
	ORDER BY Oblasts.Oblast
GO
spSelect_Oblasts_Grid "Кыргызстан"
GO
