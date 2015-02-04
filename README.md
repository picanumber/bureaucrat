# bureaucrat
A c++ library of useful but mundane things

time lapse
---
Mechanism to easily measure running time of C++ callables using the **chrono** library. 

Example usage :

```c++
// assuming mandatory include and using declarations are present
int main()
{
     vector<int> ar(2000000); 
     iota(begin(ar), end(ar), 0); 

     // 1. Client just wants a timing result : call execution
     cout << measure<std::chrono::nanoseconds>::execution(
     accumulate<decltype(begin(ar)), int>, begin(ar), end(ar), 0) << endl;

     // 2. Client want to preprocess timing : call duration, process result and then query the count
     auto avg = measure<>::duration(accumulate<decltype(begin(ar)), int>, begin(ar), end(ar), 0);
     avg     += measure<>::duration(accumulate<decltype(begin(ar)), int>, begin(ar), end(ar), 0);
     avg     += measure<>::duration(accumulate<decltype(begin(ar)), int>, begin(ar), end(ar), 0);
     cout << (avg / 3.).count() << endl;
}
```



