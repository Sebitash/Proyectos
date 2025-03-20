#ifndef NOSFERATU_H_
#define NOSFERATU_H_

#include "Vampiro.h"
#include "Utiles.h"

class Nosferatu : public Vampiro {
private:
    //ATRIBUTOS
    bool humanoMordido;

public:
    //constructor
	Nosferatu(int id, int fila, int columna);

    //PRE:
    //POST: llama al usuario para que eliga que tipo de defensa a realizar
    void elegirDefensa();

    //PRE:
    //POST: imprime por pantalla quien soy, sus atributos, y su ubicacion
    void mostrar() override;

};


#endif /* NOSFERATU_H_ */
