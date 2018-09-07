/*题意：
 *
 * 有珍珠和线，问能否重新安排使得相邻珍珠之间的线的数量相等。
 *
 * 思路：
 *
 * 首先，珍珠为0或者线为0，那么都满足条件；
 *
 * 其次，如果珍珠的个数大于线的个数，那么肯定不满足条件；
 *
 * 然后，如果线的个数能够被珍珠整除，那么满足条件，否则不满足。*/



#include <iostream>
#include <string>
#include <stdio.h>
using namespace std;
int main()
{
    string s;
    cin >> s;
    int l = 0,p = 0;
    for (int i = 0;i < s.size();i++)
    {
        if (s[i] == 'o') p++;
        else l++;
    }
    if (l == 0 || p == 0) puts("Yes");
    else 
    {
        if (p > l) puts("no");
        else if (l % p == 0) puts("yes");
        else puts("no");
    }
    return 0;
}
