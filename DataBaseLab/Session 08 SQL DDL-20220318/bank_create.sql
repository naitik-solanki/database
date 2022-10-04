create table bank(
    bank_id int auto AUTO_INCREMENT NOT NULL,
    bank_name varchar(30) NOT NULL,
    constraint pk_bank_id primary key(bank_id)
);
create table branch(
    Branch_id int AUTO_INCREMENT NOT NULL,
    Branch_code int NOT NULL,
    UNIQUE(Branch_code),
    Branch_address int NOT NULL,
    UNIQUE(Branch_address),
    Branch_city int NOT NULL,
    bank_id int NOT NULL,
    constraint pk_Branch_id PRIMARY KEY (Branch_id)
);
create table Account(
    Account_id int AUTO_INCREMENT,
    Account_number int NOT NULL,
    UNIQUE(Account_number),
    Account_balance int NOT NULL,
    Account_type ENUM('SavingsAcc','CurrentAcc','DepositAcc') NOT NULL,
    Branch_id int NOT NULL,
    constraint pk_Account_id PRIMARY KEY (Account_id)

);
create table Customer (
    Customer_id int AUTO_INCREMENT,
    customer_number int NOT NULL,
    UNIQUE(customer_number),
    Cust_name varchar(30) NOT NULL,
    Cust_address varchar(60) NOT NULL,
    Cust_city varchar(30) NOT NULL,
    constraint pk_Customer_id PRIMARY KEY (Customer_id)
);
create table Owned_by(
    owned_by_id int AUTO_INCREMENT,
    Account_id int NOT NULL,
    Customer_id int NOT NULL,
    constraint pk_Owned_by_id PRIMARY KEY(owned_by_id)
);
create table Current_Account(
    CurrentAccount_id int AUTO_INCREMENT,
    Overdraft_limit int NOT NULL,
    constraint pk_CurrentAccount_id PRIMARY KEY(CurrentAccount_id)
);
create table DepositAcc(
    DepositAccount_id int AUTO_INCREMENT,
    Investment_amount int NOT NULL,
    Maturity_amount int NOT NULL,
    Interest_rate int NOT NULL,
    Maturity_date date NOT NULL,
    constraint pk_Deposit_account_id PRIMARY KEY(DepositAccount_id)
);
create table SavingsAcc(
    SavingsAccount_id int AUTO_INCREMENT,
    Minimum_balance int NOT NULL,
    constraint pk_SavingsAccount_id PRIMARY KEY (SavingsAccount_id)
);
create table Transaction(
    Transaction_id int AUTO_INCREMENT,
    Transaction_amount int NOT NULL,
    Txn_type varchar(30),
    Txn_date date NOT NULL,
    SavingsAccount_id int NOT NULL,
    constraint pk_Transaction_id PRIMARY KEY (Transaction_id)
);
