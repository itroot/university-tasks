(function() {
System.setPenWidth(1);
System.setReperSize(3);
var cubant=createCubant("/1,1,2/");
System.print(cubant.dimension());
System.drawCubant(cubant);
System.setPenWidth(5);
System.setColor(255,255,0);
System.drawCubantFromString("/2,1,1/");
}
)()