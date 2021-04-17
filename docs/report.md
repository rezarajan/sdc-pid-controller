# **PID Controller** 

## Writeup

### The following document outlines the process of creating and tuning a PID controller which helps a car around a cyclic track in a simulator.

---

## Highway Driving Project

The goals / steps of this project are the following:
* Create a PID controller which corrects for the offset of the vehicle on a simulated track
* Tune the P, I and D parameters of the PID controller to ensure desirable behaviour
* Successfully drive the car for at least one (1) lap around the track
* Ensure that no tire leaves the drivable portion of the track surface
* Summarize the results with a written report


[//]: # (Image References)

[image1]: ./images/p_only.gif "P Only Control"
[image2]: ./images/d_only.gif "D Only Control"
[image3]: ./images/i_only.gif "I Only Control"
[image4]: ./images/pd_only.gif "PD Only Control"
[image5]: ./images/pid_only_untuned.gif "PID Only Control"

## Rubric Points
### Here I will consider the [rubric points](https://review.udacity.com/#!/rubrics/1972/view) and describe how I addressed each point in my implementation.  

---
## Implementation

The following is a link to the [project code](https://github.com/rezarajan/sdc-pid-controller). Furthermore, a video showcasing the final PID controller implementation in the test track is available [here](https://) #TODO: Include final video YouTube link.

---

## Reflection

#### *1. Describe the effect each of the P, I, D components had in your implementation.*

### *P Control*

![image1]

### *D Control*

![image2]

### *I Control*

![image3]

#### *2. Describe how the final hyperparameters were chosen.*

#TODO
| Parameter | Value |
|-----------|-------|
|P          |-0.0975|
|I          |+0.0000|
|D          |-2.3050|

#### *3. The vehicle must successfully drive a lap around the track.*

The vehicle is able to complete at least one lap around the track, staying on only the drivable surfaces. It does not pop up onto ledges or roll over any surfaces that would otherwise be considered unsafe. A video demonstrating the simulation for two consecutive laps is available [here](#https://#TODO).


---

## Recommendations

* #TODO

## Conclusions

A PID controller has been created which keeps a vehicle on track in a simulation, for at least one lap. The controller's parameters have been optimized using the Twiddle algorithm, for which the parameters have been outlined [above](#2-describe-how-the-final-hyperparameters-were-chosen). Based on these results, though the controller maintains all proportional (P), integral (I) and derivative (D) terms in code, the resulting controller is a PD controller due to a zero-value for the integral term. This indicates that the integral aspect does not play a significant role in improving the controller's performance. Recommendations are also provided for further potential improvement of the controller.