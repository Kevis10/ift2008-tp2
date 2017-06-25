/**
 * \file Graphe.cpp
 * \brief Implémentation d'un graphe orienté.
 * \author Jean-Thomas Baillargeon
 * \version 0.5
 * \date 21 juin 2017
 *
 *  Travail pratique numéro 2
 *
 */

#include "Graphe.h"
#include "AssertionException.h"
#include "algorithm"

//vous pouvez inclure d'autres librairies si c'est nécessaire

namespace TP2
{

	Graphe::Graphe(size_t nbSommets)
	:noms(), listesAdj(), nbSommets(nbSommets), nbArcs()
	{


	}

	Graphe::~Graphe(){}


	void Graphe::resize(size_t nouvelleTaille){
		noms.resize(nouvelleTaille);
		listesAdj.resize(nouvelleTaille);
		ASSERTION(noms.size()==nouvelleTaille && listesAdj.size() == nouvelleTaille);
	}

	void Graphe::nommer(size_t sommet, const std::string & nom){
		noms[sommet] = nom;
	}

	void Graphe::ajouterArc(size_t source, size_t destination,float duree, float cout){
		//peut etre verifier que le sommet existe avant d'ajouter
		//peut etre verifier que l'arc n'existe pas deja...

		Ponderations ponderation_de_arc(cout,duree);
		Arc arc_a_ajouter(destination,ponderation_de_arc);
		arc_a_ajouter.poids = ponderation_de_arc;
		listesAdj[source].push_back(arc_a_ajouter);
		nbArcs ++;
	}

	size_t Graphe::getNumeroSommet(const std::string & nom) const{
		for(size_t i =0 ; i<noms.size() ; i++){
			if(noms[i]==nom){
				return i;
			}
		}
	}


	//Mettez l'implémentation de vos méthodes ici.

}//Fin du namespace
