import java.sql.*;
public class Product {

    public static void add_product(Statement stmt,String product_name,int product_company_id,int quantity,int price)
    {
        try {
            String sql;
            sql="insert into product(product_name,product_company_id,quantity_left,price) values ( "+"'"+product_name+"',"+product_company_id+","+quantity+","+price+");";
            stmt.executeUpdate(sql); 
            
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
    public static void remove_product(Statement stmt,int product_id)
    {
        try {
            String sql;
            sql = "delete from product where product_id="+product_id+";";
            stmt.executeUpdate(sql);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
    public static void decrease_product_quantity(Statement stmt,int product_id,int quantity)
    {
        try 
        {
            String sql;
            sql = "select quantity_left from product where product_id = "+product_id+" ;";
            ResultSet rs=stmt.executeQuery(sql);
            rs.next();
            int quant=rs.getInt("quantity_left");
            //System.out.println(quant);
            sql = "update product set quantity_left = "+(quant- quantity)+" where product_id=" +product_id+" ;";
            //System.out.println(sql);
            stmt.executeUpdate(sql);
            rs.close();
        } 
        catch (Exception e) 
        {
            e.printStackTrace();
        }
    }
    public static void add_product_quantity(Statement stmt,int product_id,int quantity)
    {
        try 
        {
            String sql;
            sql = "select quantity_left from product where product_id = "+product_id +";";
            ResultSet rs=stmt.executeQuery(sql);
            rs.next();
            int quant=rs.getInt("quantity_left");
            sql = "update product set quantity_left = "+(quant+ quantity)+" where product_id=" +product_id+" ;";
            stmt.executeUpdate(sql);
            rs.close();
        } 
        catch (Exception e) 
        {
            e.printStackTrace();
        }
    }
    public static void change_product_price(Statement stmt,int product_id,int price)
    {
        try 
        {
            String sql;
            sql = "update product set price = "+price+" where product_id= "+product_id+" ;";
            stmt.executeUpdate(sql); 
        } 
        catch (Exception e) 
        {
            e.printStackTrace();
        }
    }
    public static int get_product_price(Statement stmt,int product_id)
    {
        try {
            String sql;
            sql= "select price from product where product_id = "+product_id +";";
            ResultSet rs=stmt.executeQuery(sql);
            rs.next();
            int price = rs.getInt("price");
            rs.close();
            return price;

        } catch (Exception e) {
            e.getStackTrace();
        }
        return 0;
    }
    public static void get_available_products(Statement stmt)
    {
        try {
            String sql;
            sql = "select product_name from product where quantity_left>0 ;";
            ResultSet rs = stmt.executeQuery(sql);
            while(rs.next())
            {
                System.out.println(rs.getString("product_name"));
            }
            rs.close();
        } catch (Exception e) {
            e.getStackTrace();
        }
    }

}
