#include<iostream>
#include<cmath>
#include<vector>
#include<string>

using namespace std;

const int MAX_CNT = 1000,div_num=100;
const double EPS=1e-5;

string show_vec(const vector<double> &x){
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

double inner_product(const vector<double> &x,const vector<double> &y){
  double res=0.0;
  for(int i=0;i<x.size();i++) res+=x[i]*y[i];
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
    //cout << "p " << p << endl;
    q = (-f(x2)+4*f(x1)-3*f(x))/(2*alpha);
    alpha = - q/(2*p);
    //cout << "alpha " << alpha << endl;
  }
  return alpha;
}

bool sdm(double (*f)(vector<double>&),vector<double> (*df)(vector<double>&),vector<double> &x,double &ans,int &cnt,const vector<double> &iv){
  //最急降下法
  int n = x.size();
  double delta;
  vector<double> now(n,0),next(n),s(n);
  next = iv;
  cnt=0;
  do{
    now = next;
    s=pro_vec(-1,df(now));
    delta = ls(f,now,s,10);
    for(int i=0;i<n;i++) next[i]=now[i] + delta * s[i];
  }while(hypot(now,next)>EPS && cnt++<MAX_CNT);
  ans = f(next);
  x = next;
  return cnt<MAX_CNT;
}
bool cgm(double (*f)(vector<double>&),vector<double> (*df)(vector<double>&),vector<double> &x,double &ans,int &cnt,const vector<double> &iv){
  //共役勾配法
  int n = x.size();
  double delta;
  vector<double> now(n,0),next(n),s(n);
  next = iv;
  s=pro_vec(-1,df(next));
  cnt=0;
  do{
    now = next;
    delta = ls(f,now,s,10);
    //cout << "delta" << delta << endl;
    for(int i=0;i<n;i++) next[i]= now[i] + delta * s[i];
    //cout << "x:" << show_vec(next) << endl;
    vector<double> a(n),b(n);
    a = df(next); b = df(now);
    double c = inner_product(a,a), d = inner_product(b,b);
    s = add_vec(pro_vec(-1,a),pro_vec(c/d,s));
  }while(hypot(now,next)>EPS && cnt++<MAX_CNT);
  ans = f(next);
  x = next;
  return cnt<MAX_CNT;
}
bool qn(double (*f)(vector<double>&),vector<double> (*df)(vector<double>&),vector<double> &x,double &ans,int &cnt,const vector<double> &iv){
  //準ニュートン法
  int n = x.size();
  double delta;
  vector<double> now(n,0),next(n),dx(n);
  vector<vector<double>> H(n,vector<double>(n,0));
  for(int i=0;i<n;i++) H[i][i] = 1.0;
  next = iv;
  cnt=0;
  while(true){
    now = next;
    vector<double> temp(n);
    temp = df(now);
    for(int i=0;i<n;i++){
      dx[i] = 0;
      for(int j=0;j<n;j++) dx[i]-=H[i][j]*temp[j];
    }
    double delta = ls(f,now,dx,10);
    for (int i=0; i<n; i++) dx[i] *=delta;
    next = add_vec(now,dx);
    if(hypot(now,next)<EPS) break;
    if(cnt++>MAX_CNT) return false;

    vector<vector<double>> A(n,vector<double>(n,0)),temp1(n,vector<double>(n,0));
    vector<double> dy(n),temp3(n);
    temp3 = df(next);
    for (int i=0; i<n; i++) dy[i] = temp3[i] - temp[i];
    double yx;
    yx = inner_product(dx,dy);
    for (int i=0; i<n; i++) 
      for (int j=0; j<n; j++) A[i][j] = dy[i]*dx[j]; 
    for (int i=0; i<n; i++) 
      for (int j=0; j<n; j++) A[i][j] /= (-yx);
    for (int i=0; i<n; i++) A[i][i]+=1;

    for (int i=0; i<n; i++) 
      for (int j=0; j<n; j++)
        for (int k=0; k<n; k++) temp1[i][j]+=A[k][i]*H[k][j];
    for (int i=0; i<n; i++)
      for(int j=0; j<n; j++) H[i][j] = 0;
    for (int i=0; i<n; i++) 
      for (int j=0; j<n; j++)
        for (int k=0; k<n; k++) H[i][j]+=temp1[i][k]*A[k][j];

    for (int i=0; i<n; i++)
      for(int j=0; j<n; j++) H[i][j] += dx[i]*dx[j]/yx; 
  }
  ans = f(next);
  x = next;
  return true;
}

int main(){
  vector<double> x1(4),x2(4),x3(2);
  double a1,a2,a3;
  int cnt;
  cout << "問題(1)" << endl;
  vector<double> iv1(4,1);
  if(sdm(f1,df1,x1,a1,cnt,iv1)){
    cout << "最急降下法" << endl;
    cout << "初期値 x = " << show_vec(iv1) << endl;
    cout << "最小値:" << a1 << endl;
    cout << "x = " + show_vec(x1) << endl;
    cout << "収束回数:" << cnt << endl << endl;
  }else{
    cout << "収束しない" << endl;
  }
  if(cgm(f1,df1,x1,a1,cnt,iv1)){
    cout << "共役勾配法" << endl;
    cout << "初期値 x = " << show_vec(iv1) << endl;
    cout << "最小値:" << a1 << endl;
    cout << "x = " + show_vec(x1) << endl;
    cout << "収束回数:" << cnt << endl << endl;
  }else{
    cout << "収束しない" << endl;
  }
  if(qn(f1,df1,x1,a1,cnt,iv1)){
    cout << "準ニュートン法" << endl;
    cout << "初期値 x = " << show_vec(iv1) << endl;
    cout << "最小値:" << a1 << endl;
    cout << "x = " + show_vec(x1) << endl;
    cout << "収束回数:" << cnt << endl << endl;
  }else{
    cout << "収束しない" << endl;
  }

  cout << "問題(2)" << endl;
  vector<double> iv2(4,1);
  if(sdm(f2,df2,x2,a2,cnt,iv2)){
    cout << "最急降下法" << endl;
    cout << "初期値 x = " << show_vec(iv2) << endl;
    cout << "最小値:" << a2 << endl;
    cout << "x = " + show_vec(x2) << endl;
    cout << "収束回数:" << cnt << endl << endl;
  }else{
    cout << "収束しない" << endl;
  }
  if(cgm(f2,df2,x2,a2,cnt,iv2)){
    cout << "共役勾配法" << endl;
    cout << "初期値 x = " << show_vec(iv2) << endl;
    cout << "最小値:" << a2 << endl;
    cout << "x = " + show_vec(x2) << endl;
    cout << "収束回数:" << cnt << endl << endl;
  }else{
    cout << "収束しない" << endl;
  }
  if(qn(f2,df2,x2,a2,cnt,iv2)){
    cout << "準ニュートン法" << endl;
    cout << "初期値 x = " << show_vec(iv2) << endl;
    cout << "最小値:" << a2 << endl;
    cout << "x = " + show_vec(x2) << endl;
    cout << "収束回数:" << cnt << endl << endl;
  }else{
    cout << "収束しない" << endl;
  }


  cout << "問題(3)" << endl;
  vector<double> iv3(2,0);
  if(sdm(f3,df3,x3,a3,cnt,iv3)){
    cout << "最急降下法" << endl;
    cout << "初期値 x = " << show_vec(iv3) << endl;
    cout << "最小値:" << a3 << endl;
    cout << "x = " + show_vec(x3) << endl;
    cout << "収束回数:" << cnt << endl << endl;
  }else{
    cout << "収束しない" << endl;
  }
  if(cgm(f3,df3,x3,a3,cnt,iv3)){
    cout << "共役勾配法" << endl;
    cout << "初期値 x = " << show_vec(iv3) << endl;
    cout << "最小値:" << a3 << endl;
    cout << "x = " + show_vec(x3) << endl;
    cout << "収束回数:" << cnt << endl << endl;
  }else{
    cout << "収束しない" << endl;
  }
  if(qn(f3,df3,x3,a3,cnt,iv3)){
    cout << "準ニュートン法" << endl;
    cout << "初期値 x = " << show_vec(iv3) << endl;
    cout << "最小値:" << a3 << endl;
    cout << "x = " + show_vec(x3) << endl;
    cout << "収束回数:" << cnt << endl << endl;
  }else{
    cout << "収束しない" << endl;
  }


  return 0;
}