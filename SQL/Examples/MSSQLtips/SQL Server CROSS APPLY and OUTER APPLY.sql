use SQL -- SQL Server CROSS APPLY and OUTER APPLY @ https://www.mssqltips.com/sqlservertip/1958/sql-server-cross-apply-and-outer-apply/
begin tran

IF EXISTS (SELECT * FROM sys.objects WHERE OBJECT_ID = OBJECT_ID(N'[Employee]') AND type IN (N'U')) BEGIN DROP TABLE [Employee] END --Script #1 - Creating some temporary objects to work on...
IF EXISTS (SELECT * FROM sys.objects WHERE OBJECT_ID = OBJECT_ID(N'[Department]') AND type IN (N'U')) BEGIN DROP TABLE [Department] END 

CREATE TABLE [Department]( [DepartmentID] [int] NOT NULL PRIMARY KEY, [Name] VARCHAR(250) NOT NULL, ) ON [PRIMARY] 
INSERT [Department] ([DepartmentID], [Name]) VALUES (1, N'Engineering') 
INSERT [Department] ([DepartmentID], [Name]) VALUES (2, N'Administration') 
INSERT [Department] ([DepartmentID], [Name]) VALUES (3, N'Sales') 
INSERT [Department] ([DepartmentID], [Name]) VALUES (4, N'Marketing') 
INSERT [Department] ([DepartmentID], [Name]) VALUES (5, N'Finance') 

CREATE TABLE [Employee]( [EmployeeID] [int] NOT NULL PRIMARY KEY, [FirstName] VARCHAR(250) NOT NULL, [LastName] VARCHAR(250) NOT NULL, [DepartmentID] [int] NOT NULL REFERENCES [Department](DepartmentID), ) ON [PRIMARY] 
INSERT [Employee] ([EmployeeID], [FirstName], [LastName], [DepartmentID]) VALUES (1, N'Orlando', N'Gee', 1 ) 
INSERT [Employee] ([EmployeeID], [FirstName], [LastName], [DepartmentID]) VALUES (2, N'Keith', N'Harris', 2 ) 
INSERT [Employee] ([EmployeeID], [FirstName], [LastName], [DepartmentID]) VALUES (3, N'Donna', N'Carreras', 3 ) 
INSERT [Employee] ([EmployeeID], [FirstName], [LastName], [DepartmentID]) VALUES (4, N'Janet', N'Gates', 3 ) 

select * from Department
select * from Employee

/*
SELECT * FROM Department D --Script #2 - CROSS APPLY and INNER JOIN
CROSS APPLY ( 
   SELECT * FROM Employee E 
   WHERE E.DepartmentID = D.DepartmentID 
   ) A 
SELECT * FROM Department D 
INNER JOIN Employee E ON D.DepartmentID = E.DepartmentID 

SELECT * FROM Department D --Script #3 - OUTER APPLY and LEFT OUTER JOIN
OUTER APPLY ( 
   SELECT * FROM Employee E 
   WHERE E.DepartmentID = D.DepartmentID 
   ) A 
 
SELECT * FROM Department D 
LEFT OUTER JOIN Employee E ON D.DepartmentID = E.DepartmentID 
*/

IF EXISTS (SELECT * FROM sys.objects WHERE OBJECT_ID = OBJECT_ID(N'[fn_GetAllEmployeeOfADepartment]') AND type IN (N'IF')) BEGIN DROP FUNCTION dbo.fn_GetAllEmployeeOfADepartment END --Script #4 - APPLY with table-valued function
GO
CREATE FUNCTION dbo.fn_GetAllEmployeeOfADepartment(@DeptID AS INT)  
RETURNS TABLE 
AS 
RETURN ( 
   SELECT * FROM Employee E 
   WHERE E.DepartmentID = @DeptID 
   ) 
GO
 
SELECT * FROM Department D 
CROSS APPLY dbo.fn_GetAllEmployeeOfADepartment(D.DepartmentID) 

SELECT * FROM Department D 
OUTER APPLY dbo.fn_GetAllEmployeeOfADepartment(D.DepartmentID) 

rollback tran