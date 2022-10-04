import java.sql.*;
public class Purchase {
    public static void add_purchase(Statement stmt,int bill_id,int product_id,int quantity)
    {
        try 
        {
            String sql;
            sql = "select quantity_left from product where product_id = "+product_id+";";
            ResultSet rs= stmt.executeQuery(sql);
            rs.next();
            int quant = rs.getInt("quantity_left");
            if(quant>=quantity)
            {
                sql = "insert into purchase(bill_id,product_id,quantity) values ("+bill_id+","+product_id+","+quantity+");";
                stmt.executeUpdate(sql);
                Product.decrease_product_quantity(stmt, product_id, quantity);
                int amount = Product.get_product_price(stmt, product_id)*quantity;
                
                bill.add_purchase_to_bill(stmt, amount, bill_id);
                rs.close();
            }
            else
            {
                System.out.println("Not enough quantity available");
                rs.close();
                return;
            }
        } 
        catch (Exception e) 
        {
            e.printStackTrace();
        }
    }
    public static void remove_purchase(Statement stmt,int purchase_id)
    {
        try 
        {
            String sql;
            sql = "select bill_id,product_id,quantity from purchase where purchase_id= "+purchase_id+";";
            ResultSet rs= stmt.executeQuery(sql);
            rs.next();
            int bill_id = rs.getInt("bill_id");
            int product_id = rs.getInt("product_id");
            int quant = rs.getInt("quantity");
            sql  = "select price from product where product_id = "+ product_id+";";
            rs= stmt.executeQuery(sql);
            rs.next();
            int price = rs.getInt("price");
             bill.remove_purchase_from_bill(stmt, price*quant, bill_id);
            sql = "delete from purchase where purchase_id = "+ purchase_id+";";
            stmt.executeUpdate(sql); 
            Product.add_product_quantity(stmt, product_id, quant);
            
        } catch (Exception e) 
        {
            e.getStackTrace();
        }
    }
}
