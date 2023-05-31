DROP SCHEMA if exists parcoursup CASCADE;
CREATE SCHEMA parcoursup;
SET SCHEMA 'parcoursup';
COMMIT;
CREATE TABLE _filiere 
(
  filiere_id                     NUMERIC(5) NOT NULL,
  filiere_libelle                VARCHAR(279) NOT NULL,
  filiere_libelle_tres_abrege    VARCHAR(17) NOT NULL,
  filiere_libelle_abrege         VARCHAR(66) NOT NULL,
  filiere_libelle_detaille_bis   VARCHAR(119) NOT NULL,
  CONSTRAINT filiere_pk PRIMARY KEY (filiere_id)
);
CREATE TABLE _academie 
(
  academie_nom   VARCHAR(19) NOT NULL,
  CONSTRAINT academie_pk PRIMARY KEY (academie_nom)
);
CREATE TABLE _etablissement 
(
  etablissement_code_uai   VARCHAR(8) NOT NULL,
  etablissement_nom        VARCHAR(134) NOT NULL,
  etablissement_statut     VARCHAR(32) NOT NULL,
  CONSTRAINT etablissement_pk PRIMARY KEY (etablissement_code_uai)
);
CREATE TABLE _regroupement 
(
  libelle_regroupement   VARCHAR(39) NOT NULL,
  CONSTRAINT regroupement_pk PRIMARY KEY (libelle_regroupement)
);
CREATE TABLE _session 
(
  session_annee   NUMERIC(4) NOT NULL,
  CONSTRAINT session_pk PRIMARY KEY (session_annee)
);
CREATE TABLE _mention_bac 
(
  libelle_mention   VARCHAR(36) NOT NULL,
  CONSTRAINT mention_bac_pk PRIMARY KEY (libelle_mention)
);
CREATE TABLE _type_bac 
(
  type_bac   VARCHAR(17) NOT NULL,
  CONSTRAINT type_bac_pk PRIMARY KEY (type_bac)
);
CREATE TABLE _region 
(
  region_nom   VARCHAR(26) NOT NULL,
  CONSTRAINT region_pk PRIMARY KEY (region_nom)
);
CREATE TABLE _departement 
(
  departement_code   VARCHAR(3) NOT NULL,
  departement_nom    VARCHAR(23) NOT NULL,
  region_nom         VARCHAR(26) NOT NULL,
  CONSTRAINT departement_pk PRIMARY KEY (departement_code),
  CONSTRAINT departement_fk_region FOREIGN KEY (region_nom) REFERENCES _region (region_nom)
);
CREATE TABLE _commune 
(
  commune_nom        VARCHAR(29) NOT NULL,
  departement_code   VARCHAR(3) NOT NULL,
  CONSTRAINT commune_pk PRIMARY KEY (commune_nom,departement_code),
  CONSTRAINT commune_fk_departement FOREIGN KEY (departement_code) REFERENCES _departement (departement_code)
);
CREATE TABLE _formation 
(
  cod_aff_form                      VARCHAR(5) NOT NULL,
  filiere_libelle_detaille          VARCHAR(335) NOT NULL,
  coordonnees_gps                   VARCHAR(21) NOT NULL,
  list_com                          VARCHAR(44) NOT NULL,
  concours_communs_banque_epreuve   VARCHAR(98),
  url_formation                     VARCHAR(91),
  tri                               VARCHAR(19) NOT NULL,
  filiere_id                        NUMERIC(5) NOT NULL,
  academie_nom                      VARCHAR(19) NOT NULL,
  etablissement_code_uai            VARCHAR(8) NOT NULL,
  commune_nom                       VARCHAR(29) NOT NULL,
  departement_code                  VARCHAR(3) NOT NULL,
  CONSTRAINT formation_pk PRIMARY KEY (cod_aff_form),
  CONSTRAINT formation_fk_filiere FOREIGN KEY (filiere_id) REFERENCES _filiere (filiere_id),
  CONSTRAINT formation_fk_academie FOREIGN KEY (academie_nom) REFERENCES _academie (academie_nom),
  CONSTRAINT formation_fk_etablissement FOREIGN KEY (etablissement_code_uai) REFERENCES _etablissement (etablissement_code_uai),
  CONSTRAINT formation_fk_commune FOREIGN KEY (commune_nom,departement_code) REFERENCES _commune (commune_nom,departement_code)
);
CREATE TABLE _rang_dernier_appele_selon_regroupement 
(
  cod_aff_form           VARCHAR(5) NOT NULL,
  libelle_regroupement   VARCHAR(39) NOT NULL,
  session_annee          NUMERIC(4) NOT NULL,
  rang_dernier_appele    NUMERIC(5),
  CONSTRAINT rang_dernier_appele_selon_regroupement_pk PRIMARY KEY (cod_aff_form,libelle_regroupement,session_annee),
  CONSTRAINT rang_dernier_appele_selon_regroupement_fk_formation FOREIGN KEY (cod_aff_form) REFERENCES _formation (cod_aff_form),
  CONSTRAINT rang_dernier_appele_selon_regroupement_fk_regroupement FOREIGN KEY (libelle_regroupement) REFERENCES _regroupement (libelle_regroupement),
  CONSTRAINT rang_dernier_appele_selon_regroupement_fk_session FOREIGN KEY (session_annee) REFERENCES _session (session_annee)
);
CREATE TABLE _admissions_generalites 
(
  cod_aff_form                VARCHAR(5) NOT NULL,
  session_annee               NUMERIC(4) NOT NULL,
  selectivite                 VARCHAR(23) NOT NULL,
  capacite                    NUMERIC(4) NOT NULL,
  effectif_total_candidats    NUMERIC(5) NOT NULL,
  effectif_total_candidates   NUMERIC(5) NOT NULL,
  CONSTRAINT admissions_generalites_pk PRIMARY KEY (cod_aff_form,session_annee),
  CONSTRAINT _admissions_generalites_fk_formation FOREIGN KEY (cod_aff_form) REFERENCES _formation (cod_aff_form),
  CONSTRAINT _admissions_generalites_fk_session FOREIGN KEY (session_annee) REFERENCES _session (session_annee)
);
CREATE TABLE _effectif_selon_mention 
(
  cod_aff_form                           VARCHAR(5) NOT NULL,
  session_annee                          NUMERIC(4) NOT NULL,
  libelle_mention                        VARCHAR(36) NOT NULL,
  effectif_admis_neo_bac_selon_mention   NUMERIC(3) NOT NULL,
  CONSTRAINT effectif_selon_mention_pk PRIMARY KEY (cod_aff_form,session_annee,libelle_mention),
  CONSTRAINT _effectif_selon_mention_fk_formation FOREIGN KEY (cod_aff_form) REFERENCES _formation (cod_aff_form),
  CONSTRAINT _effectif_selon_mention_fk_session FOREIGN KEY (session_annee) REFERENCES _session (session_annee),
  CONSTRAINT _effectif_selon_mention_fk_mention_bac FOREIGN KEY (libelle_mention) REFERENCES _mention_bac (libelle_mention)
);
CREATE TABLE _admissions_selon_type_neo_bac 
(
  cod_aff_form                        VARCHAR(5) NOT NULL,
  session_annee                       NUMERIC(4) NOT NULL,
  type_bac                            VARCHAR(17) NOT NULL,
  effectif_candidat_neo_bac_classes   NUMERIC(5) NOT NULL,
  CONSTRAINT _admissions_selon_type_neo_bacn_pk PRIMARY KEY (cod_aff_form,session_annee,type_bac),
  CONSTRAINT _admissions_selon_type_neo_bac_fk_formation FOREIGN KEY (cod_aff_form) REFERENCES _formation (cod_aff_form),
  CONSTRAINT _admissions_selon_type_neo_bac_fk_session FOREIGN KEY (session_annee) REFERENCES _session (session_annee),
  CONSTRAINT _admissions_selon_type_neo_bac_fk_type_bac FOREIGN KEY (type_bac) REFERENCES _type_bac (type_bac)
);
