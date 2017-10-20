USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spSelectInto_FrmLmK_LambKid" AND type = "P")
    DROP PROCEDURE spSelectInto_FrmLmK_LambKid
GO
CREATE PROCEDURE spSelectInto_FrmLmK_LambKid (@IDFarm char(2), @Date varchar(8)) AS 
    DECLARE @DateConv smalldatetime
    SET DATEFORMAT dmy
    SET @DateConv = CAST(@Date AS smalldatetime) -- Convert the date.
    IF EXISTS (SELECT * FROM sysobjects WHERE name = "FrmLmK_LambKid" AND type  = "U") 
	DROP TABLE FrmLmK_LambKid -- Drop the previous table. 
    SELECT LambKid.IDDam, LambKid.Cycle -- Create a new table.
	INTO FrmLmK_LambKid 
	FROM SheepGoat INNER JOIN LambKid ON SheepGoat.IDSheepGoat = LambKid.IDDam
	WHERE (SheepGoat.IDFarm = @IDFarm) AND 
	    (SheepGoat.IDDispReas = "-") AND
	    (LambKid.DateLambKid <= @DateConv)
    ALTER TABLE FrmLmK_LambKid -- Create the primary key.
	ADD CONSTRAINT PK_FrmLmK_LambKid PRIMARY KEY CLUSTERED (IDDam, Cycle) ON [PRIMARY]
GO
spSelectInto_FrmLmK_LambKid "ÀÀ", "01.01.03"
GO
SELECT * FROM FrmLmK_LambKid
GO