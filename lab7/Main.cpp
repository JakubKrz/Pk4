#include <iostream>
#include <semaphore>
#include <thread>
#include <fstream>
#include <string>

std::binary_semaphore zapisane(0), odczytane(0);

void pisz()
{
	for (int i = 1; i < 4; ++i)
	{
		std::ofstream plik("Zadanie3.txt");
		plik << "zapis nr " << i;
		plik.close();
		zapisane.release();

		odczytane.acquire();
	}
}

void czytaj()
{
	for (int i = 0; i < 3; ++i)
	{
		zapisane.acquire();

		std::ifstream plik("Zadanie3.txt");
		char x;
		std::string data;
		while (std::getline(plik, data))
			std::cout << data;
		std::cout << "\n";
		plik.close();

		odczytane.release();
	}
}

int main() {
	
	std::thread t1(pisz);
	std::thread t2(czytaj);

	t1.join();
	t2.join();

}