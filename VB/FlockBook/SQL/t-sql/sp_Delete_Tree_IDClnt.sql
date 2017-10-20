USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spDelete_Tree_IDClnt" AND type = "P")
    DROP PROCEDURE spDelete_Tree_IDClnt
GO
CREATE PROCEDURE spDelete_Tree_IDClnt (@IDClnt as char(9)) AS
    DELETE Tree
	WHERE IDClnt = @IDClnt
GO
SELECT * FROM Tree
GO
spDelete_Tree_IDClnt "705547512"
GO
SELECT * FROM Tree
GO