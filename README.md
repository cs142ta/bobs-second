# THIS IS OLD AND OUTDATED. SOME THINGS ARE ACCURATE, SOME ARE NOT. DON'T USE THIS.

# Bob's minute

### How to use

1. Get the help data
    a. Go to [the in-lab help queue](https://students.cs.byu.edu/~cs142ta/inlab-helpqueue/?login=)
    b. Click `More` then `View Extended Stats`
    c. Select `Span Multiple Days`, select the range you want, and hit the `Update` button
    d. Scroll to the bottom of the results to the secion called `Raw Data`
    e. Highlight and copy all the data, not including the headers
    f. Paste the data into `help-data.csv` and confirm that you got all the information
    ## If the queues revert back to separate pages, this will be relevant, but now they are together so this isn't necessary: g. Repeate these steps with [the online help queue](https://students.cs.byu.edu/~cs142ta/zoom-helpqueue/), and paste the online data after the in-lab data (but in the same spreadsheet)
2. Get the grading data
    Note: This part could use a lot of improvement. I would recommend trying to find a better way than what I've been doing, but my way at least works.
    a. Go to Canvas
    b. Click on `Grades` to get to the Gradebook
    c. Click on the Gear to get to settings, then click `View Gradebook History`
    d. Select the range you want.
       1. Select the begin and end dates
       2. Also select what assignment to use (repeat e-g for each assignment you want to include)
    ## In the old version, if you didn't specify an assignment/TA, the program would automatically ignore any of the assignments we don't care about (Lab Analyses, Orientation Exams, etc.). It is important now to select an assignment.
    e. (This is the part that's awful) Scroll down through all the grades. Canvas loads grade history at ~10 items at a time. I recommend putting your phone or something on the 'down' key and then doing something else while it loads/scrolls.
    f. Once you're done scrolling, highlight and copy all the data, not including the headers. The program is expecting all 7 fields, so include everything.
    g. Paste the data into `grade-data.csv`

3. Run the program
    a. If the code is not compiled yet, compile it with `g++ -o run *.cpp`
    b. Run the program with `./run`
    c. The program writes all help stats to `help-results.csv`, and all the grading stats to `grade-results.csv`.
