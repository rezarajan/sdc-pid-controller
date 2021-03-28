#include "PID.h"
#include <vector>
#include <iostream>
#include <string>

using std::string;

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
  avg_interval = 500;
  avg_cte = 0;
  reverse_check = false;
  check_next = false;
  param = TwiddleParam::P;

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
  double K;
  double d;
  string print_statement = "";

  // Assign the correct K value to optimize
  switch(param){
    case(TwiddleParam::P):
      K = Kp;
      d = dp;
      print_statement = "Kp";
      break;
    case(TwiddleParam::I):
      K = Ki;
      d = di;
      print_statement = "Ki";
      break;
    case(TwiddleParam::D):
      K = Kd;
      d = dd;
      print_statement = "Kd";
      break;
    default:
      K = Kp;
      d = dp;
      break;
  }

  if(counter < avg_interval){
    counter++;
    avg_cte += cte;
    // std::cout << "Counter: " << counter << std::endl;
  }
  else{
    std::cout << "Current " << print_statement << ": " << K << std::endl;
    avg_cte /= counter;
    if(dp > 0.2){
      double sq_err = avg_cte*avg_cte;
      if(sq_err < best_err){
        best_err = sq_err;
        dp *= 1.1;
        check_next = true;
      }
      else{
        // If error is worse
        if(!reverse_check){
          // First perform the reverse check
          reverse_check = true;
        }
        else{
          // Otherwise try a smaller d_gain
          // First, reset the K value
          K += d;
          // Reduce gain multiplier
          d *= 0.9;
          reverse_check = false;
          check_next = true;
        }
      }

      if(!reverse_check){
        K += d;
        // std::cout << "Adding dp: " << dp << std::endl;
      }
      else{
        K -= 2*d;
        // std::cout << "Subtracting dp: " << dp << std::endl;
      }
    }
    
    // Reassign new K value to the correct parameter
    switch(param){
      case(TwiddleParam::P):
        Kp = K;
        dp = d;
        if(check_next){
          param = TwiddleParam::I;
        }
        break;
      case(TwiddleParam::I):
        Ki = K;
        di = d;
        if(check_next){
          param = TwiddleParam::D;
        }
        break;
      case(TwiddleParam::D):
        Kd = K;
        dd = d;
        if(check_next){
          param = TwiddleParam::P;
        }
        break;
      default:
        K = Kp;
        d = dp;
        break;
    }
    
    // Reset Counter and Average
    counter = 0;
    avg_cte = 0;
    check_next = false;

  }
  // wait for robot to move
}