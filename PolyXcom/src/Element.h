/*
 * Element.h
 *
 *  Created on: 28 nov. 2016
 *      Author: Valentin BISSUEL
 */

#ifndef ELEMENT_H_
#define ELEMENT_H_


template <typename Type>
class Element {
	private:
		Type _valeur;
		Element<Type>* _suiv;

	public:
		Element(Type valeur, Element<Type>* suiv);
		//virtual ~Element();
};

#endif /* ELEMENT_H_ */
