This is a test of a tensorflow implementation to control a humanoid robotic finger (just one finger of the hand) with tensorflow.
The inputs are a video stream of the finger, 8 force values (0-1023) which measure how much tension on a wire-cable is and 8 servo speed values.
The finger is controlled by 8 servos which are in wheel mode. Each servo is pulling on a wire-cable, e.g servo-1 is pulling up and servo-2 is pulling down. So both, and the other servos also
need to interact with each other.


Input:
-> 8 force values from 0-1023
-> 8 servo speed values negative and positive (forward/backward)
-> video stream


Output:
-> best would be regression output of 8 servo speed values
-> ?


<img src="media/rviz-keyboard-ai.jpg" width="80%" />
