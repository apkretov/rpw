use test
begin tran

select /*c_PrepareId
      ,*/c_name
      ,c_namerep
      ,c_ToDo
      --,c_Order
from T_Prepare
  
/*
select c_ToDo, count(c_ToDo) Count_
from T_Prepare
group by c_ToDo
order by c_ToDo
*/

/*
select c_Order, count(c_Order) Count_
from T_Prepare
where c_Order not in ('10', '100', '101', '11', '20', '22', '5')
group by c_Order
order by c_Order
*/

rollback tran