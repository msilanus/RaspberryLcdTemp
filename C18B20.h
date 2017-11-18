/***************************************************************
*   Classe de bas niveau de gestion du bus w1 et lecture de la 
*   température donnée par un capteur 18B20 (28-...)
*
*   - sensor : contient le chemin absolu vers le fichier du capteur
*   - 18B20() : Constructeur. Rempli sensor
*   - getTemperature() : Renvoi la température en °C
*   - getSensorPath() : Renvoi le contenu de sensor
* 
*   Auteur : Marc Silanus
*   date : 18/11/2017
*   rev 0
*
***************************************************************/ 
#ifndef C18B20_H
#define C18B20_H

#include <string>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>


class C18B20
{

	private :
	
	std::string sensor;

	public :
	
	C18B20();
	float getTemperature();
	std::string getSensorPath();
};


#endif //18B20_H
