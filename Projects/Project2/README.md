# Project 2; arXiv Search Engine

### Collaborators: Sam Disharoon & Brock Forsythe

## Description

This project was to implement a search engine for various articles that are imported from a large file.  The algorithms that were used were a BST for the search function as well as the Page Rank algorithm for authority and hub scores.

### Rooms for improvement

Basically everywhere.  We attempted to parallelize everything with no success.  The Page Rank algorithm is non-existent so the authority and hub scores are not availible.  We do have the amount of pages each paper cites, but thats as far as we got. 

## Questions

*A)How long does it take to process the raw data into your index format?* 

A very long time. The citations file doesn't take long, but we literally only have it display how many papers each one cites.  Still takes ~5 seconds. The search function takes a while and only works effecitely with around 10,000 articles.

*B)How long does it take to load your database into memory?* 

A long time as well for the same reasons as *A*.

*C)How long does it take to return the results to the user?* 

Not terribly long, but we are hindered because it isn't in parallel.

*D)Where is there room for improvement?* 

LITERALLY EVERYWHERE for many reasons displayed above.

*E)Would your program make a decent "Google for research papers?"* 

Absolutely not. 
