insert into product(Pid,pname,pcat,price) values 
    (1,'Book','STAT',1) , 
    (2,'pen','STAT',1),
    (3,'T-shirt','App',1),
    (4,'Shirt','App',1),
    (5,'Computer','Elec',1),
    (6,'Laptop','Elec',1),
    (7,'Phone','Elec',1);

insert into purchase(Txn_id,P_id,qty) values
    (1,1,5),
    (2,1,3),
    (3,4,10),
    (4,4,3);