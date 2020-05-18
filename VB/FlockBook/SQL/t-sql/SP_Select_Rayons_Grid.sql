USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE NAME = "spSelect_Rayons_Grid" AND type = "P")
    DROP PROCEDURE spSelect_Rayons_Grid
GO
CREATE PROCEDURE spSelect_Rayons_Grid (@Oblast varchar(50)) AS
    SELECT /*Oblasts.Oblast AS Область,*/ Rayons.Rayon AS Район/*Районы*//*, Rayons.Remark AS Заметки*/
	FROM Oblasts 
	    INNER JOIN Rayons ON 
    		Oblasts.IDOblast = Rayons.IDOblast
	WHERE Oblasts.Oblast = @Oblast
	ORDER BY Rayons.Rayon
GO
spSelect_Rayons_Grid "Баткенская"
GO
