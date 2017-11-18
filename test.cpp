#include "C18B20.h"

using namespace std;

int main()
{
	C18B20 *mySensor = new C18B20();
	cout << "Temp : " << mySensor->getTemperature() << " °C" << endl;
	cout << "capteur : " << mySensor->getSensorPath() << endl;
	delete mySensor;
}
