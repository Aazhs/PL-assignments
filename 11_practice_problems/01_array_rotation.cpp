#include <iostream>
using namespace std;

// How this program works:
// Example: left rotate [1 2 3 4] once -> [2 3 4 1].
// Right rotation once -> [4 1 2 3].
// We use shifting because it is easy to follow; no rotation library is needed.

// Rotation moves elements around the ends without losing any value.
class Array{
    int arr[100], n;
public:
    bool input(){
        cout << "Enter size (1 to 100): ";
        if(!(cin >> n) || n < 1 || n > 100) return false;
        cout << "Enter elements: ";
        for(int i = 0; i < n; i++) if(!(cin >> arr[i])) return false;
        return true;
    }
    void rotate(int k, bool left){
        // n rotations bring the array back to its original order.
        k = (k % n + n) % n;

        // Do one simple rotation at a time, k times.
        for(int step = 0; step < k; step++){
            if(left){
                // Save the first value before shifting everything left.
                int first = arr[0];
                for(int i = 0; i < n - 1; i++){
                    arr[i] = arr[i + 1];
                }
                arr[n - 1] = first;
            }
            else{
                // Save the last value; shift backwards to avoid overwriting.
                int last = arr[n - 1];
                for(int i = n - 1; i > 0; i--){
                    arr[i] = arr[i - 1];
                }
                arr[0] = last;
            }
        }
    }

    void display(){
        for(int i = 0; i < n; i++) cout << arr[i] << " ";
        cout << "\n";
    }
};
// Program starts here: read inputs, then perform the requested operations.
int main(){
    Array a;
    if(!a.input()) return 0;
    int choice, k;
    // Repeat the menu until Exit is chosen or the input ends.
    while(true){
        cout << "\n===== Array Rotation Menu =====\n1. Left rotate\n2. Right rotate\n3. Display\n4. Exit\nEnter choice: ";
        if(!(cin >> choice) || choice == 4) break;
        switch(choice){
            case 1: case 2:
                cout << "Enter k: ";
                if(!(cin >> k)) return 0;
                a.rotate(k, choice == 1);
                a.display();
                break;
            case 3: a.display(); break;
            default: cout << "Invalid choice.\n";
        }
    }
}
