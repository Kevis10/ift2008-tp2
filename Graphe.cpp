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
	 /**
	 * \brief Constructeur du graph
	 *
	 * \post Une instance du graphe est cree
	 * \param[in] nbSommets le nombre de sommets du graphe
	 */
	Graphe::Graphe(size_t nbSommets)
	:noms(nbSommets), listesAdj(nbSommets), nbSommets(nbSommets), nbArcs()
	{

	}

	 /**
	 * \brief destructeur du graph
	 *
	 * \post Le graph est detruit
	 */
	Graphe::~Graphe(){}


	 /**
	 * \brief Change le nombre de sommets du graphe
	 *
	 * \post Le graphe a maintenant plus de sommets
	 * \param[in] nouvelleTaille le nouveau nombre de sommets du graphe
	 */
	void Graphe::resize(size_t nouvelleTaille){
		noms.resize(nouvelleTaille);
		listesAdj.resize(nouvelleTaille);
		nbSommets = nouvelleTaille;
		ASSERTION(noms.size()==nouvelleTaille && listesAdj.size() == nouvelleTaille);
	}

	/**
	 * \brief Affecte un nom a un sommet
	 *
	 * \post Le sommet est nomme
	 * \param[in] sommet le sommet a modifier
	 * \param[in] le nom a affecter au sommet
	 */
	void Graphe::nommer(size_t sommet, const std::string & nom){
		noms[sommet] = nom;
	}

	/**
	 * \brief Ajoute un arc au graphe
	 *
	 * \post L'arc est ajoute
	 * \param[in] source le point de depart
	 * \param[in] destination le point d'arrivee
	 * \param[in] duree La duree de l'arc en temps
	 * \param[in] cout Le cout de traverser l'arc en $
	 */
	void Graphe::ajouterArc(size_t source, size_t destination,float duree, float cout){
		//peut etre verifier que l'arc n'existe pas deja...

		Ponderations ponderation_de_arc(duree,cout);
		Arc arc_a_ajouter(destination,ponderation_de_arc);
		arc_a_ajouter.poids = ponderation_de_arc;
		listesAdj[source].push_back(arc_a_ajouter);
		nbArcs ++;
	}

	/**
	 * \brief Enleve un arc au graphe
	 *
	 * \post L'arc est enleve
	 * \param[in] source le point de depart
	 * \param[in] destination le point d'arrivee
	 */
	void Graphe::enleverArc(size_t source, size_t destination){

		std::list<Arc>::iterator arc_a_enlever;
		for(std::list<Arc>::iterator i = listesAdj[source].begin(); i != listesAdj[source].end(); i++ ){
			if(i->destination==destination){
				arc_a_enlever = i;
			}
		}
		listesAdj[source].erase(arc_a_enlever);
	}

	/**
	 * \brief Retourne si l'arc existe ou non
	 *
	 * \param[in] source le point de depart
	 * \param[in] destination le point d'arrivee
	 */
	bool Graphe::arcExiste(size_t source, size_t destination) const{
		ASSERTION(source<nbSommets);

		for(auto arc: listesAdj[source]){
			if(arc.destination==destination){
				return true;
			}
		}
		return false;
	}


	/**
	 * \brief Retourne la liste des sommets adjacents d'un sommet
	 *
	 * \param[in] source le point de depart
	 */
	std::vector<size_t> Graphe::listerSommetsAdjacents(size_t sommet) const{
		ASSERTION(sommet<nbSommets);
		std::vector<size_t> liste_des_adjacents;
		for(auto arc: listesAdj[sommet]){
			liste_des_adjacents.push_back(arc.destination);
		}
		return liste_des_adjacents;
	}

	/**
	 * \brief Retourne le nom d'un sommet
	 *
	 * \param[in] size_t l'index du sommet
	 */
	std::string Graphe::getNomSommet(size_t sommet) const{
		ASSERTION(sommet<nbSommets);
		return noms[sommet];
	}


	/**
	 * \brief Retourne le nombre de sommet du graphe
	 *
	*/
	int Graphe::getNombreSommets() const{
		return nbSommets;
	}

	/**
	* \brief Retourne le nombre des arcs du graphe
	*
	*/
	//
	int Graphe::getNombreArcs() const{
		return nbArcs;
	}


	/**
	 * \brief Retourne l'index du sommet
	 *
	 * \param[in] size_t le nom du sommet
	 */
	size_t Graphe::getNumeroSommet(const std::string & nom) const{
		for(size_t i =0 ; i<noms.size() ; i++){
			if(noms[i]==nom){
				return i;
			}
		}
	}

	/**
	 * \brief Retourne la ponderation des couts d'un arc donnee
	 *
	 * \param[in] source le point de depart
	 * \param[in] destination le point d'arrivee
	 */
	Ponderations Graphe::getPonderationsArc(size_t source, size_t destination) const{
		if(arcExiste(source,destination)){
			for(auto arc: listesAdj[source]){
				if(arc.destination==destination){
					return arc.poids;
				}
			}
		}
	}


	std::vector<size_t> Graphe::listerSommetsAdjacentsInverse(size_t sommet) const{
		std::vector<size_t> adjacence_inverse;
		for(size_t numero_sommet=0; numero_sommet < listesAdj.size(); numero_sommet++){
			for(auto arc: listesAdj[numero_sommet]){
				if(arc.destination==sommet){
					adjacence_inverse.push_back(numero_sommet);
				}
			}
		}
		return adjacence_inverse;
	}

}//Fin du namespace
