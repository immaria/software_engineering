#ifndef EURODIFF_WORLDMAP_H
#define EURODIFF_WORLDMAP_H

#include <map>
#include <algorithm>
#include "Country.h"


class WorldMap {
private:
    vector<Country*> countries; 
public:
    WorldMap()
    {

    }

    ~WorldMap()
    {
        for(int i=0;i<countries.size();i++)
        {
            delete countries[i];
        }
    }

    void add_country(Country* country)
    {
        countries.push_back(country);
    }


    vector<pair<string, int>> emulate()
    {
        map<string, int> resultSet; 

        bool isEnd = false;
        int day = 1;

        while(!isEnd)
        {
            isEnd = true;

            for(int i=0;i<countries.size();i++) 
            {
                countries[i]->send_coins_to_neighbours(); 
            }

            for(int i=0;i<countries.size();i++)
            {
                countries[i]->apply_coins_from_reverse();
            }

            for(int i=0;i<countries.size();i++)
            {
                if(countries[i]->is_has_all_coins_types()) 
                {
                    if(resultSet.find(countries[i]->get_name()) == resultSet.end()) 
                    {
                        resultSet.insert(pair<string, int>(countries[i]->get_name(), day)); 
                    }
                }
                else
                {
                    isEnd = false; 
                }
            }

            day++; 
        }

        vector<pair<string, int>> vec;

        for(auto it = resultSet.begin();it != resultSet.end(); ++it)
        {
            vec.push_back(*it);
        }

        sort(vec.begin(), vec.end(), [](pair<string, int> a, pair<string, int> b){
            if(a.second == b.second)
                return a.first < b.first;
            return a.second < b.second;
        });

        return vec;
    }
};


#endif
