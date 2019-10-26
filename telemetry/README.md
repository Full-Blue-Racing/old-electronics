# Telemetry Software: (INSERT NAME HERE)

If you want to develop software that plots data in real-time in several
different graph types message then I will make a detailed plan but it's
the most difficult task. It is beyong my coding skills/understanding
so you will be on your own. We have something that does this already so
no-one feel obliged to work on it.

# Post race analysis: (INSERT NAME HERE)

You will be given a .csv file containing all the data for a test session.
You need to write some code that will plot all this data in meaningful plots.
The best form for this to be in is an interactive tool that works with the
following steps:
1. Select number of graphs to plot
2. Select time range to consider (universal)
3. Select graph type for each
4. Select data fields for each graph
5. Display graphs

    
## To Do:

1. Get a list of all the data-fields you need to plot. As a base, consult the ECU documentation on Nuclino to see what is gauranteed:
    - Note you need to code this in a way so that additional data-fields are easily added

2. Determine the types of graphs we are interested in. A few examples are:
    - Data against time (e.g. rpm vs time)
    - Data against data (e.g. coordinates of car)
    - Histogram graphs
    - Fast fourier transform

3. Implement the solution in code to perform the above. Some useful features:
    - Add thresholds to data-fields that flags up when data exceeds them, e.g. colour of line you are plotting changes
    - Cursor functionality to read off values from graphs
    - Cursor on one graph also shows the corresponding data-point on other graphs