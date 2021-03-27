#include <iostream>
#include <algorithm>
#include <vector>
#include <random>

using namespace std;

bool comp1(int a)
{
    return a % 2 == 1;
}

bool comp2(int a)
{
    if(a < 0){
        a =-a;
    }
    if(a == 0){
        return false;
    }
    if(a == 1){
        return false;
    }
    int n = (int) sqrt(a);
    for(int i = 2; i <= n; i++){
        if(a % i == 0)
            return false;
    }
    return true;
}

int comp3(int a)
{
    return a * a;
}

int comp4(int a, int b)
{
    return a - b;
}

int comp5(int a)
{
    if(a < 0)
    {
        return 0;
    }
    else
    {
        return a;
    }
}
int main()
{
    vector<int> s1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    vector<int> s1_srt;
    vector<int>::iterator ip;

    int n, i, temp, pos;

    cout <<"Type how many numbers do you want to add"<< endl;
    cin >> n;
    cout << "Type in the numbers" << endl;

    for(int i = 0; i < n; i++)
    {
        cin >> temp;
        s1.push_back(temp);
    }

    auto rng = default_random_engine {};
    sort(s1.begin(), s1.end());
    ip = std::unique(s1.begin(), s1.begin() + 10 + n);
    s1.resize(std::distance(s1.begin(), ip));
    shuffle(begin(s1), end(s1), rng);
    
    cout << count_if(s1.begin(), s1.end(), comp1) << endl; 
    cout << *min_element(s1.begin(), s1.end()) << " - min in p1" << endl;
    cout << *max_element(s1.begin(), s1.end()) << " - max in p1" << endl;
    cout << *find_if(s1.begin(), s1.end(), comp2) << endl; 
    transform(s1.begin(), s1.end(), s1.begin(), comp3);

    vector <int> s2(s1.size());
    generate(s2.begin(), s2.end(), rand);
    cout << accumulate(s2.begin(), s2.end(), 0) << endl; 
    fill(s2.begin(), s2.begin() + 2, 1);

    vector<int> s3;
    transform(s1.begin(), s1.end(), s2.begin(), back_inserter(s3), comp4);
    transform(s3.begin(), s3.end(), s3.begin(), comp5);
    remove(s3.begin(), s3.end(), 0);
    reverse(s3.begin(), s3.end());
    sort(s3.begin(), s3.end());
    cout << s3[s3.size() - 1] << " " << s3[s3.size() - 2] << " " << s3[s3.size() - 3];

    return 0;
}