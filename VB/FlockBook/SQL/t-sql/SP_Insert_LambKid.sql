USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spInsert_LambKid" AND type = "P")
DROP PROCEDURE spInsert_LambKid
GO
CREATE PROCEDURE spInsert_LambKid (@IDDam char(6), @Cycle tinyint, @CycleLambKid tinyint, 
    @DateLambKid smalldatetime/*varchar(8)*/, @TypeBirth tinyint/*char(1)*/, @Abort bit) AS
    --SET DATEFORMAT dmy
    INSERT INTO LambKid(IDDam, Cycle, CycleLambKid, DateLambKid, TypeBirth, Abort)
	VALUES (@IDDam, @Cycle, @CycleLambKid, /*CAST(*/@DateLambKid /*AS smalldatetime)*/, 
	    @TypeBirth, @Abort)
GO
spInsert_LambKid  "юб0001", 1, 1, "01.06.03", 1, 0
GO