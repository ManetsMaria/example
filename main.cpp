#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <iterator>
using namespace std;
ifstream in3 ("inputstudents.txt");
ifstream in31 ("inputstudentsagain.txt");
  struct SStud
  {
      string name;
      int group;
      double ball;
      SStud() {}
      SStud (string n, int g, double b): name(n), group (g), ball (b) {}
      void show()
      {
          cout<<name<<" "<<group<<" "<<ball<<" ";
      }
      friend ostream& operator<<(ostream& os, const SStud& dt)
      {
          os<<dt.name<<endl;;
          return os;
      }
  };
  class FindBall
  {
      double ball;
  public:
    FindBall(double b): ball(b) {}
    bool operator () (const SStud& st)
    {
        return (st.ball==ball);
    }
  };
  class NotInputtingGroup
  {
      int g;
  public:
    NotInputtingGroup(int group): g(group) {}
    bool operator () (const SStud& st)
    {
        return (st.group!=g);
    }
  };
  bool sortBySurname(const SStud& st, const SStud& s)
  {
      return (st.name<s.name);
  }
  bool sortBySurnameAndGroup (const SStud& st, const SStud& s)
  {
      if (st.name==s.name)
      {
          return (st.group<s.group);
      }
      else {return (st.name<s.name);}
  }
  bool sortByBall (const SStud& st, const SStud& s)
  {
      return (st.ball<s.ball);
  }
  class PredicateForAll
  {
      SStud& st;
  public:
    PredicateForAll (SStud& s): st(s) {}
    bool operator () (SStud& s)
    {
        if (s.name==st.name && s.group==st.group)
        {
            st.ball=(st.ball+s.ball)/2;
            return true;
        }
        return false;
    }
  };
  bool findDouble (const SStud& st, const SStud s)
  {
      return (st.group==s.group && st.name==s.name);
  }
 int main ()
  {
       vector <SStud> students;
        while (!in3.eof())
         {
            string n;
            int g;
            double b;
            in3>>n;
            in3>>g;
            in3>>b;
            SStud s (n, g, b);
            students.push_back(s);
         }
         vector<SStud>::iterator ptr;
         cout<<"our students"<<endl;
         for (ptr=students.begin(); ptr!=students.end(); ptr++)
            ptr->show();
         cout<<endl;
         cout<<"input ball"<<endl;
         double ball;
         cin>>ball;
         cout<<"numbers of students with "<<ball<<" ball is "<<count_if(students.begin(), students.end(), FindBall(ball))<<endl;
         cout<<"input group"<<endl;
         int g;
         cin>>g;
         cout<<"list of student from "<<g<<" group"<<endl;
         remove_copy_if(students.begin(), students.end(), ostream_iterator <SStud> (cout), NotInputtingGroup(g));
         vector<SStud> copyback (students.size());
         cout<<"list of information about students backword"<<endl;
         copy(students.rbegin(), students.rend(), copyback.begin());
         for (ptr=copyback.begin(); ptr!=copyback.end(); ptr++)
            ptr->show();
         cout<<endl;
         cout<<"sort by name"<<endl;
         sort (students.begin(), students.end(), sortBySurname);
         for (ptr=students.begin(); ptr!=students.end(); ptr++)
            ptr->show();
         cout<<endl;
         cout<<"sort by ball"<<endl;
         sort (students.begin(), students.end(), sortByBall);
         for (ptr=students.begin(); ptr!=students.end(); ptr++)
            ptr->show();
         cout<<endl;
         cout<<"students from second file"<<endl;
         while (!in31.eof())
         {
            string n;
            int g;
            double b;
            in31>>n;
            in31>>g;
            in31>>b;
            SStud s (n, g, b);
            s.show();
            students.push_back(s);
            replace_if (students.begin(), students.end(), PredicateForAll(s), s);
         }
           cout<<endl;
           cout<<"sort by name and group and merge of students with average ball"<<endl;
         sort (students.begin(), students.end(), sortBySurnameAndGroup);
         vector<SStud>::iterator ptr1;
           ptr1=unique(students.begin(), students.end(), findDouble);
           for (ptr=students.begin(); ptr!=ptr1; ptr++)
            ptr->show();
            cout<<endl;
           return 0;
     }
