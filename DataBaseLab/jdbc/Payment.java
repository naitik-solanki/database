import java.sql.*;
public class Payment {
    public static void create_payment(Statement stmt,String payment_method,int bill_id)
    {
        try {
            String sql;
            sql = "insert into payment(payment_method,bill_id) values (" + "'"+ payment_method+"',"+bill_id +");";
            stmt.executeUpdate(sql);
        } catch (Exception e) {
            e.getStackTrace();
        }
    }
    public static void show_payment_method(Statement stmt,int payment_id)
    {
        try {
            String sql;
            sql = "select payment_method from payment where payment_id="+payment_id+";";
            ResultSet rs=stmt.executeQuery(sql);
            rs.next();
            System.out.println(rs.getString("payment_method"));
            rs.close();
        } catch (Exception e) {
            e.getStackTrace();
        }
    }
}
