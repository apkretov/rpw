USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spUpdate_Defects_Defct" AND type = "P")
    DROP PROCEDURE spUpdate_Defects_Defct
GO
CREATE PROCEDURE spUpdate_Defects_Defct (@IDDefect int, @Defect varchar(50), 
    @Remark varchar(150)) AS
    UPDATE Defects
	SET Defect = @Defect, Remark = @Remark
	WHERE IDDefect = @IDDefect 
GO
SELECT * FROM Defects 
GO
spUpdate_Defects_Defct 5, "99999999", "99999999"
GO
SELECT * FROM Defects 
GO