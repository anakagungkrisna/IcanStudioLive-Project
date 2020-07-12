# IcanStudioLive-Project
All code that are associated with IcanStudio Live Project

the code for servo-pan-tilt uses 4 inputs, which produced 5 variables. Those inputs are from 2 buttons, 1 potentiometer, and 1 joystick (Which gives x and y variables). Those 5 variables are used to control the 3 motor of the pan-tilt camera. 

The code for servo-pan-tilt-with-NRF is the modification of the servo-pan-tilt code with the wireless connection of the NRF24L01 module. It receives the information from the wireless controller(transmitter) and assign it in an array of 4. Then it process those data to move the pan-tilt camera as in the servo-pan-tilt code

The code for Transmitter-with-control is the wireless controller(transmitter) code. It uses the same input as in the code for servo-pan-tilt and assign them in an array of 4 and send them via the NRF24L01 module to be received with the pan-tilt camera(receiver) 
