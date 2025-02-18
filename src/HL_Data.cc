//   HEPLike: High Energy Physics Likelihoods
//
//   Module to read yaml files
//
//   author: Jihyun Bhom,  Marcin Chrzaszcz
//   author: Tomas Gonzalo
//////////////////////////////////////////////////


#include <cmath>
#include <limits>
#include <fstream>
#include <iomanip>
#include <iostream>

#include "HL_Stats.h"
#include "HL_Constants.h"
#include "HL_Data.h"



HL_Data:: HL_Data()
{
  initialized=false;
  HL_debug_yaml=false;
  HFile="";

}

HL_Data:: HL_Data(std::string s)
{
  initialized=true;
  HL_debug_yaml=false;
  HFile=s;
  config = YAML::LoadFile(HFile);
}

HL_Data:: HL_Data(std::string s, YAML::Node node)
{
  initialized=true;
  HL_debug_yaml=false;
  HFile=s;
  config = node;
}

void HL_Data::Read()
{
  if(! initialized)
  {
    throw std::runtime_error("HEPLike Warning, TRYING TO READ WITHOUT GIVING ANY FILE!");
    return;
  }
  read_standard();
}


void HL_Data::read_standard()
{
  HL_FileName=config["FileName"].as<std::string>();
  if(config["Name"] ) HL_Name=config["Name"].as<std::string>();
  else if (HL_debug_yaml) std::cout<<"HEPLike Warning, The <Name> is missing in the yaml file"<<std::endl;

  if(config["DOI"] ) HL_DOI=config["DOI"].as<std::string>();
  else if (HL_debug_yaml) std::cout<<"HEPLike Warning, The <DOI> is missing in the yaml file"<<std::endl;

  if(config["BibCite"]) HL_BibCite=config["BibCite"].as<std::string>();
  else if (HL_debug_yaml) std::cout<<"HEPLike Warning, The <BibCite> is missing in the yaml file"<<std::endl;

  if(config["BibEntry"]) HL_BibEntry=config["BibEntry"].as<std::string>();
  else if (HL_debug_yaml) std::cout<<"HEPLike Warning, The <BibEntry> is missing in the yaml file"<<std::endl;

  if(config["Arxiv"]) HL_Arxiv=config["Arxiv"].as<std::string>();
  else if (HL_debug_yaml) std::cout<<"HEPLike Warning, The <Arxiv> is missing in the yaml file"<<std::endl;

  if(config["SubmissionYear"]) HL_SubmissionYear =config["SubmissionYear"].as<std::string>();
  else if (HL_debug_yaml) std::cout<<"HEPLike Warning, The <SubmissionYear> is missing in the yaml file"<<std::endl;

  if(config["PublicationYear"]) HL_PublicationYear=config["PublicationYear"].as<std::string>();
  else if (HL_debug_yaml) std::cout<<"HEPLike Warning, The <PublicationYear> is missing in the yaml file"<<std::endl;

  if(config["Collaborations"]) HL_Collaborations=config["Collaborations"].as<std::string>();
  else if (HL_debug_yaml) std::cout<<"HEPLike Warning, The <Collaborations> is missing in the yaml file"<<std::endl;

  if(config["ExperimentalDataLumi"]) HL_ExperimentalDataLumi=config["ExperimentalDataLumi"].as<std::string>();
  else if (HL_debug_yaml) std::cout<<"HEPLike Warning, The <ExperimentalDataLumi> is missing in the yaml file"<<std::endl;

  if(config["ExperimentalDataYears"]) HL_ExperimentalDataYears=config["ExperimentalDataYears"].as<std::string>();
  else if (HL_debug_yaml) std::cout<<"HEPLike Warning, The <ExperimentalDataYears> is missing in the yaml file"<<std::endl;

  if(config["Process"]) HL_Decay=config["Process"].as<std::string>();
  else if(config["Decay"]) HL_Decay=config["Decay"].as<std::string>();
  else if (HL_debug_yaml) std::cout<<"HEPLike Warning, The <Process,Decay> is missing in the yaml file"<<std::endl;

  if(config["Kinematics"]) HL_Kinematics=config["Kinematics"].as<std::string>();
  else if (HL_debug_yaml) std::cout<<"HEPLike Warning, The <Kinematics> is missing in the yaml file"<<std::endl;

  if(config["HLAuthor"]) HL_Author=config["HLAuthor"].as<std::string>();
  else std::cout<<"HEPLike Warning, The <HLAuthor> is missing in the yaml file"<<std::endl;

  if(config["HLEmail"]) HL_Email=config["HLEmail"].as<std::string>();
  else std::cout<<"HEPLike Warning, The <HLEmail> is missing in the yaml file"<<std::endl;

  if(config["HL_Type"]) HL_Type=config["HL_Type"].as<std::string>();
  else if (HL_debug_yaml) std::cout<<"HEPLike Warning, The <Kinematics> is missing in the yaml file"<<std::endl;


}

std::string HL_Data::find_path(std::string s)
{
  int pos=HFile.find("/data/");
  //string path=HFile.substr (0, pos);
  if(pos<0)
    throw std::runtime_error("Error in HL_ProfLikelihood, didn't find 'data'");
  while(true)
  {
    int pos_new=HFile.find("/data/", pos+1);
    if(pos_new>0)
    {
      pos=pos_new;
    }
    else break;
  }
  std::string path=HFile.substr (0, pos);
  return path+"/"+s;
}

void HL_Data::set_debug_yaml(bool b)
{
    HL_debug_yaml = b;

}
