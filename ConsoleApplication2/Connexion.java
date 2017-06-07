import java.awt.Component;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

import javax.swing.JOptionPane;

public class Connexion {
	public void connexion(){
		try{
			Class.forName("org.mariadb.jdbc.Driver");
			System.out.println("Connexion réussie");
		}
		catch(ClassNotFoundException e){
			System.out.println("fail1");
		}
	}
	
	public void verification(String nomCompte, String motPasse, String hashed){
		File file = new File("testFileWriter.txt");
	    FileWriter fw;
		
		try{
			Connection con=DriverManager.getConnection("jdbc:mariadb://dwarves.iut-fbleau.fr/barbier","barbier","barbier");
			try{
				Statement stmt=con.createStatement();
				try{
					ResultSet rsPass=stmt.executeQuery("SELECT mdp FROM compte where login='"+nomCompte+"'");
					if(rsPass.next()){
						//while(rsPass.next()){
							if (rsPass.getString("mdp").equals(hashed)){
							    System.out.println("It matches");
							    try{
							    	fw = new FileWriter(file);
							    	fw.write(nomCompte);
							    	fw.close();
							    	java.lang.System.exit(0);
							    }catch(IOException e){
							    }
							}
							else
							    System.out.println("It does not match");
							Component frame = null;
							JOptionPane.showMessageDialog(frame, "Mot de passe erronné.");
						//}
						ResultSet rs1=stmt.executeQuery("SELECT login,mdp FROM compte where login='"+nomCompte+"' and mdp='"+motPasse+"'");
						rs1.close();
					}else{
						Component frame = null;
						JOptionPane.showMessageDialog(frame,
						    "Nom de compte inconnu.");
					}
				}
				catch(SQLException e){
					//System.out.println(e.getMessage());
					//System.out.println(e.getSQLState());
					//System.out.println(e.getErrorCode());
				}
				
			}
			catch(SQLException e){
			}
		}
		catch(SQLException e){
		}
	}
}
