import javax.swing.*;
import java.awt.*;

public class Main extends JFrame{
	public static void main(String[]args){
		Fenetre f = new Fenetre();
		ObservateurWindow obs = new ObservateurWindow();
		f.addWindowListener(obs);
		f.setVisible(true);
	}
}