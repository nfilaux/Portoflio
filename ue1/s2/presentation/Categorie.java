package presentation;

import javafx.beans.property.*;

public class Categorie {
    private StringProperty nom;
    private StringProperty salleEau;
    private StringProperty vue;

    public Categorie(String nom, String salleEau, String vue) {
        this.nom = new SimpleStringProperty(nom);
        this.salleEau = new SimpleStringProperty(salleEau);
        this.vue = new SimpleStringProperty(vue);
    }

    public String getNom() {
        return nom.get();
    }

    public StringProperty nomProperty() {
        return nom;
    }

    public void setNom(String nom) {
        this.nom.set(nom);
    }

    public String getSalleEau() {
        return salleEau.get();
    }

    public StringProperty salleEauProperty() {
        return salleEau;
    }

    public void setSalleEau(String salleEau) {
        this.salleEau.set(salleEau);
    }

    public String getVue() {
        return vue.get();
    }

    public StringProperty vueProperty() {
        return vue;
    }

    public void setVue(String vue) {
        this.vue.set(vue);
    }

    public boolean salleEauValide(String s) {
        boolean valide = true;
        if (s == null) {
            valide = false;
        }
        return valide;
    }

    public boolean vueValide(String v) {
        boolean valide = true;
        if (v == null) {
            valide = false;
        }
        return valide;
    }

    public boolean nomValide(String n) {
        boolean valide = true;
        if (n == null) {
            valide = false;
        }
        return valide;
    }

	@Override
	public String toString() {
		return this.getNom();
	}
    
    
}