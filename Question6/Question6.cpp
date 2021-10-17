#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);
struct group
{
   vector<string> names; 
   int departments[3];
};
typedef struct group group;

void theHackathon(int n, int m, int a, int b, int f, int s, int t) {
    int i, j, g1, g2, temp, tempDeps[3];
    map<string, int> players;
    map<int, group> groups;
    vector<string> request, name_group;
    string inputdata_temp;
    group tempgroup;
    tempgroup.names.push_back("");
    int maxGroups[] = {f, s, t};
    bool flag;

    for (i = 0; i < n; ++i)
    {
        getline(cin, inputdata_temp);
        name_group = split_string(inputdata_temp);

        players[name_group[0]] = i;
        tempgroup.names[0] = name_group[0];

        for (j = 0; j < 3; ++j)
        {
            tempgroup.departments[j] = 0;
        }
        tempgroup.departments[stoi(name_group[1])-1] = 1;

        groups[i] = tempgroup;
    }

    for (i = 0; i < m; ++i)
    {
        getline(cin, inputdata_temp);
        request = split_string(inputdata_temp);
        g1 = players[request[0]];
        g2 = players[request[1]];

        if(g1!=g2){)
            {
                flag = true;
                for(j=0; j< 3; j++){
                    temp = group1->departments[j] + group2->departments[j];
                    if(temp > maxGroups[j]){
                        flag = false;
                        break;
                    }
                    tempDeps[j] = temp;
                }
                if(flag){
                    (*group1).names.insert((*group1).names.end(), (*group2).names.begin(), (*group2).names.end());
                    for (j = 0; j < 3; ++j)
                    {
                        (*group1).departments[j]+=tempDeps[j];
                    }
                    for(j=0; j < (*group2).names.size(); j++){
                        players[(*group2).names[j]] = g1;
                    }
                    groups.erase(g2);
                }
            }
        }
    }

    int maxGroupSize =a;
    vector<string> namesToPrint;
    for (const auto& [key, group] : groups) {
        if(group.names.size() > maxGroupSize){
            namesToPrint.clear();
        }
        if(group.names.size() >= maxGroupSize){
           namesToPrint.insert(namesToPrint.end(), group.names.begin(), group.names.end());
            maxGroupSize = group.names.size();
        }
    }

    if(namesToPrint.size()==0){
        cout << "no groups";
    }
    else{
        sort(namesToPrint.begin(), namesToPrint.end());
        for(i=0; i < namesToPrint.size(); i++){
            cout << namesToPrint[i] << "\n";
        }
}

int main()
    string inputdata_temp;
    getline(cin, inputdata_temp);

    vector<string> inputdata = split_string(inputdata_temp);

    int n = stoi(inputdata[0]);

    int m = stoi(inputdata[1]);

    int a = stoi(inputdata[2]);

    int b = stoi(inputdata[3]);

    int f = stoi(inputdata[4]);

    int s = stoi(inputdata[5]);

    int t = stoi(inputdata[6]);

    theHackathon(n, m, a, b, f, s, t);

    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());


    // printf("g1: %d, g2: %d\n", g1, g2);
        while (input_string[input_string.length() - 1] == ' ') {       input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}
