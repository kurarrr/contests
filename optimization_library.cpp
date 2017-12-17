#include<iostream>
#include<cmath>

using namespace std;

const int MAX_CNT = 100,div_num=100;
const double eps = 1e-7,EPS=1e-5;//後者は微分用
const double golden = (sqrt(5)-1)/2;

bool gsm(double (*f)(double),double lb,double ub,double &ans,int &cnt){
  //golden section method
  double l1=-1,l2=-1,a1,a2;
  cnt = 0;
  while(abs(ub-lb)>eps){
    //cout << "[lb,ub] " << lb << "," << ub << endl;
    if(l2==-1){
      l2 = lb + golden * (ub - lb);
      a2 = f(l2);
    }
    if(l1==-1){
      l1 = lb + golden * (l2 - lb);
      a1 = f(l1);
    }

    if(a1<a2){
      ub = l2;
      l2 = l1;
      a2 = a1;
      l1 = -1;
    }else{
      lb = l1;
      l1 = l2;
      a1 = a2;
      l2 = -1;
    }
    if(cnt++>MAX_CNT) return false;
  }
  ans = lb;
  return true;
}

bool bm(double (*fp)(double),double lb,double ub,double &ans,int &cnt){
  //bisection method
  cnt = 0;
  if(lb==0) lb = 0.01;//zero division回避
  double mid,fpmid;
  while(abs(ub-lb)>eps){
    mid = (lb+ub)/2;
    fpmid = fp(mid);
    if(fpmid>0){
      ub = mid;
    }else{
      lb = mid;
    }
    if(cnt++>MAX_CNT) return false;
  }
  ans = lb;
  return true;
}

double nm(double (*fp)(double),double (*fpp)(double),double x_start,double &ans,int &cnt){
  //newton method
  cnt = 0;
  if(x_start==0) x_start = 0.01;
  double next,prev;
  next = x_start;
  do{
    prev = next;
    next = prev - fp(prev)/fpp(prev);
    if(cnt++>MAX_CNT) return false;
  }while(abs(next-prev)>eps);
  ans = next;
  return true;
}

double df(double (*func)(double),double x){
  return (func(x+EPS)-func(x-EPS))/(2*EPS);
}
double df2(double (*func)(double),double x){
  return (func(x+EPS)-2*func(x)+func(x-EPS))/(EPS*EPS);
}

double f1(double x){ return 1/x + exp(x); }
double f1p(double x){ return df(f1,x); }
double f1pp(double x){ return df2(f1,x); }

double f2(double x){ return sin(5*x)+(x-5)*(x-5); }
double f2p(double x){ return df(f2,x); }
double f2pp(double x){ return df2(f2,x); }

int main(){
  double a1,a2;
  int c1,c2;

  cout << "問題(1)" << endl;

  if(gsm(f1,0.0,10,a1,c1)){
    cout << "黄金分割法　 :" << a1 << ",";
    cout << "収束までの回数:" << c1 << endl;
  }else cout << "解無し" << a1 << endl;

  if(bm(f1p,0.0,10,a1,c1)){
    cout << "二分割法　　 :" << a1 << ",";
    cout << "収束までの回数:" << c1 << endl;
  }else cout << "解無し" << a1 << endl;

  if(nm(f1p,f1pp,0.0,a1,c1)){
    cout << "ニュートン法 :" << a1 << ",";
    cout << "収束までの回数:" << c1 << endl << endl;
  }else cout << "解無し" << a1 << endl;

  cout << "問題(2)" << endl;

  double span = 10.0/div_num;
  double a2temp,cntav;
  a2 = 0;

  cntav = 0;
  for(int i=0;i<div_num;i++){
    //区間を100分割して、それぞれで解く
    if(gsm(f2,i*span,(i+1)*span,a2temp,c2)){
      if(f2(a2temp)<f2(a2)){
        a2 = a2temp;
      }
    }
    cntav += double(c2);
  }
  cntav /= double(div_num);
  cout << "黄金分割法　 :" << a2 << ",収束までの平均回数:" << cntav << endl;

  cntav = 0;
  for(int i=0;i<div_num;i++){
    //区間を100分割して、それぞれで解く
    if(bm(f2p,i*span,(i+1)*span,a2temp,c2)){
      if(f2(a2temp)<f2(a2)){
        a2 = a2temp;
      }
    }
    cntav += double(c2);
  }
  cntav /= double(div_num);
  cout << "二分割法　　 :" << a2 << ",収束までの平均回数:" << cntav << endl;

  cntav = 0;
  for(int i=0;i<div_num;i++){
    //区間を100分割して、それぞれで解く
    if(nm(f2p,f2pp,i*span,a2temp,c2)){
      if(f2(a2temp)<f2(a2)){
        a2 = a2temp;
      }
    }
    cntav += double(c2);
  }
  cntav /= double(div_num);
  cout << "ニュートン法 :" << a2 << ",収束までの平均回数:" << cntav << endl;

  return 0;
}