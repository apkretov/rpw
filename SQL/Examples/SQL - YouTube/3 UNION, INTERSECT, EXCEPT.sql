use test
drop table t1
drop table t2

create table t1 (f1 int)
create table t2 (f1 int)

insert into t1 values
	(1),
	(2),
	(3)

insert into t2 values
	(3),
	(4),
	(5)

select * from t1
select * from t2

select * from t1
union
select * from t2

select * from t1
union all
select * from t2

select * from t1
intersect
select * from t2

select * from t1
except
select * from t2

select * from t2
except
select * from t1