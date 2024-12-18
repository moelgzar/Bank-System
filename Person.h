#include<iostream>
#include<string>
using namespace std ;

class clsPerson
{
private:
   string _FirstName ;
   string _LastName ;
   string _Emal ;
   string _Phone ;
public:
    clsPerson(string FirstName , string LastName , string Email  , string Phone ){
        _FirstName = FirstName ;
        _LastName = LastName ; 
        _Emal = Email ;
        _Phone = Phone ; 
    }

    void FirstName(string name ){
        name = _FirstName ;
    }
    string FirstName(){
        return _FirstName ;
    }
    void Phone(string Phone ){
        Phone = _Phone ;
    }
    string Phone(){
        return _Phone ;
    }
string FullName(){
    return FirstName() + LastName() ;
}
    void LastName(string name ){
        name = _LastName ;
    }
    string LastName(){
        return _LastName ;
    }
    void Email(string email ){
        email = _Emal ;
    }
    string Email(){
        return _Emal ;
    }


};
