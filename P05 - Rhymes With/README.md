###Program 5 - Rhymes With
---
	But yield who will to their separation,
	My object in living is to unite
	My avocation and my vocation
	As my two eyes make one in sight.
	Only where love and need are one,
	And the work is play for mortal stakes,
	Is the deed ever really done
	For Heaven and the future's ______.
                - Robert Frost  (1874 - 1963), from Two Tramps in Mud Time

What should the missing last word be?  cakes, sheikhs, quakes, rattlesnakes, breaks, toothaches ... are some options.  

A useful tool in such circumstances is a rhyming dictionary which is just like a normal dictionary except we lookup words starting from the end of the word rather than from the beginning.  We will make the simplifying assumption that we will match only the same ending letters (e.g. words rhyming with stakes such as cakes, takes) and not words that are plurals (toothaches) or other spellings (sheikhs) that have similar sounds.

#####Building the Trie:

To do this we will store our dictionary words in a trie which is a special kind of tree data structure that stores each word prefix only once. For more more information see Aho & Ullman Ch. 5 pp. 233-234, or Wikipedia.  Trie was originally supposed to be pronounced "tree" but common usage is "try" to differentiate it from a "tree."

For instance consider how we might store the following set of words in a trie, where an asterisk next to a letter indicates that it is a word: {ha, be, has, bat, hat, ham, bet}

![Trie](http://i.imgur.com/sZpudZn.png)

Notice how each unique prefix is only stored once.   In our case we will store our words backwards, since we are interested in matching ending letters of words to give suggestions for rhyming.  The root node has no letter and is just used as a starting point.

For this backwards representation, for example, consider the trie below representing the seven words: as, has, rakes, sakes, takes, yikes, and kites:

![TrieReversed](http://i.imgur.com/iBlmeKB.png)

Now an asterisk next to a node shows that a word is formed starting from that position, accumulating the letters along parent links until reaching the root node.  To use this tree consider attempting to find all words ending in -akes, such as for our poem above.  We do a depth-first search of the tree using the letters starting from the end of the string.  Thus we first find s, then e, then k and then a.  All descendants from this point on (e.g. doing some sort of traversal from here) are words that end in -akes, giving us what we want.  In this case the words printed would be: rakes sakes takes

---
#####Output:

Running this program should look like the following:

	Enter the suffix to find rhyming words: akes
	Found 3 words which are:
	rakes sakes takes

	Exiting program...
   
In the above example the user input (shown in bold) was:   akes  
In this example we are assuming that the tree shown above was used, where there was in fact only 3 words that matched with suffix  akes.  The number of words found and all the actual matching words should be displayed.

---
#####Guidelines:
Hard-code the dictionary filename to be dictionary.txt. You can download the dictionary from here.  The dictionary contains 40,437 words, though your program must handle a dictionary of any number of words.  See the sample code from the recent lab for an example of how to read in the dictionary from the dictionary file with the words in reversed order.  When you read in each word you should filter out any words that have non-alphabetic characters.

Each node should keep track of all possible children. Since we are limiting our words to those containing only alphabetic characters and since we are changing all dictionary input into lower-case this means each node will have a maximum of 26 children, one for each letter of the alphabet. This can be implemented in a straightforward fashion as an array of 26 Node pointers. Each node must also have a field indicating whether or not the string starting from that position is a valid dictionary word. 

Summarizing, your node struct must have:

1. char for the letter
2. boolean (or integer) indicating if the string starting at this letter is a dictionary word
3. array of 26 Node *, one for each child node for each letter a..z of the alphabet if they exist.

Grading for this program will likely be all-or-nothing for execution points.
