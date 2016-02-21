# librarymonitor
Interact with Arduino to monitor how many people went in and out of an library. 

For the arduino:

Assume the domain name is example.com, the arduino sends data by sending simply sending a GET request to example.com/sensor.

Send example.com/sensor?data=in if the arduino detects people walking into the library. 
Send example.com/sensor?data=out if the arduino detects people walking out of the library. 

Visit example.com/sensor/reset for resetting the database.
