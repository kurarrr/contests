#include<iostream>
#include<cmath>
#include<vector>
#include<string>

using namespace std;

const int MAX_CNT = 1000,div_num=100;
const double EPS=1e-5;

string show_vec(vector<double> &x){
  string s = "";
  s += "( ";
  for(int i=0;i<x.size()-1;i++) s += (to_string(x[i])+", ");
  s += (to_string(x[x.size()-1])+")");
  return s;
}

vector<double> add_vec(const vector<double> &x1,const vector<double> &x2){
  vector<double> res(x1.size());
  for(int i=0;i<x1.size();i++) res[i]=x1[i]+x2[i];
  return res;
}

vector<double> pro_vec(double a,const vector<double> &x1){
  vector<double> res(x1.size());
  for(int i=0;i<x1.size();i++) res[i]=x1[i]*a;
  return res;
}

vector<double> df(double (*func)(vector<double>&),vector<double> x){
  int n = x.size();
  vector<double> res(n);
  for(int i=0;i<n;i++){
    x[i] += EPS;
    res[i] = func(x);
    x[i] -= 2*EPS;
    res[i] -= func(x);
    x[i] += EPS;
    res[i] /= (2*EPS);
  }
  return res;
}
vector<double> ddf(double (*func)(vector<double>&),vector<double> x){
  int n = x.size();
  vector<double> res(n);
  for(int i=0;i<n;i++){
    x[i] += EPS;
    res[i] = func(x);
    x[i] -= 2*EPS;
    res[i] += func(x);
    x[i] += EPS;
    res[i] -= 2*func(x);
    res[i] /= (EPS*EPS);
  }
  return res;
}

double hypot(vector<double> &x1,vector<double> &x2){
  double res=0.0;
  for(int i=0;i<x1.size();i++) res+=pow(x1[i]-x2[i],2);
  return sqrt(res);
}

vector<vector<double>> A1
={
  {9,12,-6,-3},
  {12,41,2,11},
  {-6,2,24,-8},
  {-3,11,-8,62}
};
vector<double> B1={-27,42,32,-23};
double C1 = 163;
vector<vector<double>> A2
={
  {16,8,12,-12},
  {8,29,16,9},
  {12,16,29,-19},
  {-12,9,-19,35}
};

vector<double> B2={7,5,-2,9};
double C2 = 5;

double f1(vector<double> &x){
  double res = 0;
  for(int i=0;i<4;i++)
    for(int j=0;j<4;j++) res += A1[i][j] * x[i] * x[j];
  res /= 2.0;
  for(int i=0;i<4;i++) res += B1[i] * x[i];
  res += C1;
  return res;
}

vector<double> df1(vector<double> &x){
  vector<double> res(4,0);
  for(int i=0;i<4;i++)
    for(int j=0;j<4;j++) res[i] += A1[i][j] * x[j];
  for(int i=0;i<4;i++) res[i]+=B1[i];
  return res;
}

double f2(vector<double> &x){
  double res = 0;
  for(int i=0;i<4;i++)
    for(int j=0;j<4;j++) res += A2[i][j] * x[i] * x[j];
  res /= 2.0;
  for(int i=0;i<4;i++) res += B2[i] * x[i];
  res += C2;
  return res;
}

vector<double> df2(vector<double> &x){
  vector<double> res(4,0);
  for(int i=0;i<4;i++)
    for(int j=0;j<4;j++) res[i] += A2[i][j] * x[j];
  for(int i=0;i<4;i++) res[i]+=B2[i];
  return res;
}

double f3(vector<double> &x){
  return pow(x[0]-1,2)+10*pow(x[0]*x[0]-x[1],2);
}

vector<double> df3(vector<double> &x){
  vector<double> res(2,0);
  res[0] = 2*x[0]*(20*x[0]*x[0]-20*x[1]+1)-2;
  res[1] = 20*(x[1]-x[0]*x[0]);
  return res;
}

double ls(double (*f)(vector<double>&),vector<double> &x,vector<double> &s,int n){
  //ラインサーチ
  double p,q,r,alpha=1e-1;
  int _s = x.size();
  vector<double> x1(_s),x2(_s);
  for(int i=0;i<n;i++){
    x1 = add_vec(x,pro_vec(alpha,s));
    x2 = add_vec(x,pro_vec(alpha*2,s));
    p = (f(x2)-2*f(x1)+f(x))/(2*alpha*alpha);
    q = (-f(x2)+4*f(x1)-3*f(x))/(2*alpha);
    alpha = - q/(2*p);
  }
  return alpha;
}

bool sdm(double (*f)(vector<double>&),vector<double> (*d1)(vector<double>&),vector<double> &x,double &ans,int &cnt){
  //最急降下法
  int n= x.size();
  double delta;
  vector<double> now(n,0),next(n),s(n);
  cnt=0;
  do{
    now = next;
    s=pro_vec(-1,d1(now));
    delta = ls(f,now,s,10);
    // cout << "delta = " << delta << endl;
    // cout << "勾配:" << show_vec(s) << endl;
    for(int i=0;i<n;i++) next[i]=now[i] + delta * s[i];
    // cout << "x:" << show_vec(now) << endl;
    // cout << f(now) << endl;
    if(cnt++>MAX_CNT) return false;
  }while(hypot(now,next)>EPS);
  ans = f(next);
  x = next;
  return true;
}


// bool cgm(double (*f)(vector<double>&),vector<double> &x,vector<double> default,double &ans,int &cnt){
//   //共役勾配法
//   int n= x.size();
//   double delta;
//   vector<double> now(n,0),next(n),s(n);
//   cnt=0;
//   while(true){
//     now = next;
//     s=df(f,now);
//     // cout << "勾配:" << show_vec(s) << endl;
//     for(int i=0;i<n;i++) next[i]=now[i]-delta*s[i];
//     // cout << "x:" << show_vec(now) << endl;
//     // cout << f(now) << endl;
//     if(cnt++>MAX_CNT) return false;
//   }
//   ans = f(next);
//   x = next;
//   return true;
// }

int main(){
  vector<double> x1(4),x2(4),x3(2);
  double a1,a2,a3;
  int cnt;
  cout << "問題(1)" << endl;
  if(sdm(f1,df1,x1,a1,cnt)){
    cout << "最急降下法" << endl;
    cout << "最小値:" << a1 << endl;
    cout << "x = " + show_vec(x1) << endl;
    cout << "収束回数:" << cnt << endl;
  }else{
    cout << "収束しない" << endl;
  }

  cout << "問題(2)" << endl;
  if(sdm(f2,df2,x2,a2,cnt)){
    cout << "最急降下法" << endl;
    cout << "最小値:" << a2 << endl;
    cout << "x = " + show_vec(x2) << endl;
    cout << "収束回数:" << cnt << endl;
  }else{
    cout << "収束しない" << endl;
  }


  cout << "問題(3)" << endl;
  if(sdm(f3,df3,x3,a3,cnt)){
    cout << "最急降下法" << endl;
    cout << "最小値:" << a3 << endl;
    cout << "x = " + show_vec(x3) << endl;
    cout << "収束回数:" << cnt << endl;
  }else{
    cout << "収束しない" << endl;
  }


  return 0;
}