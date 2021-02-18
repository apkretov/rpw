USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spUpdate_Tree_Refrsh" AND type = "P")
    DROP PROCEDURE spUpdate_Tree_Refrsh
GO
CREATE PROCEDURE spUpdate_Tree_Refrsh (@Refrsh bit) AS
    UPDATE Tree
	SET Refrsh = @Refrsh
GO
SELECT * FROM Tree
GO
spUpdate_Tree_Refrsh 0
GO
SELECT * FROM Tree
GO