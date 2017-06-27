/**
 * \file ReseauInterurbain.cpp
 * \brief Implémentattion de la classe ReseauInterurbain.
 * \author Jean-Thomas Baillargeon
 * \version 0.5
 * \date 21 juin 2017
 *
 *  Travail pratique numéro 2
 *
 */
#include <sstream>
#include <fstream>
#include <string>
#include <stack>
#include <algorithm>
#include <vector>
#include "ReseauInterurbain.h"
#include "AssertionException.h"
//vous pouvez inclure d'autres librairies si c'est nécessaire

namespace TP2
{

	/**
	* \brief Constructeur du ReseauInterurbain
	*
	* \post Une instance du ReseauInterurbain est cree
	* \param[in] nomReseau le nom du reseau
	* \param[in] nbVilles le nombre de villes dans le reseau
	*/
	ReseauInterurbain::ReseauInterurbain(std::string nomReseau, size_t nbVilles)
	:unReseau(nbVilles), nomReseau(nomReseau)
	{

	}

	/**
	* \brief Destructeur du ReseauInterurbain
	*
	* \post l'instance du ReseauInterurbain est detruite
	*/
	ReseauInterurbain::~ReseauInterurbain(){

	}

	/**
	* \brief Modifie la grosseur du reseau
	*
	* \post Le reseau a une taille modifiee
	* \param[in] nouvelleTailles la nouvelle taille du reseau
	*/
	void ReseauInterurbain::resize(size_t nouvelleTailles){
		unReseau.resize(nouvelleTailles);
	}


	/**
	* \brief Calcule le plus court chemin entre deux sommets selon une poderation en temps ou en $
	*
	* \post Le reseau a une taille modifiee
	* \param[in] source le sommet de depart
	* \param[in] destination le sommet a atteindre
	* \param[in] dureeCout vrai si pondere par duree, faux si pondere par cout
	*/
	Chemin ReseauInterurbain::rechercheCheminDijkstra(const std::string & source, const std::string & destination, bool dureeCout) const {
		Chemin plus_court_chemin;
		plus_court_chemin.coutTotal = 0;
		plus_court_chemin.dureeTotale= 0;
		plus_court_chemin.reussi = false;

		std::vector<int> precedents(unReseau.getNombreSommets());
		std::vector<int> visite(unReseau.getNombreSommets(),false);
		std::vector<int> decouvert(unReseau.getNombreSommets(),false);
		std::vector<float> poids(unReseau.getNombreSommets(),1e6);
		std::vector<int> a_visiter;

		size_t initial_node = unReseau.getNumeroSommet(source);
		size_t actual_node = initial_node;
		size_t final_node =  unReseau.getNumeroSommet(destination);
		poids[actual_node] = 0.;
		a_visiter.push_back(actual_node);
		while(a_visiter.size()>0){
			//explore les points
			for(auto fin_arc: unReseau.listerSommetsAdjacents(actual_node)){
				//mise a jour temptative des poids
				float amount_to_travel = getAmountToTravel(actual_node, fin_arc, dureeCout);
				if(poids[fin_arc] > poids[actual_node]+amount_to_travel){
					poids[fin_arc]=poids[actual_node]+amount_to_travel;
					precedents[fin_arc] = actual_node;
				}
				if(!visite[fin_arc] and !decouvert[fin_arc]){
					decouvert[fin_arc] = true;
					a_visiter.push_back(fin_arc);
				}
			}

			//on trouve la prochaine ville a explorer
			a_visiter.erase(std::remove(a_visiter.begin(), a_visiter.end(), actual_node), a_visiter.end());
			visite[actual_node] = true;
			float poids_a_battre = 1e6;
			for(auto arc: a_visiter){
				if(poids[arc]<poids_a_battre){
					poids_a_battre =poids[arc];
					actual_node = arc;
				}
			}

			//si on a atteint notre but
			if(actual_node==final_node){
				std::vector<size_t> chemin_inverse;
				chemin_inverse.push_back(actual_node);
				do {
					chemin_inverse.push_back(precedents[actual_node]);
					actual_node = precedents[actual_node];
				}while( actual_node != initial_node );
				std::reverse(chemin_inverse.begin(),chemin_inverse.end());
				for(size_t index=0; index<chemin_inverse.size();index++){
					if(index>0){
						plus_court_chemin.dureeTotale += getAmountToTravel(chemin_inverse[index-1],chemin_inverse[index],true);
						plus_court_chemin.coutTotal+= getAmountToTravel(chemin_inverse[index-1],chemin_inverse[index],false);

					}
					plus_court_chemin.listeVilles.push_back(unReseau.getNomSommet(chemin_inverse[index]));
				}

				plus_court_chemin.reussi = true;
				return plus_court_chemin;

			}



		}


		return plus_court_chemin;
	}


	float ReseauInterurbain::getAmountToTravel(size_t source, size_t destination, bool dureeCout) const{

		Ponderations poids = unReseau.getPonderationsArc(source,destination);
		float a_ajouter;

		if(dureeCout){
			return poids.duree;
		}else{
			return poids.cout;
		}

	}

	/**
	* \brief Retourne les composantes fortement connexes d'un reseau
	*/

	std::vector<std::vector<std::string> > ReseauInterurbain::algorithmeKosaraju(){

		std::vector<size_t> parcours_profondeur = _parcoursCompletProfondeur();

		std::reverse(parcours_profondeur.begin(),parcours_profondeur.end());
		std::vector<std::vector<std::string> > composantes;
		std::vector<bool> visite(unReseau.getNombreSommets(),false);



		for(auto index: parcours_profondeur){
			std::vector<std::string> composante_fortement_connexe;

			if(!visite[index]){
					for(auto noeud : _parcoursProfondeur(index, visite,true)){
						composante_fortement_connexe.push_back(unReseau.getNomSommet(noeud));
					}
					composantes.push_back(composante_fortement_connexe);
				}
			}



		return composantes;
	}

	std::vector<size_t> ReseauInterurbain::_parcoursCompletProfondeur() const {
		std::vector<size_t> parcours_profondeur;
		std::vector<bool> visite(unReseau.getNombreSommets(),false);
		for(size_t index=0; index < unReseau.getNombreSommets(); index++){
			if(!visite[index]){
				for(auto noeud : _parcoursProfondeur(index, visite,false)){
					parcours_profondeur.push_back(noeud);
				}
			}
		}
		return parcours_profondeur;
	}

	std::vector<size_t> ReseauInterurbain::_parcoursProfondeur(size_t source, std::vector<bool> & visite, bool reverse) const {
		ASSERTION(source < unReseau.getNombreSommets());

		std::vector<size_t> resultat;
		std::stack<size_t> pile;
		resultat = _parcours(source, pile, visite, reverse);

		return resultat;
	}

	std::vector<size_t> ReseauInterurbain::_parcours(size_t source, std::stack<size_t> & container, std::vector<bool> & visite, bool reverse) const {
		//CODE TRES FORTEMENT INSPIRE DES LABORATOIRES :)

		ASSERTION(source < unReseau.getNombreSommets());

		std::vector<size_t> resultat;

		// On a besoin d'une manière de marquer si un sommet a été
		// visité ou non. Utilisons un vecteur de Booléens (comme nos sommets sont
	    // numérotés de 0 à m_nbSommets - 1)

		// On visite le sommet de départ et on l'ajoute comme prochain
		visite[source] = true;
		container.push(source);

		// Tant que le parcours n'est pas terminé
		while (container.size() > 0) {
			// On récupère le prochain et liste ses sommets adjacents
			size_t prochain = container.top();
			container.pop();
			resultat.push_back(prochain);

			// On liste les sommets adjacents du sommet de départ.
			std::vector<size_t> adjacents;
			if(!reverse){
				adjacents = unReseau.listerSommetsAdjacents(prochain);
			}else{
				adjacents = unReseau.listerSommetsAdjacentsInverse(prochain);
			}


			// Pour chaque sommet adjacent non visité, on l'ajoute à la pile de
			// sommets à visiter.
			for (auto it = adjacents.cbegin(); it != adjacents.cend(); ++it) {
				if (!visite[*it]) {
					container.push(*it);
					visite[*it] = true;
				}
			}
		}

		return resultat;
	}


	/**
	* \brief Genere l'output en texte d'un reseau
	*/

	void ReseauInterurbain::chargerReseau(std::ifstream & fichierEntree)
	{
		std::string buff;

		getline(fichierEntree, nomReseau);
		nomReseau.erase(0, 20); // Enlève: Reseau Interurbain:

		int nbVilles;

		fichierEntree >> nbVilles;
		getline(fichierEntree, buff); //villes

		unReseau.resize(nbVilles);

		getline(fichierEntree, buff); //Liste des villes

		size_t i = 0;

		while(getline(fichierEntree, buff) && buff != "Liste des trajets:")
		{
			unReseau.nommer(i, buff);
			i++;
		}

		while(getline(fichierEntree, buff))
		{
			std::string source = buff;
			getline(fichierEntree, buff);
			std::string destination = buff;

			getline(fichierEntree, buff);
			std::istringstream iss(buff);

			float duree;
			iss >> duree;

			float cout;
			iss >> cout;

			unReseau.ajouterArc(unReseau.getNumeroSommet(source), unReseau.getNumeroSommet(destination), duree, cout);
		}
	}


}
