###Program 6 - Trie Again

---
This is the second part to the previous program. Once again you will be implementing a rhyming dictionary, where words are stored in reverse order in the trie. Once again you will initially create the trie using all the dictionary words, using the same dictionary file used in program 5. One drawback to implementing a Trie using an array of 26 letters for all possible children is that many of those array entries are not used, particularly further down the tree.  **For this program you must implement the children of each node using a Left-child right-sibling representation, where you use a linked list for each node to store only those entries for children that actually exist.**
___
#####Implementation Guidelines

For comparison purposes consider the trie shown below duplicated from the previous assignment, representing in backwards-order the seven words: as, has, rakes, sakes, takes, yikes, and kites:

![TrieReversed](http://i.imgur.com/iBlmeKB.png)

Instead of storing an array of 26 node pointers corresponding to each alphabetic character at each node, we instead create a linked list at each node, only storing the ones that are actually used. In addition at the end of each of these linked lists we add an extra node to point back to the parent, which will help later with traversals. This version of the trie looks like:

![Imgur](http://i.imgur.com/Po9Zq5I.png)

Rather than point to all of its children, a node points to a list of its children. It points to the leftmost child in the list, and each child in the list points to the sibling to the right of it. We add one extra node at the end of the list to implement a pointer back up to the parent, using the child pointer in that extra node. With this in mind the Node struct should contain the following fields:

1.     char for the letter
2.     Boolean value indicating whether or not this node represents the starting position for a word
3.     Node * for the Leftmost child pointer
4.     Node * for the Right sibling pointer. 
The root node does not represent any letter, and the last sibling on each list (that points to the parent) can be identified because it has a right sibling pointer set to NULL.  

___
#####User Interface
This program is interactive. You will need to implement an iterator (a.k.a. cursor) that moves about the tree, depending on the user input.  Once this tree has been built, implement the following interactive commands, shown with the number of points each is worth: 


Command    |Description|
-----------|------------
**f str**  | Find the string str in the tree.  This updates the position reference. Give an error message if str is not found and reset the cursor to NULL.
**p n**    | Print the next n words from the current position reference, one per line. Successive calls to this command should print the next n words each time until there are no more. Note that these words will not be displayed in alphabetical order.
**a str**  | Add word str to the tree.
**d str**  | Delete word str from the tree, giving a warning if it doesn’t exist.  Reset the position reference to the root, but only after a successful deletion.
**?**      |  Display on-line help (should look like something like this list, with longer textual explanations).
**x**      | Exit the program.

You may assume perfect input.  A brief summary of available commands must be displayed by your program, that should look like the following:

	Options:   
	f str  Find str   
	p n    Print next n   
	a str  Add str           
	d str  Delete str   
	? Help                   
	x Exit

	Your instruction:

After the user gives some instruction and gets some output, your program will again display the above menu, continuing to do so until the user selects 'x' to exit the program.  If your program has not implemented one of the features, then when that feature is selected it should give a message indicating that feature has not been implemented.  