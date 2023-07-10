# STEM

By far my hardest engineering project, requiring two devices to communicate at high speed, with error rejection, controlling with accuracy stepper motors and dealing with bad tolerances on plastic parts 

Look at the demo here: https://youtube.com/shorts/tS_cE6SSZQE

The general layout is the following: 
1) A webcam on top that records the black plane 
2) A python function that identifies the brightest pixel, anchors to the ball with sub pixel precision and calculates the trajectory
3) A python function that sends the data to arduino (every 30ms)
4) Arduino code that recieves the data (every 8ms) and updates the behaviour
5) Arduino code that moves the motors by sending current through different wires (every 2ms)

![image](https://github.com/LucaM185/STEM/assets/66442521/fd708ec7-fa58-4be6-933b-71ca819a12b4)
