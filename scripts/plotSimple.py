import matplotlib.pyplot as plt
import matplotlib.patches as patches
from random import uniform




class RTreePlot():
    def __init__(self):
        self.fig, self.ax = plt.subplots()
        self.xs = []
        self.ys = []
        self.displayed = False
        
    def addBBox(self,minX,minY,maxX,maxY):
        rect = patches.Rectangle((minX, minY), maxX - minX, maxY - minY, linewidth=1, edgecolor=(uniform(0, 1), uniform(0, 1), uniform(0, 1)), facecolor='none')
        self.ax.add_patch(rect)
        
    def addPoint(self,x,y):
        self.xs.append(x)
        self.ys.append(y)
        
    def display(self):
        if len(self.xs) != 0:
            self.ax.scatter(self.xs, self.ys)
        plt.show()
        

plot = RTreePlot()
plot.addBBox(11704116,1145199616,2141853056,2145084544)
plot.addPoint(360717888,239040064)
plot.display()
