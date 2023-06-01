#include <iostream>
#include <semaphore>
#include <iostream>
#include <semaphore>
#include <thread>
#include <vector>

using namespace std::literals;
std::vector<std::string> data{};
std::counting_semaphore sem(0);

void PrepareData() {
	data.insert(data.end(), { "dane", "dane", "dane", "----" });
	std::cout << "Przygotowywanie danych." << '\n';
	sem.release();
}

void Result() {
	sem.acquire();
	std::cout << "Oczekiwanie na dane." << '\n';
	std::cout << "Rezultat:" << '\n';
	for (auto i : data) std::cout << i << " ";
	std::cout << '\n';
}

int main() {
	std::cout << '\n';
	std::thread t1(PrepareData);
	std::thread t2(Result);
	t1.join();
	t2.join();
	std::cout << '\n';
}