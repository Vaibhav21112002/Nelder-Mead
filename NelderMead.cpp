#include <bits/stdc++.h>
#include <chrono> 
using namespace std;
using namespace chrono;

#define endl "\n"
#define ff first
#define ss second
#define ld long double
#define lld long long double
#define pb push_back
#define all(v) v.begin(),v.end()
#define point pair<double,double>

void __print(int x) {cerr << x;}
void __print(long x) {cerr << x;}
void __print(long long x) {cerr << x;}
void __print(unsigned x) {cerr << x;}
void __print(unsigned long x) {cerr << x;}
void __print(unsigned long long x) {cerr << x;}
void __print(float x) {cerr << x;}
void __print(double x) {cerr << x;}
void __print(long double x) {cerr << x;}
void __print(char x) {cerr << '\'' << x << '\'';}
void __print(const char *x) {cerr << '\"' << x << '\"';}
void __print(const string &x) {cerr << '\"' << x << '\"';}
void __print(bool x) {cerr << (x ? "true" : "false");}
template<typename T, typename V>
void __print(const pair<T, V> &x) {cerr << '{'; __print(x.first); cerr << ','; __print(x.second); cerr << '}';}
template<typename T>
void __print(const T &x) {int f = 0; cerr << '{'; for (auto &i: x) cerr << (f++ ? "," : ""), __print(i); cerr << "}";}
void _print() {cerr << "]\n";}
template <typename T, typename... V>
void _print(T t, V... v) {__print(t); if (sizeof...(v)) cerr << ", "; _print(v...);}
#ifndef ONLINE_JUDGE
#define debug(x...) cerr << "[" << #x << "] = ["; _print(x)
#else
#define debug(x...)
#endif

void init_code(){
    #ifndef ONLINE_JUDGE
    freopen("input.txt","r", stdin);
    freopen("output.txt","w", stdout);
    #endif
}

struct points{
	point u,v,w;
};


double f(point p) {
	double x = p.ff;
	double y = p.ss;
	double ans = pow(x,2) - 4*x + pow(y,2) - y -x*y;
	return ans;
}


void sortPt(points &p){					// Sort Points based on function value
	vector<pair<double,point>> x;
	x.pb(make_pair(f(p.u),p.u));
	x.pb(make_pair(f(p.v),p.v));
	x.pb(make_pair(f(p.w),p.w));
	sort(all(x));
	p.u = x[0].ss;
	p.v = x[1].ss;
	p.w = x[2].ss;
}

point midPt(point x, point y){
	point ans;
	ans.ff = (x.ff + y.ff)/2;
	ans.ss = (x.ss + y.ss)/2;
	return ans;
}

point midPtInv(point x, point y){
	point ans;
	ans.ff = (2*y.ff - x.ff);
	ans.ss = (2*y.ss - x.ss);
	return ans;
}

void nelderMead(points &p){ // ({},{},{})
	sortPt(p);
	point mid = midPt(p.u, p.v);
	point r = midPtInv(p.w,mid);
	point e = midPtInv(mid,r);
	point c1 = midPt(p.w, mid);	
	point c0 = midPt(mid,r);
	point w1 = midPt(p.w, p.u);
	point v1 = midPt(p.v, p.u);
	if(f(r) < f(p.v) and f(r) > f(p.u)){		// Centroid
		p.w = r;
		return;
	}
	if(f(r) < f(p.u)){							// Extend
		if(f(e) < f(r)){
			p.w = e;
			return;
		}else{
			p.w = r;
			return;
		}
	}
	if(f(r) > f(p.u) and f(r) > f(p.v)){		//Contraction
		if(f(c1) > f(c0)){
			swap(c1, c0);
		}
		if(f(c1) < f(p.w)){
			p.w = c1;
			return;
		}
	}

	p.w = w1;									// Shrink
	p.v = v1;
	return;

}

void print(points p){
	sortPt(p);
	cout << "{" << p.u.ff << "," << p.u.ss << "}, {" << f(p.u) <<'}' << endl;
}


void solve()
{
	int n;
	points p;
	cin >> n; 					// Number of iterations
	cin >> p.u.ff >> p.u.ss;  	// First Point
	cin >> p.v.ff >> p.v.ss;	// Second Point
	cin >> p.w.ff >> p.w.ss;	// Third Point
	cout << "1-> ";print(p);
	for(int i = 0; i<n; i++){
		nelderMead(p);
		cout << i+2 << "-> ";print(p);
	}
}

int main()
{
	init_code();
    auto start = high_resolution_clock::now();
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    solve();
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    float timeCount = duration.count();
    timeCount /= 1000000;
    debug("Time Taken",timeCount);
	return 0;
}



// Input - >

// 29
// 0 0
// 1.2 0
// 0 0.8
