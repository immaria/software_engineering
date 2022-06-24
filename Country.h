#ifndef EURODIFF_COUNTRY_H
#define EURODIFF_COUNTRY_H

#include <string>
#include "City.h"

class Country {
private:
    string name; 
    vector<City*> cities; 
public:

    Country(string name)
    {
        this->name = name;
    }

    ~Country()
    {
        for(int i=0;i<cities.size();i++)
        {
            delete cities[i];
        }
    }

    string get_name()
    {
        return name;
    }

    void add_city(City* city)
    {
        cities.push_back(city);
    }

    vector<City*>& get_cities()
    {
        return cities;
    }

    void send_coins_to_neighbours()
    {
        for(int i=0;i<cities.size();i++)
        {
            cities[i]->send_coins_to_neighbours();
        }
    }

    void apply_coins_from_reverse()
    {
        for(int i=0;i<cities.size();i++)
        {
            cities[i]->apply_coins_from_reverse();
        }
    }

    bool is_has_all_coins_types()
    {
        return all_of(coins.begin(), coins.end(), [](int x) {
            return x > 0;
        });
    }

    bool is_has_foreign_neighbours()
    {
        return any_of(cities.begin(), cities.end(), [](City* city){
            return city->is_has_foreign_neighbours();
        });
    }
};


#endif
