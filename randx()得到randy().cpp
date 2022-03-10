// The rand7() API is already defined for you.
// int rand7();
// @return a random integer in the range 1 to 7



// randx()生成randy(),当x>y时，可直接用randx()生成1-x的随机数t，若t>y则在生成随机数，直到t<=y，将t返回即可
// 概率为：1/x + (x-y)/x^2 + (x-y)^2/x^3 + ... + (x-y)^(n-1)/x^n, 即第一次命中概率+第二次命中概率+...+第n次命中的概率
// =  1/x*(1+(x-y)/x+(x-y/x)^2+...+(x-y/x)^(n-1))
// = 等比级数求和 = 1/x *(1+(x-y)/y) = 1/x *x/y = 1/y

// 特别的当x为y的倍数时，可以直接用randx()%y+1生成rand()y, 如rand4()%2+1 =>rand2()

// 当x<y时，一个常见的思路为利用randx()生成一个randt(),t>y即可
// 存在这样一个事实，(randx()-1)*y + randy() => randx*y(), 如(rand7()-1)*5 + rand5() => rand35()
// 但在本题中我们只能使用rand7(), 所以(rand7()-1)*7 + rand7() =>rand49()

// 利用rand49()，可以直接生成rand10()
//当该方法时间复杂度较高，约为16ms
// 问题在于我们等概率生成了数字1-49，但我们只使用了1-10，11-49之间的数都被舍弃，导致算法效率很差
// 我们应该减少舍弃的数，我们可以使用等概率生成的数字1-40，即生成rand40(),再由rand40()直接生成rand10(),即rand40()%10+1=>rand10()
// 为什么生成rand40()?,因为40是距离49最近的10的倍数的数字，我们应尽可能的减少舍弃的数字

//进一步我们可以利用被舍弃的数字 41-49，将该数字减40生成1-9，即我们得到了rand9(),再利用rand9(),rand7()可生成rand63()
//再利用rand63(),舍弃61-63得到rand60(),由rand60()%10+1 =>rand10()
//进而利用舍弃的61-63得到rand3(),由rand3(),rand7()生成rand21(), 此时利用rand21()只需要舍弃1个数字即21即可生成rand10()

class Solution {
public:
    int rand10() { 
        int num = (rand7()-1)*7 + rand7(); // 生成rand49()

        //直接用rand49()生成rand10(),效率不高
        // while(num>10) num = (rand7()-1)*7 + rand7();

        //用rand49()生成rand40(),再利用rand40()%10+1=>rand10()，生成rand10(),效率高一点
        // while(num>40) num = (rand7()-1)*7 + rand7();//循环退出时，num等价于rand40()生成的数
        // num = num%10+1; //rand40()%10+1=>rand10()，生成rand10()

        //继续上面的步骤但利用舍弃的数字
        while(true){
            num = (rand7()-1)*7+rand7();
            if(num<=40){
                num = num%10+1;
                break;
            }
            else{
                num -= 40; //生成rand9()
                num = (num-1)*7+rand7(); //生成rand63()
                if(num<=60){
                    num = num%10+1;
                    break;
                }
                else{
                    num -= 60; //生成rand3()
                    num = (num-1)*7+rand7(); //生成rand21()
                    if(num<=20){
                        num = num%10+1;
                        break;
                    }
                    
                }
            }
        }

        return num;
    }
};
