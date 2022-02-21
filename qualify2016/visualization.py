# to start with, we will need matplotlib.pyplot
from matplotlib import pyplot
# next, i will set up a 8 x 8 2d matrix, with random bits as elements (0 or 1); 
# for randomization of integers (0 or 1) I use the random module in Python;
# for building each row in the 2d matrix I use list comprehension in Python
import random
data = [[random.randint(a=0,b=1) for x in range(0,8)], # row 1
        [random.randint(a=0,b=1) for x in range(0,8)], # row 2
        [random.randint(a=0,b=1) for x in range(0,8)], # row 3
        [random.randint(a=0,b=1) for x in range(0,8)], # row 4
        [random.randint(a=0,b=1) for x in range(0,8)], # row 5
        [random.randint(a=0,b=1) for x in range(0,8)], # row 6
        [random.randint(a=0,b=1) for x in range(0,8)], # row 7
        [random.randint(a=0,b=1) for x in range(0,8)]] # row 8
# display the 2d data matrix
data

data1 = [
    [0, 0, 0, 0, 0],
    [0, -1, 0, -2, 0],
    [0, 0, 0, 0, 0],
    [0, 0, -1, 0, 0],
    [0, 0, 0, 0, -2],
]

data2 = [
    [0, 1, 0, 0, 0],
    [0, 0, 0, 0, 0],
    [1, 0, 12, 0, 0],
    [0, 0, 0, 3, 0],
    [0, 0, 0, 0, 0],
]

# we will visualize the bits of this data matrix with matplot.pyplot; 
# the .imshow function from Python can do the job
pyplot.figure(figsize=(5,5))
pyplot.imshow(data1)
pyplot.colorbar()
pyplot.show()
    
pyplot.figure(figsize=(5,5))
pyplot.imshow(data2, cmap="gray")
pyplot.colorbar()
pyplot.show()