#! /usr/bin/python3

from PIL import Image
import math
import random

def length(a):
    (x, y) = a
    return math.sqrt(x*x+y*y)

def scale(a):
    (x, y) = a
    l = math.sqrt(x*x+y*y)
    if l == 0:
        return a
    return (x/l, y/l)

def vec(a, b):
    """returns vector from a to b"""
    (xa, ya) = a
    (xb, yb) = b
    return (xb-xa,yb-ya)

def dot(a, b):
    (xa, ya) = a
    (xb, yb) = b
    return xa*xb + ya*yb

def fade(x):
    return 6*pow(x, 5)-15*pow(x, 4)+10*pow(x,3)

def lerp(t, a, b):
    return (1-t)*a + t*b

def noise(x, y, g):
    X = int(x)
    Y = int(y)
    x = x - X
    y = y - Y
    x = fade(x)
    y = fade(y)
    gaa = g[X][Y]
    gab = g[X][Y+1]
    gba = g[X+1][Y]
    gbb = g[X+1][Y+1]
    paa = (0,0)
    pab = (0,0+1)
    pba = (0+1,0)
    pbb = (0+1,0+1)
    p = (x,y)
    daa = vec(paa,p)
    dab = vec(pab,p)
    dba = vec(pba,p)
    dbb = vec(pbb,p)
    maa = dot(daa,gaa)
    mab = dot(dab,gab)
    mba = dot(dba,gba)
    mbb = dot(dbb,gbb)
    v1 = lerp(x, maa, mba)
    v2 = lerp(x, mab, mbb)
    av = lerp(y, v1, v2)
    return (av/2) + 0.5
    
def randg():
    r = random.randint(0,3)
    (x,y) = (0,0)
    if r == 0:
        (x,y) = (1,1)
    elif r == 1:
        (x,y) = (-1,1)
    elif r == 2:
        (x,y) = (1,-1)
    elif r == 3:
        (x,y) = (-1,-1)
    #elif r == 4:
    #    (x,y) = (0,1)
    #elif r == 5:
    #    (x,y) = (0,-1)
    #elif r == 6:
    #    (x,y) = (1,0)
    #elif r == 7:
    #    (x,y) = (-1,0)
    else:
        print("Erreur")
    return (x,y)

def randg2():
    return scale((random.randint(-10,10), random.randint(-10,10)))

def main():
    c = 6
    sizeOne = 60
    s = sizeOne*c
    g = [[randg() for x in range(c+1)] for i in range(c+1)]
    img = Image.new('RGB', (s, s), "black")
    t = []
    pixels = img.load()
    for x in range(s):
        for y in range(s):
            color = noise(x/sizeOne, y/sizeOne, g)
            t.append(color)
            print(color)
            pixels[x,y] = int(color*255)
    print("max: ", max(t))
    print("min: ", min(t))
    img.save("image.png")
    img.show()

main()
