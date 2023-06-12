package vue;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;

import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.util.ArrayList;
import java.util.Optional;

import javafx.beans.binding.Bindings;
import javafx.beans.binding.BooleanBinding;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.control.Alert.AlertType;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.image.Image;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Stage;
import presentation.*;

public class FenListeChambres extends Stage {
	static private ObservableList<Chambre> lesChambres = FXCollections.observableArrayList();
	// les composants de la fenetre
	private AnchorPane  		racine			= new AnchorPane();
	private TableView<Chambre> 	tableChambres	= new TableView<Chambre>();
	private Button 				bnAjouter 		= new Button("Ajouter");
	private Button 				bnModifier 		= new Button("Modifier");
	private Button 				bnSupprimer 	= new Button("Supprimer");
	private Button 				bnFermer 		= new Button("Fermer");
	
	// constructeur : initialisation de la fenetre
	public FenListeChambres(){
		this.setOnCloseRequest(e ->{
			sauvegarderListeChambres();
		});
		this.setTitle("Cheval Blanc - Gestion des chambres");
		this.setWidth(665);
		this.setMinWidth(500);
		this.setMinHeight(250);
		this.setResizable(true);
		Image icon = new Image(getClass().getResourceAsStream("../Image/icone.png"));
        getIcons().add(icon);
		this.setScene(new Scene(creerContenu()));	
	}
	
	// creation du Scene graph
	private Parent creerContenu() {
			
		TableColumn<Chambre,Integer> colonne1 = new TableColumn<Chambre,Integer>("Numéro");
		colonne1.setCellValueFactory(new PropertyValueFactory<Chambre,Integer>("num"));	
		tableChambres.getColumns().add(colonne1);
		TableColumn<Chambre,Integer> colonne2 = new TableColumn<Chambre,Integer>("Max clients");
		colonne2.setCellValueFactory(new PropertyValueFactory<Chambre,Integer>("max_occupant"));	
		tableChambres.getColumns().add(colonne2);
		TableColumn<Chambre,Double> colonne3 = new TableColumn<Chambre,Double>("Prix de base");
		colonne3.setCellValueFactory(new PropertyValueFactory<Chambre,Double>("prix"));	
		tableChambres.getColumns().add(colonne3);
		TableColumn<Chambre, String> colonne4 = new TableColumn<Chambre,String>("Catégorie");
		colonne4.setCellValueFactory(new PropertyValueFactory<Chambre, String>("categorie"));
		tableChambres.getColumns().add(colonne4);
		
		TableColumn<Chambre, String> colonne5 = new TableColumn<Chambre,String>("Salle d'eau");
		colonne5.setCellValueFactory(cellData -> cellData.getValue().getCategorie().salleEauProperty());
		tableChambres.getColumns().add(colonne5);
		TableColumn<Chambre,String> colonne6 = new TableColumn<Chambre,String>("Vue");
		colonne6.setCellValueFactory(cellData -> cellData.getValue().getCategorie().vueProperty());
		tableChambres.getColumns().add(colonne6);
				
		tableChambres.getSelectionModel().setSelectionMode(SelectionMode.SINGLE);
		
		BooleanBinding rien = Bindings.equal(tableChambres.getSelectionModel().selectedIndexProperty(), -1);
		
		bnAjouter.setPrefWidth(100);
		bnAjouter.setOnAction(e ->{
			Principale.ouvrirNouvelChambre();
			});
		
		
		bnModifier.setPrefWidth(100);
		
		bnModifier.disableProperty().bind(
				Bindings.when(rien).then(true).otherwise(false));
		
		bnModifier.setOnAction(e -> {
			Principale.ouvrirDetailChambre(tableChambres.getSelectionModel().getSelectedItem());
		});
		
		bnSupprimer.setPrefWidth(100);
		
		bnSupprimer.disableProperty().bind(
				Bindings.when(rien).then(true).otherwise(false));
		
		Alert alert = new Alert(AlertType.CONFIRMATION, 
				"Vouler-vous vraiment supprimer cette chambre ?",
				ButtonType.YES,
				ButtonType.NO);
		alert.setTitle("Suppression d'une chambre");
		
		bnSupprimer.setOnAction(e -> {
			Optional<ButtonType> result = alert.showAndWait();
			if(result.isPresent() && result.get() == ButtonType.YES) {
				Principale.supprimerChambre(tableChambres.getSelectionModel().getSelectedItem());
			}
		});
		
		
		bnFermer.setPrefWidth(100);
		bnFermer.setOnAction(e -> {
			sauvegarderListeChambres();
			System.exit(0);
		});
		
		racine.setStyle("-fx-background-color: #24485C;");
		AnchorPane.setTopAnchor(tableChambres, 10.0);
		AnchorPane.setLeftAnchor(tableChambres, 10.0);
		AnchorPane.setRightAnchor(tableChambres, 120.0);
		AnchorPane.setBottomAnchor(tableChambres, 10.0);
		AnchorPane.setTopAnchor(bnAjouter, 30.0);
		AnchorPane.setRightAnchor(bnAjouter, 10.0);
		AnchorPane.setTopAnchor(bnModifier, 80.0);
		AnchorPane.setRightAnchor(bnModifier, 10.0);
		AnchorPane.setTopAnchor(bnSupprimer, 130.0);
		AnchorPane.setRightAnchor(bnSupprimer, 10.0);
		AnchorPane.setBottomAnchor(bnFermer, 10.0);
		AnchorPane.setRightAnchor(bnFermer, 10.0);
		racine.getChildren().addAll(tableChambres, bnAjouter, bnModifier, bnSupprimer, bnFermer);
		return racine;
	}
	
	public void init(ArrayList<Categorie> lesCategories) {
		
		try (ObjectInputStream inputStream = new ObjectInputStream(new FileInputStream("lesChambres.save"))) {
	        @SuppressWarnings("unchecked")
			ArrayList<ChambreData> listeChambresData = (ArrayList<ChambreData>) inputStream.readObject();
	        for (ChambreData chambreData : listeChambresData) {
	        	Categorie cat = null;
	        	for(int i=0; i<lesCategories.size(); i++) {
	        		if(chambreData.getCategorie().equals(lesCategories.get(i).getNom())){
	        			cat = lesCategories.get(i);
	        		}
	        	}
	            Chambre chambre = new Chambre(chambreData.getNum(),chambreData.getMax_occupant(),chambreData.getPrix(), cat);
	            lesChambres.add(chambre);
	        }
	        System.out.println("Liste de chambres chargée avec succès.");
	    } catch (IOException | ClassNotFoundException e) {
	    	System.out.println("Erreur lors du chargement de la liste de chambres : " + e.getMessage());;
	    }
		tableChambres.setItems(lesChambres);
	}
	
	
	public void ajouterChambre(Chambre c) {
		if(present(c)) {
			Alert alert = new Alert(AlertType.ERROR, 
					"Cette chambre existe déja !\nCependant vous pouvez la modifier à partir de la liste des chambres.",
					ButtonType.OK);
			alert.setTitle("Chambre déja existante");
			alert.show();
		}
		else {
			lesChambres.add(c);
		}
	}
	
	public void modifierChambre(Chambre c) {
		boolean trouve = false;
		int i=0;
		while (!trouve && i<lesChambres.size()) {
			if (lesChambres.get(i).getNum() == c.getNum()){
				lesChambres.set(i, c);
				trouve = true;
			}
			i++;
		}

	}
	public void supprimerChambre(Chambre c) {
		lesChambres.remove(c);
	}
	
	public boolean present(Chambre c) {
		for(int i=0; i<lesChambres.size(); i++) {
			if(lesChambres.get(i).getNum() == c.getNum()) {
				return true;
			}
		}
		return false;
	}
	
	public void sauvegarderListeChambres() {
	    ArrayList<ChambreData> listeChambresData = new ArrayList<>();
	    for (Chambre chambre : lesChambres) {
	        ChambreData chambreData = new ChambreData(chambre.getNum(), chambre.getMax_occupant(), chambre.getPrix(), chambre.getCategorie().getNom());
	        listeChambresData.add(chambreData);
	    }

	    try (ObjectOutputStream outputStream = new ObjectOutputStream(new FileOutputStream("lesChambres.save"))) {
	        outputStream.writeObject(listeChambresData);
	        System.out.println("Liste de chambres sauvegardée avec succès.");
	    } catch (IOException e) {
	    	System.out.println("Erreur lors du chargement de la liste de chambres : " + e.getMessage());
	    }
	}
}
