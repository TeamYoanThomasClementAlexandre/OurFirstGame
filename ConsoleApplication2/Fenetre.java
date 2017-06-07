import java.awt.Color;
import javax.swing.*;
import java.awt.*;
import javax.swing.ImageIcon;

public class Fenetre extends JFrame{
	public Fenetre(){
		super("Age of Strategies");
		this.setSize(800,500);
		this.setLocationRelativeTo(null);
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        JPanel panel = new JPanel(new GridBagLayout());
        GridBagConstraints c = new GridBagConstraints();

        Color color = new Color(255,255,255);//57,131,188
        panel.setBackground(color); 
        this.setContentPane(panel);
        this.setVisible(true); 
        
        Font fonte = new Font("Arial",Font.BOLD,16);
        Font fonte2 = new Font("Arial",Font.BOLD,30);

        JLabel titre = new JLabel("Age of strategies");
        titre.setFont(fonte2);
		c.weightx = 1;
		c.weighty = 1;
		c.gridheight = 1;
		c.gridx = 1;
		c.gridy = 0;
 		panel.add(titre, c);

 		JLabel ndc = new JLabel("Nom de compte");
 		ndc.setFont(fonte);
		c.weightx = 1;
		c.weighty = 1;
		c.gridx = 0;
		c.gridy = 1;
		panel.add(ndc, c);
		
		JTextField ndctxt = new JTextField("");
		ndctxt.setPreferredSize(new Dimension(100,20));
		ndctxt.setFont(fonte);
		c.weightx = 1;
		c.weighty = 1;
		c.gridx = 0;
		c.gridy = 2;
		panel.add(ndctxt, c);

		JLabel mdp = new JLabel("Mot de passe");
		mdp.setFont(fonte);
		c.weightx = 1;
		c.weighty = 1;
		c.gridx = 0;
		c.gridy = 3;
		panel.add(mdp, c);
		
		JPasswordField mdptxt = new JPasswordField("");
		mdptxt.setPreferredSize(new Dimension(100,20));
		mdptxt.setFont(fonte);
		c.weightx = 1;
		c.weighty = 1;
		c.gridx = 0;
		c.gridy = 4;
		panel.add(mdptxt, c);
		
		JButton launch = new JButton("Launch");
		c.weightx = 1;
		c.weighty = 1;
		c.gridx = 0;
		c.gridy = 5;
		Observateur obs = new Observateur(ndctxt, mdptxt);
		launch.addActionListener(obs);
		panel.add(launch, c);
		
		ImageIcon guerrier = new ImageIcon("C:\\guerrier.png");
		ImageIcon guerrier2 = new ImageIcon(guerrier.getImage().getScaledInstance(350, 350, Image.SCALE_DEFAULT));
        JLabel test = new JLabel();
        test.setIcon(guerrier2);
        c.weightx = 1;
        c.weighty = 1;
        c.gridheight = 4;
		c.gridx = 1;
		c.gridy = 2;
		panel.add(test, c);
		test.repaint();
		
		
	}
}