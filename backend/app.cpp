#include <iostream>
#include <unistd.h> // for sleep
using namespace std;

int main() {
    cout << "Served by backend: PES1UG23CS625" << endl;
    // Keep the container alive for NGINX to find it
    while (true) {
        sleep(100); 
    }
    return 0;
}