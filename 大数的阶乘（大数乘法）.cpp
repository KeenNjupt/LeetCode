#include<iostream>
#include<vector>
#include<functional>
#include<memory>


using namespace std;


void reverse(string& t){
    int end = t.size()-1;
    int start = 0;
    while(start<end){
        swap(t[start++],t[end--]);
    }

}
void mult(string& a, string& b){ // 将a*b的结果赋予a
    size_t lena = a.size();
    size_t lenb = b.size();
    // reverse(a);
    // reverse(b);
    // a,b从左到右，由低位到高位
    string res;
    int iscarry = 0;
    for(size_t i=0;i<lena;++i){
        for(size_t j=0;j<lenb;++j){
            int t = (a[i]-'0')*(b[j]-'0');
            t += iscarry;
            if(t>=10){
                iscarry = t/10;
                t %= 10;
            }
            else iscarry = 0;
            if(j+i<res.size()) {
                int ori = res[i+j]-'0';
                ori += t;
                if(ori>=10){
                    ori %= 10;
                    ++iscarry;
                }
                res[i+j] = ori+'0';
            }
            else res.push_back(t+'0');
        }
        if(iscarry>0) res.push_back(iscarry+'0');    
        iscarry = 0;
        // string st = res;
        // reverse(st);
        // cout<<st<<endl;
    }
    if(iscarry>0) res.push_back(iscarry+'0');
    a = res;
}
void minus1(string& res){ //字符串表示的数减一
    bool iscarry = true;
    size_t len = res.size();
    for(size_t i = 0;i<len;++i){
        int t = res[i]-'0';
        if(iscarry) --t;
        if(t<0){
            iscarry = true;
            t += 10;
        }
        else iscarry = false;
        res[i] = t+'0';
    }
    if(res[len-1]=='0') res.pop_back();

}
int main(int argc, char* argv[]){
    
    
    string s;
    while(cin>>s){
        reverse(s);
        string sm1 = s;
        minus1(sm1);
        while(sm1!="1"){
            mult(s,sm1);
            minus1(sm1);
        }
        reverse(s);
        cout<<s<<endl;
    }
    return 0;
}
