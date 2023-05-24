#include <iostream>
#include <future>

int factorial(std::future<int> fut)
{
	int result = 1;
	int n = fut.get();
	for (; n > 1; --n)
	{
		result *= n;
	}
	return result;
}

int main()
{
	int n;
	std::promise<int> p;
	std::future<int> fut_res = std::async(std::launch::async, factorial, p.get_future());
	std::cout << "Podaj liczbe: ";
	std::cin >> n;
	p.set_value(n);
	int x = fut_res.get();
	std::cout << x;
	return 0;
}
