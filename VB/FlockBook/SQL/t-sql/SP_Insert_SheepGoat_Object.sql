USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spInsert_SheepGoat_Object" AND type = "P")
    DROP PROCEDURE spInsert_SheepGoat_Object
GO
CREATE PROCEDURE spInsert_SheepGoat_Object ( @IDFarm char(2), @IDSheepGoat char(6), 
    @IDSex char(1), @IDBreedBase char(2), @Crossed bit, @BreedCross varchar(100), 
    @DateBirth smalldatetime/*varchar(8)*/, @IDFarmBirth char(2), @TypeBirth tinyint/*char(1)*/, 
    @IDSire char(6), @IDDam char(6), @DateDisp  smalldatetime/*varchar(8)*/, @IDDispReas char(2),
    @Remark varchar(150) ) AS
    --SET DATEFORMAT dmy
    INSERT INTO SheepGoat(IDFarm, IDSheepGoat, IDSex, IDBreedBase, Crossed, BreedCross, 
	DateBirth, IDFarmBirth, TypeBirth, IDSire, IDDam, DateDisp, IDDispReas, Remark)
	VALUES ( @IDFarm, @IDSheepGoat, @IDSex, @IDBreedBase, @Crossed,	@BreedCross, 	
	    /*CAST(*/@DateBirth /*AS smalldatetime)*/,	@IDFarmBirth, @TypeBirth, @IDSire, @IDDam, 
	    /*CAST(*/@DateDisp /*AS smalldatetime)*/, @IDDispReas, @Remark )
GO
spInsert_SheepGoat_Object "юб", "юб9999", "0", "юб", 0, "юб", "1/1/00", "юб", 1/*TypeBirth*/, 
    "-", "-", "1/1/1900", "-", "-"
GO