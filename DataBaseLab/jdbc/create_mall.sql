create table product(
    product_id int AUTO_INCREMENT,
    product_name varchar(50) NOT NULL,
    product_company_id int NOT NULL,
    quantity_left int ,
    price int  NOT NULL,
    constraint pk_product primary key (product_id)
);
create table purchase(
    purchase_id int AUTO_INCREMENT,
    bill_id int ,
    product_id int ,
    quantity int  NOT NULL,
    constraint pk_purchase primary key (purchase_id)
);
create table bill(
    bill_id int  AUTO_INCREMENT,
    customer_id int  NOT NULL,
    payment_id int ,
    bill_amount int  NOT NULL,
    constraint pk_bill primary key (bill_id)
);
create table payment(
    payment_id int  AUTO_INCREMENT,
    payment_method varchar(50)  NOT NULL,
    bill_id int NOT NULL,
    constraint pk_payment primary key (payment_id),
    constraint valid_payment_id CHECK(payment_method='CreditCard' or payment_method='DebitCard' or payment_method='Cash' or payment_method='UPI')
);