# Spotify Music Player System - Change Details

## Context
Project run karte waqt compile error aa raha tha. Error `stack` aur `queue` type resolution se related tha.

---

## File-wise Changes

### 1) `strategies/RandomPlayStrategy.hpp`

#### Kya change kiya
- `#include <stack>` add kiya.
- `#include <vector>` explicitly add kiya.
- Include line par short comment add kiya taaki clear ho ki compile error fix ke liye include add hua.

#### Kyun karna pada
- Is file me `stack<Song*> history;` use ho raha tha.
- `<stack>` include nahi tha, isliye compiler error aaya:  
  **`'stack' does not name a type`**
- `remainingSongs` ke liye vector use ho raha tha; indirect include dependency avoid karne ke liye `<vector>` bhi explicitly add kiya.

---

### 2) `strategies/CustomQueueStrategy.hpp`

#### Kya change kiya
- `#include <queue>` add kiya.
- `#include <stack>` add kiya.
- `using namespace std;` add kiya (file me `queue`/`stack` unqualified use ho rahe the).
- Include lines par short comments add kiye taaki reason clear rahe.

#### Kyun karna pada
- Is file me:
  - `queue<Song*> nextQueue;`
  - `stack<Song*> prevStack;`
  use ho raha tha.
- `<queue>` aur `<stack>` includes missing the, isliye errors aaye:
  - **`'queue' does not name a type`**
  - **`'stack' does not name a type`**
- `using namespace std;` ke bina unqualified `queue`/`stack` compile issue de sakte the.

---

## Validation (Run/Build Result)

### Build command
`g++ -std=c++17 -Wall -Wextra -O2 main.cpp -o main.exe`

### Result
- Build successful after above changes.
- Program successfully run hua aur playback logs console me aaye.

---

## Remaining Non-blocking Note

- `PlayStrategy.hpp` me `addToNext(Song* song)` ke parameter ka warning aa raha hai (`unused parameter`), lekin ye run/compile block nahi karta.
- Is request ke scope me sirf run-breaking errors fix kiye gaye.
