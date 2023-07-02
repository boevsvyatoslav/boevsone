#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

int main(){
	ifstream inp("ks_19_0");
	long long n, mw;
	inp >> n >> mw;
	vector <long long> q(n);
	vector <long long> w(n);
	for (int i = 0; i < n; i++) 
		inp >> q[i] >> w[i];


    vector <vector <long long> > r(n, vector <long long> (mw + 1, 0));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j <= mw; j++) {
			if (w[i] <= j) {
				if (i > 0) 
					r[i][j] = max(r[i - 1][j], r[i - 1][j - w[i]] + q[i]);
				else r[i][j] = q[i];}
			else if (i > 0)	r[i][j] = r[i - 1][j];}}

	vector <int> result(n, 0);
	int i = n - 1, j = mw;
	while (r[i][j] && i>=1) 
	{if (r[i][j] == r[i - 1][j]) i--;
        else if (r[i][j] == q[i] + r[i - 1][j - w[i]]) {
            result[i] = 1;
            j -= w[i];i--;}}
	long long vs = 0, ws = 0;
	for (int i = 0; i < n; i++){
	    if (result[i]) {vs += q[i];ws += w[i];}}
	cout << vs << endl;
}
