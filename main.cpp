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

struct Sortie
{
    string nameOfProject;
    vector<string> CollaboUsed;

};

struct Collabo
{
    string name;
    int nbSkills;
    vector< pair< string, int> > competence;
    vector< pair<int, int> > used;
};

struct Project
{
    string name;
    int nbDays;
    int score;
    int nbDaysMax;
    int nbSkills;
    int tmax;
    vector< pair< string, int> > competence;
    vector<bool> skillUsed;
    double prio;
};

bool isFree(Collabo &a, int debut, int fin)
{
    for (int i = 0; a.used.size(); i++)
    {
        if(!(debut < a.used[i].first && fin < a.used[i].first || debut > a.used[i].second && fin > a.used[i].second))
            return false;
    }
    return true;
}

string hasSkill(Collabo& a, vector<pair<string, int> >&comp, vector<bool>& usedSkill)
{
    for (int i = 0; i < comp.size(); i++)
    {
        for (int j = 0; j < a.competence.size(); j++)
        {
            if(a.competence[j].first == comp[i].first && (a.competence[j].second >= comp[i].second))
               {
               usedSkill[j] = true;
               return comp[i].first;
               }
        }
    }
    return "NO";
}


Sortie listUser(Project& p, vector<Collabo>& allColabo)
{
    vector<int> IndiceDesCollabos;
    Sortie yikes;
    int min = -1;
    for (int i = 0; i < p.nbSkills; i++)
    {
        for (int j = 0; j < allColabo.size(); j++)
        {
            if(hasSkill(allColabo[j],p.competence, p.skillUsed) != "NO" && isFree(allColabo[j], p.tmax, p.nbDaysMax))
            {
                IndiceDesCollabos.push_back(j);
                allColabo[j].name += " ";
                yikes.CollaboUsed.push_back((allColabo[j]));

                allColabo[j].used.push_back(make_pair(p.tmax, p.nbDaysMax)); // gerer le cas ou un skill n'est pas affecté
            }
        }
    }
    if (yikes.CollaboUsed.size() == p.nbSkills)
    {
        return yikes;
    }
    else
    {
        for (int i = 0; i < IndiceDesCollabos.size(); i++)
        {
            allColabo[IndiceDesCollabos[i]].used.pop_back();

        }
    }


}


int main() {
    bool isGoProject;
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
                cout << "name: " <<Contributeur[n-1].name << endl;
                cout << "line vaut contributeur " << line << endl;
                if (Contributeur[n-1].competence.size() == Contributeur[n-1].nbSkills)
                {
                    currentSize = 0;
                    if (Contributeur.size() == sizeCount)
                    {
                        isGoProject = true;
                        continue;
                    }




                }
            }

            //cout << "sizeCount : " << sizeCount << "sizeProject : " << sizeProject << "currentSize : " << currentSize << endl;
            if (currentProject == 0 && Projects.size() < sizeProject && isGoProject )
            {
               cout << "line vaut " << line << endl;
               int space = line.find(' ');
               Project x;
               x.name = line.substr(0,space).c_str();
               line = line.substr(space+1).c_str();
               cout << "line2 vaut " << line << endl;
               space = line.find(' ');
               x.nbDays = atoi( line.substr(0,space).c_str());
               line = line.substr(space+1).c_str();
               cout << "line3 vaut " << line << endl;
               space = line.find(' ');
               x.score = atoi( line.substr(0,space).c_str());
               line = line.substr(space+1).c_str();
               space = line.find(' ');
               x.nbDaysMax = atoi( line.substr(0,space).c_str());
               x.nbSkills =atoi( line.substr(space).c_str());
               x.tmax = x.nbDaysMax - x.nbDays;
               x.skillUsed.push_back(false);
               if (x.nbSkills != 0)
               {
               x.prio = x.score / (x.nbSkills * x.nbDays);
               }
               else
               {
                   x.prio = x.score / (x.nbDays);
               }
               Projects.push_back(x);
               currentProject++;

            }
            else if (currentProject!=0)
            {
                cout << "line vaut skills" << line << endl;
                int n = Projects.size();
                int space = line.find(' ');
                string comp = line.substr(0,space).c_str();
                int level =  atoi( line.substr(space).c_str());
                Projects[n - 1].competence.push_back(std::make_pair(comp,level));
                if (Projects[n-1].competence.size() == Projects[n-1].nbSkills)
                {
                    currentProject = 0;

                }

            }
        }

        }


    }

    for (int i = 0; i <Projects.size(); i++)
    {
        cout << Projects[i].name << endl;
    }
    return 0;
	/* Vous pouvez aussi effectuer votre traitement une fois que vous avez lu toutes les données.*/
}


