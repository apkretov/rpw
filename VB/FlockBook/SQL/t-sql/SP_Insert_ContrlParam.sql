USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spInsert_ContrlParam" AND type = "P")
    DROP PROCEDURE spInsert_ContrlParam
GO
CREATE PROCEDURE spInsert_ContrlParam (@AgeWeanMin smallint, @AgeWeanMax smallint, 
    @Age7MonMin smallint, @Age7MonMax smallint, @Age1YrCheck bit, @Age1YrWtMin smallint, 
    @Age1YrWtMax smallint, @Age1YrShearMin smallint, @Age1YrShearMax smallint, 
    @AgeMatMinSire smallint, @AgeMatMinDam smallint, @LifeTimeMax tinyint, 
    @PregnLengMin smallint, @PregnLengNorm smallint, @PregnLengMax smallint, 
    @InterAnnlMin smallint, @InterAnnlMax smallint, @BreedBaseDam bit, @ConvCrossToPure bit,
    @BVTestLifeTime bit, @BVTestYr tinyint, @SelIndxScale smallint) AS
    INSERT INTO ContrlParam(AgeWeanMin, AgeWeanMax, Age7MonMin, Age7MonMax, Age1YrCheck, 
	Age1YrWtMin, Age1YrWtMax, Age1YrShearMin, Age1YrShearMax, AgeMatMinSire, AgeMatMinDam, 
	LifeTimeMax, PregnLengMin, PregnLengNorm, PregnLengMax, InterAnnlMin, InterAnnlMax, 
	BreedBaseDam, ConvCrossToPure, BVTestLifeTime, BVTestYr, SelIndxScale)
	VALUES (@AgeWeanMin, @AgeWeanMax, @Age7MonMin, @Age7MonMax, @Age1YrCheck, @Age1YrWtMin, 
	    @Age1YrWtMax, @Age1YrShearMin, @Age1YrShearMax, @AgeMatMinSire, @AgeMatMinDam, 
	    @LifeTimeMax, @PregnLengMin, @PregnLengNorm, @PregnLengMax, @InterAnnlMin, 
	    @InterAnnlMax, @BreedBaseDam, @ConvCrossToPure, @BVTestLifeTime, @BVTestYr, 
	    @SelIndxScale)
GO
SELECT * FROM ContrlParam 
GO
spInsert_ContrlParam 120, 150, 210, 240, 1, 365, 455, 365, 485, 180, 180, 10, 135, 150, 165, 305,
    425, 1, 0, 1, 1, 5
GO
SELECT * FROM ContrlParam 
GO