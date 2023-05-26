#include <iostream>
#include <thread>
#include <mutex>
#include <queue>

//zad1

std::mutex Mutex1;

void WyswietlId(std::atomic<unsigned long long int> *Id)
{
	Mutex1.lock();
	
	*Id = std::hash<std::thread::id>{}(std::this_thread::get_id());
	std::cout << "Id tego watku = " << *Id << std::endl;
	
	Mutex1.unlock();
}
void DodajId(std::atomic<unsigned long long int>* Id1, std::atomic<unsigned long long int>* Id2)
{
	Mutex1.lock();

	auto suma = *Id1 + *Id2;
	std::cout << "suma id wynosi " << suma << std::endl;

	Mutex1.unlock();
}

int main()
{
	//Zad1
	std::atomic<unsigned long long int> Id1 = 0, Id2 = 0;
	std::thread watek1(WyswietlId, &Id1);
	std::thread watek2(WyswietlId, &Id2);
	std::thread watek3(DodajId, &Id1, &Id2);
	watek1.join();
	watek2.join();
	watek3.join();

	return 0;
}