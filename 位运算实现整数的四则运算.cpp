#include<iostream>
#include<climits>

using std::cin;
using std::cout;
using std::endl;

int add(int a, int b){// a+b 可由不考虑进位的加法(a^b)+ (a+b)产生的进位(a&b)<<1得到， 递推实现直到a&b=0
    int t ;
    while(b!=0){
        t = a^b; 
        b = (a&b)<<1;
        a = t;
//         cout<<a<<' '<<b<<'\n';
    }
    return a;
}
int getNeg(int a){//返回-a，根据补码-a为a各位取反末位+1
    return add(~a,1);
}
int minus(int a, int b){// a-b,用a+(-b)表示
    return add(a,getNeg(b));
}
int multi(int a, int b){ //a*b可表示为a*(b的二进制形式),res = 0,由b的低位到高位，该第i位(由0开始)为1，则res += a<<i
    //该第i位为0则不变
    //如 13*5 = 13*(101) = 13*(100)即13左移2位 + 13*(001)即13左移0位
    
    //cpp中对有符号数的右移为算数右移，即会保留符号位, -1右移1位还是-1， 要想逻辑右移可以将数转化为无符号数
    //cpp中对一个数<<32位以上，会将移位数对32取余,即a<<32 = a<<0还是a
    int res = 0;
//     int digpos = 0;
//     while(b&&(digpos<32)){ //当b为0或已经遍历所有位
//         if(b&1) res = add(res,a<<digpos);
//         ++digpos;
//         b>>=1;
//     }
//     return res;
    
    //优化移位，在移位b时，也移位a
//     while (b&&a) { //a等于0时表示已移位了32次，遍历完了b的所有位数
//         if ((b & 1) != 0) {
//             res = add(res, a);
//         }
//         a <<= 1;
//         b >>= 1;
// //         cout<<a<<' '<<b<<' '<<res<<endl;
//     }
//     return res;
    
    //将a和b转为无符号数
    uint32_t ua = a;
    uint32_t ub = b;
    while(ub){
        if(ub&1) res = add(res,ua);
        ub>>=1;
        ua<<=1;
    }
    return res;
}

bool isneg(int a){
    return ((a>>31)&1)==1?true:false;
}
int dividhelp(int a, int b){ //二进制的除法模拟, 二进制的好处在于商结果位要么为0，要么为1
    int res = 0;
    bool isnega = false;
    bool isnegb = false;
    if(isneg(a)){
        a = getNeg(a);
        isnega = true;
    }
    if(isneg(b)){
        b = getNeg(b);
        isnegb = true;
    }
    for(int i=31;i>=0;i = minus(i,1)){ //表示结果在第i位上的情况
        int diff = minus(a>>i,b); //a>>i - b
        if(!isneg(diff)){ //a>>i -b >=0 , a>=(b<<i), 则res第i位上为1
            res |= (1<<i);
            a = minus(a,b<<i);
        }
//         cout<<res<<'\t';
    }
    return isnega^isnegb?getNeg(res):res;
}

int divid(int a, int b){ //a,b有可能是最小负数，则a，b无法正确的转为相应的正数
    //分4种情况讨论
    if(a>INT_MIN&&b>INT_MIN) return dividhelp(a,b);
    else if(a==INT_MIN&&b==INT_MIN) return 1;
    else if(a<INT_MIN&&b==INT_MIN) return 0;
    else if(a==INT_MIN&&b<INT_MIN){
        int c = dividhelp(a+1,b); // c = (a+1)/b ,结果为c+(a-c*b)/b
        int diff = minus(a,multi(c,b)); //a-c*b
        return add(c,dividhelp(diff,b));
    }
    return 0;
}
int main(int argc, char* argv[]){
    int a,b;
    char op;
    cin>>a>>op>>b;
//     cout<<a<<' '<<op<<' '<<b<<'\n';
    if(op=='+') cout<<add(a,b)<<'\n';
    else if(op=='-') cout<<minus(a,b)<<'\n';
    else if(op=='*') cout<<multi(a,b)<<'\n';
    else if(op=='\\') cout<<divid(a,b)<<'\n';
    
    return 0;
}
