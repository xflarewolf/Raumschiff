// classes example
#include <iostream>
#include <string>
using namespace std;


class Raumschiff {
    private:
      string name;
      int x, y;
    public:
      Raumschiff(string);  // Konstruktor
      Raumschiff(int, int);  // Konstruktor
      void taufe(string);
      void setze_position(int, int);
      void ausgabe();
};


Raumschiff::Raumschiff(string n) {
    taufe(n);
    x = 0;
    y = 0;
}

Raumschiff::Raumschiff(int ax, int ay) {
    taufe("unbekanntes Flugobjekt");
    x = ax;
    y = ay;
}

void Raumschiff::taufe(string n) {
    name = n;
}

void Raumschiff::setze_position(int ax, int ay) {
    x = ax;
    y = ay;
}

void Raumschiff::ausgabe() {
   cout << "Das Schiff " << name;
   cout << " befindet sich bei (" << x << "/" << y << ")" << endl;
}

int main() {
  Raumschiff schiff1("Voyager");
  Raumschiff schiff2(33, 44);

  Raumschiff *schiffe[10];
  schiffe[0] = &schiff1;
  schiffe[1] = &schiff2;

  for (int i=0; i<2; i++) {
      schiffe[i]->ausgabe();
  }

  return 0;
}

