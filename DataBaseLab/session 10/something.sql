select e.fname,count(d.essn) 
from employee e 
inner  join 
dependent d on e.ssn=d.essn
group by e.ssn;

select p.* , pur.*
from product p 
inner join 
purchase pur
on p.Pid = pur.P_id;

select p.pname,sum(p.price*pur.qty) as 'total'
from product p 
inner join 
purchase pur
on p.pid = pur.P_id
group by p.pname;

select pname,
from product 
where pid not in (select P_id from purchase);

select pname,Txn_id,qty
from purchase RIGHT JOIN 
product on 
product.pid = purchase.P_id
;

select e.fname, count(d.essn)
from employee e 
natural join dependent d
group by e.ssn;

select * from employee where dno = 4 
union select * from employee where dno=5;

select fname from employee e
where not exists(
    select * from works_on w 
    where w.essn = e.ssn
);