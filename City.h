#ifndef EURODIFF_CITY_H
#define EURODIFF_CITY_H

#include <vector>

using namespace std;

class City {
private:
    string country;
    vector<string> coin_types;
    vector<int> coins;
    vector<int> reserve;
    vector<City*> neighbours;
public:

    City(string country, vector<string> coin_types)
    {
        this->country = country;
        this->coin_types = coin_types;

        coins.resize(coin_types.size());
        fill(coins.begin(), coins.end(), 0);

        reserve.resize(coin_types.size());
        fill(reserve.begin(), reserve.end(), 0);

        int index = find(coin_types.begin(), coin_types.end(), country) - coin_types.begin();
        coins[index] = 1000000;
    }

    void add_neighbour(City* city)
    {
        neighbours.push_back(city);
    }

    void send_coins_to_neighbours()
    {
        for(int i = 0;i < coins.size();i++)
        {
            int send_value = coins[i] / 1000;

            for(int j = 0;j < neighbours.size();j++)
            {
                neighbours[j]->receive_coins(coin_types[i], send_value);
                coins[i] -= send_value; 
            }
        }

    }

    void receive_coins(string country, int count)
    {
        int index = find(coin_types.begin(), coin_types.end(), country) - coin_types.begin();
        reserve[index] += count; 
    }

    void apply_coins_from_reverse()
    {
        for(int i = 0;i < coins.size();i++)
        {
            coins[i] += reserve[i];
            reserve[i] = 0;
        }
    }

    bool is_has_all_coins_types()
    {
        for(int i=0;i<coins.size();i++)
        {
            if(coins[i] == 0) {
                return false;
            }
        }

        return true;
    }

    bool is_has_foreign_neighbours()
    {
        for(int i=0;i<neighbours.size();i++)
        {
            if(neighbours[i]->country != country)
                return true;
        }

        return false;
    }
};


#endif
