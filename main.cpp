#include <iostream>
#include <fstream>

#include "WorldMapBuilder.h"

using namespace std;

int main() {
    ifstream file;

    string filename;

    cout << "Filename > ";
    cin >> filename;

    file.open(filename);

    if(!file.is_open())
    {
        cout << "Cant find file!";
        return 0; 
    }

    int test_case = 0, count = 1;
    string country;
    int xl, xh, yl, yh;

    while(count != 0)
    {
        WorldMapBuilder worldMapBuilder;

        file >> count;

        if(count == 0)
            break;

        for(int i=0;i<count;i++)
        {
            file >> country >> xl >> yl >> xh >> yh; 
            worldMapBuilder.add_country(country, xl, xh, yl, yh);  
        }

        WorldMap *worldMap;
        try {
            worldMap = worldMapBuilder.build(); 
        }catch (CountryWithoutNeighboursException& e) {
            cout << "Case number " << ++test_case << endl;
            cout << "Error: " << e.what() << endl;
            continue;
        }

        vector<pair<string, int>> result = worldMap->emulate();
        cout << "Case number " << ++test_case << endl;

        for(auto it = result.begin();it != result.end(); ++it)
        {
            cout << it->first << " " << it->second << endl;
        }
        cout << endl;

        delete worldMap;
    }

    file.close();

    return 0;
}
