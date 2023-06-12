package presentation;

import java.io.Serializable;



public class ChambreData implements Serializable {
	private static final long serialVersionUID = 1L;
	private int num;
	private int max_occupant;
    private double prix;
    private String categorie;

    public ChambreData(int num, int max_occupant, double prix, String categorie) {
		super();
		this.num = num;
		this.max_occupant = max_occupant;
		this.prix = prix;
		this.categorie = categorie;
	}

	public int getNum() {
		return num;
	}

	public void setNum(int num) {
		this.num = num;
	}

	public int getMax_occupant() {
		return max_occupant;
	}

	public void setMax_occupant(int max_occupant) {
		this.max_occupant = max_occupant;
	}

	public double getPrix() {
		return prix;
	}

	public void setPrix(double prix) {
		this.prix = prix;
	}

	public String getCategorie() {
		return categorie;
	}

	public void setCategorie(String categorie) {
		this.categorie = categorie;
	}
}