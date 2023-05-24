
float toNDC(float coord,float totalCoord) {
    float percentage = (coord/totalCoord)*100;
    return ((percentage*2)/100-1);
} 