#include "ImpresionesPantalla.h"

void ImpresionesPantalla::impresionJuego() {
    Gotoxy gotox;
    cout << gotox.pos(2, 35)<< "\n";
    cout << gotox.pos(3,35) << TXT_DARK_RED_52 <<"███╗   ██╗ ██████╗ ███████╗███████╗███████╗██████╗  █████╗ ████████╗██╗   ██╗\n"<< END_COLOR;
    cout << gotox.pos(4,35) << TXT_DARK_RED_52 <<"████╗  ██║██╔═══██╗██╔════╝██╔════╝██╔════╝██╔══██╗██╔══██╗╚══██╔══╝██║   ██║\n"<< END_COLOR;
    cout << gotox.pos(5,35) << TXT_DARK_RED_52 <<"██╔██╗ ██║██║   ██║███████╗█████╗  █████╗  ██████╔╝███████║   ██║   ██║   ██║\n"<< END_COLOR;
    cout << gotox.pos(6,35) << TXT_DARK_RED_52 <<"██║╚██╗██║██║   ██║╚════██║██╔══╝  ██╔══╝  ██╔══██╗██╔══██║   ██║   ██║   ██║\n"<< END_COLOR;
    cout << gotox.pos(7,35) << TXT_DARK_RED_52 <<"██║ ╚████║╚██████╔╝███████║██║     ███████╗██║  ██║██║  ██║   ██║   ╚██████╔╝\n"<< END_COLOR;
    cout << gotox.pos(8,35) << TXT_DARK_RED_52 <<"╚═╝  ╚═══╝ ╚═════╝ ╚══════╝╚═╝     ╚══════╝╚═╝  ╚═╝╚═╝  ╚═╝   ╚═╝    ╚═════╝ \n"<< END_COLOR;

    cout << gotox.pos(12, 50) <<TXT_LIGHT_GRAY_246<< "╔════════════════════════════════════════╗" << endl<< END_COLOR;
    cout << gotox.pos(13, 50) <<TXT_LIGHT_GRAY_246<< "║" << setfill(' ') << setw(43) << "║" << endl<< END_COLOR;
    cout << gotox.pos(14, 50) <<TXT_LIGHT_GRAY_246<< "║" << setfill(' ') << setw(43) << "║" << endl<< END_COLOR;
    cout << gotox.pos(15, 50) <<TXT_LIGHT_GRAY_246<< "║" << setfill(' ') << setw(43) << "║" << endl<< END_COLOR;
    cout << gotox.pos(16, 50) <<TXT_LIGHT_GRAY_246<< "║" << setfill(' ') << setw(43) << "║" << endl<< END_COLOR;
    cout << gotox.pos(17, 50) <<TXT_LIGHT_GRAY_246<< "║" << setfill(' ') << setw(43) << "║" << endl<< END_COLOR;
    cout << gotox.pos(18, 50) <<TXT_LIGHT_GRAY_246<< "║" << setfill(' ') << setw(43) << "║" << endl<< END_COLOR;
    cout << gotox.pos(19, 50) <<TXT_LIGHT_GRAY_246<< "║" << setfill(' ') << setw(43) << "║" << endl<< END_COLOR;
    cout << gotox.pos(20, 50) <<TXT_LIGHT_GRAY_246<< "║" << setfill(' ') << setw(43) << "║" << endl<< END_COLOR;
    cout << gotox.pos(21, 50) <<TXT_LIGHT_GRAY_246<< "║" << setfill(' ') << setw(43) << "║" << endl<< END_COLOR;
    cout << gotox.pos(22, 50) <<TXT_LIGHT_GRAY_246<< "║" << setfill(' ') << setw(43) << "║" << endl<< END_COLOR;
    cout << gotox.pos(23, 50) <<TXT_LIGHT_GRAY_246<< "║" << setfill(' ') << setw(43) << "║" << endl<< END_COLOR;
    cout << gotox.pos(24, 50) <<TXT_LIGHT_GRAY_246<< "╚════════════════════════════════════════╝" << endl<< END_COLOR;
    cout << gotox.pos(14, 51) << TXT_LIGHT_RED_9 << setfill(' ') << setw(23) << "OPCIONES" << END_COLOR;
    cout << gotox.pos(16, 51) << TXT_GREEN_2 << setfill(' ') << setw(23) << "1. Jugar"<< END_COLOR;
    cout << gotox.pos(18, 51) << TXT_BLUE_4 << setfill(' ') << setw(25) << "2. Créditos"<< END_COLOR;
    cout << gotox.pos(20, 51) << TXT_YELLOW_148 <<setfill(' ') << setw(23) << "3. Salir"<< END_COLOR;
    cout << gotox.pos(22, 55) << setfill(' ') << setw(19) << "Opción: ";
}

void ImpresionesPantalla::impresionCreditos() {
    Gotoxy gotox;
    impresionTituloCreditos();
    cout << gotox.pos(10, 50) << "╔════════════════════════════════════════╗" << endl;
    cout << gotox.pos(11, 50) << "║" << setfill(' ') << setw(43) << "║" << endl;
    cout << gotox.pos(12, 50) << "║" << setfill(' ') << setw(30) << "CREADO POR EL GRUPO UML" << setfill(' ') << setw(13) << "║" << endl;
    cout << gotox.pos(13, 50) << "║" << setfill(' ') << setw(43) << "║" << endl;
    cout << gotox.pos(14, 50) << "║" << setfill(' ') << setw(25) << "INTEGRANTES:" << setfill(' ') << setw(18) << "║" << endl;
    cout << gotox.pos(15, 50) << "║" << setfill(' ') << setw(43) << "║" << endl;
    cout << gotox.pos(16, 50) << "║" << setfill(' ') << setw(24) << "Lara Galvan" << setfill(' ') << setw(19) << "║" << endl;
    cout << gotox.pos(17, 50) << "║" << setfill(' ') << setw(27) << "Sebastian Makkos" << setfill(' ') << setw(16) << "║" << endl;
    cout << gotox.pos(18, 50) << "║" << setfill(' ') << setw(27) << "Daniela Palacios" << setfill(' ') << setw(16) << "║" << endl;
    cout << gotox.pos(19, 50) << "║" << setfill(' ') << setw(28) << "Gabriel Carniglia" << setfill(' ') << setw(15) << "║" << endl;
    cout << gotox.pos(20, 50) << "║" << setfill(' ') << setw(43) << "║" << endl;
    cout << gotox.pos(21, 50) << "╚════════════════════════════════════════╝" << endl;

}

void ImpresionesPantalla::impresionSalir() {
    Gotoxy gotox;
    cout << gotox.pos(10, 50) << "╔════════════════════════════════════════╗" << endl;
    cout << gotox.pos(11, 50) << "║" << setfill(' ') << setw(43) << "║" << endl;
    cout << gotox.pos(12, 50) << "║" << setfill(' ') << setw(30) << "Saliendo del juego..." << setfill(' ') << setw(13) << "║" << endl;
    cout << gotox.pos(13, 50) << "║" << setfill(' ') << setw(43) << "║" << endl;
    cout << gotox.pos(14, 50) << "║" << setfill(' ') << setw(25) << "Hasta luego" << setfill(' ') << setw(18) << "║" << endl;
    cout << gotox.pos(15, 50) << "║" << setfill(' ') << setw(43) << "║" << endl;
    cout << gotox.pos(16, 50) << "║" << setfill(' ') << setw(26) << "Vuelva Pronto" << setfill(' ') << setw(17) << "║" << endl;
    cout << gotox.pos(17, 50) << "║" << setfill(' ') << setw(43) << "║" << endl;
    cout << gotox.pos(18, 50) << "║" << setfill(' ') << setw(27) << "#QuedateEnCasa" << setfill(' ') << setw(16) << "║" << endl;
    cout << gotox.pos(19, 50) << "║" << setfill(' ') << setw(43) << "║" << endl;
    cout << gotox.pos(20, 50) << "║" << setfill(' ') << setw(43) << "║" << endl;
    cout << gotox.pos(21, 50) << "╚════════════════════════════════════════╝" << endl;
}

void ImpresionesPantalla::impresionTituloBusquedaCuadrante(){
    Gotoxy gotox;
    cout << gotox.pos(2, 2) << "\n";
    cout << gotox.pos(3, 2) << TXT_YELLOW_148 <<"██████  ██    ██ ███████  ██████  ██    ██ ███████ ██████   █████       ██████ ██    ██  █████  ██████  ██████   █████  ███    ██ ████████ ███████ \n"<< END_COLOR;
    cout << gotox.pos(4, 2) <<TXT_YELLOW_148 <<"██   ██ ██    ██ ██      ██    ██ ██    ██ ██      ██   ██ ██   ██     ██      ██    ██ ██   ██ ██   ██ ██   ██ ██   ██ ████   ██    ██    ██      \n"<< END_COLOR;
    cout << gotox.pos(5, 2) <<TXT_YELLOW_148 <<"██████  ██    ██ ███████ ██    ██ ██    ██ █████   ██   ██ ███████     ██      ██    ██ ███████ ██   ██ ██████  ███████ ██ ██  ██    ██    █████   \n"<< END_COLOR;
    cout << gotox.pos(6, 2) <<TXT_YELLOW_148 <<"██   ██ ██    ██      ██ ██ ▄▄ ██ ██    ██ ██      ██   ██ ██   ██     ██      ██    ██ ██   ██ ██   ██ ██   ██ ██   ██ ██  ██ ██    ██    ██      \n"<< END_COLOR;
    cout << gotox.pos(7, 2) <<TXT_YELLOW_148 <<"██████   ██████  ███████  ██████   ██████  ███████ ██████  ██   ██      ██████  ██████  ██   ██ ██████  ██   ██ ██   ██ ██   ████    ██    ███████ \n"<< END_COLOR;
    cout << gotox.pos(8, 2) <<TXT_YELLOW_148 <<"                             ▀▀                                                                                                                    \n"<< END_COLOR;
}

void ImpresionesPantalla::impresionTituloMenu() {
    Gotoxy gotox;
    cout << gotox.pos(2, 53) << "███    ███ ███████ ███    ██ ██    ██ \n";
    cout << gotox.pos(3, 53) << "████  ████ ██      ████   ██ ██    ██ \n";
    cout << gotox.pos(4, 53) << "██ ████ ██ █████   ██ ██  ██ ██    ██ \n";
    cout << gotox.pos(5, 53) << "██  ██  ██ ██      ██  ██ ██ ██    ██ \n";
    cout << gotox.pos(6, 53) << "██      ██ ███████ ██   ████  ██████  \n";
}

void ImpresionesPantalla::impresionTituloAltaObjeto() {
    Gotoxy gotox;
    cout << gotox.pos(4, 30)<<TXT_ORANGE_130<< " █████  ██      ████████  █████       ██████  ██████       ██ ███████ ████████  ██████  \n"<< END_COLOR;
    cout << gotox.pos(5, 30)<<TXT_ORANGE_130<< "██   ██ ██         ██    ██   ██     ██    ██ ██   ██      ██ ██         ██    ██    ██ \n"<< END_COLOR;
    cout << gotox.pos(6, 30)<< TXT_ORANGE_130<<"███████ ██         ██    ███████     ██    ██ ██████       ██ █████      ██    ██    ██ \n"<< END_COLOR;
    cout << gotox.pos(7, 30)<< TXT_ORANGE_130<<"██   ██ ██         ██    ██   ██     ██    ██ ██   ██ ██   ██ ██         ██    ██    ██ \n"<< END_COLOR;
    cout << gotox.pos(8, 30)<< TXT_ORANGE_130<<"██   ██ ███████    ██    ██   ██      ██████  ██████   █████  ███████    ██     ██████  \n"<< END_COLOR;
}

void ImpresionesPantalla::impresionTituloBajaObjeto() {
    Gotoxy gotox;
    cout << gotox.pos(4, 30) <<TXT_DARK_AQUA_23<< "██████   █████       ██  █████       ██████  ██████       ██ ███████ ████████  ██████  \n"<< END_COLOR;
    cout << gotox.pos(5, 30) <<TXT_DARK_AQUA_23<< "██   ██ ██   ██      ██ ██   ██     ██    ██ ██   ██      ██ ██         ██    ██    ██ \n"<< END_COLOR;
    cout << gotox.pos(6, 30) <<TXT_DARK_AQUA_23<< "██████  ███████      ██ ███████     ██    ██ ██████       ██ █████      ██    ██    ██ \n"<< END_COLOR;
    cout << gotox.pos(7, 30) <<TXT_DARK_AQUA_23<< "██   ██ ██   ██ ██   ██ ██   ██     ██    ██ ██   ██ ██   ██ ██         ██    ██    ██ \n"<< END_COLOR;
    cout << gotox.pos(8, 30) <<TXT_DARK_AQUA_23<< "██████  ██   ██  █████  ██   ██      ██████  ██████   █████  ███████    ██     ██████  \n"<< END_COLOR;
    cout << endl;
    cout << endl;
    cout << endl;
}

void ImpresionesPantalla::impresionTituloTablero(){
    Gotoxy gotox;
    cout <<gotox.pos(1, 20) << "████████ \n";
    cout <<gotox.pos(2, 20) << "   ██    \n";
    cout <<gotox.pos(3, 20) << "   ██    \n";
    cout <<gotox.pos(4, 20) << "   ██    \n";
    cout <<gotox.pos(5, 20) << "   ██    \n";

    cout <<gotox.pos(7, 20) <<TXT_LIGHT_YELLOW_149<< " █████  \n"<< END_COLOR;
    cout <<gotox.pos(8, 20) <<TXT_LIGHT_YELLOW_149<< "██   ██ \n"<< END_COLOR;
    cout <<gotox.pos(9, 20) <<TXT_LIGHT_YELLOW_149<< "███████ \n"<< END_COLOR;
    cout <<gotox.pos(10, 20) <<TXT_LIGHT_YELLOW_149<< "██   ██ \n"<< END_COLOR;
    cout <<gotox.pos(11, 20) <<TXT_LIGHT_YELLOW_149<< "██   ██ \n"<< END_COLOR;

    cout <<gotox.pos(13, 20) <<TXT_ORANGE_130<< "██████  \n"<< END_COLOR;
    cout <<gotox.pos(14, 20) <<TXT_ORANGE_130<<  "██   ██ \n"<< END_COLOR;
    cout <<gotox.pos(15, 20) <<TXT_ORANGE_130<<  "██████  \n"<< END_COLOR;
    cout <<gotox.pos(16, 20) <<TXT_ORANGE_130<<  "██   ██ \n"<< END_COLOR;
    cout <<gotox.pos(17, 20) <<TXT_ORANGE_130<<  "██████  \n"<< END_COLOR;

    cout <<gotox.pos(19, 20) <<TXT_PINK_161<< "██      \n"<< END_COLOR;
    cout <<gotox.pos(20, 20) <<TXT_PINK_161<< "██      \n"<< END_COLOR;
    cout <<gotox.pos(21, 20) <<TXT_PINK_161<< "██      \n"<< END_COLOR;
    cout <<gotox.pos(22, 20) <<TXT_PINK_161<< "██      \n"<< END_COLOR;
    cout <<gotox.pos(23, 20) <<TXT_PINK_161<< "███████ \n"<< END_COLOR;

    cout <<gotox.pos(25, 20) <<TXT_AQUA_35<< "███████ \n"<< END_COLOR;
    cout <<gotox.pos(26, 20) <<TXT_AQUA_35<< "██      \n"<< END_COLOR;
    cout <<gotox.pos(27, 20) <<TXT_AQUA_35<< "█████   \n"<< END_COLOR;
    cout <<gotox.pos(28, 20) <<TXT_AQUA_35<< "██      \n"<< END_COLOR;
    cout <<gotox.pos(29, 20) <<TXT_AQUA_35<< "███████ \n"<< END_COLOR;

    cout <<gotox.pos(31, 20) <<TXT_LIGHT_BLUE_6<< "██████  \n"<< END_COLOR;
    cout <<gotox.pos(32, 20) <<TXT_LIGHT_BLUE_6<< "██   ██ \n"<< END_COLOR;
    cout <<gotox.pos(33, 20) <<TXT_LIGHT_BLUE_6<< "██████  \n"<< END_COLOR;
    cout <<gotox.pos(34, 20) <<TXT_LIGHT_BLUE_6<< "██   ██ \n"<< END_COLOR;
    cout <<gotox.pos(35, 20) <<TXT_LIGHT_BLUE_6<< "██   ██ \n"<< END_COLOR;

    cout <<gotox.pos(37, 20) <<TXT_RED_124<< " ██████  \n"<< END_COLOR;
    cout <<gotox.pos(38, 20) <<TXT_RED_124<< "██    ██ \n"<< END_COLOR;
    cout <<gotox.pos(39, 20) <<TXT_RED_124<< "██    ██ \n"<< END_COLOR;
    cout <<gotox.pos(40, 20) <<TXT_RED_124<< "██    ██ \n"<< END_COLOR;
    cout <<gotox.pos(41, 20) <<TXT_RED_124<< " ██████  \n"<< END_COLOR;

}

void ImpresionesPantalla::impresionTituloBusquedaID() {
    Gotoxy gotox;

    cout << gotox.pos(4, 35) <<TXT_LIGHT_AQUA_41<<"██████  ██    ██ ███████  ██████  ██    ██ ███████ ██████   █████      ██ ██████  \n"<< END_COLOR;
    cout << gotox.pos(5, 35) <<TXT_LIGHT_AQUA_41<<"██   ██ ██    ██ ██      ██    ██ ██    ██ ██      ██   ██ ██   ██     ██ ██   ██ \n"<< END_COLOR;
    cout << gotox.pos(6, 35) <<TXT_LIGHT_AQUA_41<<"██████  ██    ██ ███████ ██    ██ ██    ██ █████   ██   ██ ███████     ██ ██   ██ \n"<< END_COLOR;
    cout << gotox.pos(7, 35) <<TXT_LIGHT_AQUA_41<<"██   ██ ██    ██      ██ ██ ▄▄ ██ ██    ██ ██      ██   ██ ██   ██     ██ ██   ██ \n"<< END_COLOR;
    cout << gotox.pos(8, 35) <<TXT_LIGHT_AQUA_41<<"██████   ██████  ███████  ██████   ██████  ███████ ██████  ██   ██     ██ ██████  \n"<< END_COLOR;
    cout << gotox.pos(9, 35) <<TXT_LIGHT_AQUA_41<<"                             ▀▀                                                   \n"<< END_COLOR;
    cout << endl;
}

void ImpresionesPantalla::impresionTituloCreditos() {
    Gotoxy gotox;
    cout << gotox.pos(4, 40) <<TXT_PURPLE_5<<" ██████ ██████  ███████ ██████  ██ ████████  ██████  ███████ \n"<< END_COLOR;
    cout << gotox.pos(5, 40) <<TXT_PURPLE_5<<"██      ██   ██ ██      ██   ██ ██    ██    ██    ██ ██      \n"<< END_COLOR;
    cout << gotox.pos(6, 40) <<TXT_PURPLE_5<<"██      ██████  █████   ██   ██ ██    ██    ██    ██ ███████ \n"<< END_COLOR;
    cout << gotox.pos(7, 40) <<TXT_PURPLE_5<<"██      ██   ██ ██      ██   ██ ██    ██    ██    ██      ██ \n"<< END_COLOR;
    cout << gotox.pos(8, 40) <<TXT_PURPLE_5<<" ██████ ██   ██ ███████ ██████  ██    ██     ██████  ███████ \n"<< END_COLOR;
}

void ImpresionesPantalla::impresionCoordenadas(int alto, int ancho) {
    Gotoxy gotox;
    int fila = 1;
    int columna = 1;
    int i, j;
    for(i= 6; fila <= alto; i+=2 ){
        cout << gotox.pos(i, 57) << fila;
        fila++;
    }
    for(j = 62; columna <= ancho; j+=6){
        cout << gotox.pos(4, j) << columna;
        columna++;

    }

}


void ImpresionesPantalla::impresionGameOver(){
    Gotoxy gotox;
    cout <<gotox.pos(20, 40)  <<"  ▄████  ▄▄▄       ███▄ ▄███▓▓█████     ▒█████   ██▒   █▓▓█████  ██▀███  \n";
    cout <<gotox.pos(21, 40)  <<" ██▒ ▀█▒▒████▄    ▓██▒▀█▀ ██▒▓█   ▀    ▒██▒  ██▒▓██░   █▒▓█   ▀ ▓██ ▒ ██▒\n";
    cout <<gotox.pos(22, 40)  <<"▒██░▄▄▄░▒██  ▀█▄  ▓██    ▓██░▒███      ▒██░  ██▒ ▓██  █▒░▒███   ▓██ ░▄█ ▒\n";
    cout <<gotox.pos(23, 40)  <<"░▓█  ██▓░██▄▄▄▄██ ▒██    ▒██ ▒▓█  ▄    ▒██   ██░  ▒██ █░░▒▓█  ▄ ▒██▀▀█▄  \n";
    cout <<gotox.pos(24, 40)  <<"░▒▓███▀▒ ▓█   ▓██▒▒██▒   ░██▒░▒████▒   ░ ████▓▒░   ▒▀█░  ░▒████▒░██▓ ▒██▒\n";
    cout <<gotox.pos(25, 40)  <<" ░▒   ▒  ▒▒   ▓▒█░░ ▒░   ░  ░░░ ▒░ ░   ░ ▒░▒░▒░    ░ ▐░  ░░ ▒░ ░░ ▒▓ ░▒▓░\n";
    cout <<gotox.pos(26, 40)  <<"  ░   ░   ▒   ▒▒ ░░  ░      ░ ░ ░  ░     ░ ▒ ▒░    ░ ░░   ░ ░  ░  ░▒ ░ ▒░\n";
    cout <<gotox.pos(27, 40)  <<"░ ░   ░   ░   ▒   ░      ░      ░      ░ ░ ░ ▒       ░░     ░     ░░   ░ \n";
    cout <<gotox.pos(28, 40)  <<"      ░       ░  ░       ░      ░  ░       ░ ░        ░     ░  ░   ░     \n";
    cout <<gotox.pos(29, 40)  <<"                                                     ░                   ";
}

void ImpresionesPantalla::impresionOpcionesObjetos() {
    Gotoxy gotox;

    cout << gotox.pos(12, 50) << "╔════════════════════════════════════════╗" << endl;
    cout << gotox.pos(13, 50) << "║" << setfill(' ') << setw(43) << "║" << endl;
    cout << gotox.pos(14, 50) << "║" << setfill(' ') << setw(43) << "║" << endl;
    cout << gotox.pos(15, 50) << "║" << setfill(' ') << setw(43) << "║" << endl;
    cout << gotox.pos(16, 50) << "║" << setfill(' ') << setw(43) << "║" << endl;
    cout << gotox.pos(17, 50) << "║" << setfill(' ') << setw(43) << "║" << endl;
    cout << gotox.pos(18, 50) << "║" << setfill(' ') << setw(43) << "║" << endl;
    cout << gotox.pos(19, 50) << "║" << setfill(' ') << setw(43) << "║" << endl;
    cout << gotox.pos(20, 50) << "║" << setfill(' ') << setw(43) << "║" << endl;
    cout << gotox.pos(21, 50) << "║" << setfill(' ') << setw(43) << "║" << endl;
    cout << gotox.pos(22, 50) << "║" << setfill(' ') << setw(43) << "║" << endl;
    cout << gotox.pos(23, 50) << "║" << setfill(' ') << setw(43) << "║" << endl;
    cout << gotox.pos(24, 50) << "║" << setfill(' ') << setw(43) << "║" << endl;
    cout << gotox.pos(25, 50) << "║" << setfill(' ') << setw(43) << "║" << endl;
    cout << gotox.pos(26, 50) << "║" << setfill(' ') << setw(43) << "║" << endl;

    cout << gotox.pos(14, 54) << setfill(' ') << setw(23) << "1. humano";
    cout << gotox.pos(15, 54) << setfill(' ') << setw(23) << "2. Cazador";
    cout << gotox.pos(16, 54) << setfill(' ') << setw(23) << "3. Vanesa";
    cout << gotox.pos(17, 54) << setfill(' ') << setw(23) << "4. Vampirella";
    cout << gotox.pos(18, 54) << setfill(' ') << setw(23) << "5. Vampiro";
    cout << gotox.pos(19, 54) << setfill(' ') << setw(23) << "6. Nosferatu";
    cout << gotox.pos(20, 54) << setfill(' ') << setw(23) << "7. Zombi";
    cout << gotox.pos(21, 54) << setfill(' ') << setw(23) << "8. Agua";
    cout << gotox.pos(22, 54) << setfill(' ') << setw(23) << "9. Balas";
    cout << gotox.pos(23, 54) << setfill(' ') << setw(23) << "10. Estaca";
    cout << gotox.pos(24, 54) << setfill(' ') << setw(23) << "11. Escopeta";
    cout << gotox.pos(25, 54) << setfill(' ') << setw(23) << "12. Cruz";
    cout << gotox.pos(27, 50) << "╚════════════════════════════════════════╝" << endl;


}
void ImpresionesPantalla::impresionBotonContinuar(){
    Gotoxy gotox;
    string continuar;
    cout << gotox.pos(32, 50) << "PRESIONE ENTER PARA CONTINUAR..";
    cin.get();
    cin.get();
}


void ImpresionesPantalla::impresionOpcionesCuadrante() {

    Gotoxy gotox;

    cout << gotox.pos(10, 50) << "╔════════════════════════════════════════╗" << endl;
    cout << gotox.pos(11, 50) << "║" << setfill(' ') << setw(43) << "║" << endl;
    cout << gotox.pos(12, 50) << "║" << setfill(' ') << setw(43) << "║" << endl;
    cout << gotox.pos(13, 50) << "║" << setfill(' ') << setw(43) << "║" << endl;
    cout << gotox.pos(14, 50) << "║" << setfill(' ') << setw(43) << "║" << endl;
    cout << gotox.pos(15, 50) << "║" << setfill(' ') << setw(43) << "║" << endl;
    cout << gotox.pos(16, 50) << "║" << setfill(' ') << setw(43) << "║" << endl;
    cout << gotox.pos(17, 50) << "║" << setfill(' ') << setw(43) << "║" << endl;
    cout << gotox.pos(12, 58) << "1. NO";
    cout << gotox.pos(12, 78) << "3. NE";
    cout << gotox.pos(16, 58) << "2. SO";
    cout << gotox.pos(16, 78) <<"4. SE";
    cout << gotox.pos(18, 50) << "╚════════════════════════════════════════╝" << endl;

}
void ImpresionesPantalla::referenciasTablero(){
    Gotoxy gotox;
    cout << gotox.pos(30, 88) << "COLORES DE CASILLEROS";
    cout << gotox.pos(32, 88) << "VOLCÁN " << BGND_DARK_RED_88 << "  "<< END_COLOR;
    cout << gotox.pos(32, 105) << "LAGO " << BGND_BLUE_4 << "  "<< END_COLOR;
    cout << gotox.pos(34, 88) << "PRECIPICIO " << BGND_LIGHT_GRAY_246 << "  "<< END_COLOR;
    cout << gotox.pos(34, 105) << "MONTAÑA " <<  BGND_BROWN_94 << "  "<< END_COLOR;
    cout << gotox.pos(36, 88) << "CAMINO " << BGND_GRAY_241 << "  "<< END_COLOR;
    cout << gotox.pos(36, 105) << "VACIO " << BGND_DARK_PURPLE_53 << "  "<< END_COLOR;

    cout << gotox.pos(25, 118) << "REFERENCIAS OBJETOS";
    cout << gotox.pos(26, 118) << "N: Nosferatu";
    cout << gotox.pos(27, 118) << "V: Vanesa";
    cout << gotox.pos(28, 118) << "z: Zombi";
    cout << gotox.pos(29, 118) << "v: Vampiro";
    cout << gotox.pos(30, 118) << "h: Humano";
    cout << gotox.pos(31, 118) << "H: Cazador";
    cout << gotox.pos(32, 118) << "W: Vanesa";
    cout << gotox.pos(33, 118) << "A: Agua Bendita";
    cout << gotox.pos(34, 118) << "b: Balas";
    cout << gotox.pos(35, 118) << "e: Estaca";
    cout << gotox.pos(36, 118) << "E: Escopeta";
    cout << gotox.pos(37, 118) << "C: Cruz";

}

void ImpresionesPantalla::imprimirMenuJuego() {
    Gotoxy gotox;
    impresionTituloMenu();
    cout << gotox.pos(8, 50) << "╔════════════════════════════════════════╗" << endl;
    cout << gotox.pos(9, 50) << "║" << setfill(' ') << setw(43) << "║" << endl;
    cout << gotox.pos(10, 50) << "║" << setfill(' ') << setw(43) << "║" << endl;
    cout << gotox.pos(11, 50) << "║" << setfill(' ') << setw(43) << "║" << endl;
    cout << gotox.pos(12, 50) << "║" << setfill(' ') << setw(43) << "║" << endl;
    cout << gotox.pos(13, 50) << "║" << setfill(' ') << setw(43) << "║" << endl;
    cout << gotox.pos(14, 50) << "║" << setfill(' ') << setw(43) << "║" << endl;
    cout << gotox.pos(15, 50) << "║" << setfill(' ') << setw(43) << "║" << endl;
    cout << gotox.pos(16, 50) << "║" << setfill(' ') << setw(43) << "║" << endl;
    cout << gotox.pos(17, 50) << "║" << setfill(' ') << setw(43) << "║" << endl;
    cout << gotox.pos(18, 50) << "║" << setfill(' ') << setw(43) << "║" << endl;
    cout << gotox.pos(19, 50) << "║" << setfill(' ') << setw(43) << "║" << endl;
    cout << gotox.pos(20, 50) << "║" << setfill(' ') << setw(43) << "║" << endl;
    cout << gotox.pos(21, 50) << "║" << setfill(' ') << setw(43) << "║" << endl;
    cout << gotox.pos(22, 50) << "║" << setfill(' ') << setw(43) << "║" << endl;
    cout << gotox.pos(23, 50) << "║" << setfill(' ') << setw(43) << "║" << endl;
    cout << gotox.pos(24, 50) << "║" << setfill(' ') << setw(43) << "║" << endl;
    cout << gotox.pos(25, 50) << "║" << setfill(' ') << setw(43) << "║" << endl;
    cout << gotox.pos(26, 50) << "║" << setfill(' ') << setw(43) << "║" << endl;
    cout << gotox.pos(27, 50) << "╚════════════════════════════════════════╝" << endl;

    cout << gotox.pos(11, 59) << setfill(' ') << setw(23) << "1. Dar de alta un objeto";
    cout << gotox.pos(13, 59) << setfill(' ') << setw(23) << "2. Dar de baja un objeto";
    cout << gotox.pos(15, 58) << setfill(' ') << setw(23) << "3. Mostrar Tablero";
    cout << gotox.pos(17, 59) << setfill(' ') << setw(23) << "4. Buscar por cuadrante";
    cout << gotox.pos(19, 55) << setfill(' ') << setw(23) << "5. Buscar por ID";
    cout << gotox.pos(21, 54) << setfill(' ') << setw(23) << "6. Simulacion";
    cout << gotox.pos(23, 52) << setfill(' ') << setw(23) << "7. Salir";
    cout << gotox.pos(25, 51) << setfill(' ') << setw(23) << "OPCION: ";
}

void ImpresionesPantalla::impresionMenuSimulacion() {
    Gotoxy gotox;
    impresionTituloMenu();
    cout << gotox.pos(8, 50) << "╔════════════════════════════════════════╗" << endl;
    cout << gotox.pos(9, 50) << "║" << setfill(' ') << setw(43) << "║" << endl;
    cout << gotox.pos(10, 50) << "║" << setfill(' ') << setw(43) << "║" << endl;
    cout << gotox.pos(11, 50) << "║" << setfill(' ') << setw(43) << "║" << endl;
    cout << gotox.pos(12, 50) << "║" << setfill(' ') << setw(43) << "║" << endl;
    cout << gotox.pos(13, 50) << "║" << setfill(' ') << setw(43) << "║" << endl;
    cout << gotox.pos(14, 50) << "║" << setfill(' ') << setw(43) << "║" << endl;
    cout << gotox.pos(15, 50) << "║" << setfill(' ') << setw(43) << "║" << endl;
    cout << gotox.pos(16, 50) << "║" << setfill(' ') << setw(43) << "║" << endl;
    cout << gotox.pos(17, 50) << "║" << setfill(' ') << setw(43) << "║" << endl;
    cout << gotox.pos(18, 50) << "║" << setfill(' ') << setw(43) << "║" << endl;
    cout << gotox.pos(19, 50) << "║" << setfill(' ') << setw(43) << "║" << endl;
    cout << gotox.pos(20, 50) << "║" << setfill(' ') << setw(43) << "║" << endl;
    cout << gotox.pos(21, 50) << "║" << setfill(' ') << setw(43) << "║" << endl;
    cout << gotox.pos(22, 50) << "║" << setfill(' ') << setw(43) << "║" << endl;
    cout << gotox.pos(23, 50) << "║" << setfill(' ') << setw(43) << "║" << endl;
    cout << gotox.pos(24, 50) << "╚════════════════════════════════════════╝" << endl;


    cout << gotox.pos(11, 55) << setfill(' ') << setw(23) << "1. Buscar por ID";
    cout << gotox.pos(13, 57) << setfill(' ') << setw(23) << "2. Mostrar Tablero";
    cout << gotox.pos(15, 55) << setfill(' ') << setw(23) << "3. Mostrar cantidad integrantes";
    cout << gotox.pos(16, 54) << setfill(' ') << setw(23) << "por bando";
    cout << gotox.pos(18, 59) << setfill(' ') << setw(23) << "4. Seleccionar Bando";
    cout << gotox.pos(20, 52) << setfill(' ') << setw(23) << "5. Salir";
    cout << gotox.pos(22, 51) << setfill(' ') << setw(23) << "OPCION: ";
}

void ImpresionesPantalla::impresionMostrarCantidadBando(int humanos, int monstruos) {
    Gotoxy gotox;


    cout << gotox.pos(2, 15) << " ██████  █████  ███    ██ ████████ ██ ██████   █████  ██████      ██████   █████  ███    ██ ██████   ██████  \n";
    cout << gotox.pos(3, 15) << "██      ██   ██ ████   ██    ██    ██ ██   ██ ██   ██ ██   ██     ██   ██ ██   ██ ████   ██ ██   ██ ██    ██ \n";
    cout << gotox.pos(4, 15) << "██      ███████ ██ ██  ██    ██    ██ ██   ██ ███████ ██   ██     ██████  ███████ ██ ██  ██ ██   ██ ██    ██ \n";
    cout << gotox.pos(5, 15) << "██      ██   ██ ██  ██ ██    ██    ██ ██   ██ ██   ██ ██   ██     ██   ██ ██   ██ ██  ██ ██ ██   ██ ██    ██ \n";
    cout << gotox.pos(6, 15) << " ██████ ██   ██ ██   ████    ██    ██ ██████  ██   ██ ██████      ██████  ██   ██ ██   ████ ██████   ██████  \n";
    cout << gotox.pos(10, 25) << "╔════════════════════════════════════════╗" << endl;
    cout << gotox.pos(11, 25) << "║" << setfill(' ') << setw(43) << "║" << endl;
    cout << gotox.pos(12, 25) << "║" << setfill(' ') << setw(43) << "║" << endl;
    cout << gotox.pos(13, 25) << "║" << setfill(' ') << setw(43) << "║" << endl;
    cout << gotox.pos(14, 25) << "║" << setfill(' ') << setw(43) << "║" << endl;
    cout << gotox.pos(15, 25) << "╚════════════════════════════════════════╝" << endl;
    cout << gotox.pos(10, 75) << "╔════════════════════════════════════════╗" << endl;
    cout << gotox.pos(11, 75) << "║" << setfill(' ') << setw(43) << "║" << endl;
    cout << gotox.pos(12, 75) << "║" << setfill(' ') << setw(43) << "║" << endl;
    cout << gotox.pos(13, 75) << "║" << setfill(' ') << setw(43) << "║" << endl;
    cout << gotox.pos(14, 75) << "║" << setfill(' ') << setw(43) << "║" << endl;
    cout << gotox.pos(15, 75) << "╚════════════════════════════════════════╝" << endl;

    cout << gotox.pos(12, 42) <<"HUMANOS";
    cout << gotox.pos(13, 45) << humanos;

    cout << gotox.pos(12, 91) <<"MONSTRUOS";
    cout << gotox.pos(13, 95) << monstruos;

    cout << endl;
    cout << endl;
}
