package presentation;

import javafx.application.Application;
import javafx.stage.Modality;
import javafx.stage.Stage;
import modele.*;
import vue.*;

public class Principale extends Application{
	static private FenNouveauChambre fNouvChambre = new FenNouveauChambre();
	static private FenDetailChambre fDetailChambre = new FenDetailChambre();
	static private FenListeChambres fListeChambre = new FenListeChambres();
	
	public void start(Stage f) throws Exception {
		AccesDonnees.connexion();
		fNouvChambre.initModality(Modality.APPLICATION_MODAL);
		fDetailChambre.initModality(Modality.APPLICATION_MODAL);
		fListeChambre.init(AccesDonnees.getLesCategorie());
		fListeChambre.show();
	} 
	
	static public void main(String[] args) { 
		Application.launch(args); 
	}

	// gestion des fenêtres
	static public void ouvrirNouvelChambre() {
		fNouvChambre.init(AccesDonnees.getLesCategorie());
		fNouvChambre.show();
	}
	
	static public void ouvrirDetailChambre(Chambre c) {
		fDetailChambre.init(AccesDonnees.getLesCategorie() , c);
		fDetailChambre.show();
	}
	
	// gestion des données : les modifications
	static public void ajouterChambre(Chambre e) {
		// actualiser l'ObservableList dans la fenetre liste des chambres
		fListeChambre.ajouterChambre(e);
		// enregistrer l'ajout
		AccesDonnees.ajouterChambre(e);	
	}
	static public void modifierChambre(Chambre e) {
		// actualiser l'ObservableList dans la fenetre liste des chambres
		fListeChambre.modifierChambre(e);
		// enregistrer la modif
		AccesDonnees.modifierChambre(e);	
	}
	static public void supprimerChambre(Chambre e) {
		// actualiser l'ObservableList dans la fenetre liste des chambres
		fListeChambre.supprimerChambre(e);
		// enregistrer la suppression
		AccesDonnees.supprimerChambre(e);
	}

}
