alter table purchase
add constraint fk_purchase_bill_id foreign key(bill_id) REFERENCES bill(bill_id) on delete  cascade;
alter table purchase
add constraint fk_purchase_product_id foreign key(product_id) REFERENCES product(product_id) on delete  cascade;
alter table bill
add constraint fk_bill_payment_id foreign key(payment_id) REFERENCES payment(payment_id) on delete  cascade;