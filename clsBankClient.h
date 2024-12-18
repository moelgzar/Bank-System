#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <string>
#include "clsString.h"
#include "Person.h"
using namespace std;

class clsBankClient : public clsPerson
{
private:
    enum eMode
    {
        EmptyMode = 0,
        UpdateMode = 1,
        AddNewMode = 3,
        DeleteMode = 4,
    };
    eMode _Mode;
    string _AccountNumber;
    string _PinCode;
    float _AccountBalance;
    bool  _MarkDeleted = false ;
    /*-----------------------------------------------------------------------------------------------*/
    /// <summary>
    /// Converts a line of text into a clsBankClient object. The line must be in the format of:
    /// FirstName#/#LastName#/#Email#/#Phone#/#AccountNumber#/#PinCode#/#AccountBalance
    /// </summary>
    /// <param name="Line">The line to convert.</param>
    /// <param name="seperator">The seperator to use when splitting the line. Default is "#/#".</param>
    /// <returns>A clsBankClient object with the mode set to eMode::UpdateMode.</returns>
    static clsBankClient _ConvertLineToClientObject(string Line, string seperator = "#//#")
    {
        vector<string> vClientData;
        vClientData = clsString::Split(Line, seperator);
        return clsBankClient(eMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2],
                             vClientData[3], vClientData[4], vClientData[5], stod(vClientData[6]));
    }
    /*-----------------------------------------------------------------------------------------------*/
    /// <summary>
    /// Gets an empty clsBankClient object with the mode set to eMode::EmptyMode.
    /// </summary>
    /// <returns>An empty clsBankClient object.</returns>
    static clsBankClient _GetEmptyClinrtObject()
    {
        return clsBankClient(eMode::EmptyMode, "", "", "", "", "", "", 0);
    }

    /*-----------------------------------------------------------------------------------------------*/

    /// <summary>
    /// Converts a clsBankClient object to a line of text. The line is formatted as:
    /// FirstName#/#LastName#/#Email#/#Phone#/#AccountNumber#/#PinCode#/#AccountBalance
    /// </summary>
    /// <param name="client">The clsBankClient object to convert.</param>
    /// <param name="seperator">The separator to use when joining the fields. Default is "#/#".</param>
    /// <returns>A string representing the clsBankClient object, with fields separated by the specified separator.</returns>
    static string _ConvertClientOblectToLine(clsBankClient client, string seperator = "#//#")
    {

        string DataLineRecord = "";

        DataLineRecord += client.FirstName() + seperator;
        DataLineRecord += client.LastName() + seperator;
        DataLineRecord += client.Email() + seperator;
        DataLineRecord += client.Phone() + seperator;
        DataLineRecord += client.AccountNumber() + seperator;
        DataLineRecord += client.PinCode() + seperator;
        DataLineRecord += to_string(client._AccountBalance);
    }
    /*-----------------------------------------------------------------------------------------------*/

    /// <summary>
    /// Saves a list of clsBankClient objects to a file named "Clients.txt".
    /// Each client object is converted to a line of text using _ConvertClientOblectToLine.
    /// The file is opened in overwrite mode, and each line is written to the file.
    /// </summary>
    /// <param name="vClients">A vector of clsBankClient objects to be saved to the file.</param>
    static void _SaveClintDataToFile(vector<clsBankClient> vClients)
    {
        fstream myfile;
            cout << "\niam now in SAVE function \n";

        myfile.open("Clients.txt", ios::out); // overrite mode
         cout << "\n over ride  \n";

        string DataLine;
        if (myfile.is_open())
        {
                cout << "\niam now ensure the file is open  \n";
            for (clsBankClient c : vClients)
            {
                if(c.IsMarkDeleted() == false){
                cout << "\niam writing now clints again after delte  \n";
                DataLine = _ConvertClientOblectToLine(c);
                myfile << DataLine << endl;
                }
            }
            myfile.close();
            cout << "\n close file   \n";
        }
    }
    /*-----------------------------------------------------------------------------------------------*/
    /// <summary>
    /// Loads the list of clsBankClient objects from a file named "Clients.txt". The file is opened in read mode, and each line is read and converted to a clsBankClient object using _ConvertLineToClientObject.
    /// </summary>
    /// <returns>A vector of clsBankClient objects that were loaded from the file.</returns>
    /// function used _ConvertLineToClientObject().
    static vector<clsBankClient> _LoadClientDataFromFile()
    {

        vector<clsBankClient> vClient;

        fstream myfile;
        myfile.open("Clients.txt", ios::in);
        if (myfile.is_open())
        {

            string Line;
            while (getline(myfile, Line))
            {
                clsBankClient client = _ConvertLineToClientObject(Line);

                vClient.push_back(client);
            }
        }
        return vClient;
    }

    /// <summary>
    /// Updates the current clsBankClient object in the file "Clients.txt".
    /// The file is loaded into a vector of clsBankClient objects.
    /// The first object in the vector that has the same AccountNumber() as the current object is overwritten with the current object.
    /// The vector is then saved back to the file.
    /// function used _LoadClientDataFromFile() , _SaveClintDataToFile().
    /// </summary>
    void _Update()
    {

        vector<clsBankClient> vClient;
        vClient = _LoadClientDataFromFile();
        for (clsBankClient &c : vClient)
        {
            if (c.AccountNumber() == AccountNumber())
                c = *this;
            break;
        }

        _SaveClintDataToFile(vClient);
    }
    /*-----------------------------------------------------------------------------------------------*/
    /// <summary>
    /// Determines if the current clsBankClient object is in an empty state.
    /// </summary>
    /// <returns>True if the object is in EmptyMode; otherwise, false.</returns>
    bool Is_empty()
    {
        return (_Mode == eMode::EmptyMode);
    }

    bool IsMarkDeleted(){
        return _MarkDeleted ;
    }
    void _AddNew()
    {

        fstream myfile;

        myfile.open("Clients.txt", ios::out); // overrite mode
        string DataLine;
        if (myfile.is_open())
        {

            DataLine = _ConvertClientOblectToLine(*this);
            myfile << DataLine << endl;

            myfile.close();
        }


    }

    void _DeleteClient(){

     }
public:
    clsBankClient(eMode Mode, string FirstName, string LastName,
                  string Email, string Phone, string AccountNumber, string PinCode,
                  float AccountBalance) : clsPerson(FirstName, LastName, Email, Phone)

    {
        _Mode = Mode;
        _AccountNumber = AccountNumber;
        _PinCode = PinCode;
        _AccountBalance = AccountBalance;
    }

    void print()
    {

        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << FirstName();
        cout << "\nLastName    : " << LastName();
        cout << "\nFull Name   : " << FullName();
        cout << "\nEmail       : " << Email();
        cout << "\nPhone       : " << Phone();
        cout << "\nAcc. Number : " << _AccountNumber;
        cout << "\nPassword    : " << _PinCode;
        cout << "\nBalance     : " << _AccountBalance;
        cout << "\n___________________\n";
    }
    /*-----------------------------------------------------------------------------------------------*/
    /// Set and Get utlity functions
    void AccountBalance(float AccountBalance)
    {
        _AccountBalance = AccountBalance;
    }
    float AcountBalance()
    {
        return _AccountBalance;
    }
    string AccountNumber()
    {
        return _AccountNumber;
    }

    void PinCode(string PinCode)
    {
        _PinCode = PinCode;
    }
    string PinCode()
    {
        return _PinCode;
    }
    /*-----------------------------------------------------------------------------------------------*/

    /// <summary>
    /// Finds the clsBankClient object in the file "Clients.txt" that has the specified account number.
    /// </summary>
    /// <param name="AccoutNumber">The account number to search for.</param>
    /// <returns>The found clsBankClient object, or an empty object if not found.</returns>
    /// function used _ConvertLineToClientObject , _GetEmptyClinrtObject
    static clsBankClient Find(string AccoutNumber)
    {

        vector<clsBankClient> vClients;
        fstream Myfile;
        Myfile.open("Clients.txt", ios::in); // read from file
        if (Myfile.is_open())
        {
            string Line;
            while (getline(Myfile, Line))
            {
                clsBankClient Client = _ConvertLineToClientObject(Line);
                if (Client.AccountNumber() == AccoutNumber)
                {
                    Myfile.close();
                    return Client;
                }
                vClients.push_back(Client);
            }
            Myfile.close();
            return _GetEmptyClinrtObject();
        }
    }

    /// <summary>
    /// Finds the clsBankClient object in the file "Clients.txt" that has the specified account number and pin code.
    /// </summary>
    /// <param name="AccoutNumber">The account number to search for.</param>
    /// <param name="PinCode">The pin code to search for.</param>
    /// <returns>The found clsBankClient object, or an empty object if not found.</returns>
    /// function used _ConvertLineToClientObject , _GetEmptyClinrtObject
    static clsBankClient Find(string AccoutNumber, string PinCode)
    {
        vector<clsBankClient> vClients;
        fstream Myfile;
        Myfile.open("Clients.txt", ios::in); // read from file
        if (Myfile.is_open())
        {
            string Line;
            while (getline(Myfile, Line))
            {
                clsBankClient Client = _ConvertLineToClientObject(Line);
                if (Client.AccountNumber() == AccoutNumber && Client.PinCode() == PinCode)
                {
                    Myfile.close();
                    return Client;
                }
                vClients.push_back(Client);
            }
            Myfile.close();
        }
    }
    /*-----------------------------------------------------------------------------------------------*/
    /// <summary>
    /// Determines if the clsBankClient object with the specified account number exists in the file "Clients.txt".
    /// </summary>
    /// <param name="AccountNumber">The account number to search for.</param>
    /// <returns>True if the object exists; otherwise, false.</returns>
    /// function used Find
    static bool IsClintExist(string AccountNumber)
    {
        clsBankClient client = clsBankClient::Find(AccountNumber);
        return (!(client.Is_empty()));
    }

    enum enSaveRes
    {
        SvFaildEmpty = 0,
        SvSucccessed = 1,
        SvFaildAccountExit = 2
    };
    /*-----------------------------------------------------------------------------------------------*/
    /// <summary>
    /// Saves the current clsBankClient object to a file named "Clients.txt".
    /// </summary>
    /// <returns>enSaveRes::SvSucccessed if the save operation succeeded; otherwise, enSaveRes::SvFaildEmpty.</returns>
    /// <remarks>If the object is empty (i.e. the Mode is eMode::EmptyMode), a message is printed to the console and the function returns enSaveRes::SvFaildEmpty.</remarks>
    enSaveRes Save()
    {
        switch (_Mode)
        {
        case UpdateMode:
            _Update();
            return SvSucccessed;
            break;

        case EmptyMode:
            return SvFaildEmpty;
            break;
        case AddNewMode:
        {
            if (clsBankClient::IsClintExist(_AccountNumber))
                return SvFaildAccountExit;
            else
            {
                _AddNew();
                return SvSucccessed;
            }
            break;
        }
        case DeleteMode:
        {
            if (clsBankClient::IsClintExist(_AccountNumber))
            {
                _DeleteClient();
                return SvSucccessed ;
            }
            else
            {
                return SvFaildEmpty;
            }
            break;
        }
        }
    }
    static clsBankClient GetAddNewClientObject(string AccountNumber)
    {
        return clsBankClient(eMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
    }

   bool  Delete(){
    cout << "\niam now in delete function \n";
    vector<clsBankClient> vClient ;
    vClient = _LoadClientDataFromFile();
    cout << "after loading the clients \n";

    for(clsBankClient& c : vClient)
    {
        if(c.AccountNumber() == AccountNumber())
        {
            c._MarkDeleted = true;
             cout << "\nafter marking \n";
            break; 
        }
    }

    _SaveClintDataToFile(vClient);
    *this = _GetEmptyClinrtObject();
 return true ;
    }
  static  vector<clsBankClient> GetClientsList(){
        return _LoadClientDataFromFile();
    }

    static float TotalBalance(){
        vector<clsBankClient> vClients  = GetClientsList();
        float total  = 0 ;
        for (clsBankClient c : vClients){
            total += c.AcountBalance(); 
        }
        return total;
    }
};