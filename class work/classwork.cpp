#include <iostream>

using namespace std;

class Character{
public:
    Character(){
      m_name = "UnKnown";
    }

    Character(char* name){
        m_name = name;
    }



    char* GetName() {return m_name;}
    
    

private:
    char* m_name;
    
};

class Protagoinst : public Character{
    public:
        Protagoinst(){

        }
        
        Protagoinst(char* name) : Character(name){

        }

        
    private:

    
};

int main()
{
    Character* p = new Protagoinst();
    cout << p->GetName() << std::endl;

    p = new Protagoinst("Alex Bowes");
    cout << p->GetName() << endl;


}