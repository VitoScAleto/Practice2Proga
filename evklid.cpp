#include <iostream>
using namespace std;

tuple<int, int, int> evklid(int a, int b, int x, int y){
    tuple<int, int, int> X = make_tuple(a, 1, 0);
    tuple<int, int, int> Y = make_tuple(b, 0, 1);
    cout << get<0>(X) << "\t" << get<1>(X) << "\t" << get<2>(X) << endl;
    cout << get<0>(Y) << "\t" << get<1>(Y) << "\t" << get<2>(Y) << endl;

    while (get<0>(Y) != 0) {
        int Q = get<0>(X) / get<0>(Y);
        tuple<int, int, int> T = make_tuple(get<0>(X) % get<0>(Y), get<1>(X) - Q * get<1>(Y), get<2>(X) - Q * get<2>(Y));
        cout << get<0>(T) << "\t" << get<1>(T) << "\t" << get<2>(T) << "\t" << Q << endl;
        X = Y;
        Y = T;
    }

    return X;
}

int main(){
    int a = 28;
    int b = 19;
    int x = 0, y = 0;
    tuple<int, int, int> result = evklid(a,b,x,y);

    cout << endl;
    cout << " "<< a << " * (" << get<1> (result) << ") + " << b << " * ("<< get<2> (result) << ") = " << get<0> (result) << endl;

    return 0;
}
