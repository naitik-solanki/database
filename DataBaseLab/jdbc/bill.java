import java.sql.*;

import javax.naming.spi.DirStateFactory.Result;
public class bill {
    public static void create_new_bill(Statement stmt,String payment_method,int customer_id)
    {
        try {
            String sql;
            Payment.create_payment(stmt, payment_method, -1);
            sql = "select payment_id from payment where bill_id = -1;";
            ResultSet rs = stmt.executeQuery(sql);
            rs.next();
            int payment_id=rs.getInt("payment_id");
            System.out.println(payment_id);
            sql = "insert into bill(customer_id,payment_id,bill_amount) values ("+customer_id+","+payment_id+",0);";
            stmt.executeUpdate(sql);
            sql = "select bill_id from bill where payment_id = "+payment_id+";";
            rs = stmt.executeQuery(sql);
            rs.next();
            int bill_id=rs.getInt("bill_id");
            sql = "update payment set bill_id="+bill_id+" where payment_id= "+payment_id+";";
            stmt.executeUpdate(sql); 
        } catch (Exception e) {
            e.getStackTrace();
        }
    }
    public static void add_purchase_to_bill(Statement stmt,int amount,int bill_id)
    {
        try 
        {
            String sql;
            sql = "select bill_amount from bill where bill_id = "+bill_id+";";
            ResultSet rs= stmt.executeQuery(sql);
            rs.next();
            int amt=rs.getInt("bill_amount");

            sql = "update bill set bill_amount = " +(amount+amt) +"where bill_id = " + bill_id+";";
            stmt.executeUpdate(sql);
        }
        catch (Exception e) 
        {
            e.getStackTrace();
        }
    }
    public static void remove_purchase_from_bill(Statement stmt,int amount,int bill_id)
    {
        try 
        {
            String sql;
            sql = "select bill_amount from bill where bill_id = "+bill_id+";";
            ResultSet rs= stmt.executeQuery(sql);
            rs.next();
            int amt=rs.getInt("bill_amount");

            sql = "update bill set bill_amount = " +(amt-amount) +" where bill_id = " + bill_id+";";
            stmt.executeUpdate(sql);
        }
        catch (Exception e) 
        {
            e.getStackTrace();
        }
    }
    public static void get_bill_amount(Statement stmt,int bill_id)
    {
        try 
        {
            String sql;
            sql="select bill_amount from bill where bill_id= "+bill_id+";";
            ResultSet rs=stmt.executeQuery(sql);
            rs.next();
            int amount = rs.getInt("bill_amount");
            System.out.println("Bill amount = "+amount);
            
        } 
        catch (Exception e) 
        {
            e.getStackTrace();
        }
    }
    public static void get_amount_spent(Statement stmt,int customer_id)
    {
        try 
        {
           String sql;
           sql ="select sum(bill_amount) as sum from bill where customer_id = "+customer_id+";";
           ResultSet rs = stmt.executeQuery(sql);
           rs.next();
           int amount = rs.getInt("sum");
           System.out.println("total anount spent by "+customer_id +" is "+ amount); 
        } 
        catch (Exception e) 
        {
            e.getStackTrace();
        }
    }
    public static void getBill(Statement stmt,int bill_id)
    {
        try {
            String sql;
            sql = "select product_id ,quantity from purchase where bill_id = "+bill_id+";";
            ResultSet rs=stmt.executeQuery(sql);
            System.out.println("product name , quantity");
            //rs.next();
            while(rs.next())
            {
                int id=rs.getInt("product_id");
                int quant = rs.getInt("quantity");
                sql = "select product_name from product where product_id=" +id+";";
                ResultSet temp = stmt.executeQuery(sql);
                temp.next();
                String s= temp.getString("product_name");
                System.out.println(s+" "+quant);
            }
            rs.close();

        } catch (Exception e) {
            e.getStackTrace();
        }
    }
}
