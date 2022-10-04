insert into product(product_name,product_company_id,quantity_left,price) values 
('Apple',1,50,800),
('Mango',1,100,500),
('Banana',1,10,30),
('Kiwi',2,5,600),
('Orange',2,40,100),
('Grapes',2,20,110),
('Water Bottle',3,40,120),
('Moisturizer',4,80,300),
('Water Bottle-1',5,20,400),
('Water Bottle-2',5,10,100),
('T-shirt-1',6,3,800),
('T-shirt-2',6,1,900);

insert into purchase(bill_id,product_id,quantity) values
(1,1,2),
(1,3,4),
(1,7,1),
(2,5,3),
(3,6,3),
(4,8,2);

insert into bill(customer_id,payment_id,bill_amount) values
(1,1,1040),
(2,2,300),
(3,3,330),
(4,3,600);

insert into payment(payment_method,bill_id) values
('Cash',1),
('UPI',2),
('CreditCard',3),
('DebitCard',4);