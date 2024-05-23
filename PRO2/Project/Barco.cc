#include "Barco.hh"

Barco::Barco() {
    producto_a_comprar = -1;
    producto_a_vender = -1;

    unidades_a_comprar = -1;
    unidades_a_vender = -1;

    ultima_ciudad_viaje.clear();

    ini = false;
}

Barco::Barco(int producto_a_comprar, int producto_a_vender, int unidades_a_comprar, int unidades_a_vender) {
    this->producto_a_comprar = producto_a_comprar;
    this->producto_a_vender = producto_a_vender;

    this->unidades_a_comprar = unidades_a_comprar;
    this->unidades_a_vender = unidades_a_vender;

    ultima_ciudad_viaje.clear();

    ini = true;
}

void Barco::modificar_barco(int producto_a_comprar, int producto_a_vender, int unidades_a_comprar, int unidades_a_vender) {
    this->producto_a_comprar = producto_a_comprar;
    this->producto_a_vender = producto_a_vender;

    this->unidades_a_comprar = unidades_a_comprar;
    this->unidades_a_vender = unidades_a_vender;
}

void Barco::escribir_barco() const {

    if(not ini) {
        return;
    }

    cout << producto_a_comprar << ' ' << unidades_a_comprar << ' ' << producto_a_vender << ' ' << unidades_a_vender << endl;

    for(auto it = ultima_ciudad_viaje.begin(); it != ultima_ciudad_viaje.end(); ++it) {
        cout << *it << endl;
    }
}

void Barco::hacer_viaje(const BinTree<string>& mapa_rio, map<string, Ciudad>& lista_ciudades, vector<Producto>& lista_productos) {

    int unidades_comprar_barco = unidades_a_comprar;
    int unidades_vender_barco = unidades_a_vender;

    BinTree<InfoNodo> travelled_tree = travelled_tree_rec(mapa_rio, lista_ciudades, unidades_comprar_barco, unidades_vender_barco);

    string last_city = "";

    travel_tree(travelled_tree, mapa_rio, lista_ciudades, last_city, lista_productos);

    //BinTree<int> mod_tree = change_tree(travelled_tree);

    //mod_tree.setOutputFormat(BinTree<InfoNodo>::VISUALFORMAT);
    //cout << mod_tree << endl;

    if(last_city != "") ultima_ciudad_viaje.push_back(last_city);

    int total = 0;

    if(not travelled_tree.empty()) {
        total = travelled_tree.value().total();
    }

    cout << total << endl;
}

BinTree<InfoNodo> Barco::travelled_tree_rec(const BinTree<string>& mapa_rio, map<string, Ciudad>& lista_ciudades, int unidades_comprar_barco, int unidades_vender_barco) {
    //Base case
    InfoNodo node = InfoNodo();

    if(mapa_rio.empty() or (unidades_comprar_barco <= 0 and unidades_vender_barco <= 0)) {
        return BinTree<InfoNodo> (InfoNodo(), BinTree<InfoNodo>(), BinTree<InfoNodo>());
    }

    string id_ciudad = mapa_rio.value();
    auto it = lista_ciudades.find(id_ciudad);

    node.compra = 0;
    node.venta = 0;

    if(it->second.contiene_producto_ciudad(producto_a_comprar)) {
        int cantidad_vender = it->second.exceso(producto_a_comprar);
        
        //La ciudad quiere vender este producto.
        if(cantidad_vender > 0) {
            int cantidad = min(cantidad_vender, unidades_comprar_barco);

            node.venta = cantidad;
            node.total_venta += cantidad;
            unidades_comprar_barco -= cantidad;
        }
    }

    if(it->second.contiene_producto_ciudad(producto_a_vender)) {
        int cantidad_comprar = it->second.exceso(producto_a_vender);

        if(cantidad_comprar < 0) {
            int cantidad = min(abs(cantidad_comprar), unidades_vender_barco);

            node.compra = cantidad;
            node.total_compra += cantidad;
            unidades_vender_barco -= cantidad;
        }
    }

    auto tleft = travelled_tree_rec(mapa_rio.left(), lista_ciudades, unidades_comprar_barco, unidades_vender_barco);
    auto tright = travelled_tree_rec(mapa_rio.right(), lista_ciudades, unidades_comprar_barco, unidades_vender_barco);

    int totalleft = 0, totalright = 0;

    if(not tleft.empty()) {
        totalleft = tleft.value().total();
    }

    if(not tright.empty()) {
        totalright = tright.value().total();
    }

    if(totalleft > totalright) {

        node.altura += tleft.value().altura + 1;
        node.total_compra += tleft.value().total_compra;
        node.total_venta += tleft.value().total_venta;

        return BinTree<InfoNodo> (node, tleft, tright);
    }
    else if(totalleft < totalright) {
        node.altura += tright.value().altura + 1;
        node.total_compra += tright.value().total_compra;
        node.total_venta += tright.value().total_venta;

        return BinTree<InfoNodo> (node, tleft, tright);
    }
    else {
        
        node.altura += min(tleft.value().altura, tright.value().altura) + 1;

        if(tleft.value().altura > tright.value().altura) {
            node.total_compra += tright.value().total_compra;
            node.total_venta += tright.value().total_venta;

            return BinTree<InfoNodo> (node, tleft, tright);
        }
        else {
            node.total_compra += tleft.value().total_compra;
            node.total_venta += tleft.value().total_venta;

            return BinTree<InfoNodo> (node, tleft, tright);
        }
    }
}

void Barco::travel_tree(const BinTree<InfoNodo>& travelled_tree, const BinTree<string>& mapa_rio, map<string, Ciudad>& lista_ciudades, string& last_city, vector<Producto>& lista_productos) {
    //Base case
    if(travelled_tree.empty() or mapa_rio.empty()) return;

    string id_ciudad = mapa_rio.value();

    if(travelled_tree.value().venta > 0 and unidades_a_comprar > 0) {

        lista_ciudades[id_ciudad].reduccion(producto_a_comprar, travelled_tree.value().venta, lista_productos[producto_a_comprar - 1]);

        last_city = id_ciudad;
    }

    if(travelled_tree.value().compra > 0 and unidades_a_vender > 0) {

        lista_ciudades[id_ciudad].adquisicion(producto_a_vender, travelled_tree.value().compra, lista_productos[producto_a_vender - 1]);

        last_city = id_ciudad;
    }


    if(not travelled_tree.left().empty() and not travelled_tree.right().empty()) {
        
        if(travelled_tree.left().value().total() < travelled_tree.right().value().total()) {
            travel_tree(travelled_tree.right(), mapa_rio.right(), lista_ciudades, last_city, lista_productos);
        }
        else if(travelled_tree.left().value().total() > travelled_tree.right().value().total()) {
            travel_tree(travelled_tree.left(), mapa_rio.left(), lista_ciudades, last_city, lista_productos);
        }
        else {
            if(travelled_tree.left().value().altura > travelled_tree.right().value().altura) {
                travel_tree(travelled_tree.right(), mapa_rio.right(), lista_ciudades, last_city, lista_productos);
            }
            else {
                travel_tree(travelled_tree.left(), mapa_rio.left(), lista_ciudades, last_city, lista_productos);
            }
        }
    }
    return;
}

void Barco::clear_travel() {
    ultima_ciudad_viaje.clear();
}

void Barco::modify_list(string last_city) {
    ultima_ciudad_viaje.push_back(last_city);
}

int Barco::prod_comprar() {
    return producto_a_comprar;
}

int Barco::prod_vender() {
    return producto_a_vender;
}

int Barco::un_comprar() {
    return unidades_a_comprar;
}

int Barco::un_vender() {
    return unidades_a_vender;
}

bool Barco::inicializado() {
    return ini;
}