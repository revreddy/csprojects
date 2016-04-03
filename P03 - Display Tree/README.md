###Program 3 - Display Tree

---
#####Objectives:

Write a function that takes a tree and prints it out so that it looks like a tree.  Use heapForProg3.cpp as a starting point. This program builds the heap by taking input values from the user, followed by -1.  Rewrite the displayQueue(...) function so that instead of heaps looking (for example) like:
1492
1783 1776
1804 1865 1945 1963
1918 2001 1941

they look something like:

                      ___1492___
                     /          \
                  1783           1776
                 /    \         /    \
             1804      1865  1945    1963
            /   \      /
          1918 2001  1941
---
#####Guidelines:
- Assume a screen size of 80 columns wide and 50 rows high max.
- Use only "ASCII graphics," meaning regular characters you would find on a keyboard
- While your output doesn't have to look exactly like the above, it should have connective characters between rows and should look reasonably balanced.
- Consider creating an "output array" that you can easily manipulate.  To help center elements consider first finding the widest row.  
- You may assume each number is 1..4 digits, and each can be displayed in a fixed 4-digit "window"
- Some hardcoding allowed, but should implement some other branching and looping controls as well.
