/*lopez */
#include <iostream>
#include <list>
#include <vector>
#include <time.h>
using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */



/*int in[]={1,2,3,0,4,5,6};
int solucion[36][7]={{4,5,6,0,1,2,3},{4,6,5,0,1,2,3},{5,4,6,0,1,2,3},{5,6,4,0,1,2,3},{6,5,4,0,1,2,3},{6,4,5,0,1,2,3},
					   {4,5,6,0,1,3,2},{4,6,5,0,1,3,2},{5,4,6,0,1,3,2},{5,6,4,0,1,3,2},{6,5,4,0,1,3,2},{6,4,5,0,1,3,2},
					   {4,5,6,0,3,2,1},{4,6,5,0,3,2,1},{5,4,6,0,3,2,1},{5,6,4,0,3,2,1},{6,5,4,0,3,2,1},{6,4,5,0,3,2,1},
					   {4,5,6,0,3,1,2},{4,6,5,0,3,1,2},{5,4,6,0,3,1,2},{5,6,4,0,3,1,2},{6,5,4,0,3,1,2},{6,4,5,0,3,1,2},//conjunto de soluciones posibles
					   {4,5,6,0,2,1,3},{4,6,5,0,2,1,3},{5,4,6,0,2,1,3},{5,6,4,0,2,1,3},{6,5,4,0,2,1,3},{6,4,5,0,2,1,3},
					   {4,5,6,0,2,3,1},{4,6,5,0,2,3,1},{5,4,6,0,2,3,1},{5,6,4,0,2,3,1},{6,5,4,0,2,3,1},{6,4,5,0,2,3,1}};
*/					   

//std::vector<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );
//vector<int> inicio(in,in+sizeof(in)/sizeof(int));
clock_t ini,fin;
list <vector <int> > todos;
list <list <vector <int> > > todos2;
vector <int> inicio2;
vector <int> solucion2;
int numRanas;
int mitadRanas;

void ImprimirEstado(vector <int> estado){
	for(int i=0;i<estado.size();i++){
		cout<<estado[i];
	}
	cout<<""<<endl;
}

void GenerarInicio(int ranas){
//	cout<<"entra generar " ;
	int mitad=ranas/2;
	mitadRanas=mitad;
	int contador=mitad+1;
	int c=1;
	for(int i=0;i<=ranas;i++){
		if(i<mitad){
			inicio2.push_back(i+1);
			solucion2.push_back(contador);
			contador++;
			//inicio2[i]=i+1;
		}else if(i==mitad){
			inicio2.push_back(0);
			solucion2.push_back(0);
			//inicio2[i]=0;
		}else if(i>mitad){
			inicio2.push_back(i);
			solucion2.push_back(c);
			c++;
			//inicio2[i]=i;
		}
	}
	cout<<"estado inicial : ";
	ImprimirEstado(inicio2);
	cout<<endl;
	cout<<"solucion esperado : ";
	ImprimirEstado(solucion2);
	cout<<endl;
	
}

void ImprimirLista(list <vector <int> > lista){
	while(!lista.empty()){
		vector<int> v= lista.front();
		ImprimirEstado(v);
		lista.pop_front();
	}
}

bool puedeMoverse(vector <int> estado,int pos1,int salto){
	if(estado[pos1+salto]==0){
		return true;
	}else{
		return false;
	}
}

vector<int> HacerMovimiento(vector<int> estado,int pos1,int pos2){
	int aux=estado[pos1];
	estado[pos1]=estado[pos2];
	estado[pos2]=aux;
	return estado;
}

/*
bool SolucionVerifica(vector <int> estado){
	//bool est= false;
	int contador=0;
	for(int i=0;i<36;i++){
		for(int j=0;j<7;j++){
			//cout<<solucion[i][j];
			if(estado[j]==solucion[i][j]){
				contador++;
			}
		}
		if(contador==7){
			return true;
		}else{
			contador=0;
		}
	}
	return false;
}*/
bool SolucionVerifica2(vector<int> estado){
	int contador=0;
	for(int i=0;i<estado.size();i++){
		if(estado[i]==solucion2[i]){
			contador++;
		}
	}
	if(contador==estado.size()){
		return true;
	}else{
		return false;
	}
	
}
//metodo principal
void Anchura(vector<int> inicio){//recibe un vector de inicio
	list<vector <int> > sublista;
	sublista.push_back(inicio);
	 todos2.push_back(sublista);
	//todos.push_front(inicio);
	
	while(!todos2.empty()){
		list<vector <int> > auxiliar2=todos2.front();
		vector<int> auxiliar=auxiliar2.back(); 
		ImprimirEstado(auxiliar);
		if(SolucionVerifica2(auxiliar)){
			
			fin=clock();
			float tiempo= (float)fin-(float)ini;
			cout<<"solucion encontrado : "<<endl;
			ImprimirLista(auxiliar2);
			cout<<"tiempo de ejecucion : "<<tiempo<<" milisegundos "<<endl;
			//ImprimirEstado(auxiliar);
			todos2.clear();
		}else{
		for(int i=0;i<auxiliar.size();i++){
			//mover hacia la derecha 1 campo
			
			if(auxiliar[i]<=mitadRanas){
				if((i+1)<=numRanas && puedeMoverse(auxiliar,i,1) ){
					vector<int> au2=HacerMovimiento(auxiliar,i,i+1);
					list<vector <int> > aux1=auxiliar2;
					aux1.push_back(au2);
					todos2.push_back(aux1);
					//todos.push_back(au2);
					//ImprimirEstado(au2);
				}
				//mover hacia la derecha 2
				if((i+2)<=numRanas && puedeMoverse(auxiliar,i,2)  ){
					vector<int> au2=HacerMovimiento(auxiliar,i,i+2);
					list <vector <int> > aux2=auxiliar2;
					aux2.push_back(au2);
					todos2.push_back(aux2);
					//ImprimirEstado(au2);
				}				
			}
			
			if(auxiliar[i]>mitadRanas){
				//moder hacia la izqquierda 1 campo
				if((i !=0 ) && puedeMoverse(auxiliar,i,-1) ){
					vector<int> au2=HacerMovimiento(auxiliar,i,i-1);
					list<vector <int> > aux1=auxiliar2;
					aux1.push_back(au2);
					
					todos2.push_back(aux1);
					
					//todos.push_back(au2);
					//ImprimirEstado(au2);
				}
				//mover hacia la izquierda 2 campos
				if(i>= 2 && puedeMoverse(auxiliar,i,-2) ){
					vector<int> au2=HacerMovimiento(auxiliar,i,i-2);
					
					list<vector <int> >aux1 = auxiliar2;
					aux1.push_back(au2);
					todos2.push_back(aux1);
					//todos.push_back(au2);
					//ImprimirEstado(au2);
				}
			}

		}
			todos2.pop_front();			
		}
	
		
	}
	
}

int main(int argc, char** argv) {
	int ranas;
	cout<<"ingrese cantidad de ranas en total : "<<endl;
	cin>>ranas;
	numRanas=ranas;
	GenerarInicio(ranas);
	//cout<<"valor inicio . "<<inicio2.size();
	ini=clock();
	Anchura(inicio2);
	return 0;
}
