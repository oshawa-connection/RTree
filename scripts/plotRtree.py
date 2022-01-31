import re

POINT_HEADER = "[POINT]\n"
BBOX_HEADER = "[BBOX]\n"

with open("../output/rtree.txt","r") as f:
    while(True):
        result = f.readline()
        if (result == POINT_HEADER):
            # print("POINT")
            pass
        if (result == BBOX_HEADER):
            # TODO: don't write out the field name, just write out the values.
            idLine = f.readline()
            id = int(re.search('id=(.*)\n', idLine).group(1))
            #so now read the next 5 lines.
            print(id)
        if result == "": # assume no blank lines
            break