# t-019-bctott
Binary Clock Thats Over The Top


## v01.00 

### features  
* binary led clock (hr/min/sec)
  * 12/24hr time selection
* temperature
* humidity
* proximity turn-on/off
* hourly buzzer
* up-time tracking (how long clock has been running before)
* 

### hw
* arduino uno
* LEDs
  * 1 yellow: 12/24 indication
  * 5 blue: 24 possible hours (2^5=32)
  * 6 red : 60 min (2^6=64)
  * 6 green: 60 sec
* 4 digit seven-segment display 
  * temperature/humidity
  * 
* shift registers 
* proximity sensor
  * turn on leds/display when in room, otherwise turn off to conserve battery 
* buzzer
* switches
  * 1 power on/off
  * set time
    * 1 sel
    * 1 +
    * 1 - 


# further enhancements (beyond v01.00)
* sync to timezone 
* send data log of up-time/temp/humid back to host computer
* python/c app to set time via bluetooth


