/** @file Barco.hh
    @brief Especificación de la clase Barco 
*/

#ifndef _BARCO_HH_
#define _BARCO_HH_

#ifndef NO_DIAGRAM
#include <iostream>
#include "Producto.hh"
#include <map>
#include <list>
#include <vector>
#endif

/*The boat is the object that allows commerce between two cities. The boat will contain an additional inventory, with its own products, 
such that it is allows to purchase and sell two DIFFERENT products.*/

class Barco {
    private:

        int producto_a_comprar;
        double unidades_a_comprar;

        int producto_a_vender;
        double unidades_a_vender;

        int num_viajes;
        vector<string> ultima_ciudad_viaje;

        string ciudad_anterior;

    public:
        Barco();

        Barco(int producto_a_comprar, int producto_a_vender, double unidades_a_comprar, double unidades_a_vender);

        void escribir_barco() const;

        //Modificar los datos de un barco
        //Escribir los datos del barco
};
#endif