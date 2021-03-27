#include "PID.h"
#include <vector>
#include <iostream>

/**
 * TODO: Complete the PID class. You may add any additional desired functions.
 */

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp_, double Ki_, double Kd_) {
  /**
   * ~TODO~: Initialize PID coefficients (and errors, if needed)
   */
  Kp = Kp_;
  Ki = Ki_;
  Kd = Kd_;

  p_error = 0, i_error = 0, d_error = 0;
  dp = 1, di = 0, dd = 1;
  best_err = 9999;
  counter = 0;
  avg_interval = 200;
  avg_cte = 0;
  reverse_check = false;

}

void PID::UpdateError(double cte) {
  /**
   * ~TODO~: Update PID errors based on cte.
   */
  p_error = cte;
  i_error += cte;
  d_error = cte - d_error;

}

double PID::TotalError() {
  /**
   * ~TODO~: Calculate and return the total error
   */
  /**
   * TODO: create time variable for timestep in updating the differential error
   */ 
  return -Kp*p_error -Ki*i_error - Kd*d_error;  // TODO: Add your total error calc here!
}

void PID::Twiddle(double cte){
  // std::vector<double> k = {Kp, Kd, Ki}; 
  // std::vector<double> dk = {dp, dd, di}; 
  // for(int i = 0; i < k.size(); i++){
  //   k[i] += dk[i];
  // }
  // reverse_check ? Kp -= 2*dp : Kp += dp;
  if(counter < avg_interval){
    counter++;
    avg_cte += cte;
    std::cout << "Counter: " << counter << std::endl;
  }
  else{
    std::cout << "Current Kp: " << Kp << std::endl;
    avg_cte /= counter;
    if(dp > 0.2){
      double sq_err = avg_cte*avg_cte;
      // double sq_err = cte*cte;
      
      if(sq_err < best_err){
        best_err = sq_err;
        dp *= 1.1;
      }
      else{
        // If error is worse
        if(!reverse_check){
          // First perform the reverse check
          reverse_check = true;
        }
        else{
          // Otherwise try a smaller d_gain
          // First, reset the Kp value
          Kp += dp;
          // Reduce gain multiplier
          dp *= 0.9;
          reverse_check = false;
        }
      }

      if(!reverse_check){
        Kp += dp;
        std::cout << "Adding dp: " << dp << std::endl;
      }
      else{
        Kp -= 2*dp;
        std::cout << "Subtracting dp: " << dp << std::endl;
      }
    }
    counter = 0;
    avg_cte = 0;
  }
  // wait for robot to move
}

// void PID::UpdateTwiddle(double cte){
//   double sq_err = cte*cte;
  
//   if(sq_err < best_err){
//     best_err = sq_err;
//     dp *= 1.1;
//   }
//   else{
//     // If error is worse
//     if(!reverse_check){
//       // First perform the reverse check
//       reverse_check = true;
//     }
//     else{
//       // Otherwise try a smaller d_gain
//       // First, reset the Kp value
//       Kp += dp;
//       // Reduce gain multiplier
//       dp *= 0.9;
//     }
//   }
// }