//   HEPLike: High Energy Physics Likelihoods
//
//   Module to construck likelihoods for gaussian distribution
//
//   author: Jihyun Bhom, Marcin Chrzaszcz
//   author: Tomas Gonzalo
//////////////////////////////////////////////////


#include <cmath>
#include <limits>
#include <fstream>
#include <iomanip>
#include <iostream>

#include "HL_Stats.h"
#include "HL_Constants.h"
#include "HL_Gaussian.h"

using namespace std;

void HL_Gaussian::Read()
{
  if(! initialized)
  {
    throw std::runtime_error("TRYING TO READ WITHOUT GIVING ANY FILE!");
    return;
  }

  read_standard();

  if(config["Observables"])
  {
    YAML::Node node  = config["Observables"];
    ObsName=node[0][0].as<std::string>();
    HL_Central=node[0][1].as<double>();
    HL_Sigma_stat=node[0][2].as<double>();
    if(node[0].size()>3)
    {
      HL_Sigma_syst=node[0][3].as<double>();
    }
    else
    {
      HL_Sigma_syst=0.;
    }

  }
  else
  {
    throw std::runtime_error("Error in the HL_Gaussian class, your yaml file has missing Observables");
  }

}

double HL_Gaussian::GetChi2(double theory, double theory_var)
{
  double theory_err=sqrt(theory_var);

  double err2=HL_Sigma_stat*HL_Sigma_stat+ HL_Sigma_syst*HL_Sigma_syst+theory_err*theory_err;
  double chi2=(HL_Central-theory)*(HL_Central-theory)/err2;
  return chi2;
}


double HL_Gaussian::GetLogLikelihood(double theory, double theory_err)
{

  double chi2=GetChi2(theory,theory_err);

  return -0.5*chi2;
}

double HL_Gaussian::GetLikelihood(double theory, double theory_err)
{
  double log_likelihood=GetLogLikelihood(theory,theory_err);
  return gsl_sf_exp(log_likelihood);
}
