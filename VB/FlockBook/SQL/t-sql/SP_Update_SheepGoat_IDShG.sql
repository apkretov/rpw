USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spUpdate_SheepGoat_IDShG" AND type = "P")
    DROP PROCEDURE spUpdate_SheepGoat_IDShG
GO
CREATE PROCEDURE spUpdate_SheepGoat_IDShG ( @IDSheepGoatOrigin char(6), @IDFarm char(2), 
    @IDSheepGoat char(6), @IDSex char(1), @IDBreedBase char(2),	@Crossed bit, 
    @BreedCross varchar(100), @DateBirth smalldatetime/*varchar(8)*/, @IDFarmBirth char(2), 
    @TypeBirth tinyint/*char(1)*/, @IDSire char(6), @IDDam char(6), @DateDisp  smalldatetime/*varchar(8)*/, 
    @IDDispReas char(2), @Remark varchar(150) ) AS
    --SET DATEFORMAT dmy
    UPDATE SheepGoat
	SET IDFarm = @IDFarm, IDSheepGoat = @IDSheepGoat, IDSex = @IDSex, 
	    IDBreedBase = @IDBreedBase, Crossed = @Crossed, BreedCross = @BreedCross, 
	    DateBirth = /*CAST(*/@DateBirth /*AS smalldatetime)*/, IDFarmBirth = @IDFarmBirth, 
	    TypeBirth = @TypeBirth, IDSire = @IDSire, IDDam = @IDDam, 
	    DateDisp = /*CAST(*/@DateDisp /*AS smalldatetime)*/, IDDispReas = @IDDispReas, 
	    Remark = @Remark
	WHERE IDSheepGoat = @IDSheepGoatOrigin
GO
spUpdate_SheepGoat_IDShG "ÀÂ0001", "ÀÂ", "ÀÂ0001", "1", "ÊÈ", 0, "ÊÈ", "01.01.98", "- ", 
    1/*TypeBirth*/, "-", "-", "01.01.1900", "-", "-"
GO