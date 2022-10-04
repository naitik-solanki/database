alter table employee
  add constraint fk_super_ssn FOREIGN KEY (super_ssn)
  REFERENCES employee(ssn);
alter table employee
  add constraint fk_dno FOREIGN KEY (dno)
  REFERENCES department(dnumber);
alter table department
  add constraint fk_mgr_ssn FOREIGN KEY(mgr_ssn)
  REFERENCES employee(ssn);
alter table dept_locations
  add constraint fk_dnumber FOREIGN KEY(dnumber)
  REFERENCES department(dnumber);
alter table project
  add constraint fk_dnum FOREIGN KEY(dnum)
  REFERENCES department(dnumber);
alter table works_on
  add constraint fk_essn FOREIGN KEY(essn)
  REFERENCES employee(ssn);
alter table works_on
  add constraint fk_pno FOREIGN KEY(pno)
  REFERENCES project(pnumber);
alter table dependent
  add constraint fk_dept_essn FOREIGN KEY(essn)
  REFERENCES employee(ssn);
