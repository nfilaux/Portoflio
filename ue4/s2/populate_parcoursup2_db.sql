SET SCHEMA 'parcoursup2';

-- TABLE temporaire
drop table if exists import_data;
create table import_data(
  session_annee                                                                   numeric(4)    not null,
  etablissement_statut                                                            varchar(40)   not null,
  etablissement_code_uai                                                          varchar(10)   not null, 
  etablissement_nom                                                               varchar(150)  not null,
  departement_code                                                                varchar(3)    not null,
  departement_nom                                                                 varchar(50)   not null, 
  region_nom                                                                      varchar(50)   not null, 
  academie_nom                                                                    varchar(50)   not null, 
  commune_nom                                                                     varchar(50)   not null,
  filiere_libelle                                                                 varchar(400)  not null, 
  selectivite                                                                     varchar(30)   not null, 
  filiere_libelle_tres_abrege                                                     varchar(30)   not null, 
  filiere_libelle_detaille                                                        varchar(400)  not null, 
  filiere_libelle_abrege                                                          varchar(100)  not null,
  filiere_libelle_detaille_bis                                                    varchar(150)  not null,
  filiere_libelle_tres_detaille                                                   varchar(400), -- peut être vide
  coordonnees_gps                                                                 varchar(30)   not null, 
  capacite                                                                        integer       not null, 
  effectif_total_candidats                                                        integer       not null, 
  effectif_total_candidates                                                       integer       not null,
  effectif_candidat_neo_bac_classes_type_general                                  integer       not null, 
  effectif_candidat_neo_bac_classes_type_techno                                   integer       not null, 
  effectif_candidat_neo_bac_classes_type_pro                                      integer       not null,  
  effectif_candidat_classes_type_autres                                           integer       not null,
  effectif_admis_neo_bac_type_general                                             integer       not null, -- effectif_admis_neo_bac type_bac = general
  effectif_admis_neo_bac_type_techno                                              integer       not null, -- effectif_admis_neo_bac type_bac = techno
  effectif_admis_neo_bac_type_pro                                                 integer       not null, -- effectif_admis_neo_bac type_bac = pro
  effectif_admis_neo_bac_type_autres                                              integer       not null, -- effectif_admis_neo_bac type_bac = autres
  effectif_admis_neo_bac_selon_mention_type_mention_sans_info                     integer       not null,
  effectif_admis_neo_bac_selon_mention_type_mention_sans_mention                  integer       not null,
  effectif_admis_neo_bac_selon_mention_type_mention_assez_bien                    integer       not null,
  effectif_admis_neo_bac_selon_mention_type_mention_bien                          integer       not null,
  effectif_admis_neo_bac_selon_mention_type_mention_tres_bien                     integer       not null,
  effectif_admis_neo_bac_selon_mention_type_mention_tres_bien_fel                 integer       not null,
  effectif_admis_neo_bac_avec_mention_type_bac_general                            integer       not null,
  effectif_admis_neo_bac_avec_mention_type_bac_techno                             integer       not null,
  effectif_admis_neo_bac_avec_mention_type_bac_pro                                integer       not null,
  regroupement_1                                                                  varchar(100), 
  rang_dernier_appele_groupe1                                                     integer,
  regroupement_2                                                                  varchar(100), 
  rang_dernier_appele_groupe2                                                     integer,
  regroupement_3                                                                  varchar(100), 
  rang_dernier_appele_groupe3                                                     integer,
  list_com                                                                        varchar(60)   not null, 
  tri                                                                             varchar(20)   not null, 
  cod_aff_form                                                                    varchar(20)   not null,
  concours_communs_banques_epreuves                                               varchar(100),
  url_formation                                                                   varchar(150)
);

-- IMPORT de toutes les données utilisées
WbImport -file=./fr-esr-parcoursup_2022.csv
         -header=true
         -delimiter=';'
         -quoteChar='"' 
         -table=import_data
         -schema=parcoursup2
         -mode=insert
         -filecolumns=session_annee, etablissement_statut, etablissement_code_uai, etablissement_nom,
                      departement_code, departement_nom, region_nom, academie_nom, commune_nom,
                      filiere_libelle, selectivite, filiere_libelle_tres_abrege, filiere_libelle_detaille, 
                      filiere_libelle_abrege, filiere_libelle_detaille_bis, filiere_libelle_tres_detaille, 
                      coordonnees_gps, capacite, effectif_total_candidats, effectif_total_candidates, 
                      effectif_total_phase_principale, effectif_internat_phase_principale, 
                      effectif_neo_bac_general_phase_principale, effectif_neo_bac_general_phase_principale_boursier,
                      effectif_neo_bac_techno_phase_principale, effectif_neo_bac_techno_principale_boursier, 
                      effectif_neo_bac_pro_phase_principale, effectif_neo_bac_pro_phase_principale_boursier,
                      effectif_total_autres_phase_principale, effectif_total_phase_complementaire,
                      effectif_neo_bac_general_phase_complementaire, effectif_neo_bac_techno_phase_complementaire,
                      effectif_neo_bac_pro_phase_complementaire, effectif_total_autres_phase_complementaire,
                      effectif_total_classes_phase_principale, effectif_total_classes_phase_complementaire,
                      effectif_total_classes_internat_cpge, effectif_total_classes_hors_internat_cpge,
                      effectif_candidat_neo_bac_classes_type_general, 
                      effectif_candidat_neo_bac_boursiers_classes_type_general,
                      effectif_candidat_neo_bac_classes_type_techno, 
                      effectif_candidat_neo_bac_boursiers_classes_type_techno,
                      effectif_candidat_neo_bac_classes_type_pro, 
                      effectif_candidat_neo_bac_boursiers_classes_type_pro, effectif_candidat_classes_type_autres,
                      effectif_total_proposition_admission, effectif_total_admis, effectif_total_admises,
                      effectif_total_admis_phase_principale, effectif_total_admis_phase_complementaire,
                      effectif_proposition_admis_ouverture_procedure_principale, effectif_proposition_admis_avant_bac,
                      effectif_proposition_admis_avant_fin_procedure_principale, effectif_admis_en_internat, 
                      effectif_total_admis_boursiers_neo_bac, effectif_total_admis_neo_bac, 
                      effectif_admis_neo_bac_type_general, effectif_admis_neo_bac_type_techno,
                      effectif_admis_neo_bac_type_pro, effectif_admis_neo_bac_type_autres,
                      effectif_admis_neo_bac_selon_mention_type_mention_sans_info,
                      effectif_admis_neo_bac_selon_mention_type_mention_sans_mention,
                      effectif_admis_neo_bac_selon_mention_type_mention_assez_bien,
                      effectif_admis_neo_bac_selon_mention_type_mention_bien,
                      effectif_admis_neo_bac_selon_mention_type_mention_tres_bien,
                      effectif_admis_neo_bac_selon_mention_type_mention_tres_bien_fel,
                      effectif_admis_neo_bac_avec_mention_type_bac_general,
                      effectif_admis_neo_bac_avec_mention_type_bac_techno,
                      effectif_admis_neo_bac_avec_mention_type_bac_pro,
                      effectif_admis_meme_etablissement, effectif_admises_meme_etablissement,
                      effectif_admis_meme_academie, effectif_admis_meme_academis_pcv,
                      pourcent_proposition_admis_ouverture_procedure_principale, pourcent_proposition_avant_bac,
                      pourcent_proposition_admis_avant_fin_procedure_principale, pourcent_admises,
                      pourcent_neo_bac_admis_meme_academie, pourcent_neo_bac_admis_meme_academie_pcv,
                      pourcent_neo_bac_admis_meme_etablissement_bts_cpge, pourcent_neo_bac_admis_boursiers,
                      pourcent_neo_bac, pourcent_neo_bac_mention_sans_info, pourcent_neo_bac_mention_sans,
                      pourcent_neo_bac_mention_assez_bien, pourcent_neo_bac_mention_bien, 
                      pourcent_neo_bac_mention_très_bien, pourcent_neo_bac_mention_très_bien_felicitations,
                      pourcent_neo_bac_general, pourcent_neo_bac_general_avec_mention, pourcent_neo_bac_techno, 
                      pourcent_neo_bac_techno_avec_mention, pourcent_neo_bac_pro, pourcent_neo_bac_pro_avec_mention,
                      effectif_candidats_terminale_generale_avec_proposition_admis,
                      effectif_candidats_terminale_generale_boursiers_avec_proposition_admis,
                      effectif_candidats_terminale_techno_avec_proposition_admis,
                      effectif_candidats_terminale_techno_boursiers_avec_proposition_admis,
                      effectif_candidats_terminale_pro_avec_proposition_admis,
                      effectif_candidats_terminale_pro_boursiers_avec_proposition_admis,
                      effectif_autres_candidats_avec_proposition_admis, regroupement_1, rang_dernier_appele_groupe1,
                      regroupement_2, rang_dernier_appele_groupe2, regroupement_3, rang_dernier_appele_groupe3,
                      list_com, tri, cod_aff_form, concours_communs_banques_epreuves, url_formation, taux_acces,
                      part_terminale_generale_en_position_admis_phase_principale, 
                      part_terminale_techno_en_position_admis_phase_principale,
                      part_terminale_pro_en_position_admis_phase_principale,
                      etablissement_id_paysage, composante_id_paysage
         -importColumns=session_annee, etablissement_statut, etablissement_code_uai, etablissement_nom,
                      departement_code, departement_nom, region_nom, academie_nom, commune_nom, filiere_libelle, 
                      selectivite, filiere_libelle_tres_abrege, filiere_libelle_detaille, filiere_libelle_abrege,
                      filiere_libelle_detaille_bis, filiere_libelle_tres_detaille, coordonnees_gps, capacite, 
                      effectif_total_candidats, effectif_total_candidates, 
                      effectif_candidat_neo_bac_classes_type_general, 
                      effectif_candidat_neo_bac_classes_type_techno, 
                      effectif_candidat_neo_bac_classes_type_pro, 
                      effectif_candidat_classes_type_autres,
                      effectif_admis_neo_bac_type_general, effectif_admis_neo_bac_type_techno,
                      effectif_admis_neo_bac_type_pro, effectif_admis_neo_bac_type_autres,
                      effectif_admis_neo_bac_selon_mention_type_mention_sans_info,
                      effectif_admis_neo_bac_selon_mention_type_mention_sans_mention,
                      effectif_admis_neo_bac_selon_mention_type_mention_assez_bien,
                      effectif_admis_neo_bac_selon_mention_type_mention_bien,
                      effectif_admis_neo_bac_selon_mention_type_mention_tres_bien,
                      effectif_admis_neo_bac_selon_mention_type_mention_tres_bien_fel,
                      effectif_admis_neo_bac_avec_mention_type_bac_general,
                      effectif_admis_neo_bac_avec_mention_type_bac_techno,
                      effectif_admis_neo_bac_avec_mention_type_bac_pro,
                      regroupement_1, rang_dernier_appele_groupe1, regroupement_2, rang_dernier_appele_groupe2,
                      regroupement_3, rang_dernier_appele_groupe3,
                      list_com, tri, cod_aff_form, concours_communs_banques_epreuves, url_formation;
--         -keyColumns=etablissement_code_UAI;


DELETE FROM _effectif_selon_mention;
DELETE FROM _rang_dernier_appele_selon_regroupement;
DELETE FROM _admissions_selon_type_neo_bac;
DELETE FROM _admissions_generalites;
DELETE FROM _formation;
DELETE FROM _commune;
DELETE FROM _departement;
DELETE FROM _region;
DELETE FROM _filiere;
DELETE FROM _etablissement;
DELETE FROM _type_bac;
DELETE FROM _session;
DELETE FROM _regroupement;
DELETE FROM _mention_bac;
DELETE FROM _academie;

INSERT INTO _region
            (region_nom)
SELECT DISTINCT region_nom
FROM   import_data;


INSERT INTO _departement
            (departement_code,
             departement_nom,
             region_nom)
SELECT DISTINCT departement_code,
                departement_nom,
                region_nom
FROM   import_data;


INSERT INTO _commune
            (commune_nom,
             departement_code)
SELECT DISTINCT commune_nom,
                departement_code
FROM   import_data;


INSERT INTO _academie
            (academie_nom)
SELECT DISTINCT academie_nom
FROM   import_data;


INSERT INTO _filiere
            (filiere_libelle,
             filiere_libelle_tres_abrege,
             filiere_libelle_abrege,
             filiere_libelle_detaille_bis)
SELECT DISTINCT filiere_libelle,
                filiere_libelle_tres_abrege,
                filiere_libelle_abrege,
                filiere_libelle_detaille_bis
FROM   import_data;


INSERT INTO _etablissement
            (etablissement_code_uai,
             etablissement_nom,
             etablissement_statut)
SELECT DISTINCT etablissement_code_uai,
                etablissement_nom,
                etablissement_statut
FROM   import_data;


INSERT INTO _session
            (session_annee)
SELECT DISTINCT session_annee
FROM   import_data;


INSERT INTO _regroupement
            (libelle_regroupement)
SELECT DISTINCT regroupement_1
FROM   import_data
WHERE  regroupement_1 IS NOT NULL
UNION
SELECT DISTINCT regroupement_2
FROM   import_data
WHERE  regroupement_2 IS NOT NULL
UNION
SELECT DISTINCT regroupement_3
FROM   import_data
WHERE  regroupement_3 IS NOT NULL;


INSERT INTO _mention_bac
            (libelle_mention)
VALUES      ('Sans information'),
            ('Sans mention'),
            ('Assez bien'),
            ('Bien'),
            ('Très bien'),
            ('Très bien avec félicitations du jury');


INSERT INTO _type_bac
            (type_bac)
VALUES      ('Bac général'),
            ('Bac technologique'),
            ('Bac professionnel'),
            ('Autres');


INSERT INTO _formation
            (filiere_libelle_detaille,
             coordonnees_gps,
             list_com,
             cod_aff_form,
             tri,
             concours_communs_banques_epreuves,
             url_formation,
             filiere_id,
             etablissement_code_uai,
             commune_nom,
             departement_code,
             academie_nom)
SELECT DISTINCT filiere_libelle_detaille,
                coordonnees_gps,
                list_com,
                cod_aff_form,
                tri,
                concours_communs_banques_epreuves,
                url_formation,
                filiere_id,
                etablissement_code_uai,
                commune_nom,
                departement_code,
                academie_nom
FROM   import_data
       natural JOIN _filiere;


INSERT INTO _admissions_generalites
            (cod_aff_form,
             session_annee,
             selectivite,
             capacite,
             effectif_total_candidats,
             effectif_total_candidates)
SELECT DISTINCT cod_aff_form,
                session_annee,
                selectivite,
                capacite,
                effectif_total_candidats,
                effectif_total_candidates
FROM   import_data;


INSERT INTO _rang_dernier_appele_selon_regroupement
            (cod_aff_form,
             session_annee,
             libelle_regroupement,
             rang_dernier_appele)
SELECT DISTINCT cod_aff_form,
                session_annee,
                regroupement_1,
                rang_dernier_appele_groupe1
FROM   import_data
WHERE  regroupement_1 IS NOT NULL
UNION ALL
SELECT DISTINCT cod_aff_form,
                session_annee,
                regroupement_2,
                rang_dernier_appele_groupe2
FROM   import_data
WHERE  regroupement_2 IS NOT NULL
UNION ALL
SELECT DISTINCT cod_aff_form,
                session_annee,
                regroupement_3,
                rang_dernier_appele_groupe3
FROM   import_data
WHERE  regroupement_3 IS NOT NULL;


INSERT INTO _admissions_selon_type_neo_bac
            (cod_aff_form,
             session_annee,
             type_bac,
             effectif_candidat_neo_bac_classes)
SELECT cod_aff_form,
       session_annee,
       'Bac général',
       effectif_candidat_neo_bac_classes_type_general
FROM   import_data
UNION
SELECT cod_aff_form,
       session_annee,
       'Bac technologique',
       effectif_candidat_neo_bac_classes_type_techno
FROM   import_data
UNION
SELECT cod_aff_form,
       session_annee,
       'Autres',
       effectif_candidat_classes_type_autres
FROM   import_data
UNION
SELECT cod_aff_form,
       session_annee,
       'Bac professionnel',
       effectif_candidat_neo_bac_classes_type_pro
FROM   import_data;


INSERT INTO _effectif_selon_mention
            (cod_aff_form,
             session_annee,
             libelle_mention,
             effectif_admis_neo_bac_selon_mention)
SELECT cod_aff_form,
       session_annee,
       'Sans information',
       effectif_admis_neo_bac_selon_mention_type_mention_sans_info
FROM   import_data
UNION
SELECT cod_aff_form,
       session_annee,
       'Sans mention',
       effectif_admis_neo_bac_selon_mention_type_mention_sans_mention
FROM   import_data
UNION
SELECT cod_aff_form,
       session_annee,
       'Assez bien',
       effectif_admis_neo_bac_selon_mention_type_mention_assez_bien
FROM   import_data
UNION
SELECT cod_aff_form,
       session_annee,
       'Bien',
       effectif_admis_neo_bac_selon_mention_type_mention_bien
FROM   import_data
UNION
SELECT cod_aff_form,
       session_annee,
       'Très bien',
       effectif_admis_neo_bac_selon_mention_type_mention_tres_bien
FROM   import_data
UNION
SELECT cod_aff_form,
       session_annee,
       'Très bien avec félicitations du jury',
       effectif_admis_neo_bac_selon_mention_type_mention_tres_bien_fel
FROM   import_data;

DROP TABLE import_data;