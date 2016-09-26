# pub-server
PMD Data generator using DDS publish to make data available to subscribers

This blob of horrible hacked code implements a data generator
to publish a single DDS Topic of simulated data containing three data
elements:

Function	Name
Heartrate	ecgValue
ABP			abpValue
Pleth		plethValue

It is implemented using the Qt framework for no good reason other than 
that it was there ;)

The single executable is called pub-server. It takes no parameters but
requires an X-server be available on the target.
