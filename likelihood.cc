#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>


double poisson(double mu, int k) {
  double P=(pow(mu, k)*exp(-mu))/(tgamma(k+1));
  return P;
}

double prob(std::vector<int> daten, double mu)
{
  double x=1;
  for(int k : daten)
  {
    x*=pow(mu, k)*exp(-mu)/(tgamma(k+1));
  }
  return x;
}

int main() {
    using namespace std;

    std::vector<int> daten;
    ifstream fin("datensumme.txt");
    int n_i;
    for(int i = 0 ; i < 234 ; ++i) {
        fin >> n_i;
        daten.push_back(n_i);
    }
    fin.close();

    std:cout << prob(daten, 3.11538) << std::endl;

    ofstream fout("likelihood.txt");
    for(double i=0; i<6; i+=0.1)
    {
      fout << prob(daten, i) << std::endl;
    }
    fout.close();

    ofstream gout("nll.txt");
    for(double i=0; i<6; i+=0.1)
    {
      gout << i << "  " << -2*log(prob(daten, i)) << std::endl; 
    }
    gout.close();

    ofstream hout("deltanll.txt");
    for(double i=0; i<6; i+=0.1)
    {
      hout << i << "  " << -2*log(prob(daten, i)) + 2*log(prob(daten, 3.11538)) << std::endl;
    }

    double pq;
    for(int k : daten)
    {
      pq = poisson(k, 3.11538)/poisson(k,k);
    }
    std::cout << pq << std::endl;
}