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
		Chemin compile_pls;
		return compile_pls;
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
						composante_fortement_connexe.push_back(std::to_string(noeud));
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
