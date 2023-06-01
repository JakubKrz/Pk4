#include <iostream>
#include <semaphore>
#include <thread>
#include <barrier>
#include <vector>

std::barrier bariera(3);

class Prostopadloscian
{
private: 
	float a, b, c;
public:
	Prostopadloscian(int a, int b, int c) : a(a), b(b), c(c) {};
	void Oblicz() 
	{
		std::cout << "Pole prostopadloscianu = " << (a * b + a * c + c * b) * 2 << "\n";
		bariera.arrive_and_wait();
		std::cout << "Objetosc prostopadloscianu = " << a*c*b << "\n";
	}
};
class Prostokat 
{
private:
	float a, b;
public:
	Prostokat(float a, float b) : a(a), b(b) {};
	void Oblicz()
	{
		std::cout << "Pole prostokata = " << a*b << "\n";
		bariera.arrive_and_drop();
	}
};

int main() {
	Prostopadloscian x(2, 4, 8);
	Prostopadloscian z(1, 2, 4);
	Prostokat y(5, 10);
	std::thread t1([&x]() {x.Oblicz(); });
	std::thread t3([&z]() {z.Oblicz(); });
	std::thread t2([&y]() {y.Oblicz(); });
	t1.join();
	t2.join();
	t3.join();
	std::cout << '\n';
}
