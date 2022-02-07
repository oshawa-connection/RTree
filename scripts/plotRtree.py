from random import uniform
from typing import List
import matplotlib.pyplot as plt
import matplotlib.patches as patches

POINT_HEADER = "[POINT]\n"
BBOX_HEADER = "[BBOX]\n"

xs = [] 
ys = []

fig, ax = plt.subplots()

bboxColourDict = {}

class BBox:
    def __init__(self,id,rect,minX,minY,maxX,maxY):
        self.id = id
        self.rect = rect
        self.minX = minX
        self.minY = minY
        self.maxX =maxX
        self.maxY = maxY

    def centreX(self):
        return (self.maxX + self.minX) / 2.0

    def centreY(self):
        return (self.maxY + self.minY) / 2.0


class Point:
    def __init__(self,bboxID,x,y):
        self.bboxID = bboxID
        self.x = x
        self.y = y

    def getColour(self):
        return bboxColourDict[self.bboxID]

points : List[Point] = []
bboxes: List[BBox] = []
with open("../output/rtree.txt","r") as f:
    while(True):
        result = f.readline()
        if (result == POINT_HEADER):
            idLine = int(f.readline())
            xLine = float(f.readline())
            yLine = float(f.readline())
            
            points.append(Point(idLine,xLine,yLine))

        if (result == BBOX_HEADER):
            # TODO: don't write out the field name, just write out the values.
            idLine = int(f.readline())
            minX = float(f.readline())
            minY = float(f.readline())
            maxX = float(f.readline())
            maxY = float(f.readline())
            bboxColour = (uniform(0, 1), uniform(0, 1), uniform(0, 1))
            bboxColourDict[idLine] = bboxColour
            bboxes.append(BBox(idLine,patches.Rectangle((minX, minY), maxX - minX, maxY - minY, linewidth=1, edgecolor=bboxColour, facecolor='none'),minX, minY,maxX,maxY))
            
        if result == "": # assume no blank lines
            break

bboxIds = []

for point in points:
    bboxIds.append(point.bboxID)

bboxIds = set(bboxIds)

for bbox in bboxes:
    if (bbox.id in bboxIds):
        ax.add_patch(bbox.rect)  
        print(f"{bbox.centreX()}, {bbox.centreY()}")
        ax.text(bbox.centreX(),bbox.centreY(),bbox.id,fontsize=12)

for point in points:
    plt.scatter(point.x,point.y,color=point.getColour())
plt.show()