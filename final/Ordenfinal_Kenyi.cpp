#include <iostream>
#include <iomanip> // para usar setw()
#include <string>
#include <vector>
#include <algorithm> // para usar min() y max()
#include <fstream>   // para usar ofstream

using namespace std;

enum class TipoUnidad{ Terrestre, Aereo };
enum class TamanioUnidad { Pequeno, Mediano, Grande };
enum class TipoDanoAereo{ Normal, Explosivo, Contusivo};
enum class TipoDanoTerrestre { Normal, Explosivo, Contusivo};
enum class Raza { Terran, Protos, Zerg};

// Sobrecarga de operadores para imprimir los enumeradores
ostream &operator<<(std::ostream &out, const TamanioUnidad value)
{
    switch (value)
    {
    case TamanioUnidad::Pequeno:
        out << "Pequeno";
        break;
    case TamanioUnidad::Mediano:
        out << "Mediano";
        break;
    case TamanioUnidad::Grande:
        out << "Grande";
        break;
    }
    return out;
}
ostream &operator<<(std::ostream &out, const TipoUnidad value)
{
    switch (value)
    {
    case TipoUnidad::Terrestre:
        out << "Terrestre";
        break;
    case TipoUnidad::Aereo:
        out << "Aereo";
        break;
    }
    return out;
}

class CUnidad
{
protected:
    string _nombre;
    double _vida;
    int _blindaje;
    int _danoTerrestre;
    TipoDanoTerrestre _tipoDanoTerrestre;
    int _danoAereo;
    TipoDanoAereo _tipoDanoAereo;
    TamanioUnidad _tamanio;
    TipoUnidad _tipo;
    Raza _raza;
public:
    //  Constructor con guion bajo
    CUnidad(string nombre, int vida, int blindaje, int danoTerrestre, TipoDanoTerrestre tipoDanoTerrestre, int danoAereo, TipoDanoAereo tipoDanoAereo, TamanioUnidad tamanio, TipoUnidad tipo, Raza raza)
        : _nombre(nombre), _vida(vida), _blindaje(blindaje), _danoTerrestre(danoTerrestre), _tipoDanoTerrestre(tipoDanoTerrestre), _danoAereo(danoAereo), _tipoDanoAereo(tipoDanoAereo), _tamanio(tamanio), _tipo(tipo), _raza(raza) {}

    // Todos los getters para imprimir la tabla de datos
    string getNombre() { return _nombre; }
    int getVida() { return _vida; }
    int getBlindaje() { return _blindaje; }
    int getDanoTerrestre() { return _danoTerrestre; }
    TipoDanoTerrestre getTipoDanoTerrestre() { return _tipoDanoTerrestre; }
    int getDanoAereo() { return _danoAereo; }
    TipoDanoAereo getTipoDanoAereo() { return _tipoDanoAereo; }
    TamanioUnidad getTamanio() { return _tamanio; }
    TipoUnidad getTipo() { return _tipo; }
    Raza getRaza() { return _raza; }
    // seters para poder actualizar la vida
    void setVida(int vida) { _vida = vida; }
    void setRaza(Raza raza) { _raza = raza; }

    void setDanoTerrestre(int danoTerrestre) { _danoTerrestre = danoTerrestre; }
    void setDanoAereo(int danoAereo) { _danoAereo = danoAereo; }

    // Destructor
    virtual ~CUnidad() {} // declaranndo aquim, ya no es necesario declarar en cada clase
};
// Los puntos de blindaje, le restan en % al dano de ataque. Inlcusive, le restan si este previamente ha sido mutiplicado por los factores de la matriz especial
class CTerran : public CUnidad
{
public:
    CTerran(string nombre, int vida, int blindaje, int danoTerrestre, TipoDanoTerrestre tipoDano_Terrestre, int danoAereo, TipoDanoAereo tipoDano_Aereo, TamanioUnidad tamanio, TipoUnidad tipo)
        : CUnidad(nombre, vida, blindaje, danoTerrestre, tipoDano_Terrestre, danoAereo, tipoDano_Aereo, tamanio, tipo, Raza::Terran) {}

    // destructor
    ~CTerran() {}
};

class CProtos : public CUnidad
{
private:
    double _escudo;

public:
    // Constructor de protos guion bajo
    CProtos(string nombre, int vida, int blindaje, int danoTerrestre, TipoDanoTerrestre tipoDanoTerrestre, int danoAereo, TipoDanoAereo tipoDanoAereo, TamanioUnidad tamanio, TipoUnidad tipo, int escudo)
        : CUnidad(nombre, vida, blindaje, danoTerrestre, tipoDanoTerrestre, danoAereo, tipoDanoAereo, tamanio, tipo, Raza::Protos), _escudo(escudo) {}

    // funcion para obtener acceso al escudo
    int getEscudo() { return _escudo; }

    // actualizar el escudo
    void setEscudo(double escudo) { _escudo = escudo; }

    // destructor
    ~CProtos() {}
};

class CZerg : public CUnidad
{
private:
    bool autodestruccion;
    bool primerAtaque;

public:
    CZerg(string nombre, int vida, int blindaje, int danoTerrestre, TipoDanoTerrestre tipoDano_Terrestre, int danoAereo, TipoDanoAereo tipoDano_Aereo, TamanioUnidad tamanio, TipoUnidad tipo, bool autodestruccion)
        : CUnidad(nombre, vida, blindaje, danoTerrestre, tipoDano_Terrestre, danoAereo, tipoDano_Aereo, tamanio, tipo, Raza::Zerg), autodestruccion(autodestruccion), primerAtaque(true) {}

    // funcion para obtener acceso a la  autodestruccion y primer ataque
    bool getAutodestruccion() { return autodestruccion; }
    bool getPrimerAtaque() { return primerAtaque; }
    // seter
    void setPrimerAtaque(bool primerAtaque) { this->primerAtaque = primerAtaque; }

    // destructor
    ~CZerg() {}
};

void imprimirTabla(CUnidad &unidad)
{

    cout << left << setw(15) << unidad.getNombre() << setw(10) << unidad.getVida() << setw(10) << unidad.getBlindaje() << setw(18) << unidad.getDanoTerrestre() << setw(15) << unidad.getDanoAereo() << setw(10) << unidad.getTamanio() << setw(10) << unidad.getTipo() << endl;
}
void imprimirTabla(CUnidad *unidad)
{
    // cout<<left<<setw(15)<<"Nombre"<<setw(10)<<"Vida"<<setw(10)<<"Blindaje"<<setw(18)<<"Daño Terrestre"<<setw(15)<<"Daño Aereo"<<setw(10)<<"Tamaño"<<setw(10)<<"Tipo"<<endl;

    cout << left << setw(15) << unidad->getNombre() << setw(10) << unidad->getVida() << setw(10) << unidad->getBlindaje() << setw(18) << unidad->getDanoTerrestre()
         << setw(15) << unidad->getDanoAereo() << setw(10) << unidad->getTamanio() << setw(10) << unidad->getTipo() << endl;
}

void ImprimirDatos(vector<CUnidad *> Base)
{
    for (int i = 0; i < Base.size(); i++)
    {
        cout << i + 1 << ". ";
        imprimirTabla(Base[i]);
    }
}

//! FUNCIONES
// Buscar el factor de la matriz especial

// Funcion para ver lo de la raza a escoger y el vector y por raza esocger swtich

// funcion para imprimir la tabla de datos de los heroes, de la raza que se escogio, que se encuentran en el vector

// Funcion para imprimir en el consola y en el archivo

// Funcion para imprimr los heores que se escogieron pero ordenados

int main()
{
    string jugador1, jugador2;
    int squad1, squad2, raza_squad1, raza_squad2;
    ofstream archivo;
    archivo.open("Partida.txt", ios::out);

    // leer el archivo de texto MensajeInicio.txt, y mostrarlo en pantalla y guardlo en el archivo partida.txt, lina por linea
    // el archivo MensajeInicio.txt, ya esta escrito y solo se debe leer y mostrar en pantalla y guardar en el archivo partida.txt
    ifstream archivo_lectura;
    string texto;
    archivo_lectura.open("MensajeInicio.txt", ios::binary);
    if (archivo_lectura.fail())
    {
        cout << "No se pudo abrir el archivo" << endl;
        exit(1);
    }
    while (!archivo_lectura.eof())
    {
        getline(archivo_lectura, texto);
        // cout << texto ;
        archivo << texto;
    }
    archivo_lectura.close();
    cout << endl;
    archivo << endl;

    cout << "-----Bienvenidos al juego de StarCraft: Brood War-------\n"
         << endl;
    archivo << "-----Bienvenidos al juego de StarCraft: Brood War-------\n"
            << endl;
    cout << "Ingrese el nombre del jugador 1: ";
    cin >> jugador1;
    cout << "Ingrese el nombre del jugador 2: ";
    cin >> jugador2;
    cout << "Hola " << jugador1 << " y " << jugador2 << ", vamos a jugar" << endl;
    archivo << "Hola " << jugador1 << " y " << jugador2 << ", vamos a jugar" << endl;
    cout << endl;
    cout << jugador1 << "¿De que raza sera su squad? " << endl;
    cout << "1. Terran" << endl;
    cout << "2. Protos" << endl;
    cout << "3. Zerg" << endl;
    cin >> raza_squad1;
    cout << jugador1 << "¿De cuantas unidades sera su squad?" << endl;
    cin >> squad1;
    cout << "Los heroes disponibles son: " << endl;
    cout << left << setw(15) << "Nombre" << setw(10) << "Vida" << setw(10) << "Blindaje" << setw(18) << "Daño Terrestre" << setw(15) << "Daño Aereo" << setw(10) << "Tamaño" << setw(10) << "Tipo" << endl;

    /*Definicion de los herores Terrán*/
    // CUnidad(nombre, vida, blindaje, danoTerrestre, tipoDano_Terrestre, danoAereo, tipoDano_Aereo, tamanio, tipo, Raza::Terran) {}
    CTerran Batlecuirser("Batlecuirser", 500, 3, 25, TipoDanoTerrestre::Normal, 25, TipoDanoAereo::Normal, TamanioUnidad::Grande, TipoUnidad::Aereo);
    CTerran Firebat("Firebat", 50, 1, 16, TipoDanoTerrestre::Contusivo, 0, TipoDanoAereo::Normal, TamanioUnidad::Pequeno, TipoUnidad::Terrestre);
    CTerran Ghost("Ghost", 45, 0, 10, TipoDanoTerrestre::Contusivo, 10, TipoDanoAereo::Contusivo, TamanioUnidad::Pequeno, TipoUnidad::Terrestre);
    CTerran Goliath("Goliath", 125, 1, 12, TipoDanoTerrestre::Normal, 20, TipoDanoAereo::Explosivo, TamanioUnidad::Grande, TipoUnidad::Aereo);
    CTerran Marine("Marine", 40, 0, 6, TipoDanoTerrestre::Normal, 6, TipoDanoAereo::Normal, TamanioUnidad::Pequeno, TipoUnidad::Terrestre);
    CTerran Duran("Duran", 200, 2, 25, TipoDanoTerrestre::Contusivo, 25, TipoDanoAereo::Contusivo, TamanioUnidad::Pequeno, TipoUnidad::Terrestre);
    CTerran Scv("Scv", 60, 0, 5, TipoDanoTerrestre::Normal, 0, TipoDanoAereo::Normal, TamanioUnidad::Pequeno, TipoUnidad::Terrestre);
    CTerran Tank("Tank", 150, 1, 70, TipoDanoTerrestre::Explosivo, 0, TipoDanoAereo::Normal, TamanioUnidad::Grande, TipoUnidad::Terrestre);
    CTerran Valkyrie("Valkyrie", 200, 2, 0, TipoDanoTerrestre::Normal, 48, TipoDanoAereo::Explosivo, TamanioUnidad::Grande, TipoUnidad::Aereo);
    CTerran Vulture("Vulture", 80, 0, 20, TipoDanoTerrestre::Contusivo, 0, TipoDanoAereo::Normal, TamanioUnidad::Mediano, TipoUnidad::Terrestre);
    CTerran Wraith("Wraith", 120, 0, 8, TipoDanoTerrestre::Normal, 20, TipoDanoAereo::Explosivo, TamanioUnidad::Grande, TipoUnidad::Aereo);

    /*Definicion de los herores Protos*/
    // Escudo el ultimo parametro
    CProtos Arbiter("Arbiter", 200, 1, 10, TipoDanoTerrestre::Explosivo, 10, TipoDanoAereo::Explosivo, TamanioUnidad::Grande, TipoUnidad::Aereo, 150);
    CProtos Archon("Archon", 10, 0, 30, TipoDanoTerrestre::Normal, 30, TipoDanoAereo::Normal, TamanioUnidad::Grande, TipoUnidad::Terrestre, 350);
    CProtos Carrier("Carrier", 300, 4, 48, TipoDanoTerrestre::Normal, 48, TipoDanoAereo::Normal, TamanioUnidad::Grande, TipoUnidad::Aereo, 150);
    CProtos Corsair("Corsair", 100, 1, 0, TipoDanoTerrestre::Normal, 6, TipoDanoAereo::Explosivo, TamanioUnidad::Mediano, TipoUnidad::Aereo, 80);
    CProtos Templar("Templar", 80, 1, 40, TipoDanoTerrestre::Normal, 0, TipoDanoAereo::Normal, TamanioUnidad::Pequeno, TipoUnidad::Terrestre, 40);
    CProtos Dragoon("Dragoon", 100, 1, 20, TipoDanoTerrestre::Explosivo, 20, TipoDanoAereo::Explosivo, TamanioUnidad::Grande, TipoUnidad::Terrestre, 80);
    CProtos Probe("Probe", 20, 0, 5, TipoDanoTerrestre::Normal, 0, TipoDanoAereo::Normal, TamanioUnidad::Pequeno, TipoUnidad::Terrestre, 20);
    CProtos Reaver("Reaver", 100, 0, 125, TipoDanoTerrestre::Normal, 0, TipoDanoAereo::Normal, TamanioUnidad::Grande, TipoUnidad::Terrestre, 80);
    CProtos Scout("Scout", 150, 0, 8, TipoDanoTerrestre::Normal, 28, TipoDanoAereo::Explosivo, TamanioUnidad::Grande, TipoUnidad::Aereo, 100);
    CProtos Zelaot("Zelaot", 100, 1, 16, TipoDanoTerrestre::Normal, 0, TipoDanoAereo::Normal, TamanioUnidad::Pequeno, TipoUnidad::Terrestre, 60);

    /*Definicion de los herores Zerg*/
    // CUnidad(nombre, vida, blindaje, danoTerrestre, tipoDano_Terrestre, danoAereo, tipoDano_Aereo, tamanio, tipo, Raza::Zerg), autodestruccion(autodestruccion), primerAtaque(true)
    CZerg Broodling("Broodling", 30, 0, 4, TipoDanoTerrestre::Normal, 0, TipoDanoAereo::Normal, TamanioUnidad::Pequeno, TipoUnidad::Terrestre, false);
    CZerg Devourer("Devourer", 250, 2, 0, TipoDanoTerrestre::Normal, 25, TipoDanoAereo::Explosivo, TamanioUnidad::Grande, TipoUnidad::Aereo, false);
    CZerg Drone("Drone", 40, 0, 5, TipoDanoTerrestre::Normal, 0, TipoDanoAereo::Normal, TamanioUnidad::Pequeno, TipoUnidad::Terrestre, false);
    CZerg Hydralisk("Hydralisk", 80, 0, 10, TipoDanoTerrestre::Explosivo, 10, TipoDanoAereo::Explosivo, TamanioUnidad::Mediano, TipoUnidad::Aereo, false);
    CZerg Infested("Infested", 60, 0, 500, TipoDanoTerrestre::Explosivo, 0, TipoDanoAereo::Normal, TamanioUnidad::Pequeno, TipoUnidad::Terrestre, true);
    CZerg Lurker("Lurker", 125, 1, 20, TipoDanoTerrestre::Normal, 0, TipoDanoAereo::Normal, TamanioUnidad::Mediano, TipoUnidad::Terrestre, false);
    CZerg Mutalisk("Mutalisk", 120, 0, 9, TipoDanoTerrestre::Normal, 9, TipoDanoAereo::Normal, TamanioUnidad::Pequeno, TipoUnidad::Aereo, false);
    CZerg Scourge("Scourge", 25, 0, 0, TipoDanoTerrestre::Normal, 110, TipoDanoAereo::Normal, TamanioUnidad::Pequeno, TipoUnidad::Aereo, true);
    CZerg Ultralisk("Ultralisk", 400, 3, 20, TipoDanoTerrestre::Normal, 0, TipoDanoAereo::Normal, TamanioUnidad::Grande, TipoUnidad::Terrestre, false);
    CZerg Zergling("Zergling", 35, 0, 5, TipoDanoTerrestre::Normal, 0, TipoDanoAereo::Normal, TamanioUnidad::Pequeno, TipoUnidad::Terrestre, false);

    vector<CUnidad *> squad1_2;
    switch (raza_squad1)
    {
    case 1: // terran

        // agregar estos heores al vector donde se guardaran los heroes de la raza que se eligio
        squad1_2.push_back(new CTerran("Batlecuirser", 500, 3, 25, TipoDanoTerrestre::Normal, 25, TipoDanoAereo::Normal, TamanioUnidad::Grande, TipoUnidad::Aereo));
        squad1_2.push_back(new CTerran("Firebat", 50, 1, 16, TipoDanoTerrestre::Contusivo, 0, TipoDanoAereo::Normal, TamanioUnidad::Pequeno, TipoUnidad::Terrestre));
        squad1_2.push_back(new CTerran("Ghost", 45, 0, 10, TipoDanoTerrestre::Contusivo, 10, TipoDanoAereo::Contusivo, TamanioUnidad::Pequeno, TipoUnidad::Terrestre));
        squad1_2.push_back(new CTerran("Goliath", 125, 1, 12, TipoDanoTerrestre::Normal, 20, TipoDanoAereo::Explosivo, TamanioUnidad::Grande, TipoUnidad::Aereo));
        squad1_2.push_back(new CTerran("Marine", 40, 0, 6, TipoDanoTerrestre::Normal, 6, TipoDanoAereo::Normal, TamanioUnidad::Pequeno, TipoUnidad::Terrestre));
        squad1_2.push_back(new CTerran("Duran", 200, 2, 25, TipoDanoTerrestre::Contusivo, 25, TipoDanoAereo::Contusivo, TamanioUnidad::Pequeno, TipoUnidad::Terrestre));
        squad1_2.push_back(new CTerran("Scv", 60, 0, 5, TipoDanoTerrestre::Normal, 0, TipoDanoAereo::Normal, TamanioUnidad::Pequeno, TipoUnidad::Terrestre));
        squad1_2.push_back(new CTerran("Tank", 150, 1, 70, TipoDanoTerrestre::Explosivo, 0, TipoDanoAereo::Normal, TamanioUnidad::Grande, TipoUnidad::Terrestre));
        squad1_2.push_back(new CTerran("Valkyrie", 200, 2, 0, TipoDanoTerrestre::Normal, 48, TipoDanoAereo::Explosivo, TamanioUnidad::Grande, TipoUnidad::Aereo));
        squad1_2.push_back(new CTerran("Vulture", 80, 0, 20, TipoDanoTerrestre::Contusivo, 0, TipoDanoAereo::Normal, TamanioUnidad::Mediano, TipoUnidad::Terrestre));
        squad1_2.push_back(new CTerran("Wraith", 120, 0, 8, TipoDanoTerrestre::Normal, 20, TipoDanoAereo::Explosivo, TamanioUnidad::Grande, TipoUnidad::Aereo));
        break;
    case 2: // proto
        // agregar estos heores al vector donde se guardaran los heroes de la raza que se eligio
        squad1_2.push_back(new CProtos("Arbiter", 200, 1, 10, TipoDanoTerrestre::Explosivo, 10, TipoDanoAereo::Explosivo, TamanioUnidad::Grande, TipoUnidad::Aereo, 150));
        squad1_2.push_back(new CProtos("Archon", 10, 0, 30, TipoDanoTerrestre::Normal, 30, TipoDanoAereo::Normal, TamanioUnidad::Grande, TipoUnidad::Terrestre, 350));
        squad1_2.push_back(new CProtos("Carrier", 300, 4, 48, TipoDanoTerrestre::Normal, 48, TipoDanoAereo::Normal, TamanioUnidad::Grande, TipoUnidad::Aereo, 150));
        squad1_2.push_back(new CProtos("Corsair", 100, 1, 0, TipoDanoTerrestre::Normal, 6, TipoDanoAereo::Explosivo, TamanioUnidad::Mediano, TipoUnidad::Aereo, 80));
        squad1_2.push_back(new CProtos("Templar", 80, 1, 40, TipoDanoTerrestre::Normal, 0, TipoDanoAereo::Normal, TamanioUnidad::Pequeno, TipoUnidad::Terrestre, 40));
        squad1_2.push_back(new CProtos("Dragoon", 100, 1, 20, TipoDanoTerrestre::Explosivo, 20, TipoDanoAereo::Explosivo, TamanioUnidad::Grande, TipoUnidad::Terrestre, 80));
        squad1_2.push_back(new CProtos("Probe", 20, 0, 5, TipoDanoTerrestre::Normal, 0, TipoDanoAereo::Normal, TamanioUnidad::Pequeno, TipoUnidad::Terrestre, 20));
        squad1_2.push_back(new CProtos("Reaver", 100, 0, 125, TipoDanoTerrestre::Normal, 0, TipoDanoAereo::Normal, TamanioUnidad::Grande, TipoUnidad::Terrestre, 80));
        squad1_2.push_back(new CProtos("Scout", 150, 0, 8, TipoDanoTerrestre::Normal, 28, TipoDanoAereo::Explosivo, TamanioUnidad::Grande, TipoUnidad::Aereo, 100));
        squad1_2.push_back(new CProtos("Zelaot", 100, 1, 16, TipoDanoTerrestre::Normal, 0, TipoDanoAereo::Normal, TamanioUnidad::Pequeno, TipoUnidad::Terrestre, 60));

        break;
    case 3: // zerg
        // agregar estos heores al vector donde se guardaran los heroes de la raza que se eligio
        squad1_2.push_back(new CZerg("Broodling", 30, 0, 4, TipoDanoTerrestre::Normal, 0, TipoDanoAereo::Normal, TamanioUnidad::Pequeno, TipoUnidad::Terrestre, false));
        squad1_2.push_back(new CZerg("Devourer", 250, 2, 0, TipoDanoTerrestre::Normal, 25, TipoDanoAereo::Explosivo, TamanioUnidad::Grande, TipoUnidad::Aereo, false));
        squad1_2.push_back(new CZerg("Drone", 40, 0, 5, TipoDanoTerrestre::Normal, 0, TipoDanoAereo::Normal, TamanioUnidad::Pequeno, TipoUnidad::Terrestre, false));
        squad1_2.push_back(new CZerg("Hydralisk", 80, 0, 10, TipoDanoTerrestre::Explosivo, 10, TipoDanoAereo::Explosivo, TamanioUnidad::Mediano, TipoUnidad::Aereo, false));
        squad1_2.push_back(new CZerg("Infested", 60, 0, 500, TipoDanoTerrestre::Explosivo, 0, TipoDanoAereo::Normal, TamanioUnidad::Pequeno, TipoUnidad::Terrestre, true));
        squad1_2.push_back(new CZerg("Lurker", 125, 1, 20, TipoDanoTerrestre::Normal, 0, TipoDanoAereo::Normal, TamanioUnidad::Mediano, TipoUnidad::Terrestre, false));
        squad1_2.push_back(new CZerg("Mutalisk", 120, 0, 9, TipoDanoTerrestre::Normal, 9, TipoDanoAereo::Normal, TamanioUnidad::Pequeno, TipoUnidad::Aereo, false));
        squad1_2.push_back(new CZerg("Scourge", 25, 0, 0, TipoDanoTerrestre::Normal, 110, TipoDanoAereo::Normal, TamanioUnidad::Pequeno, TipoUnidad::Aereo, true));
        squad1_2.push_back(new CZerg("Ultralisk", 400, 3, 20, TipoDanoTerrestre::Normal, 0, TipoDanoAereo::Normal, TamanioUnidad::Grande, TipoUnidad::Terrestre, false));
        squad1_2.push_back(new CZerg("Zergling", 35, 0, 5, TipoDanoTerrestre::Normal, 0, TipoDanoAereo::Normal, TamanioUnidad::Pequeno, TipoUnidad::Terrestre, false));

        break;
    default:
        cout << "Opcion invalida" << endl;
        break;
    }
    // imprimir los heroes
    ImprimirDatos(squad1_2);

    // para el numero de squad que requiero
    // vector que guarde los heores con sus clases
    vector<CUnidad *> HeoresSquad1;
    for (int i = 0; i < squad1;)
    {
        string var;
        cout << "Ingrese el nombre del heroe que desea: ";
        cin >> var;
        auto iterador = find_if(squad1_2.begin(), squad1_2.end(), [&var](CUnidad *unidad)
                                { return unidad->getNombre() == var; });
        if (iterador != squad1_2.end())
        {
            HeoresSquad1.push_back(*iterador);
            i++;
        }
        else
        {
            cout << "No se encontro el heroe" << endl;
        }
    }
    cout << "Los heroes que selecciono " << jugador1 << " son: " << endl;
    archivo << "Los heroes que selecciono " << jugador1 << " son: " << endl;

    for (auto i : HeoresSquad1)
    {
        cout << "\t" << i->getNombre() << endl;
        imprimirTabla(i);
        archivo << "\t" << i->getNombre() << endl;
    }
    cout << endl;

    // Implementamos jugador 2
    cout << jugador2 << "¿De que raza sera su squad? " << endl;
    cout << "1. Terran" << endl;
    cout << "2. Protos" << endl;
    cout << "3. Zerg" << endl;
    cin >> raza_squad2;
    cout << jugador2 << "¿De cuantas unidades sera su squad?" << endl;
    cin >> squad2;
    cout << "Los heroes disponibles son: " << endl;
    cout << left << setw(15) << "Nombre" << setw(10) << "Vida" << setw(10) << "Blindaje" << setw(18) << "Daño Terrestre" << setw(15) << "Daño Aereo" << setw(10) << "Tamaño" << setw(10) << "Tipo" << endl;

    vector<CUnidad *> squad2_2;
    switch (raza_squad2)
    {
    case 1: // terran

        // agregar estos heores al vector donde se guardaran los heroes de la raza que se eligio
        squad2_2.push_back(new CTerran("Batlecuirser", 500, 3, 25, TipoDanoTerrestre::Normal, 25, TipoDanoAereo::Normal, TamanioUnidad::Grande, TipoUnidad::Aereo));
        squad2_2.push_back(new CTerran("Firebat", 50, 1, 16, TipoDanoTerrestre::Contusivo, 0, TipoDanoAereo::Normal, TamanioUnidad::Pequeno, TipoUnidad::Terrestre));
        squad2_2.push_back(new CTerran("Ghost", 45, 0, 10, TipoDanoTerrestre::Contusivo, 10, TipoDanoAereo::Contusivo, TamanioUnidad::Pequeno, TipoUnidad::Terrestre));
        squad2_2.push_back(new CTerran("Goliath", 125, 1, 12, TipoDanoTerrestre::Normal, 20, TipoDanoAereo::Explosivo, TamanioUnidad::Grande, TipoUnidad::Aereo));
        squad2_2.push_back(new CTerran("Marine", 40, 0, 6, TipoDanoTerrestre::Normal, 6, TipoDanoAereo::Normal, TamanioUnidad::Pequeno, TipoUnidad::Terrestre));
        squad2_2.push_back(new CTerran("Duran", 200, 2, 25, TipoDanoTerrestre::Contusivo, 25, TipoDanoAereo::Contusivo, TamanioUnidad::Pequeno, TipoUnidad::Terrestre));
        squad2_2.push_back(new CTerran("Scv", 60, 0, 5, TipoDanoTerrestre::Normal, 0, TipoDanoAereo::Normal, TamanioUnidad::Pequeno, TipoUnidad::Terrestre));
        squad2_2.push_back(new CTerran("Tank", 150, 1, 70, TipoDanoTerrestre::Explosivo, 0, TipoDanoAereo::Normal, TamanioUnidad::Grande, TipoUnidad::Terrestre));
        squad2_2.push_back(new CTerran("Valkyrie", 200, 2, 0, TipoDanoTerrestre::Normal, 48, TipoDanoAereo::Explosivo, TamanioUnidad::Grande, TipoUnidad::Aereo));
        squad2_2.push_back(new CTerran("Vulture", 80, 0, 20, TipoDanoTerrestre::Contusivo, 0, TipoDanoAereo::Normal, TamanioUnidad::Mediano, TipoUnidad::Terrestre));
        squad2_2.push_back(new CTerran("Wraith", 120, 0, 8, TipoDanoTerrestre::Normal, 20, TipoDanoAereo::Explosivo, TamanioUnidad::Grande, TipoUnidad::Aereo));
        break;
    case 2: // protos
        // agregar estos heores al vector donde se guardaran los heroes de la raza que se eligio
        squad2_2.push_back(new CProtos("Arbiter", 200, 1, 10, TipoDanoTerrestre::Explosivo, 10, TipoDanoAereo::Explosivo, TamanioUnidad::Grande, TipoUnidad::Aereo, 150));
        squad2_2.push_back(new CProtos("Archon", 10, 0, 30, TipoDanoTerrestre::Normal, 30, TipoDanoAereo::Normal, TamanioUnidad::Grande, TipoUnidad::Terrestre, 350));
        squad2_2.push_back(new CProtos("Carrier", 300, 4, 48, TipoDanoTerrestre::Normal, 48, TipoDanoAereo::Normal, TamanioUnidad::Grande, TipoUnidad::Aereo, 150));
        squad2_2.push_back(new CProtos("Corsair", 100, 1, 0, TipoDanoTerrestre::Normal, 6, TipoDanoAereo::Explosivo, TamanioUnidad::Mediano, TipoUnidad::Aereo, 80));
        squad2_2.push_back(new CProtos("Templar", 80, 1, 40, TipoDanoTerrestre::Normal, 0, TipoDanoAereo::Normal, TamanioUnidad::Pequeno, TipoUnidad::Terrestre, 40));
        squad2_2.push_back(new CProtos("Dragoon", 100, 1, 20, TipoDanoTerrestre::Explosivo, 20, TipoDanoAereo::Explosivo, TamanioUnidad::Grande, TipoUnidad::Terrestre, 80));
        squad2_2.push_back(new CProtos("Probe", 20, 0, 5, TipoDanoTerrestre::Normal, 0, TipoDanoAereo::Normal, TamanioUnidad::Pequeno, TipoUnidad::Terrestre, 20));
        squad2_2.push_back(new CProtos("Reaver", 100, 0, 125, TipoDanoTerrestre::Normal, 0, TipoDanoAereo::Normal, TamanioUnidad::Grande, TipoUnidad::Terrestre, 80));
        squad2_2.push_back(new CProtos("Scout", 150, 0, 8, TipoDanoTerrestre::Normal, 28, TipoDanoAereo::Explosivo, TamanioUnidad::Grande, TipoUnidad::Aereo, 100));
        squad2_2.push_back(new CProtos("Zelaot", 100, 1, 16, TipoDanoTerrestre::Normal, 0, TipoDanoAereo::Normal, TamanioUnidad::Pequeno, TipoUnidad::Terrestre, 60));
        break;

    case 3: // zerg
        // agregar estos heores al vector donde se guardaran los heroes de la raza que se eligio
        squad2_2.push_back(new CZerg("Broodling", 30, 0, 4, TipoDanoTerrestre::Normal, 0, TipoDanoAereo::Normal, TamanioUnidad::Pequeno, TipoUnidad::Terrestre, false));
        squad2_2.push_back(new CZerg("Devourer", 250, 2, 0, TipoDanoTerrestre::Normal, 25, TipoDanoAereo::Explosivo, TamanioUnidad::Grande, TipoUnidad::Aereo, false));
        squad2_2.push_back(new CZerg("Drone", 40, 0, 5, TipoDanoTerrestre::Normal, 0, TipoDanoAereo::Normal, TamanioUnidad::Pequeno, TipoUnidad::Terrestre, false));
        squad2_2.push_back(new CZerg("Hydralisk", 80, 0, 10, TipoDanoTerrestre::Explosivo, 10, TipoDanoAereo::Explosivo, TamanioUnidad::Mediano, TipoUnidad::Aereo, false));
        squad2_2.push_back(new CZerg("Infested", 60, 0, 500, TipoDanoTerrestre::Explosivo, 0, TipoDanoAereo::Normal, TamanioUnidad::Pequeno, TipoUnidad::Terrestre, true));
        squad2_2.push_back(new CZerg("Lurker", 125, 1, 20, TipoDanoTerrestre::Normal, 0, TipoDanoAereo::Normal, TamanioUnidad::Mediano, TipoUnidad::Terrestre, false));
        squad2_2.push_back(new CZerg("Mutalisk", 120, 0, 9, TipoDanoTerrestre::Normal, 9, TipoDanoAereo::Normal, TamanioUnidad::Pequeno, TipoUnidad::Aereo, false));
        squad2_2.push_back(new CZerg("Scourge", 25, 0, 0, TipoDanoTerrestre::Normal, 110, TipoDanoAereo::Normal, TamanioUnidad::Pequeno, TipoUnidad::Aereo, true));
        squad2_2.push_back(new CZerg("Ultralisk", 400, 3, 20, TipoDanoTerrestre::Normal, 0, TipoDanoAereo::Normal, TamanioUnidad::Grande, TipoUnidad::Terrestre, false));
        squad2_2.push_back(new CZerg("Zergling", 35, 0, 5, TipoDanoTerrestre::Normal, 0, TipoDanoAereo::Normal, TamanioUnidad::Pequeno, TipoUnidad::Terrestre, false));
        break;

    default:
        cout << "Opcion invalida" << endl;
        break;
    }
    // imprimir los heroes
    ImprimirDatos(squad2_2);

    vector<CUnidad *> HeoresSquad2;
    for (int i = 0; i < squad2;)
    {
        string var;
        cout << "Ingrese el nombre del heroe que desea: ";
        cin >> var;
        auto iterador = find_if(squad2_2.begin(), squad2_2.end(), [&var](CUnidad *unidad)
                                { return unidad->getNombre() == var; });
        if (iterador != squad2_2.end())
        {
            HeoresSquad2.push_back(*iterador);
            i++;
        }
        else
        {
            cout << "No se encontro el heroe" << endl;
        }
    }

    cout << "Los heroes que selecciono " << jugador2 << " son: " << endl;
    archivo << "Los heroes que selecciono " << jugador2 << " son: " << endl;
    for (auto i : HeoresSquad2)
    {
        cout << "\t" << i->getNombre() << endl;
        imprimirTabla(i);
        archivo << "\t" << i->getNombre() << endl;
    }

    // La tabla de las condiciones especiales, de tamano y el daño que hace a cada tipo de unidad
    // expresarla en una matriz de 3x3
    // columna -> tamaño del enemigo
    // columna 1 -> pequeno
    // columna 2 -> mediano
    // columna 3 -> grande
    // fila->  tipo de ataque
    // fila 1 . Normal
    // fila 2 . Explosivo
    // fila 3 . Contusivo
    // memoria dinamica -> PARA LA MATRIZ ESPECIAL
    double **matrizEspecial = new double *[3];
    for (int i = 0; i < 3; i++)
    {
        matrizEspecial[i] = new double[3];
    }
    // llenar la matriz
    matrizEspecial[0][0] = 1;
    matrizEspecial[0][1] = 1;
    matrizEspecial[0][2] = 1;
    matrizEspecial[1][0] = 0.5;
    matrizEspecial[1][1] = 0.75;
    matrizEspecial[1][2] = 1;
    matrizEspecial[2][0] = 1;
    matrizEspecial[2][1] = 0.5;
    matrizEspecial[2][2] = 0.25;

    // Los numeros de la matriz son los factores de daño que se le hara al enemigo
    // se debera de recorrer la matriz, para saber el factor de daño que se le hara al enemigo

    cout << "Comienza la batalla" << endl;
    cout << endl;
    archivo << "Comienza la batalla" << endl;
    archivo << endl;

    int turno = 1;
    // Ciclo de batalla
    while (!HeoresSquad1.empty() && !HeoresSquad2.empty())
    {
        cout << "\tTurno: " << turno << endl;
        archivo << "\tTurno: " << turno << endl;
        // Buscar la unidad enemiga con mayor vida
        sort(HeoresSquad2.begin(), HeoresSquad2.end(),
             [](CUnidad *a, CUnidad *b)
             { return a->getVida() > b->getVida(); });

        sort(HeoresSquad1.begin(), HeoresSquad1.end(),
             [](CUnidad *a, CUnidad *b)
             { return a->getVida() > b->getVida(); });
        // imprimri los heroes de cada squad ordenamos

        int indice1 = 0;
        int indice2 = 0;
        auto enemigoMaxVida1 = HeoresSquad2.begin() + indice1;
        auto enemigoMaxVida2 = HeoresSquad1.begin() + indice2;

        // Hacer que todo el grupo ataque al enemigo con mayor vida
        /* Los puntos de blindaje, le restan en % al dano de ataque. Si esl numero de blindaje es 1, se le resta el 10% del dano de ataque
        Inclusive, le restan si este previamente ha sido mutiplicado por los factores de la matriz especial */

        // En caso de que la unidad sea protos, primero se debe de ver si tiene escudo
        //  si tiene escudo, se le restara el dano al escudo
        //  hasta que este se acabe y luego se le restara a la vida
        for (const auto &unidad : HeoresSquad1)
        {
            if (enemigoMaxVida1 != HeoresSquad2.end() && (*enemigoMaxVida1)->getVida() > 0)
            {
                while ((*enemigoMaxVida1)->getTipo() == TipoUnidad::Terrestre && unidad->getDanoTerrestre() == 0 && indice1 < HeoresSquad2.size())
                {
                    cout << "El heroe " << unidad->getNombre() << " no puede atacar a " << (*enemigoMaxVida1)->getNombre() << endl;
                    archivo << "El herore " << unidad->getNombre() << " no puede atacar a " << (*enemigoMaxVida1)->getNombre() << endl;
                    // si el enemigo con mayor vida es terrestre y la unidad no tiene dano terrestre
                    // se pasa al siguiente enemigo con mayor vida
                    indice1++;
                    enemigoMaxVida1 = HeoresSquad2.begin() + indice1;
                    // el dano de la unidad no se actualiza a 0, porque puede que el siguiente enemigo con mayor vida
                }

                while ((*enemigoMaxVida1)->getTipo() == TipoUnidad::Aereo && unidad->getDanoAereo() == 0 && indice1 < HeoresSquad2.size())
                {
                    cout << "El heroe " << unidad->getNombre() << " no puede atacar a " << (*enemigoMaxVida1)->getNombre() << endl;
                    archivo << "El herore " << unidad->getNombre() << " no puede atacar a " << (*enemigoMaxVida1)->getNombre() << endl;
                    indice1++;

                    enemigoMaxVida1 = HeoresSquad2.begin() + indice1;
                    // el dano de la unidad no se actualiza a 0, porque puede que el siguiente enemigo con mayor vida
                }
                if (indice1 >= HeoresSquad2.size())
                {
                    cout << "Los herores del suad 1 no pueden atacar a los enemigos del squad 2" << endl;
                    break;
                }

                //// si el enemigo con mayor vida esta vivo
                double factorDanio;
                double danoReal;
                // ver si el tipo del enemigo con mayor vida es terrestre o aerero
                if ((*enemigoMaxVida1)->getTipo() == TipoUnidad::Terrestre)
                {
                    // unidad usará el tipo de ataque terrestre
                    // ver que tipo de dano terrestre tiene la unidad
                    if (unidad->getTipoDanoTerrestre() == TipoDanoTerrestre::Normal)
                    { // fila 0
                        if ((*enemigoMaxVida1)->getTamanio() == TamanioUnidad::Pequeno)
                        {
                            factorDanio = matrizEspecial[0][0];
                        }
                        else if ((*enemigoMaxVida1)->getTamanio() == TamanioUnidad::Mediano)
                        {
                            factorDanio = matrizEspecial[0][1];
                        }
                        else if ((*enemigoMaxVida1)->getTamanio() == TamanioUnidad::Grande)
                        {
                            factorDanio = matrizEspecial[0][2];
                        }
                    }
                    else if (unidad->getTipoDanoTerrestre() == TipoDanoTerrestre::Explosivo)
                    { // fila 1
                        if ((*enemigoMaxVida1)->getTamanio() == TamanioUnidad::Pequeno)
                        {
                            factorDanio = matrizEspecial[1][0];
                        }
                        else if ((*enemigoMaxVida1)->getTamanio() == TamanioUnidad::Mediano)
                        {
                            factorDanio = matrizEspecial[1][1];
                        }
                        else if ((*enemigoMaxVida1)->getTamanio() == TamanioUnidad::Grande)
                        {
                            factorDanio = matrizEspecial[1][2];
                        }
                    }
                    else if (unidad->getTipoDanoTerrestre() == TipoDanoTerrestre::Contusivo)
                    { // fila 2

                        if ((*enemigoMaxVida1)->getTamanio() == TamanioUnidad::Pequeno)
                        {
                            factorDanio = matrizEspecial[2][0];
                        }
                        else if ((*enemigoMaxVida1)->getTamanio() == TamanioUnidad::Mediano)
                        {
                            factorDanio = matrizEspecial[2][1];
                        }
                        else if ((*enemigoMaxVida1)->getTamanio() == TamanioUnidad::Grande)
                        {
                            factorDanio = matrizEspecial[2][2];
                        }
                    }
                    // si tiene blindaje 1 se le resta el 10% del dano de ataque
                    factorDanio = factorDanio * ((10 - (*enemigoMaxVida1)->getBlindaje()) / 10);

                    danoReal = unidad->getDanoTerrestre() * factorDanio;
                }
                else
                { // aereo
                    if (unidad->getTipoDanoAereo() == TipoDanoAereo::Normal)
                    { // fila 0
                        if ((*enemigoMaxVida1)->getTamanio() == TamanioUnidad::Pequeno)
                        {
                            factorDanio = matrizEspecial[0][0];
                        }
                        else if ((*enemigoMaxVida1)->getTamanio() == TamanioUnidad::Mediano)
                        {
                            factorDanio = matrizEspecial[0][1];
                        }
                        else if ((*enemigoMaxVida1)->getTamanio() == TamanioUnidad::Grande)
                        {
                            factorDanio = matrizEspecial[0][2];
                        }
                    }
                    else if (unidad->getTipoDanoAereo() == TipoDanoAereo::Explosivo)
                    { // fila 1
                        if ((*enemigoMaxVida1)->getTamanio() == TamanioUnidad::Pequeno)
                        {
                            factorDanio = matrizEspecial[1][0];
                        }
                        else if ((*enemigoMaxVida1)->getTamanio() == TamanioUnidad::Mediano)
                        {
                            factorDanio = matrizEspecial[1][1];
                        }
                        else if ((*enemigoMaxVida1)->getTamanio() == TamanioUnidad::Grande)
                        {
                            factorDanio = matrizEspecial[1][2];
                        }
                    }
                    else if (unidad->getTipoDanoAereo() == TipoDanoAereo::Contusivo)
                    { // fila 2

                        if ((*enemigoMaxVida1)->getTamanio() == TamanioUnidad::Pequeno)
                        {
                            factorDanio = matrizEspecial[2][0];
                        }
                        else if ((*enemigoMaxVida1)->getTamanio() == TamanioUnidad::Mediano)
                        {
                            factorDanio = matrizEspecial[2][1];
                        }
                        else if ((*enemigoMaxVida1)->getTamanio() == TamanioUnidad::Grande)
                        {
                            factorDanio = matrizEspecial[2][2];
                        }
                    }
                    factorDanio = factorDanio * ((10 - (*enemigoMaxVida1)->getBlindaje()) / 10);
                    danoReal = unidad->getDanoAereo() * factorDanio;
                }

                // ver si la el enemigo tiene escudo
                if ((*enemigoMaxVida1)->getRaza() == Raza::Protos)
                {
                    // transformano el enemigo a protos
                    CProtos *enemigoProtos = dynamic_cast<CProtos *>(*enemigoMaxVida1);
                    // ver si tiene escudo, si tiene primero se le resta al escudo y luego a la vida
                    if ((enemigoProtos)->getEscudo() > 0)
                    {
                        (enemigoProtos)->setEscudo((enemigoProtos)->getEscudo() - danoReal);

                        if ((enemigoProtos)->getEscudo() < 0)
                        {
                            enemigoProtos->setEscudo(0);
                            (enemigoProtos)->setVida((enemigoProtos)->getVida() - danoReal);
                        }

                        cout << unidad->getNombre() << " ataca a " << (*enemigoMaxVida1)->getNombre() << " con " << danoReal << " de dano " << endl;
                        cout << (*enemigoMaxVida1)->getNombre() << " - Vida " << (*enemigoMaxVida1)->getVida() << " - Escudo " << (enemigoProtos)->getEscudo() << endl;

                        archivo << unidad->getNombre() << " ataca a " << (*enemigoMaxVida1)->getNombre() << " con " << danoReal << " de dano " << endl;
                        archivo << (*enemigoMaxVida1)->getNombre() << " - Vida " << (*enemigoMaxVida1)->getVida() << " - Escudo " << (enemigoProtos)->getEscudo() << endl;
                    }
                    else
                    { // si no tiene escudo, se le resta a la vida
                        (*enemigoMaxVida1)->setVida((*enemigoMaxVida1)->getVida() - danoReal);
                        cout << unidad->getNombre() << " ataca a " << (*enemigoMaxVida1)->getNombre() << " con " << danoReal << " de dano " << endl;
                        cout << (*enemigoMaxVida1)->getNombre() << " - Vida " << (*enemigoMaxVida1)->getVida() << " - Escudo " << (enemigoProtos)->getEscudo() << endl;

                        archivo << unidad->getNombre() << " ataca a " << (*enemigoMaxVida1)->getNombre() << " con " << danoReal << " de dano  " << endl;
                        archivo << (*enemigoMaxVida1)->getNombre() << " - Vida " << (*enemigoMaxVida1)->getVida() << " - Escudo " << (enemigoProtos)->getEscudo() << endl;
                    }
                }
                else if ((*enemigoMaxVida1)->getRaza() == Raza::Zerg)
                {
                    CZerg *enemigoZerg = dynamic_cast<CZerg *>((*enemigoMaxVida1));
                    // primer ataque
                    if (enemigoZerg->getPrimerAtaque() == true)
                    {
                        // cambiamos el valor de primer ataque a false
                        enemigoZerg->setPrimerAtaque(false);
                        // se le resta el dano a la vida del enemigo
                        enemigoZerg->setVida(enemigoZerg->getVida() - danoReal);
                        // si es la primera vez que ataca, se le suma 1 a la vida
                        enemigoZerg->setVida(enemigoZerg->getVida() + 1);
                        cout << unidad->getNombre() << " ataca a " << (*enemigoMaxVida1)->getNombre() << " con " << danoReal << " de dano" << endl;
                        cout << "La unidad atacdada tiene primer ataque, por lo que se le suma 1 a la vida" << endl;
                        cout << (*enemigoMaxVida1)->getNombre() << " - Vida" << (*enemigoMaxVida1)->getVida() << endl;

                        archivo << unidad->getNombre() << " ataca a " << (*enemigoMaxVida1)->getNombre() << " con " << danoReal << " de dano" << endl;
                        archivo << "La unidad atacdada tiene primer ataque, por lo que se le suma 1 a la vida" << endl;
                        archivo << (*enemigoMaxVida1)->getNombre() << " es: " << (*enemigoMaxVida1)->getVida() << endl;
                    }
                    else
                    {
                        // no es la primera vez
                        (*enemigoMaxVida1)->setVida((*enemigoMaxVida1)->getVida() - danoReal);
                        // se le resta el dano a la vida del enemigo
                        cout << unidad->getNombre() << " ataca a " << (*enemigoMaxVida1)->getNombre() << " con " << danoReal << " de dano" << endl;
                        cout << (*enemigoMaxVida1)->getNombre() << "  - Vida : " << (*enemigoMaxVida1)->getVida() << endl;

                        archivo << unidad->getNombre() << " ataca a " << (*enemigoMaxVida1)->getNombre() << " con " << danoReal << " de dano" << endl;
                        archivo << (*enemigoMaxVida1)->getNombre() << "  - Vida : " << (*enemigoMaxVida1)->getVida() << endl;
                    }
                }
                else
                { // Terran
                    (*enemigoMaxVida1)->setVida((*enemigoMaxVida1)->getVida() - danoReal);
                    cout << unidad->getNombre() << " ataca a " << (*enemigoMaxVida1)->getNombre() << " con " << danoReal << " de dano " << endl;
                    cout << (*enemigoMaxVida1)->getNombre() << "  - Vida : " << (*enemigoMaxVida1)->getVida() << endl;

                    archivo << unidad->getNombre() << " ataca a " << (*enemigoMaxVida1)->getNombre() << " con " << danoReal << " de dano " << endl;
                    archivo << (*enemigoMaxVida1)->getNombre() << "  - Vida : " << (*enemigoMaxVida1)->getVida() << endl;
                }
                // Vemos si la unidad es Zerg, aumentamo lo de autodestrucion, si tiene esta habilidad, explota después de atacar
                if ((unidad)->getRaza() == Raza::Zerg)
                {
                    CZerg *unidadZerg = dynamic_cast<CZerg *>((unidad));
                    if ((unidadZerg)->getAutodestruccion() == true)
                    {
                        (unidadZerg)->setVida(0);
                        cout << "La unidad " << unidadZerg->getNombre() << " ha explotado" << endl;
                        archivo << "La unidad " << unidadZerg->getNombre() << " ha explotado" << endl;

                        // eliminar a la unidadzerg del vector de heroes del squad1 si expplota
                        HeoresSquad1.erase(find(HeoresSquad1.begin(), HeoresSquad1.end(), unidadZerg));
                    }
                }
                
                // ver si el enemigo murio
                if ((*enemigoMaxVida1)->getVida() <= 0)
                {
                    cout << (*enemigoMaxVida1)->getNombre() << " ha muerto" << endl;
                    archivo << (*enemigoMaxVida1)->getNombre() << " ha muerto" << endl;
                    // eliminamos al enemigo *enemigoMaxVida1 del vector de heroes del squad2
                    HeoresSquad2.erase(find(HeoresSquad2.begin(), HeoresSquad2.end(), *enemigoMaxVida1));
                }

            } // aqui termina el if de la vida del en
              // termina el for de la unidad atacante
            for (auto &unidad2 : HeoresSquad2)
            { //
                if (enemigoMaxVida2 != HeoresSquad1.end() && (*enemigoMaxVida2)->getVida() > 0)

                {
                    while ((*enemigoMaxVida2)->getTipo() == TipoUnidad::Terrestre && unidad2->getDanoTerrestre() == 0 && indice1 < HeoresSquad1.size())
                    {
                        cout << "El heroe " << unidad2->getNombre() << " no puede atacar a " << (*enemigoMaxVida2)->getNombre() << endl;
                        archivo << "El heroe " << unidad2->getNombre() << " no puede atacar a " << (*enemigoMaxVida2)->getNombre() << endl;

                        indice2++;
                        enemigoMaxVida2 = HeoresSquad1.begin() + indice2;
                    }
                    while ((*enemigoMaxVida2)->getTipo() == TipoUnidad::Aereo && unidad2->getDanoAereo() == 0 && indice1 < HeoresSquad1.size())
                    {
                        cout << "El herore " << unidad2->getNombre() << " no puede atacar a " << (*enemigoMaxVida2)->getNombre() << endl;
                        archivo << "El heroe " << unidad2->getNombre() << " no puede atacar a " << (*enemigoMaxVida2)->getNombre() << endl;

                        indice2++;
                        enemigoMaxVida2 = HeoresSquad1.begin() + indice2;
                    }

                    if (indice2 >= HeoresSquad2.size())
                    {
                        cout << "Los herores del suad 1 no pueden atacar a los enemigos del squad 2" << endl;
                        break;
                    }
                    // si el enemigo con mayor vida esta vivo
                    double factorDanio;
                    double danoReal;

                    // ver si el tipo del enemigo con mayor vida es terrestre o aerero
                    if ((*enemigoMaxVida2)->getTipo() == TipoUnidad::Terrestre)
                    {
                        // unidad usará el tipo de ataque terrestre
                        // ver que tipo de dano terrestre tiene la unidad
                        if (unidad2->getTipoDanoTerrestre() == TipoDanoTerrestre::Normal)
                        { // fila 0
                            if ((*enemigoMaxVida2)->getTamanio() == TamanioUnidad::Pequeno)
                            {
                                factorDanio = matrizEspecial[0][0];
                            }
                            else if ((*enemigoMaxVida2)->getTamanio() == TamanioUnidad::Mediano)
                            {
                                factorDanio = matrizEspecial[0][1];
                            }
                            else if ((*enemigoMaxVida2)->getTamanio() == TamanioUnidad::Grande)
                            {
                                factorDanio = matrizEspecial[0][2];
                            }
                        }
                        else if (unidad2->getTipoDanoTerrestre() == TipoDanoTerrestre::Explosivo)
                        { // fila 1
                            if ((*enemigoMaxVida2)->getTamanio() == TamanioUnidad::Pequeno)
                            {
                                factorDanio = matrizEspecial[1][0];
                            }
                            else if ((*enemigoMaxVida2)->getTamanio() == TamanioUnidad::Mediano)
                            {
                                factorDanio = matrizEspecial[1][1];
                            }
                            else if ((*enemigoMaxVida2)->getTamanio() == TamanioUnidad::Grande)
                            {
                                factorDanio = matrizEspecial[1][2];
                            }
                        }
                        else if (unidad2->getTipoDanoTerrestre() == TipoDanoTerrestre::Contusivo)
                        { // fila 2

                            if ((*enemigoMaxVida2)->getTamanio() == TamanioUnidad::Pequeno)
                            {
                                factorDanio = matrizEspecial[2][0];
                            }
                            else if ((*enemigoMaxVida2)->getTamanio() == TamanioUnidad::Mediano)
                            {
                                factorDanio = matrizEspecial[2][1];
                            }
                            else if ((*enemigoMaxVida2)->getTamanio() == TamanioUnidad::Grande)
                            {
                                factorDanio = matrizEspecial[2][2];
                            }
                        }
                        factorDanio = factorDanio * ((10 - (*enemigoMaxVida2)->getBlindaje()) / 10);
                        danoReal = unidad2->getDanoTerrestre() * factorDanio;
                    }
                    else
                    { // aereo
                        if (unidad2->getTipoDanoAereo() == TipoDanoAereo::Normal)
                        { // fila 0
                            if ((*enemigoMaxVida2)->getTamanio() == TamanioUnidad::Pequeno)
                            {
                                factorDanio = matrizEspecial[0][0];
                            }
                            else if ((*enemigoMaxVida2)->getTamanio() == TamanioUnidad::Mediano)
                            {
                                factorDanio = matrizEspecial[0][1];
                            }
                            else if ((*enemigoMaxVida2)->getTamanio() == TamanioUnidad::Grande)
                            {
                                factorDanio = matrizEspecial[0][2];
                            }
                        }
                        else if (unidad2->getTipoDanoAereo() == TipoDanoAereo::Explosivo)
                        { // fila 1
                            if ((*enemigoMaxVida2)->getTamanio() == TamanioUnidad::Pequeno)
                            {
                                factorDanio = matrizEspecial[1][0];
                            }
                            else if ((*enemigoMaxVida2)->getTamanio() == TamanioUnidad::Mediano)
                            {
                                factorDanio = matrizEspecial[1][1];
                            }
                            else if ((*enemigoMaxVida2)->getTamanio() == TamanioUnidad::Grande)
                            {
                                factorDanio = matrizEspecial[1][2];
                            }
                        }
                        else if (unidad2->getTipoDanoAereo() == TipoDanoAereo::Contusivo)
                        { // fila 2

                            if ((*enemigoMaxVida2)->getTamanio() == TamanioUnidad::Pequeno)
                            {
                                factorDanio = matrizEspecial[2][0];
                            }
                            else if ((*enemigoMaxVida2)->getTamanio() == TamanioUnidad::Mediano)
                            {
                                factorDanio = matrizEspecial[2][1];
                            }
                            else if ((*enemigoMaxVida2)->getTamanio() == TamanioUnidad::Grande)
                            {
                                factorDanio = matrizEspecial[2][2];
                            }
                        }
                        // como hallo con el blindaje, considerando que si el blindaje es 1, se le resta el 10% del dano de ataque
                        factorDanio = factorDanio * ((10 - (*enemigoMaxVida2)->getBlindaje()) / 10);
                        danoReal = unidad2->getDanoAereo() * factorDanio;
                    }
                    // ver si la unidad tiene escudo
                    if ((*enemigoMaxVida2)->getRaza() == Raza::Protos)
                    {
                        // transformano el enemigo a protos
                        CProtos *enemigoProtos2 = dynamic_cast<CProtos *>((*enemigoMaxVida2));
                        // ver si tiene escudo, si tiene primero se le resta al escudo y luego a la vida
                        if ((enemigoProtos2)->getEscudo() > 0)
                        {
                            // imprimir la vida del escudo y la vida
                            cout << unidad2->getNombre() << " ataca a " << (*enemigoMaxVida2)->getNombre() << " con " << danoReal << " de dano" << endl;
                            (enemigoProtos2)->setEscudo((enemigoProtos2)->getEscudo() - danoReal);
                            if ((enemigoProtos2)->getEscudo() < 0)
                            {
                                (enemigoProtos2)->setVida((enemigoProtos2)->getVida() - danoReal);
                            }

                            cout << enemigoProtos2->getNombre() << " - Vida " << enemigoProtos2->getVida() << " - Escudo " << enemigoProtos2->getEscudo() << endl;

                            archivo << unidad2->getNombre() << " ataca a " << (*enemigoMaxVida2)->getNombre() << " con " << danoReal << " de dano " << endl;
                            archivo << enemigoProtos2->getNombre() << " - Vida " << enemigoProtos2->getVida() << " -> Escudo " << enemigoProtos2->getEscudo() << endl;

                            // si el escudo se acaba, se le resta a la vida
                            if ((enemigoProtos2)->getEscudo() < 0)
                            {
                                // se le resta el dano a la vida
                                enemigoProtos2->setEscudo(0);
                                (enemigoProtos2)->setVida((enemigoProtos2)->getVida() - danoReal);
                                cout << enemigoProtos2->getNombre() << " -> Vida " << enemigoProtos2->getVida() << " ; -> Escudo " << enemigoProtos2->getEscudo() << endl;
                                archivo << enemigoProtos2->getNombre() << " -> Vida " << enemigoProtos2->getVida() << "; ->  Escudo " << enemigoProtos2->getEscudo() << endl;
                            }
                        }
                        else
                        { // si no tiene escudo, se le resta a la vida
                            cout << unidad2->getNombre() << " ataca a " << (*enemigoMaxVida2)->getNombre() << " con " << danoReal << " de dano $" << endl;
                            (*enemigoMaxVida2)->setVida((*enemigoMaxVida2)->getVida() - danoReal);
                            cout << *enemigoMaxVida2 << " -> Vida " << (*enemigoMaxVida1)->getVida() << "; -> Escudo" << 0 << endl;

                            archivo << unidad2->getNombre() << " ataca a " << (*enemigoMaxVida2)->getNombre() << " con " << danoReal << " de dano %" << endl;
                            archivo << *enemigoMaxVida2 << " -> Vida " << (*enemigoMaxVida2)->getVida() << "; -> Escudo" << 0 << endl;
                        }
                    }
                    else if ((*enemigoMaxVida2)->getRaza() == Raza::Zerg)
                    {
                        CZerg *enemigoZerg2 = dynamic_cast<CZerg *>((*enemigoMaxVida2));
                        /*  if (enemigoZerg2->getAutodestruccion() == true)
                          {
                              // la unidad atacante muere inmediatamente después de hacerle daño al defensor
                              // se le resta el dano a la vida del enemigo
                              enemigoZerg2->setVida(enemigoZerg2->getVida() - danoReal);
                              // la unidad atacante muere y la defendida tambien
                              (*enemigoMaxVida2)->setVida(0);
                              unidad2->setVida(0);
                              cout << unidad2->getNombre() << " ataca a " << (*enemigoMaxVida2)->getNombre() << " con " << danoReal << " de dano" << endl;
                              cout << "La unidad atacdada tiene autodestruccion, por lo que ambas unidades murieron" << endl;
                              cout << (*enemigoMaxVida2)->getNombre() << " - Vida " << (*enemigoMaxVida2)->getVida() << endl;
                              cout << unidad2->getNombre() << "  - Vida " << unidad2->getVida() << endl;

                              archivo << unidad2->getNombre() << " ataca a " << (*enemigoMaxVida2)->getNombre() << " con " << danoReal << " de dano $" << endl;
                              archivo << "La unidad atacdada tiene autodestruccion, por lo que ambas unidades murieron" << endl;
                              archivo << (*enemigoMaxVida2)->getNombre() << " - Vida " << (*enemigoMaxVida2)->getVida() << endl;
                              archivo << unidad2->getNombre() << " - Vida " << unidad2->getVida() << endl;
                          }*/

                        // primer ataque
                        if (enemigoZerg2->getPrimerAtaque() == true)
                        {
                            // cambiamos el valor de primer ataque a false
                            enemigoZerg2->setPrimerAtaque(false);

                            // se le resta el dano a la vida del enemigo
                            enemigoZerg2->setVida(enemigoZerg2->getVida() - danoReal);
                            // si es la primera vez que ataca, se le suma 1 a la vida
                            enemigoZerg2->setVida(enemigoZerg2->getVida() + 1);
                            cout << unidad2->getNombre() << " ataca a " << (*enemigoMaxVida2)->getNombre() << " con " << danoReal << " de dano" << endl;
                            cout << "La unidad atacdada tiene primer ataque, por lo que se le suma 1 a la vida" << endl;
                            cout << (*enemigoMaxVida2)->getNombre() << " - Vida" << (*enemigoMaxVida2)->getVida() << endl;

                            archivo << unidad2->getNombre() << " ataca a " << (*enemigoMaxVida2)->getNombre() << " con " << danoReal << " de dano " << endl;
                            archivo << "La unidad atacdada tiene primer ataque, por lo que se le suma 1 a la vida" << endl;
                            archivo << (*enemigoMaxVida2)->getNombre() << " es: " << (*enemigoMaxVida2)->getVida() << endl;
                        }
                        else
                        {
                            // no es la primera vez
                            cout << unidad2->getNombre() << " ataca a " << (*enemigoMaxVida2)->getNombre() << " con " << danoReal << " de dano" << endl;
                            // se le resta el dano a la vida del enemigo
                            (*enemigoMaxVida2)->setVida((*enemigoMaxVida2)->getVida() - danoReal);
                            cout << (*enemigoMaxVida2)->getNombre() << "  - Vida : " << (*enemigoMaxVida2)->getVida() << endl;

                            archivo << unidad2->getNombre() << " ataca a " << (*enemigoMaxVida2)->getNombre() << " con " << danoReal << " de dano " << endl;
                            archivo << (*enemigoMaxVida2)->getNombre() << "  - Vida : " << (*enemigoMaxVida2)->getVida() << endl;
                        }
                    }
                    else
                    { // Terran
                        (*enemigoMaxVida2)->setVida((*enemigoMaxVida2)->getVida() - danoReal);
                        cout << unidad2->getNombre() << " ataca a " << (*enemigoMaxVida2)->getNombre() << " con " << danoReal << " de dano " << endl;
                        cout << (*enemigoMaxVida2)->getNombre() << "  - Vida : " << (*enemigoMaxVida2)->getVida() << endl;

                        archivo << unidad2->getNombre() << " ataca a " << (*enemigoMaxVida2)->getNombre() << " con " << danoReal << " de dano " << endl;
                        archivo << (*enemigoMaxVida2)->getNombre() << "  - Vida : " << (*enemigoMaxVida2)->getVida() << endl;
                    }
                    archivo << endl;

                    // Vemos si la unidad es Zerg, aumentamo lo de autodestrucion, si tiene esta habilidad, explota después de atacar
                    if ((unidad2)->getRaza() == Raza::Zerg)
                    {
                        CZerg *unidadZerg2 = dynamic_cast<CZerg *>((unidad2));
                        if ((unidadZerg2)->getAutodestruccion() == true)
                        {
                            (unidadZerg2)->setVida(0);
                            cout << "La unidad " << unidadZerg2->getNombre() << " ha explotado" << endl;
                            archivo << "La unidad " << unidadZerg2->getNombre() << " ha explotado" << endl;
                            // elimiar a la unidad herore si explota
                            HeoresSquad2.erase(find(HeoresSquad2.begin(), HeoresSquad2.end(), unidadZerg2));
                        }
                    }
                    // ver si el enemigo murio
                    if ((*enemigoMaxVida2)->getVida() <= 0)
                    {
                        cout << (*enemigoMaxVida2)->getNombre() << " ha muerto" << endl;
                        archivo << (*enemigoMaxVida2)->getNombre() << " ha muerto" << endl;
                        // eliminamos al enemigo *enemigoMaxVida2 del vector de heroes del squad1
                        HeoresSquad1.erase(find(HeoresSquad1.begin(), HeoresSquad1.end(), *enemigoMaxVida2));
                    }
                } // aqui termina el if de la vida del enemigo
            }     // aqui termina el for del squad 2
            // Eliminar unidades muertas y se actualiza el enemigo con mayor vida
            HeoresSquad1.erase(remove_if(HeoresSquad1.begin(), HeoresSquad1.end(),
                                         [](CUnidad *u)
                                         { return u->getVida() <= 0; }),
                               HeoresSquad1.end());
            HeoresSquad2.erase(remove_if(HeoresSquad2.begin(), HeoresSquad2.end(),
                                         [](CUnidad *u)
                                         { return u->getVida() <= 0; }),
                               HeoresSquad2.end());

        } // termian el for del squad 1
        cout << endl;
        turno++;
    } // aqui termina el while
    archivo << endl;

    // Imprimir resultado de la batalla
    if (HeoresSquad1.empty())
    {
        cout << "Gana " << jugador2 << "con su  squad 2!" << endl;
        archivo << "Gana " << jugador2 << "con su  squad 2!" << endl;
    }
    else
    {
        cout << "Gana " << jugador1 << "con su squad 1!" << endl;
        archivo << "Gana " << jugador1 << " con su squad 1!" << endl;
    }
    archivo.close();

    // Liberar memoria de las instancias creadas
    for (auto &unidad : HeoresSquad1)
    {
        delete unidad;
    }
    for (auto &unidad : HeoresSquad2)
    {
        delete unidad;
    }
    for (int i = 0; i < 3; i++)
    {
        delete[] matrizEspecial[i];
    }
    delete[] matrizEspecial;

    return 0;
}