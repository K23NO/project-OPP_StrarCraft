#include <iostream>
#include <iomanip> // para usar setw()
#include <string>
#include <vector>
#include <algorithm>  // para usar min() y max() 
#include <fstream> // para usar ofstream


using namespace std;

enum class TipoUnidad { Terrestre, Aereo };
enum class TamanioUnidad { Pequeno, Mediano, Grande };
enum class TipoDanoAereo { Normal, Explosivo, Contusivo };
enum class TipoDanoTerrestre { Normal, Explosivo, Contusivo };
enum class Raza { Terran, Protos, Zerg };

ostream& operator<<(std::ostream& out, const TipoDanoTerrestre value){
    switch (value)
    {
    case TipoDanoTerrestre::Normal:
        out << "Normal";
        break;
    case TipoDanoTerrestre::Explosivo:
        out << "Explosivo";
        break;
    case TipoDanoTerrestre::Contusivo:
        out << "Contusivo";
        break;
    } 
    return out;
}
ostream& operator<<(std::ostream& out, const TipoDanoAereo value){
    switch (value)
    {
    case TipoDanoAereo::Normal:
        out << "Normal";
        break;
    case TipoDanoAereo::Explosivo:
        out << "Explosivo";
        break;
    case TipoDanoAereo::Contusivo:
        out << "Contusivo";
        break;
    }
    return out;
}
ostream& operator<<(std::ostream& out, const TamanioUnidad value){
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

std::ostream& operator<<(std::ostream& out, const Raza value){
  const char* s = 0;
  #define PROCESS_VAL(p) case(p): s = #p; break;
  switch(value){
    PROCESS_VAL(Raza::Terran);
    PROCESS_VAL(Raza::Protos);
    PROCESS_VAL(Raza::Zerg);
  }
  #undef PROCESS_VAL
 out << s;
return out;
}

ostream& operator<<(std::ostream& out, const TipoUnidad value){
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

class CUnidad {
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

    
   //Todos los getters para imprimir la tabla de datos
    string getNombre(){ return _nombre;}
    int getVida(){ return _vida;}
    int getBlindaje(){ return _blindaje;}
    int getDanoTerrestre(){ return _danoTerrestre;}
    TipoDanoTerrestre getTipoDanoTerrestre(){ return _tipoDanoTerrestre;}
    int getDanoAereo(){ return _danoAereo;}
    TipoDanoAereo getTipoDanoAereo(){ return _tipoDanoAereo;}
    TamanioUnidad getTamanio(){ return _tamanio;}
    TipoUnidad getTipo(){ return _tipo;}
    Raza getRaza(){ return _raza;}
    // seters para poder actualizar la vida
    void setVida(int vida){ _vida = vida;}
    void setRaza(Raza raza){ _raza = raza;}

   
    //Destructor
    virtual ~CUnidad(){} // declaranndo aquim, ya no es necesario declarar en cada clase

};
//Los puntos de blindaje, le restan en % al dano de ataque. Inlcusive, le restan si este previamente ha sido mutiplicado por los factores de la matriz especial
class CTerran : public CUnidad {
public:
    CTerran(string nombre, int vida, int blindaje, int danoTerrestre, TipoDanoTerrestre tipoDano_Terrestre, int danoAereo, TipoDanoAereo tipoDano_Aereo, TamanioUnidad tamanio, TipoUnidad tipo)
        : CUnidad(nombre, vida, blindaje, danoTerrestre, tipoDano_Terrestre, danoAereo, tipoDano_Aereo, tamanio, tipo, Raza::Terran) {}

 

};

class CProtos : public CUnidad {
private:
    int _escudo;
public:
    //Constructor de protos guion bajo
    CProtos(string nombre, int vida, int blindaje, int danoTerrestre, TipoDanoTerrestre tipoDanoTerrestre, int danoAereo, TipoDanoAereo tipoDanoAereo, TamanioUnidad tamanio, TipoUnidad tipo, int escudo)
        : CUnidad(nombre, vida, blindaje, danoTerrestre, tipoDanoTerrestre, danoAereo, tipoDanoAereo, tamanio, tipo, Raza::Protos), _escudo(escudo) {}
    
    //funcion para obtener acceso al escudo
    int getEscudo(){ return _escudo;}

    //actualizar el escudo
    void setEscudo(int escudo){ _escudo = escudo;}
    
};

class CZerg : public CUnidad {
private:
    bool autodestruccion;
    bool primerAtaque;
public:
    CZerg(string nombre, int vida, int blindaje, int danoTerrestre, TipoDanoTerrestre tipoDano_Terrestre, int danoAereo, TipoDanoAereo tipoDano_Aereo, TamanioUnidad tamanio, TipoUnidad tipo, bool autodestruccion)
        : CUnidad(nombre, vida, blindaje, danoTerrestre, tipoDano_Terrestre, danoAereo, tipoDano_Aereo, tamanio, tipo, Raza::Zerg), autodestruccion(autodestruccion), primerAtaque(true) {}

    //funcion para obtener acceso a la  autodestruccion y primer ataque
    bool getAutodestruccion(){ return autodestruccion;}
    bool getPrimerAtaque(){ return primerAtaque;}
    // seter 
    void setPrimerAtaque(bool primerAtaque){ this->primerAtaque = primerAtaque;}

};

void imprimirTabla(CUnidad& unidad){
    //cout<<left<<setw(15)<<"Nombre"<<setw(10)<<"Vida"<<setw(10)<<"Blindaje"<<setw(18)<<"Daño Terrestre"<<setw(15)<<"Daño Aereo"<<setw(10)<<"Tamaño"<<setw(10)<<"Tipo"<<endl;
   
    //todos los geters

    cout<<left<<setw(15)<<unidad.getNombre()<<setw(10)<<unidad.getVida()<<setw(10)<<unidad.getBlindaje()<<setw(18)<<unidad.getDanoTerrestre()<<setw(15)<<unidad.getDanoAereo()<<setw(10)<<unidad.getTamanio()<<setw(10)<<unidad.getTipo()<<endl;
}
void imprimirTabla(CUnidad* unidad){
    //cout<<left<<setw(15)<<"Nombre"<<setw(10)<<"Vida"<<setw(10)<<"Blindaje"<<setw(18)<<"Daño Terrestre"<<setw(15)<<"Daño Aereo"<<setw(10)<<"Tamaño"<<setw(10)<<"Tipo"<<endl;
   
    if (dynamic_cast<CTerran*>(unidad) == nullptr) {
        cout << "Terran ";
    }
    else if (dynamic_cast<CProtos*>(unidad) == nullptr) {
        cout << "Protos ";
    }
    else if (dynamic_cast<CZerg*>(unidad) == nullptr) {
        cout << "Zerg ";
    }

    cout<<left<<setw(15)<<unidad->getNombre()<<setw(10)<<unidad->getVida()<<setw(10)<<unidad->getBlindaje()<<setw(18)<<unidad->getDanoTerrestre()<<setw(15)<<unidad->getDanoAereo()<<setw(10)<<unidad->getTamanio()<<setw(10)<<unidad->getTipo()<<endl;
}
// funcion con la que se puede imprimir todas las caractericticas de los heroes

// funcion para imprimir los datos de los heroes de la raza que se seleciono
void ImprimirDatos(vector<CUnidad*> Base){
    for (int i = 0; i < Base.size(); i++) {
        imprimirTabla(Base[i]);
    }
}

int main(){
    string jugador1, jugador2;
    int squad1, squad2, raza_squad1, raza_squad2;
    ofstream archivo;
    archivo.open("Partida.txt", ios::out);

    cout<<"-----Bienvenidos al juego de StarCraft: Brood War-------\n"<<endl;
    archivo<<"-----Bienvenidos al juego de StarCraft: Brood War-------\n"<<endl;
    cout<<"Ingrese el nombre del jugador 1: ";
    cin>>jugador1;
    cout<<"Ingrese el nombre del jugador 2: ";
    cin>>jugador2;
    cout<<"Hola "<<jugador1<<" y "<<jugador2<<", vamos a jugar"<<endl;
    archivo<<"Hola "<<jugador1<<" y "<<jugador2<<", vamos a jugar"<<endl;
    cout << endl;
    cout<< jugador1 << "¿De que raza sera su squad? "<<endl;
    cout<<"1. Terran"<<endl;
    cout<<"2. Protos"<<endl;
    cout<<"3. Zerg"<<endl;
    cin>> raza_squad1;
    cout<<jugador1<<"¿De cuantas unidades sera su squad?"<<endl;
    cin>>squad1;
    cout<< "Los heroes disponibles son: "<<endl;
    cout<<left<<setw(15)<<"Nombre"<<setw(10)<<"Vida"<<setw(10)<<"Blindaje"<<setw(18)<<"Daño Terrestre"<<setw(15)<<"Daño Aereo"<<setw(10)<<"Tamaño"<<setw(10)<<"Tipo"<<endl;

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
    CTerran Valkyrie("Valkyrie", 200, 2, 0, TipoDanoTerrestre::Normal, 48 , TipoDanoAereo::Explosivo, TamanioUnidad::Grande, TipoUnidad::Aereo);
    CTerran Vulture("Vulture", 80, 0, 20, TipoDanoTerrestre::Contusivo, 0, TipoDanoAereo::Normal, TamanioUnidad::Mediano, TipoUnidad::Terrestre);
    CTerran Wraith("Wraith", 120, 0, 8, TipoDanoTerrestre::Normal, 20, TipoDanoAereo::Explosivo, TamanioUnidad::Grande, TipoUnidad::Aereo);

    /*Definicion de los herores Protos*/ 
    //Escudo el ultimo parametro
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
    //CUnidad(nombre, vida, blindaje, danoTerrestre, tipoDano_Terrestre, danoAereo, tipoDano_Aereo, tamanio, tipo, Raza::Zerg), autodestruccion(autodestruccion), primerAtaque(true) 
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
    
    vector<CUnidad*> squad1_2;
    switch (raza_squad1)
    {
    case 1: // terran   
        imprimirTabla(Batlecuirser);
        imprimirTabla(Firebat);
        imprimirTabla(Ghost);
        imprimirTabla(Goliath);
        imprimirTabla(Marine);
        imprimirTabla(Duran);
        imprimirTabla(Scv);
        imprimirTabla(Tank);
        imprimirTabla(Valkyrie);
        imprimirTabla(Vulture);
        imprimirTabla(Wraith);
        // agregar estos heores al vector donde se guardaran los heroes de la raza que se eligio
        squad1_2.push_back( new CTerran("Batlecuirser", 500, 3, 25, TipoDanoTerrestre::Normal, 25, TipoDanoAereo::Normal, TamanioUnidad::Grande, TipoUnidad::Aereo));
        squad1_2.push_back( new CTerran("Firebat", 50, 1, 16, TipoDanoTerrestre::Contusivo, 0, TipoDanoAereo::Normal, TamanioUnidad::Pequeno, TipoUnidad::Terrestre));
        squad1_2.push_back( new CTerran("Ghost", 45, 0, 10, TipoDanoTerrestre::Contusivo, 10, TipoDanoAereo::Contusivo, TamanioUnidad::Pequeno, TipoUnidad::Terrestre));
        squad1_2.push_back( new CTerran("Goliath", 125, 1, 12, TipoDanoTerrestre::Normal, 20, TipoDanoAereo::Explosivo, TamanioUnidad::Grande, TipoUnidad::Aereo));
        squad1_2.push_back( new CTerran("Marine", 40, 0, 6, TipoDanoTerrestre::Normal, 6, TipoDanoAereo::Normal, TamanioUnidad::Pequeno, TipoUnidad::Terrestre));
        squad1_2.push_back( new CTerran("Duran", 200, 2, 25, TipoDanoTerrestre::Contusivo, 25, TipoDanoAereo::Contusivo, TamanioUnidad::Pequeno, TipoUnidad::Terrestre));
        squad1_2.push_back( new CTerran("Scv", 60, 0, 5, TipoDanoTerrestre::Normal, 0, TipoDanoAereo::Normal, TamanioUnidad::Pequeno, TipoUnidad::Terrestre));
        squad1_2.push_back( new CTerran("Tank", 150, 1, 70, TipoDanoTerrestre::Explosivo, 0, TipoDanoAereo::Normal, TamanioUnidad::Grande, TipoUnidad::Terrestre));
        squad1_2.push_back( new CTerran("Valkyrie", 200, 2, 0, TipoDanoTerrestre::Normal, 48 , TipoDanoAereo::Explosivo, TamanioUnidad::Grande, TipoUnidad::Aereo));
        squad1_2.push_back( new CTerran("Vulture", 80, 0, 20, TipoDanoTerrestre::Contusivo, 0, TipoDanoAereo::Normal, TamanioUnidad::Mediano, TipoUnidad::Terrestre));
        squad1_2.push_back( new CTerran("Wraith", 120, 0, 8, TipoDanoTerrestre::Normal, 20, TipoDanoAereo::Explosivo, TamanioUnidad::Grande, TipoUnidad::Aereo));
        
        break;
    case 2: // protos
        imprimirTabla(Arbiter);
        imprimirTabla(Archon);
        imprimirTabla(Carrier);
        imprimirTabla(Corsair);
        imprimirTabla(Templar);
        imprimirTabla(Dragoon);
        imprimirTabla(Probe);
        imprimirTabla(Reaver);
        imprimirTabla(Scout);
        imprimirTabla(Zelaot);  
        // agregar estos heores al vector donde se guardaran los heroes de la raza que se eligio
        squad1_2.push_back(new CProtos ("Arbiter", 200, 1, 10, TipoDanoTerrestre::Explosivo, 10, TipoDanoAereo::Explosivo, TamanioUnidad::Grande, TipoUnidad::Aereo, 150));
        squad1_2.push_back(new CProtos ("Archon", 10, 0, 30, TipoDanoTerrestre::Normal, 30, TipoDanoAereo::Normal, TamanioUnidad::Grande, TipoUnidad::Terrestre, 350));
        squad1_2.push_back(new CProtos ("Carrier", 300, 4, 48, TipoDanoTerrestre::Normal, 48, TipoDanoAereo::Normal, TamanioUnidad::Grande, TipoUnidad::Aereo, 150));
        squad1_2.push_back(new CProtos ("Corsair", 100, 1, 0, TipoDanoTerrestre::Normal, 6, TipoDanoAereo::Explosivo, TamanioUnidad::Mediano, TipoUnidad::Aereo, 80));
        squad1_2.push_back(new CProtos ("Templar", 80, 1, 40, TipoDanoTerrestre::Normal, 0, TipoDanoAereo::Normal, TamanioUnidad::Pequeno, TipoUnidad::Terrestre, 40));
        squad1_2.push_back(new CProtos ("Dragoon", 100, 1, 20, TipoDanoTerrestre::Explosivo, 20, TipoDanoAereo::Explosivo, TamanioUnidad::Grande, TipoUnidad::Terrestre, 80));
        squad1_2.push_back(new CProtos ("Probe", 20, 0, 5, TipoDanoTerrestre::Normal, 0, TipoDanoAereo::Normal, TamanioUnidad::Pequeno, TipoUnidad::Terrestre, 20));
        squad1_2.push_back(new CProtos ("Reaver", 100, 0, 125, TipoDanoTerrestre::Normal, 0, TipoDanoAereo::Normal, TamanioUnidad::Grande, TipoUnidad::Terrestre, 80));
        squad1_2.push_back(new CProtos ("Scout", 150, 0, 8, TipoDanoTerrestre::Normal, 28, TipoDanoAereo::Explosivo, TamanioUnidad::Grande, TipoUnidad::Aereo, 100));
        squad1_2.push_back(new CProtos ("Zelaot", 100, 1, 16, TipoDanoTerrestre::Normal, 0, TipoDanoAereo::Normal, TamanioUnidad::Pequeno, TipoUnidad::Terrestre, 60));

        break;
    case 3: // zerg
        imprimirTabla(Broodling);
        imprimirTabla(Devourer);
        imprimirTabla(Drone);
        imprimirTabla(Hydralisk);
        imprimirTabla(Infested);
        imprimirTabla(Lurker);
        imprimirTabla(Mutalisk);
        imprimirTabla(Scourge);
        imprimirTabla(Ultralisk);
        imprimirTabla(Zergling);   
        // agregar estos heores al vector donde se guardaran los heroes de la raza que se eligio
        squad1_2.push_back(new CZerg ("Broodling", 30, 0, 4, TipoDanoTerrestre::Normal, 0, TipoDanoAereo::Normal, TamanioUnidad::Pequeno, TipoUnidad::Terrestre, false));
        squad1_2.push_back(new CZerg ("Devourer", 250, 2, 0, TipoDanoTerrestre::Normal, 25, TipoDanoAereo::Explosivo, TamanioUnidad::Grande, TipoUnidad::Aereo, false));
        squad1_2.push_back(new CZerg ("Drone", 40, 0, 5, TipoDanoTerrestre::Normal, 0, TipoDanoAereo::Normal, TamanioUnidad::Pequeno, TipoUnidad::Terrestre, false));
        squad1_2.push_back(new CZerg ("Hydralisk", 80, 0, 10, TipoDanoTerrestre::Explosivo, 10, TipoDanoAereo::Explosivo, TamanioUnidad::Mediano, TipoUnidad::Aereo, false));
        squad1_2.push_back(new CZerg ("Infested", 60, 0, 500, TipoDanoTerrestre::Explosivo, 0, TipoDanoAereo::Normal, TamanioUnidad::Pequeno, TipoUnidad::Terrestre, true));
        squad1_2.push_back(new CZerg ("Lurker", 125, 1, 20, TipoDanoTerrestre::Normal, 0, TipoDanoAereo::Normal, TamanioUnidad::Mediano, TipoUnidad::Terrestre, false));
        squad1_2.push_back(new CZerg ("Mutalisk", 120, 0, 9, TipoDanoTerrestre::Normal, 9, TipoDanoAereo::Normal, TamanioUnidad::Pequeno, TipoUnidad::Aereo, false));
        squad1_2.push_back(new CZerg ("Scourge", 25, 0, 0, TipoDanoTerrestre::Normal, 110, TipoDanoAereo::Normal, TamanioUnidad::Pequeno, TipoUnidad::Aereo, true));
        squad1_2.push_back(new CZerg ("Ultralisk", 400, 3, 20, TipoDanoTerrestre::Normal, 0, TipoDanoAereo::Normal, TamanioUnidad::Grande, TipoUnidad::Terrestre, false));
        squad1_2.push_back(new CZerg ("Zergling", 35, 0, 5, TipoDanoTerrestre::Normal, 0, TipoDanoAereo::Normal, TamanioUnidad::Pequeno, TipoUnidad::Terrestre, false));
        break;

    default:
        cout<< "Opcion invalida"<<endl;
        break;
    }

    // para el numero de squad que requiero 
    // vector que guarde los heores con sus clases
    vector<CUnidad*> HeoresSquad1;
    for(int i= 0; i<squad1; ){
        string var;
        cout<<"Ingrese el nombre del heroe que desea: ";
        cin>>var;
        auto iterador = find_if(squad1_2.begin(), squad1_2.end(), [&var](CUnidad* unidad){return unidad->getNombre() == var;});
        if(iterador != squad1_2.end()){
            HeoresSquad1.push_back(*iterador);
        i++;}
        else{
            cout<<"No se encontro el heroe"<<endl;
        }
    }
    cout<<"Los heroes que selecciono "<<jugador1<<" son: "<<endl;
    archivo<<"Los heroes que selecciono "<<jugador1<<" son: "<<endl;

    for(auto i: HeoresSquad1){
        cout<<"\t" <<i->getNombre()<<endl;
        imprimirTabla(i);
        archivo<<"\t" <<i->getNombre()<<endl;
    }
    cout << endl;

    //Implementamos jugador 2 
    cout<< jugador2 << "¿De que raza sera su squad? "<<endl;
    cout<<"1. Terran"<<endl;
    cout<<"2. Protos"<<endl;
    cout<<"3. Zerg"<<endl;
    cin>> raza_squad2;
    cout<<jugador2<<"¿De cuantas unidades sera su squad?"<<endl;
    cin>>squad2;
    cout<<"Los heroes disponibles son: "<<endl;
    cout<<left<<setw(15)<<"Nombre"<<setw(10)<<"Vida"<<setw(10)<<"Blindaje"<<setw(18)<<"Daño Terrestre"<<setw(15)<<"Daño Aereo"<<setw(10)<<"Tamaño"<<setw(10)<<"Tipo"<<endl;

    vector<CUnidad*> squad2_2;
    switch (raza_squad2){
        case 1: // terran
        imprimirTabla(Batlecuirser);
        imprimirTabla(Firebat);
        imprimirTabla(Ghost);
        imprimirTabla(Goliath);
        imprimirTabla(Marine);
        imprimirTabla(Duran);
        imprimirTabla(Scv);
        imprimirTabla(Tank);
        imprimirTabla(Valkyrie);
        imprimirTabla(Vulture);
        imprimirTabla(Wraith);
        // agregar estos heores al vector donde se guardaran los heroes de la raza que se eligio
        squad2_2.push_back( new CTerran("Batlecuirser", 500, 3, 25, TipoDanoTerrestre::Normal, 25, TipoDanoAereo::Normal, TamanioUnidad::Grande, TipoUnidad::Aereo));
        squad2_2.push_back( new CTerran("Firebat", 50, 1, 16, TipoDanoTerrestre::Contusivo, 0, TipoDanoAereo::Normal, TamanioUnidad::Pequeno, TipoUnidad::Terrestre));
        squad2_2.push_back( new CTerran("Ghost", 45, 0, 10, TipoDanoTerrestre::Contusivo, 10, TipoDanoAereo::Contusivo, TamanioUnidad::Pequeno, TipoUnidad::Terrestre));
        squad2_2.push_back( new CTerran("Goliath", 125, 1, 12, TipoDanoTerrestre::Normal, 20, TipoDanoAereo::Explosivo, TamanioUnidad::Grande, TipoUnidad::Aereo));
        squad2_2.push_back( new CTerran("Marine", 40, 0, 6, TipoDanoTerrestre::Normal, 6, TipoDanoAereo::Normal, TamanioUnidad::Pequeno, TipoUnidad::Terrestre));
        squad2_2.push_back( new CTerran("Duran", 200, 2, 25, TipoDanoTerrestre::Contusivo, 25, TipoDanoAereo::Contusivo, TamanioUnidad::Pequeno, TipoUnidad::Terrestre));
        squad2_2.push_back( new CTerran("Scv", 60, 0, 5, TipoDanoTerrestre::Normal, 0, TipoDanoAereo::Normal, TamanioUnidad::Pequeno, TipoUnidad::Terrestre));
        squad2_2.push_back( new CTerran("Tank", 150, 1, 70, TipoDanoTerrestre::Explosivo, 0, TipoDanoAereo::Normal, TamanioUnidad::Grande, TipoUnidad::Terrestre));
        squad2_2.push_back( new CTerran("Valkyrie", 200, 2, 0, TipoDanoTerrestre::Normal, 48 , TipoDanoAereo::Explosivo, TamanioUnidad::Grande, TipoUnidad::Aereo));
        squad2_2.push_back( new CTerran("Vulture", 80, 0, 20, TipoDanoTerrestre::Contusivo, 0, TipoDanoAereo::Normal, TamanioUnidad::Mediano, TipoUnidad::Terrestre));
        squad2_2.push_back( new CTerran("Wraith", 120, 0, 8, TipoDanoTerrestre::Normal, 20, TipoDanoAereo::Explosivo, TamanioUnidad::Grande, TipoUnidad::Aereo));
        
        break;
    case 2: // protos
        imprimirTabla(Arbiter);
        imprimirTabla(Archon);
        imprimirTabla(Carrier);
        imprimirTabla(Corsair);
        imprimirTabla(Templar);
        imprimirTabla(Dragoon);
        imprimirTabla(Probe);
        imprimirTabla(Reaver);
        imprimirTabla(Scout);
        imprimirTabla(Zelaot);  
        // agregar estos heores al vector donde se guardaran los heroes de la raza que se eligio
        squad2_2.push_back(new CProtos ("Arbiter", 200, 1, 10, TipoDanoTerrestre::Explosivo, 10, TipoDanoAereo::Explosivo, TamanioUnidad::Grande, TipoUnidad::Aereo, 150));
        squad2_2.push_back(new CProtos ("Archon", 10, 0, 30, TipoDanoTerrestre::Normal, 30, TipoDanoAereo::Normal, TamanioUnidad::Grande, TipoUnidad::Terrestre, 350));
        squad2_2.push_back(new CProtos ("Carrier", 300, 4, 48, TipoDanoTerrestre::Normal, 48, TipoDanoAereo::Normal, TamanioUnidad::Grande, TipoUnidad::Aereo, 150));
        squad2_2.push_back(new CProtos ("Corsair", 100, 1, 0, TipoDanoTerrestre::Normal, 6, TipoDanoAereo::Explosivo, TamanioUnidad::Mediano, TipoUnidad::Aereo, 80));
        squad2_2.push_back(new CProtos ("Templar", 80, 1, 40, TipoDanoTerrestre::Normal, 0, TipoDanoAereo::Normal, TamanioUnidad::Pequeno, TipoUnidad::Terrestre, 40));
        squad2_2.push_back(new CProtos ("Dragoon", 100, 1, 20, TipoDanoTerrestre::Explosivo, 20, TipoDanoAereo::Explosivo, TamanioUnidad::Grande, TipoUnidad::Terrestre, 80));
        squad2_2.push_back(new CProtos ("Probe", 20, 0, 5, TipoDanoTerrestre::Normal, 0, TipoDanoAereo::Normal, TamanioUnidad::Pequeno, TipoUnidad::Terrestre, 20));
        squad2_2.push_back(new CProtos ("Reaver", 100, 0, 125, TipoDanoTerrestre::Normal, 0, TipoDanoAereo::Normal, TamanioUnidad::Grande, TipoUnidad::Terrestre, 80));
        squad2_2.push_back(new CProtos ("Scout", 150, 0, 8, TipoDanoTerrestre::Normal, 28, TipoDanoAereo::Explosivo, TamanioUnidad::Grande, TipoUnidad::Aereo, 100));
        squad2_2.push_back(new CProtos ("Zelaot", 100, 1, 16, TipoDanoTerrestre::Normal, 0, TipoDanoAereo::Normal, TamanioUnidad::Pequeno, TipoUnidad::Terrestre, 60));
        break;

    case 3: // zerg
        imprimirTabla(Broodling);
        imprimirTabla(Devourer);
        imprimirTabla(Drone);
        imprimirTabla(Hydralisk);
        imprimirTabla(Infested);
        imprimirTabla(Lurker);
        imprimirTabla(Mutalisk);
        imprimirTabla(Scourge);
        imprimirTabla(Ultralisk);
        imprimirTabla(Zergling);   
        // agregar estos heores al vector donde se guardaran los heroes de la raza que se eligio
        squad2_2.push_back(new CZerg ("Broodling", 30, 0, 4, TipoDanoTerrestre::Normal, 0, TipoDanoAereo::Normal, TamanioUnidad::Pequeno, TipoUnidad::Terrestre, false));
        squad2_2.push_back(new CZerg ("Devourer", 250, 2, 0, TipoDanoTerrestre::Normal, 25, TipoDanoAereo::Explosivo, TamanioUnidad::Grande, TipoUnidad::Aereo, false));
        squad2_2.push_back(new CZerg ("Drone", 40, 0, 5, TipoDanoTerrestre::Normal, 0, TipoDanoAereo::Normal, TamanioUnidad::Pequeno, TipoUnidad::Terrestre, false));
        squad2_2.push_back(new CZerg ("Hydralisk", 80, 0, 10, TipoDanoTerrestre::Explosivo, 10, TipoDanoAereo::Explosivo, TamanioUnidad::Mediano, TipoUnidad::Aereo, false));
        squad2_2.push_back(new CZerg ("Infested", 60, 0, 500, TipoDanoTerrestre::Explosivo, 0, TipoDanoAereo::Normal, TamanioUnidad::Pequeno, TipoUnidad::Terrestre, true));
        squad2_2.push_back(new CZerg ("Lurker", 125, 1, 20, TipoDanoTerrestre::Normal, 0, TipoDanoAereo::Normal, TamanioUnidad::Mediano, TipoUnidad::Terrestre, false));
        squad2_2.push_back(new CZerg ("Mutalisk", 120, 0, 9, TipoDanoTerrestre::Normal, 9, TipoDanoAereo::Normal, TamanioUnidad::Pequeno, TipoUnidad::Aereo, false));
        squad2_2.push_back(new CZerg ("Scourge", 25, 0, 0, TipoDanoTerrestre::Normal, 110, TipoDanoAereo::Normal, TamanioUnidad::Pequeno, TipoUnidad::Aereo, true));
        squad2_2.push_back(new CZerg ("Ultralisk", 400, 3, 20, TipoDanoTerrestre::Normal, 0, TipoDanoAereo::Normal, TamanioUnidad::Grande, TipoUnidad::Terrestre, false));
        squad2_2.push_back(new CZerg ("Zergling", 35, 0, 5, TipoDanoTerrestre::Normal, 0, TipoDanoAereo::Normal, TamanioUnidad::Pequeno, TipoUnidad::Terrestre, false));
        break;

    default:
        cout<< "Opcion invalida"<<endl;
        break;
    }

    vector<CUnidad*> HeoresSquad2;
    for(int i= 0; i<squad2; ){
        string var;
        cout<<"Ingrese el nombre del heroe que desea: ";
        cin>>var;
        auto iterador = find_if(squad2_2.begin(), squad2_2.end(), [&var](CUnidad* unidad){return unidad->getNombre() == var;});
        if(iterador != squad2_2.end()){
            HeoresSquad2.push_back(*iterador);
        i++;}
        else{
            cout<<"No se encontro el heroe"<<endl;
        }
    }

    cout<<"Los heroes que selecciono "<<jugador2<<" son: "<<endl;
    archivo<<"Los heroes que selecciono "<<jugador2<<" son: "<<endl;
    for(auto i: HeoresSquad2){
        cout<<"\t" <<i->getNombre()<<endl;
        imprimirTabla(i);
        archivo<<"\t" <<i->getNombre()<<endl;
    }

    // La tabla de las condiciones especiales, de tamano y el daño que hace a cada tipo de unidad
    // expresarla en una matriz de 3x3
    //columna -> tamaño del enemigo
    // columna 1 -> pequeno
    // columna 2 -> mediano
    // columna 3 -> grande
    // fila->  tipo de ataque
    // fila 1 . Normal
    // fila 2 . Explosivo
    // fila 3 . Contusivo
    // memoria dinamica -> PARA LA MATRIZ ESPECIAL
    double **matrizEspecial = new double*[3];
    for(int i = 0; i < 3; i++){
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
    
    cout<<"Comienza la batalla"<<endl;
    archivo<<endl;
    archivo<<"Comienza la batalla"<<endl;
    archivo<<endl;

    // el vector HeoresSquad1 y HeoresSquad2 tienen los nombre de los heroes que se seleccionaron
    // se implementa el juego
    // implementamos el ciclo while para que se repita el juego hasta que uno de los dos jugadores se quede sin heroes
    // la batalla será por turnos. 
    //Los puntos de blindaje, le restan en % al dano de ataque. Inlcusive, le restan si este previamente ha sido mutiplicado por los factores de la matriz especial
    int turno = 1;
    // Ciclo de batalla
    while (!HeoresSquad1.empty() && !HeoresSquad2.empty()) {
        cout<< "\tTurno: " << turno << endl;
        archivo<< "\tTurno: " << turno << endl;
    // Buscar la unidad enemiga con mayor vida
        auto enemigoMaxVida1 = max_element(HeoresSquad2.begin(), HeoresSquad2.end(),
        [](CUnidad* a, CUnidad* b) { return a->getVida() < b->getVida(); });
        
        auto enemigoMaxVida2 = max_element(HeoresSquad1.begin(), HeoresSquad1.end(),
            [](CUnidad* a, CUnidad* b) { return a->getVida() < b->getVida(); });

    // Hacer que todo el grupo ataque al enemigo con mayor vida
    /* Los puntos de blindaje, le restan en % al dano de ataque. Si esl numero de blindaje es 1, se le resta el 10% del dano de ataque
    Inclusive, le restan si este previamente ha sido mutiplicado por los factores de la matriz especial */
        
    //En caso de que la unidad sea protos, primero se debe de ver si tiene escudo
    // si tiene escudo, se le restara el dano al escudo
    // hasta que este se acabe y luego se le restara a la vida
        for (auto& unidad : HeoresSquad1) {
            if (enemigoMaxVida1 != HeoresSquad2.end() && (*enemigoMaxVida1)->getVida() > 0) {
                double factorDanio;
                double danoReal;
                // ver si el tipo del enemigo con mayor vida es terrestre o aerero
                if ((*enemigoMaxVida1)->getTipo() == TipoUnidad::Terrestre) {
                    // unidad usará el tipo de ataque terrestre 
                    // ver que tipo de dano terrestre tiene la unidad
                    if(unidad->getTipoDanoTerrestre() == TipoDanoTerrestre::Normal) { // fila 0
                        if ((*enemigoMaxVida1)->getTamanio() == TamanioUnidad::Pequeno) {
                            factorDanio = matrizEspecial[0][0];
                            }
                        else if ((*enemigoMaxVida1)->getTamanio() == TamanioUnidad::Mediano) {
                            factorDanio = matrizEspecial[0][1];
                            }
                        else if ((*enemigoMaxVida1)->getTamanio() == TamanioUnidad::Grande) {
                            factorDanio = matrizEspecial[0][2];
                        }
                    }
                    else if(unidad->getTipoDanoTerrestre() == TipoDanoTerrestre::Explosivo) { // fila 1
                        if ((*enemigoMaxVida1)->getTamanio() == TamanioUnidad::Pequeno) {
                            factorDanio = matrizEspecial[1][0];
                        }
                        else if ((*enemigoMaxVida1)->getTamanio() == TamanioUnidad::Mediano) {
                            factorDanio = matrizEspecial[1][1];
                        }
                        else if ((*enemigoMaxVida1)->getTamanio() == TamanioUnidad::Grande) {
                        factorDanio = matrizEspecial[1][2];
                        }
                    }
                    else if(unidad->getTipoDanoTerrestre() == TipoDanoTerrestre::Contusivo) {  // fila 2

                        if ((*enemigoMaxVida1)->getTamanio() == TamanioUnidad::Pequeno) {
                            factorDanio = matrizEspecial[2][0];
                            }
                        else if ((*enemigoMaxVida1)->getTamanio() == TamanioUnidad::Mediano) {
                            factorDanio = matrizEspecial[2][1];
                            }
                        else if ((*enemigoMaxVida1)->getTamanio() == TamanioUnidad::Grande) {
                            factorDanio = matrizEspecial[2][2];
                        }
                    }
                    factorDanio = factorDanio * (1 - (*enemigoMaxVida1)->getBlindaje());
                    danoReal = unidad->getDanoTerrestre() * factorDanio;
                }
                else  { // aereo
                    if(unidad->getTipoDanoTerrestre() == TipoDanoTerrestre::Normal) { // fila 0
                        if ((*enemigoMaxVida1)->getTamanio() == TamanioUnidad::Pequeno) {
                            factorDanio = matrizEspecial[0][0];
                            }
                        else if ((*enemigoMaxVida1)->getTamanio() == TamanioUnidad::Mediano) {
                            factorDanio = matrizEspecial[0][1];
                            }
                        else if ((*enemigoMaxVida1)->getTamanio() == TamanioUnidad::Grande) {
                            factorDanio = matrizEspecial[0][2];
                        }
                    }
                    else if(unidad->getTipoDanoTerrestre() == TipoDanoTerrestre::Explosivo) { // fila 1
                        if ((*enemigoMaxVida1)->getTamanio() == TamanioUnidad::Pequeno) {
                            factorDanio = matrizEspecial[1][0];
                        }
                        else if ((*enemigoMaxVida1)->getTamanio() == TamanioUnidad::Mediano) {
                            factorDanio = matrizEspecial[1][1];
                        }
                        else if ((*enemigoMaxVida1)->getTamanio() == TamanioUnidad::Grande) {
                        factorDanio = matrizEspecial[1][2];
                        }
                    }
                    else if(unidad->getTipoDanoTerrestre() == TipoDanoTerrestre::Contusivo) {  // fila 2

                        if ((*enemigoMaxVida1)->getTamanio() == TamanioUnidad::Pequeno) {
                            factorDanio = matrizEspecial[2][0];
                            }
                        else if ((*enemigoMaxVida1)->getTamanio() == TamanioUnidad::Mediano) {
                            factorDanio = matrizEspecial[2][1];
                            }
                        else if ((*enemigoMaxVida1)->getTamanio() == TamanioUnidad::Grande) {
                            factorDanio = matrizEspecial[2][2];
                        }
                    }
                    factorDanio = factorDanio * (1 - (*enemigoMaxVida1)->getBlindaje());
                    danoReal = unidad->getDanoAereo() * factorDanio;

                    
                }
                // ver si la unidad tiene escudo
                if((*enemigoMaxVida1)->getRaza() == Raza::Protos){
                        // transformano el enemigo a protos
                        CProtos *enemigoProtos = dynamic_cast<CProtos*>((*enemigoMaxVida1));
                        // ver si tiene escudo, si tiene primero se le resta al escudo y luego a la vida
                        if((enemigoProtos)->getEscudo() > 0){
                            (enemigoProtos)->setEscudo((enemigoProtos)->getEscudo() - danoReal);
                            if((enemigoProtos)->getEscudo() < 0){
                                (enemigoProtos)->setVida((*enemigoMaxVida1)->getVida() + (enemigoProtos)->getEscudo());
                                (enemigoProtos)->setEscudo(0);
                                    }
                                }
                        else{  // si no tiene escudo, se le resta a la vida
                            (enemigoProtos)->setVida((*enemigoMaxVida1)->getVida() - danoReal);
                        }
                    }
                else if((*enemigoMaxVida1)-> getRaza() == Raza::Zerg){
                        // lo del primer ataque y  la auto destruccion
                        /* Autodestruccion:Esta característica puede ser verdadera o falsa. Algunas unidades Zerg
                        se autodestruyen después de realizar un ataque y otras no. <
                        Las unidade zerg que se autodestruyen son: «Infested» y «Scrouge». Estas dos unidades
                        explotan al atacar a sus oponentes. Esto quiere decir que, al atacar, la unidad atacante 
                        muere inmediatamente después de hacerle daño al defensor */
                        /* Primer ataques : Las unidades Zerg recuperan 1 
                        punto de vida tras ser atacadas por primera vez, debido a que sus cuerpos se autogeneran. 
                        Sin embargo, esta autogeneración no se realiza si es que la unidad está viva*/
                        CZerg *enemigoZerg = dynamic_cast<CZerg*>((*enemigoMaxVida1));
                        if(enemigoZerg->getAutodestruccion() == true){
                            // la unidad atacante muere inmediatamente después de hacerle daño al defensor
                            // se le resta el dano a la vida del enemigo
                            enemigoZerg->setVida(enemigoZerg->getVida() - danoReal);
                            // la unidad atacante muere
                            unidad->setVida(0);
                        }
                        // primer ataque
                        if(enemigoZerg->getPrimerAtaque() == true){
                            // si es la primera vez que ataca, se le suma 1 a la vida
                            enemigoZerg->setVida(enemigoZerg->getVida() + 1);
                            // se le resta el dano a la vida del enemigo
                            enemigoZerg->setVida(enemigoZerg->getVida() - danoReal);
                        }
                        else{
                            // se le resta el dano a la vida del enemigo
                            enemigoZerg->setVida(enemigoZerg->getVida() - danoReal);
                        }
                    }
                    else{ // Terran 
                        (*enemigoMaxVida1)->setVida((*enemigoMaxVida1)->getVida() - danoReal);
                    }
                
                cout<<"La vida de "<<(*enemigoMaxVida1)->getNombre()<<" es: "<<(*enemigoMaxVida1)->getVida()<<endl;
                cout<< unidad->getNombre() << " ataca a " << (*enemigoMaxVida1)->getNombre() << " con " << danoReal << " de dano" << endl;
               
                archivo<<"La vida de "<<(*enemigoMaxVida1)->getNombre()<<" es: "<<(*enemigoMaxVida1)->getVida()<<endl;
                archivo<< unidad->getNombre() << " ataca a " << (*enemigoMaxVida1)->getNombre() << " con " << danoReal << " de dano" << endl;
                

                // ver si el enemigo murio
                if ((*enemigoMaxVida1)->getVida() <= 0) {
                    cout << (*enemigoMaxVida1)->getNombre() << " ha muerto" << endl;
                    archivo << (*enemigoMaxVida1)->getNombre() << " ha muerto" << endl;
                }
                
            } // termina el el if de la vida del enemigo
        for (auto& unidad : HeoresSquad2) {
            if (enemigoMaxVida2 != HeoresSquad1.end() && (*enemigoMaxVida2)->getVida() > 0) {
                double factorDanio;
                double danoReal;

                // ver si el tipo del enemigo con mayor vida es terrestre o aerero
                if ((*enemigoMaxVida2)->getTipo() == TipoUnidad::Terrestre) {
                
                    // unidad usará el tipo de ataque terrestre 
                    // ver que tipo de dano terrestre tiene la unidad
                    if(unidad->getTipoDanoTerrestre() == TipoDanoTerrestre::Normal) { // fila 0
                        if ((*enemigoMaxVida2)->getTamanio() == TamanioUnidad::Pequeno) {
                            factorDanio = matrizEspecial[0][0];
                            }
                        else if ((*enemigoMaxVida2)->getTamanio() == TamanioUnidad::Mediano) {
                            factorDanio = matrizEspecial[0][1];
                            }
                        else if ((*enemigoMaxVida2)->getTamanio() == TamanioUnidad::Grande) {
                            factorDanio = matrizEspecial[0][2];
                        }
                    }
                    else if(unidad->getTipoDanoTerrestre() == TipoDanoTerrestre::Explosivo) { // fila 1
                        if ((*enemigoMaxVida2)->getTamanio() == TamanioUnidad::Pequeno) {
                            factorDanio = matrizEspecial[1][0];
                        }
                        else if ((*enemigoMaxVida2)->getTamanio() == TamanioUnidad::Mediano) {
                            factorDanio = matrizEspecial[1][1];
                        }
                        else if ((*enemigoMaxVida2)->getTamanio() == TamanioUnidad::Grande) {
                        factorDanio = matrizEspecial[1][2];
                        }
                    }
                    else if(unidad->getTipoDanoTerrestre() == TipoDanoTerrestre::Contusivo) {  // fila 2

                        if ((*enemigoMaxVida2)->getTamanio() == TamanioUnidad::Pequeno) {
                            factorDanio = matrizEspecial[2][0];
                            }
                        else if ((*enemigoMaxVida2)->getTamanio() == TamanioUnidad::Mediano) {
                            factorDanio = matrizEspecial[2][1];
                            }
                        else if ((*enemigoMaxVida2)->getTamanio() == TamanioUnidad::Grande) {
                            factorDanio = matrizEspecial[2][2];
                        }
                    }
                    factorDanio = factorDanio * (1 - (*enemigoMaxVida2)->getBlindaje());
                    
                    danoReal = unidad->getDanoTerrestre() * factorDanio;
                }
                else  { // aereo
                    if(unidad->getTipoDanoTerrestre() == TipoDanoTerrestre::Normal) { // fila 0
                        if ((*enemigoMaxVida2)->getTamanio() == TamanioUnidad::Pequeno) {
                            factorDanio = matrizEspecial[0][0];
                            }
                        else if ((*enemigoMaxVida2)->getTamanio() == TamanioUnidad::Mediano) {
                            factorDanio = matrizEspecial[0][1];
                            }
                        else if ((*enemigoMaxVida2)->getTamanio() == TamanioUnidad::Grande) {
                            factorDanio = matrizEspecial[0][2];
                        }
                    }
                    else if(unidad->getTipoDanoTerrestre() == TipoDanoTerrestre::Explosivo) { // fila 1
                        if ((*enemigoMaxVida2)->getTamanio() == TamanioUnidad::Pequeno) {
                            factorDanio = matrizEspecial[1][0];
                        }
                        else if ((*enemigoMaxVida2)->getTamanio() == TamanioUnidad::Mediano) {
                            factorDanio = matrizEspecial[1][1];
                        }
                        else if ((*enemigoMaxVida2)->getTamanio() == TamanioUnidad::Grande) {
                        factorDanio = matrizEspecial[1][2];
                        }
                    }
                    else if(unidad->getTipoDanoTerrestre() == TipoDanoTerrestre::Contusivo) {  // fila 2

                        if ((*enemigoMaxVida2)->getTamanio() == TamanioUnidad::Pequeno) {
                            factorDanio = matrizEspecial[2][0];
                            }
                        else if ((*enemigoMaxVida2)->getTamanio() == TamanioUnidad::Mediano) {
                            factorDanio = matrizEspecial[2][1];
                            }
                        else if ((*enemigoMaxVida2)->getTamanio() == TamanioUnidad::Grande) {
                            factorDanio = matrizEspecial[2][2];
                        }
                    }
                    factorDanio = factorDanio * (1 - (*enemigoMaxVida2)->getBlindaje());
                    danoReal = unidad->getDanoAereo() * factorDanio;
                }
                // ver si la unidad tiene escudo
                if((*enemigoMaxVida2)->getRaza() == Raza::Protos){
                        // transformano el enemigo a protos
                        CProtos *enemigoProtos = dynamic_cast<CProtos*>((*enemigoMaxVida1));
                        // ver si tiene escudo, si tiene primero se le resta al escudo y luego a la vida
                        if((enemigoProtos)->getEscudo() > 0){
                            (enemigoProtos)->setEscudo((enemigoProtos)->getEscudo() - danoReal);
                            if((enemigoProtos)->getEscudo() < 0){
                                (enemigoProtos)->setVida((*enemigoMaxVida1)->getVida() + (enemigoProtos)->getEscudo());
                                (enemigoProtos)->setEscudo(0);
                                    }
                                }
                        else{  // si no tiene escudo, se le resta a la vida
                            (enemigoProtos)->setVida((*enemigoMaxVida1)->getVida() - danoReal);
                        }
                    }
                    else if((*enemigoMaxVida1)-> getRaza() == Raza::Zerg){
                        // lo del primer ataque y  la auto destruccion
                        /* Autodestruccion:Esta característica puede ser verdadera o falsa. Algunas unidades Zerg
                        se autodestruyen después de realizar un ataque y otras no. 
                        Las unidade zerg que se autodestruyen son: «Infested» y «Scrouge». Estas dos unidades
                        explotan al atacar a sus oponentes. Esto quiere decir que, al atacar, la unidad atacante 
                        muere inmediatamente después de hacerle daño al defensor */
                        /* Primer ataques : Las unidades Zerg recuperan 1 
                        punto de vida tras ser atacadas por primera vez, debido a que sus cuerpos se autogeneran. 
                        Sin embargo, esta autogeneración no se realiza si es que la unidad está viva*/
                        CZerg *enemigoZerg = dynamic_cast<CZerg*>((*enemigoMaxVida1));
                        if(enemigoZerg->getAutodestruccion() == true){
                            // la unidad atacante muere inmediatamente después de hacerle daño al defensor
                            // se le resta el dano a la vida del enemigo
                            enemigoZerg->setVida(enemigoZerg->getVida() - danoReal);
                            // la unidad atacante muere
                            unidad->setVida(0);
                        }
                        // primer ataque
                        if(enemigoZerg->getPrimerAtaque() == true){
                            // si es la primera vez que ataca, se le suma 1 a la vida
                            enemigoZerg->setVida(enemigoZerg->getVida() + 1);
                            // se le resta el dano a la vida del enemigo
                            enemigoZerg->setVida(enemigoZerg->getVida() - danoReal);
                        }
                        else{
                            // se le resta el dano a la vida del enemigo
                            enemigoZerg->setVida(enemigoZerg->getVida() - danoReal);
                        }
                    }
                    else { // Terran
                        (*enemigoMaxVida2)->setVida((*enemigoMaxVida2)->getVida() - danoReal);

                    }


                cout<<"La vida de "<<(*enemigoMaxVida2)->getNombre()<<" es: "<<(*enemigoMaxVida2)->getVida()<<endl;
                cout<< unidad->getNombre() << " ataca a " << (*enemigoMaxVida2)->getNombre() << " con " << danoReal << " de dano" << endl;
                cout<<endl;

                archivo<<"La vida de "<<(*enemigoMaxVida2)->getNombre()<<" es: "<<(*enemigoMaxVida2)->getVida()<<endl;
                archivo<< unidad->getNombre() << " ataca a " << (*enemigoMaxVida2)->getNombre() << " con " << danoReal << " de dano" << endl;

                archivo<<endl;
                // ver si el enemigo murio
                if ((*enemigoMaxVida2)->getVida() <= 0) {
                    cout << (*enemigoMaxVida2)->getNombre() << " ha muerto" << endl;
                    archivo << (*enemigoMaxVida2)->getNombre() << " ha muerto" << endl;
                }
            }
        }
        // Eliminar unidades muertas y se actualiza el enemigo con mayor vida
        HeoresSquad1.erase(remove_if(HeoresSquad1.begin(), HeoresSquad1.end(),
            [](CUnidad* u) { return u->getVida() <= 0; }), HeoresSquad1.end());
        HeoresSquad2.erase(remove_if(HeoresSquad2.begin(), HeoresSquad2.end(),
            [](CUnidad* u) { return u->getVida() <= 0; }), HeoresSquad2.end());
} 
cout<<endl;
turno++;
}

archivo<<endl;

// Imprimir resultado de la batalla
if (HeoresSquad1.empty()) {
    cout <<"Gana "<<jugador2 <<"con su  squad 2!" << endl;
    archivo <<"Gana "<<jugador2 <<"con su  squad 2!" << endl;
}
else {
    cout << "Gana "<<jugador1 <<"con su squad 1!" << endl;
    archivo << "Gana "<<jugador1<<" con su squad 1!" << endl;
}
archivo.close();

// Liberar memoria de las instancias creadas
for (auto& unidad : HeoresSquad1) {
    delete unidad;
}
for (auto& unidad : HeoresSquad2) {
    delete unidad;
}
for(int i = 0; i < 3; i++){
    delete[] matrizEspecial[i];
}
delete[] matrizEspecial;

return 0;
    
}