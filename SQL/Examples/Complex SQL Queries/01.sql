use test
go

/*
Employee_num 	Employee_name 	Department
1 	Rahul 	OBIEE
1 	Rahul 	OBIEE
2 	Rohit 	OBIEE
*/

drop table Employee;
create table Employee(
	Employee_num int,
	Employee_name text,
	Department text
)

insert into Employee values
	(1, 'Rahul', 'OBIEE'),
	(1, 'Rahul', 'OBIEE'),
	(2, 'Rohit', 'OBIEE')
select * from Employee
go

