create table product(
    Pid int  AUTO_INCREMENT,
    pname varchar(30),
    pcat varchar(30),
    price int,
    constraint pk_product PRIMARY KEY (Pid)
);

create table purchase(
    Txn_id int AUTO_INCREMENT,
    P_id int,
    qty int,
    constraint pk_purchase PRIMARY KEY (Txn_id)
);
