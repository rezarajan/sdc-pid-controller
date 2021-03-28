#ifndef PID_H
#define PID_H
#include <vector>

class PID {
 public:
  /**
   * Constructor
   */
  PID();

  /**
   * Destructor.
   */
  virtual ~PID();

  /**
   * Initialize PID.
   * @param (Kp_, Ki_, Kd_) The initial PID coefficients
   */
  void Init(double Kp_, double Ki_, double Kd_);

  /**
   * Update the PID error variables given cross track error.
   * @param cte The current cross track error
   */
  void UpdateError(double cte);

  /**
   * Calculate the total PID error.
   * @output The total PID error
   */
  double TotalError();

  /**
   * Optimize PID gains using the Twiddle algorithm
   * @param cte The current cross track error
   */
  void Twiddle(double cte);
  // void UpdateTwiddle(double cte);

 private:
  /**
   * PID Errors
   */
  double p_error;
  double i_error;
  double d_error;

  /**
   * PID Coefficients
   */ 
  double Kp;
  double Ki;
  double Kd;

  /**
   * Twiddle differentials
   */
  double dp;
  double di;
  double dd;
  double best_err;
  double avg_cte;
  /**
   * Twiddle Flags
   */
  int counter;
  int avg_interval;
  bool reverse_check;
  bool check_next;
  std::vector<bool> reverse_checks;
  enum class TwiddleParam {P,I,D};
  TwiddleParam param;
};

#endif  // PID_H