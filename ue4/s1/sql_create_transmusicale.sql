DROP SCHEMA if exists transmusicales CASCADE;
CREATE SCHEMA transmusicales;
SET SCHEMA 'transmusicales';
CREATE TABLE _annee 
(
  an   NUMERIC(4) PRIMARY KEY
);
CREATE TABLE _pays 
(
  nom_p   VARCHAR(30) PRIMARY KEY
);
CREATE TABLE _ville 
(
  nom_v   VARCHAR(30) PRIMARY KEY,
  nom_p   VARCHAR(30) NOT NULL,
  CONSTRAINT ville_fk_pays FOREIGN KEY (nom_p) REFERENCES _pays (nom_p)
);
CREATE TABLE _lieu 
(
  id_lieu        VARCHAR(10) PRIMARY KEY,
  nom_lieu       VARCHAR(30) NOT NULL,
  accespmr       BOOLEAN NOT NULL,
  capacite_max   NUMERIC(5) NOT NULL,
  type_lieu      VARCHAR(20) NOT NULL,
  nom_v          VARCHAR(30) NOT NULL,
  CONSTRAINT lieu_fk_ville FOREIGN KEY (nom_v) REFERENCES _ville (nom_v)
);
CREATE TABLE _formation 
(
  libelle_formation   VARCHAR(20) PRIMARY KEY
);
CREATE TABLE _type_musique 
(
  type_m   VARCHAR(20) PRIMARY KEY
);
CREATE TABLE _edition 
(
  nom_edition   VARCHAR(30) PRIMARY KEY,
  an            NUMERIC NOT NULL,
  CONSTRAINT edition_fk_annee FOREIGN KEY (an) REFERENCES _annee (an)
);
CREATE TABLE _concert 
(
  no_concert    VARCHAR(10) PRIMARY KEY,
  titre         VARCHAR(20) NOT NULL,
  resume_c      VARCHAR(100) NOT NULL,
  duree         NUMERIC(3) NOT NULL,
  tarif         FLOAT(5) NOT NULL,
  type_m        VARCHAR(20) NOT NULL,
  nom_edition   VARCHAR(30) NOT NULL,
  CONSTRAINT concert_fk_type_musique FOREIGN KEY (type_m) REFERENCES _type_musique (type_m),
  CONSTRAINT concert_fk_edition FOREIGN KEY (nom_edition) REFERENCES _edition (nom_edition)
);
CREATE TABLE _groupe_artiste 
(
  id_groupe_artiste     VARCHAR(10) PRIMARY KEY,
  nom_groupe_artiste    VARCHAR(20) NOT NULL,
  site_web              VARCHAR(50) NOT NULL,
  debut                 NUMERIC(4) NOT NULL,
  sortie_discographie   NUMERIC(4) NOT NULL,
  nom_p                 VARCHAR(30) NOT NULL,
  CONSTRAINT groupe_artiste_fk_annee_debut FOREIGN KEY (debut) REFERENCES _annee (an),
  CONSTRAINT groupe_artiste_fk_annee_sortie FOREIGN KEY (sortie_discographie) REFERENCES _annee (an),
  CONSTRAINT groupe_artiste_fk_pays FOREIGN KEY (nom_p) REFERENCES _pays (nom_p)
);
CREATE TABLE _type_ponctuel 
(
  id_groupe_artiste   VARCHAR(10) NOT NULL,
  type_m              VARCHAR(20) NOT NULL,
  CONSTRAINT type_ponctuel_fk_groupe_artiste FOREIGN KEY (id_groupe_artiste) REFERENCES _groupe_artiste (id_groupe_artiste),
  CONSTRAINT type_ponctuel_fk_type_musique FOREIGN KEY (type_m) REFERENCES _type_musique (type_m),
  CONSTRAINT type_ponctuel_pk PRIMARY KEY (id_groupe_artiste,type_m)
);
CREATE TABLE _type_principal 
(
  id_groupe_artiste   VARCHAR(10) NOT NULL,
  type_m              VARCHAR(20) NOT NULL,
  CONSTRAINT type_principal_fk_groupe_artiste FOREIGN KEY (id_groupe_artiste) REFERENCES _groupe_artiste (id_groupe_artiste),
  CONSTRAINT type_principal_fk_type_musique FOREIGN KEY (type_m) REFERENCES _type_musique (type_m),
  CONSTRAINT type_principal_pk PRIMARY KEY (id_groupe_artiste,type_m)
);
CREATE TABLE _a_pour 
(
  id_groupe_artiste   VARCHAR(10) NOT NULL,
  libelle_formation   VARCHAR(20) NOT NULL,
  CONSTRAINT a_pour_fk_groupe_artiste FOREIGN KEY (id_groupe_artiste) REFERENCES _groupe_artiste (id_groupe_artiste),
  CONSTRAINT a_pour_fk_formation FOREIGN KEY (libelle_formation) REFERENCES _formation (libelle_formation),
  CONSTRAINT a_pour_pk PRIMARY KEY (id_groupe_artiste,libelle_formation)
);
COMMIT;
