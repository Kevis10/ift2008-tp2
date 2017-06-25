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
#include "ReseauInterurbain.h"
#include "AssertionException.h"
//vous pouvez inclure d'autres librairies si c'est nécessaire

namespace TP2
{

	ReseauInterurbain::ReseauInterurbain(std::string nomReseau, size_t nbVilles)
	:unReseau(nbVilles), nomReseau(nomReseau)
	{

	}

	ReseauInterurbain::~ReseauInterurbain(){

	}


	Chemin ReseauInterurbain::rechercheCheminDijkstra(const std::string & source, const std::string & destination, bool dureeCout) const {
		Chemin compile_pls;
		return compile_pls;
	}

	std::vector<std::vector<std::string> > ReseauInterurbain::algorithmeKosaraju(){
		std::vector<std::vector<std::string> > compile_pls;
		return compile_pls;
	}

	// Méthode fournie
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

//À compléter par l'implémentation des autres méthodes demandées

}//Fin du namespace
