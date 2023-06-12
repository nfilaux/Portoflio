package modele;

import java.util.ArrayList;
import presentation.*;

public class AccesDonnees {
	static private ArrayList<Chambre> 	lesChambres 	= new ArrayList<Chambre>();
	static private ArrayList<Categorie> lesCategories	= new ArrayList<Categorie>();

	static public void connexion() { 
		lesCategories.add(new Categorie("Chambre économique", "Douche", "Vue sur rue"));
		lesCategories.add(new Categorie("Chambre standard", "Baignoire", "Vue sur rue"));
		lesCategories.add(new Categorie("Chambre supérieure", "Baignoire", "Vue sur jardin"));
		lesCategories.add(new Categorie("Petite suite", "Douche", "Vue sur jardin"));
		lesCategories.add(new Categorie("Suite supérieure", "Baignoire", "Vue sur jardin"));
		
		lesChambres.add(new Chambre(201, 5, 99.99, lesCategories.get(0)));
	}

	// méthodes de consultation : elles fournissent des listes de données
	static public ArrayList<Chambre> getLesChambres() {
		return lesChambres;
	}
	
	

	static public ArrayList<Categorie> getLesCategorie() {
		return lesCategories;
	}
	
	// méthodes de mise à jour
	static public void ajouterChambre(Chambre e) {
		lesChambres.add(e);
	}
	static public void supprimerChambre(Chambre e) {
		boolean trouve = false;
		int i=0;
		while (!trouve && i<lesChambres.size()) {
			if (lesChambres.get(i).getNum()==e.getNum()){
				lesChambres.remove(i);
				trouve = true;
			}
			i++;
		}
	}
	static public void modifierChambre(Chambre e) {
		boolean trouve = false;
		int i=0;
		while (!trouve && i<lesChambres.size()) {
			if (lesChambres.get(i).getNum()==e.getNum()){
				lesChambres.set(i, e);
				trouve = true;
			}
			i++;
		}
	}
}
