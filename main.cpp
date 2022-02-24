/*******
 * Read input from cin
 * Use cout << ... to output your result to STDOUT.
 * Use cerr << ... to output debugging information to STDERR
 * ***/
#include <iostream>
#include <limits>
#include <sstream>
#include <ctype.h>
#include <fstream>
#include <string.h>
#include <cstdlib>
#include <vector>

using namespace std;

struct Collabo
{
    string name;
    int nbSkills;
    vector< pair< string, int> > competence;
};

struct Project
{
    string name;
    int nbDays;
    int score;
    int nbDaysMax;
    int nbSkills;
    vector< pair< string, int> > competence;
};

int main() {
    string line;
    ifstream myfile;
    myfile.open("a.in");
    int nbLine = 0;
    int sizeCount = 0;
    int sizeProject = 0;
    int currentSize = 0;
    int currentProject = 0;
    vector<Collabo> Contributeur;
    vector<Project> Projects;
   if(!myfile.is_open()) {
      perror("Error open");
      return -1;
   }
    while(getline(myfile, line)) {
        {
	    if(sizeCount == 0)
        {
            cout<< "add first time" << endl;
            int space = line.find(' ');
            sizeCount = atoi( line.substr(0,space).c_str());
            sizeProject = atoi( line.substr(space).c_str());;
            nbLine++;
        }
        else
        {
            if (currentSize == 0 && Contributeur.size() < sizeCount ) // first line of contributeur, with name & nb skills
            {

               int space = line.find(' ');
               Collabo x;
               x.name = line.substr(0,space).c_str();
               x.nbSkills =atoi( line.substr(space).c_str());
               Contributeur.push_back(x);
               currentSize++;

            }
            else if (currentSize!=0)
            {

                int n = Contributeur.size();
                int space = line.find(' ');
                string comp = line.substr(0,space).c_str();
                int level =  atoi( line.substr(space).c_str());
                Contributeur[n - 1].competence.push_back(std::make_pair(comp,level));
                if (Contributeur[n-1].competence.size() == Contributeur[n-1].nbSkills)
                {
                    currentSize = 0;

                }
            }

            cout << "sizeCount : " << sizeCount << "sizeProject : " << sizeProject << "currentSize : " << currentSize << endl;
            if (currentSize == 0 && Contributeur.size() == sizeCount-1 && currentProject == 0 && Projects.size() < sizeProject)
            {
               cout << "line vaut " << line << endl;
               int space = line.find(' ');
               Project x;
               x.name = line.substr(0,space).c_str();
               line = line.substr(space).c_str();
               space = line.find(' ');
               x.nbDays = atoi( line.substr(0,space).c_str());
               line = line.substr(space).c_str();
               space = line.find(' ');
               x.score = atoi( line.substr(0,space).c_str());
               space = line.find(' ');
               x.nbDaysMax = atoi( line.substr(0,space).c_str());
               x.nbSkills =atoi( line.substr(space).c_str());
               Projects.push_back(x);
               currentProject++;

            }
            else if (currentProject!=0)
            {

                int n = Projects.size();
                int space = line.find(' ');
                string comp = line.substr(0,space).c_str();
                int level =  atoi( line.substr(space).c_str());
                Projects[n - 1].competence.push_back(std::make_pair(comp,level));
                if (Projects[n-1].competence.size() == Projects[n-1].nbSkills)
                {
                    currentProject =0;

                }

            }
        }

        }


    }
     cout << sizeCount << " "<< sizeProject << "contributeur name : "<<Contributeur[1].name <<"contributeur skills : "<<Contributeur[0].nbSkills << "skills : " << Contributeur[0].competence[0].first;
     cout <<  "project name : "<<Projects[0].name;
    return 0;
	/* Vous pouvez aussi effectuer votre traitement une fois que vous avez lu toutes les données.*/
}
