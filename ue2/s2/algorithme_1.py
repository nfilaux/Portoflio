#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Fri Feb 10 10:54:09 2023

@author: nfilaux

"Plateau" représente un tableau d'echec et "JeuReines" permet de résoudre le probleme des huit dames à l'aide de "Plateau"
"""

import time

#création d'une calsse plateau qui représente un échequier pour poser les reines
class Plateau(object):
    def __init__(self, taille, jeu=None, coord=[]):
        #si aucun tableau en parametre on créer un tableau vide de taille x taille pour connaître les positions libres
        if jeu == None:
            jeu = [[True for j in range(taille)] for i in range(taille)]
        self.jeu = jeu
        #tableau pour stocker les coordonnés des dames
        self.coord_dames = coord
        #tableau pour les dimensions
        self.taille = taille
    
    #redefinition de __str__ pour afficher le tableau de jeu
    def __str__(self):
        return str(self.jeu)
    
    #Methode pour placer une reine sur le platrau aux coordonnées i, j
    def poser_reine(self, i, j, lst=None):
        lig = i
        col = j
        # si la case est libre
        if self.jeu[i][j] == True:
            for k in range(self.taille):
                #bloque lignes verticales et horizontales
                self.jeu[i][k] = False
                self.jeu[k][j] = False
            #bloque diagonale NO --> SE
            while lig > 0 and col > 0:
                lig-=1
                col-=1
            while lig < self.taille and col < self.taille:
                self.jeu[lig][col] = False
                lig+=1
                col+=1
            lig = i
            col = j
            #bloque diagonale NE --> SO
            while lig > 0 and col < self.taille-1:
                lig-=1
                col+=1
            while lig < self.taille and col >= 0:
                self.jeu[lig][col] = False
                lig+=1
                col-=1
            #on ajoute la reine place aux tableau de coordonnées
            if lst == None:
                self.coord_dames.append((i,j))
            else:
                lst.append((i,j))
            #reine placee
            return True
        #reine non place
        return False
    
    #Methode pour récuperer les coordonnées des dames
    def get_reines(self):
        return self.coord_dames
    
     # Methode pour trouver les position où une reine peut être placée
    def trouve_positions_libres(self):
        lst_libres = []
        for i in range(self.taille):
            for j in range(self.taille):
                if self.jeu[i][j] == True:
                    lst_libres.append((i,j))
        return lst_libres
    
    # Méthode pour créer une copie du plateau actuel
    def copy(self):
        j = [x.copy() for x in self.jeu]
        c = self.coord_dames.copy()
        t = self.taille
        return Plateau(t,j,c)
    
class JeuReines(object):
    
    def __init__(self, n):
        self.coord_toutes_reines = [] # liste des solutions
        self.complex = n # taille du plateau
    
    def solutions(self, etat=None):
        #si on a pas d'état en parametre on créer un nouveau plateau
        if etat == None:
            #plateau vierge
            etat = Plateau(self.complex)
        
        # si le nombre de reines posés == taille du jeu on l'ajoute à la liste des solutions
        if len(etat.get_reines()) >= self.complex:
            #ajoute à la liste des solutions finales
            self.coord_toutes_reines.append(etat.get_reines())
            return 1
        
        # on boucle sur toutes les positions libres
        for coord in etat.trouve_positions_libres():
            #on crée une copie du plateau car sinon tout les autres appels seront affectés par les changement fiat par la premieres itération
            etat_temp = etat.copy()
            #on pose la reine
            etat_temp.poser_reine(coord[0], coord[1])
            #on contniue avec un appel récursif avec l'état actuel
            self.solutions(etat_temp)
        return 0
    
    # methode pour obtenir toutes les solutions trouvées
    def getToutesReines(self):
        self.suppDoublon()
        return self.coord_toutes_reines
    
    #  methode pour supprimer les doublons dans la liste des solutions
    def suppDoublon(self):
        #liste temporaire pour stocker les solutions déja trié
        temp = []
        for i in range(len(self.coord_toutes_reines)):
            #on trie
            self.coord_toutes_reines[i].sort()
            #on ajoute a la liste temporaire
            temp.append(self.coord_toutes_reines[i].copy())
        #reset la liste
        self.coord_toutes_reines = []
        #boucle chaque elements trié
        for x in temp:
            #verifie doublon
            if x not in self.coord_toutes_reines:
                #on ajoute
                self.coord_toutes_reines.append(x)
    
    def afficher(self):
        for i in self.getToutesReines():
            print(i)



temps_debut = time.time() #on prend note du temps avant l'execution des fonctions/methodes
sol = JeuReines(7) #on creer l'objet pour resoudre le probleme
sol.solutions() # on lance la resolution
temps_fin = time.time() #on reprend le temps
print(sol.afficher()) #affiche les solutions
print("Temps d'execution :", temps_fin - temps_debut, "secondes /", (temps_fin - temps_debut)/60, "minutes")