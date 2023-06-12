package presentation;

import javafx.beans.property.*;

public class Chambre{

	private IntegerProperty num;
    private IntegerProperty max_occupant;
    private DoubleProperty prix;
    private ObjectProperty<Categorie> categorie;

    public Chambre(int num, int max_occupant, double prix, Categorie categorie)  {
        this.num = new SimpleIntegerProperty(num);
        this.max_occupant = new SimpleIntegerProperty(max_occupant);
        this.prix = new SimpleDoubleProperty(prix);
        this.categorie = new SimpleObjectProperty<>(categorie);
    }
    
    
    public void setNum(IntegerProperty num) {
		this.num = num;
	}
	public void setPrix(DoubleProperty prix) {
			this.prix = prix;
		}
	public void setCategorie(ObjectProperty<Categorie> categorie) {
		this.categorie = categorie;
	}
	public void setMax_occupant(IntegerProperty max_occupant) {
			this.max_occupant = max_occupant;
		}
	
	public Double getPrix() {
		return prix.getValue();
	}

	public Categorie getCategorie() {
        return categorie.get();
    }

	public int getMax_occupant() {
		return max_occupant.get();
	}

	public int getNum() {
        return num.get();
    }
}

