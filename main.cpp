#include <iostream>
#include <iomanip>
#include <fstream>
#include <ctime>
#include <string>
#include <thread>
#include <condition_variable>
#include <chrono>
#include <mutex>
#include <time.h>
#include "C18B20.h"
#include "rgb_lcd.h"

using namespace std;

mutex m_mutex;
condition_variable m_condVar;
bool done;

int temperature;


int addLog(string logFile, string logString)
{
	ofstream flog(logFile, ios::app);
	if(flog)
        {		
		flog << logString ;
		flog.close();
        }
}

bool isDone()
{
	return done;
}



void thMesure()
{  	
	C18B20 *mySensor = new C18B20();
	
	while(1)
	{
		temperature =  mySensor->getTemperature();
	
		// Make This Thread sleep for 0.5 Second
	   	this_thread::sleep_for(chrono::milliseconds(1000));
	
	   	// Lock The Data structure
	   	lock_guard<mutex> guard(m_mutex);
	   	// Set the flag to true
	   	done = true;
		// Notify the condition variable
		m_condVar.notify_one();
	}
}// fin du thread thMesure


void thAffiche()
{
	time_t now;
	tm *nowinfo; 	

	string log;	
	rgb_lcd *myLcd;
	myLcd = new rgb_lcd();
    	myLcd->begin(16,2);
    	myLcd->setRGB(0,0,255);
	myLcd->setCursor(5, 0);
    	myLcd->write("Mesure");
	myLcd->setCursor(2, 1); 
    	myLcd->write("de distance");
	cout << "wait please ..." << endl;
	sleep(3);
	while(1)
	{
		unique_lock<mutex> mlock(m_mutex);
    		// Start waiting for the Condition Variable to get signaled
    		// Wait() will internally release the lock and make the thread to block
    		// As soon as condition variable get signaled, resume the thread and
    		// again acquire the lock. Then check if condition is met or not
    		// If condition is met then continue else again go in wait.
    		m_condVar.wait(mlock, bind(isDone));

		// Write info on LCD display
		if(temperature<17) myLcd->setColor(WHITE);
		else if(temperature<20) myLcd->setRGB(255,127,0);
		else myLcd->setColor(RED);

		myLcd->clear();		
		myLcd->setCursor(5, 0);
    		myLcd->write(to_string(temperature) + " C");
		
		// Prepare to log and display to screen or push on websocket
		now = time(0);
		nowinfo = localtime(&now);
		
		if(nowinfo->tm_mday<10) log="0" + to_string(nowinfo->tm_mday) + "/";
		else log += to_string(nowinfo->tm_mday) +"/";
		if(nowinfo->tm_mon<9) log += "0" + to_string(nowinfo->tm_mon + 1) + "/";
		else log += to_string(nowinfo->tm_mon + 1) + "/";
		log += to_string(nowinfo->tm_year + 1900) + " - ";
		if(nowinfo->tm_hour<10) log += "0" + to_string(nowinfo->tm_hour) + ":";
		else log += to_string(nowinfo->tm_hour) + ":";
		if(nowinfo->tm_min<10) log += "0" +to_string(nowinfo->tm_min) + ":";
		else log += to_string(nowinfo->tm_min) + ":";
		if(nowinfo->tm_sec<10) log += "0" + to_string(nowinfo->tm_sec);
		else log += to_string(nowinfo->tm_sec); 		
		log += "   |   ";
		log += to_string(temperature) + " °C\n";		
		cout << log;
		
		// Job is done, log it and ready for new measure
		addLog("/var/www/html/distance.log", log);
		log.clear();
		done = false;		
	}
}// fin du thread thAffiche

int main()
{	
	//Desactiver la bufferisation
	setbuf(stdout, NULL);
	
	thread th1 (thMesure);
	thread th2 (thAffiche);
	
	th1.join();
	th2.join();
	
}
