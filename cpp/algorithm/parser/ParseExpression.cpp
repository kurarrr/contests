// verify: http://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=3658794#1

#include "../../template/template.cpp"

class ParseExpression{
  public:
  using Result = pair<int,int>; // value, index
  int idx, val;
  ParseExpression(const string& s){
    // expression := factor{+factor}*
    // factor     := term{*term}*
    // term       := (expression)|Number
    tie(val,idx) = expression(s);
  }
  int op(char optr,int lhs,int rhs){
    if(optr=='+') return lhs+rhs;
    if(optr=='-') return lhs-rhs;
    if(optr=='*') return lhs*rhs;
    if(optr=='/') return lhs/rhs;
    return -1; // undefined
  }
  Result expression(const string& s,int p=0){
    Result res = factor(s,p);
    p = res.second;
    while(p<s.size() && (s[p] == '+' || s[p] == '-')){
      Result right = factor(s,p+1);
      res.first = op(s[p],res.first,right.first);
      p = right.second;
    }
    res.second = p;
    return res;
  }
  Result factor(const string& s,int p=0){
    Result res = term(s,p);
    p = res.second;
    while(p<s.size() && (s[p] == '*' || s[p] == '/')){
      Result right = term(s,p+1);
      res.first = op(s[p],res.first,right.first);
      p = right.second;
    }
    res.second = p;
    return res;
  }
  Result term(const string& s,int p=0){
    if(s[p]=='('){
      Result res = expression(s,p+1);
      res.second++; // skip '('
      return res;
    }else{
      int val = 0;
      while(isdigit(s[p])) val = val * 10 + (s[p++]-'0');
      return Result(val, p);
    }
  }
};

int main(){
  int Q; cin >> Q ;
  rep(i,Q){
    string s;
    cin >> s;
    cout << ParseExpression(s).val << endl;
  }
  return 0;
}
