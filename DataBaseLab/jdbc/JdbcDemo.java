//STEP 1. Import required packages

import java.sql.*;
import java.util.Scanner;



public class JdbcDemo {

   static final String JDBC_DRIVER = "com.mysql.jdbc.Driver";  
   static final String DB_URL = "jdbc:mysql://localhost/shopping_mall?useSSL=false";
   static final String USER = "root";// add your user 
   static final String PASS = "Naitik178*";// add password
   static Scanner sc = new Scanner(System.in);
   static String sql;
   

   public static void main(String[] args) {
   Connection conn = null;
   Statement stmt = null;

   
// STEP 2. Connecting to the Database
   try{
      //STEP 2a: Register JDBC driver
      Class.forName(JDBC_DRIVER);
      //STEP 2b: Open a connection
      System.out.println("Connecting to database...");
      conn = DriverManager.getConnection(DB_URL,USER,PASS);
      //STEP 2c: Execute a query
      System.out.println("Creating statement...");
      stmt = conn.createStatement();

//STEP 3: Query to database
      

while(true)
{
         System.out.println();
         System.out.println("---------------------------------------------------------------------");
         System.out.println("1. Add a product");
         System.out.println("2. Remove a product");
         System.out.println("3. Change price of a product");
         System.out.println("4. Increase quantity of  product");
         System.out.println("5. Decrease quantity of a product");
         System.out.println("6. Create a bill");
         System.out.println("7. Add a purchase");
         System.out.println("8. Get price of a  product");
         System.out.println("9. Show amount spent by a given customer");
         System.out.println("10. Show list of all available products");
         System.out.println("11. Show a bill");
         System.out.println("12. remove a purchase");
         System.out.println("13. exit");
         int key = sc.nextInt();
         if(key==13)
         {
            break;
         }
         switch (key) 
         {
            case 1:
            {
               System.out.println("Enter product name");
               String name = sc.next();
               System.out.println("Enter product company_id");
               int C_id = sc.nextInt();
               System.out.println("Enter product price");
               int price = sc.nextInt();
               System.out.println("Enter quantity of the product");
               int quantity = sc.nextInt();
               Product.add_product(stmt, name, C_id, quantity, price);
               break;
            }
            case 2:
            {
               System.out.println("Enter product id");
               int id = sc.nextInt();
               Product.remove_product(stmt, id);
               break;
            }
            case 3:
            {
               System.out.println("Enter the product id");
               int id = sc.nextInt();
               System.out.println("Enter the new price of the product");
               int price = sc.nextInt();
               Product.change_product_price(stmt, id, price);
               break;
            }
            case 4:
            {
               System.out.println("Enter the product id");
               int id = sc.nextInt();
               System.out.println("Enter the new quantity of the product to be added");
               int quant = sc.nextInt();
               Product.add_product_quantity(stmt, id, quant);
               break;
            }
            case 5:
            {
               System.out.println("Enter the product id");
               int id = sc.nextInt();
               System.out.println("Enter the new quantity of the product to be removed");
               int quant = sc.nextInt();
               Product.decrease_product_quantity(stmt, id, quant);
               break;
            }
            case 6:
            {
               System.out.println("Enter payment method");
               String payment_method = sc.next();
               System.out.println("Enter customer id ");
               int customer_id = sc.nextInt();
               bill.create_new_bill(stmt, payment_method, customer_id);
               break;
            }
            case 7:
            {
               System.out.println("Enter the product id");
               int product_id = sc.nextInt();
               System.out.println("Enter the quantity");
               int quantity = sc.nextInt();
               System.out.println("Enter the bill id");
               int bill_id = sc.nextInt();
               Purchase.add_purchase(stmt, bill_id, product_id, quantity);
               break;
            }
            case 8:
            {
               System.out.println("Enter the product id");
               int id = sc.nextInt();
               int price =Product.get_product_price(stmt, id);
               System.out.println(price);
               break;
            }
            case 9:
            {
               System.out.println("Enter customer id");
               int customer_id = sc.nextInt();
               bill.get_amount_spent(stmt, customer_id);
               break;
            }
            case 10:
            {
               Product.get_available_products(stmt);
               break;
            }
            case 11:
            {
               System.out.println("Enter bill id");
               int bill_id = sc.nextInt();
               bill.getBill(stmt, bill_id);
               break;
            }
            case 12:
            {
               System.out.println("Enter purchase id");
               int purchase_id = sc.nextInt();
               System.out.println(purchase_id);
               Purchase.remove_purchase(stmt, purchase_id);
               break;
            }
            default:
               break;

         }
         System.out.println();
         System.out.println("---------------------------------------------------------------------");
}

      sc.close();

//STEP 5: Clean-up environment
      stmt.close();
      conn.close();
	}catch(SQLException se){    	 //Handle errors for JDBC
      	se.printStackTrace();
   	}catch(Exception e){        	//Handle errors for Class.forName
      e.printStackTrace();
   }finally{				//finally block used to close resources
      try{
         if(stmt!=null)
            stmt.close();
      }catch(SQLException se2){
      }
      try{
         if(conn!=null)
            conn.close();
      }catch(SQLException se){
         se.printStackTrace();
      }					//end finally try
   }					//end try
   System.out.println("End of Code");

   }				
}					


//Note : By default autocommit is on. you can set to false using con.setAutoCommit(false)
