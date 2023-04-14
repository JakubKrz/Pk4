#include <iostream>
#include <regex>

using namespace std;

int main()
{	//Zadanie 1
	string tekst = "Sed ac lacus vel mi finibus tincidunt sit regex amet eu elit.MaurisRegex vestibulum nisi eget quam solliregexcitudin consectetur.Fusce sed pharetra urna.Aenean ut felis lorem.Nunc vel augue quis purus elementum euismod vitae id nulla.Ut velit tortor, pulvinar vitae libero sit amet, scelerisque elementum REGEX nisi.Aenean at lobortis ipsum, id tristique nunc.Cras eget vulputate massa, sit amet aliquet libero.Mauris non est at ante malesuada regex volutpat.In hac habitasse Regex platea dictumst.";
	regex spacja(" ");
	cout << "Tekst bez spacji: " << regex_replace(tekst, spacja, "") << "\n\n";

	regex szukane("REGEX|[rR]egex");
	int licznik = 0;
	smatch pom;
	while (regex_search(tekst, pom, szukane))
	{
		tekst = pom.suffix();
		licznik++;
	}
	cout <<"liczba znalezionych slow regex = "<< licznik << "\n\n";
	//Zadanie 2
	const string emaile[] = { "helena78@gmail.com", "drg narf@encu.com", "stoutbds@o2.com", "regex@regex.re", "space@ space.sp", "zadlugiadresemail@nie.com", "astron@o.o"};
	regex mail("([\\w&#]{1,10}@[A-Za-z0-9]{2,10}.[A-Za-z]{2,3})");
	vector<string> niepoprawne;
	cout << "Poprawne adresy email:\n";
	for (const auto& pom : emaile)
	{
		if (regex_match(pom, mail))
		{
			cout << pom << "\n";
		}
		else
		{
			niepoprawne.push_back(pom);
		}
	}
	cout << "\nNiepoprawne adresy email:\n";
	for (auto &it : niepoprawne)
	{
		cout << it << endl;
	}
	return 0;
}