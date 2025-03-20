#include "Humano.h"
#include "Utiles.h"
#include "Constantes.h"

const int NULO = 0;

int Humano::cantidadHumanos = 0;

Humano::Humano(int id, int fila, int columna) : Ser(id, fila, columna) {
    this->nombreMapa = LETRA_HUMANO;
    this->recargaEnergiaTurno = 5;
    this->energiaMinimaAtaque = 5;
    this->PORCENTAJE_ATAQUE_ZOMBI = 0.2;
    this->PORCENTAJE_ATAQUE_VAMPIRO = 0.2;
    this->convertidoZombi = false;
    this->convertidoVampiro = false;
    this->turnosConversionZombi = 0;
    cantidadHumanos++;
}

int Humano::devolverCantidadHumanos() {
    return cantidadHumanos;
}


void Humano::mostrar() {
    std::cout << "\n Soy Humano Simple" << std::endl;
    mostrarAtributos();
    mostrarInventario();
}

void Humano::mostrarInventario() {
    std::cout << std::endl << "\t INVENTARIO" << std::endl;
    if (inventario->inventarioVacio()) {
        std::cout << "...esta vacío --_(o.o)_--" << std::endl;
    } else {
        if (inventario->tieneEscopeta()) {
            std::cout << ". Escopeta: 1" << std::endl;
        }
        if (inventario->tieneEstaca()) {
            std::cout << ". Estaca: " << inventario->getEstaca() << std::endl;
        }
        if (inventario->tieneAguaBendita()) {
            std::cout << ". Agua Bendita: " << inventario->getAguaBendita() << std::endl;
        }
        if (inventario->getBala() > NULO) {
            std::cout << ". Balas: " << inventario->getBala() << std::endl;
        }
        if (inventario->tieneCruz()) {
            std::cout << ". Cruces: " << inventario->getCruz() << std::endl;
        }
    }
}

bool Humano::elegirArma(Accion &error, ITEM_ELEGIDO &armaElegida) {
    armaElegida = ITEM_ESCOPETA;
    bool exito = false;

    if (inventario->tieneEscopeta()) {
        if (inventario->tieneBalasSuficientes()) {
            exito = true;
        } else {
            error = SIN_BALAS_SUFICIENTES;
        }
    } else {
        error = NO_HAY_ESCOPETA_EN_INVENTARIO;
    }
    return exito;
}

void Humano::atacar(ITEM_ELEGIDO arma) {
    disminuirEnergia(energiaMinimaAtaque);
    inventario->disminuirElemento(ITEM_BALA); //Unica arma posible: Escopeta
}

void Humano::recibeAtaque(Ser *atacante, ITEM_ELEGIDO arma) {
    float vidaQuitada = 0;
    if (esHumanoSimple() && seDefiendeDelAtaque) {
        armadura++;
    }
    if (atacante->esVampiroGeneral() ) {
        if (atacante->esVampiro()) {
            vidaQuitada = atacante->obtenerFuerza() * proteccionArmaduraAtaque();
        } else if (atacante->esNosferatu()) {
            if (this->obtenerVida() <= 30 && !(esVanesa() && seDefiendeDelAtaque)) {
                convertidoVampiro = true;
            } else {
                vidaQuitada = atacante->obtenerFuerza() * proteccionArmaduraAtaque();
            }
        } else if (atacante->esVampirella()) {
            vidaQuitada = atacante->obtenerFuerza() * proteccionArmaduraAtaque();
            disminuirArmadura(1);

        }

    } else if (atacante->esZombi() && !convertidoZombi) {
        convertidoZombi = true;
    }
    if (!(esVanesa() && seDefiendeDelAtaque && atacante->esVampiroGeneral() ) ) {
        disminuirVida((int) vidaQuitada);
    }
    if (esHumanoSimple() && seDefiendeDelAtaque) {
        armadura--;
    }
    mostrarAtaqueRecibido(atacante, arma, vidaQuitada);
}

void Humano::mostrarAtaqueRecibido(Ser *atacante, ITEM_ELEGIDO arma, int vidaQuitada) {
    string nombreAtacado;
    if (esHumanoSimple()) {
        nombreAtacado = "l humano";
    } else if (esCazador()) {
        nombreAtacado = "l Cazador";
    } else {
        nombreAtacado = " Vanesa";
    }
    if (atacante->esVampiroGeneral() && esVanesa() && seDefiendeDelAtaque){
        cout << endl << "Has intentado atacar a Vanesa... pero ella se esta defendiendo"
             << endl << "con la cruz de Jesucristo. Perdiste tu tiempo!" << endl;
    } else if (convertidoZombi && !convertidoVampiro) {
        cout << endl << "El zombi ha mordido a" << nombreAtacado << "!" << endl;
        cout << endl << "En dos turnos se convertirá en un muerto viviente" << endl;
    } else if (convertidoVampiro) {
        cout << endl << "Nosferatu ha convertido a" << nombreAtacado << " en vampiro!" << endl;
        cout << endl << "Para cuando le llegue el turno a los humanos, ya se habrá convertido..!" << endl;
    }else if (vidaQuitada) {
        cout << "Con este ataque se le saca hasta " << vidaQuitada << " puntos de vida a" << nombreAtacado << ". "
             << endl;
    }
}

bool Humano::convertidoEnVampiro() {
    return convertidoVampiro;
}

bool Humano::convertidoEnZombi() {
    return convertidoZombi;
}

void Humano::esperarConversionZombi() {
    turnosConversionZombi++;
}

bool Humano::seConvierteEnZombiAhora() {
    return (convertidoZombi && turnosConversionZombi == 2);
}

void Humano::seEvitoLaConversionZombi() {
    convertidoZombi = false;
    turnosConversionZombi = 0;
}

void Humano::elegirDefensa() {
    cout << endl << "ELIJA UNA DEFENSA:" << endl;
    if (inventario->tieneAguaBendita()) {
        string input;
        cout << "1 - Agua Bendita: Se regenerará toda la vida" << endl;
        cout << "2 - Ninguna: +1 de armadura por 1 turno" << endl;
        cin >> input;
        int opcion = Utiles::ingresoValido(input, 1, 2);
        if (opcion == 1) {
            defensaElegida = DEFENSA_AGUA;
        } else {
            defensaElegida = DEFENSA_HUMANO_PUNTO_ARMADURA;
        }
    } else {
        cout << endl << "El humano ganó 3 de energía" << endl;
        defensaElegida = DEFENSA_NINGUN_ELEMENTO;
    }
}

float Humano::getPorcentajeAtaqueZombi() {
    return PORCENTAJE_ATAQUE_ZOMBI;
}

float Humano::getPorcentajeAtaqueVampiro() {
    return PORCENTAJE_ATAQUE_VAMPIRO;
}

void Humano::defender() {
    if (defensaElegida == DEFENSA_AGUA) {
        setVida(100);
        inventario->disminuirElemento(ITEM_AGUA_BENDITA);
        cout << "Se regeneró toda la vida de este humano, gastando su agua bendita" << endl;
    } else if (defensaElegida == DEFENSA_HUMANO_PUNTO_ARMADURA) {
        seDefiendeDelAtaque = true;
        cout << "El humano obtiene un punto de armadura extra en el próximo turno" << endl;
    } else {
        aumentarEnergia(3);
        cout << "Se le aumenta al humano hasta 3 de energía" << endl;
    }
}

Humano::~Humano() {
    cantidadHumanos--;

}

