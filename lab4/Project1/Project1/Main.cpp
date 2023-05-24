#include <iostream>
#include <vector>
#include <ranges>
#include <string>
#include <random>

using namespace std;
int main()
{
	//Zadanie 1
	cout << "Zadanie 1\n\n";
	vector<int> vec = { 12,2,3,4,5,14,2,7,8,9,1,12,6 };
	for (int i : vec) cout << i <<" ";
	cout << endl;
	auto output1 = vec
		| views::reverse
		| views::filter([](int pom) {return pom > 4; })
		| views::take(4);
	cout << "ostanie 4 liczby wieksze od cztery - ";
	for (int i : output1)
	{
		cout << i << " ";
	}
	
	//Zadanie 2
	cout << "\n\nZadanie 2\n\n";
	random_device random;
	mt19937 gen(random());
	uniform_int_distribution<> dist(21, 37);
	
	vector<int> vec2(10);
	ranges::generate(vec2, [&]() {return dist(gen); });
	for (auto x : vec2) cout << x<<" ";
	cout << endl<<"parzyste podzielone przez 2 - ";
	
	for (int i : views::transform(views::filter(vec2, [](int i) {return i % 2 == 0; }), [](int i) {return i / 2; }))
		cout<< i<<" ";
	cout << endl << "nieparzyste podniesione do kwadratu - ";

	for (int i : views::transform(views::filter(vec2, [](int i) {return i % 2 != 0; }), [](int i) {return i*i; }))
		cout << i << " ";
	cout << endl;

	//Zadanie 3
	cout << "\nZadanie 3\n\n";
	struct Mieszkanie 
	{
		string nazwa;
		int metraz;
	};
	vector<Mieszkanie> mieszkania =
	{
		{"duzy dom",185}, {"blizniak",120},  {"mieszkanie w bloku", 75},
		{"maly dom", 110}, {"male mieszkanie",15}, {"mieszkanie w bloku", 55},
		{"blok",65}, {"willa",295}
	};
	vector<Mieszkanie> output3;
	ranges::copy_if(mieszkania, back_inserter(output3), [](Mieszkanie pom) { return pom.metraz > 60; });
	ranges::sort(output3, ranges::less{}, & Mieszkanie::nazwa);

	cout << "Posortowane mieszkania z metrazem wiekszym niz 60: \n";
	for (const Mieszkanie &i : output3)
	{
		cout << i.nazwa << " " << i.metraz << endl;
	}
}