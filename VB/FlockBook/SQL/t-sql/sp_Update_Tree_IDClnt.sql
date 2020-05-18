USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spUpdate_Tree_IDClnt" AND type = "P")
    DROP PROCEDURE spUpdate_Tree_IDClnt
GO
CREATE PROCEDURE spUpdate_Tree_IDClnt (@IDClnt as char(9), @Refrsh bit) AS
    UPDATE Tree
	SET Refrsh = @Refrsh
	    WHERE IDClnt = @IDClnt
GO
SELECT * FROM Tree
GO
spUpdate_Tree_IDClnt "123456789", 0
GO
SELECT * FROM Tree
GO