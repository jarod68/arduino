#pragma once

#ifndef WEATHERINFERENCE_H
#define WEATHERINFERENCE_H

//#include <Arduino.h>

#include "Pronostic.h"
#include "Tendency.h"
#include "SlidingHistory.h"
#include "ATendencyStrategy.h"
#include "APronosticStrategy.h"

/**
* Abstract class to infer weather values (indoor temperature, indoor humidity, indoor pressures, outdoor temperature).
* It uses SlidingHistory to manage history of values and compute mean at defined time interval.
*/
template<typename T>
class WeatherInference
{

public:

	/**
	* Constructor using history size argument, and delays
	*/
	WeatherInference	(ATendencyStrategy<T>	* tendencyStrategy, 
						 APronosticStrategy<T>	* pronosticStrategy) :
						_tendencyStrategy	(tendencyStrategy),
						_pronosticStrategy	(pronosticStrategy)
			
	{}

	virtual		~WeatherInference	()
	{}

	/**
	* Sets the indoor temperature with the specified value, and recompute tendency
	*/
	virtual void	appendIndoorTemperature		(T indoorTemperature){
		
			_tendencyStrategy->appendIndoorTemperature(indoorTemperature);
			_pronosticStrategy->appendIndoorTemperature(indoorTemperature);
	}

	/**
	* Sets the indoor humidity with the specified value, and recompute tendency
	*/
	virtual void	appendIndoorHumidity		(T indoorHumidity){
		
			_tendencyStrategy->appendIndoorHumidity(indoorHumidity);
			_pronosticStrategy->appendIndoorHumidity(indoorHumidity);
	}

	/**
	* Sets the indoor pressure with the specified value, and recompute tendency
	*/
	virtual void	appendIndoorPressure		(T indoorPressure){
		
			_tendencyStrategy->appendIndoorPressure(indoorPressure);
			_pronosticStrategy->appendIndoorPressure(indoorPressure);
	}

	/**
	* Sets the outdoor temperature with the specified value, and recompute tendency
	*/
	virtual void	appendOutdoorTemperature	(T outdoorTemperature){
		
			_tendencyStrategy->appendOutdoorTemperature(outdoorTemperature);
			_pronosticStrategy->appendOutdoorTemperature(outdoorTemperature);
	}

	/**
	* Gets the indoor temperature tendency
	*/
	virtual		Tendency	getIndoorTemperatureTendency	(){
		
		return _tendencyStrategy->getIndoorTemperatureTendency();
	}

	/**
	* Gets the indoor humidity tendency
	*/
	virtual		Tendency	getIndoorHumidityTendency	(){
		
		return _tendencyStrategy->getIndoorHumidityTendency();
	}

	/**
	* Gets the indoor pressure tendency
	*/
	virtual		Tendency	getIndoorPressureTendency	(){
		
		return _tendencyStrategy->getIndoorPressureTendency();
	}

	/**
	* Gets the outdoor temperature tendency
	*/
	virtual		Tendency	getOutdoorTemperatureTendency(){
		
		return _tendencyStrategy->getOutdoorTemperatureTendency();
	}

	virtual		Pronostic	getPronostic				(){
		return _pronosticStrategy->getPronostic();
	}


	private:
		ATendencyStrategy<T>	*	_tendencyStrategy;
		APronosticStrategy<T>	*	_pronosticStrategy;
};

#endif