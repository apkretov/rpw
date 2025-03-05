USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spSelectInto_FrmLmK_Mate" AND type = "P")
    DROP PROCEDURE spSelectInto_FrmLmK_Mate
GO
CREATE PROCEDURE spSelectInto_FrmLmK_Mate (@IDFarm char(2), @Date varchar(8)) AS 
    DECLARE @DateConv smalldatetime
    DECLARE @PregnLengMax smallint
    DECLARE @DateMateBeg smalldatetime
    SET DATEFORMAT dmy
    SET @DateConv = CAST(@Date AS smalldatetime) -- Convert the date.
    SELECT @PregnLengMax = PregnLengMax FROM ContrlParam -- The maximal pregnancy term.
    SET @DateMateBeg = @DateConv - @PregnLengMax -- The mating date to begin filtering from.
    IF EXISTS (SELECT * FROM sysobjects WHERE name = "FrmLmK_Mate" AND type  = "U") 
	DROP TABLE FrmLmK_Mate -- Drop the previous table. 
    SELECT SheepGoat.IDFarm, Mate.IDDam, Mate.Cycle, Mate.DateMatFrom, Mate.IDSire -- Create a 
	INTO FrmLmK_Mate 							   -- new table.
	FROM SheepGoat INNER JOIN Mate ON SheepGoat.IDSheepGoat = Mate.IDDam
	WHERE (SheepGoat.IDFarm = @IDFarm) AND 
	    (SheepGoat.IDDispReas = "-") AND
	    (Mate.DateMatFrom <= @DateConv) AND
	    (Mate.DateMatFrom >= @DateMateBeg) 
    ALTER TABLE FrmLmK_Mate -- Create the primary key.
	ADD CONSTRAINT PK_FrmLmK_Mate PRIMARY KEY CLUSTERED (IDDam, Cycle) ON [PRIMARY]
GO
spSelectInto_FrmLmK_Mate "¿¿", "01.01.00"
GO
SELECT * FROM FrmLmK_Mate
GO