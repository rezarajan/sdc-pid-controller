# **PID Controller** 

## Writeup

### The following document outlines the process of creating and tuning a PID controller which helps a car navigate around a track in a simulator.

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

The following is a link to the [project code](https://github.com/rezarajan/sdc-pid-controller). Furthermore, a video showcasing the final PID controller implementation in the test track is available [here](https://youtu.be/AJYaWOHqug8).

---

## Reflection

#### *1. Describe the effect each of the P, I, D components had in your implementation.*

The effects of each of the proportional (P), derivative (D) and integral (I) components of the controller are described below. Note that in this project's implementation, only a steering controller is implemented, while the throttle is maintained constant.

### *P Control*

The p-term of the controller applies a steering correction which is proportional to the tracking error of the car from the center of the road. However, since a vehicle cannot instantaneously change its steering value to any given value, i.e. steering corrections must be incremental, a proportional correction may result in the vehicle overshooting the center of the road, and thus oscillating.

Using a p-value found by trial-and-error, the effects of only proportional control are shown below:

![image1]

The above animation shows how the proportional controller, with an appropriately selected gain, is able to control the car fairly well for some time on the road, before becoming unstable and oscillating. This is most notable at the point where the road starts to curve. This problem persists in further testing, and is a result of the difficulty of correcting for a continuously changing target center.

### *D Control*

The d-term of the controller acts to reduce oscillations induced by overshooting in the p-term. In other words, it should act to counter the p-term, but not so much as to overpower it. The below illustration shows the effects of only d-control, the value of which is again found by trial-and-error.

![image2]

Clearly the d-controller becomes unstable much faster than the p-control. This is expected since this component is meant to work in conjunction with the p-controller. It does, however, at least function around turns, unlike the p-controller. Therefore, it would be trivial to assume that some combination of both p and d controls would allow the car to at least navigate around the track to some extent.

### *I Control*

The i-term is meant as a correction to a controller which maintains a steady-state error. It is not expected to use the integral term in isolation. A demonstration of an i-controller is shown below: 

![image3]

Clearly, the i-controller does not do much to help the car navigate the track.

### *PID Control*

The [final controller](https://youtu.be/AJYaWOHqug8) includes function for the P, D and I terms. However, in the final controller only the P and D terms are assigned non-zero values, indicating that the car can successfully navigate solely on PD control, and that the i-term does not impact the vehicle's behaviour in any significant way.
#### *2. Describe how the final hyperparameters were chosen.*

Parameter-tuning is done using an online Twiddle algorithm, whereby the parameters are adjusted as the car drives around the track. This has proven to be a better solution than offline Twiddle, since the target is always moving. The inital parameters are selected from the [previous tests](#1-describe-the-effect-each-of-the-p-i-d-components-had-in-your-implementation), whereby each parameter is selected based on trial-and-error.

After a few trials of the online Twiddle algorithm, the following are the final controller parameters:

| Parameter | Value |
|-----------|-------|
|P          |-0.0975|
|I          |+0.0000|
|D          |-2.3050|

#### *3. The vehicle must successfully drive a lap around the track.*

The vehicle is able to complete at least one lap around the track, staying on only the drivable surfaces. It does not pop up onto ledges or roll over any surfaces that would otherwise be considered unsafe. A video demonstrating the simulation for two consecutive laps is available [here](#https://youtu.be/AJYaWOHqug8).


---

## Recommendations

* The current steering controller implementation still results in undesirable behaviour from the vehicle, such as steering oscillations and sharp turns. It is recommended that a controller also be created to manage throttle, such that the settling time for steering is reduced and turns are able to be taken more smoothly.
* After many laps the steering controller eventually becomes unstable and the car runs off-track. Further tuning may be necessary to address this scenario, or perhaps an implementation of a throttle controller may help.

## Conclusions

A PID steering controller has been created which keeps a vehicle on track in a simulation, for at least one lap. The controller's parameters have been optimized using the Twiddle algorithm, yielding the hyperparameters [above](#2-describe-how-the-final-hyperparameters-were-chosen). Based on these results, though the controller maintains all proportional (P), integral (I) and derivative (D) terms in code, the resulting controller is a PD controller due to a zero-value for the integral term. This indicates that the integral term does not play a significant role in improving the controller's performance. Recommendations are also provided for potential improvement of the controller.