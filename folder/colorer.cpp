#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

int main() {
	ifstream file("gc_4_1");
	int nv, ne;
	file >> nv >> ne;

	vector <pair <int, int> > e(ne);
	for (int i = 0; i < ne; i++) 
	{
		file >> e[i].first >> e[i].second;
	}

	vector<int> c(nv, 0);
	c[0] = 1;
	for (int i = 1; i < nv; i++) {				
	    set <int> mc;

	    for (int j = 0; j < ne; j++){				
	        if (e[j].first == i)			
	            mc.insert(c[e[j].second]);			
	        else if (e[j].second == i) 		       
	            mc.insert(c[e[j].first]);		       
	    }
        set <int>::iterator search;
        for (int j = 1; j < nv + 1; j++) {			
            search = mc.find(j);				
            if (search == mc.end()){				
                c[i] = j;						
                break; 
            }
        }
	}

    sort(c.begin(), c.end());
	cout << *(c.end() - 1)<<endl;

}
