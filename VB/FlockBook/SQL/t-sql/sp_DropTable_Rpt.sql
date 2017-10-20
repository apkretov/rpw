USE FlockBook
GO
IF EXISTS (SELECT name FROM sysobjects WHERE name = "spDropTable_SumFlockManagm" AND type = "P")
    DROP PROCEDURE spDropTable_SumFlockManagm
GO
CREATE PROCEDURE spDropTable_SumFlockManagm AS

if exists (select * from sysobjects where id = object_id(N'[dbo].[SumGenEval_Appraisal]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[SumGenEval_Appraisal]

if exists (select * from sysobjects where id = object_id(N'[dbo].[SumGenEval_ApprSire]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[SumGenEval_ApprSire]

if exists (select * from sysobjects where id = object_id(N'[dbo].[SumGenEval_FarmBrdSrOffsp]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[SumGenEval_FarmBrdSrOffsp]

if exists (select * from sysobjects where id = object_id(N'[dbo].[SumGenEval_Farms]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[SumGenEval_Farms]

if exists (select * from sysobjects where id = object_id(N'[dbo].[SumGenEval_Weight]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[SumGenEval_Weight]

if exists (select * from sysobjects where id = object_id(N'[dbo].[SumGenEval_WeightSire]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[SumGenEval_WeightSire]

if exists (select * from sysobjects where id = object_id(N'[dbo].[SumGenEval_Wool]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[SumGenEval_Wool]

if exists (select * from sysobjects where id = object_id(N'[dbo].[SumGenEval_WoolSire]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[SumGenEval_WoolSire]

if exists (select * from sysobjects where id = object_id(N'[dbo].[SumGenEval_Wt7Mon]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[SumGenEval_Wt7Mon]

if exists (select * from sysobjects where id = object_id(N'[dbo].[SumGenEval_Wt7MonSire]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[SumGenEval_Wt7MonSire]

if exists (select * from sysobjects where id = object_id(N'[dbo].[SumGenEval_WtBirth]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[SumGenEval_WtBirth]

if exists (select * from sysobjects where id = object_id(N'[dbo].[SumGenEval_WtBirthSire]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[SumGenEval_WtBirthSire]

if exists (select * from sysobjects where id = object_id(N'[dbo].[SumGenEval_WtWean]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[SumGenEval_WtWean]

if exists (select * from sysobjects where id = object_id(N'[dbo].[SumGenEval_WtWeanSire]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[SumGenEval_WtWeanSire]

if exists (select * from sysobjects where id = object_id(N'[dbo].[SumPerform_Appraisal]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[SumPerform_Appraisal]

if exists (select * from sysobjects where id = object_id(N'[dbo].[SumPerform_Farms]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[SumPerform_Farms]

if exists (select * from sysobjects where id = object_id(N'[dbo].[SumPerform_MaxAge]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[SumPerform_MaxAge]

if exists (select * from sysobjects where id = object_id(N'[dbo].[SumPerform_SheepGoat]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[SumPerform_SheepGoat]

if exists (select * from sysobjects where id = object_id(N'[dbo].[SumPerform_Weight7Mon]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[SumPerform_Weight7Mon]

if exists (select * from sysobjects where id = object_id(N'[dbo].[SumPerform_WeightWean]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[SumPerform_WeightWean]

if exists (select * from sysobjects where id = object_id(N'[dbo].[SumPerform_WeightWoolAnnl]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[SumPerform_WeightWoolAnnl]

if exists (select * from sysobjects where id = object_id(N'[dbo].[SumFlockManagm_Appraisal]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[SumFlockManagm_Appraisal]

if exists (select * from sysobjects where id = object_id(N'[dbo].[SumFlockManagm_BearDistr1]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[SumFlockManagm_BearDistr1]

if exists (select * from sysobjects where id = object_id(N'[dbo].[SumFlockManagm_BearDistr2]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[SumFlockManagm_BearDistr2]

if exists (select * from sysobjects where id = object_id(N'[dbo].[SumFlockManagm_BearDistr_AllAge]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[SumFlockManagm_BearDistr_AllAge]

if exists (select * from sysobjects where id = object_id(N'[dbo].[SumFlockManagm_Disp1]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[SumFlockManagm_Disp1]

if exists (select * from sysobjects where id = object_id(N'[dbo].[SumFlockManagm_Disp2]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[SumFlockManagm_Disp2]

if exists (select * from sysobjects where id = object_id(N'[dbo].[SumFlockManagm_Disp3]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[SumFlockManagm_Disp3]

if exists (select * from sysobjects where id = object_id(N'[dbo].[SumFlockManagm_Disp_All]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[SumFlockManagm_Disp_All]

if exists (select * from sysobjects where id = object_id(N'[dbo].[SumFlockManagm_Disp_Female2All]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[SumFlockManagm_Disp_Female2All]

if exists (select * from sysobjects where id = object_id(N'[dbo].[SumFlockManagm_Disp_Female4All]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[SumFlockManagm_Disp_Female4All]

if exists (select * from sysobjects where id = object_id(N'[dbo].[SumFlockManagm_Disp_Female6All]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[SumFlockManagm_Disp_Female6All]

if exists (select * from sysobjects where id = object_id(N'[dbo].[SumFlockManagm_Disp_Male1All]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[SumFlockManagm_Disp_Male1All]

if exists (select * from sysobjects where id = object_id(N'[dbo].[SumFlockManagm_Disp_Male3All]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[SumFlockManagm_Disp_Male3All]

if exists (select * from sysobjects where id = object_id(N'[dbo].[SumFlockManagm_Disp_Male5All]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[SumFlockManagm_Disp_Male5All]

if exists (select * from sysobjects where id = object_id(N'[dbo].[SumFlockManagm_Disp_TotalDisp]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[SumFlockManagm_Disp_TotalDisp]

if exists (select * from sysobjects where id = object_id(N'[dbo].[SumFlockManagm_Farms]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[SumFlockManagm_Farms]

if exists (select * from sysobjects where id = object_id(N'[dbo].[SumFlockManagm_LambKid]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[SumFlockManagm_LambKid]

if exists (select * from sysobjects where id = object_id(N'[dbo].[SumFlockManagm_LambKidCount]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[SumFlockManagm_LambKidCount]

if exists (select * from sysobjects where id = object_id(N'[dbo].[SumFlockManagm_LambKidWeaned]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[SumFlockManagm_LambKidWeaned]

if exists (select * from sysobjects where id = object_id(N'[dbo].[SumFlockManagm_Mate]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[SumFlockManagm_Mate]

if exists (select * from sysobjects where id = object_id(N'[dbo].[SumFlockManagm_Offspring]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[SumFlockManagm_Offspring]

if exists (select * from sysobjects where id = object_id(N'[dbo].[SumFlockManagm_PerfAge]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[SumFlockManagm_PerfAge]

if exists (select * from sysobjects where id = object_id(N'[dbo].[SumFlockManagm_PerfAge_GreaseAge]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[SumFlockManagm_PerfAge_GreaseAge]

if exists (select * from sysobjects where id = object_id(N'[dbo].[SumFlockManagm_PerfAge_GreaseGroup]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[SumFlockManagm_PerfAge_GreaseGroup]

if exists (select * from sysobjects where id = object_id(N'[dbo].[SumFlockManagm_PerfAge_WeightAge]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[SumFlockManagm_PerfAge_WeightAge]

if exists (select * from sysobjects where id = object_id(N'[dbo].[SumFlockManagm_PerfAge_WeightGroup]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[SumFlockManagm_PerfAge_WeightGroup]

if exists (select * from sysobjects where id = object_id(N'[dbo].[SumFlockManagm_PerfSexAge]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[SumFlockManagm_PerfSexAge]

if exists (select * from sysobjects where id = object_id(N'[dbo].[SumFlockManagm_PerfSexAge_FarmSexAge]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[SumFlockManagm_PerfSexAge_FarmSexAge]

if exists (select * from sysobjects where id = object_id(N'[dbo].[SumFlockManagm_PerfSexAge_WoolAnnl]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[SumFlockManagm_PerfSexAge_WoolAnnl]

if exists (select * from sysobjects where id = object_id(N'[dbo].[SumFlockManagm_PerfSexAge_WoolMaxAge]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[SumFlockManagm_PerfSexAge_WoolMaxAge]

if exists (select * from sysobjects where id = object_id(N'[dbo].[SumFlockManagm_PerfSexAge_WtAnnl]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[SumFlockManagm_PerfSexAge_WtAnnl]

if exists (select * from sysobjects where id = object_id(N'[dbo].[SumFlockManagm_PerfSexAge_WtBirth]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[SumFlockManagm_PerfSexAge_WtBirth]

if exists (select * from sysobjects where id = object_id(N'[dbo].[SumFlockManagm_PerfSexAge_WtMaxAge]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[SumFlockManagm_PerfSexAge_WtMaxAge]

if exists (select * from sysobjects where id = object_id(N'[dbo].[SumFlockManagm_Reprod]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[SumFlockManagm_Reprod]

if exists (select * from sysobjects where id = object_id(N'[dbo].[SumFlockManagm_Reprod_AbortCount]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[SumFlockManagm_Reprod_AbortCount]

if exists (select * from sysobjects where id = object_id(N'[dbo].[SumFlockManagm_Reprod_OffspBornCount]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[SumFlockManagm_Reprod_OffspBornCount]

if exists (select * from sysobjects where id = object_id(N'[dbo].[SumFlockManagm_SheepGoat]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[SumFlockManagm_SheepGoat]

if exists (select * from sysobjects where id = object_id(N'[dbo].[SumFlockManagm_SheepGoatDisp]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[SumFlockManagm_SheepGoatDisp]

if exists (select * from sysobjects where id = object_id(N'[dbo].[SumFlockManagm_Weight7Mon]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[SumFlockManagm_Weight7Mon]

if exists (select * from sysobjects where id = object_id(N'[dbo].[SumFlockManagm_WeightAnnl]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[SumFlockManagm_WeightAnnl]

if exists (select * from sysobjects where id = object_id(N'[dbo].[SumFlockManagm_WeightWean]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[SumFlockManagm_WeightWean]

if exists (select * from sysobjects where id = object_id(N'[dbo].[SumFlockManagm_WoolAnnl]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[SumFlockManagm_WoolAnnl]

if exists (select * from sysobjects where id = object_id(N'[dbo].[Cert_ApprAge_YrAll]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[Cert_ApprAge_YrAll]

if exists (select * from sysobjects where id = object_id(N'[dbo].[Cert_Appraisal]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[Cert_Appraisal]

if exists (select * from sysobjects where id = object_id(N'[dbo].[Cert_PerfAge_YrAll]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[Cert_PerfAge_YrAll]

if exists (select * from sysobjects where id = object_id(N'[dbo].[Cert_SheepGoat]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[Cert_SheepGoat]

if exists (select * from sysobjects where id = object_id(N'[dbo].[Cert_SheepGoatDam]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[Cert_SheepGoatDam]

if exists (select * from sysobjects where id = object_id(N'[dbo].[Cert_SheepGoatSire]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[Cert_SheepGoatSire]

if exists (select * from sysobjects where id = object_id(N'[dbo].[Cert_WeightWoolAnnl]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[Cert_WeightWoolAnnl]

if exists (select * from sysobjects where id = object_id(N'[dbo].[CertEweShegoat_LambKid]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[CertEweShegoat_LambKid]

if exists (select * from sysobjects where id = object_id(N'[dbo].[CertEweShegoat_Offspring]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[CertEweShegoat_Offspring]

if exists (select * from sysobjects where id = object_id(N'[dbo].[CertRamHegoat_BV_Appr]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[CertRamHegoat_BV_Appr]

if exists (select * from sysobjects where id = object_id(N'[dbo].[CertRamHegoat_BV_Weight]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[CertRamHegoat_BV_Weight]

if exists (select * from sysobjects where id = object_id(N'[dbo].[CertRamHegoat_BV_Wool]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[CertRamHegoat_BV_Wool]

if exists (select * from sysobjects where id = object_id(N'[dbo].[CertRamHegoat_BV_Wt7Mon]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[CertRamHegoat_BV_Wt7Mon]

if exists (select * from sysobjects where id = object_id(N'[dbo].[CertRamHegoat_BV_WtBirth]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[CertRamHegoat_BV_WtBirth]

if exists (select * from sysobjects where id = object_id(N'[dbo].[CertRamHegoat_BV_WtWean]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[CertRamHegoat_BV_WtWean]

if exists (select * from sysobjects where id = object_id(N'[dbo].[CertRamHegoat_Mate]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[CertRamHegoat_Mate]

if exists (select * from sysobjects where id = object_id(N'[dbo].[CertRamHegoat_SireOffspring]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[CertRamHegoat_SireOffspring]

if exists (select * from sysobjects where id = object_id(N'[dbo].[FrmAppr]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[FrmAppr]

if exists (select * from sysobjects where id = object_id(N'[dbo].[FrmInvMat]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[FrmInvMat]

if exists (select * from sysobjects where id = object_id(N'[dbo].[FrmLmK_LambKid]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[FrmLmK_LambKid]

if exists (select * from sysobjects where id = object_id(N'[dbo].[FrmLmK_Mate]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[FrmLmK_Mate]

if exists (select * from sysobjects where id = object_id(N'[dbo].[FrmWtLmK]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[FrmWtLmK]

if exists (select * from sysobjects where id = object_id(N'[dbo].[FrmWtWool]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[FrmWtWool]

GO


spDropTable_SumFlockManagm
GO