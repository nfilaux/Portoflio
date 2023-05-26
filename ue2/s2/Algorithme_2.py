#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Fri Mar 31 09:32:53 2023

@author: rcolas
"""

import time

#-----------------------------------------------------Fonctions-------------------------------------------

def bonnePos(chess, ligne, colonne,taille):
    """
    Permets de vérifier si oui ou non la reine que l'on souhaite placer aligné ou non avec une autre reine sur l'échiquier

    renvoie vrai si peut-être placer faux sinon

    """
    #Vérifie la ligne
    for j in range(taille):
        if chess[ligne][j] == 1:
            return False
    #Vérifie la colonne
    for i in range(taille):
        if chess[i][colonne] == 1:
            return False

    #Vérifie la diagonal haut gauche
    i, j = ligne, colonne
    while i >= 0 and j >= 0:
        if chess[i][j] == 1:
            return False
        i -= 1
        j -= 1
        
    #Vérifie la diagonal basse droit
    i, j = ligne, colonne
    while i < taille and j < taille:
        if chess[i][j] == 1:
            return False
        i += 1
        j += 1

    #Vérifie la diagonal haut droit
    i, j = ligne, colonne
    while i >= 0 and j < taille:
        if chess[i][j] == 1:
            return False
        i -= 1
        j += 1

    #Vérifie la diagonal basse gauche
    i, j = ligne, colonne
    while i < taille and j >= 0:
        if chess[i][j] == 1:
            return False
        i += 1
        j -= 1
    return True

def print_solutions(chess):
    """
    Permets d'organiser l'affichage des solutions
    """
    for ligne in chess:
        print(ligne[:])
    print()


def posReine(chess, colonne,taille):
    """
    Fonction principale récursive qui place les reines colonnes par colonnes jusqu'à la fin et sauvegarde les bonnes et mauvaises solution dans des listes
    """
    if colonne == taille: #Si on arrive a la dernière colonne ,c'est un bon paterne de reine
        ajoutesol(solutions) #donc on ajoute aux solutions
        return True #puis on s'arrete

    for ligne in range(taille):#Pour chaque ligne de la colonne où on se trouve
        if bonnePos(chess, ligne, colonne,taille): #on vérifie si l'emplacement sur cette ligne est bonne et si oui,
            chess[ligne][colonne] = 1              #on place la reine
            posReine(chess, colonne + 1,taille)    #on passe à l'autre colonne
            chess[ligne][colonne] = 0              #on initilise les colonnes cases sans reines
        else:   # si aucune ligne bonne
             ajoutesol(bad_solutions)   #alors mauvaise solution on ajoute dans les mauvaises solutions
    return False

def ajoutesol(typesol):
    """
    Ajoute une solutions dans la liste choisi (bonne ou maivaise sol)
    """
    new_solution = [] #on créer la solution

    for ligne in chess: 
        copied_ligne = ligne[:]
        new_solution.append(copied_ligne)  # on ajoute toutes les lignes dans la solution

    typesol.append(new_solution) #on ajoute la solution à la liste des solutions


#-----------------------------------------------------Programmme-------------------------------------------

taille = 4
chess = [[0 for j in range(taille)] for i in range(taille)] #initialisation de l'echequier
solutions = []
bad_solutions = [] 

start_time = time.time()

posReine(chess, 0, taille) # lancement du programme pour echiquier de taille par taille

print("--- %s seconds ---" % (time.time() - start_time))

print("Solutions trouvées ",len(solutions),":")     #J'affiche mes bonnes solutions
for sol in solutions:
    print_solutions(sol)


print("Mauvaises solutions ",len(bad_solutions),": \nVouler vous les afficher ? O pour oui")
rep = input()
if rep == "O": # Je demande si l'utilisateur souhaite afficher les mauvaises solutions car elles prennent beaucoup de place dans le terminale

    for bad_sol in bad_solutions:
        print_solutions(bad_sol)


