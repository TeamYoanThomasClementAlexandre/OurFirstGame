import java.awt.event.*;
import javax.swing.*;

public class Observateur implements ActionListener{
	private JTextField ndc;
	private JPasswordField mdp;
	private static int workload = 10;
	
	public Observateur(JTextField ndctxt, JPasswordField mdptxt){
		this.ndc = ndctxt;
		this.mdp = mdptxt;
	}
	
	public static String hashPassword(String password_plaintext) {
		String salt = BCrypt.gensalt(workload);
		String hashed_password = BCrypt.hashpw(password_plaintext, salt);
		return(hashed_password);
	}
	
	public void actionPerformed(ActionEvent e){
		
		String monmdp = new String(mdp.getPassword());				
		
		String nomCompte = ndc.getText();
		String mdp = hashPassword(monmdp);
		
		Connexion con = new Connexion();
		con.verification(nomCompte, monmdp, mdp);
	}
}