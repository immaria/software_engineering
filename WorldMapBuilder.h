#ifndef EURODIFF_WORLDMAPBUILDER_H
#define EURODIFF_WORLDMAPBUILDER_H

#include "WorldMap.h"

class CountryWithoutNeighboursException : exception{
private:
    string country;
public:
    CountryWithoutNeighboursException(string country) {
        this->country = country;
    }

    string what () {
        return country + " without neighbours";
    }
};

class WorldMapBuilder {
private:
    vector<string> country_names;
    string grid[10][10]; 
public:
    WorldMapBuilder()
    {
        for(int i=0;i<10;i++)
        {
            for(int j=0;j<10;j++)
            {
                grid[i][j] = "";
            }
        }
    }

    void add_country(string name, int xl, int xh, int yl, int yh)
    {
        country_names.push_back(name); 

        int minX = min(xl, xh) - 1;
        int minY = min(yl, yh) - 1;

        int w = abs(xh - xl) + 1;
        int h = abs(yl - yh) + 1;

        for(int i=minY;i<minY + h;i++)
        {
            for(int j=minX;j<minX + w;j++)
            {
                grid[i][j] = name;
            }
        }
    }

    WorldMap* build()
    {
        WorldMap* worldMap = new WorldMap();
        vector<Country*> countries;

        for(int i=0;i<country_names.size();i++)
        {
            countries.push_back(new Country(country_names[i]));
            worldMap->add_country(countries[i]);
        }

        City* cities[10][10];

        for(int i=0;i<10;i++)
        {
            for(int j=0;j<10;j++)
            {
                if(grid[i][j] == "") 
                {
                    cities[i][j] = nullptr;
                    continue;
                }

                cities[i][j] = new City(grid[i][j], country_names);

                for(int k=0;k<countries.size();k++)
                {
                    if(countries[k]->get_name() == grid[i][j])
                    {
                        countries[k]->add_city(cities[i][j]);
                        break;
                    }
                }
            }
        }

        for(int i=0;i<10;i++)
        {
            for(int j=0;j<10;j++)
            {
                if(cities[i][j] == nullptr)
                    continue;

                if(i != 0 && cities[i-1][j] != nullptr) 
                    cities[i][j]->add_neighbour(cities[i-1][j]);  

                if(i != 9 && cities[i+1][j] != nullptr)
                    cities[i][j]->add_neighbour(cities[i+1][j]);

                if(j != 0 && cities[i][j-1] != nullptr)
                    cities[i][j]->add_neighbour(cities[i][j-1]);

                if(j != 9 && cities[i][j+1] != nullptr)
                    cities[i][j]->add_neighbour(cities[i][j+1]);
            }
        }

        if(countries.size() == 1)
            return worldMap;

        for(int i=0;i<countries.size();i++)
        {
            if(!countries[i]->is_has_foreign_neighbours())
            {
                throw CountryWithoutNeighboursException(countries[i]->get_name());
            }
        }

        return worldMap;
    }
};


#endif
