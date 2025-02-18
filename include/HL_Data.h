//   HEPLike: High Energy Physics Likelihoods
//
//   Header for baseic class
//
//   author: Jihyun Bhom, Marcin Chrzaszcz
//   author: Tomas Gonzalo
//////////////////////////////////////////////////
#ifndef HL_DATA_H
#define HL_DATA_H

#include <cmath>
#include <limits>
#include <fstream>
#include <iomanip>



#include "HL_Stats.h"

#include "yaml-cpp/yaml.h"


class HL_Data
{

 public:

  HL_Data();
  HL_Data(std::string);
  HL_Data(std::string,YAML::Node);

  std::string HFile;
  void Read();
  std::string find_path(std::string);
  void set_debug_yaml(bool);



 protected:

  YAML::Node config;

  //HL_LIke info:
  std::string HL_FileName;
  std::string HL_Name;

  // bibligraphic data:
  std::string HL_DOI;
  std::string HL_BibCite;
  std::string HL_BibEntry;
  std::string HL_Arxiv;
  std::string HL_SubmissionYear;
  std::string HL_PublicationYear;

  // Collaborations numbers
  std::string HL_Collaborations;
  std::string HL_Collaboration_number;

  // addition data
  std::string HL_ExperimentalDataLumi; // 1fb for example
  std::string HL_ExperimentalDataYears;
  std::string HL_Decay;
  std::string HL_Kinematics;


  std::string HL_Author;
  std::string HL_Email;
  std::string HL_Type;


  bool initialized;
  bool HL_debug_yaml;

  void read_standard();


};


#endif
