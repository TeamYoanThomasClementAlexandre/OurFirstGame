import java.util.*;

public class Freq<T>{
	private T[] elem;

	public Freq(T[] elem0){
		this.elem=elem0;
	}

	public T getValeur(){
		int compteur=0;
		int grosCompteur=0;
		int indice=0;
		int n;
		int i;
		for(i=elem.length-1;i>0;i--){
			for(n=0;n<elem.length;n++){
				if(elem[i].equals(elem[n])){
					compteur++;
				}
			}
			if(compteur>=grosCompteur){
				grosCompteur=compteur;
				indice=i;
			}
			compteur=0;
		}
		return elem[indice];	
	}


	public static void main(String[] args) {
		int i=1;
		Integer tab[]={1,6,6,6,3,3,4,4,5,5};
		Freq<Integer> test=new Freq<Integer>(tab);
		System.out.println(""+ test.getValeur());
		System.out.print("Clément");	}
}