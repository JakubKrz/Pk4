#include <iostream>
import BasicPlanes;

using namespace std;


int main()
{
	Rectangle A{ {0,1},{5,5} };
	Rectangle B{ {-3,-7},{1,2} };
	Rectangle C{ {-10,-12},{-3,-8} };

	cout <<"Prostokat A - wysokosc = "<< Height(A)<<" ";
	cout << "szereokosc = " << Width(A) <<" ";
	cout <<"powierzchnia = "<< Area(A)<<endl;

	cout << "Prostokat B - wysokosc = " << Height(B) << " ";
	cout << "szereokosc = " << Width(B) << " ";
	cout << "powierzchnia = " << Area(B) << endl;

	cout << "Prostokat C - wysokosc = " << Height(C) << " ";
	cout << "szereokosc = " << Width(C) << " ";
	cout << "powierzchnia = " << Area(C) << endl;
	return 0;
}