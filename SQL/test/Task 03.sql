use test
begin tran

/*
-- Populata a test table.
set identity_insert test_data2 on -- Cannot insert explicit value for identity column in table 'table' when IDENTITY_INSERT is set to OFF @ https://stackoverflow.com/questions/1334012/cannot-insert-explicit-value-for-identity-column-in-table-table-when-identity
insert into test_data2(c_addr, id)
select top 3	
	-- tp.*,	
	td.*
	-- tp.c_name,
	-- tp.c_namerep,
	-- replace(td.c_addr, tp.c_name, tp.c_namerep) replaced
from T_Prepare as tp,
test_data as td
where td.c_addr like '% ' + tp.c_name + ' %'
set identity_insert test_data2 off -- Cannot insert explicit value for identity column in table 'table' when IDENTITY_INSERT is set to OFF @ https://stackoverflow.com/questions/1334012/cannot-insert-explicit-value-for-identity-column-in-table-table-when-identity
select * from test_data2
*/

/*
create table t(f int) -- Test testing uniquness.
insert into t values(0)
insert into t values(1)
insert into t values(1)
insert into t values(2)

select * from t

select f, count(f) as count_
from t
group by f
having count(f) > 1

select count(id) as count_id -- Test uniquness of id.
from test_data

select count(id) as count_id
from test_data
group by id
having count(id) > 1
*/

select /*top 3*/ * from test_data -- The data before.
go

select top 3 tp.*, -- The replacements.
	td2.*,
	replace(td2.c_addr, tp.c_name, tp.c_namerep) as c_addr_replaced
from T_Prepare as tp, 
	test_data as td2
where td2.c_addr like '% ' + tp.c_name + ' %'
go

update test_data -- Update the data.
set c_addr = replace(tpR.c_addr, tpR.c_name, tpR.c_namerep)
from (
	select td.c_addr,
		td.id,
		tp.c_name, 
		tp.c_namerep
	from T_Prepare as tp, 
		test_data as td
	where td.c_addr like '% ' + tp.c_name + ' %'
) as tpR -- The T_Prepare-replacemnts table.
where test_data.id = tpR.id
go

select /*top 3*/ * from test_data -- The data after.
go

rollback tran
-- commit tran

/* Messages:

(99999 rows affected)

(3 rows affected)

(12382 rows affected)

(99999 rows affected)
*/