/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** Author: Matthieu Holtz
** Year: 2014
** -------------------------------------------------------------------------*/
#include "NTPClock.h"
#include <Arduino.h>

#define TWENTYFOURHRMILLIS 86400000

NTPClock::NTPClock(NTPClient * ntpClient) :_ntpClient(ntpClient),
										_localTimeReference(0),
										_ntpTimeReference(0),
										_timezoneOffset(0),
										_synchronizationTimestamp(0)
{
	this->synchronize();
}

NTPClock	::	NTPClock	(NTPClient * ntpClient, unsigned int timezoneOffset) :
																				_ntpClient(ntpClient),
																				_localTimeReference(0),
																				_ntpTimeReference(0),
																				_timezoneOffset(timezoneOffset),
																				_synchronizationTimestamp(0)
{
	this->synchronize();
}

NTPClock	::	~NTPClock	()
{
}

unsigned long  NTPClock		::	getPosixTimestamp	()
{

	unsigned long timestamp = _ntpTimeReference + systemTimeSec() - _localTimeReference;

	if (_synchronizationTimestamp + TWENTYFOURHRMILLIS <= timestamp || _synchronizationTimestamp <= 0)
		synchronize();
	
	return timestamp;
}

void			NTPClock	::	synchronize		()
{
	_ntpTimeReference = _ntpClient->requestTime();
	_localTimeReference = systemTimeSec();
	_synchronizationTimestamp = _ntpTimeReference - _localTimeReference;;
}

unsigned long	NTPClock	::	systemTimeSec	()
{
	return (unsigned long)((double)millis() / 1000.0);
}

unsigned int	NTPClock	::	getHours		()
{
	return getHours_UTC() + _timezoneOffset;
}

unsigned int	NTPClock	::	getMinutes		()
{
	return ((getPosixTimestamp() % 3600) / 60); 
}

unsigned int	NTPClock	::	getSeconds		()
{
	return (getPosixTimestamp() % 60);
}

unsigned int	NTPClock	::	getHours_UTC()
{
	return (getPosixTimestamp() % 86400L) / 3600;
}

void			NTPClock	::	setTimezoneOffset(unsigned int offset)
{
	_timezoneOffset = offset;
}

unsigned int	NTPClock	::	getTimezoneOffset()
{
	return _timezoneOffset;
}