#include "MantasM2001Hash.hpp"

// bool FailoTikrinimas(string failas)
// {
//     ifstream in(failas);
//     return in.good();
// }

// string DarbasSuFailu(string failas)
// {
//     ifstream in(failas);
//     string eilute;
//     string duomenys;
    

//     while(in)
//     {
//         getline(in,eilute);
//         duomenys += eilute;
//     }
//     in.close();
//     return DuomenuHashinimas(duomenys);
// }

string MantasM2001Hash::DuomenuHashinimas(string duomenys)
{
    string hash; // cia saugojamas hashas
    unsigned int temp = 12345; //kintamasis, kuriame laikomas skaicius, kuri vis keisime dauginant is ivairiu skaiciu (is pradziu sudauginsime su simboliu ascii vertemis ir pan.)
    int ascii = 0; //skaicius gautas is 'temp', kuri naudosim grazinti kokia nors ascii reiksme i hasha

    unsigned int sum = 0; //ascii reiksmiu suma (testavimui)
    //int s = 10000;

    for(int i = 0; i<duomenys.length(); i++) //input'as keicia pati skaiciu
    {
        sum += int(duomenys[i]); //(testavimui)
        temp = (temp * (int(duomenys[i])+2)*2)+i+sum;
        temp<<2;
        temp = temp*temp*temp;

        //if(i == 1022 || i == 1023 || i == 1024 || i == 1025 || i == 1062 || i == 1063) cout<<"i: "<<i<<" "<<temp<<" "<<int(duomenys[i])+2<<endl;
    }

    //cout<<"s: "<<s<<endl; //(testavimui)

    string paverstasSkaicius; //vertimui skaiciu i string
    char simbolis; //char'as kuris eis i hasha (gaunamas is 'ascii' reiksmes)

    //hash'o sudarymas
    for(int i = 0; i<64; i++)
    {
        temp = temp * M_PI;
        paverstasSkaicius = to_string(temp);
        ascii = (paverstasSkaicius[1]*paverstasSkaicius[3] + paverstasSkaicius[4]*paverstasSkaicius.back() + paverstasSkaicius[2]*i + temp/2) % 16 + 48; //gaunam ascii reiksmes 48-63
        //if(i==0) cout<<"a: "<<temp<<endl; //testavimui
        if (ascii>57) ascii += 39; //kad gauti raides a-f
        simbolis = ascii;
        hash += simbolis;
    }
    return hash;
}

// void VartotojoIvedimas()
// {
//     string ats;
//     string failas;
//     string duomenys;
//     string hashas;

//     while(ats!="y" && ats!="n")
//     {
//         cout<<"Ar duomenis imti is failo? (y/n): ";
//         cin>>ats;
//         if(ats!="y" && ats!="n") cout<<"\nIveskite atsakyma is naujo.\n"<<endl;
//     }
//     if(ats=="y")
//     {
//         cout<<"Iveskite failo pavadinima (pvz. failas.txt): ";
//         cin>>failas;
//         if(!FailoTikrinimas(failas))
//         {
//             cout<<"Tokio failo nerasta. Programos darbas baigiamas."<<endl;
//             exit;
//         }
//         hashas = DarbasSuFailu(failas);
//     }
//     else 
//     {
//         cout<<"Iveskite duomenis ranka: ";
//         getline(cin >> ws, duomenys);
//         hashas = DuomenuHashinimas(duomenys);
//     }

//     cout<<"hash'as: "<<hashas<<endl;
//     cout<<"hash'o ilgis: "<<hashas.length()<<endl;
// }