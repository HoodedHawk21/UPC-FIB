#include "Producto.hh"
#include "Productos.hh"
#include <map>

/*The boat is the object that allows commerce between two cities. The boat will contain an additional inventory, with its own products, 
such that it is allows to purchase and sell two DIFFERENT products.*/

class Barco {
    private:
        list<Producto> inventario_barco = list<Producto> ();
        int num_viajes = 0;
        //inventario: lista de productos que tiene a disposicion el barco;
        //Numero de viajes

    public:
        //Setters and getters
        void modificar_barco(/*argumentos*/) {
            //To do
        }

        void escribir_barco(/*agrumentos*/) {
            //To do
        }
        //Modificar los datos de un barco
        //Escribir los datos del barco
};