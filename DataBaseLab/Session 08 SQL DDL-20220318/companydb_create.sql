create table employee (
  fname varchar(30) NOT NULL,
  minit char(1) NOT NULL,
  lname varchar(30) NOT NULL,
  ssn int,
  bdate date,
  address varchar(60),
  sex char(1),
  salary int,
  super_ssn int,
  dno smallint NOT NULL,
  constraint pk_employee PRIMARY KEY (ssn)
);

create table department (
  dname varchar(30) NOT NULL,
  dnumber smallint,
  mgr_ssn int,
  mgr_start_date date,
  constraint pk_department PRIMARY KEY(dnumber)
);
create table dept_locations (
  dnumber smallint,
  dlocation varchar(60),
  constraint pk_dept_location PRIMARY KEY (dnumber,dlocation)
);
create table project(
  pname varchar(30),
  pnumber smallint,
  plocation varchar(60),
  dnum smallint,
  constraint pk_project PRIMARY KEY (pnumber)
);
create table works_on(
  essn int,
  pno smallint,
  hours smallint,
  constraint pk_works_on PRIMARY KEY (essn,pno)
);
create table dependent(
  essn int,
  dependent_name varchar(60),
  sex char(1),
  bdate date,
  relationship varchar(60),
  constraint pk_dependent PRIMARY KEY(essn,dependent_name)
);
