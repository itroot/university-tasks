log("This is a js script. 2+2="+(2+2));

function printHausdorff(cubant1, cubant2) {
    log("Hausdorf metric between "+cubant1+" and "+cubant2+" : "+
    hausdorff(cubant1, cubant2)
    );
}

var cubant1=createCubant("/1,1,0,1/");
var cubant2=createCubant("/1,1,1,1/");
log("Cubant: "+cubant1.toString());

printHausdorff(cubant1, cubant2);

