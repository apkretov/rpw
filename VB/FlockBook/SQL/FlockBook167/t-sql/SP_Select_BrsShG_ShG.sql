USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE NAME = "spSelect_BrsShG_ShG" AND 
	type = "P")
DROP PROCEDURE spSelect_BrsShG_ShG
GO
CREATE PROCEDURE spSelect_BrsShG_ShG (@IDFarm char(2), @IDSexMl char(1), @IDSexFm char(1), 
	@CrossedPure bit, @CrossedCross bit, @AgeMin /*small*/int, @AgeMax /*small*/int, 
	@DateDispMin int, @DateDispMax int)
AS
--SET DATEFORMAT dmy
SELECT SheepGoat.IDFarm, SheepGoat.IDSheepGoat, Sex.Sex, 
    SheepGoat.BreedCross, SheepGoat.DateBirth, 
    SheepGoat.IDSire, SheepGoat.IDDam, 
    SheepGoat.TypeBirth, SheepGoat.IDFarmBirth, 
    BrsShG_ShG_Disp.DateDisp, 
    Disposition.DispReas, CopmClass.CompClass, 
    TestSire.DateTestSire, SheepGoat.Remark
FROM TestSire RIGHT OUTER JOIN
    SheepGoat INNER JOIN
    Sex ON 
    SheepGoat.IDSex = Sex.IDSex INNER JOIN
    Disposition ON 
    SheepGoat.IDDispReas = Disposition.IDDispReas ON 
    TestSire.IDSire = SheepGoat.IDSheepGoat LEFT OUTER
     JOIN
    CopmClass INNER JOIN
    SelIndxCompClass ON 
    CopmClass.IDCompClass = SelIndxCompClass.IDCompClass
     ON 
    SheepGoat.IDSheepGoat = SelIndxCompClass.IDSheepGoat
     LEFT OUTER JOIN
    BrsShG_ShG_Disp ON 
    SheepGoat.IDSheepGoat = BrsShG_ShG_Disp.IDSheepGoat
WHERE ((SheepGoat.IDFarm = @IDFarm) AND 
	((SheepGoat.IDSex = @IDSexMl) OR (SheepGoat.IDSex = @IDSexFm)) AND 
	((SheepGoat.Crossed = @CrossedPure) OR (SheepGoat.Crossed = @CrossedCross)) AND 
	(GETDATE() - SheepGoat.DateBirth > @AgeMin) AND 
	(GETDATE() - SheepGoat.DateBirth < @AgeMax) AND 
	(SheepGoat.DateDisp >= @DateDispMin) AND 
	(SheepGoat.DateDisp <= @DateDispMax))
GO
spSelect_BrsShG_ShG "юб", "0", "1", 0, 1, 0, 65500, 0, 65500
--spSelect_BrsShG_ShG "юб", "0", "1", 0, 1, 0, 7300, 0, 65500
GO