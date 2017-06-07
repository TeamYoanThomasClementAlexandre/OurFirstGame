import java.awt.event.*;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

import javax.swing.JFrame;

public class ObservateurWindow extends JFrame implements WindowListener,
                                            WindowFocusListener,
                                            WindowStateListener {

	@Override
	public void windowStateChanged(WindowEvent e) {
		
	}

	@Override
	public void windowGainedFocus(WindowEvent arg0) {
		
	}

	@Override
	public void windowLostFocus(WindowEvent arg0) {
		
	}

	@Override
	public void windowActivated(WindowEvent arg0) {
		
	}

	@Override
	public void windowClosed(WindowEvent arg0) {
		
	}

	@Override
	public void windowClosing(WindowEvent arg0) {
		File file = new File("testFileWriter.txt");
	    FileWriter fw = null;
	    
		try {
			fw = new FileWriter(file);
		} catch (IOException e) {
			e.printStackTrace();
		}
    	try {
			fw.write("null");
		} catch (IOException e) {
			e.printStackTrace();
		}
    	try {
			fw.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	@Override
	public void windowDeactivated(WindowEvent arg0) {
		
	}

	@Override
	public void windowDeiconified(WindowEvent arg0) {
		
	}

	@Override
	public void windowIconified(WindowEvent arg0) {
		
	}

	@Override
	public void windowOpened(WindowEvent arg0) {
		
	}
	
}