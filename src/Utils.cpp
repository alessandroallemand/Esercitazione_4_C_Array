#include "Utils.hpp"
#include "fstream"
#include "iostream"
#include "sstream"
#include "iomanip"

using namespace std;

// in questa funzione, grazie al passaggio dei parametri per riferimento
//riesco ad estrapolare le informazioni che mi serveno dal file
// corrispondente all'inputFilePath.
bool ImportVectors(const string& inputFilePath, 
				   size_t& n, 
				   double*& w, 
				   double*& r, 
				   double& S)
{
    //se il file non si apre la funzione restituisce false
	ifstream inputfile(inputFilePath);
	if(inputfile.fail())
		return false;

	// dichiaro le variabili per poter leggere le righe
	string riga;
	char c1;
	char c2;
	
	//Leggo la prima riga del file e salvo 1000 dentro ad S
	getline(inputfile, riga);
	stringstream str1(riga);
	str1 >> c1 >> c2 >> S;
	
	//Leggo la seconda riga del file e salvo 8 dentro ad n
	getline(inputfile, riga);
	stringstream str2(riga);
	str2 >> c1 >> c2 >> n;
	
	//Salto la terza riga 
	getline(inputfile, riga);

	// allochiamo memoria dinamica, e facciamo in modo che w ed
    //r puntino rispettivamente a quegli indirizzi di memoria heap
    // grezie all'operatore heap
	w = new double[n];
	r = new double[n];
	
    //leggendo le varie righe salvo all'interno dei vettori w e r
    //tutti i valori, che diventano rispettivamente l'(i+1)-esimo elemento
    //del rispettivo vettore 
	for(unsigned int i = 0; i < n; i++){
		getline(inputfile, riga);
		stringstream str3(riga);
		str3 >> w[i] >> c2 >> r[i];
	}
	
	return true;
}

// in questa funzione eseguo il prodotto scalare tra i 2 vettori 
// a cui puntano v e r
double DotProduct(const size_t& n, 
				  const double* const& w, 
				  const double* const& r)
{
	double prodotto = 0.0;
	for(unsigned int i = 0; i < n; i++)
		prodotto += w[i] * r[i];
    return prodotto;
}

// in questa funzione calcolo il valore finale del portafoglio
double ValuePortfolio(const size_t& n,
					  const double& S,
					  const double* const& w,
					  const double* const& r)
{
	double V = 0.0;
	for(unsigned int i = 0; i < n; i++)
		V += w[i] * (1 + r[i]);
	V = V * S;
	return V;
}

//in questa funzione stampiamo i risultati ricavati grazie 
// alle funzioni precedenti sul file result.txt 
bool ExportResult(const string& outputFilePath, 
				  const size_t& n, 
				  const double* const& w, 
				  const double* const& r, 
				  const double& S,
				  const double& V,
				  const double& prodotto)
{
    ofstream outputfile;
    outputfile.open(outputFilePath);

    //se il file non si apre viene restituito un messaggio di errore
    //(grazie a cerr)
    if (outputfile.fail())
    {
        cerr << "file non aperto" << endl;
        return false;
    }

    outputfile << "S = " <<  fixed << setprecision(2) << S << ", n = " << n << endl;
	
	outputfile << "w = [ ";
	for(unsigned int i = 0; i < n; i++)
		outputfile << w[i] << " ";
	outputfile << "]" << endl;
	
	outputfile << "r = [ ";
	for(unsigned int i = 0; i < n; i++)
		outputfile << r[i] << " ";
	outputfile << "]" << endl;

	outputfile << "Rate of return of the portfolio: " << setprecision(4) << fixed << prodotto << endl;
	outputfile << "V: " << fixed << setprecision(2) << V << endl;

    outputfile.close();
	
    return true;
}