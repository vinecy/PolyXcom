/*
 * Element.cpp
 *
 *  Created on: 28 nov. 2016
 *      Author: Valentin BISSUEL
 */

#include <iostream>
#include "Element.h"

using namespace std;

template <typename Type>
Element<Type>::Element(Type valeur, Element<Type>* suiv){
   _valeur = valeur;
   _suiv = suiv;
   cout << "constructeur element" << endl;
}

