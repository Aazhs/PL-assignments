#include <iostream>
using namespace std;

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
        int temp[100];
        // Reduce large rotations; negative k rotates in the opposite direction.
        k = (k % n + n) % n;
        for(int i = 0; i < n; i++){
            int position = left ? (i - k + n) % n : (i + k) % n;
            temp[position] = arr[i];
        }
        for(int i = 0; i < n; i++) arr[i] = temp[i];
    }
    void display(){
        for(int i = 0; i < n; i++) cout << arr[i] << " ";
        cout << "\n";
    }
};
int main(){
    Array a;
    if(!a.input()) return 0;
    int choice, k;
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
