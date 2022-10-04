select * from employee;
select fname,salary from employee;
/*
select <column list>
from <table list>
where <filter condition>
group by <column lsit>
having <filter condition>
order by <column list>
*/

select fname as 'First name' from employee;/* to give an alias name*/

select fname , salary/12 as 'monthly salary' from employee;

select concat(fname, ' ',lname) as 'Fullname' from employee;

select fname, dno , salary from employee where dno=5 and sex='M';

select fname from employee where super_ssn is not NULL;
/*while using NULL , you cannot use = , use is instead*/

select fname from employee where fname like 'j%';

select min(salary) as 'minimum',max(salary),sum(salary),avg(salary) from employee where dno=4;

select count(*) from employee;

select count(fname) from employee;

select count(super_ssn) from employee;

select distinct dno from employee;

-- nested quries
-- remember this pattern
select fname,salary from employee where salary=(select max(salary) from employee); 

select * from dept_locations;

select fname,dno from employee where dno in (select dnumber from dept_locations where dlocation = 'Houston');

select fname,salary 
from employee 
where salary>
(select avg(salary) 
from employee
);

select e1.fname,e1.salary,e1.dno
from employee e1
where e1.salary >
(select avg(e2.salary) from employee e2 
where e2.dno = e1.dno);

select fname, salary from employee where salary between 25000 and 40000; /* inclusive*/

select dno, avg(salary)
from employee
group by dno;

select dlocation,count(dlocation)
from dept_locations
group by dlocation;

select year(bdate),count(year(bdate))
from employee
group by year(bdate);

select dno,sex,avg(salary) 
from employee
group by sex,dno;

select dno,sex,avg(salary) 
from employee
where dno in (select dnumber from dept_locations where dlocation='Houston')
group by sex,dno
having avg(salary)>30000;

select fname, dno, salary 
from employee 
order by dno,salary desc;



-- join operation

select e.ssn,d.dname,dd.dependent_name
from employee e
inner join department d
on e.dno = d.dnumber
inner join dependent dd
on e.ssn = dd.essn;

select fname,dname 
from employee e,
department d,
dependent dd
where e.dno = d.dnumber 
and
e.ssn = dd.essn;
