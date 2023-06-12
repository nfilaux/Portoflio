package vue;

import javafx.geometry.Insets;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.control.Alert.AlertType;
import javafx.scene.image.Image;
import javafx.scene.layout.*;
import javafx.scene.paint.Color;
import javafx.stage.Stage;
import presentation.Categorie;
import presentation.Chambre;
import presentation.Principale;

import java.util.ArrayList;

public class FenDetailChambre extends Stage {
	
	// les composants du formulaire
	private GridPane			racine			= new GridPane();
	private HBox				zoneBoutons		= new HBox();
	
	private Label 				lblNum			= new Label("Numéro * :");
	private Label 				lblCategorie	= new Label("Catégorie * :");
	private Label 				lblNMaxNb		= new Label("Nombre max d'occupant * :");
	private Label 				lblPrix			= new Label("Prix * :");
	
	private TextField			txtNum			= new TextField();
	private TextField			txtMaxNb		= new TextField();
	private TextField			txtPrix			= new TextField();
	
	private ComboBox<Categorie>	cbCategorie		= new ComboBox<Categorie>();
	private Button 				bnOK 			= new Button("Enregistrer");
	private Button 				bnAnnuler 		= new Button("Annuler");
	
	// constructeur : initialisation de la fenetre et des données
	public FenDetailChambre(){		
		this.setTitle("Détail chambre");
		this.sizeToScene();
		this.setResizable(false);
		Image icon = new Image(getClass().getResourceAsStream("../Image/icone.png"));
        getIcons().add(icon);
		this.setScene(new Scene(creerContenu()));	
	}
	
	private Parent creerContenu() {
		txtNum.setDisable(true);	// le matricule n'est pas modifiable (c'est un identifiant)
		txtNum.setMaxWidth(164);
		txtMaxNb.setMaxWidth(164);
		txtPrix.setMaxWidth(164);
		bnOK.setPrefWidth(100);
		bnOK.setOnAction(e ->{	
			if(!estEntier(txtMaxNb.textProperty().getValue()) || txtMaxNb.textProperty().getValue().equals("")) {
				Alert alert = new Alert(AlertType.ERROR, 
						"Le nombre d'occupant maximum n'est pas un entier positif !\nVeuillez ressaisir la valeur.",
						ButtonType.OK);
				alert.setTitle("Erreur de format sur max occupant");
				alert.show();
			}
			else if(!estDecimal(txtPrix.textProperty().getValue()) || txtPrix.textProperty().getValue().equals("")) {
				Alert alert = new Alert(AlertType.ERROR, 
						"Le prix n'est pas un réel positif !\nVeuillez ressaisir la valeur.",
						ButtonType.OK);
				alert.setTitle("Erreur de format sur le prix");
				alert.show();
			}
			else {
				int num = Integer.parseInt(txtNum.textProperty().getValue());
				int nbMax = Integer.parseInt(txtMaxNb.textProperty().getValue());
				double prix = Double.parseDouble(txtPrix.textProperty().getValue());
				Categorie cat = cbCategorie.getValue();
			
				Principale.modifierChambre(new Chambre(num, nbMax, prix, cat));
				this.close();
			}
		});
		
		bnAnnuler.setPrefWidth(100);
		bnAnnuler.setOnAction(e ->{
			this.close();
		});
		racine.setStyle("-fx-background-color: #24485C;");
		// construction du Scene Graph
		zoneBoutons.getChildren().addAll(bnOK, bnAnnuler);
		zoneBoutons.setSpacing(10);
		racine.addRow(0,  lblNum, txtNum);
		lblNum.setTextFill(Color.WHITE);
		racine.addRow(1,  lblNMaxNb, txtMaxNb);
		lblNMaxNb.setTextFill(Color.WHITE);
		racine.addRow(2,  lblPrix, txtPrix);
		lblPrix.setTextFill(Color.WHITE);
		racine.addRow(3,  lblCategorie, cbCategorie);
		lblCategorie.setTextFill(Color.WHITE);

		racine.add(zoneBoutons, 1, 10);
		racine.setHgap(10);
		racine.setVgap(15);
		racine.setPadding(new Insets(10));
		return racine;
	}
	
	public void init(ArrayList<Categorie> lesCategories, Chambre c) {
		txtNum.textProperty().setValue(Integer.toString(c.getNum()));
		txtMaxNb.textProperty().setValue(Integer.toString(c.getMax_occupant()));
		txtPrix.textProperty().setValue(Double.toString(c.getPrix()));
		
		this.cbCategorie.getItems().clear();
		for (int i=0; i<lesCategories.size() ; i++) {
			this.cbCategorie.getItems().add(lesCategories.get(i));
		}
		this.cbCategorie.setValue(c.getCategorie());
	}
	
	private boolean estDecimal(String str) {
		return str.matches("\\d*(\\.\\d+)?");
	}
	
	private boolean estEntier(String str) {
		return str.matches("\\d*");
	}
}
