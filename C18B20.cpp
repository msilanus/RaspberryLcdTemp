#include "C18B20.h"

using namespace std;

C18B20::C18B20()
{
    struct dirent *entry;
		sensor = "/sys/bus/w1/devices/";
    DIR *dir = opendir(sensor.c_str());
    if (dir == NULL) {
        cout << "bus w1 pas disponible" << endl;
    }

    while ((entry = readdir(dir)) != NULL) {
        if(entry->d_name[0]=='2' && entry->d_name[1]=='8') break;
    }

    closedir(dir);
    
	  string sensorName(entry->d_name);
		sensor += sensorName + "/w1_slave";
		//cout << "C18B20::C18B20 : " << sensor << endl;
	
}

float C18B20::getTemperature()
{
	string line;
	string temp="";
	float temperature;	

	ifstream file(sensor.c_str());
  if (file.is_open())
  {
	
    while ( getline (file,line) )
    {
			temp+=line;
    }
		file.close();
		int pos = temp.find("t=");
		if(pos>0) 
		{
			temp=temp.substr(pos+2);
			temperature = stof(temp)/1000;
			return temperature;
		}
		else return -1;
	}
	else return -1;

}

string C18B20::getSensorPath()
{
	return sensor;
}
