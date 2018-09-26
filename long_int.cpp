#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <sstream>
#include <iomanip>

using namespace std;

const int base = 1000000000; //The base number = 10^9

class long_int{
private:
    vector <int> n; //We'll have a vector of numbers and each will be less than 10^9
public:
    long_int(){
        n.push_back(0); //initializing
    }
    long_int(string x){ //we'll initialize everything from string
        for (int i = x.size(); i > 0; i-=9){
            if (i < 9){
                n.push_back(atoi (x.substr(0, i).c_str()));
            }
            else{
                n.push_back(atoi (x.substr(i-9, 9).c_str()));
            }
        }
    }
    long_int(vector <int> x){
        n = x;
    }
    string get() const{
        string output;
        stringstream ss;
        if (n.size() == 0){
            return "0";
        }
        else{
            ss << n[n.size()-1];
            output += ss.str();
            for (int i = n.size()-2; i >= 0; i--){
                ss.str("");
                ss << setw(9) << setfill('0') << n[i];
                output += ss.str();
            }
        }
        return output;
    }
    friend ostream& operator<<(ostream& os, const long_int& x);
    int operator [] (int i){
        return n[i];
    }
    int size_9(){
        return n.size();
    }
    void operator += (long_int b){
        int buff = 0;
        for (int i = 0; i < max(size_9(), b.size_9()) || buff; i++){
            if (i == size_9()){
                n.push_back(0);
            }
            n[i] += buff + (i < b.size_9() ? b[i] : 0);
            buff = (n[i] >= base);
            if (buff){
                n[i] -= base;
            }
        }
    }
    long_int operator + (long_int b){
        long_int c(n);
        c += b;
        return c;
    }
};

istream& operator >> ( istream& is, long_int& x){
    string s;
    is >> s;
    x = long_int(s);
    return is;
}

ostream& operator << (ostream& os, const long_int& x){
    os << x.get();
    return os;
}

int main () {
    long_int a, b;
    cin >> a >> b;
    long_int c;
    c = a + b;
    cout << c;
    return 0;
}
