USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spSelect_Tree_IDClnt" AND type = "P")
    DROP PROCEDURE spSelect_Tree_IDClnt
GO
CREATE PROCEDURE spSelect_Tree_IDClnt (@IDClnt as char(9)) AS
    SELECT * FROM Tree
	WHERE IDClnt = @IDClnt
GO 
spSelect_Tree_IDClnt "123456789"
GO